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
// chemprop.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChemPropProperty dialog


//!            *ILVCAGMFYWHKREQDNSTP BZX**
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
//
//
//Yours:  Cystine: Reduced
//
//
//!            *ILVCAGMFYWHKREQDNSTP BZX**
//     Proline:                    P   X -
//     Glycine:      G                 X -
//        Tiny:    CAG           S     X -
//       Small:   V AG         DNSTP   X -
//    Positive:           HKR          X -
//    Negative:              E D       X -
//     Charged:           HKRE D       X -
//  Amphoteric:           H REQDN    BZX -
//       Polar:    C    YWHKREQDNST  BZX -
//   Aliphatic: ILV A                  X -
//    Aromatic:        FYWH            X -
// Hydrophobic: ILVCAGMFYWH       TP   X -


// Changed per Dad

//!            *ILVCAGMFYWHKREQDNSTP BZX**
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
//
//
//Yours:  Cystine: Reduced
//
//
//!            *ILVCAGMFYWHKREQDNSTP BZX**
//     Proline:                    P   X -
//     Glycine:      G                 X -
//        Tiny:    CAG           S     X -
//       Small:   V AG         DNSTP   X -
//    Positive:           HKR          X -
//    Aromatic:        FYWH            X -
//    Negative:              E D       X -
//     Charged:           HKRE D       X -
//  Amphoteric:           H REQDN    BZX -
//       Polar:    C    YWHKREQDNST  BZX -
//   Aliphatic: ILV A                  X -
// Hydrophobic: ILVCAGMFYWH       TP   X -


CChemPropProperty::CChemPropProperty(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CChemPropProperty::IDD)
{
	//{{AFX_DATA_INIT(CChemPropProperty)
	m_Cysteine = -1;
	m_ShowProperty = -1;
	m_PropEnable = FALSE;
	//}}AFX_DATA_INIT
}

void CChemPropProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChemPropProperty)
	DDX_Control(pDX, IDC_CHEMPROP, m_ChemPropList);
	DDX_Control(pDX, IDC_PROPCONS, m_PropConsList);
	DDX_Radio(pDX, IDC_CYSTEINE, m_Cysteine);
	DDX_Radio(pDX, IDC_SHOWPROPERTY, m_ShowProperty);
	DDX_Check(pDX, IDC_PROPENAB, m_PropEnable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChemPropProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CChemPropProperty)
	ON_BN_CLICKED(IDC_CHEMPROPBACK, OnChempropback)
	ON_BN_CLICKED(IDC_CHEMPROPFORE, OnChempropfore)
	ON_BN_CLICKED(IDC_PROPCONSBACK, OnPropconsback)
	ON_BN_CLICKED(IDC_PROPCONSFORE, OnPropconsfore)
	ON_LBN_DBLCLK(IDC_CHEMPROP, OnDblclkChemprop)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CYSTEINE, OnCysteine)
	ON_BN_CLICKED(IDC_REDUCED, OnReduced)
	ON_BN_CLICKED(IDC_PROPENAB, OnPropenab)
	ON_LBN_SELCHANGE(IDC_CHEMPROP, OnSelchangeChemprop)
	ON_BN_CLICKED(IDC_DESCRIPTION, OnDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChemPropProperty message handlers

BOOL CChemPropProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();

	m_ButPropEnab = (CButton *)GetDlgItem(IDC_PROPENAB);

	// CListBox
	m_ChemPropList.AddString("Proline" );
	m_ChemPropList.SetItemDataPtr(0, &ChemGroup[0] );
	m_ChemPropList.AddString("Glycine" );
	m_ChemPropList.SetItemDataPtr(1, &ChemGroup[1] );
	m_ChemPropList.AddString("Tiny" );
	m_ChemPropList.SetItemDataPtr(2, &ChemGroup[2] );
	m_ChemPropList.AddString("Small" );
	m_ChemPropList.SetItemDataPtr(3, &ChemGroup[3] );
	m_ChemPropList.AddString("Positive" );
	m_ChemPropList.SetItemDataPtr(4, &ChemGroup[4] );
	m_ChemPropList.AddString("Aromatic" );
	m_ChemPropList.SetItemDataPtr(5, &ChemGroup[5] );
	m_ChemPropList.AddString("Negative" );
	m_ChemPropList.SetItemDataPtr(6, &ChemGroup[6] );
	m_ChemPropList.AddString("Charged" );
	m_ChemPropList.SetItemDataPtr(7, &ChemGroup[7] );
	m_ChemPropList.AddString("Amphoteric" );
	m_ChemPropList.SetItemDataPtr(8, &ChemGroup[8] );
	m_ChemPropList.AddString("Polar" );
	m_ChemPropList.SetItemDataPtr(9, &ChemGroup[9] );
	m_ChemPropList.AddString("Aliphatic" );
	m_ChemPropList.SetItemDataPtr(10, &ChemGroup[10] );
	m_ChemPropList.AddString("Hydrophobic" );
	m_ChemPropList.SetItemDataPtr(11, &ChemGroup[11] );

	m_PropConsList.AddString("Column Ident.");
	m_PropConsList.SetItemDataPtr(0, &ChemCons[0] );
	m_PropConsList.AddString("Group Ident.");
	m_PropConsList.SetItemDataPtr(1, &ChemCons[1] );
	m_PropConsList.AddString("Group Cons.");
	m_PropConsList.SetItemDataPtr(2, &ChemCons[2] );


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChemPropProperty::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
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

void CChemPropProperty::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
    char tchBuffer[256]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    stcChemProp* tCP;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_CHEMPROP)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			tCP = (stcChemProp *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%2d:",  lpDrawItemStruct->itemID + 1 );
			
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
			m_ChemPropList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, tCP->BackColor );
			SetTextColor ( lpDrawItemStruct->hDC, tCP->TextColor );

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
	
	} else if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_PROPCONS)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			tCP = (stcChemProp *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%2d:",  lpDrawItemStruct->itemID + 1 );
			
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
			m_PropConsList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, tCP->BackColor );
			SetTextColor ( lpDrawItemStruct->hDC, tCP->TextColor );

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

	// TODO: Add your control notification handler code here
