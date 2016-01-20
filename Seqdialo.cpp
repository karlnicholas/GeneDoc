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
// seqdialo.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqDialog dialog


CSeqDialog::CSeqDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSeqDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeqDialog)
	//}}AFX_DATA_INIT
}


void CSeqDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeqDialog)
	DDX_Control(pDX, IDC_COUNTSEL, m_CountSel);
	DDX_Control(pDX, IDC_SEQCOUNT, m_strSeqCount);
	DDX_Control(pDX, IDC_LIST1, m_SeqList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeqDialog, CDialog)
	//{{AFX_MSG_MAP(CSeqDialog)
	ON_BN_CLICKED(IDC_SEQDELETE, OnSeqdelete)
	ON_BN_CLICKED(IDC_SEQDETAILS, OnSeqdetails)
	ON_BN_CLICKED(IDC_SEQIMPORT, OnSeqimport)
	ON_BN_CLICKED(IDC_SEQMOVEDOWN, OnSeqmovedown)
	ON_BN_CLICKED(IDC_SEQMOVEUP, OnSeqmoveup)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_MOVEBOTT, OnMovebott)
	ON_BN_CLICKED(IDC_MOVETOP, OnMovetop)
	ON_BN_CLICKED(IDC_COMPLIMENT, OnCompliment)
	ON_BN_CLICKED(IDC_REVERSE, OnReverse)
	ON_BN_CLICKED(IDC_SEQEXPORT, OnSeqexport)
	ON_BN_CLICKED(IDC_DUPLICATE, OnDuplicate)
	ON_BN_CLICKED(IDC_WRITESCR, OnWritescr)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_SORTNAME, OnSortname)
	ON_BN_CLICKED(IDC_SAVESORT, OnSavesort)
	ON_BN_CLICKED(IDC_LOADSORT, OnLoadsort)
	ON_BN_CLICKED(IDC_SORTDESC, OnSortdesc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSeqDialog message handlers

BOOL CSeqDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: add draw code for native data here
	m_Modify = 0;

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	int Count = 0;
	if ( pGSFiller != NULL ) {

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
	
			// CListBox
			int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
			m_SeqList.SetItemDataPtr(aloc, tCGSeg );
			Count++;
	
		}
	}
	char scount[256];
	wsprintf(scount, "%d Seq", Count );
	m_strSeqCount.SetWindowText(scount);
	
	if ( m_SeqList.GetCount() ) {
		m_SeqList.SetSel(0);
	}

	CenterWindow();
	
	return TRUE;
}

void CSeqDialog::OnSeqdelete() 
{
	// TODO: Add your control notification handler code here

//	int SeqSel = m_SeqList.GetCurSel();
//	if ( SeqSel == LB_ERR ) return;

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;


	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	if ( AfxMessageBox ( "Are you Sure you want to delete these Sequences!!!", MB_OKCANCEL ) != IDOK ) {
		return;
	}

	int Count = m_SeqList.GetCount();

	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		CString tStr;

		m_SeqList.GetText ( SeqSel, tStr );

		m_SeqList.DeleteString ( SeqSel );
		Count--;
/*
		if ( m_SeqList.GetCount() != SeqSel ) {
			m_SeqList.SetCurSel ( SeqSel );
		} else {
			m_SeqList.SetCurSel ( SeqSel - 1);
		}
*/
		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
		pGSFiller->SegDataList.RemoveAt (tPos);

		// Remove from Groups List.

		// Is it in a group already?
		if ( tCGSeg->m_DisplayGroup != 0 ) {
			int GrpNum = 0;
			CDisplayVars *DisplayVars = NULL;
			POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
				GrpNum++;
				if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
			}

			tCGSeg->m_DisplayGroup = 0;

			CPtrList *pDVGL;
			if ( DisplayVars != NULL ) pDVGL = DisplayVars->GetGroupList();

			POSITION oPos = pDVGL->Find( tCGSeg );
						
			if ( oPos != NULL ) pDVGL->RemoveAt( oPos );
						
		}


		char scount[256];
		wsprintf(scount, "%d Seq", Count );
		m_strSeqCount.SetWindowText(scount);
		// CStatic

		// Remove from tree, remove node if not root

		m_pPGSeq = NULL;

		pDoc->m_pPGBase->CallSDFromNamedSeq ( this, tCGSeg->GetTitle() );

		if ( m_pPGSeq != NULL ) {

			CPhyloNode *pPN = (CPhyloNode*)m_pPGSeq->m_pPGParent;

			CPhyloNode *pPNUlt = (CPhyloNode *)pPN->m_pPGParent;
			
			if ( pPNUlt != NULL ) {
				
				POSITION Pos = pPNUlt->m_PhyloList.Find( pPN );

				CPhyloGenBase *pPB2;
				while ( (pPB2 = (CPhyloGenBase*)pPN->m_PhyloList.RemoveHead()) == m_pPGSeq ) {
					delete pPB2;
				}
				

				pPB2->m_pPGParent = pPNUlt;
				pPB2->m_FirstSelection = 0;

				pPNUlt->m_PhyloList.SetAt( Pos, pPB2 );

				delete pPN;

			} else {

				POSITION Pos = pPN->m_PhyloList.Find( m_pPGSeq );
				
				pPN->m_PhyloList.RemoveAt(Pos);

				delete m_pPGSeq;

			}

			pDoc->SetDepths();
			pDoc->WriteString();
		}

		delete tCGSeg;

		pDoc->SetModifiedFlag();

		// Test for single Entry in root node. Special case.
		// If true, delete it.
		if ( pDoc->m_pPGBase->m_PhyloList.GetCount() == 1 ) {

			if ( pDoc->m_pPGBase != NULL ) {
				CPhyloNode *pPNDoc = pDoc->m_pPGBase;
				CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetHead();
				if ( pPGB->IsKindOf( RUNTIME_CLASS(CPhyloNode) ) ) {
					// Clear out old one
					pPNDoc->m_PhyloList.RemoveHead();

					CPhyloNode *pPN = (CPhyloNode *)pPGB;

					CPhyloGenBase *pPB2 = (CPhyloGenBase*)pPN->m_PhyloList.RemoveHead();
					pPB2->m_pPGParent = pPNDoc;
					pPB2->m_FirstSelection = 0;
					pPNDoc->m_PhyloList.AddHead( pPB2 );

					pPB2 = (CPhyloGenBase*)pPN->m_PhyloList.RemoveHead();
					pPB2->m_pPGParent = pPNDoc;
					pPB2->m_FirstSelection = 0;
					pPNDoc->m_PhyloList.AddTail( pPB2 );
							
					delete pPN;

					pDoc->SetDepths();
					pDoc->WriteString();

				}
			}
		}

	}

	if ( pDoc->pGSFiller->SegDataList.GetCount() == 3 ) {
		delete pDoc->pGSFiller;
		pDoc->pGSFiller = NULL;
	}

	m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );

	delete SelArray;

    m_SeqList.Invalidate();

	pDoc->UpdateAllViews(NULL);
}


