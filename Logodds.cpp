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
// logodds.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogOddsPropPage dialog


CLogOddsPropPage::CLogOddsPropPage() : CPropertyPage(CLogOddsPropPage::IDD)
{
	//{{AFX_DATA_INIT(CLogOddsPropPage)
	m_iLogOddsNoOv = FALSE;
	m_dLogOddsMin = 0.0;
	m_iLogOddsBestN = 0;
	m_iLogOddsMode = -1;
	m_dLogOddsTL1 = 0.0;
	m_dLogOddsTL2 = 0.0;
	m_dLogOddsTL3 = 0.0;
	m_iEnabled = FALSE;
	m_dLogOddsMPC = 0.0;
	m_iLogOddsOutTab = -1;
	m_iLogOddsBack = -1;
	m_dLogOddsStA = 0.0;
	m_dLogOddsStC = 0.0;
	m_dLogOddsStG = 0.0;
	m_dLogOddsStT = 0.0;
	//}}AFX_DATA_INIT
	m_DialogInited = 0;
	m_ProjectType = -1;
}

void CLogOddsPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogOddsPropPage)
	DDX_Control(pDX, IDC_OUTTAB, m_cbOutTab);
	DDX_Control(pDX, IDC_MOTIFLIST, m_listLogOdds);
	DDX_Check(pDX, IDC_ALLOWOV, m_iLogOddsNoOv);
	DDX_Text(pDX, IDC_BETTERTHAN, m_dLogOddsMin);
	DDX_Text(pDX, IDC_BESTN, m_iLogOddsBestN);
	DDX_Radio(pDX, IDC_MODE, m_iLogOddsMode);
	DDX_Text(pDX, IDC_TRILEVEL1, m_dLogOddsTL1);
	DDX_Text(pDX, IDC_TRILEVEL2, m_dLogOddsTL2);
	DDX_Text(pDX, IDC_TRILEVEL3, m_dLogOddsTL3);
	DDX_Check(pDX, IDC_ENABLED, m_iEnabled);
	DDX_Text(pDX, IDC_MPC, m_dLogOddsMPC);
	DDX_CBIndex(pDX, IDC_OUTTAB, m_iLogOddsOutTab);
	DDX_Radio(pDX, IDC_BACKGROUND2, m_iLogOddsBack);
	DDX_Text(pDX, IDC_STATICA, m_dLogOddsStA);
	DDX_Text(pDX, IDC_STATICC, m_dLogOddsStC);
	DDX_Text(pDX, IDC_STATICG, m_dLogOddsStG);
	DDX_Text(pDX, IDC_STATICT, m_dLogOddsStT);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLogOddsPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLogOddsPropPage)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_MEME, OnMeme)
	ON_BN_CLICKED(IDC_TEXTCOLOR, OnTextcolor)
	ON_LBN_DBLCLK(IDC_MOTIFLIST, OnDblclkMotiflist)
	ON_BN_CLICKED(IDC_OVERLAP, OnOverlap)
	ON_LBN_SELCHANGE(IDC_MOTIFLIST, OnSelchangeMotiflist)
	ON_BN_CLICKED(IDC_ENABLED, OnEnabled)
	ON_CBN_SELCHANGE(IDC_OUTTAB, OnSelchangeOuttab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLogOddsPropPage message handlers
BOOL CLogOddsPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( m_ProjectType == -1 ) m_ProjectType = pDoc->m_UserVars.m_ProjectType;

	if ( m_ProjectType > 1 ) {
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "1:1:Pam30" );
		m_cbOutTab.AddString( "1:1:Pam60" );
		m_cbOutTab.AddString( "1:1:Pam90" );
		m_cbOutTab.AddString( "3:1:Pam30" );
		m_cbOutTab.AddString( "3:1:Pam60" );
		m_cbOutTab.AddString( "3:1:Pam90" );
		m_cbOutTab.AddString( "Pam30:pseudo" );
		m_cbOutTab.AddString( "Pam60:pseudo" );
		m_cbOutTab.AddString( "Pam90:pseudo" );
	} else {
		// CComboBox
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "BloSum30" );
		m_cbOutTab.AddString( "BloSum50" );
		m_cbOutTab.AddString( "BloSum62" );
		m_cbOutTab.AddString( "BloSum75" );
	}

	m_DialogInited = 1;
	ReBuildListBox();	
	m_LogOddsChanged = 0;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogOddsPropPage::ChangeProjectType(int nType)
{
	m_ProjectType = nType;

	if ( !m_DialogInited ) return;

	if ( m_ProjectType > 1 ) {
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "1:1:Pam30" );
		m_cbOutTab.AddString( "1:1:Pam60" );
		m_cbOutTab.AddString( "1:1:Pam90" );
		m_cbOutTab.AddString( "3:1:Pam30" );
		m_cbOutTab.AddString( "3:1:Pam60" );
		m_cbOutTab.AddString( "3:1:Pam90" );
		m_cbOutTab.AddString( "Pam30:pseudo" );
		m_cbOutTab.AddString( "Pam60:pseudo" );
		m_cbOutTab.AddString( "Pam90:pseudo" );

		m_cbOutTab.SetCurSel(m_iLogOddsOutTab);

		OnSelchangeOuttab();
	} else {
		// CComboBox
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "BloSum30" );
		m_cbOutTab.AddString( "BloSum50" );
		m_cbOutTab.AddString( "BloSum62" );
		m_cbOutTab.AddString( "BloSum75" );

		if ( m_iLogOddsOutTab > 3 ) m_iLogOddsOutTab = 2;
		m_cbOutTab.SetCurSel(m_iLogOddsOutTab);

		m_dLogOddsStA = 235091.0;
		m_dLogOddsStC = 181410.0;
		m_dLogOddsStG = 185091.0;
		m_dLogOddsStT = 226863.0;
	}


}

