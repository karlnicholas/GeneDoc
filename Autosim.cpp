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
CGenedocDoc::AutoShadeIdentity(
	ShadeSegStc *opSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
)
{

	int MatchArr[2][26];
	ShadePairStruct SelConsSPS;
	ShadePairStruct OtherSPS;
	int Count;
//	int SaveGroup;

	ShadeSegStc **pSegArr = new ShadeSegStc*[2];	// Gonna need access to comment row here
	for ( int i = 0; i < 2; ++i ) {
		pSegArr[i] = new ShadeSegStc[RowCount];
		memset ( pSegArr[i], 0, sizeof( ShadeSegStc) * RowCount );
	}
	int *pGrpCont = new int[2];

	memset ( pGrpCont, 0, sizeof(int) * 2 );

	int SelCount = 0;
	CPtrList *pList = DisplayVars->GetIdentList();
	for (int i=0; i < RowCount; ++i ) {
		int f = 0;
		POSITION fPos = pList->GetHeadPosition();
		while ( fPos != NULL ) {
			CGeneSegment *pCGSeg = (CGeneSegment *)pList->GetNext(fPos);
			if ( pCGSeg == opSegArr[i].pCGSeg ) {
				f = 1;
				break;
			}
		}
		if ( f ) {
			pSegArr[0][pGrpCont[0]].pGeneStor = opSegArr[i].pGeneStor;
			pSegArr[0][pGrpCont[0]++].pCGSeg = opSegArr[i].pCGSeg;
		} else {
			pSegArr[1][pGrpCont[1]].pGeneStor = opSegArr[i].pGeneStor;
			pSegArr[1][pGrpCont[1]++].pCGSeg = opSegArr[i].pCGSeg;
		}
		SelCount++;
	}

	double tCalc = (double)pGrpCont[1]; // here
	int RowCount100 = (int)(tCalc * (DisplayVars->GetPrimaryLevel() / 100.0) + 0.5);
	int RowCount80 =  (int)(tCalc * (DisplayVars->GetSecondaryLevel() / 100.0) + 0.5);
	int RowCount60 =  (int)(tCalc * (DisplayVars->GetTertiaryLevel() / 100.0) + 0.5);


	int j;

	DWORD OuterCount = opSegArr[0].pCGSeg->GetTextLength();

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for (int i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		int GotSomething = 0;

		for (int i = 0; i < pGrpCont[0]; ++i ) {

			GetLevelColors( DisplayVars, 0, 
				&(pSegArr[0][i].pGeneStor)[tCount].TextColor, 
				&(pSegArr[0][i].pGeneStor)[tCount].BackColor
			);
			char tChar = (pSegArr[0][i].pGeneStor)[tCount].CharGene;
			// Reset Display Char while here.
			if ( DisplayVars->GetResidueMode() == 0 ) {
				if ( m_UserVars.m_ResidueUpper == 1 ) {
					(pSegArr[0][i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
				} else if ( m_UserVars.m_ResidueUpper == 2 ) {
					(pSegArr[0][i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
				} else {
					(pSegArr[0][i].pGeneStor)[tCount].CharDisplay = tChar;
				}
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[0][i].pGeneStor)[tCount].CharDisplay = ' ';
			}


			tChar = toupper(tChar);
			//
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				// Special Case, always set real gaps to '-' for difference mode.
			}
			GotSomething = 1;
			tChar -= 'A';
			MatchArr[0][tChar]++;
		}

		// Clear out old comments on consensus row
		// 
		if ( pConsensusRow != NULL ) {
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
		if ( GotSomething ) {
			// Sort the Array
			Count = 0;
			// call subroutine to use Groupings and ScoreTable
			if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
				GetDNAAmbiguous( &SelConsSPS, pSegArr[0], pGrpCont[0], &Count, tCount, 1 );
			} else {
				SortMatchArr ( DisplayVars, MatchArr, &SelConsSPS, &Count, 1 );
			}

			if ( Count != pGrpCont[0] ) GotSomething = 0;
		}

		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for (int i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		for (int i = 0; i < pGrpCont[1]; ++i ) {

			GetLevelColors( DisplayVars, 0, 
				&(pSegArr[1][i].pGeneStor)[tCount].TextColor, 
				&(pSegArr[1][i].pGeneStor)[tCount].BackColor
			);
			char tChar = (pSegArr[1][i].pGeneStor)[tCount].CharGene;
			// Reset Display Char while here.
			if ( DisplayVars->GetResidueMode() == 0 ) {
				if ( m_UserVars.m_ResidueUpper == 1 ) {
					(pSegArr[1][i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
				} else if ( m_UserVars.m_ResidueUpper == 2 ) {
					(pSegArr[1][i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
				} else {
					(pSegArr[1][i].pGeneStor)[tCount].CharDisplay = tChar;
				}
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[1][i].pGeneStor)[tCount].CharDisplay = ' ';
			}


			tChar = toupper(tChar);

			//
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				continue;
			}
			tChar -= 'A';
			MatchArr[0][tChar]++;
		}


		if( !GotSomething ) continue;

		// Sort the Array
		Count = 0;
		// call subroutine to use Groupings and ScoreTable
		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( &OtherSPS, pSegArr[1], pGrpCont[1], &Count, tCount, 1 );
		} else {
			SortMatchArr ( DisplayVars, MatchArr, &OtherSPS, &Count, 1 );
		}

		// Got Something to do now.
		// Mark Conserved Idents
		for (int i = 0; i < pGrpCont[0]; ++i ) {
			char tChar = (pSegArr[0][i].pGeneStor)[tCount].CharGene;
			tChar = toupper( tChar );
			char *pc = SelConsSPS.Group;
			while ( *pc != 0 ) {
				if ( tChar == *pc ) {
					DisplayVars->GetIdentColors( 
						&(pSegArr[0][i].pGeneStor)[tCount].TextColor, 
						&(pSegArr[0][i].pGeneStor)[tCount].BackColor
					);
					break;
				}
				pc++;
			}
		}

		// Set the Consensus Line.
		if ( pConsensusRow != NULL) {

			char tComment = OtherSPS.RowNum;
			if ( tComment != SelConsSPS.RowNum ) {

				if ( tComment == 'T' || tComment == 'U' ) { 
					if ( m_UserVars.m_ProjectType == 3 ) {
						tComment = 'T';
					} else if ( m_UserVars.m_ProjectType == 4 ) {
						tComment = 'U';
					}
				}

				// Use Top Consensus Row
				(pConsensusRow->pGeneStor)[tCount].CharDisplay = tComment;
			}
		}


		if ( DisplayVars->GetGroupEnabled() && SelConsSPS.Group[1] == 0 ) {

			int GroupCount = m_UserVars.m_ShadePairArray.GetSize();
			ShadePairStruct* tpSPS;
			int MatchFound = 0;

			// First do the Groups of numbers .. kill out DupArr
			for (int i = 0; i < GroupCount; ++i ) {
				tpSPS = (ShadePairStruct*)m_UserVars.m_ShadePairArray[i];

				int tLen = strlen ( tpSPS->Group );
				// Sum up counts for this group
				for ( j=0; j < tLen; ++j ) {
					char tChar = tpSPS->Group[j];
					tChar = toupper(tChar);
					if ( SelConsSPS.Group[0] == tChar) {
						MatchFound = 1;
						break;
					}
				}
				if ( MatchFound ) {
					break;
				}
			}
			if ( MatchFound ) {
				strcpy ( SelConsSPS.Group, tpSPS->Group );
//				SaveGroup = i + 1;
			} else {
//				SaveGroup = 0;
			}
		}

	
		// Got Something to do now.
		int tShade = 3;
		int oGroup = 0;

		if ( DisplayVars->GetIdentDisplayStyle() ) {

			Count = 0;		
			char SavChar = 0;
			// Mark GeneStors
			for (int i = 0; i < pGrpCont[1]; ++i ) {
				char tChar = (pSegArr[1][i].pGeneStor)[tCount].CharGene;
				tChar = toupper( tChar );
				if ( SavChar == 0 ) SavChar = tChar;
				char *pc = SelConsSPS.Group;
				while ( *pc != 0 ) {
					if ( tChar == *pc ) {
						Count++;
						if ( SavChar != tChar ) oGroup = 1;
						break;
					}
					pc++;
				}
			}
			
			// Check for any shading
			if ( ShadeLevel == SHADELEVEL4 ) {
				if ( !(Count >= RowCount60) ) {
					// Nothing here
					continue;
				}
			} else if ( ShadeLevel == SHADELEVEL3 ) {
				if ( !(Count >= RowCount80) ) {
					// Nothing here
					continue;
				}
			} else if ( ShadeLevel == SHADELEVEL2 ) {
				if ( !(Count >= RowCount100) ) {
					// Nothing here
					continue;
				}
			}
			// Find the Shade to set.
			tShade = 0;

			if ( Count >= RowCount60 ) {
				tShade = 1;
			}
			if ( Count >= RowCount80 ) {
				tShade = 2;
			}
			if ( Count >= RowCount100 ) {
				tShade = 3;
			}
			// And its length

			// Figure out Substitution group options ...
			if ( DisplayVars->GetConsSubStyle() == 1 ) {
				if ( oGroup ) {
					if ( tShade > 0 ) tShade--;
				}
			} else if ( DisplayVars->GetConsSubStyle() == 2 ) {
				if ( oGroup ) {
					if ( tShade != 1 ) tShade = 1;
					else tShade = 0;
				} else if ( tShade == 1 ) tShade = 0;
			}
			
		}


		for (int i = 0; i < pGrpCont[1]; ++i ) {
			char tChar = (pSegArr[1][i].pGeneStor)[tCount].CharGene;
			tChar = toupper( tChar );
			char *pc = SelConsSPS.Group;
			while ( *pc != 0 ) {
				if ( tChar == *pc ) {
					GetLevelColors( DisplayVars, tShade, 
						&(pSegArr[1][i].pGeneStor)[tCount].TextColor, 
						&(pSegArr[1][i].pGeneStor)[tCount].BackColor
					);
					break;
				}
				pc++;
			}
		}

	}

	for (int i = 0; i < 2; ++i ) {
		delete pSegArr[i];
	}
	delete pSegArr;
	delete pGrpCont;

}