void 
CSeqDialog::CallSDFromNamedSeq( CObject *p )
{
	m_pPGSeq = (CPhyloSeq *)p;
}

void 
CSeqDialog::OnSeqdetails() 
{
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	// TODO: Add your control notification handler code here
	int SeqSel = m_SeqList.GetCurSel();
	if ( SeqSel != LB_ERR ) {
		CSeqDetDialog tDlg;
		tDlg.m_Instruct.Empty();

		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
		tDlg.m_SeqWeight = tCGSeg->GetWeight();
		tDlg.m_TextStart = tCGSeg->GetTextStart();
		tDlg.m_Descr = tCGSeg->GetDescr();

		m_SeqList.GetText ( SeqSel, tDlg.m_SeqName );

		if ( tDlg.DoModal() != IDOK ) {
			return;
		}
		if ( tDlg.m_NameChanged ) {
			if ( tDlg.m_SeqName.Find(" " ) != -1 ) {
				if ( AfxMessageBox("Space in Sequence Names can cause your data file to become unreadable by GeneDoc and/or other programs.\nAre you SURE you want spaces in the Sequence Name?", MB_YESNO ) != IDYES ) {
					return;
				}
			}
			CGeneSegment *tCGSeg = (CGeneSegment *)m_SeqList.GetItemDataPtr(SeqSel);
			m_SeqList.DeleteString( SeqSel );
			int aloc = m_SeqList.InsertString ( SeqSel, tDlg.m_SeqName );
			m_SeqList.SetItemDataPtr(aloc, tCGSeg );
			m_SeqList.SetSel ( SeqSel );

			CGSFiller *pGSFiller = pDoc->pGSFiller;
			// Put the data rows on the list
			
			POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
			tCGSeg->SetTitle( tDlg.m_SeqName );
			tCGSeg->SetDescr( tDlg.m_Descr );
			
			pDoc->SetModifiedFlag();
		}
		if ( tDlg.m_DescrChanged ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)m_SeqList.GetItemDataPtr(SeqSel);
			m_SeqList.DeleteString( SeqSel );
			int aloc = m_SeqList.InsertString ( SeqSel, tDlg.m_SeqName );
			m_SeqList.SetItemDataPtr(aloc, tCGSeg );
			m_SeqList.SetSel ( SeqSel );

			CGSFiller *pGSFiller = pDoc->pGSFiller;
			// Put the data rows on the list
			
			POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
			tCGSeg->SetDescr( tDlg.m_Descr );
			
			pDoc->SetModifiedFlag();
		}
		if ( tDlg.m_WeightChanged ) {
			CGSFiller *pGSFiller = pDoc->pGSFiller;
			// Put the data rows on the list
			
			POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
			tCGSeg->SetWeight( tDlg.m_SeqWeight );
			
			pDoc->SetModifiedFlag();
		}
		if ( tDlg.m_StartChanged ) {
			CGSFiller *pGSFiller = pDoc->pGSFiller;
			// Put the data rows on the list
			
			POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
			tCGSeg->SetTextStart( tDlg.m_TextStart );
			
			pDoc->SetModifiedFlag();
		}
	}

}