void
CLogOddsPropPage::ReBuildListBox()
{
	m_listLogOdds.ResetContent();
	POSITION tPos = m_listCopy.GetHeadPosition();
	int count = 0;
	while ( tPos != NULL ) {
		stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetNext(tPos);

		m_listLogOdds.AddString(pLogOdds->strMotif );
		m_listLogOdds.SetItemDataPtr(count++, pLogOdds );
	}
}

void CLogOddsPropPage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	
    char tchBuffer[2048]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    stcLogOdds* pLogOdds;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_MOTIFLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 7;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pLogOdds = (stcLogOdds *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%s",  (const char *)pLogOdds->strName );
			
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
				pLogOdds->strName.GetLength(), 
				NULL
			);
			
			// Bingo ..
			m_listLogOdds.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 100; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			if ( pLogOdds->iEnabled ) {
				SetBkColor ( lpDrawItemStruct->hDC, pLogOdds->rgbBack );
				SetTextColor ( lpDrawItemStruct->hDC, pLogOdds->rgbText );
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
}

void CLogOddsPropPage::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
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


void CLogOddsPropPage::OnDblclkMotiflist() 
{
	// TODO: Add your control notification handler code here
	OnEdit();	
}

void CLogOddsPropPage::OnEdit() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}

	if ( (CurSel = m_listLogOdds.GetCurSel()) == LB_ERR ) {
		return;
	}
	
	CLogDlg tDlg;

	// CPtrList
	stcLogOdds* pLogOdds = (stcLogOdds *)m_listCopy.GetAt( m_listCopy.FindIndex( CurSel) );

	tDlg.m_Name = pLogOdds->strName;
	tDlg.m_Motif = pLogOdds->strMotif;
	tDlg.m_Descrip = pLogOdds->strDescrip;
	tDlg.m_Enabled = pLogOdds->iEnabled;
	tDlg.m_Bayes = pLogOdds->dLogOddsBayes;

	if ( tDlg.DoModal() != IDOK ) return;

	pLogOdds->strName = tDlg.m_Name;
	pLogOdds->strMotif = tDlg.m_Motif;
	pLogOdds->strDescrip = tDlg.m_Descrip;
	pLogOdds->iEnabled = tDlg.m_Enabled;
	pLogOdds->dLogOddsBayes = tDlg.m_Bayes;

	ReBuildListBox();	

	m_listLogOdds.Invalidate();

	m_LogOddsChanged = 1;
	
}

void CLogOddsPropPage::OnDelete() 
{

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) return;


	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listLogOdds.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		m_listLogOdds.DeleteString ( SeqSel );

		stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );
		m_listCopy.RemoveAt( m_listCopy.FindIndex( SeqSel) );
		delete [] pLogOdds->dLogOddsArr;
		delete pLogOdds;
	}

	m_listLogOdds.SelItemRange(FALSE, 0, m_listLogOdds.GetCount()-1 );

	delete SelArray;

	ReBuildListBox();
	m_listLogOdds.Invalidate();

	m_LogOddsChanged = 1;
	
}

