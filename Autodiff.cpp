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
CGenedocDoc::AutoShadeDifference(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
)
{
	int RowCount100;
	int RowCount80;
	int RowCount60;

	int MatchArr[2][26];
	ShadePairStruct tSPS;
	int Count;
	int SaveGroup;

	
	float tCalc = (float)RowCount;
	RowCount100 = (int)(tCalc * (DisplayVars->GetPrimaryLevel() / 100.0) + .5);
	RowCount80 =  (int)(tCalc * (DisplayVars->GetSecondaryLevel() / 100.0) + .5);
	RowCount60 =  (int)(tCalc * (DisplayVars->GetTertiaryLevel() / 100.0) + .5);

	
	int i, j;
	char SaveFirst;

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

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			// Reset Display Char while here.
			if ( m_UserVars.m_ResidueUpper == 1 ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
			} else if ( m_UserVars.m_ResidueUpper == 2 ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
			} else {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = tChar;
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
			}


			tChar = toupper(tChar);

			if ( i == 0 ) {
				SaveFirst = tChar;
			}

			//
			// if ( (tChar == '-') || ( tChar == '.') ) {
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				// Special Case, always set real gaps to '-' for difference mode.
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = '-';
				continue;
			}
			GotSomething = 1;
			tChar -= 'A';
			MatchArr[0][tChar]++;
		}

		// Clear out old comments on consensus row
		// 
		if ( pConsensusRow != NULL && DisplayVars->GetDiffMode() == 1) {
			// Use Top Consensus Row
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = ' ';
			// (pSegArr[1].pGeneStor)[tCount].CharShade = 0;
			GetLevelColors( DisplayVars, 0, 
				&(pConsensusRow->pGeneStor)[tCount].TextColor, 
				&(pConsensusRow->pGeneStor)[tCount].BackColor
			);
			(pConsensusRow->pGeneStor)[tCount].CharScore = 0;

		}

		// Test for work to do
		if ( !GotSomething ) continue;

		// Sort the Array
		Count = 0;
		// call subroutine to use Groupings and ScoreTable
		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( &tSPS, pSegArr, RowCount, &Count, tCount, 1 );
		} else {
			SortMatchArr ( DisplayVars, MatchArr, &tSPS, &Count, 1 );
		}

		if ( DisplayVars->GetDiffMode() == 1 ) {

			// Set consensus line shade to 0
			Count = 1;
			ShadeLevel = SHADELEVEL0;
			
			// if ( SaveFirst != '-' && SaveFirst != '.' ) {
			if ( SaveFirst >= 'A' && SaveFirst <= 'Z' ) {

				if ( DisplayVars->GetGroupEnabled() ) {
	
					int GroupCount = m_UserVars.m_ShadePairArray.GetSize();
					ShadePairStruct* tpSPS;
					int MatchFound = 0;
	
					// First do the Groups of numbers .. kill out DupArr
					for ( i = 0; i < GroupCount; ++i ) {
						tpSPS = (ShadePairStruct*)m_UserVars.m_ShadePairArray[i];
	
						int tLen = strlen ( tpSPS->Group );
						// Sum up counts for this group
						for ( j=0; j < tLen; ++j ) {
							char tChar = tpSPS->Group[j];
							tChar = toupper(tChar);
							if ( SaveFirst == tChar) {
								MatchFound = 1;
								break;
							}
						}
						if ( MatchFound ) {
							break;
						}
					}
					if ( MatchFound ) {
						strcpy ( tSPS.Group, tpSPS->Group );
						SaveGroup = i + 1;
					} else {
						tSPS.Group[0] = SaveFirst;
						tSPS.Group[1] = 0;
						SaveGroup = 0;
					}
				} else {
					tSPS.Group[0] = SaveFirst;
					tSPS.Group[1] = 0;
				}
			} else {
				// Do Nothing if first one is a gap
				tSPS.Group[0] = 0;
				Count = 0;
			}
		}

		// Got Something to do now.
		
		// Mark GeneStors
		for ( i = 0; i < RowCount; ++i ) {
			if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
			if ( i == 0 && DisplayVars->GetDiffMode() == 1) {
				if ( m_UserVars.m_ResidueUpper == 1 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
				} else if ( m_UserVars.m_ResidueUpper == 2 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
				} else {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = (pSegArr[i].pGeneStor)[tCount].CharGene;
				}
				if ( m_UserVars.m_TransTilde ) {
					if ( tChar == '~' ) (pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
				}

				if ( (SaveGroup + '0') == tSPS.RowNum )  {
					tSPS.RowNum = ' ';
				}
				if ( tSPS.RowNum == tChar ) {
					tSPS.RowNum = ' ';
				}
			} else {

				char *pc = tSPS.Group;
				while ( *pc != 0 ) {
					if ( tChar == *pc ) {
						(pSegArr[i].pGeneStor)[tCount].CharDisplay = '.';
						break;
					}
					pc++;
				}
			}
		}
		
		
		int tShade = 0;

		if ( Count >= RowCount60 && ShadeLevel >= 4 ) {
			tShade = 1;
		}
		if ( Count >= RowCount80 && ShadeLevel >= 3 ) {
			tShade = 2;
		}
		if ( Count >= RowCount100 && ShadeLevel >= 2 ) {
			tShade = 3;
		}
			
		// Set the Consensus Line.
		if ( Count != 0  && DisplayVars->GetDiffMode() == 1 && pConsensusRow != NULL) {

			char tComment = tSPS.RowNum;

			if ( tComment == 'T' || tComment == 'U' ) { 
				if ( m_UserVars.m_ProjectType == 3 ) {
					tComment = 'T';
				} else if ( m_UserVars.m_ProjectType == 4 ) {
					tComment = 'U';
				}
			}

			// Use Top Consensus Row
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = tComment;
			// (pSegArr[1].pGeneStor)[tCount].CharShade = 0;
//			GetLevelColors( DisplayVars, 0, 
//				&(pConsensusRow->pGeneStor)[tCount].TextColor, 
//				&(pConsensusRow->pGeneStor)[tCount].BackColor
//			);
//			(pConsensusRow->pGeneStor)[tCount].CharScore = 0;

		}
	}
}

