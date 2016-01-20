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
// searchdl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchPropPage dialog

CSearchPropPage::CSearchPropPage() : CPropertyPage(CSearchPropPage::IDD)
{
	//{{AFX_DATA_INIT(CSearchPropPage)
	m_ProSite = -1;
	m_iEnabled = FALSE;
	//}}AFX_DATA_INIT
}

void CSearchPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchPropPage)
	DDX_Control(pDX, IDC_SEARCHLIST, m_listSearch);
	DDX_Radio(pDX, IDC_PROSITE, m_ProSite);
	DDX_Check(pDX, IDC_ENABLED, m_iEnabled);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSearchPropPage)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_TEXTCOLOR, OnTextcolor)
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_BN_CLICKED(IDC_PROSITE, OnProsite)
	ON_LBN_DBLCLK(IDC_SEARCHLIST, OnDblclkSearchlist)
	ON_BN_CLICKED(IDC_LOADFILE, OnLoadfile)
	ON_BN_CLICKED(IDC_LOADREBASE, OnLoadrebase)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_BN_CLICKED(IDC_OVERLAP, OnOverlap)
	ON_BN_CLICKED(IDC_WRITERE, OnWritere)
	ON_BN_CLICKED(IDC_REBASE, OnRebase)
	ON_LBN_SELCHANGE(IDC_SEARCHLIST, OnSelchangeSearchlist)
	ON_BN_CLICKED(IDC_ENABLED, OnEnabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSearchPropPage message handlers

BOOL CSearchPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// CListBox ..
	ReBuildListBox();	
	m_SearchChanged = 0;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CSearchPropPage::ReBuildListBox()
{
	m_listSearch.ResetContent();
	POSITION tPos = m_listCopy.GetHeadPosition();
	int count = 0;
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_listCopy.GetNext(tPos);

		m_listSearch.AddString(pSearch->strSearch );
		m_listSearch.SetItemDataPtr(count++, pSearch );
	}
}

void CSearchPropPage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
    char tchBuffer[2048]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    stcSearch* pSearch;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_SEARCHLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 7;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pSearch = (stcSearch *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%s",  (const char *)pSearch->strName );
			
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
				pSearch->strName.GetLength(), 
				NULL
			);
			
			// Bingo ..
			m_listSearch.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 100; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			if ( pSearch->iEnabled ) {
				SetBkColor ( lpDrawItemStruct->hDC, pSearch->rgbBack );
				SetTextColor ( lpDrawItemStruct->hDC, pSearch->rgbText );
			} else {
				SetBkColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );
				SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );
			}

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
	
	}

//	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSearchPropPage::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
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
		CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	}
	
}

void CSearchPropPage::OnDblclkSearchlist() 
{
	// TODO: Add your control notification handler code here
	OnEdit();	
}

void CSearchPropPage::OnEdit() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}

	if ( (CurSel = m_listSearch.GetCurSel()) == LB_ERR ) {
		return;
	}
	
	CSrchDlg tDlg;

	// CPtrList
	stcSearch* pSearch = (stcSearch *)m_listCopy.GetAt( m_listCopy.FindIndex( CurSel) );

	tDlg.m_Name = pSearch->strName;
	tDlg.m_Motif = pSearch->strSearch;
	tDlg.m_Descrip = pSearch->strDescrip;
	tDlg.m_iEnabled = pSearch->iEnabled;

	if ( tDlg.DoModal() != IDOK ) return;

	pSearch->strName = tDlg.m_Name;
	pSearch->strSearch = tDlg.m_Motif;
	pSearch->strDescrip = tDlg.m_Descrip;
	pSearch->iEnabled = tDlg.m_iEnabled;

	ReBuildListBox();	

	m_listSearch.Invalidate();

	m_SearchChanged = 1;
	
}

void CSearchPropPage::OnNew() 
{
	// TODO: Add your control notification handler code here
	CSrchDlg tDlg;

	// CPtrList

	if ( tDlg.DoModal() == IDOK ) {
		if ( !tDlg.m_Motif.GetLength() ) return;

		stcSearch *pSearch = new stcSearch;

		pSearch->iEnabled = tDlg.m_iEnabled;

		pSearch->rgbText = RGB(255,255,255);
		pSearch->rgbBack = RGB(0,0,0);
		pSearch->strName = tDlg.m_Name;
		pSearch->strSearch = tDlg.m_Motif;
		pSearch->strDescrip = tDlg.m_Descrip;

		m_listCopy.AddTail ( pSearch );

		ReBuildListBox();
		m_listSearch.Invalidate();

		m_SearchChanged = 1;
	}
	
}

