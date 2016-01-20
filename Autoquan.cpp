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
CGenedocDoc::AutoShadeQuantify(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
)
{
	int MatchArr[2][26];
	ShadePairStruct tSPS[3];
	int i;

	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for ( i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}
		
		int GotSomething = 0;
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
			//
			tChar = toupper(tChar);
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				continue;			
			}
			GotSomething = 1;
			tChar -= 'A';
			MatchArr[0][tChar]++;
		}
		// Clear out old comments on bottom comment row

		if ( pConsensusRow != NULL ) {
			// Use Top Consensus Row
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = ' ';

			GetLevelColors( DisplayVars, 0, 
				&(pConsensusRow->pGeneStor)[tCount].TextColor, 
				&(pConsensusRow->pGeneStor)[tCount].BackColor
			);
			(pConsensusRow->pGeneStor)[tCount].CharScore = 0;

		}

		// Test for something to do
		if ( !GotSomething ) continue;
		
		// Call SortMatchArr
		tSPS[0].RowNum = 0;
		tSPS[1].RowNum = 0;
		tSPS[2].RowNum = 0;
		int Count = 0;
		// To Sort array using Shade Groups and Score table
		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( tSPS, pSegArr, RowCount, &Count, tCount, 3 );
		} else {
			SortMatchArr ( DisplayVars, MatchArr, tSPS, &Count, 3 );
		}

		// Mark GeneStors
		for ( i = 0; i < RowCount; ++i ) {
			if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
			int match = 0;
			if ( ShadeLevel >= SHADELEVEL2) { 
				if ( tSPS[0].RowNum == 0 ) break;
				char *pc = tSPS[0].Group;
				while ( *pc != 0 ) {
					if ( tChar == *pc ) {
						// (pSegArr[i].pGeneStor)[tCount].CharShade = 3;
						GetLevelColors( DisplayVars, 3, 
							&(pSegArr[i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[i].pGeneStor)[tCount].BackColor
						);
						match = 1;
						break;
					}
					pc++;
				}
			}
			if ( (ShadeLevel >= SHADELEVEL3) && (!match) ) {
				if ( tSPS[1].RowNum == 0 ) break;
				char *pc = tSPS[1].Group;
				while ( *pc != 0 ) {
					if ( tChar == *pc ) {
						// (pSegArr[i].pGeneStor)[tCount].CharShade = 2;
						GetLevelColors( DisplayVars, 2, 
							&(pSegArr[i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[i].pGeneStor)[tCount].BackColor
						);
						match = 1;
						break;
					}
					pc++;
				}
			} 
			if ( (ShadeLevel >= SHADELEVEL4) && (!match) ) {
				if ( tSPS[2].RowNum == 0 ) break;
				char *pc = tSPS[2].Group;
				while ( *pc != 0 ) {
					if ( tChar == *pc ) {
						// (pSegArr[i].pGeneStor)[tCount].CharShade = 1;
						GetLevelColors( DisplayVars, 1, 
							&(pSegArr[i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[i].pGeneStor)[tCount].BackColor
						);
						match = 1;
						break;
					}
					pc++;
				}
			} 

			if ( !match || ShadeLevel == SHADELEVEL0 ) {
				// (pSegArr[i].pGeneStor)[tCount].CharShade = 0;
				GetLevelColors( DisplayVars, 0, 
					&(pSegArr[i].pGeneStor)[tCount].TextColor, 
					&(pSegArr[i].pGeneStor)[tCount].BackColor
				);
			}
		}
			
		// Set the Comment Line.
		if ( Count != 0 ) {
			char tComment = tSPS[0].RowNum;
			if ( tComment == 'T' || tComment == 'U' ) { 
				if ( m_UserVars.m_ProjectType == 3 ) {
					tComment = 'T';
				} else if ( m_UserVars.m_ProjectType == 4 ) {
					tComment = 'U';
				}
			}
			if ( pConsensusRow != NULL ) {
				(pConsensusRow->pGeneStor)[tCount].CharDisplay = tComment;
			}
		}
	}
}