void CSeqDialog::OnSeqimport() 
{
	int SaveSel = m_SeqList.GetCount();	

	if ( !pDoc->SequenceImport() ) return;

	m_Modify = 1;

	m_SeqList.ResetContent();
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	int Count = 0;
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}

		// CListBox
		int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );

		
		Count++;
	}

	char scount[256];
	wsprintf(scount, "%d Seq", Count );
	m_strSeqCount.SetWindowText(scount);

	if ( m_SeqList.GetCount() ) {
		m_SeqList.SetSel(SaveSel);
	}
}

/*

  
	int SeqSel = m_SeqList.GetCurSel();
	if ( SeqSel != LB_ERR ) {
		if ( SeqSel == m_SeqList.GetCount() - 1 ) {
			return;
		}
		CString tStr;
		m_SeqList.GetText ( SeqSel, tStr );
		CGeneSegment *tCGSeg = (CGeneSegment *)m_SeqList.GetItemDataPtr(SeqSel);
		m_SeqList.DeleteString( SeqSel );
		int aloc = m_SeqList.InsertString ( SeqSel + 1, tStr );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );
		m_SeqList.SetCurSel ( SeqSel + 1 );
		

		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list
		
		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
		pGSFiller->SegDataList.RemoveAt (tPos);
		tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);
		pGSFiller->SegDataList.InsertAfter ( tPos, tCGSeg );
		
		pDoc->SetModifiedFlag();
		
	}
*/

int CSeqDialog::MoveDownFunc() 
{

	int count = 0;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return -1;

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return -1;
	           
	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	if ( pGSFiller != NULL ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
	
			if ( ffirst == 0 ) {
				// Looking for first selected ...
				// CListBox
				if ( m_SeqList.GetSel(count) > 0 ) {
					FirstSel = count;
					ffirst = 1;
				}
			} else {
				if ( m_SeqList.GetSel(count) == 0 ) {
					LastSel = count;
					CString tStr;
					m_SeqList.GetText ( count, tStr );
					CGeneSegment *tCGSeg = (CGeneSegment *)m_SeqList.GetItemDataPtr(count);
					m_SeqList.DeleteString( count );
					int aloc = m_SeqList.InsertString ( FirstSel, tStr );
					m_SeqList.SetItemDataPtr(aloc, tCGSeg );

					POSITION tSPos = pGSFiller->SegDataList.FindIndex (count + 2);
					tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(tSPos);
					pGSFiller->SegDataList.RemoveAt (tSPos);
					tSPos = pGSFiller->SegDataList.FindIndex (FirstSel + 2);
					pGSFiller->SegDataList.InsertBefore ( tSPos, tCGSeg );

					pDoc->SetModifiedFlag();

					break;
				}
			}
			count++;
		}
	}

	if ( LastSel != -1 ) {
		m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] < LastSel ) {
				m_SeqList.SetSel( SelArray[i] + 1, TRUE );
			} else {
				m_SeqList.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;

	return LastSel;

}

void CSeqDialog::OnSeqmovedown() 
{
	// TODO: Add your control notification handler code here
	MoveDownFunc();

    m_SeqList.Invalidate();
}


int CSeqDialog::MoveUpFunc()
{
	int count = m_SeqList.GetCount() -1;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return -1;

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return -1;
	           
	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );


	// Put the data rows on the list

	if ( pGSFiller != NULL ) {
		POSITION tPos = pGSFiller->SegDataList.GetTailPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetPrev(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
	
			if ( ffirst == 0 ) {
				// Looking for first selected ...
				// CListBox
				if ( m_SeqList.GetSel(count) > 0 ) {
					FirstSel = count;
					ffirst = 1;
				}
			} else {
				if ( m_SeqList.GetSel(count) == 0 ) {
					LastSel = count;
					CString tStr;
					m_SeqList.GetText ( count, tStr );
					CGeneSegment *tCGSeg = (CGeneSegment *)m_SeqList.GetItemDataPtr(count);
					m_SeqList.DeleteString( count );
					if ( FirstSel == m_SeqList.GetCount() ) {
						int aloc = m_SeqList.InsertString ( -1, tStr );
						m_SeqList.SetItemDataPtr(aloc, tCGSeg );
					} else {
						int aloc = m_SeqList.InsertString ( FirstSel, tStr );
						m_SeqList.SetItemDataPtr(aloc, tCGSeg );
					}

					POSITION tSPos = pGSFiller->SegDataList.FindIndex (count + 2);
					tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(tSPos);
					pGSFiller->SegDataList.RemoveAt (tSPos);
					tSPos = pGSFiller->SegDataList.FindIndex (FirstSel - 1 + 2);
					pGSFiller->SegDataList.InsertAfter ( tSPos, tCGSeg );

					pDoc->SetModifiedFlag();

					break;
				}
			}
			count--;
		}
	}

	if ( LastSel != -1 ) {
		m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] > LastSel ) {
				m_SeqList.SetSel( SelArray[i] - 1, TRUE );
			} else {
				m_SeqList.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;

	return LastSel;
}

