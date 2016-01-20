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

#include "stdafx.h"


void 
CGenedocDoc::AutoShadeContrast(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{

	int i;

	int tRC = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here

	ShadeSegStc *pOSegArr = new ShadeSegStc[tRC];	// Gonna need access to comment row here

	if ( pOSegArr == 0 ) {
		AfxMessageBox("AutoShadeQuantify:New Fail 1");
		return;
	}

	int GrpNum = 0;
	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars* pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		GrpNum++;
		if ( pDV->GetGroupName() == DisplayVars->GetGroupName() ) break;
	}

	int pSegCount = 0;
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE && tCGSeg->m_DisplayGroup != GrpNum ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			pOSegArr[pSegCount].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			pOSegArr[pSegCount].pCGSeg = tCGSeg;
			if ( pOSegArr[pSegCount].pGeneStor == NULL) {
				AfxMessageBox("AutoShade:GlobalLock:Fail:1");
				delete pOSegArr;
				return;
			}
			pSegCount++;
		}
	}


	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	
	// init locations

	int PWScrG, PWScrO;
	
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
	
		for ( i = 0; i < RowCount; ++i ) {
			// Lets Clear out old shades while here.
			GetLevelColors( DisplayVars, 0, 
				&(pSegArr[i].pGeneStor)[tCount].TextColor, 
				&(pSegArr[i].pGeneStor)[tCount].BackColor
			);

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			// Reset Display Char while here.
			if ( DisplayVars->GetResidueMode() == 0 ) {
				if ( m_UserVars.m_ResidueUpper == 1 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
				} else if ( m_UserVars.m_ResidueUpper == 2 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
				} else {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = tChar;
				}
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
			}
		}

		int CheckG = PairwiseCheck( pSegArr, RowCount, tCount, &PWScrG );

		int CheckO = PairwiseCheckOther( pSegArr, RowCount, pOSegArr, pSegCount, tCount, &PWScrO );

		if ( CheckG && CheckO ) {
			for ( i = 0; i < RowCount; ++i ) {
				// Lets Clear out old shades while here.
				DisplayVars->GetTitleColors( 
					&((pSegArr[i].pGeneStor)[tCount].TextColor), 
					&((pSegArr[i].pGeneStor)[tCount].BackColor)
				);
			}
		}
	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE && tCGSeg->m_DisplayGroup != GrpNum ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			GlobalUnlock( tSegHandle );
		}
	}
	delete pOSegArr;

}

int 
CGenedocDoc::PairwiseCheckOther( 
	ShadeSegStc *pSegArr, 
	int RowCount, 
	ShadeSegStc *pOSegArr, 
	int pSegCount, 
	DWORD tCount, 
	int *PWScr ) 
{
	int CheckReturn = 1;
	int tPWScr = 0;

	if ( pSegCount <= 1 ) {
		*PWScr = 0;
		return 1;
	}

	for ( int i = 0; i < RowCount; ++i ) {
		for ( int j = 0; j < pSegCount; ++j ) {
			char tChari = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChari = toupper(tChari);
			char tCharj = (pOSegArr[j].pGeneStor)[tCount].CharGene;
			tCharj = toupper(tCharj);
			int Score = 0;
			if ( tChari >= 'A' && tChari <='Z' ) {
				if ( tCharj >= 'A' && tCharj <='Z' ) {
					Score = ScoreCurrentArray( tChari, tCharj );
				} else {
					Score = GapLen;
				}
			} else if ( tCharj >= 'A' && tCharj <='Z' ) {
				Score = GapLen;
			}
			// ask less than or less than or equal
			if ( Score <= CurrentZeroDistance ) {
				CheckReturn = 0;
			}
			tPWScr += Score;
		}
	}

	*PWScr = tPWScr;

	return CheckReturn;
}

int 
CGenedocDoc::PairwiseCheck( ShadeSegStc *pSegArr, int pSegCount, DWORD tCount, int *PWScr )
{

	int CheckReturn = 1;
	int tPWScr = 0;

	if ( pSegCount <= 1 ) {
		*PWScr = 0;
		return 1;
	}

	int GapCheck = 0;

	for ( int i = 0; i < pSegCount - 1; ++i ) {
		for ( int j = i + 1; j < pSegCount; ++j ) {
			char tChari = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChari = toupper(tChari);
			char tCharj = (pSegArr[j].pGeneStor)[tCount].CharGene;
			tCharj = toupper(tCharj);
			int Score = 0;
			if ( tChari >= 'A' && tChari <='Z' ) {
				if ( tCharj >= 'A' && tCharj <='Z' ) {
					Score = ScoreCurrentArray( tChari, tCharj );
				} else {
					Score = GapLen;
					GapCheck = 1;
				}
			} else if ( tCharj >= 'A' && tCharj <='Z' ) {
				Score = GapLen;
				GapCheck = 1;
			}
			// Stays zero if both are non score chars.
			if ( Score == 0 ) {
				GapCheck = 1;
			}
			if ( Score >= CurrentZeroDistance ) {
				CheckReturn = 0;
			}
			tPWScr += Score;
		}
	}
	
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONTNG && GapCheck == 1 ) {
		CheckReturn = 0;
	}

	*PWScr = tPWScr;

	return CheckReturn;
}
