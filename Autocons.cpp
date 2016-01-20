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
CGenedocDoc::AutoShadeConserve(
	ShadeSegStc* pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc* pConsensusRow 
) 
{

	int RowCount100;
	int RowCount80;
	int RowCount60;
	int MatchArr[2][26];
	ShadePairStruct tSPS;
	char tChar;
	int i;

	
	double tCalc = (double)RowCount; // here
	RowCount100 = (int)(tCalc * (DisplayVars->GetPrimaryLevel() / 100.0) + 0.5);
	RowCount80 =  (int)(tCalc * (DisplayVars->GetSecondaryLevel() / 100.0) + 0.5);
	RowCount60 =  (int)(tCalc * (DisplayVars->GetTertiaryLevel() / 100.0) + 0.5);

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
			// (pSegArr[i].pGeneStor)[tCount].CharShade = 0;
			GetLevelColors( DisplayVars, 0, 
				&(pSegArr[i].pGeneStor)[tCount].TextColor, 
				&(pSegArr[i].pGeneStor)[tCount].BackColor
			);

			tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			// Reset Display Char here
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
		// 
		if ( pConsensusRow != NULL ) {
			// Use Top Consensus Row
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = m_UserVars.m_ConservedGap;
			// (pSegArr[1].pGeneStor)[tCount].CharShade = 0;
			GetLevelColors( DisplayVars , 0, 
				&(pConsensusRow->pGeneStor)[tCount].TextColor, 
				&(pConsensusRow->pGeneStor)[tCount].BackColor
			);
			(pConsensusRow->pGeneStor)[tCount].CharScore = 0;

		}

		if ( !GotSomething ) continue;

		int MaxMatchCount = RowCount60;
		
		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( &tSPS, pSegArr, RowCount, &MaxMatchCount, tCount, 1 );
		} else {
			SortMatchArr ( DisplayVars, MatchArr, &tSPS, &MaxMatchCount, 1 );
		}
		

		// Check for any shading
		if ( ShadeLevel == SHADELEVEL4 ) {
			if ( !(MaxMatchCount >= RowCount60) ) {
				// Nothing here
				continue;
			}
		} else if ( ShadeLevel == SHADELEVEL3 ) {
			if ( !(MaxMatchCount >= RowCount80) ) {
				// Nothing here
				continue;
			}
		} else if ( ShadeLevel == SHADELEVEL2 ) {
			if ( !(MaxMatchCount >= RowCount100) ) {
				// Nothing here
				continue;
			}
		}


		// Got Something to do now.
		// Find the Shade to set.
		int tShade = 0;

		if ( MaxMatchCount >= RowCount60 ) {
			tShade = 1;
		}
		if ( MaxMatchCount >= RowCount80 ) {
			tShade = 2;
		}
		if ( MaxMatchCount >= RowCount100 ) {
			tShade = 3;
		}

		int sShade = tShade;

		// And its length
		int tLen = strlen ( tSPS.Group );

		// Figure out Substitution group options ...
		if ( DisplayVars->GetConsSubStyle() == 1 ) {
			if ( tLen > 1 ) {
				if ( tShade > 0 ) tShade--;
			}
		} else if ( DisplayVars->GetConsSubStyle() == 2 ) {
			if ( tLen > 1 ) {
				if ( tShade != 1 ) tShade = 1;
				else tShade = 0;
			} else if ( tShade == 1 ) tShade = 0;
		}
		
		int ShadeModeSave = DisplayVars->GetModeConserved();
		DisplayVars->SetModeConserved( SHADECONSERVED );

		// Mark GeneStors
		for ( i = 0; i < RowCount; ++i ) {
			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);

			// Test for any char in group.
			for ( int j=0; j < tLen; ++j ) {
				char tCharG = tSPS.Group[j];
				tCharG = toupper(tCharG);

				if ( tChar == tCharG && ShadeLevel != SHADELEVEL0 ) {
					// (pSegArr[i].pGeneStor)[tCount].CharShade = tShade;
					GetLevelColors( DisplayVars, tShade, 
						&(pSegArr[i].pGeneStor)[tCount].TextColor,
						&(pSegArr[i].pGeneStor)[tCount].BackColor
					);
					// No need to test further
					break;
				}
			}
		}

		DisplayVars->SetModeConserved( ShadeModeSave );

		tShade = sShade;

		if ( tShade == 0 ) continue;
		// Don't comment tert cols.
		// 
		if ( tShade < 3 && tSPS.RowNum < 'A') {
			continue;
		}

		// Don't comment 60% rows.
		if ( tShade == 1 ) {
			continue;
		}

		// Set the Consensus Row.
		char tComment = tSPS.RowNum;

		if ( tComment == 'T' || tComment == 'U' ) { 
			if ( m_UserVars.m_ProjectType == 3 ) {
				tComment = 'T';
			} else if ( m_UserVars.m_ProjectType == 4 ) {
				tComment = 'U';
			}
		}
		
		if ( tShade != 3 ) {
			tComment = tolower(tComment);
		}

		// comments on bottom comment row?
		if ( pConsensusRow != NULL ) {
			// Use Top Consensus Row
			(pConsensusRow->pGeneStor)[tCount].CharDisplay = tComment;
		}
	}
}