void CSeqDialog::OnSeqmoveup() 
{
	// TODO: Add your control notification handler code here
	MoveUpFunc();

    m_SeqList.Invalidate();
}

void CSeqDialog::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	OnSeqdetails();
}

void CSeqDialog::OnMovebott() 
{
	// TODO: Add your control notification handler code here
	while ( MoveDownFunc() != -1 );

    m_SeqList.Invalidate();
	
}

void CSeqDialog::OnMovetop() 
{
	// TODO: Add your control notification handler code here
	
	while ( MoveUpFunc() != -1 );

    m_SeqList.Invalidate();

}

void CSeqDialog::OnCompliment() 
{
	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( AfxMessageBox ( "DNA Compliment Sequences: Are you Sure?", MB_OKCANCEL ) != IDOK ) {
		return;
	}

	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->DNACompliment(pDoc->m_UserVars.m_ProjectType);

	}

	pDoc->SetModifiedFlag();

	m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );

	delete SelArray;

    m_SeqList.Invalidate();
}

void CSeqDialog::OnReverse() 
{
	// TODO: Add your control notification handler code here
	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( AfxMessageBox ( "Reverse Sequences: Are you Sure?", MB_OKCANCEL ) != IDOK ) {
		return;
	}

	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->Reverse();

	}

	pDoc->SetModifiedFlag();

	m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );

	delete SelArray;

    m_SeqList.Invalidate();
	
}


void CSeqDialog::OnSeqexport() 
{
	// TODO: Add your control notification handler code here
	pDoc->SequenceExport();
	
}

void CSeqDialog::OnDuplicate() 
{
	// TODO: Add your control notification handler code here

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( AfxMessageBox ( "Duplicate Sequences: Are you Sure?", MB_OKCANCEL ) != IDOK ) {
		return;
	}

	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	CSeqDetDialog tDlg;

	for ( int i=0; i < SelCount; ++i ) {

		int SeqSel = SelArray[i];
		
		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
		
		// CString
		tDlg.m_SeqName.Empty();
		tDlg.m_Descr = tCGSeg->GetDescr();
		tDlg.m_Instruct = "SET NEW NAME FOR " + tCGSeg->GetTitle();
		if ( tDlg.DoModal() != IDOK ) continue;

		CPtrList CommentList;
		CPtrList SequenceList;

		// CEdit

		SeqNameStruct *tSNS;
		tSNS = new SeqNameStruct;
		tSNS->Name = tDlg.m_SeqName;
		tSNS->Descr = tDlg.m_Descr;
		tSNS->Check = 1234;
		tSNS->Weight = 1.0;

		tSNS->Len = tCGSeg->GetTextLength();
		tSNS->Start = tCGSeg->GetTextStart();

		DWORD Size = tSNS->Len;
		GeneStor *pc = (GeneStor *)GlobalLock(tCGSeg->GetTextHandle());
		if ( pc == NULL ) {
			AfxMessageBox("Duplicate:GlobalLock:Fail:2");
			return;
		}

		tSNS->hText = GlobalAlloc( GMEM_FLAG,  Size );
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("Duplicate:GlobalAlloc:Fail:1");
			return;
		}

		char *pn = (char *)GlobalLock(tSNS->hText);
		if ( pn == NULL ) {
			AfxMessageBox("Duplicate:GlobalLock:Fail:1");
			return;
		}
		
		while ( Size-- ) {
			*pn++ = pc->CharGene;
			pc++;
		}
		GlobalUnlock(tCGSeg->GetTextHandle());
		GlobalUnlock(tSNS->hText);

		SequenceList.AddTail( tSNS );
		
		pDoc->gMaxStrSize = tSNS->Len;

		pDoc->ProcessRows( CommentList, SequenceList, 1 );

	}

	delete SelArray;

	m_Modify = 1;

	m_SeqList.ResetContent();
	int Count = 0;
	
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}

		// CListBox
		int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );
		Count++;
	}

	char scount[256];
	wsprintf(scount, "%d Seq", Count );
	m_strSeqCount.SetWindowText(scount);

	pDoc->SetModifiedFlag();


	
}

