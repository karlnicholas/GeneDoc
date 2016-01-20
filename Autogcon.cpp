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
CGenedocDoc::AutoShadeGroupConserve(
	ShadeSegStc* pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc* pConsensusRow 
) 
{

	int MatchArr[2][26];
	ShadePairStruct tSPS;
	char tChar;
	int i;

	COLORREF TextColor, BackColor;
	GetLevelColors( &m_UserVars.m_Vars, 0, &TextColor, &BackColor );
	
	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {

		if ( (pSegArr[0].pGeneStor)[tCount].BackColor != BackColor ) continue;


		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for ( i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		int GotSomething = 0;

		for ( i = 0; i < RowCount; ++i ) {

			tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;

			// if ( (tChar == '-') || (tChar == '.') ) {
			tChar = toupper(tChar);
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				continue;
			}
			GotSomething = 1;
			tChar -= 'A';
			MatchArr[0][tChar]++;
		}

		// Clear out old comments on bottom comment row
		if ( !GotSomething ) continue;

		int MaxMatchCount = (int)((double)RowCount * (m_UserVars.m_GroupConsLevel / 100.0) + 0.5);
		

		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( &tSPS, pSegArr, RowCount, &MaxMatchCount, tCount, 1 );
		} else {
			SortMatchArr ( DisplayVars, MatchArr, &tSPS, &MaxMatchCount, 1 );
		}

		

		if ( !(MaxMatchCount >= (int)((double)RowCount * (m_UserVars.m_GroupConsLevel / 100.0) + 0.5) ) ) {
			// Nothing here
			continue;
		}


		// And its length
		int tLen = strlen ( tSPS.Group );

		// Mark GeneStors
		for ( i = 0; i < RowCount; ++i ) {

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
	
			// Test for any char in group.
			for ( int j=0; j < tLen; ++j ) {
				char tCharG = tSPS.Group[j];
				tCharG = toupper(tCharG);
	
				if ( tChar == tCharG ) {
					// (pSegArr[i].pGeneStor)[tCount].CharShade = tShade;
					DisplayVars->GetTitleColors(
						&(pSegArr[i].pGeneStor)[tCount].TextColor,
						&(pSegArr[i].pGeneStor)[tCount].BackColor
					);
						// No need to test further
					break;
				}
			}
		}
	}
}



void 
CGenedocDoc::AutoGroupConsCross(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{

	int i;

	typedef struct {
		int GroupNum;
		int GroupCount;
		int Offset;
	} stcSG;

	typedef struct {
		COLORREF TextColor;
		COLORREF BackColor;
	} stcCA;

	int NumOGroups = m_UserVars.m_DisplayVars.GetCount() - 1;
	if ( !NumOGroups ) return;

	stcSG *SortGroup = new stcSG[NumOGroups];
	stcCA ColorArr[26];

	int tRC = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here

	ShadeSegStc *pOSegArr = new ShadeSegStc[tRC];	// Gonna need access to comment row here

	if ( pOSegArr == 0 ) {
		AfxMessageBox("AutoShadeQuantify:New Fail 1");
		return;
	}

	int GrpNum = 0;
	int GrpCnt = 0;
	int GrpAdd = 0;
	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars* pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		GrpCnt++;
		if ( pDV->GetGroupName() == DisplayVars->GetGroupName() ) {
			GrpNum = GrpCnt;
		} else {
			SortGroup[GrpAdd].GroupNum = GrpCnt;
			SortGroup[GrpAdd].GroupCount = pDV->GetGroupList()->GetCount();
			SortGroup[GrpAdd].Offset = 0;
			GrpAdd++;
		}
	}

	// Sort SortGroup Array
	for ( i=0; i < NumOGroups; ++i ) {
		for ( int j=i+1; j < NumOGroups; ++j ) {
			if ( SortGroup[i].GroupCount > SortGroup[j].GroupCount ) {
				stcSG tSG = SortGroup[i];
				SortGroup[i] = SortGroup[j];
				SortGroup[j] = tSG;
			}
		}
	}

	for ( i=1; i < NumOGroups; ++i) {
		SortGroup[i].Offset = SortGroup[i-1].GroupCount + SortGroup[i-1].Offset;
	}

	int pSegCount = 0;
	int pSegLoc;
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE && tCGSeg->m_DisplayGroup != GrpNum && tCGSeg->m_DisplayGroup != 0 ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			for ( i=0; i < NumOGroups; ++i ) {
				if ( SortGroup[i].GroupNum == tCGSeg->m_DisplayGroup ) break;
			}
			SortGroup[i].GroupCount -= 1;
			pSegLoc = SortGroup[i].Offset + (SortGroup[i].GroupCount);
			pOSegArr[pSegLoc].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			pOSegArr[pSegLoc].pCGSeg = tCGSeg;
			if ( pOSegArr[pSegLoc].pGeneStor == NULL) {
				AfxMessageBox("AutoShade:GlobalLock:Fail:1");
				delete pOSegArr;
				return;
			}
			pSegCount++;
		}
	}



	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	
	// init locations

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
	
		for ( i = 0; i < RowCount; ++i ) {
			if ( (pSegArr[i].pGeneStor)[tCount].BackColor != m_UserVars.m_BackColor0 ) break;
		}

		if ( i != RowCount ) continue;

		for ( i = 0; i < 26; ++i ) {
			ColorArr[i].BackColor = m_UserVars.m_BackColor0;
			ColorArr[i].TextColor = m_UserVars.m_ForeColor0;
		}

		for ( i = 0; i < pSegCount; ++ i ) {
			char tChar = (pOSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				ColorArr[tChar - 'A'].BackColor = (pOSegArr[i].pGeneStor)[tCount].BackColor;
				ColorArr[tChar - 'A'].TextColor = (pOSegArr[i].pGeneStor)[tCount].TextColor;
			}
		}
			

		for ( i = 0; i < RowCount; ++i ) {
			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				(pSegArr[i].pGeneStor)[tCount].TextColor = ColorArr[tChar - 'A'].TextColor;
				(pSegArr[i].pGeneStor)[tCount].BackColor = ColorArr[tChar - 'A'].BackColor;
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
	delete SortGroup;
	delete pOSegArr;

}
