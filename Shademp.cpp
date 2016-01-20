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
// ShadeModep.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShadeModeProperty dialog


CShadeModeProperty::CShadeModeProperty() : CPropertyPage(CShadeModeProperty::IDD)
{
	m_DialogInited = 0;
	//{{AFX_DATA_INIT(CShadeModeProperty)
	m_ModeConserved = -1;
	m_PrimaryLevel = 0.0;
	m_SecondaryLevel = 0.0;
	m_TertiaryLevel = 0.0;
	m_DiffMode = -1;
	m_ResidueMode = -1;
	m_ShadeLevel = -1;
	m_GroupEnabled = FALSE;
	m_ConsSubStyle = -1;
	//}}AFX_DATA_INIT
}

void CShadeModeProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShadeModeProperty)
	DDX_Radio(pDX, IDC_MODECONSERVED, m_ModeConserved);
	DDX_Text(pDX, IDC_STRPRIM, m_PrimaryLevel);
	DDV_MinMaxDouble(pDX, m_PrimaryLevel, 0., 100.);
	DDX_Text(pDX, IDC_STRSEC, m_SecondaryLevel);
	DDV_MinMaxDouble(pDX, m_SecondaryLevel, 0., 100.);
	DDX_Text(pDX, IDC_STRTERT, m_TertiaryLevel);
	DDV_MinMaxDouble(pDX, m_TertiaryLevel, 0., 100.);
	DDX_Radio(pDX, IDC_DIFFCONSENSUS, m_DiffMode);
	DDX_Radio(pDX, IDC_RESDISPNORMAL, m_ResidueMode);
	DDX_Radio(pDX, IDC_SHADELEVEL0, m_ShadeLevel);
	DDX_Check(pDX, IDC_GENEGROUPENABLED, m_GroupEnabled);
	DDX_Radio(pDX, IDC_CONSSUBIDENT, m_ConsSubStyle);
	//}}AFX_DATA_MAP
}

BOOL CShadeModeProperty::OnStyleClicked(UINT /*nCmdID*/)
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
//		((CModalShadeModePropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CShadeModeProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CShadeModeProperty)
	ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDC_CHANGEBACK0, OnChangeback0)
    ON_BN_CLICKED(IDC_CHANGEBACK100, OnChangeback100)
    ON_BN_CLICKED(IDC_CHANGEBACK60, OnChangeback60)
    ON_BN_CLICKED(IDC_CHANGEBACK80, OnChangeback80)
    ON_BN_CLICKED(IDC_CHANGEFORE0, OnChangefore0)
    ON_BN_CLICKED(IDC_CHANGEFORE100, OnChangefore100)
    ON_BN_CLICKED(IDC_CHANGEFORE60, OnChangefore60)
    ON_BN_CLICKED(IDC_CHANGEFORE80, OnChangefore80)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShadeModeProperty message handlers
BOOL CShadeModeProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_DialogInited = 1;
	// TODO: Add extra initialization here
	ResetData();

	// CListBox	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void 
CShadeModeProperty::ResetData()
{
	if ( m_DialogInited ) UpdateData(FALSE);
}
	

void CShadeModeProperty::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
        // TODO: Add your message handler code here and/or call default

        if ( 
                nIDCtl == IDC_100DISP 
                || nIDCtl == IDC_80DISP 
                || nIDCtl == IDC_60DISP 
                || nIDCtl == IDC_0DISP 
        ) {

                TEXTMETRIC m_TM;
                HGDIOBJ tFont;
                LOGFONT tLOGFONT;
                memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

                strcpy ( tLOGFONT.lfFaceName, "Courier New" );
                tLOGFONT.lfWeight = m_FontWeight;
                tLOGFONT.lfHeight = -MulDiv( m_FontSize, GetDeviceCaps(lpDrawItemStruct->hDC, LOGPIXELSY), 72);
        
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
                
                if ( nIDCtl == IDC_100DISP ) {
                        SetBkColor( lpDrawItemStruct->hDC, m_BackColor100 );
                        SetTextColor( lpDrawItemStruct->hDC, m_ForeColor100 );
                } else if ( nIDCtl == IDC_80DISP ) {
                        SetBkColor( lpDrawItemStruct->hDC, m_BackColor80 );
                        SetTextColor( lpDrawItemStruct->hDC, m_ForeColor80 );
                } else if ( nIDCtl == IDC_60DISP ) {
                        SetBkColor( lpDrawItemStruct->hDC, m_BackColor60 );
                        SetTextColor( lpDrawItemStruct->hDC, m_ForeColor60 );
                } else if ( nIDCtl == IDC_0DISP ) {
                        SetBkColor( lpDrawItemStruct->hDC, m_BackColor0 );
                        SetTextColor( lpDrawItemStruct->hDC, m_ForeColor0 );
                }
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

        CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CShadeModeProperty::OnChangeback0() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_BackColor0);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_BackColor0 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangeback100() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_BackColor100);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_BackColor100 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangeback60() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_BackColor60);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_BackColor60 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangeback80() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_BackColor80);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_BackColor80 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangefore0() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_ForeColor0);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_ForeColor0 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangefore100() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_ForeColor100);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_ForeColor100 = tDlg.GetColor();

        RedrawWindow();
        
}

void CShadeModeProperty::OnChangefore60() 
{
        // TODO: Add your control notification handler code here
        
        CColorDialog    tDlg(m_ForeColor60);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_ForeColor60 = tDlg.GetColor();

        RedrawWindow();
}

void CShadeModeProperty::OnChangefore80() 
{
        // TODO: Add your control notification handler code here
        CColorDialog    tDlg(m_ForeColor80);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        m_ForeColor80 = tDlg.GetColor();

        RedrawWindow();
        
}

