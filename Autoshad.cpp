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


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void
CGenedocDoc::AutoShade( int ShadeLevel, int ScoreAll) 
{
	if ( pGSFiller == NULL ) {
		return;
	}

	BeginWaitCursor();	// Let em know

	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPDNASET ) {
		AutoShadeDNASet();
	} else if ( !m_UserVars.m_GroupDisplayMode ) {
	

		if ( ShadeLevel == -1 ) {
			ShadeLevel = m_UserVars.m_Vars.GetLastShadeLevel();
		} else {
			m_UserVars.m_Vars.SetLastShadeLevel( ShadeLevel );
		}

		ShadeSegStc *pSegArr;
		ShadeSegStc *pConsensusRow = NULL;

		int RowCount;
		int i = 0, pSegCount = 0;
		CGeneSegment *tCGSeg;
		HANDLE tSegHandle;
		
		// TODO: Going to need to find a way to set the background colors for the comment rows.

		RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here

		pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here

		if ( pSegArr == 0 ) {
			AfxMessageBox("AutoShadeQuantify:New Fail 1");
			return;
		}

		int ConsensusCount = -1;

		if ( m_UserVars.m_ConsensusLine == 0 ) {
			// Use Top Consensus Row
			ConsensusCount = 1;
		} else if ( m_UserVars.m_ConsensusLine == 1 ) {
			// Use Bottom Consensus Row
			ConsensusCount = RowCount - 1;
		}
		// 2 = no consensus

		
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				tSegHandle = tCGSeg->GetTextHandle();
				pSegArr[pSegCount].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
				pSegArr[pSegCount].pCGSeg = tCGSeg;
				if ( pSegArr[pSegCount].pGeneStor == NULL) {
					AfxMessageBox("AutoShade:GlobalLock:Fail:1");
					delete pSegArr;
					return;
				}
				pSegCount++;
			} else if ( i == 1 || i == RowCount-1 ) {
				tSegHandle = tCGSeg->GetTextHandle();
				GeneStor *pGS = (GeneStor *) GlobalLock( tSegHandle );
			
				DWORD OuterCount = tCGSeg->GetTextLength();
				for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
					// Use Top Consensus Row
					pGS->CharDisplay = ' ';
					pGS->CharScore = 0;
					GetLevelColors( &m_UserVars.m_Vars, 0, &pGS->TextColor, &pGS->BackColor );
					pGS++;
				}
				GlobalUnlock( tSegHandle );
			} else {
				tSegHandle = tCGSeg->GetTextHandle();
				GeneStor *pGS = (GeneStor *) GlobalLock( tSegHandle );
			
				DWORD OuterCount = tCGSeg->GetTextLength();
				for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
					// Use Top Consensus Row
					pGS->CharDisplay = ' ';
					pGS->CharScore = 0;
					GetLevelColors( &m_UserVars.m_Vars, 0, &pGS->TextColor, &pGS->BackColor );
					pGS++;
				}
				GlobalUnlock( tSegHandle );
			}
			// comments on bottom comment row?
			if ( i == ConsensusCount ) {
				tSegHandle = tCGSeg->GetTextHandle();
				pConsensusRow = new ShadeSegStc;
				pConsensusRow->pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
				pConsensusRow->pCGSeg = tCGSeg;
				if ( pConsensusRow->pGeneStor == NULL) {
					AfxMessageBox("AutoShade:GlobalLock:Fail:2");
					delete pSegArr;
					if ( pConsensusRow != NULL ) delete pConsensusRow;
					return;
				}
			}
			i++;
		}


		int ModeConserved = m_UserVars.m_Vars.GetModeConserved();
		// Test For Residue Mode
		if ( m_UserVars.m_Vars.GetResidueMode() == 1 ) {
			if ( m_UserVars.m_Vars.GetDiffMode() == 1 ) {
				AutoShadeDifference( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			} else {
				AutoShadeDifference( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
			}
		} 
		
		if ( ModeConserved == SHADEPROPERTY 
			|| ModeConserved == SHADESTRUCTURE 
			|| ModeConserved == SHADESEARCH 
			|| ModeConserved == SHADEPHYSIOCHEM 
			|| ModeConserved == SHADELOGODDS ) 
		{
			if ( m_UserVars.m_Vars.GetResidueMode() == 0 
				|| (m_UserVars.m_Vars.GetResidueMode() == 1 && m_UserVars.m_Vars.GetDiffMode() == 0) 
			) {
				AutoShadeConserve( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			}
		}

			// Old Start
		if ( ModeConserved == SHADECONSERVED ) {
			if ( m_UserVars.m_Vars.GetDiffMode() == 1 && m_UserVars.m_Vars.GetResidueMode() == 1 ) {
				AutoShadeConserve( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
			} else {
				AutoShadeConserve( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			}
		} else if ( ModeConserved == SHADEQUANTIFY ) {
			if ( m_UserVars.m_Vars.GetDiffMode() == 1 && m_UserVars.m_Vars.GetResidueMode() == 1) {
				AutoShadeQuantify( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
			} else {
				AutoShadeQuantify( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			}
		} else if ( ModeConserved == SHADEPROPERTY ) {
			AutoShadeProperty( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		} else if ( ModeConserved == SHADESTRUCTURE ) {
			AutoShadeStructure( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		} else if ( ModeConserved == SHADEPHYSIOCHEM ) {
			AutoShadeGroupChem( pSegArr, pSegCount, 0, &m_UserVars.m_Vars, pConsensusRow );
		} else if ( ModeConserved == SHADESEARCH ) {
			AutoShadeSearch( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		} else if ( ModeConserved == SHADEIDENTITY ) {
			AutoShadeIdentity( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		} else if ( ModeConserved == SHADELOGODDS ) {
			AutoShadeLogOdds( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		}

		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				tSegHandle = tCGSeg->GetTextHandle();
				GlobalUnlock( tSegHandle );
			}
		}

		delete pSegArr;
		if ( pConsensusRow != NULL ) delete pConsensusRow;

	} else {
	
	// New Start
		
		ShadeSegStc *pSegArr;
		ShadeSegStc *pConsensusRow = NULL;

		int RowCount;
		int i = 0, pSegCount = 0;
		CGeneSegment *tCGSeg;
		HANDLE tSegHandle;
		
		// TODO: Going to need to find a way to set the background colors for the comment rows.

		RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here

		pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here

		if ( pSegArr == 0 ) {
			AfxMessageBox("AutoShadeQuantify:New Fail 1");
			return;
		}

		ShadeSegStc *pGroupArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here
		int gCount;

		int ConsensusCount = -1;

		if ( m_UserVars.m_ConsensusLine == 0 ) {
			// Use Top Consensus Row
			ConsensusCount = 1;
		} else if ( m_UserVars.m_ConsensusLine == 1 ) {
			// Use Bottom Consensus Row
			ConsensusCount = RowCount - 1;
		}
		// 2 = no consensus

		
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				tSegHandle = tCGSeg->GetTextHandle();
				pSegArr[pSegCount].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
				pSegArr[pSegCount].pCGSeg = tCGSeg;
				if ( pSegArr[pSegCount].pGeneStor == NULL) {
					AfxMessageBox("AutoShade:GlobalLock:Fail:1");
					delete pSegArr;
					return;
				}
				pSegCount++;
			} else if ( i == 1 || i == RowCount-1 ) {
				tSegHandle = tCGSeg->GetTextHandle();
				GeneStor *pGS = (GeneStor *) GlobalLock( tSegHandle );
			
				DWORD OuterCount = tCGSeg->GetTextLength();
				for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
					// Use Top Consensus Row
					pGS->CharDisplay = ' ';
					pGS->CharScore = 0;
					GetLevelColors( &m_UserVars.m_Vars, 0, &pGS->TextColor, &pGS->BackColor );
					pGS++;
				}
				GlobalUnlock( tSegHandle );
			} else {
				tSegHandle = tCGSeg->GetTextHandle();
				GeneStor *pGS = (GeneStor *) GlobalLock( tSegHandle );
			
				DWORD OuterCount = tCGSeg->GetTextLength();
				for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
					// Use Top Consensus Row
					pGS->CharDisplay = ' ';
					pGS->CharScore = 0;
					GetLevelColors( &m_UserVars.m_Vars, 0, &pGS->TextColor, &pGS->BackColor );
					pGS++;
				}
				GlobalUnlock( tSegHandle );
			}
			// comments on bottom comment row?
			if ( i == ConsensusCount ) {
				tSegHandle = tCGSeg->GetTextHandle();
				pConsensusRow = new ShadeSegStc;
				pConsensusRow->pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
				pConsensusRow->pCGSeg = tCGSeg;
				if ( pConsensusRow->pGeneStor == NULL) {
					AfxMessageBox("AutoShade:GlobalLock:Fail:2");
					delete pSegArr;
					if ( pConsensusRow != NULL ) delete pConsensusRow;
					return;
				}
			}
			i++;
		}


		// This takes care of consensus line ...
		if ( ShadeLevel == -1 ) {
			ShadeLevel = m_UserVars.m_Vars.GetLastShadeLevel();
		} else {
			m_UserVars.m_Vars.SetLastShadeLevel( ShadeLevel );
		}		


		int ShadeMode = m_UserVars.m_Vars.GetModeConserved();
		if ( ShadeMode == SHADECONSERVED 
			|| ShadeMode == SHADEPROPERTY 
			|| ShadeMode == SHADESTRUCTURE 
			|| ShadeMode == SHADESEARCH 
			|| ShadeMode == SHADELOGODDS  
			|| ShadeMode == SHADEPHYSIOCHEM ) {
			if ( m_UserVars.m_Vars.GetResidueMode() == 0 
				|| (m_UserVars.m_Vars.GetResidueMode() == 1 && m_UserVars.m_Vars.GetDiffMode() == 0) 
			) {
				AutoShadeConserve( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			}
		} else if ( ShadeMode == SHADEQUANTIFY ) {
			AutoShadeQuantify( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
		}

		int DoneDiff = 0;
		if ( m_UserVars.m_Vars.GetResidueMode() == 1 ) {
			if ( m_UserVars.m_Vars.GetDiffMode() == 1 ) {
				AutoShadeDifference( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, pConsensusRow );
			} else {
				AutoShadeDifference( pSegArr, pSegCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
			}
			// AutoShadeDifference( pSegArr, pSegCount, 0, &m_UserVars.m_Vars, NULL );
			DoneDiff = 1;
		}
			
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONS || m_UserVars.m_GroupDisplayMode == GROUPDISPCONSX ) {
			AutoShadeConserve( pSegArr, pSegCount, SHADELEVEL2, &m_UserVars.m_Vars, NULL );
		} else if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM && m_UserVars.m_ChemPropShowProp == 1 ) {
			AutoShadeGroupChemCons( pSegArr, pSegCount, SHADELEVEL2, &m_UserVars.m_Vars, NULL );
		}
			

		POSITION dPos = m_UserVars.m_DisplayVars.GetHeadPosition();
		// Skip first - no more, no more
		// m_UserVars.m_DisplayVars.GetNext(dPos);

		while ( dPos != NULL ) {
			CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(dPos);

			CPtrList *pPL = DisplayVars->GetGroupList();
				
			gCount = 0;

			for ( i = 0; i < pSegCount; ++i ) {
				if ( pPL->Find( pSegArr[i].pCGSeg ) != NULL ) {
					pGroupArr[gCount] = pSegArr[i];
					gCount++;
					pSegArr[i].pCGSeg = NULL;
				}
			}

			// If nothing in the group, skip it.
			if ( gCount == 0 ) continue;

			int tShadeLevel = DisplayVars->GetLastShadeLevel();
					
			int ModeConserved = DisplayVars->GetModeConserved();
			
			// Check if Base Diff Mode OverRides?
			int SaveDiff;
			if ( DoneDiff ) {
				SaveDiff = DisplayVars->GetResidueMode();
				DisplayVars->SetResidueMode(1);		// Force No Change of Diff
			} else {
				if ( DisplayVars->GetResidueMode() == 1 ) {
					AutoShadeDifference( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
				}
			}

			// Old Start
			if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONT || m_UserVars.m_GroupDisplayMode == GROUPDISPCONTNG ) {
				AutoShadeContrast( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPCR || m_UserVars.m_GroupDisplayMode == GROUPDISPPCRSIM ) {
				AutoShadePCR( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONS || m_UserVars.m_GroupDisplayMode == GROUPDISPCONSX ) {
				AutoShadeGroupConserve( pGroupArr, gCount, 0, DisplayVars, NULL );
			} else if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM ) {
				AutoShadeGroupChem( pGroupArr, gCount, 0, DisplayVars, NULL );
			} else if ( ModeConserved == SHADECONSERVED ) {
				AutoShadeConserve( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADEQUANTIFY ) {
				AutoShadeQuantify( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADEPROPERTY ) {
				AutoShadeProperty( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADESTRUCTURE ) {
				AutoShadeStructure( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADEPHYSIOCHEM ) {
				AutoShadeGroupChem( pGroupArr, gCount, 0, DisplayVars, NULL );
			} else if ( ModeConserved == SHADESEARCH ) {
				AutoShadeSearch( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADEIDENTITY ) {
				AutoShadeIdentity( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			} else if ( ModeConserved == SHADELOGODDS ) {
				AutoShadeLogOdds( pGroupArr, gCount, tShadeLevel, DisplayVars, NULL );
			}
			
			// Reset Diff Mode
			if ( DoneDiff ) {
				DisplayVars->SetResidueMode(SaveDiff);
			}

		}
		
		// Test For Residue Mode
		int ModeConserved = m_UserVars.m_Vars.GetModeConserved();

		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONSX ) {

			pSegCount = 0;
			POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
				tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
				if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
					pSegArr[pSegCount].pCGSeg = tCGSeg;
					pSegCount++;
				}
			}
			
			POSITION dPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			// Skip first - no more, no more
			// m_UserVars.m_DisplayVars.GetNext(dPos);

			while ( dPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(dPos);
			
				CPtrList *pPL = DisplayVars->GetGroupList();
				gCount = 0;

				for ( i = 0; i < pSegCount; ++i ) {
					if ( pPL->Find( pSegArr[i].pCGSeg ) != NULL ) {
						pGroupArr[gCount] = pSegArr[i];
						gCount++;
						pSegArr[i].pCGSeg = NULL;
					}
				}

				// If nothing in the group, skip it.
				if ( gCount == 0 ) continue;

				AutoGroupConsCross( pGroupArr, gCount, 0, DisplayVars, NULL );
			}
		}


		gCount = 0;
		for ( i = 0; i < pSegCount; ++i ) {
			if ( pSegArr[i].pCGSeg != NULL ) {
				pGroupArr[gCount] = pSegArr[i];
				gCount++;
			}
		}
			// Old Start
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM ) {
			// do nothing ..
		} else if ( ModeConserved == SHADECONSERVED ) {
			AutoShadeConserve( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADEQUANTIFY ) {
			AutoShadeQuantify( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADEPROPERTY ) {
			AutoShadeProperty( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADESTRUCTURE ) {
			AutoShadeStructure( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADESEARCH ) {
			AutoShadeSearch( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADEIDENTITY ) {
			AutoShadeIdentity( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} else if ( ModeConserved == SHADELOGODDS ) {
			AutoShadeLogOdds( pGroupArr, gCount, ShadeLevel, &m_UserVars.m_Vars, NULL );
		} 


		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				tSegHandle = tCGSeg->GetTextHandle();
				GlobalUnlock( tSegHandle );
			}
		}

		delete pGroupArr;
		delete pSegArr;
		if ( pConsensusRow != NULL ) delete pConsensusRow;

	}


	if ( m_UserVars.m_ShowManShade ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				tCGSeg->ResetShades();
			}
		}
	}

	DoMarkerLine();

	if ( m_UserVars.m_ShowComments ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				tCGSeg->ResetComments();
			}
		}
	}

	ReScoreAll(ScoreAll);

	// Flag the doc as dirty
	// SetModifiedFlag();

	UpdateAllViews(NULL);
	// 
	EndWaitCursor();
}

void
CGenedocDoc::DoMarkerLine()
{

	CGeneSegment *tCGSeg;
	GeneStor *pGS;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

	// Is consensus top?
	if ( m_UserVars.m_ConsensusLine == 0 ) {
		// Then use score line
		pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
	} else {
		// Else use top comment line ..
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
	}

	DWORD SegLength = tCGSeg->GetTextLength();

	// Do Marker Line ...
	if ( m_UserVars.m_MarkerEnable ) {

		long Start = 1;
		long Spacing = m_UserVars.m_MarkerSpacing;
		long ReplaceCounter = 1;
		long Replace = m_UserVars.m_MarkerReplace;
		int tinc;
		if ( m_UserVars.m_MarkerStart <= 0 ) tinc = -1;
		else tinc = 1;

		while ( Start != m_UserVars.m_MarkerStart ) {
			Start += tinc;
			if ( tinc == 1 && Start == m_UserVars.m_MarkerStart ) break;
			if ( (Start % Spacing) == 0 ) {
				ReplaceCounter += tinc;
			}
		}


		for ( DWORD dwCount = 0; dwCount < SegLength; ++dwCount ) {
			// Set Nothings.
			if ( Start % Spacing != 0 ) {
				pGS->CharDisplay = ' ';
				pGS++;
				Start++;
				continue;
			} else {
				pGS->CharDisplay = m_UserVars.m_MarkerSymb;
				if ( m_UserVars.m_MarkerReplace != 0 ) {
					if ( ReplaceCounter % m_UserVars.m_MarkerReplace == 0) {
						char cText[20];
						_snprintf( cText, sizeof(cText), "%ld", Start );
						int iLen = strlen ( cText );
						GeneStor* tpGS;
						if ( (DWORD)iLen > dwCount ) {
							tpGS = pGS;
							for ( int i=0; i < iLen; ++i ) {
								tpGS->CharDisplay = cText[i];
								tpGS++;
								pGS++;
								Start++;
								dwCount++;
							}
							pGS--;
							Start--;
							dwCount--;
						} else {
							tpGS = pGS - iLen + 1;
							for ( int i=0; i < iLen; ++i ) {
								tpGS->CharDisplay = cText[i];
								tpGS++;
							}
						}
					}
				}
				Start++;
				ReplaceCounter++;
				pGS++;
			}
		}

	} else {
		for ( DWORD dwCount = 0; dwCount < SegLength; ++dwCount ) {
			// Set Nothings.
			pGS->CharDisplay = ' ';
			pGS++;
		}
	}

	GlobalUnlock( tCGSeg->GetTextHandle() );
}