void CLogOddsPropPage::OnTextcolor() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	if ( (CurSel = m_listLogOdds.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	stcLogOdds* pLogOdds = (stcLogOdds *)m_listLogOdds.GetItemDataPtr(CurSel);
	tDlg.m_cc.rgbResult = pLogOdds->rgbText;
	if ( tDlg.DoModal() == IDOK ) {

		int *SelArray = new int[SelCount];
		
		m_listLogOdds.GetSelItems( SelCount, SelArray );

		for ( int i=SelCount-1; i >=0; --i ) {

			int SeqSel = SelArray[i];
		
			stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

			pLogOdds->rgbText = tDlg.GetColor();
		}

		delete SelArray;

		m_listLogOdds.Invalidate();

		m_LogOddsChanged = 1;
	}
	
}

void CLogOddsPropPage::OnBackcolor() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}

	if ( (CurSel = m_listLogOdds.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	stcLogOdds* pLogOdds = (stcLogOdds *)m_listLogOdds.GetItemDataPtr(CurSel);
	tDlg.m_cc.rgbResult = pLogOdds->rgbBack;
	if ( tDlg.DoModal() == IDOK ) {
		int *SelArray = new int[SelCount];
		
		m_listLogOdds.GetSelItems( SelCount, SelArray );

		for ( int i=SelCount-1; i >=0; --i ) {

			int SeqSel = SelArray[i];
		
			stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

			pLogOdds->rgbBack = tDlg.GetColor();
		}

		delete SelArray;

		m_listLogOdds.Invalidate();

		m_LogOddsChanged = 1;
	}

}

void
CLogOddsPropPage::ColorCopyList()
{
	int count = m_listCopy.GetCount();
	if ( count < 2 ) return;
	int step = 255 / count;
	int red = 255;
	int green = 0;
	int blue = 0;

	POSITION tPos = m_listCopy.GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetNext(tPos);
		if ( pLogOdds->rgbBack == RGB(0,0,0) ) {
			pLogOdds->rgbBack = RGB(red, green, blue );
		}
		red -= step;
		blue += step;
		if ( red <= 0 ) {
			red = 0;
			blue = 255;
		}
	}
}

/*
void CLogOddsPropPage::OnMovedn() 
{

	int count = 0;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listLogOdds.GetSelItems( SelCount, SelArray );

	POSITION tPos = m_listCopy.GetHeadPosition();
	while (tPos != NULL ) {

		m_listCopy.GetNext(tPos);

		if ( ffirst == 0 ) {
			// Looking for first selected ...
			// CListBox
			if ( m_listLogOdds.GetSel(count) > 0 ) {
				FirstSel = count;
				ffirst = 1;
			}
		} else {
			if ( m_listLogOdds.GetSel(count) == 0 ) {
				stcLogOdds *tLogOdds;
				LastSel = count;
				CString tStr;
				m_listLogOdds.GetText ( count, tStr );
				tLogOdds = (stcLogOdds *)m_listLogOdds.GetItemDataPtr ( count );
				m_listLogOdds.DeleteString( count );
				m_listLogOdds.InsertString ( FirstSel, tStr );
				m_listLogOdds.SetItemDataPtr ( FirstSel, tLogOdds );

				POSITION tSPos = m_listCopy.FindIndex (count);
				tLogOdds = (stcLogOdds *)m_listCopy.GetAt(tSPos);
				m_listCopy.RemoveAt(tSPos);
				tSPos = m_listCopy.FindIndex (FirstSel);
				m_listCopy.InsertBefore ( tSPos, tLogOdds );

				break;
			}
		}
		count++;
	}

	if ( LastSel != -1 ) {
		m_listLogOdds.SelItemRange(FALSE, 0, m_listLogOdds.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] < LastSel ) {
				m_listLogOdds.SetSel( SelArray[i] + 1, TRUE );
			} else {
				m_listLogOdds.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;


//	ReBuildListBox();	

	m_listLogOdds.Invalidate();

	m_LogOddsChanged = 1;

}

void CLogOddsPropPage::OnMoveup() 
{
	int count = m_listLogOdds.GetCount() - 1;
	int ffirst = 0;
	int FirstSel;
	int LastSel = -1;
	
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_listLogOdds.GetSelItems( SelCount, SelArray );


	// Put the data rows on the list

	POSITION tPos = m_listCopy.GetTailPosition();
	while (tPos != NULL ) {

	
		m_listCopy.GetPrev(tPos);

		if ( ffirst == 0 ) {
			// Looking for first selected ...
			// CListBox
			if ( m_listLogOdds.GetSel(count) > 0 ) {
				FirstSel = count;
				ffirst = 1;
			}
		} else {
			if ( m_listLogOdds.GetSel(count) == 0 ) {
				LastSel = count;
				CString tStr;
				stcLogOdds *tLogOdds;
				m_listLogOdds.GetText ( count, tStr );
				tLogOdds = (stcLogOdds *)m_listLogOdds.GetItemDataPtr ( count );
				m_listLogOdds.DeleteString( count );
				if ( FirstSel == m_listLogOdds.GetCount() ) {
					m_listLogOdds.InsertString ( -1, tStr );
					m_listLogOdds.SetItemDataPtr ( FirstSel, tLogOdds );
				} else {
					m_listLogOdds.InsertString ( FirstSel, tStr );
					m_listLogOdds.SetItemDataPtr ( FirstSel, tLogOdds );
				}

				POSITION tSPos = m_listCopy.FindIndex (count);
				tLogOdds = (stcLogOdds *)m_listCopy.GetAt(tSPos);
				m_listCopy.RemoveAt (tSPos);
				tSPos = m_listCopy.FindIndex (FirstSel - 1);
				m_listCopy.InsertAfter ( tSPos, tLogOdds );

				break;
			}
		}
		count--;
	}

	if ( LastSel != -1 ) {
		m_listLogOdds.SelItemRange(FALSE, 0, m_listLogOdds.GetCount()-1 );
		for ( int i=0; i < SelCount; ++i ) {
			if ( SelArray[i] > LastSel ) {
				m_listLogOdds.SetSel( SelArray[i] - 1, TRUE );
			} else {
				m_listLogOdds.SetSel( SelArray[i], TRUE );
			}
		}
	}

    // CListBox
	delete SelArray;

	m_listLogOdds.Invalidate();

	m_LogOddsChanged = 1;

}
*/

