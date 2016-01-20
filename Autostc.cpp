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



BOOL 
CGenedocDoc::SetStructureAlignment(CDisplayVars *DisplayVars)
{

	int RowCount;
	ShadeSegStc *pSegArr;

	if ( pGSFiller == NULL ) {
		return 0;
	}
	
	if ( DisplayVars->GetStcGroup().GetResiduesSize() == 0 ) return 0;

	CPtrList *pGroupList;

	if ( DisplayVars->GetGroupName().GetLength() != 0 ) {
		pGroupList = DisplayVars->GetGroupList();
	} else {
		pGroupList = &pGSFiller->SegDataList;
	}

	RowCount = pGroupList->GetCount();	// Subtract 1 for comment row. here
	
	pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here

	if ( pSegArr == 0 ) {
		AfxMessageBox("AutoShadeProperty:New Fail:1");
		return 0;
	}

	CGeneSegment *tCGSeg;
	int i = 0;
	HANDLE tSegHandle;
	int MasterRow = -1;

	CString MasterSeq = DisplayVars->GetStcGroup().GetMasterSeq();

	POSITION tPos = pGroupList->GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGroupList->GetNext(tPos);

		// Check for master seq for later.
		if ( tCGSeg->GetTitle() == MasterSeq ) MasterRow = i;

		// Lock it down
		tSegHandle = tCGSeg->GetTextHandle();
		pSegArr[i].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
		pSegArr[i].pCGSeg = tCGSeg;
		if ( pSegArr[i].pGeneStor == NULL) {
			AfxMessageBox("AutoShadeProperty:GlobalLock:Fail:1");
			delete pSegArr;
			return 0;
		}
		i++;
	}

	// init locations
	DWORD StcResiduesPos = 1;
	HGLOBAL hStcResidues = DisplayVars->GetStcGroup().GetResidues();
	DWORD StcResiduesLength = DisplayVars->GetStcGroup().GetResiduesSize();


//	CDisplayVars *pDV;
//	CPtrList *pPL = &m_UserVars.m_DisplayVars;
	
	DWORD OuterCount = tCGSeg->GetTextLength();

	DWORD ScoreValue = 0;
	DWORD ScoreCount = 0;
	DWORD tCount;

	char *pStcResidues = (char *)GlobalLock( hStcResidues );
	if ( pStcResidues == NULL ) goto ErrorOut;

	if ( MasterRow == -1 ) {
		AfxMessageBox( "Master Sequence Not Found in Group" );
		goto ErrorOut;
	}

//	tPos = pPL->GetHeadPosition();
//	while ( tPos != NULL ) {
//		pDV = (CDisplayVars *)pPL->GetNext(tPos);
//		if ( pDV == DisplayVars ) {
//			break;
//		}
//	}

	for ( tCount = 0L; tCount < OuterCount; ++tCount ) {

		ScoreValue = 0L;

		if ( StcResiduesPos != 0L ) {
			char tChar = (pSegArr[MasterRow].pGeneStor)[tCount].CharGene;
			tChar = toupper (tChar);
			if ( (tChar >= 'A' && tChar <= 'Z') ) { 
				if ( tChar == toupper(pStcResidues[StcResiduesPos - 1L]) ) {
					ScoreValue = StcResiduesPos;
				}
			}
		}
		

		for ( i = 0; i < RowCount; ++i ) {
			
			// if its a comment row .. go on .. after shading.
			if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
		 		continue;
			}
		
			// Save New Residue Location Value
			(pSegArr[i].pGeneStor)[tCount].CharScore = ScoreValue;
		}


		if ( ScoreValue > 0L ) {
			if ( StcResiduesPos++ >= StcResiduesLength ) {
				StcResiduesPos = 0L;
			}
			ScoreCount++;
		}
	}


	if ( ! ((ScoreCount > (OuterCount/2))||(ScoreCount > (StcResiduesLength/2))) ) {

		StcResiduesPos = 1;
		
		for ( tCount = 0L; tCount < OuterCount; ++tCount ) {

			ScoreValue = 0L;

			if ( StcResiduesPos != 0L ) {
				char tChar = (pSegArr[MasterRow].pGeneStor)[tCount].CharGene;
				tChar = toupper (tChar);
				if ( (tChar >= 'A' && tChar <= 'Z') ) { 

					if ( tChar == toupper(pStcResidues[StcResiduesPos - 1L]) ) {
						ScoreValue = StcResiduesPos;
					} else {
						for ( ;StcResiduesPos < StcResiduesLength; StcResiduesPos++ ) {
							if ( tChar == toupper(pStcResidues[StcResiduesPos - 1L]) ) {
								if ( (StcResiduesPos+1 < StcResiduesLength ) && (tCount+1 < OuterCount) ) {
									char tChar2 = toupper((pSegArr[MasterRow].pGeneStor)[tCount+1].CharGene);
									if ( tChar2 >= 'A' && tChar2 <= 'Z' ) {
										if ( toupper(pStcResidues[StcResiduesPos]) == tChar2 ) {
											ScoreValue = StcResiduesPos;
											break;
										}
									} else {
										ScoreValue = StcResiduesPos;
										break;
									}
								} else {
									ScoreValue = StcResiduesPos;
									break;
								}
							}
						}
					}
				}
			}
			

			for ( i = 0; i < RowCount; ++i ) {
				
				// if its a comment row .. go on .. after shading.
				if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
		 			continue;
				}
			
				// Save New Residue Location Value
				(pSegArr[i].pGeneStor)[tCount].CharScore = ScoreValue;
			}


			if ( ScoreValue > 0L ) {
				if ( StcResiduesPos++ >= StcResiduesLength ) {
					StcResiduesPos = 0L;
				}
			}
		}
	}	
	
	GlobalUnlock( hStcResidues );

ErrorOut:

	tPos = pGroupList->GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGroupList->GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		GlobalUnlock( tSegHandle );
	}
	delete pSegArr;

	return 1;
}

void 
CGenedocDoc::AutoShadeStructure(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{

	int i;

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
			
			if ( ShadeLevel != SHADELEVEL0 ) {

				DWORD ScoreValue = (pSegArr[i].pGeneStor)[tCount].CharScore;
	
				if ( ScoreValue > 0 ) {
	
					DisplayVars->GetStcGroup().GetCurrentData ( ScoreValue - 1, 
						&(pSegArr[i].pGeneStor)[tCount].TextColor, 
						&(pSegArr[i].pGeneStor)[tCount].BackColor
					);
	
				}
			
			}
		}
	}
}