//	CColorDialog tDlg;
//	tDlg.m_cc.Flags |= CC_RGBINIT;
//	tDlg.m_cc.rgbResult = ChemGroup[10].TextColor;
//	if ( tDlg.DoModal() == IDOK ) {
//		ChemGroup[10].TextColor = tDlg.GetColor();
//		pDoc->m_UserVars.ChemGroupRed[10].BackColor = tDlg.GetColor();
//	}



void CChemPropProperty::OnChempropback() 
{
	// TODO: Add your control notification handler code here
	// CListBox	
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = ChemGroup[CurSel].BackColor;
	if ( tDlg.DoModal() == IDOK ) {
		ChemGroup[CurSel].BackColor = tDlg.GetColor();
	}

	m_ChemPropList.Invalidate();
}

void CChemPropProperty::OnChempropfore() 
{
	// TODO: Add your control notification handler code here
	// CListBox	
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = ChemGroup[CurSel].TextColor;
	if ( tDlg.DoModal() == IDOK ) {
		ChemGroup[CurSel].TextColor = tDlg.GetColor();
	}

	m_ChemPropList.Invalidate();
}

void CChemPropProperty::OnPropconsback() 
{
	// TODO: Add your control notification handler code here
	// CListBox	
	int CurSel;
	if ( (CurSel = m_PropConsList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = ChemCons[CurSel].BackColor;
	if ( tDlg.DoModal() == IDOK ) {
		ChemCons[CurSel].BackColor = tDlg.GetColor();
	}

	m_PropConsList.Invalidate();
}

void CChemPropProperty::OnPropconsfore() 
{
	// TODO: Add your control notification handler code here
	// CListBox	
	int CurSel;
	if ( (CurSel = m_PropConsList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	// CPtrArray
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = ChemCons[CurSel].TextColor;
	if ( tDlg.DoModal() == IDOK ) {
		ChemCons[CurSel].TextColor = tDlg.GetColor();
	}

	m_PropConsList.Invalidate();
}

void CChemPropProperty::OnDblclkChemprop() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	ChemPropEnabled[CurSel] = !ChemPropEnabled[CurSel];

//	m_ChemPropList.Invalidate();
	m_ButPropEnab->SetCheck( ChemPropEnabled[CurSel] % 2 );

	m_ButPropEnab->Invalidate();
}



void CChemPropProperty::OnCysteine() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
}

void CChemPropProperty::OnReduced() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}


void CChemPropProperty::OnPropenab() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	ChemPropEnabled[CurSel] = !ChemPropEnabled[CurSel];

//	m_ChemPropList.Invalidate();
	
}

void CChemPropProperty::OnSelchangeChemprop() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		return;
	}
	
	m_ButPropEnab->SetCheck( ChemPropEnabled[CurSel] % 2 );

	m_ButPropEnab->Invalidate();
	
}

void CChemPropProperty::OnDescription() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ChemPropList.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select Property" );
		return;
	}
	
	char Message[128];
	if ( !m_Cysteine ) {
		_snprintf ( Message, 127, "PhysioChem Prop Members: %s\n*** Oxidized Cysteine", ChemGroup[CurSel].Chem );
	} else {
		_snprintf ( Message, 127, "PhysioChem Prop Members: %s\n*** Reduced Cysteine", ChemGroupRed[CurSel].Chem );
	}

	AfxMessageBox( Message );
	
}
