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

 
#pragma optimize ("", off )


void 
CGenedocDoc::DStatScore( DWORD StartRange, DWORD EndRange, int GroupOnly ) 
{
	int i, j;

	BeginWaitCursor();
	// First loop writes comments
	GeneStor *GOut;
	GeneStor *GInner;
	unsigned long Score;
	DWORD tCount;

	GeneStor tGStor;

	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;
	
	POSITION tPos;
	

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	tPos = pGSFiller->SegDataList.GetHeadPosition();

	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	int MaxTitle = 0;
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
		if ( (pWS[i]).pText == NULL ) {
			AfxMessageBox("dstatscore:globallock:fail:2");
			delete pWS;
			return;
		}
		i++;
	}

	// only sequences now ..
	int iWithin = 0, iBetween = 0;

	for ( i = 0; i < Count; ++i ) {
		for ( j = 0; j < Count; ++j ) {

			if ( j > i ) {
				continue;
			}

			if ( j == i ) {
				continue;
			}

			if ( (pWS[i]).pCGSeg->m_DisplayGroup != 0 && (pWS[j]).pCGSeg->m_DisplayGroup != 0) {
				if ( (pWS[i]).pCGSeg->m_DisplayGroup == (pWS[j]).pCGSeg->m_DisplayGroup ) {
					iWithin++;
				} else {
					iBetween++;
				}
			} else if ( !GroupOnly ) {
				iBetween++;
			}
		}
	}


	if ( iWithin == 0 || iBetween == 0 ) {
		AfxMessageBox( "DStat Score Count == 0: Not Enough Groups Defined" );
		goto ErrorOut;
	}

	DStatObject.DeleteContents();
	DStatObject.m_ScoreCount1 = iWithin;
	DStatObject.m_ScoreArray1 = new double[iWithin];

	DStatObject.m_ScoreCount2 = iBetween;
	DStatObject.m_ScoreArray2 = new double[iBetween];

	DStatObject.m_XAxisTitle = "Scores: ";
	DStatObject.m_xXAxTPct = .45;
	DStatObject.m_RoundingFactor = 100.0;
	DStatObject.m_TSide = 1;
	DStatObject.m_NameSet1 = "Within";
	DStatObject.m_NameSet2 = "Between";

	iWithin = 0;
	iBetween = 0;

	for ( i = 0; i < Count; ++i ) {
		GOut = (pWS[i]).pText;

		for ( j = 0; j < Count; ++j ) {

			if ( j > i ) {
				continue;
			}

			if ( j == i ) {
				continue;
			}

			GInner = (pWS[j]).pText;
			Score = 0;
			
			// First Number
			// This Section for Absolute Similarity
			// Here we have Absoulte Calc's

			int OpenGp = 0, TopGap = 0;
			
			tCount = StartRange; 
			while ( tCount < EndRange ) {
			
				tGStor = GInner[tCount];	// Indexed from Loop B
				char Nuc1 = toupper(tGStor.CharGene);
				tGStor = GOut[tCount];	// Indexed from Loop A
				char Nuc2 = toupper(tGStor.CharGene);

				int gc1 = !(Nuc1 >= 'A' && Nuc1 <= 'Z');
				int gc2 = !(Nuc2 >= 'A' && Nuc2 <= 'Z');
			
				if ( !gc1 && !gc2 ) {
					Score += ScoreCurrentArray(Nuc1, Nuc2 );
					OpenGp = 0;
				} else if ( gc1 && !gc2 ) {
					Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						Score += NewGap;
						TopGap = 1;
					} else {
						if ( !TopGap ) {
							Score += NewGap;
							TopGap = 1;
						}
					}
				} else if ( !gc1 && gc2 ) {
					Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						Score += NewGap;
						TopGap = 0;
					} else {
						if ( TopGap ) {
							Score += NewGap;
							TopGap = 0;
						}
					}
				}
				tCount = tCount + 1L;
			}

			// Score is Set here
			if ( (pWS[i]).pCGSeg->m_DisplayGroup != 0 && (pWS[j]).pCGSeg->m_DisplayGroup != 0) {
				if ( (pWS[i]).pCGSeg->m_DisplayGroup == (pWS[j]).pCGSeg->m_DisplayGroup ) {
					DStatObject.m_ScoreArray1[iWithin] = Score;
					iWithin++;
				} else {
					DStatObject.m_ScoreArray2[iBetween] = Score;
					iBetween++;
				}
			} else if ( !GroupOnly ) {
				DStatObject.m_ScoreArray2[iBetween] = Score;
				iBetween++;
			}
			// Fill out DStatOb            
		}
	}

	DStatObject.MyDocDStat();

	if ( m_pDStatView == NULL ) {
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenDStatView();
	} else {
		m_pDStatView->GetParentFrame()->ActivateFrame();
		m_pDStatView->Invalidate();
	}
	
ErrorOut:
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	delete pWS;

	EndWaitCursor();
}

#pragma optimize ("", on )



