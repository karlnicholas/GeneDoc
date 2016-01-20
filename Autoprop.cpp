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
CGenedocDoc::AutoShadeProperty(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{
	int LevelArr[26];
	
	int PropLevel = ShadeLevel - SHADELEVEL2;
	if ( PropLevel < 0 ) PropLevel = 0;
	
	int i = 0, j;
	int PropStyle = DisplayVars->GetPropStyle();

	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();

	// Inner Loop
	memset ( LevelArr, 0, sizeof(LevelArr) );
	// init locations
	int GroupCount = 
		((CPtrArray*)(DisplayVars->GetProperty().GetArray( PropLevel )))->GetSize();
	PropertyStruct* tpPS;
	
	// First do the Groups of numbers .. kill out DupArr
	for ( i = 0; i < GroupCount; ++i ) {
		tpPS = (PropertyStruct*)
			((CPtrArray*)(DisplayVars->GetProperty().GetArray( PropLevel )))->GetAt(i);
	
		int tLen = strlen ( tpPS->Group );
		// Sum up counts for this group
		for ( j=0; j < tLen; ++j ) {
			char tChar = tpPS->Group[j];
			// if ( (tChar == '-') || ( tChar == '.') ) { 
			if ( !(tChar >= 'A' && tChar <= 'Z') ) { 
				continue;
			}
			tChar = toupper(tChar);
			tChar -= 'A';
			LevelArr[tChar] = i + 1;		// Set the level of the char in the array
		}
	}

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
	
		int level = -1;
		if ( PropStyle == 0 ) {
			for ( i = 0; i < RowCount; ++i ) {

				char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
				tChar = toupper(tChar);

				if ( !(tChar >= 'A' && tChar <= 'Z') ) { 
					level = -1;
					break;
				}
				tChar -= 'A';
				if ( level == -1 ) {
					level = LevelArr[tChar];
				} else if ( level != LevelArr[tChar] ) {
					level = -1;
					break;
				}
			}
		}

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
	
			if ( ShadeLevel != SHADELEVEL0 ) {

				if ( PropStyle == 0 ) {
					if ( level != -1 ) {
						// Lets Clear out old shades while here.
						GetLevelColors( DisplayVars, level, 
							&(pSegArr[i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[i].pGeneStor)[tCount].BackColor
						);
					}
				} else {
					tChar = toupper(tChar);
					if ( tChar >= 'A' && tChar <= 'Z' ) { 
						tChar -= 'A';
						GetLevelColors( DisplayVars, LevelArr[tChar], 
							&(pSegArr[i].pGeneStor)[tCount].TextColor, 
							&(pSegArr[i].pGeneStor)[tCount].BackColor
						);
					}
				}				
			}
		}
	}
}