/*
// CDialog
void CSeqDialog::OnCopy() 
{
	// TODO: Add your control notification handler code here

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	// Put the data rows on the list
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( SelCount != 1 ) {
		AfxMessageBox("Please Select only One Sequence to Copy to ClipBoard!" );
		return;
	}
	           
	int Selection;
	
	m_SeqList.GetSelItems( SelCount, &Selection );

	POSITION tPos = pGSFiller->SegDataList.FindIndex (Selection + 2);

	CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);
	
//	m_SeqList.SetSel(-1, FALSE);

    // Open the clipboard, and empty it.
 
    if (!OpenClipboard() )
        return; 

    EmptyClipboard(); 

	// Get Residues into Global Mem.
    HGLOBAL hglbCopy = tCGSeg->GetResidues();

    if (hglbCopy == NULL) { 
        CloseClipboard(); 
        return; 
    } 

    // Place the handle on the clipboard.

    SetClipboardData(CF_TEXT, hglbCopy); 
 
    CloseClipboard(); 


}


void CSeqDialog::OnExportselected() 
{
	// TODO: Add your control notification handler code here
	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list

	if ( pGSFiller == NULL ) return;

	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tCGSeg->SetExportFlag(0);

	}

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list

		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->SetExportFlag(1);

	}

	pDoc->SequenceExport(TRUE);

	m_SeqList.SelItemRange(FALSE, 0, m_SeqList.GetCount()-1 );

	delete SelArray;

    m_SeqList.Invalidate();
	
}
*/

void CSeqDialog::OnWritescr() 
{

	static char *aatrans[] = {
		"Ala", "", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile", "", "Lys",
		"Leu", "Met", "Asn", "", "Pro", "Gln", "Arg", "Ser", "Thr", "", "Val",
		"Trp", "Xxx", "Tyr", "Glx" 
	};

	static char BASED_CODE szFilter[] = "Scr Files (*.scr)|*.scr|All Files (*.*)|*.*||";

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	// Put the data rows on the list
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( SelCount != 1 ) {
		AfxMessageBox("Please Select only One Sequence!" );
		return;
	}

	
	char OutBuf[256];

	
	COLORREF TextC, BkC;
	pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextC, &BkC );

	int OffSet = 0;

	int Selection;
	
	m_SeqList.GetSelItems( SelCount, &Selection );

	POSITION tPos = pGSFiller->SegDataList.FindIndex (Selection + 2);

	CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

	GeneStor *pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

	if ( pGS == NULL ) return;

	DWORD tCount = tCGSeg->GetTextLength();

	CString possName = tCGSeg->GetTitle() + ".scr";

	CFileDialog fDlg(FALSE, "scr", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );


	CPDBDialog tDlg;
	CPtrList m_ColorList;

	// Fill out color list.
	for ( DWORD i = 0; i < tCount; ++i ) {
		POSITION tPos = tDlg.m_ColorList.GetHeadPosition();
		int found = 0;
		while ( tPos != NULL ) {
			stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)tDlg.m_ColorList.GetNext(tPos);
			if ( pPDBC->rgbText == pGS[i].TextColor
				&& pPDBC->rgbBack == pGS[i].BackColor
			) {
				found = 1;
				break;
			}
		}
		if ( !found  ) {
			stcPDBCOLOR *pPDBC = new stcPDBCOLOR;
			pPDBC->rgbText = pGS[i].TextColor;
			pPDBC->rgbBack = pGS[i].BackColor;
			tDlg.m_ColorList.AddTail( pPDBC );

			if ( !(pGS[i].TextColor == TextC && pGS[i].BackColor == BkC) ) {
				stcPDBCOLOR *pPDBC2 = new stcPDBCOLOR;
				pPDBC2->rgbText = pGS[i].TextColor;
				pPDBC2->rgbBack = pGS[i].BackColor;
				m_ColorList.AddTail( pPDBC2 );
			}
		}
	}

	if ( tDlg.DoModal() != IDOK ) goto Out;


	// CDocument
	OffSet = tDlg.m_PDBOffset;

	if ( fDlg.DoModal() != IDOK ) goto Out;

	
