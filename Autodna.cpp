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

#define TLOC 1
#define GLOC 2
#define CLOC 4
#define ALOC 8


void 
CGenedocDoc::AutoShadeDNASet() 
{
TRY {

	int i;
	
	int tRC = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here

	int GrpCnt = m_UserVars.m_DisplayVars.GetCount() + 1;

	ShadeSegStc **pSegArr = new ShadeSegStc*[GrpCnt];	// Gonna need access to comment row here
	for ( i = 0; i < GrpCnt; ++i ) {
		pSegArr[i] = new ShadeSegStc[tRC];
		memset ( pSegArr[i], 0, sizeof( ShadeSegStc) * tRC );
	}
	int *pGrpCont = new int[GrpCnt];

	CDisplayVars** pDVars = new CDisplayVars*[GrpCnt];

	pDVars[0] = &m_UserVars.m_Vars;
	GrpCnt = 1;
	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars* pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		pDVars[GrpCnt] = pDV;
		GrpCnt++;
	}

	memset ( pGrpCont, 0, sizeof(int) * GrpCnt );

	DWORD OuterCount;

	int ConsensusCount = -1;
	ShadeSegStc *pConsensusRow = NULL;

	if ( m_UserVars.m_ConsensusLine == 0 ) {
		// Use Top Consensus Row
		ConsensusCount = 1;
	} else if ( m_UserVars.m_ConsensusLine == 1 ) {
		// Use Bottom Consensus Row
		ConsensusCount = tRC - 1;
	}
	i = 0;
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		OuterCount = tCGSeg->GetTextLength();
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			pSegArr[tCGSeg->m_DisplayGroup][pGrpCont[tCGSeg->m_DisplayGroup]].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			pSegArr[tCGSeg->m_DisplayGroup][pGrpCont[tCGSeg->m_DisplayGroup]++].pCGSeg = tCGSeg;
		}
		// comments on bottom comment row?
		if ( i == ConsensusCount ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			pConsensusRow = new ShadeSegStc;
			pConsensusRow->pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			pConsensusRow->pCGSeg = tCGSeg;
		}
		i++;

	}

	// init locations
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
	
		memset ( pGrpCont, 0, sizeof(int) * GrpCnt );
		int Inval = 0;

		for ( int gCnt = 0; gCnt < GrpCnt; ++gCnt ) {

			for ( i = 0; i < tRC; ++i ) {
				
				if ( pSegArr[gCnt][i].pCGSeg == NULL ) break;

				// Lets Clear out old shades while here.
				GetLevelColors( &m_UserVars.m_Vars, 0, 
					&(pSegArr[gCnt][i].pGeneStor)[tCount].TextColor, 
					&(pSegArr[gCnt][i].pGeneStor)[tCount].BackColor
				);

				char tChar = (pSegArr[gCnt][i].pGeneStor)[tCount].CharGene;
				// Reset Display Char while here.
				if ( m_UserVars.m_Vars.GetResidueMode() == 0 ) {
					if ( m_UserVars.m_ResidueUpper == 1 ) {
						(pSegArr[gCnt][i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
					} else if ( m_UserVars.m_ResidueUpper == 2 ) {
						(pSegArr[gCnt][i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
					} else {
						(pSegArr[gCnt][i].pGeneStor)[tCount].CharDisplay = tChar;
					}
				}
				if ( m_UserVars.m_TransTilde ) {
					if ( tChar == '~' ) (pSegArr[gCnt][i].pGeneStor)[tCount].CharDisplay = ' ';
				}

				tChar = (pSegArr[gCnt][i].pGeneStor)[tCount].CharGene;

				tChar = toupper(tChar);
				if ( !(tChar >= 'A' && tChar <= 'Z') ) {
					pGrpCont[gCnt] = -1;
//					Inval = 1;
					continue;
				}
				switch( tChar ) {
				case 'A':
					pGrpCont[gCnt] |= ALOC;
					break;
				case 'G':
					pGrpCont[gCnt] |= GLOC;
					break;
				case 'C':
					pGrpCont[gCnt] |= CLOC;
					break;
				case 'T':
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'U':
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'Y':
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'R':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= GLOC;
					break;
				case 'W':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'S':
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= GLOC;
					break;
				case 'K':
					pGrpCont[gCnt] |= TLOC;
					pGrpCont[gCnt] |= GLOC;
					break;
				case 'M':
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= ALOC;
					break;
				case 'B':
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= GLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'D':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= GLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'H':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'V':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= GLOC;
					break;
				case 'N':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= GLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				case 'X':
					pGrpCont[gCnt] |= ALOC;
					pGrpCont[gCnt] |= CLOC;
					pGrpCont[gCnt] |= GLOC;
					pGrpCont[gCnt] |= TLOC;
					break;
				}
			}
		}

		if ( Inval ) continue;
		// Do Test .. only groups here ..
		for (int gCnt = 1; gCnt < GrpCnt; ++gCnt ) {

			if ( pGrpCont[gCnt] == -1 ) continue;

			int GroupUnion = pGrpCont[gCnt];
			int ti;
			for ( ti=0; ti < GrpCnt; ++ti ) {
				if ( ti == gCnt ) continue;
				if ( pGrpCont[ti] == 0 ) continue;
				if ( (GroupUnion & pGrpCont[ti]) == 0 ) break;
			}

			if ( ti < GrpCnt ) {
				// Then we shade the business ..
				for ( i = 0; i < tRC; ++i ) {
					if ( pSegArr[gCnt][i].pCGSeg == NULL ) break;

					char tChar = (pSegArr[gCnt][i].pGeneStor)[tCount].CharGene;
					tChar = toupper(tChar);
					if ( tChar >= 'A' && tChar <= 'Z' ) {

						pDVars[gCnt]->GetTitleColors( 
							&(pSegArr[gCnt][i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[gCnt][i].pGeneStor)[tCount].BackColor
						);
					}
				}
			}
		}


		int GroupUnion = pGrpCont[0];
		for ( i=0; i < GrpCnt; ++i ) {
			GroupUnion &= pGrpCont[i];
		}

		char cCons;
		char larr[] = " TGKCYSBAWRDMHVN";
		cCons = larr[GroupUnion];

		if ( pConsensusRow != NULL ) {
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = cCons;
		}
	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			HANDLE tSegHandle = tCGSeg->GetTextHandle();
			GlobalUnlock( tSegHandle );
		}
	}

	for ( i = 0; i < GrpCnt; ++i ) {
		delete pSegArr[i];
	}
	delete pSegArr;
	delete pGrpCont;
	delete pDVars;
	if ( pConsensusRow != NULL ) delete pConsensusRow;

}
CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH

}