void CLogOddsPropPage::OnOverlap() 
{
	// TODO: Add your control notification handler code here
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = m_OverlapColor;
	if ( tDlg.DoModal() == IDOK ) {
		m_OverlapColor = tDlg.GetColor();
		m_LogOddsChanged = 1;
	}
}


void CLogOddsPropPage::OnMeme() 
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, NULL, NULL, 0, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	// clear out old list.
	while ( !m_listCopy.IsEmpty() ) {
		stcLogOdds *ps = (stcLogOdds *)m_listCopy.RemoveHead();
		delete [] ps->dLogOddsArr;
		delete ps;
	}

	pDoc->BeginWaitCursor();

	if ( !pDoc->ScanMemeMotifs( tDlg.GetPathName(), &m_listCopy ) ) return;

#ifndef _WIN32
	m_strLogOddsFile = tDlg.GetFileTitle();
#else
	m_strLogOddsFile = tDlg.GetFileName();
#endif

	ColorCopyList();
	ReBuildListBox();
	Invalidate();
	UpdateData(FALSE);
	pDoc->EndWaitCursor();

	m_LogOddsChanged = 1;

	
}

void CLogOddsPropPage::OnSelchangeMotiflist() 
{
	// TODO: Add your control notification handler code here
	// CListbox
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	if ( SelCount > 1 ) {
		m_iEnabled = FALSE;
		UpdateData(FALSE);
		return;
	}
	           
	int SelArray;
	
	m_listLogOdds.GetSelItems( SelCount, &SelArray );

	stcLogOdds* pLogOdds = (stcLogOdds *)m_listLogOdds.GetItemDataPtr(SelArray);

	m_iEnabled = pLogOdds->iEnabled;

	UpdateData(FALSE);

}

void CLogOddsPropPage::OnEnabled() 
{
	// TODO: Add your control notification handler code here
	int SelCount = m_listLogOdds.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;

	int *SelArray = new int[SelCount];
	
	m_listLogOdds.GetSelItems( SelCount, SelArray );

	UpdateData();
	
	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];

		stcLogOdds *pLogOdds = (stcLogOdds *)m_listCopy.GetAt( m_listCopy.FindIndex( SeqSel) );

		pLogOdds->iEnabled = m_iEnabled;
	}

	delete SelArray;

	m_listLogOdds.Invalidate();

}


void CLogOddsPropPage::OnSelchangeOuttab() 
{
	// TODO: Add your control notification handler code here
	if ( m_ProjectType > 1 ) {

//		UpdateData();
		m_iLogOddsOutTab = m_cbOutTab.GetCurSel();

		switch ( m_iLogOddsOutTab ) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_dLogOddsStA = 250000;
			m_dLogOddsStC = 250000;
			m_dLogOddsStG = 250000;
			m_dLogOddsStT = 250000;
			break;
		case 6:
		case 7:
		case 8:
			m_dLogOddsStA = 244000;
			m_dLogOddsStC = 254000;
			m_dLogOddsStG = 263000;
			m_dLogOddsStT = 239000;
			break;
		}
		UpdateData(FALSE);
	}
}