void 
CGenedocDoc::GetDNAAmbiguous( 
	ShadePairStruct *pSPS, 
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int *MaxMatchCount, 
	DWORD tCount, 
	int Depth )
{
	int MatchArr[2][26];
	char tChar;
	int j;
	typedef struct {
		int Label;
		int	Count;		// Number of Matches
		char Data[MAXSHADEGROUP + 1];	// The chars
	} ScoreStruct;
	int tMaxC;
	int psCount = 0;

//    ScoreStruct *Scores;
	ScoreStruct tSc;
	
	ScoreStruct Scores[26];

	for ( int i = 0; i < Depth; ++i ) {
		pSPS[i].Group[0] = 0;
		pSPS[i].RowNum = 'A';
	}

	while ( Depth-- ) {
		
		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for ( int i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		int gotsom = 0;
		int i;
		for ( i = 0; i < RowCount; ++i ) {
			//
			tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			tChar = toupper(tChar);
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				continue;
			}

			int getout = 0;
			for ( int ti = 0; ti < psCount; ++ti ) {
				int tl = strlen( pSPS[ti].Group );
				for ( int tx = 0; tx < tl; ++tx ) {
					if ( pSPS[ti].Group[tx] == tChar ) {
						getout = 1;
						tx = tl;
						ti = psCount;
						break;
					}
				}
			}
			if ( getout) continue;
			gotsom = 1;

			switch( tChar ) {
			case 'A':
				MatchArr[0]['A'-'A']++;
				break;
			case 'G':
				MatchArr[0]['G'-'A']++;
				break;
			case 'C':
				MatchArr[0]['C'-'A']++;
				break;
			case 'T':
				MatchArr[0]['T'-'A']++;
				break;
			case 'U':
				MatchArr[0]['T'-'A']++;
				break;
			case 'Y':
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['Y'-'A']++;
				break;
			case 'R':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['R'-'A']++;
				break;
			case 'W':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['W'-'A']++;
				break;
			case 'S':
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['S'-'A']++;
				break;
			case 'K':
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['K'-'A']++;
				break;
			case 'M':
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['M'-'A']++;
				break;
			case 'B':
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['B'-'A']++;
				break;
			case 'D':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['D'-'A']++;
				break;
			case 'H':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['H'-'A']++;
				break;
			case 'V':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['V'-'A']++;
				break;
			case 'N':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['N'-'A']++;
				MatchArr[0]['X'-'A']++;
				break;
			case 'X':
				MatchArr[0]['A'-'A']++;
				MatchArr[0]['C'-'A']++;
				MatchArr[0]['G'-'A']++;
				MatchArr[0]['T'-'A']++;
				MatchArr[0]['N'-'A']++;
				MatchArr[0]['X'-'A']++;
				break;
			}
		}

		// Anything left to do?
		if ( !gotsom ) return;

		// Now do the single Chars
		for (int i = 0; i < 26; ++i ) {
			Scores[i].Label = Scores[i].Data[0] = MatchArr[1][i] + 'A';
			Scores[i].Data[1] = 0;
			Scores[i].Count = MatchArr[0][i];
		}

		// Sort blindly now by Number of matches
		for (int i = 0; i < (26 - 1); ++i ) {
			for ( j = 0; j < (26 - 1); ++j ) {
				if ( Scores[j].Count < Scores[j+1].Count ) {
					tSc = Scores[j];
					Scores[j] = Scores[j+1];
					Scores[j+1] = tSc;
				}
			}
		}


		// Now look for how many highest matches
		tMaxC = Scores[0].Count;
		int Count = 1;
		for ( i = 1; i < 26 ; ++i ) {
			if ( Scores[i].Count < tMaxC ) break;
			Count++;
		}

		char cCons;

		if ( Count > 1 ) {
			for ( i=0; i < Count; ++i ) {
				if ( 
					Scores[i].Label != 'C' &&
					Scores[i].Label != 'A' &&
					Scores[i].Label != 'G' &&
					Scores[i].Label != 'T' 
				) break;
			}

			if ( i != Count ) {
				cCons = Scores[i].Label;
			} else {
				// ONly non-amb codes in top level ...
				int num = 0;
				for ( i=0; i < Count; ++i ) {
					switch ( Scores[i].Label ) {
					case 'T':
						num |= 1;
						break;
					case 'G':
						num |= 2;
						break;
					case 'C':
						num |= 4;
						break;
					case 'A':
						num |= 8;
						break;
					}
				}
				switch (num) {
				case 12: 
					cCons = 'M';
					break;
				case 10: 
					cCons = 'R';
					break;
				case 9: 
					cCons = 'W';
					break;
				case 6: 
					cCons = 'S';
					break;
				case 5: 
					cCons = 'Y';
					break;
				case 3: 
					cCons = 'K';
					break;
				case 14: 
					cCons = 'V';
					break;
				case 13: 
					cCons = 'H';
					break;
				case 11: 
					cCons = 'D';
					break;
				case 7: 
					cCons = 'B';
					break;
				case 15: 
					cCons = 'N';
					break;
				}
			}
		} else {
			cCons = Scores[0].Label;
		}

		pSPS[psCount].RowNum = cCons;
		if ( psCount == 0 ) {
			*MaxMatchCount = Scores[0].Count;
		}

		switch( cCons ) {
		case 'A':
			strcpy ( pSPS[psCount].Group, "ARWMDHVNX" );
			break;
		case 'G':
			strcpy ( pSPS[psCount].Group, "GRSKBDVNX" );
			break;
		case 'C':
			strcpy ( pSPS[psCount].Group, "CYSMBHVNX" );
			break;
		case 'T':
			strcpy ( pSPS[psCount].Group, "TUYWKBDHNX" );
			break;
		case 'Y':
			strcpy ( pSPS[psCount].Group, "CTUYNX" );
			break;
		case 'R':
			strcpy ( pSPS[psCount].Group, "AGRNX" );
			break;
		case 'W':
			strcpy ( pSPS[psCount].Group, "ATUWNX" );
			break;
		case 'S':
			strcpy ( pSPS[psCount].Group, "CGSNX" );
			break;
		case 'K':
			strcpy ( pSPS[psCount].Group, "TUGKNX" );
			break;
		case 'M':
			strcpy ( pSPS[psCount].Group, "CAMNX" );
			break;
	// triplets
		case 'B':
			strcpy ( pSPS[psCount].Group, "CGTUYSKBNX" );
			break;
		case 'D':
			strcpy ( pSPS[psCount].Group, "AGTURWKDNX" );
			break;
		case 'H':
			strcpy ( pSPS[psCount].Group, "ACTUYWMHNX" );
			break;
		case 'V':
			strcpy ( pSPS[psCount].Group, "ACGRSMVNX" );
			break;
		case 'N':
			strcpy ( pSPS[psCount].Group, "ACGTUYRWSKMBDHVNX" );
			break;
		case 'X':
			strcpy ( pSPS[psCount].Group, "ACGTUYRWSKMBDHVNX" );
			break;
		}

		psCount++;
	}

	return;
}
	