void CSearchPropPage::OnDelete() 
{

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;


	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listSearch.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		m_listSearch.DeleteString ( SeqSel );

		stcSearch *pSearch = (stcSearch *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );
		m_listCopy.RemoveAt( m_listCopy.FindIndex( SeqSel) );
		delete pSearch;
	}

	m_listSearch.SelItemRange(FALSE, 0, m_listSearch.GetCount()-1 );

	delete SelArray;

	ReBuildListBox();
	m_listSearch.Invalidate();

	m_SearchChanged = 1;
	
}

void CSearchPropPage::OnTextcolor() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	if ( (CurSel = m_listSearch.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	stcSearch* pSearch = (stcSearch *)m_listSearch.GetItemDataPtr(CurSel);
	tDlg.m_cc.rgbResult = pSearch->rgbText;
	if ( tDlg.DoModal() == IDOK ) {

		int *SelArray = new int[SelCount];
		
		m_listSearch.GetSelItems( SelCount, SelArray );

		for ( int i=SelCount-1; i >=0; --i ) {

			int SeqSel = SelArray[i];
		
			stcSearch *pSearch = (stcSearch *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

			pSearch->rgbText = tDlg.GetColor();
		}

		delete SelArray;

		m_listSearch.Invalidate();

		m_SearchChanged = 1;
	}
	
}

void CSearchPropPage::OnBackcolor() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}

	if ( (CurSel = m_listSearch.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	stcSearch* pSearch = (stcSearch *)m_listSearch.GetItemDataPtr(CurSel);
	tDlg.m_cc.rgbResult = pSearch->rgbBack;
	if ( tDlg.DoModal() == IDOK ) {
		int *SelArray = new int[SelCount];
		
		m_listSearch.GetSelItems( SelCount, SelArray );

		for ( int i=SelCount-1; i >=0; --i ) {

			int SeqSel = SelArray[i];
		
			stcSearch *pSearch = (stcSearch *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

			pSearch->rgbBack = tDlg.GetColor();
		}

		delete SelArray;

		m_listSearch.Invalidate();

		m_SearchChanged = 1;
	}

}

void CSearchPropPage::OnProsite() 
{
	// TODO: Add your control notification handler code here
	m_SearchChanged = 1;
	
}

void CSearchPropPage::OnRebase() 
{
	// TODO: Add your control notification handler code here
	m_SearchChanged = 1;
	
}


void CSearchPropPage::OnLoadfile() 
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "Dat Files (*.dat)|*.dat|All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, "dat", "prosite", 0, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	pDoc->BeginWaitCursor();
	pDoc->ScanPrositeMotifs( tDlg.GetPathName(), &m_listCopy );

	ColorCopyList();
	ReBuildListBox();
	m_ProSite = 0;
	Invalidate();
	UpdateData(FALSE);
	pDoc->EndWaitCursor();

	m_SearchChanged = 1;

}

void CSearchPropPage::OnLoadrebase() 
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, NULL, NULL, 0, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	pDoc->ScanRebaseFile( tDlg.GetPathName(), &m_listCopy );
	pDoc->EndWaitCursor();

	ColorCopyList();
	ReBuildListBox();
	m_ProSite = 1;
	Invalidate();
	UpdateData(FALSE);

	m_SearchChanged = 1;


}

void
CSearchPropPage::ColorCopyList()
{
	int count = m_listCopy.GetCount();
	if ( count < 2 ) return;
	int step = 255 / count;
	int red = 255;
	int green = 0;
	int blue = 0;

	POSITION tPos = m_listCopy.GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_listCopy.GetNext(tPos);
		if ( pSearch->rgbBack == RGB(0,0,0) ) {
			pSearch->rgbBack = RGB(red, green, blue );
		}
		red -= step;
		blue += step;
		if ( red <= 0 ) {
			red = 0;
			blue = 255;
		}
	}
}

