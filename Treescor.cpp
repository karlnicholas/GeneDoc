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
CGenedocDoc::CallSetObj(CObject *p)
{
	ASSERT( p->IsKindOf( RUNTIME_CLASS(CPhyloNode) ) );
	CPhyloNode *pPN = (CPhyloNode *)p;

	m_TreeScoreList.AddTail( pPN );
}


BOOL 
CGenedocDoc::DocPeekMessage(HWND hCanDlg)
{
	MSG msg;

	while (!m_CancelFlag &&
			::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
			return FALSE;               // Bag out if WM_QUIT received
	}

    // let MFC do its idle processing
    LONG lIdle = 0;
    while ( AfxGetApp()->OnIdle(lIdle++ ) )
        ;  
    // Perform some background processing here 
    // using another call to OnIdle
	return !m_CancelFlag;
}

int 
CGenedocDoc::TreeScore( DWORD *nStartRange, DWORD *nEndRange, 
unsigned long *Score, int RowCount, ShadeSegStc *pSegArr, CString& PathName )
{

	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;
	DWORD tCount;
	unsigned long maxscore;
	unsigned long score;

	int TSWLength, i;
	int RetVal = 1;
		
	int tGapChar;
	
	if ( m_UserVars.m_GapInd == 0 ) {
		tGapChar = '-';
		m_GapChar = '-';
	} else {
		tGapChar = '.';
		m_GapChar = '.';
	}


	*Score = 0;
	
	if ( m_pPGBase == NULL ) {
		AfxMessageBox("No Tree to Score Against!" );
		return 0;
	}

	if ( !m_pPGBase->CheckCounts(1) ) {
		AfxMessageBox("Tree Not Completed!");
		return 0;
	}

//	CString PathName = ConvertPathname ( ".tsd" );


	if ( m_TreeDebugOutput ) {
		m_DebugFile = fopen( (const char *)PathName, "wb" );
		if ( m_DebugFile == NULL ) {
			AfxMessageBox ( "Score Info File Open Fails" );
			return 0;
		}
	}
	
	for ( i = 0; i < RowCount; ++i ) {
		
		pSegArr[i].pCGSeg->m_pMyGeneStor = pSegArr[i].pGeneStor;
		
	}
	

	m_TreeScoreList.RemoveAll();
	// Start Tree score setup
	m_MaxDepth = 0;
	m_CallSwitch = CALLSETMAX;
	m_pPGBase->CallDocFromSeq(this);

	m_CallSwitch = CALLSETOBJ;
    
    int tMaxDepth = m_MaxDepth;
	while ( tMaxDepth >= 0 ) {
		m_pPGBase->CallDocFromDepth(this, tMaxDepth);
		tMaxDepth--;
	}
	
	m_MaxDepth++;
	

	TSWLength = m_TreeScoreList.GetCount();
	
	TreeScoreWork *TSArray = new TreeScoreWork[TSWLength];
	
	int InitPrevFlag = 1;
	// End new tree score setup.
	// ModeLess DialogBox

	m_CancelFlag = 0;
	m_ScoreWaitCursor = 1;


	AfxGetMainWnd()->EnableWindow(FALSE);   // Disable main window
	
	CScoreCancelDialog CanDlg;
	CanDlg.m_CancelFlag = &m_CancelFlag;
	CanDlg.m_ScoreWaitCursor = &m_ScoreWaitCursor;

	CanDlg.MyCreate();

	{	
	char ibuff[33];
	CanDlg.m_ShowStatus.Empty();
	CanDlg.m_ShowStatus += "Columns = ";
	CanDlg.m_ShowStatus += _ltoa( EndRange - StartRange + 1, ibuff, 10 );
	CanDlg.m_ShowStatus += ", Trees = 0K";
	CanDlg.UpdateData(FALSE);
	}

	tCount = StartRange; 

	unsigned long totalloopcount = 0;

	while ( tCount <= EndRange ) {

		//ok, build union first 
		// Take assignment from root and propigate it
		// level will have a first time through flag, will grab assigned parents
		// 
		// take a path of all lefts first time through, score it, save it high score

		int TSIndex= 0;
		unsigned long loopcount = 0;
	

		POSITION tPos = m_TreeScoreList.GetHeadPosition();
		while ( tPos != NULL ) {
			CPhyloNode *pPN = (CPhyloNode*)m_TreeScoreList.GetNext( tPos );
			
			TSArray[TSIndex].m_pPN = pPN;
			pPN->m_AverageCost = 0;

			CString Ancest[2];

			CPhyloGenBase *pPGBase = (CPhyloGenBase*)pPN->m_PhyloList.GetHead();
			if ( pPGBase->IsKindOf(RUNTIME_CLASS(CPhyloNode))) {
				TSArray[TSIndex].DescendentTypeL = 1;
				TSArray[TSIndex].DescendentTSWL = (TreeScoreWork *)pPGBase->m_pTSW;
				int LenStr = TSArray[TSIndex].DescendentTSWL->UnionStringLength;
				for ( i = 0; i < LenStr; ++i ) {
					Ancest[0] += "" + TSArray[TSIndex].DescendentTSWL->UnionString[i];
				}
			} else {
				TSArray[TSIndex].DescendentTypeL = 0;
				TSArray[TSIndex].DescendentCharL = toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				Ancest[0] = "" + toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				if ( InitPrevFlag ) {
					pPGBase->m_pPrevResidue = 0;
				} else {
					pPGBase->m_pPrevResidue = pPGBase->m_cAncestry;
				}
				pPGBase->m_cAncestry = toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				pPGBase->m_AverageCost = 0;
			}

			pPGBase = (CPhyloGenBase*)pPN->m_PhyloList.GetTail();
			if ( pPGBase->IsKindOf(RUNTIME_CLASS(CPhyloNode))) {
				TSArray[TSIndex].DescendentTypeR = 1;
				TSArray[TSIndex].DescendentTSWR = (TreeScoreWork *)pPGBase->m_pTSW;
				int LenStr = TSArray[TSIndex].DescendentTSWR->UnionStringLength;
				for ( i = 0; i < LenStr; ++i ) {
					Ancest[1] += "" + TSArray[TSIndex].DescendentTSWR->UnionString[i];
				}
			} else {
				TSArray[TSIndex].DescendentTypeR = 0;
				TSArray[TSIndex].DescendentCharR = toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				Ancest[1] = "" + toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				if ( InitPrevFlag ) {
					pPGBase->m_pPrevResidue = 0;
				} else {
					pPGBase->m_pPrevResidue = pPGBase->m_cAncestry;
				}
				pPGBase->m_cAncestry = toupper(((CPhyloSeq *)pPGBase)->GetGeneStor()[tCount].CharGene);
				pPGBase->m_AverageCost = 0;
			}

			
			// Make union of string, removing duplicates	
			int Length = Ancest[1].GetLength();
			
			for ( i=0; i < Length; ++i ) {
				if ( Ancest[0].Find(Ancest[1].GetAt(i)) == -1 ) {
					Ancest[0] += Ancest[1].GetAt(i);
				}
			}

			Length = Ancest[0].GetLength();
			TSArray[TSIndex].UnionStringLength = Length;
			
			for ( i = 0; i < Length; ++i ) {
				TSArray[TSIndex].UnionString[i] = Ancest[0][i];
			}
			
			TSArray[TSIndex].UnionParentAppended = 0;
			TSArray[TSIndex].m_PrevBestResidue = 0;

			TSArray[TSIndex].m_ScoreIndex = Length - 1;
//			TSArray[TSIndex].m_ScoreCarry = 1;

			pPN->m_pTSW = &TSArray[TSIndex];
			
			TSIndex++;

		}

		InitPrevFlag = 0;

/*8*********************************************************/

		maxscore = ULONG_MAX;

		int PrevCarry;
		int clearcarry = 1;

        do {
        
			int firstflag = 1;
			int NumbTreeTest = 0;
			
			unsigned long TotalScore = 0;
		
			for ( int count= 0; count < TSWLength; ++count ) {
				
				TreeScoreWork *pTSWTempR;
				TreeScoreWork *pTSWTempL;

				TreeScoreWork *pTSW = &TSArray[count];
				
				if ( firstflag ) {
					firstflag = 0;
					PrevCarry = 1;
				}

				if ( PrevCarry ) {

					pTSW->m_ScoreIndex++;

					if ( pTSW->m_ScoreIndex == pTSW->UnionStringLength ) {
						pTSW->m_ScoreIndex = 0;
						pTSW->m_ScoreCarry = 1;
					}
					
					pTSW->m_cAncestry = pTSW->UnionString[pTSW->m_ScoreIndex];
			
					if ( pTSW->DescendentTypeL == 1 ) {
						// Write over old char
						// Check for duplicates ..
						pTSWTempL = pTSW->DescendentTSWL;
						if ( pTSWTempL->UnionParentAppended ) pTSWTempL->UnionStringLength--;
						int PChar = pTSW->m_cAncestry;
						int DSLength = pTSWTempL->UnionStringLength;
						int *pDChar = pTSWTempL->UnionString;
						for ( i = 0; i < DSLength; ++i ) {
							if ( *pDChar++ == PChar ) break;
						}
						if ( i == DSLength ) {
							pTSWTempL->UnionString[DSLength] = PChar;
							pTSWTempL->UnionStringLength++;
							pTSWTempL->UnionParentAppended = 1;
						} else {
							pTSWTempL->UnionParentAppended = 0;
						}						
					}

					if ( pTSW->DescendentTypeR == 1 ) {
						// Write over old char
						// Check for duplicates ..
						pTSWTempR = pTSW->DescendentTSWR;
						if ( pTSWTempR->UnionParentAppended ) pTSWTempR->UnionStringLength--;
						int PChar = pTSW->m_cAncestry;
						int DSLength = pTSWTempR->UnionStringLength;
						int *pDChar = pTSWTempR->UnionString;
						for ( i = 0; i < DSLength; ++i ) {
							if ( *pDChar++ == PChar ) break;
						}
						if ( i == DSLength ) {
							pTSWTempR->UnionString[DSLength] = PChar;
							pTSWTempR->UnionStringLength++;
							pTSWTempR->UnionParentAppended = 1;
						} else {
							pTSWTempR->UnionParentAppended = 0;
						}						
					}

				}
				
				if ( m_NumbTreeFlag && NumbTreeTest ) {
					goto NumbTreeJump;
				}

				int DescendentsL;
				int DescendentsR;
				int DescentAssignedDescentL;
				int DescentAssignedDescentR;

				if ( pTSW->DescendentTypeL == 1 ) {
					DescendentsL = pTSW->DescendentTSWL->m_cAncestry;
					DescentAssignedDescentL = pTSW->DescendentTSWL->m_AssignedDescent;
				} else {
					DescendentsL = pTSW->DescendentCharL;
					DescentAssignedDescentL = 1;
				}
				if ( pTSW->DescendentTypeR == 1 ) {
					DescendentsR = pTSW->DescendentTSWR->m_cAncestry;
					DescentAssignedDescentR = pTSW->DescendentTSWR->m_AssignedDescent;
				} else {
					DescendentsR = pTSW->DescendentCharR;
					DescentAssignedDescentR = 1;
				}
			
				
				pTSW->m_AssignedDescent = 0;
				
				if ( pTSW->m_cAncestry == DescendentsL && DescentAssignedDescentL == 1 ) {
					pTSW->m_AssignedDescent = 1;
				} else if ( pTSW->m_cAncestry == DescendentsR && DescentAssignedDescentR == 1 ) {
					pTSW->m_AssignedDescent = 1;
				}
				
				if ( !pTSW->m_AssignedDescent && m_NumbTreeFlag ) {
					NumbTreeTest = 1;
				}

				
				if ( (pTSW->m_cAncestry >= 'A' && pTSW->m_cAncestry <= 'Z') && (DescendentsL >= 'A' && DescendentsL <= 'Z') ) {
					score = ScoreCurrentArray( pTSW->m_cAncestry, DescendentsL );
				} else {
					score = GapLen;
					if ( (pTSW->m_PrevBestResidue >= 'A' && pTSW->m_PrevBestResidue <= 'Z') ) {
						score += NewGap;
					}
				}
				
				if ( (pTSW->m_cAncestry >= 'A' && pTSW->m_cAncestry <= 'Z') && (DescendentsR >= 'A' && DescendentsR <= 'Z') ) {
					score += ScoreCurrentArray( pTSW->m_cAncestry, DescendentsR );
				} else {
					score += GapLen;
					if ( (pTSW->m_PrevBestResidue >= 'A' && pTSW->m_PrevBestResidue <= 'Z') ) {
						score += NewGap;
					}
				}
				
//				pTSW->m_SaveScore = score;

				TotalScore += score;

NumbTreeJump:
				PrevCarry = pTSW->m_ScoreCarry;
				
				pTSW->m_ScoreCarry = 0;

			}

			if ( m_NumbTreeFlag ) {
				if ( NumbTreeTest ) {
					goto SkipMaxScore;
				}
			}

			if ( TotalScore < maxscore ) {
				// Test the new score for a valid path

				
				if ( TreeTestGood(TSArray, TSWLength) ) {

					TreeSaveBest *pTSBTemp;

					if ( m_TreeDebugOutput && loopcount ) {
						// Clear best list if any
						while ( !m_SaveBestList.IsEmpty() ) delete (TreeSaveBest **)m_SaveBestList.RemoveHead();
		
						pTSBTemp = new TreeSaveBest[TSWLength];
					}
	
					for ( i = 0; i < TSWLength; ++i ) {
						TreeScoreWork *pTSW = &TSArray[i];
						pTSW->m_SaveBestResidue = pTSW->m_cAncestry;
						if ( m_TreeDebugOutput && loopcount ) {
							pTSBTemp[i].m_cAncestry = pTSW->m_cAncestry;
							pTSBTemp[i].m_PrevBestResidue = pTSW->m_PrevBestResidue;
						}
					}
					// save this score!
	
					maxscore = TotalScore;
					m_DebugScore = maxscore;
					
					if ( m_TreeDebugOutput && loopcount ) {
						m_SaveBestList.AddTail(pTSBTemp);
					}
	
				}

			} else if ( (maxscore == TotalScore) && m_TreeDebugOutput ) {

				if ( TreeTestGood(TSArray, TSWLength) ) {
					
					TreeSaveBest *pTSBTemp = new TreeSaveBest[TSWLength];

					for ( i = 0; i < TSWLength; ++i ) {
						TreeScoreWork *pTSW = &TSArray[i];
						pTSBTemp[i].m_cAncestry = pTSW->m_cAncestry;
						pTSBTemp[i].m_PrevBestResidue = pTSW->m_PrevBestResidue;
					}

					m_SaveBestList.AddTail(pTSBTemp);
				}

			}

SkipMaxScore:

//			if ( m_CancelFlag ) goto AbortExit;	// memory leak
			
			loopcount++;
			totalloopcount++;

			if ( clearcarry ) {
				clearcarry = 0;
				PrevCarry = 0;
			}


			if ( loopcount % 250000L == 0L ) {
				if ( !DocPeekMessage(CanDlg.m_hWnd) ) {
					while ( !m_SaveBestList.IsEmpty() ) {
						TreeSaveBest *pTSBTemp = (TreeSaveBest *)m_SaveBestList.RemoveHead();
						delete pTSBTemp;
					}
					RetVal = 0;
					goto AbortExit;
				}
			}
			if ( totalloopcount % 250000L == 0 ) {
				char ibuff[33];
				CanDlg.m_ShowStatus.Empty();
				CanDlg.m_ShowStatus += "Columns = ";
				CanDlg.m_ShowStatus += _ltoa( EndRange - tCount + 1, ibuff, 10 );
				CanDlg.m_ShowStatus += ", Trees = ";
				CanDlg.m_ShowStatus += _ltoa( totalloopcount / 1000, ibuff, 10 );
				CanDlg.m_ShowStatus += 'K';
				CanDlg.UpdateData(FALSE);
			}


        } while ( !PrevCarry );


		if ( m_TreeDebugOutput ) {

			m_CostDiv = 0;
			m_ScAve = 1;

			while ( !m_SaveBestList.IsEmpty() ) {
				m_CostDiv++;
				TreeSaveBest *pTSBTemp = (TreeSaveBest *)m_SaveBestList.RemoveHead();
				for ( i = 0; i < TSWLength; ++i ) {
					TreeScoreWork *pTSW = &TSArray[i];
					pTSW->m_cAncestry = pTSBTemp[i].m_cAncestry;
					pTSW->m_PrevBestResidue = pTSBTemp[i].m_PrevBestResidue;
				}
				
				OnDrawDebugTree();
				
				delete pTSBTemp;
			}

			if ( m_CostDiv > 1 ) {

				fprintf(m_DebugFile, "\r\n========Summary Tree of Average Costs========\r\n" );

				for ( i = 0; i < TSWLength; ++i ) {
					TreeScoreWork *pTSW = &TSArray[i];
					pTSW->m_cAncestry = ' ';
				}
				// Flag to do an average
				m_ScAve = 0;

				OnDrawDebugTree();
			}
	
			fprintf(m_DebugFile, "***************Number of Trees Tested = %ld\r\n\r\n", loopcount );
		}
			
		for ( i = 0; i < TSWLength; ++i ) {
			TreeScoreWork *pTSW = &TSArray[i];
			pTSW->m_PrevBestResidue = pTSW->m_SaveBestResidue;
		}
		
		*Score += maxscore;
		
		tCount = tCount + 1L;

		char ibuff[33];
		CanDlg.m_ShowStatus.Empty();
		CanDlg.m_ShowStatus += "Columns = ";
		CanDlg.m_ShowStatus += _ltoa( EndRange - tCount + 1, ibuff, 10 );
		CanDlg.m_ShowStatus += ", Trees = ";
		CanDlg.m_ShowStatus += _ltoa( totalloopcount / 1000, ibuff, 10 );
		CanDlg.m_ShowStatus += 'K';
		CanDlg.UpdateData(FALSE);

		if ( !DocPeekMessage(CanDlg.m_hWnd) ) {
			RetVal = 0;
			goto AbortExit;
		}


	}

AbortExit:

	AfxGetMainWnd()->EnableWindow(TRUE);    // Enable main window

	CanDlg.DestroyWindow();

	delete TSArray;

	if ( m_TreeDebugOutput ) {
		fclose(m_DebugFile);
	}

	m_TreeScoreList.RemoveAll();

	return RetVal;
}


