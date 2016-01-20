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
// pdbdialo.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDBDialog dialog


CPDBDialog::CPDBDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPDBDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPDBDialog)
	m_ClearAll = TRUE;
	m_IncludeBase = TRUE;
	m_SafeMode = TRUE;
	m_PDBOffset = 0;
	m_DispSidechain = FALSE;
	m_SideDisp = _T("Ball&Stick");
	m_ComboBack = _T("Cartoon");
	m_ShadeWhich = 0;
	m_ExcludeO = FALSE;
	m_GroupSel = TRUE;
	//}}AFX_DATA_INIT
}

void CPDBDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPDBDialog)
	DDX_Control(pDX, IDC_SIDECOLORLIST, m_SideColorList);
	DDX_Check(pDX, IDC_CLEARALL, m_ClearAll);
	DDX_Check(pDX, IDC_INCLUDEBASE, m_IncludeBase);
	DDX_Check(pDX, IDC_SAFEMODE, m_SafeMode);
	DDX_Text(pDX, IDC_PDBOFFSET, m_PDBOffset);
	DDX_Check(pDX, IDC_DISPSIDE, m_DispSidechain);
	DDX_CBString(pDX, IDC_SIDEDISP, m_SideDisp);
	DDX_CBString(pDX, IDC_COMBOBACK, m_ComboBack);
	DDX_Radio(pDX, IDC_ALL, m_ShadeWhich);
	DDX_Check(pDX, IDC_EXCLUDEO, m_ExcludeO);
	DDX_Check(pDX, IDC_GROUPSEL, m_GroupSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPDBDialog, CDialog)
	//{{AFX_MSG_MAP(CPDBDialog)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_DISPSIDE, OnDispside)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPDBDialog message handlers


BOOL CPDBDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	POSITION tPos = m_ColorList.GetHeadPosition();
	while ( tPos != NULL ) {
		stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)m_ColorList.GetNext(tPos);
		int at = m_SideColorList.AddString("GeneDoc");
		m_SideColorList.SetItemDataPtr( at, pPDBC );
	}
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_COMBOBACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIDEDISP)->EnableWindow(FALSE);
	m_SideColorList.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPDBDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	// TODO: Add your message handler code here and/or call default
    char tchBuffer[256]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    stcPDBCOLOR* pPDBC;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_SIDECOLORLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pPDBC = (stcPDBCOLOR *)lpDrawItemStruct->itemData;

			strcpy ( tchBuffer, "    " );
			
//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));
			
			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				3
			);
			
			// Bingo ..
			m_SideColorList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, pPDBC->rgbBack );
			SetTextColor ( lpDrawItemStruct->hDC, pPDBC->rgbText );

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

//	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CPDBDialog::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
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


void CPDBDialog::OnOK() 
{
	// TODO: Add extra validation here
	CPtrList tList;
	CPtrList dList;
	int i;
	int *SelArray;

	int SelCount = m_SideColorList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) goto Out;
	           
	SelArray = new int[SelCount];
	
	m_SideColorList.GetSelItems( SelCount, SelArray );

	for ( i=0; i < SelCount; ++i ) {
		int SeqSel = SelArray[i];
		POSITION tPos = m_ColorList.FindIndex (SeqSel);
		stcPDBCOLOR* oPDBC = (stcPDBCOLOR*)m_ColorList.GetAt( tPos );
		stcPDBCOLOR* pPDBC = new stcPDBCOLOR;
		pPDBC->rgbText = oPDBC->rgbText;
		pPDBC->rgbBack = oPDBC->rgbBack;
		tList.AddTail( pPDBC );
	}

	delete SelArray;

Out:
	while ( !m_ColorList.IsEmpty() ) {
		delete (stcPDBCOLOR*) m_ColorList.RemoveHead();
	}

	// CPtrList
	while ( !tList.IsEmpty() ) {
		m_ColorList.AddTail( tList.RemoveHead() );
	}

	CDialog::OnOK();

	
}

void CPDBDialog::OnDispside() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if ( m_DispSidechain ) {
		GetDlgItem(IDC_COMBOBACK)->EnableWindow(TRUE);
		GetDlgItem(IDC_SIDEDISP)->EnableWindow(TRUE);
		m_SideColorList.EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_COMBOBACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIDEDISP)->EnableWindow(FALSE);
		m_SideColorList.EnableWindow(FALSE);
	}
}