void CSearchPropPage::OnMovedown() 
{

	int count = 0;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listSearch.GetSelItems( SelCount, SelArray );

	POSITION tPos = m_listCopy.GetHeadPosition();
	while (tPos != NULL ) {

		m_listCopy.GetNext(tPos);

		if ( ffirst == 0 ) {
			// Looking for first selected ...
			// CListBox
			if ( m_listSearch.GetSel(count) > 0 ) {
				FirstSel = count;
				ffirst = 1;
			}
		} else {
			if ( m_listSearch.GetSel(count) == 0 ) {
				stcSearch *tSearch;
				LastSel = count;
				CString tStr;
				m_listSearch.GetText ( count, tStr );
				tSearch = (stcSearch *)m_listSearch.GetItemDataPtr ( count );
				m_listSearch.DeleteString( count );
				m_listSearch.InsertString ( FirstSel, tStr );
				m_listSearch.SetItemDataPtr ( FirstSel, tSearch );

				POSITION tSPos = m_listCopy.FindIndex (count);
				tSearch = (stcSearch *)m_listCopy.GetAt(tSPos);
				m_listCopy.RemoveAt(tSPos);
				tSPos = m_listCopy.FindIndex (FirstSel);
				m_listCopy.InsertBefore ( tSPos, tSearch );

				break;
			}
		}
		count++;
	}

	if ( LastSel != -1 ) {
		m_listSearch.SelItemRange(FALSE, 0, m_listSearch.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] < LastSel ) {
				m_listSearch.SetSel( SelArray[i] + 1, TRUE );
			} else {
				m_listSearch.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;


//	ReBuildListBox();	

	m_listSearch.Invalidate();

	m_SearchChanged = 1;

}

void CSearchPropPage::OnMoveup() 
{
	int count = m_listSearch.GetCount() - 1;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listSearch.GetSelItems( SelCount, SelArray );


	// Put the data rows on the list

	POSITION tPos = m_listCopy.GetTailPosition();
	while (tPos != NULL ) {

	
		m_listCopy.GetPrev(tPos);

		if ( ffirst == 0 ) {
			// Looking for first selected ...
			// CListBox
			if ( m_listSearch.GetSel(count) > 0 ) {
				FirstSel = count;
				ffirst = 1;
			}
		} else {
			if ( m_listSearch.GetSel(count) == 0 ) {
				LastSel = count;
				CString tStr;
				stcSearch *tSearch;
				m_listSearch.GetText ( count, tStr );
				tSearch = (stcSearch *)m_listSearch.GetItemDataPtr ( count );
				m_listSearch.DeleteString( count );
				if ( FirstSel == m_listSearch.GetCount() ) {
					m_listSearch.InsertString ( -1, tStr );
					m_listSearch.SetItemDataPtr ( FirstSel, tSearch );
				} else {
					m_listSearch.InsertString ( FirstSel, tStr );
					m_listSearch.SetItemDataPtr ( FirstSel, tSearch );
				}

				POSITION tSPos = m_listCopy.FindIndex (count);
				tSearch = (stcSearch *)m_listCopy.GetAt(tSPos);
				m_listCopy.RemoveAt (tSPos);
				tSPos = m_listCopy.FindIndex (FirstSel - 1);
				m_listCopy.InsertAfter ( tSPos, tSearch );

				break;
			}
		}
		count--;
	}

	if ( LastSel != -1 ) {
		m_listSearch.SelItemRange(FALSE, 0, m_listSearch.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] > LastSel ) {
				m_listSearch.SetSel( SelArray[i] - 1, TRUE );
			} else {
				m_listSearch.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;

	m_listSearch.Invalidate();

	m_SearchChanged = 1;

}

void CSearchPropPage::OnOverlap() 
{
	// TODO: Add your control notification handler code here
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = m_OverlapColor;
	if ( tDlg.DoModal() == IDOK ) {
		m_OverlapColor = tDlg.GetColor();
		m_SearchChanged = 1;
	}
}

void CSearchPropPage::OnWritere() 
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( FALSE, NULL, NULL, 0, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	char oBuff[512];

TRY {

	CStdioFile oFile( tDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	oFile.WriteString( "..\n" );
	oFile.WriteString( "\n" );

	POSITION tPos = m_listCopy.GetHeadPosition();
	int count = 0;
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_listCopy.GetNext(tPos);
		// AlwI       9 GGATCnnnn'n_   1 !                                    >NSU
		sprintf( oBuff, "%s   0 %s  0 ! > [%d,%d,%d][%d,%d,%d]\n", 
			pSearch->strName, pSearch->strSearch, 
			GetRValue( pSearch->rgbBack ), GetGValue( pSearch->rgbBack ), GetBValue( pSearch->rgbBack ), 
			GetRValue( pSearch->rgbText ), GetGValue( pSearch->rgbText ), GetBValue( pSearch->rgbText ) 
		);

		oFile.WriteString( oBuff );
		oFile.WriteString( "\n" );
	}

	oFile.Close();

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}


void CSearchPropPage::OnSelchangeSearchlist() 
{
	// TODO: Add your control notification handler code here
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	if ( SelCount > 1 ) {
		m_iEnabled = FALSE;
		UpdateData(FALSE);
		return;
	}
	           
	int SelArray;
	
	m_listSearch.GetSelItems( SelCount, &SelArray );

	stcSearch* pSearch = (stcSearch *)m_listSearch.GetItemDataPtr(SelArray);

	m_iEnabled = pSearch->iEnabled;

	UpdateData(FALSE);

}

void CSearchPropPage::OnEnabled() 
{
	// TODO: Add your control notification handler code here
	int SelCount = m_listSearch.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	int *SelArray = new int[SelCount];
	
	m_listSearch.GetSelItems( SelCount, SelArray );

	UpdateData();
	
	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];

		stcSearch *pSearch = (stcSearch *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

		pSearch->iEnabled = m_iEnabled;
	}

	delete SelArray;

	m_listSearch.Invalidate();
	
}