int
CGenedocDoc::TreeTestGood( TreeScoreWork *TSArray, int TSWLength )
{	
	int TreeGood = 1;
	
	for ( int i = 0; i < TSWLength; ++i ) {
		TreeScoreWork *pTSW = &TSArray[i];
		if ( pTSW->m_AssignedDescent == 0 ) {
			TreeGood = 0;
			CPhyloNode *pPN2 = pTSW->m_pPN;
			while ( pPN2->m_pPGParent != NULL ) {
				if ( ((TreeScoreWork*)((CPhyloNode *)pPN2->m_pPGParent)->m_pTSW)->m_cAncestry != ((TreeScoreWork*)((CPhyloNode *)pPN2)->m_pTSW)->m_cAncestry ) {
					return 0;
				}
				if ( ((TreeScoreWork*)((CPhyloNode *)pPN2->m_pPGParent)->m_pTSW)->m_AssignedDescent ) {
					TreeGood = 1;
					// Path is good
					break;
				}
				pPN2 = (CPhyloNode *)pPN2->m_pPGParent;
			}
		}
	}
	
	return TreeGood;
}
	


#define DDCELLW 4
#define DDCELLW12 2
#define DDCELLV 1


void 
CGenedocDoc::CallDrawDebug(CObject *p)
{
	CString ResultString;
	
	ASSERT( p->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) );
	CPhyloSeq *pPS = (CPhyloSeq *)p;

	CPhyloGenBase *pPGB = pPS;
	CPhyloGenBase *pPNPLast = pPGB;
	int tDepth = m_MaxDepth;
	int DrawCmd;  
	int Depth2;
	
	
	int BuffSize = ((tDepth -1) * DDCELLW * 2) + 30;

	char * pResString = ResultString.GetBuffer( BuffSize + 1 );
	pResString[BuffSize] = 0;
	
	for ( int i = 0; i < BuffSize; ++i ) {
		pResString[i] = ' ';
	}
	
	ResultString.ReleaseBuffer(BuffSize + 1);

	while ( pPGB != NULL ) {
		Depth2 = pPGB->m_Depth * DDCELLW * 2;

		if ( pPGB->IsKindOf( RUNTIME_CLASS(CPhyloSeq) ) ) {
			if ( pPGB->m_Depth > 1 ) {
				while ( tDepth > pPGB->m_Depth ) {
					if ( tDepth == m_MaxDepth ) {
						DrawCmd = CPhyloGenBase::DLABEL;
					} else if ( tDepth >= pPGB->m_Depth ) {
						DrawCmd = CPhyloGenBase::DEXTEND;
					}
					DoDrawDebugCmd( ResultString, DrawCmd, ((tDepth -1) * DDCELLW * 2 ), pPGB );
					tDepth--;
				}

				pPNPLast = pPGB;
				pPGB = pPGB->m_pPGParent;
				
				continue;
				
			}
		}

		DrawCmd = pPGB->DetermineDraw( pPNPLast );
			
		DoDrawDebugCmd( ResultString, DrawCmd, Depth2, pPGB );
		
		pPNPLast = pPGB;
		pPGB = pPGB->m_pPGParent;
		
	}
	
    fprintf ( m_DebugFile, "%s\r\n", (const char *)ResultString );

}

