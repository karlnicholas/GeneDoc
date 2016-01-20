/*
    GeneDoc: Multiple Sequence Alignment Editing Utility
    Copyright (C) 2000, Karl Nicholas

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
// geneddoc.cpp : implementation of the CGenedocDoc class
//

#include "stdafx.h"
#include <ctype.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


int
CGenedocDoc::FindScore ( DWORD Location, DWORD *nStartRange, DWORD *nEndRange )
{
	CGeneSegment *tCGSeg;
	HANDLE tSegHandle;

	tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetHead();
	tSegHandle = tCGSeg->GetTextHandle();
	GeneStor *pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
	if ( pGeneStor == NULL ) {
		AfxMessageBox("FindScore:GlobalLock:Fail:1");
		return 0;
	}

	DWORD SegLength = tCGSeg->GetTextLength();

	DWORD StartCount = Location;
	DWORD EndCount = Location;

	if ( pGeneStor[StartCount].CharScore == 0 ) {
		GlobalUnlock( tSegHandle );
		return 0;
	}

	while ( 1 ) {
		if ( pGeneStor[StartCount].CharScore == 0 ) {
			StartCount++;
			break;
		}
		if ( pGeneStor[StartCount].CharScore == 3 ) {
			break;
		}
		if ( pGeneStor[StartCount].CharScore == 4 ) {
			break;
		}
		if ( StartCount == 0 ) {
			break;
		}
		StartCount--;
	}

	do {
		if ( pGeneStor[EndCount].CharScore == 0 ) {
			EndCount--;
			break;
		}
		if ( pGeneStor[EndCount].CharScore == 5 ) {
			break;
		}
		if ( pGeneStor[EndCount].CharScore == 6 ) {
			break;
		}
	} while ( (++EndCount) < SegLength );

	GlobalUnlock( tSegHandle );

	*nStartRange = StartCount;
	*nEndRange = EndCount;

	return 1;

}


void
CGenedocDoc::Score( DWORD *nStartRange, DWORD *nEndRange )
{
	int RowCount;
	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;
	DWORD tCount;
	CString PathName;

	ShadeSegStc *pSegArr;
	
	if ( pGSFiller == NULL ) {
		return;
	}
	

	unsigned long Score = 0;


	RowCount = pGSFiller->SegDataList.GetCount() - 1;	// Subtract 1 for comment row.
	
	DWORD SegLength = ((CGeneSegment*)pGSFiller->SegDataList.GetHead())->GetTextLength();
	
	pSegArr = new ShadeSegStc[RowCount + 1];	// Gonna need access to comment row
	if ( pSegArr == 0 ) { 
		AfxMessageBox( "Score:new:fail:1" );
		return;
	}
	
	CGeneSegment *tCGSeg;
	int i = 0;
	HANDLE tSegHandle;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		pSegArr[i].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
		pSegArr[i].pCGSeg = tCGSeg;
		if ( pSegArr[i].pGeneStor == NULL ) {
			AfxMessageBox("Score:GlobalLock:Fail:1");
			delete pSegArr;
			return;
		}
		i++;
	}
	

	AfxGetApp()->DoWaitCursor(1);
	



	if ( m_UserVars.m_ScoringMethod == SCORETREE || m_UserVars.m_ScoringMethod == SCORENUMB ) {
		// option flags
		m_NumbTreeFlag = (m_UserVars.m_ScoringMethod == SCORENUMB);

//		m_TreeDebugOutput = 1;
		//
		if ( m_TreeDebugOutput ) {
			GetTempFileName(PathName);
		}

		if ( !TreeScore(  nStartRange, nEndRange, &Score, RowCount, pSegArr, PathName ) ) {
			AfxGetApp()->DoWaitCursor(-1);
			delete pSegArr;
			return;
		}
	} else if ( m_UserVars.m_ScoringMethod == SCOREPAIR ) {
		if ( !PairWiseScore(  nStartRange, nEndRange, &Score, RowCount, pSegArr ) ) {
			AfxGetApp()->DoWaitCursor(-1);
			delete pSegArr;
			return;
		}
	} else if ( m_UserVars.m_ScoringMethod == SCORELOGODD ) {
		if ( !LogOddsScore(  nStartRange, nEndRange, &Score, RowCount, pSegArr ) ) {
			AfxGetApp()->DoWaitCursor(-1);
			delete pSegArr;
			return;
		}
	}


	char ScoreBuff[33];
	
	_ultoa( Score, ScoreBuff, 10 );
	
	char *ncp = ScoreBuff;
	while (*ncp == ' ' ) ++ncp;
	int sclen = strlen ( ncp );
	long DotGap = ((EndRange - StartRange - sclen) / 2) + 1;
	if ( DotGap < 0 ) DotGap = 0;
	
	
	for ( tCount = StartRange; tCount <= EndRange; tCount = tCount + 1L ) {	 // Drawing loop
		if ( tCount == StartRange ) {
			DWORD CheckCount = tCount;
			(pSegArr[0].pGeneStor)[tCount].CharScore = 3;
			while ( 1 ) {
				if ( CheckCount == 0 ) {
					CheckCount--;
					break;
				}
				CheckCount--;
				if ( (pSegArr[0].pGeneStor)[CheckCount].CharScore != 0
					&& (pSegArr[0].pGeneStor)[CheckCount].CharScore <= 4 
				) {
					(pSegArr[0].pGeneStor)[CheckCount].CharDisplay = ' ';
					(pSegArr[0].pGeneStor)[CheckCount].CharScore = 0;
				} else {
					break;
				}
			}
			*nStartRange = CheckCount + 1;
		} else if ( tCount == EndRange ) {
			// Right mode Position
			DWORD CheckCount = EndRange;
			(pSegArr[0].pGeneStor)[tCount].CharScore = 5;
			while ( (++CheckCount) < SegLength ) {
				if ( (pSegArr[0].pGeneStor)[CheckCount].CharScore != 0 
					&& (
						(pSegArr[0].pGeneStor)[CheckCount].CharScore <= 2 
						|| (pSegArr[0].pGeneStor)[CheckCount].CharScore >= 5
					)
				) {
					(pSegArr[0].pGeneStor)[CheckCount].CharDisplay = ' ';
					(pSegArr[0].pGeneStor)[CheckCount].CharScore = 0;
				} else {
					break;
				}
			}
			*nEndRange = CheckCount - 1;
		} else {
			(pSegArr[0].pGeneStor)[tCount].CharScore = 1;
		}

		if ( tCount < (StartRange + DotGap) ) {
			(pSegArr[0].pGeneStor)[tCount].CharDisplay = ' ';	// .
		} else if ( tCount >= (StartRange + DotGap + sclen) ) {
			(pSegArr[0].pGeneStor)[tCount].CharDisplay = ' ';	// .
		} else {
			(pSegArr[0].pGeneStor)[tCount].CharDisplay = ncp[sclen - (StartRange + DotGap + sclen - tCount)];
		}

	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		GlobalUnlock( tSegHandle );
	}
	delete pSegArr;

	if ( m_TreeDebugOutput ) {
		if ( m_pTextView == NULL ) {
	
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pScoreInfoView->Invalidate();
		}
		m_pTextView->LoadFile(PathName);
		DeleteTempFile( PathName );
	}

	
	AfxGetApp()->DoWaitCursor(-1);
}

/*
int
CGenedocDoc::ScoreCurrentArray( char n1, char n2 ) 
{
	
	int Loc1, Loc2;
	
//	n1 = toupper(n1);
//	n2 = toupper(n2);

//	Loc1 = IndexChar ( n1 );
		
	if ( Loc1 == INT_MIN ) {
		return INT_MIN;	// No Match
	}

//	Loc2 = IndexChar ( n2 );

	if ( Loc2 == INT_MIN ) {
		return INT_MIN;	// No Match
	}

	return ScoreArray[Loc1][Loc2];
	
}

*/