TRY
{
	CStdioFile oFile( fDlg.GetPathName() ,CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	if ( tDlg.m_ClearAll ) {
		oFile.WriteString( "select all\n" );
		oFile.WriteString( "colour bonds none\n" );
		oFile.WriteString( "colour backbone none\n" );
		oFile.WriteString( "colour hbonds none\n" );
		oFile.WriteString( "colour ssbonds none\n" );
		oFile.WriteString( "colour ribbons none\n" );
		oFile.WriteString( "colour white\n" );
	}

	if ( tDlg.m_DispSidechain && tDlg.m_ClearAll ) {
		oFile.WriteString( "wireframe off\n" );
		oFile.WriteString( "spacefill off\n" );
		oFile.WriteString( "cartoon off\n" );
	}

	CString ShadeWhich;
	ShadeWhich = " ";
	if ( tDlg.m_ShadeWhich == 1 ) {
		ShadeWhich = " and backbone";
	} else if ( tDlg.m_ShadeWhich == 2 ) {
		ShadeWhich = " and sidechain";
	}

	for ( DWORD i = 0; i < tCount; ++i ) {
		char tChar = toupper(pGS[i].CharGene );
		if ( tChar >= 'A' && tChar <= 'Z' ) {

			if ( !tDlg.m_IncludeBase ) {
				if ( pGS[i].BackColor == pDoc->m_UserVars.m_BackColor0 
					&& pGS[i].TextColor == pDoc->m_UserVars.m_ForeColor0 
				) continue;
			}

			if ( tDlg.m_SafeMode ) {
				sprintf( OutBuf, "select %s%ld%s\ncolour [%d,%d,%d]\n", 
					aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
					(const char *)ShadeWhich, 
					GetRValue( pGS[i].BackColor ), 
					GetGValue( pGS[i].BackColor ), 
					GetBValue( pGS[i].BackColor ) 
				);
			} else {
				sprintf( OutBuf, "select %ld%s\ncolour [%d,%d,%d]\n", 
					pGS[i].GeneSeqNumber + OffSet, 
					(const char *)ShadeWhich, 
					GetRValue( pGS[i].BackColor ), 
					GetGValue( pGS[i].BackColor ), 
					GetBValue( pGS[i].BackColor ) 
				);
			}
			oFile.WriteString( OutBuf );

		}
	}

	oFile.WriteString( "select all\n" );

	if ( tDlg.m_GroupSel ) {


		UINT ocount = 0;
		UINT scount = 1;
		UINT gcount = 1;
		tPos = m_ColorList.GetHeadPosition();
		while ( tPos != NULL ) {
			stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)m_ColorList.GetNext(tPos);
			sprintf( OutBuf, "#colour [%d,%d,%d]\nselect ", 
				GetRValue( pPDBC->rgbBack ), 
				GetGValue( pPDBC->rgbBack ), 
				GetBValue( pPDBC->rgbBack ) 
			);
			oFile.WriteString( OutBuf );
			for (int i = 0; i < tCount; ++i ) {
				char tChar = toupper(pGS[i].CharGene );
				if ( tChar >= 'A' && tChar <= 'Z' ) {

					if ( pPDBC->rgbText == pGS[i].TextColor
						&& pPDBC->rgbBack == pGS[i].BackColor
					) {
						if ( ocount++ >= 10 ) {
							sprintf( OutBuf, "\ndefine gsel%03d%03d selected\nselect ", gcount, scount++ );
							oFile.WriteString( OutBuf );
							ocount = 0;
						}
						sprintf( OutBuf, "%s%ld%s or ", 
							aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
							(const char *)ShadeWhich 
						);
						oFile.WriteString( OutBuf );
					}
				}
			}
			int i;
			sprintf( OutBuf, "\n" );
			oFile.WriteString( OutBuf );
			if ( scount != 1 ) {
				ocount = 0;
				sprintf( OutBuf, "define gsel%03d%03d selected\nselect ", gcount, scount++ );
				oFile.WriteString( OutBuf );
				for ( i = 1; i < scount; ++i ) {
					if ( ocount++ >= 8 ) {
						sprintf( OutBuf, "\ndefine gsel%03d%03d selected\nselect gsel%03d%03d or ", gcount, scount, gcount, scount );
						scount++;
						oFile.WriteString( OutBuf );
						ocount = 0;
					}
					sprintf( OutBuf, "gsel%03d%03d or ", gcount, i );
					oFile.WriteString( OutBuf );
				}
	//			sprintf( OutBuf, "\ndefine gsel%03d%03d selected\n", gcount, scount++ );
	//			oFile.WriteString( OutBuf );
				oFile.WriteString( "\n" );
			}
			sprintf( OutBuf, "define group%d selected\n", gcount++ );
			oFile.WriteString( OutBuf );
			scount = 1;
			ocount = 0;
		}
	}

	while ( !m_ColorList.IsEmpty() ) {
		delete (stcPDBCOLOR*) m_ColorList.RemoveHead();
	}

	oFile.WriteString( "select all\n" );

	if ( tDlg.m_DispSidechain ) {
		CString strBack;
		if ( tDlg.m_ExcludeO ) {
			strBack = "select backbone and not *.o\n";
		} else {
			strBack = "select backbone\n";
		}
		if ( tDlg.m_ComboBack == "Stick" ) {
			strBack += "wireframe 80\n";
		} else if ( tDlg.m_ComboBack == "SpaceFill" ) {
			strBack += "spacefill\n";
		} else if ( tDlg.m_ComboBack == "Ball&Stick" ) {
			strBack += "spacefill 120\nwireframe 40\n";
		} else if ( tDlg.m_ComboBack == "WireFrame" ) {
			strBack += "wireframe\n";
		} else if ( tDlg.m_ComboBack == "Ribbon" ) {
			strBack += "ribbon\n";
		} else if ( tDlg.m_ComboBack == "Cartoon" ) {
			strBack += "cartoon\n";
		}

		oFile.WriteString( strBack );

		CString strDisp;
		if ( tDlg.m_SideDisp == "Stick" ) {
			strDisp = "wireframe 80";
		} else if ( tDlg.m_SideDisp == "SpaceFill" ) {
			strDisp = "spacefill";
		} else if ( tDlg.m_SideDisp == "Ball&Stick" ) {
			strDisp = "spacefill 120\nwireframe 40";
		} else if ( tDlg.m_SideDisp == "WireFrame" ) {
			strDisp = "wireframe";
		}

		for (int i = 0; i < tCount; ++i ) {
			char tChar = toupper(pGS[i].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				POSITION cPos = tDlg.m_ColorList.GetHeadPosition();
				int found = 0;
				while ( cPos != NULL ) {
					stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)tDlg.m_ColorList.GetNext(cPos);
					if ( pGS[i].BackColor == pPDBC->rgbBack && pGS[i].TextColor == pPDBC->rgbText ) {
						found = 1;
						break;
					}
				}
				if ( found ) {
					if ( tDlg.m_SafeMode ) {
						// Thanks God ...
						if ( tChar == 'P' ) {
							sprintf( OutBuf, "select %s%ld and sidechain or %s%ld.ca or %s%ld.n\n%s\n", 
								aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
								aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
								aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
								strDisp
							);
						} else {
							sprintf( OutBuf, "select %s%ld and sidechain or %s%ld.ca\n%s\n", 
								aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
								aatrans[tChar-'A'], pGS[i].GeneSeqNumber + OffSet, 
								strDisp
							);
						}
					} else {
						sprintf( OutBuf, "select %ld and sidechain or ld.ca\n%s\n", 
							pGS[i].GeneSeqNumber + OffSet, 
							pGS[i].GeneSeqNumber + OffSet, 
							strDisp
						);
					}
					oFile.WriteString( OutBuf );
				}
			}
		}
		
		oFile.WriteString( "select all\n" );
	}
	
	oFile.Close();

}
CATCH( CFileException, e )
{
	AfxMessageBox("File Error" );
}
END_CATCH