void
CGenedocDoc::DrawDebugNodeBox(CString &ResString, int StartX, CPhyloGenBase *pPGB ) 
{
	CPhyloNode *pPN = (CPhyloNode *)pPGB;
	char Buff[7];
	unsigned pscore;


	if ( pPGB->m_pPGParent == NULL ) {
	
		_snprintf( Buff, 6, "%4ld %c", 
			m_DebugScore, 
			(char)((TreeScoreWork *)pPN->m_pTSW)->m_cAncestry
		);

	} else {

		if ( m_ScAve ) {
			char Char1, Char2;
							  
			Char1 = (char)((TreeScoreWork *)pPGB->m_pTSW)->m_cAncestry;
			Char2 = ((TreeScoreWork *)pPGB->m_pPGParent->m_pTSW)->m_cAncestry;
			
			if ( Char1 != m_GapChar && Char2 != m_GapChar ) {
				pscore = ScoreCurrentArray( Char1, Char2 );
			} else {
				pscore = GapLen;
				if ( ((TreeScoreWork *)pPGB->m_pTSW)->m_PrevBestResidue != m_GapChar ) {
					pscore += NewGap;
				}
			}
					
			pPN->m_AverageCost += pscore;
		} else {
			pscore = (unsigned)((double)pPGB->m_AverageCost / (double)m_CostDiv + 0.5);
		}

		_snprintf( Buff, 6, "%2d %c -", 
			pscore, 
			(char)((TreeScoreWork *)pPN->m_pTSW)->m_cAncestry
		);


	}



/*		pPN->m_Number, 
		pPN->m_cAncestry, 
		pPN->m_AssignedDescent, 
		pPN->m_SaveScore
*/

	Buff[6] = 0;
	
	for ( int i=0; i < 6; ++i ) {
		ResString.SetAt( StartX + i, Buff[i] );
	}
}

