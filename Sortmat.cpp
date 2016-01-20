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


// The char for the comment string is returned in rSPS[n].RowNum
void
CGenedocDoc::SortMatchArr( CDisplayVars *DisplayVars, int MatchArr[2][26], ShadePairStruct* rSPS, int *Count, int Depth )
{
	// Code to include
	int i, j, k;
	typedef struct {
		int Label;
		int	Count;		// Number of Matches
		char Data[MAXSHADEGROUP + 1];	// The chars
	} ScoreStruct;
	int tMaxC;

    ScoreStruct *Scores;
	ScoreStruct tSc;
	int TotalCount;
    
	if ( DisplayVars->GetGroupEnabled() ) {

		int DupArr[26];
		int GroupCount = m_UserVars.m_ShadePairArray.GetSize();

	
		// Lets see if any of the Group Sets add up to a Higher Count.
	
		TotalCount = GroupCount + 26;
		
		Scores = new ScoreStruct[TotalCount];
		
		if (Scores == 0 ) {
			AfxMessageBox("SortMAtchArr:new:fail:1");
			return;
		}
		
		// Clear out DupArr
		memset ( DupArr, 0, sizeof(DupArr) );
	
		// First do the Groups of numbers .. kill out DupArr
		for ( i = 0; i < GroupCount; ++i ) {
			ShadePairStruct* tSPS = (ShadePairStruct*)m_UserVars.m_ShadePairArray[i];
			int tLen = strlen ( tSPS->Group );
			tMaxC = 0;
			int GroupMatches = 0;
			// Sum up counts for this group
			for ( j=0; j < tLen; ++j ) {
				char tChar = tSPS->Group[j];
				tChar = toupper(tChar);
				tChar -= 'A';
				if ( MatchArr[0][tChar] != 0 ) {
					GroupMatches++;
				}
				tMaxC += MatchArr[0][tChar];
			}
			// If a good group, set entries in DupArr
			if ( GroupMatches > 1 ) {
				for ( j=0; j < tLen; ++j ) {
					char tChar = tSPS->Group[j];
					tChar = toupper(tChar);
					tChar -= 'A';
					DupArr[tChar] = 1;
				}
			} else {
				tMaxC = 0;
			}
				
			strcpy ( Scores[i + 26].Data, tSPS->Group );
			char *pc = Scores[i+26].Data;
			while ( *pc != 0 ) *pc++ = toupper( *pc );
			Scores[i + 26].Count = tMaxC;
			Scores[i+26].Label = tSPS->RowNum + '0';
		}
	
	
		// Now do the single Chars
		for ( i = 0; i < 26; ++i ) {
			Scores[i].Label = Scores[i].Data[0] = MatchArr[1][i] + 'A';
			Scores[i].Data[1] = 0;
			if ( DupArr[i] == 0 ) {
				Scores[i].Count = MatchArr[0][i];
			} else {
				Scores[i].Count = 0;
			}
		}
	} else {
		// Do only single chars

		TotalCount = 26;
		
		Scores = new ScoreStruct[TotalCount];
		if (Scores == 0 ) {
			AfxMessageBox("SortMAtchArr:new:fail:2");
			return;
		}
		// Now do the single Chars
		for ( i = 0; i < 26; ++i ) {
			Scores[i].Label = Scores[i].Data[0] = MatchArr[1][i] + 'A';
			Scores[i].Data[1] = 0;
			Scores[i].Count = MatchArr[0][i];
		}
	}
	
		
	// Sort blindly now by Number of matches
	for ( i = 0; i < (TotalCount - 1); ++i ) {
		for ( j = 0; j < (TotalCount - 1); ++j ) {
			if ( Scores[j].Count < Scores[j+1].Count ) {
				tSc = Scores[j];
				Scores[j] = Scores[j+1];
				Scores[j+1] = tSc;
			}
		}
	}
	
	int totScores = 0;

	// delete matches if groups enabled	
	if ( Count != NULL ) {
		if ( Scores[0].Count < *Count ) {
			*Count = Scores[0].Count;
			delete Scores;
			return;
		}
	}

	// Find highest by count/score, 
	do {
		// Now look for how many highest matches
		tMaxC = Scores[totScores].Count;
		// Test if we done all we can do!
		if ( tMaxC == 0 ) break;
		for ( i = totScores + 1; i < TotalCount; ++i ) {
			if ( Scores[i].Count != tMaxC ) {
				break;
			}
		}
	
		tMaxC = i - totScores;
		// if a tie, then we sort by scores ...
		for ( i = totScores; i < (totScores + tMaxC - 1); ++i ) {
			for ( j = totScores; j < (totScores + tMaxC - 1); ++j ) {
				// Ahh yes, the 'score' ...
				long CumScore1 = 0, CumScore2 = 0;
				char *pc, *pc2;

				pc = Scores[j].Data;
				while ( *pc != 0 ) {
					char CurData = *pc;
					for ( k = 0; k < 26; ++k ) {
						// Test nothing to test against
						if ( MatchArr[0][k] == 0 ) continue;
						pc2 = Scores[j].Data;
						while ( *pc2 != 0 ) {
							if ( (MatchArr[1][k] + 'A') == *pc2 ) {
								break;
							}
							pc2++;
						}
						if ( *pc2 != 0 ) continue;
						CumScore1 += 
							ScoreCurrentArray ( CurData, MatchArr[1][k] + 'A' ) 
							* (MatchArr[0][k]) 
							* (MatchArr[0][CurData - 'A'])
						;
					}
					pc++;
				}
				
				pc = Scores[j+1].Data;
				while ( *pc != 0 ) {
					char CurData = *pc;
					for ( k = 0; k < 26; ++k ) {
						// Test nothing to test against
						if ( MatchArr[0][k] == 0 ) continue;
						pc2 = Scores[j+1].Data;
						while ( *pc2 != 0 ) {
							if ( (MatchArr[1][k] + 'A') == *pc2 ) {
								break;
							}
							pc2++;
						}
						if ( *pc2 != 0 ) continue;
						CumScore2 += 
							ScoreCurrentArray ( CurData, MatchArr[1][k] + 'A' ) 
							* (MatchArr[0][k]) 
							* (MatchArr[0][CurData - 'A'])
						;
					}
					pc++;
				}
				
// Is this the test? 
				if ( CumScore1 > CumScore2 ) {
					tSc = Scores[j];
					Scores[j] = Scores[j+1];
					Scores[j+1] = tSc;
				}
			}
		}

		// Add up count and Offset		
		totScores += tMaxC;

	} while ( totScores < Depth );

	// Return 'Depth' answers.	
	for ( i = 0; i < Depth; ++i ) {
		strcpy ( rSPS[i].Group, Scores[i].Data );
		rSPS[i].RowNum = Scores[i].Label;
	}

	// This too if he wants it.
	if ( Count != NULL ) {
		*Count = Scores[0].Count;
	}

	delete Scores;

}

