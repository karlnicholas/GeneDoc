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
CGenedocDoc::AutoShadePCR(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{
TRY {

	int i;
	int MatchArr[2][26];
	ShadePairStruct tSPS;

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

		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for ( i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		int GotSomething = 0;

		for ( i = 0; i < RowCount; ++i ) {

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;

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

		int MaxMatchCount;

		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
			GetDNAAmbiguous( &tSPS, pSegArr, RowCount, &MaxMatchCount, tCount, 1 );
		} else {
			PCRMatchArr ( MatchArr, &tSPS, &MaxMatchCount );
			// SortMatchArr ( DisplayVars, MatchArr, &tSPS, &MaxMatchCount, 1 );
		}

		if ( !(MaxMatchCount >= (int)((double)RowCount * (m_UserVars.m_GroupConsLevel / 100.0) + 0.5) ) ) {
			// Nothing here
			continue;
		}

		
		// Do it for other sequences ...
		// Inner Loop
		memset ( MatchArr, 0, sizeof(MatchArr) );
		// init locations
		for ( i = 0; i < 26; ++i ) {
			MatchArr[1][i] = i;
		}

		GotSomething = 0;

		for ( i = 0; i < pSegCount; ++i ) {

			int tChar = (pOSegArr[i].pGeneStor)[tCount].CharGene;

			// if ( (tChar == '-') || (tChar == '.') ) {
			tChar = toupper(tChar);
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				continue;
			}
			GotSomething = 1;
			if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_DNAAmbEn ) {
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
			} else {
				tChar -= 'A';
				MatchArr[0][tChar]++;
			}
		}

		int tMaxC;
		// Now Check to Other Groups to see if the max found residue(s) are in there
		if ( GotSomething ) {
			if ( m_UsePCRSim && tSPS.RowNum == '1' && !1 ) {
				int tLen = m_UserVars.m_PCRSimilarities.GetLength();
				tMaxC = 0;
				int GroupMatches = 0;
				// Sum up counts for this group
				for ( int j=0; j < tLen; ++j ) {
					char tChar = m_UserVars.m_PCRSimilarities[j];
					tChar = toupper(tChar);
					tChar -= 'A';
					if ( MatchArr[0][tChar] != 0 ) {
						GroupMatches++;
					}
					tMaxC += MatchArr[0][tChar];
				}
			} else {
				// And its length
				tMaxC = 0;
				int tLen = strlen ( tSPS.Group );
				for ( int j=0; j < tLen; ++j ) {
					tMaxC += MatchArr[0][tSPS.Group[j] - 'A'];
				}
			}
		} else {
			tMaxC = 0;
		}

		if ( tMaxC > (int)((double)RowCount * (m_UserVars.m_PCRLevel / 100.0) + 0.5) ) {
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
CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH

}

// The char for the comment string is returned in rSPS[n].RowNum
void
CGenedocDoc::PCRMatchArr( int MatchArr[2][26], ShadePairStruct* rSPS, int *Count )
{
	// Code to include
	int i, j;
	typedef struct {
		int Label;
		int	Count;		// Number of Matches
		char Data[MAXSHADEGROUP + 1];	// The chars
	} ScoreStruct;
	int tMaxC;

    ScoreStruct *Scores;
	ScoreStruct tSc;
	int TotalCount;
    
	if ( m_UsePCRSim ) {

		int DupArr[26];
		int GroupCount = 1;

	
		// Lets see if any of the Group Sets add up to a Higher Count.
	
		TotalCount = 1 + 26;
		
		Scores = new ScoreStruct[TotalCount];
		
	
		// Clear out DupArr
		memset ( DupArr, 0, sizeof(DupArr) );
	
		int tLen = m_UserVars.m_PCRSimilarities.GetLength();
		tMaxC = 0;
		int GroupMatches = 0;
		// Sum up counts for this group
		for ( j=0; j < tLen; ++j ) {
			char tChar = m_UserVars.m_PCRSimilarities[j];
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
				char tChar = m_UserVars.m_PCRSimilarities[j];
				tChar = toupper(tChar);
				tChar -= 'A';
				DupArr[tChar] = 1;
			}
		} else {
			tMaxC = 0;
		}
			
		strcpy ( Scores[26].Data, m_UserVars.m_PCRSimilarities );
		char *pc = Scores[26].Data;
		while ( *pc != 0 ) *pc++ = toupper( *pc );
		Scores[26].Count = tMaxC;
		Scores[26].Label = 1 + '0';
		// Searched the similarity array	


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

		// Now do the single Chars
		for ( i = 0; i < 26; ++i ) {
			Scores[i].Label = Scores[i].Data[0] = MatchArr[1][i] + 'A';
			Scores[i].Data[1] = 0;
			Scores[i].Count = MatchArr[0][i];
		}
	}

	// do all the sorting now ...
		
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
	
	// Return First answers.
	strcpy ( rSPS->Group, Scores[0].Data );
	rSPS->RowNum = Scores[0].Label;

	// This too if he wants it.
	*Count = Scores[0].Count;

	delete Scores;

}

