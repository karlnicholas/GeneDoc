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

#ifndef _WIN32
#pragma optimize ("", off )
#endif


int 
CGenedocDoc::PairWiseScore( DWORD *nStartRange, DWORD *nEndRange, 
unsigned long *Score, int RowCount, ShadeSegStc *pSegArr )
{

	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;
	DWORD tCount;
	char tGapChar;
	int rScore;
	GeneStor tGStor;

	if ( m_UserVars.m_GapInd == 0 ) {
		tGapChar = '-';
	} else {
		tGapChar = '.';
	}
	
	*Score = 0;

//	long NewGap = -1;
//	long GapLen = -1;
// Now held in genedoc.h

	int OpenGp = 0, TopGap = 0;

	for ( int n = 2; n < RowCount - 1; ++n ) {		// Loop A
	
		for ( int m = n + 1; m < RowCount; ++m ) {	// Loop B
		
			tCount = StartRange; 
			while ( tCount <= EndRange ) {

				tGStor = (pSegArr[m].pGeneStor)[tCount];	// Indexed from Loop B
				char Nuc1 = toupper(tGStor.CharGene);
				tGStor = (pSegArr[n].pGeneStor)[tCount];	// Indexed from Loop A
				char Nuc2 = toupper(tGStor.CharGene);

				int gc1 = !(Nuc1 >= 'A' && Nuc1 <= 'Z');
				int gc2 = !(Nuc2 >= 'A' && Nuc2 <= 'Z');

				if ( !gc1 && !gc2 ) {
					rScore = ScoreCurrentArray(Nuc1, Nuc2 );
					if ( rScore == INT_MIN ) {
						AfxMessageBox ( "Invalid Char in Score Range" );
						return 0;
					}
					*Score += rScore;
					OpenGp = 0;
				} else if ( gc1 && !gc2 ) {
					*Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						*Score += NewGap;
						TopGap = 1;
					} else {
						if ( !TopGap ) {
							*Score += NewGap;
							TopGap = 1;
						}
					}
				} else if ( !gc1 && gc2 ) {
					*Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						*Score += NewGap;
						TopGap = 0;
					} else {
						if ( TopGap ) {
							*Score += NewGap;
							TopGap = 0;
						}
					}
				}
				tCount = tCount + 1L;
			}
		}
	}

	return 1;
}

#ifndef _WIN32
#pragma optimize ("", on )
#endif