void
CGenedocDoc::DoDrawDebugCmd ( CString& ResString, int DrawCmd, int Depth2, CPhyloGenBase* pPGB )
{
	char NameBuff[20];
	int i, length;
	unsigned pscore;
	char Char1, Char2;

	switch ( DrawCmd ) {    
	case CPhyloGenBase::DLABEL:

		if ( m_ScAve ) {
			Char1 = (char)pPGB->m_cAncestry;
			Char2 = ((TreeScoreWork *)pPGB->m_pPGParent->m_pTSW)->m_cAncestry;

			if ( Char1 != m_GapChar && Char2 != m_GapChar ) {
				pscore = ScoreCurrentArray( Char1, Char2 );
			} else {
				pscore = GapLen;
				if ( pPGB->m_pPrevResidue != m_GapChar ) {
					pscore += NewGap;
				}
			}
			pPGB->m_AverageCost += pscore;
		} else {
			pscore = (unsigned)((double)pPGB->m_AverageCost / (double)m_CostDiv + 0.5);
		}
		_snprintf(NameBuff, 
			20, " %2d %c *%s", 
			pscore, 
			(char)pPGB->m_cAncestry, 
			(const char *)((CPhyloSeq *)pPGB)->GetName() 
		);
		NameBuff[19] = 0;


		length = strlen ( NameBuff );
		for ( i=0; i < length; ++i ) {
			ResString.SetAt( Depth2 + DDCELLW + i, NameBuff[i] );
		}
		
//		pDC->TextOut ( m_CharWidth * (Depth2 + 1), DrawY, NameBuff, strlen(NameBuff) );
			
		for ( i=0; i < DDCELLW; ++i ) {
			ResString.SetAt( Depth2 + i, '-' );
		}
//		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
//		pDC->LineTo( (m_CharWidth * (Depth2 + 1)), DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODESU:
		// Draw Node Indicator

		DrawDebugNodeBox( ResString, Depth2 + DDCELLW12, pPGB );

		// Draw a line through the middle, second spot
		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + i, '-' );
		}