Out:
	GlobalUnlock( tCGSeg->GetTextHandle() );

	while ( !tDlg.m_ColorList.IsEmpty() ) delete (stcPDBCOLOR *)tDlg.m_ColorList.RemoveHead();
}


void CSeqDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	
    char tchBuffer[2048]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    CGeneSegment *pCGSeg;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_LIST1)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 7;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pCGSeg = (CGeneSegment *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%s",  (const char *)pCGSeg->GetTitle() );
			
//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));
			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
			ExtTextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				ETO_CLIPPED, 
				&rect, 
				tchBuffer, 
				pCGSeg->GetTitle().GetLength(), 
				NULL
			);
			
			// Bingo ..
			strncpy ( tchBuffer, pCGSeg->GetDescr(), pCGSeg->GetDescr().GetLength() );
			tchBuffer[pCGSeg->GetDescr().GetLength()] = 0;
			
			for ( i = strlen ( tchBuffer ); i < 100; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left + OffSet, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);
			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 

			break;
 
		case ODA_SELECT:
 
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);
			
			break; 
		}
		char scount[256];
		wsprintf(scount, "%d Selected", 	m_SeqList.GetSelCount() );
		m_CountSel.SetWindowText(scount);
		// CStatic
	
	}
}

void CSeqDialog::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( (
		lpMeasureItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	} else {
		CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	}
	
}

void CSeqDialog::OnSortname() 
{

	// TODO: Add your control notification handler code here
	pDoc->BeginWaitCursor();
	int count = 0;
	CGeneSegment *tCGSeg;
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( pGSFiller != NULL ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			count++;
		}
	}

	for ( int i = 2; i < count + 2; ++i ) {
		for ( int j = 2; j < count + 2; ++j ) {
			CGeneSegment *iCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(pGSFiller->SegDataList.FindIndex(i));

			CGeneSegment *jCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(pGSFiller->SegDataList.FindIndex(j));

			if ( jCGSeg->GetTitle().CompareNoCase( iCGSeg->GetTitle() ) > 0 ) {

				POSITION iSPos = pGSFiller->SegDataList.FindIndex(i);

				POSITION jSPos = pGSFiller->SegDataList.FindIndex(j);

				pGSFiller->SegDataList.SetAt( iSPos, jCGSeg );

				pGSFiller->SegDataList.SetAt( jSPos, iCGSeg );
			}
		}
	}
	
	// Put the data rows on the list
	while ( m_SeqList.GetCount() ) {
		m_SeqList.DeleteString ( 0 );
	}

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}

		// CListBox
		int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );

	}
	
	if ( m_SeqList.GetCount() ) {
		m_SeqList.SetSel(0);
	}

    m_SeqList.Invalidate();

	pDoc->SetModifiedFlag();
	pDoc->EndWaitCursor();
}