void 
CGenedocDoc::DStatStat(int Opt) 
{
	int i, j;
	int GroupNum1, GroupNum2;
	CString GroupName1, GroupName2;

	// Check for Groups and Get Group Name
	if ( Opt == 2 || Opt == 3 ) {
		CGroupSelect tDlg;
		tDlg.GroupSeq = 0;
		tDlg.pDoc = this;
		if ( tDlg.DoModal() != IDOK ) return;
		if ( tDlg.GroupNum1 == 0 ) return;
		if ( tDlg.GroupNum2 == 0 ) return;
		GroupNum1 = tDlg.GroupNum1;
		GroupName1 = tDlg.GroupName1;
		GroupNum2 = tDlg.GroupNum2;
		GroupName2 = tDlg.GroupName2;
	}

	BeginWaitCursor();

	// First loop writes comments
	GeneStor *GOut;
	GeneStor *GInner;
	long Score;

	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;
	
	POSITION tPos;
	

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	int MaxTitle = 0;
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
		if ( (pWS[i]).pText == NULL ) {
			AfxMessageBox("dstatscore:globallock:fail:2");
			delete pWS;
			return;
		}
		i++;
	}

	if ( Opt == 0 || Opt == 1 ) {
		int ScoreCount = 0;
		for ( i = 0; i < Count; ++i ) {
			for ( j = i + 1; j < Count; ++j ) {
				ScoreCount++;
			}
		}

		DStatObject.DeleteContents();
		DStatObject.m_ScoreCount1 = ScoreCount;
		DStatObject.m_ScoreArray1 = new double[ScoreCount];

		DStatObject.m_RoundingFactor = 10.0;
		DStatObject.m_TSide = 2;

		DStatObject.m_NameSet1 = "All";
		DStatObject.m_NameSet2 = "";

		if ( Opt == 0 ) {
			DStatObject.m_XAxisTitle = "% Identity: ";
			DStatObject.m_xXAxTPct = .45;
		} else {
			DStatObject.m_XAxisTitle = "% Favorable Substitutions: ";
			DStatObject.m_xXAxTPct = .35;
		}

		for ( i = 0; i < Count; ++i ) {
			GOut = (pWS[i]).pText;

			for ( j = i + 1; j < Count; ++j ) {
				GInner = (pWS[j]).pText;
				if ( Opt == 0 ) {
					Score = 0;
					DWORD Total = 0;
					
					// First Number
					// This Section for Absolute Similarity
					// Here we have Absoulte Calc's
					DWORD Length = pWS[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( cInner == cOuter ) {
								Score++;
							}
						}
					}

					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray1[--ScoreCount] = Score * 100.0 / Total;
				} else {
					Score = 0;
					DWORD Total = 0;
					// Here we have Absoulte Calc's
					DWORD Length = pWS[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( (cInner >= 'A' && cInner <= 'Z') && (cOuter >= 'A' && cOuter <= 'Z') ) {
								if ( ScoreCurrentArray(cInner, cOuter) < CurrentZeroDistance ) {
									Score++;
								}
							}
						}
						
					}
					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray1[--ScoreCount] = Score * 100.0 / Total;
				}
			}
		}
	} else {
		int CountGroup1 = 0;
		int CountGroup2 = 0;
		struct WorkStruct *pWSGroup1 = new WorkStruct[Count];
		struct WorkStruct *pWSGroup2 = new WorkStruct[Count];

		for ( i = 0; i < Count; ++i ) {
			if ( (pWS[i]).pCGSeg->m_DisplayGroup == GroupNum1 ) {
				pWSGroup1[CountGroup1] = pWS[i];
				CountGroup1++;
			} else if ( GroupNum2 == 1 ) {
				pWSGroup2[CountGroup2] = pWS[i];
				CountGroup2++;
			} else if ( (pWS[i]).pCGSeg->m_DisplayGroup == (GroupNum2 - 1) ) {
				pWSGroup2[CountGroup2] = pWS[i];
				CountGroup2++;
			}
		}

		if ( CountGroup1 <= 1 || CountGroup2 <= 1 ) {
			AfxMessageBox( "Not Enough Sequences in a Group: Needs 2 or more per" );
			goto ErrorOut;
		}


		int ScoreCount1 = 0;
		int ScoreCount2 = 0;
		for ( i = 0; i < CountGroup1; ++i ) {
			for ( j = i + 1; j < CountGroup1; ++j ) {
				ScoreCount1++;
			}
		}

		for ( i = 0; i < CountGroup2; ++i ) {
			for ( j = i + 1; j < CountGroup2; ++j ) {
				ScoreCount2++;
			}
		}


		DStatObject.DeleteContents();
		DStatObject.m_ScoreCount1 = ScoreCount1;
		DStatObject.m_ScoreArray1 = new double[ScoreCount1];
		DStatObject.m_ScoreCount2 = ScoreCount2;
		DStatObject.m_ScoreArray2 = new double[ScoreCount2];


//		DStatObject.m_ScoreCount1 = 10;
//		DStatObject.m_ScoreArray1 = new double[10];
//		DStatObject.m_ScoreCount2 = 10;
//		DStatObject.m_ScoreArray2 = new double[10];

		DStatObject.m_TSide = 2;
		DStatObject.m_RoundingFactor = 10.0;
		DStatObject.m_NameSet1 = GroupName1;
		DStatObject.m_NameSet2 = GroupName2;

		if ( Opt == 2 ) {
			DStatObject.m_XAxisTitle = "% Identity: ";
			DStatObject.m_xXAxTPct = .30;
		} else {
			DStatObject.m_XAxisTitle = "% Favorable Substitutions: ";
			DStatObject.m_xXAxTPct = .20;
		}

//		goto tdata;

		for ( i = 0; i < CountGroup1; ++i ) {
			GOut = (pWSGroup1[i]).pText;

			for ( j = i + 1; j < CountGroup1; ++j ) {
				GInner = (pWSGroup1[j]).pText;
				if ( Opt == 2 ) {
					Score = 0;
					DWORD Total = 0;
					
					// First Number
					// This Section for Absolute Similarity
					// Here we have Absoulte Calc's
					DWORD Length = pWSGroup1[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( cInner == cOuter ) {
								Score++;
							}
						}
					}

					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray1[--ScoreCount1] = Score * 100.0 / Total;
				} else {
					Score = 0;
					DWORD Total = 0;
					// Here we have Absoulte Calc's
					DWORD Length = pWSGroup1[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( (cInner >= 'A' && cInner <= 'Z') && (cOuter >= 'A' && cOuter <= 'Z') ) {
								if ( ScoreCurrentArray(cInner, cOuter) < CurrentZeroDistance ) {
									Score++;
								}
							}
						}
						
					}
					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray1[--ScoreCount1] = Score * 100.0 / Total;
				}
			}
		}

		// Non Groups
		for ( i = 0; i < CountGroup2; ++i ) {
			GOut = (pWSGroup2[i]).pText;

			for ( j = i + 1; j < CountGroup2; ++j ) {
				GInner = (pWSGroup2[j]).pText;
				if ( Opt == 2 ) {
					Score = 0;
					DWORD Total = 0;
					
					// First Number
					// This Section for Absolute Similarity
					// Here we have Absoulte Calc's
					DWORD Length = pWSGroup2[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( cInner == cOuter ) {
								Score++;
							}
						}
					}

					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray2[--ScoreCount2] = Score * 100.0 / Total;
				} else {
					Score = 0;
					DWORD Total = 0;
					// Here we have Absoulte Calc's
					DWORD Length = pWSGroup2[j].pCGSeg->GetTextLength();
					while (Length--) {
						char cInner = toupper(GInner[Length].CharGene);
						char cOuter = toupper(GOut[Length].CharGene);
						if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
							Total++;
							if ( (cInner >= 'A' && cInner <= 'Z') && (cOuter >= 'A' && cOuter <= 'Z') ) {
								if ( ScoreCurrentArray(cInner, cOuter) < CurrentZeroDistance ) {
									Score++;
								}
							}
						}
						
					}
					// Here we have percentage Calc's
					// Score = (Score * 100L) / (Total);
					DStatObject.m_ScoreArray2[--ScoreCount2] = Score * 100.0 / Total;
				}
			}
		}