//		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODESL:
		
		ResString.SetAt( Depth2 + DDCELLW + DDCELLV, ',' );
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + DDCELLW + DDCELLW12 + i, '-' );
		}
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * (Depth2 + 1) + m_CharWidth, DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODET:

		ResString.SetAt( Depth2 + DDCELLW + DDCELLV, '|' );
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
//		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + DDCELLW + DDCELLW12 + i, '-' );
		}
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * (Depth2 + 2), DrawY + HalfHeight );


		break;
	case CPhyloGenBase::DNODEM:
		ResString.SetAt( Depth2 + DDCELLW + DDCELLV, '|' );
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
//		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		break;
	case CPhyloGenBase::DNODEEU:

		ResString.SetAt( Depth2 + DDCELLW + DDCELLV, '`' );

//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
//		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );

		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + DDCELLW + DDCELLW12 + i, '-' );
		}
//		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * (Depth2 + 2), DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODEEL:

		DrawDebugNodeBox(ResString, Depth2 + DDCELLW12, pPGB );

		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + i, '-' );
		}
		// Draw a line through the middle, second spot
//		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );
		break;
	case CPhyloGenBase::DNOTHING:
		break;
	case CPhyloGenBase::DEXTEND:
		// Extension line
//		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * (Depth2 + 3), DrawY + HalfHeight );
		for ( i=0; i < DDCELLW * 3; ++i ) {
			ResString.SetAt( Depth2 + i, '-' );
		}
		break;
	case CPhyloGenBase::DNODER:		// Root Node
		// Extension line
		DrawDebugNodeBox(ResString, Depth2 + DDCELLW12, pPGB );

		for ( i=0; i < DDCELLW12; ++i ) {
			ResString.SetAt( Depth2 + i, '-' );
		}
		// Draw a line through the middle, second spot
//		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
//		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );
		

		break;
			
	}
}

void 
CGenedocDoc::OnDrawDebugTree()
{

	m_CallSwitch = CALLDRAWDEBUG;

	m_pPGBase->CallDocFromSeq(this);

	fprintf(m_DebugFile, "\r\n" );
}