void CSeqDialog::OnSavesort() 
{
	// TODO: Add your control notification handler code here
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	static char BASED_CODE szFilter[] = "Snm Files (*.snm)|*.snm|All Files (*.*)|*.*||";

	CString possName = pDoc->GetTitle().SpanExcluding(".");

	CFileDialog fDlg(FALSE, "snm", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( fDlg.DoModal() != IDOK ) return;

TRY
{
	CStdioFile oFile( fDlg.GetPathName() ,CFile::modeCreate | CFile::modeWrite | CFile::typeText );


	if ( pGSFiller != NULL ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			oFile.WriteString( tCGSeg->GetTitle() + "\n" );
		}
	}


	oFile.Close();

}
CATCH( CFileException, e )
{
	AfxMessageBox("File Error" );
}
END_CATCH

}

void CSeqDialog::OnLoadsort() 
{
	int Max = 0;

#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		Max++;
	}


	static char BASED_CODE szFilter[] = "Snm Files (*.snm)|*.snm|All Files (*.*)|*.*||";
	CString PathName;

	CString possName = pDoc->GetTitle().SpanExcluding(".");
	CFileDialog tDlg( TRUE, "snm", possName, 0, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;

#ifndef _WIN32
	PathName = tDlg.GetFileTitle();
#else
	PathName = tDlg.GetFileName();
#endif

TRY {

	CString tString;

	CStdioFile rFile(PathName, CFile::modeRead | CFile::typeText );

	Max += 2;
	int into = 2;

    while( 1 )
    {
		if ( into > Max ) break;

		tString.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( rFile.ReadString( rbuff, sizeof(rbuff) ) == NULL ) {
			break;
		}
		// CString
		tString = CString(rbuff).SpanExcluding("\n\r");
#else
		if ( !rFile.ReadString( tString ) ) {
			break;
		}
#endif

		for ( int j = 2; j < Max; ++j ) {

			CGeneSegment *jCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(pGSFiller->SegDataList.FindIndex(j));

			if ( jCGSeg->GetTitle().Compare( tString ) == 0 ) {

				POSITION iSPos = pGSFiller->SegDataList.FindIndex(into);
				CGeneSegment *iCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(iSPos);

				POSITION jSPos = pGSFiller->SegDataList.FindIndex(j);

				pGSFiller->SegDataList.SetAt( iSPos, jCGSeg );

				pGSFiller->SegDataList.SetAt( jSPos, iCGSeg );

				into++;
				break;
			}
		}
	}

	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
END_CATCH

	// Put the data rows on the list
	while ( m_SeqList.GetCount() ) {
		m_SeqList.DeleteString ( 0 );
	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}

		// CListBox
		int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );

	}
	
	if ( m_SeqList.GetCount() ) {
		m_SeqList.SetSel(0);
	}

    m_SeqList.Invalidate();

	pDoc->SetModifiedFlag();

	
}

void CSeqDialog::OnSortdesc() 
{

	// TODO: Add your control notification handler code here
	pDoc->BeginWaitCursor();
	int count = 0;
	CGeneSegment *tCGSeg;
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;

	if ( pGSFiller != NULL ) {
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			count++;
		}
	}

	for ( int i = 2; i < count + 2; ++i ) {
		for ( int j = 2; j < count + 2; ++j ) {
			CGeneSegment *iCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(pGSFiller->SegDataList.FindIndex(i));

			CGeneSegment *jCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt(pGSFiller->SegDataList.FindIndex(j));

			if ( jCGSeg->GetDescr().CompareNoCase( iCGSeg->GetDescr() ) > 0 ) {

				POSITION iSPos = pGSFiller->SegDataList.FindIndex(i);

				POSITION jSPos = pGSFiller->SegDataList.FindIndex(j);

				pGSFiller->SegDataList.SetAt( iSPos, jCGSeg );

				pGSFiller->SegDataList.SetAt( jSPos, iCGSeg );
			}
		}
	}
	
	// Put the data rows on the list
	while ( m_SeqList.GetCount() ) {
		m_SeqList.DeleteString ( 0 );
	}

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}

		// CListBox
		int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
		m_SeqList.SetItemDataPtr(aloc, tCGSeg );

	}
	
	if ( m_SeqList.GetCount() ) {
		m_SeqList.SetSel(0);
	}

    m_SeqList.Invalidate();

	pDoc->SetModifiedFlag();
	pDoc->EndWaitCursor();
}

	