/*
tdata:
		DStatObject.m_ScoreArray2[0] = 50;
		DStatObject.m_ScoreArray2[1] = 52;
		DStatObject.m_ScoreArray2[2] = 54;
		DStatObject.m_ScoreArray2[3] = 56;
		DStatObject.m_ScoreArray2[4] = 58;
		DStatObject.m_ScoreArray2[5] = 60;
		DStatObject.m_ScoreArray2[6] = 62;
		DStatObject.m_ScoreArray2[7] = 64;
		DStatObject.m_ScoreArray2[8] = 66;
		DStatObject.m_ScoreArray2[9] = 68;
		
		DStatObject.m_ScoreArray1[0] = 69;
		DStatObject.m_ScoreArray1[1] = 71;
		DStatObject.m_ScoreArray1[2] = 73;
		DStatObject.m_ScoreArray1[3] = 75;
		DStatObject.m_ScoreArray1[4] = 77;
		DStatObject.m_ScoreArray1[5] = 79;
		DStatObject.m_ScoreArray1[6] = 81;
		DStatObject.m_ScoreArray1[7] = 83;
		DStatObject.m_ScoreArray1[8] = 85;
		DStatObject.m_ScoreArray1[9] = 87;
*/
		delete pWSGroup1;
		delete pWSGroup2;

	}
	

	DStatObject.MyDocDStat();

	if ( m_pDStatView == NULL ) {
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenDStatView();
	} else {
		m_pDStatView->GetParentFrame()->ActivateFrame();
		m_pDStatView->Invalidate();
	}

ErrorOut:
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	delete pWS;

	EndWaitCursor();

}
