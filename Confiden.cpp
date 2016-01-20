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
// confiden.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfIdent dialog


CConfIdent::CConfIdent():CPropertyPage(CConfIdent::IDD)
{
	m_DialogInited = 0;
	m_ModifyAll = 0;
	//{{AFX_DATA_INIT(CConfIdent)
	m_IdentDisplayStyle = -1;
	//}}AFX_DATA_INIT
}

void CConfIdent::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfIdent)
	DDX_Control(pDX, IDC_TEXTCOLOR, m_TextButton);
	DDX_Control(pDX, IDC_BACKCOLOR, m_BackButton);
	DDX_Control(pDX, IDC_LISTSEQUENCE, m_listSequence);
	DDX_Radio(pDX, IDC_SHOWALL, m_IdentDisplayStyle);
	//}}AFX_DATA_MAP
}

BOOL CConfIdent::OnStyleClicked(UINT /*nCmdID*/)
{
	// The CStylePage property page is used for both the
	// CModalShapePropSheet and the CModelessShapePropSheet.
	// Both these versions of the property sheet share a common
	// feature that they immediately update a shape.  In the
	// case of CModalShapePropSheet, the shape is in the preview
	// window.  In the case of CModelessShapePropSheet, the shape
	// is the currently selected shape in the view.

	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();

	if (pPropertySheet->IsKindOf(RUNTIME_CLASS(CModalDisplayPropSheet)))
	{
		UpdateData();
//		((CModalDisplayPropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CConfIdent, CPropertyPage)
	//{{AFX_MSG_MAP(CConfIdent)
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_BN_CLICKED(IDC_TEXTCOLOR, OnTextcolor)
	ON_LBN_DBLCLK(IDC_LISTSEQUENCE, OnDblclkListsequence)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_TOGGLE, OnToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfIdent message handlers

void CConfIdent::OnBackcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = m_rgbBack;
	if ( tDlg.DoModal() == IDOK ) {
		m_rgbBack = tDlg.GetColor();
	}

	m_listSequence.Invalidate();
	
}

void CConfIdent::OnTextcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog tDlg;
	tDlg.m_cc.Flags |= CC_RGBINIT;
	tDlg.m_cc.rgbResult = m_rgbText;
	if ( tDlg.DoModal() == IDOK ) {
		m_rgbText = tDlg.GetColor();
	}

	m_listSequence.Invalidate();
	
}

void CConfIdent::OnDblclkListsequence() 
{
	// TODO: Add your control notification handler code here
	int Sel = m_listSequence.GetCurSel();
	if ( Sel == LB_ERR ) return;
	CString Seg;
	char * pc = Seg.GetBuffer(128);
	m_listSequence.GetText( Sel, pc );
	Seg.ReleaseBuffer();
	int f=0;
	POSITION tPos = m_IdentList.GetHeadPosition();
	CGeneSegment *tCGSeg;
	while ( tPos != NULL ) {
		tCGSeg = (CGeneSegment *)m_IdentList.GetNext(tPos);
		if ( tCGSeg->GetTitle() == Seg ) {
			f = 1;
			break;
		}
	}

	if ( f ) {
		tPos = m_IdentList.Find( tCGSeg );
		m_IdentList.RemoveAt(tPos);
	} else {
		tPos = m_SegList.GetHeadPosition();
		while ( tPos != NULL ) {
			tCGSeg = (CGeneSegment *)m_SegList.GetNext(tPos);
			if ( tCGSeg->GetTitle() == Seg ) {
				m_IdentList.AddTail( tCGSeg );
				break;
			}
		}
	}

	m_listSequence.SetCurSel(-1);
	m_listSequence.Invalidate();
}

BOOL CConfIdent::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DialogInited = 1;

	ResetData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfIdent::ResetData()
{
	if ( !m_DialogInited) return;

	m_listSequence.ResetContent();
	POSITION tPos = m_SegList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)m_SegList.GetNext(tPos);
		int pos = m_listSequence.AddString(tCGSeg->GetTitle());
		m_listSequence.SetItemDataPtr(pos, tCGSeg);
	}

	if ( m_ModifyAll ) {
		m_listSequence.EnableWindow(FALSE);
		m_BackButton.EnableWindow(FALSE);
		m_TextButton.EnableWindow(FALSE);
	} else {
		m_listSequence.EnableWindow(TRUE);
		m_BackButton.EnableWindow(TRUE);
		m_TextButton.EnableWindow(TRUE);
	}

	if ( m_DialogInited ) UpdateData(FALSE);
}

void CConfIdent::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
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

void CConfIdent::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
    char tchBuffer[256]; 
    RECT rect;
    int i, f;
    CGeneSegment* pCGSeg;
	POSITION tPos;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_LISTSEQUENCE)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pCGSeg = (CGeneSegment*)lpDrawItemStruct->itemData;

			f = 0;
			tPos = m_IdentList.GetHeadPosition();
			while ( tPos != NULL ) {
				CGeneSegment *tCGSeg = (CGeneSegment*)m_IdentList.GetNext(tPos);
				if ( pCGSeg == tCGSeg ) {
					f = 1;
					break;
				}
			}

			if ( f ) {
				SetBkColor ( lpDrawItemStruct->hDC, m_rgbBack );
				SetTextColor ( lpDrawItemStruct->hDC, m_rgbText );
			} else {
				SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
				SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );
			}

			// Bingo ..
			m_listSequence.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen(tchBuffer); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);
			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.right; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 

			break;
 
		case ODA_SELECT:
 
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.right; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);
			
			break; 
		}
	
	}

//	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CConfIdent::OnToggle() 
{
	// TODO: Add your control notification handler code here
	int Sel = m_listSequence.GetCurSel();
	if ( Sel == LB_ERR ) {
		AfxMessageBox("Please Select a Sequence" );
		return;
	}
	CString Seg;
	char * pc = Seg.GetBuffer(128);
	m_listSequence.GetText( Sel, pc );
	Seg.ReleaseBuffer();
	int f=0;
	POSITION tPos = m_IdentList.GetHeadPosition();
	CGeneSegment *tCGSeg;
	while ( tPos != NULL ) {
		tCGSeg = (CGeneSegment *)m_IdentList.GetNext(tPos);
		if ( tCGSeg->GetTitle() == Seg ) {
			f = 1;
			break;
		}
	}

	if ( f ) {
		tPos = m_IdentList.Find( tCGSeg );
		m_IdentList.RemoveAt(tPos);
	} else {
		tPos = m_SegList.GetHeadPosition();
		while ( tPos != NULL ) {
			tCGSeg = (CGeneSegment *)m_SegList.GetNext(tPos);
			if ( tCGSeg->GetTitle() == Seg ) {
				m_IdentList.AddTail( tCGSeg );
				break;
			}
		}
	}

	m_listSequence.SetCurSel(-1);
	m_listSequence.Invalidate();
	
}
