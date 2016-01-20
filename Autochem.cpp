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

//     Proline:                    P   X -
//     Glycine:      G                 X -
//        Tiny:     AG           S     X -
//       Small:   VCAG         DNSTP   X -
//    Positive:           HKR          X -
//    Negative:              E D       X -
//     Charged:           HKRE D       X -
//  Amphoteric:           H REQDN    BZX -
//       Polar:         YWHKREQDNST  BZX -
//   Aliphatic: ILV A                  X -
//    Aromatic:        FYWH            X -
// Hydrophobic: ILVCAGMFYWH       TP   X -



// Changed to this as per Dad ...

//     Proline:                    P   X -
//     Glycine:      G                 X -
//        Tiny:     AG           S     X -
//       Small:   VCAG         DNSTP   X -
//    Positive:           HKR          X -
//    Aromatic:        FYWH            X -
//    Negative:              E D       X -
//     Charged:           HKRE D       X -
//  Amphoteric:           H REQDN    BZX -
//       Polar:         YWHKREQDNST  BZX -
//   Aliphatic: ILV A                  X -
// Hydrophobic: ILVCAGMFYWH       TP   X -

void 
CGenedocDoc::AutoShadeGroupChem(
	ShadeSegStc* pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc* pConsensusRow 
) 
{

	if ( m_UserVars.m_ChemPropShowProp ) {
		AutoShadeGroupChemCons( pSegArr, RowCount, ShadeLevel, DisplayVars, pConsensusRow );
		return;
	}

	int LevelArr[26];
	stcChemProp *ChemGroup;
	stcChemProp *ChemColor = m_UserVars.ChemGroupOxi;
	if ( m_UserVars.m_ChemPropCysteine == 0 ) 
		ChemGroup = m_UserVars.ChemGroupOxi;
	else 
		ChemGroup = m_UserVars.ChemGroupRed;
	
	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {

		int i;

		int level;
		int ChemPropCount = 0;

		do {
			// Inner Loop
			memset ( LevelArr, 0, sizeof(LevelArr) );
			// init locations
			int GroupCount = strlen ( ChemGroup[ChemPropCount].Chem );

			// First do the Groups of numbers .. kill out DupArr
			for ( i = 0; i < GroupCount; ++i ) {
				char tChar = ChemGroup[ChemPropCount].Chem[i];
				tChar = toupper(tChar);
				tChar -= 'A';
				LevelArr[tChar] = 1;
			}

			level = 1;

			for ( i = 0; i < RowCount; ++i ) {
				char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
				tChar = toupper(tChar);
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					tChar -= 'A';
					if ( !LevelArr[tChar] ) {
						level = -1;
						break;
					}
				}
			}

			if ( level == -1 ) ChemPropCount++;

		} while ( level == -1 && ChemPropCount < 12 );


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

	
			if ( level != -1 ) {
				// Lets Clear out old shades while here.
				tChar = toupper(tChar);
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					if ( m_UserVars.ChemPropEnabled[ChemPropCount] ) {
						(pSegArr[i].pGeneStor)[tCount].TextColor = ChemColor[ChemPropCount].TextColor;
						(pSegArr[i].pGeneStor)[tCount].BackColor = ChemColor[ChemPropCount].BackColor;
					}
				}
			}
		}
	}
}

void 
CGenedocDoc::AutoShadeGroupChemCons(
	ShadeSegStc* pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc* pConsensusRow 
) 
{

	int LevelArr[26];
	stcChemProp *ChemGroup;
	if ( m_UserVars.m_ChemPropCysteine == 0 ) 
		ChemGroup = m_UserVars.ChemGroupOxi;
	else 
		ChemGroup = m_UserVars.ChemGroupRed;

	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		
		int i;

		int level;
		int ChemPropCount = 0;
		char FirstChar = 0;

		if ( ShadeLevel == SHADELEVEL2 ) {
		
	
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

			for ( i = 0; i < RowCount; ++i ) {
				char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
				tChar = toupper(tChar);
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					if ( !FirstChar ) FirstChar = tChar;
					else if ( tChar != FirstChar ) break;
				}
			}
			if ( i == RowCount ) {
				for ( i = 0; i < RowCount; ++i ) {
					// Lets Clear out old shades while here.
					char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
					tChar = toupper(tChar);
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.ChemCons[0].TextColor;
						(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.ChemCons[0].BackColor;
					}
				}
			}

		} else {

			int Ident;
			if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM ) {
				for ( i = 0; i < RowCount; ++i ) {
					if ( (pSegArr[i].pGeneStor)[tCount].BackColor == m_UserVars.ChemCons[0].BackColor )
						break;
				}
				if ( i != RowCount ) continue;
			} else {
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
			}

			do {
				// Inner Loop
				memset ( LevelArr, 0, sizeof(LevelArr) );
				// init locations
				int GroupCount = strlen ( ChemGroup[ChemPropCount].Chem );
				
				// First do the Groups of numbers .. kill out DupArr
				for ( i = 0; i < GroupCount; ++i ) {
					char tChar = ChemGroup[ChemPropCount].Chem[i];
					tChar = toupper(tChar);
					tChar -= 'A';
					LevelArr[tChar] = 1;
				}

				level = 1;
				char FirstChar = 0;
				Ident = 1;

				for ( i = 0; i < RowCount; ++i ) {
			
					char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
					tChar = toupper(tChar);
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						tChar -= 'A';
						if ( !LevelArr[tChar] ) {
							level = -1;
							break;
						}
						// Test for Identity
						if ( !FirstChar ) FirstChar = tChar;
						else if ( tChar != FirstChar ) Ident = 0;
					}
				}

				if ( level == -1 ) ChemPropCount++;

			} while ( level == -1 && ChemPropCount < 12 );


			for ( i = 0; i < RowCount; ++i ) {
		
				if ( level != -1 ) {
					char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
					tChar = toupper(tChar);
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						if ( Ident ) {
							(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.ChemCons[1].TextColor;
							(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.ChemCons[1].BackColor;
						} else {
							(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.ChemCons[2].TextColor;
							(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.ChemCons[2].BackColor;
						}
					}
				}
			}
		}
	}
}

