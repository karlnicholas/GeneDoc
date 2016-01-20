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
// colorbar.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorBar dialog


CColorBar::CColorBar(CWnd* pParent)
	: CDialog(CColorBar::IDD, pParent)
{
	m_pParent = pParent;
	//{{AFX_DATA_INIT(CColorBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CColorBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBar)
	DDX_Control(pDX, IDC_COLORLIST, m_ColorList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorBar, CDialog)
	//{{AFX_MSG_MAP(CColorBar)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	ON_LBN_DBLCLK(IDC_COLORLIST, OnDblclkColorlist)
	ON_BN_CLICKED(IDC_CHANGEBACK, OnChangeback)
	ON_BN_CLICKED(IDC_CHANGETEXT, OnChangetext)
	ON_LBN_SELCHANGE(IDC_COLORLIST, OnSelchangeColorlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorBar message handlers

BOOL CColorBar::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CGenedocDoc *pDoc = ((CGenedocView *)m_pParent)->GetDocument();
	
	int Levels = pDoc->GetNumColors(&pDoc->m_UserVars.m_Vars);
	PropertyStruct *pPS;
	
	for ( int i=0; i < Levels; ++i ) {
		pPS = new PropertyStruct;
		pPS->RowNum = i;
		pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, i, &pPS->TextColor, &pPS->BkColor );
		m_ColorList.AddString("GENE");
		m_ColorList.SetItemDataPtr ( i, pPS );
	}
	
	if ( Levels ) {
		m_ColorList.SetCurSel(m_ShadeLevel);
	}
	
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CColorBar::OnOK()
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();

	// m_ShadeLevel = m_ColorList.GetCurSel();
}


void CColorBar::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( (
		lpMeasureItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpMeasureItemStruct->CtlID == IDC_COLORLIST)
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	}

	// Was commented
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CColorBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	
    char tchBuffer[256]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    PropertyStruct * tPS;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_COLORLIST)
		&& (lpDrawItemStruct->itemID != -1)
		) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			tPS = (PropertyStruct *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%2d:", tPS->RowNum );
			
//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));
			
			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				3
			);
			
			m_ColorList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, tPS->BkColor );
			SetTextColor ( lpDrawItemStruct->hDC, tPS->TextColor );

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

	if ( nIDCtl == IDC_DISP ) {

		TEXTMETRIC m_TM;
		HGDIOBJ tFont;
		LOGFONT tLOGFONT;
		int tPointSize;
		int tFontWeight;
		memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

		CGenedocDoc *pDoc = ((CGenedocView *)m_pParent)->GetDocument();

		tFontWeight = pDoc->m_UserVars.m_FontWeight;
        
		tPointSize = pDoc->m_UserVars.m_FontSize;


		strcpy ( tLOGFONT.lfFaceName, "Courier New" );
		tLOGFONT.lfWeight = tFontWeight;
		tLOGFONT.lfHeight = -MulDiv( tPointSize , GetDeviceCaps(lpDrawItemStruct->hDC, LOGPIXELSY), 72);
        
		tFont = CreateFontIndirect( &tLOGFONT );
        
		HGDIOBJ oFont = SelectObject( lpDrawItemStruct->hDC, tFont);


		GetTextMetrics( lpDrawItemStruct->hDC, &m_TM );

		MoveToEx ( lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.left, 
			lpDrawItemStruct->rcItem.top, 
			NULL
		);

		LineTo ( lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.left, 
			lpDrawItemStruct->rcItem.bottom - 1 
		);

		LineTo ( lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.right - 1, 
			lpDrawItemStruct->rcItem.bottom - 1 
		);

		LineTo ( lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.right - 1, 
			lpDrawItemStruct->rcItem.top 
		);

		LineTo ( lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.left, 
			lpDrawItemStruct->rcItem.top 
		);
                
		int hx = (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / 2;
		int hy = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / 2;
		hx -= m_TM.tmAveCharWidth / 2;
		hy -= (m_TM.tmHeight - m_TM.tmInternalLeading) / 2;
                
		SetBkColor( lpDrawItemStruct->hDC, m_BackColor );
		SetTextColor( lpDrawItemStruct->hDC, m_TextColor );
		// RECT

		TextOut (
			lpDrawItemStruct->hDC, 
			lpDrawItemStruct->rcItem.left + hx, 
			lpDrawItemStruct->rcItem.top + hy, 
			"G", 1
		);
                

		if ( oFont != NULL ) {
			SelectObject( lpDrawItemStruct->hDC, oFont);
		}

	}

	// Was commented
	// CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}



void CColorBar::OnDestroy()
{
	int Count = m_ColorList.GetCount();
	for ( int i=0; i < Count; ++i ) {
		delete (PropertyStruct *)m_ColorList.GetItemDataPtr( i );
	}

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CColorBar::OnDblclkColorlist()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CColorBar::OnChangeback() 
{
	// TODO: Add your control notification handler code here
	CColorDialog    tDlg(m_BackColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	// m_ColorChanged = 1;
        
	m_BackColor = tDlg.GetColor();

	RedrawWindow();
	
}

void CColorBar::OnChangetext() 
{
	// TODO: Add your control notification handler code here
	CColorDialog    tDlg(m_TextColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	// m_ColorChanged = 1;
        
	m_TextColor = tDlg.GetColor();

	RedrawWindow();
	
	
}

void CColorBar::OnSelchangeColorlist() 
{
	// TODO: Add your control notification handler code here
	// OnSelectChange
	// CListBox

	if ( m_ColorList.GetCurSel() != LB_ERR ) {
		
		m_ShadeLevel = m_ColorList.GetCurSel();

		CGenedocDoc *pDoc = ((CGenedocView *)m_pParent)->GetDocument();

		pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, m_ShadeLevel, &m_TextColor, &m_BackColor );

		RedrawWindow();
	}
	
}
