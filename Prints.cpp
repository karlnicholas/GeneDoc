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
// prints.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintProperty dialog


CPrintProperty::CPrintProperty() : CPropertyPage(CPrintProperty::IDD)
{
	//{{AFX_DATA_INIT(CPrintProperty)
	m_BottomBorder = 0;
	m_LeftBorder = 0;
	m_RightBorder = 0;
	m_TopBorder = 0;
	m_Orientation = -1;
	m_PrintFontPoints = "";
	m_PrintFontName = "";
	m_PrintFontWeight = "";
	m_PrintPage = -1;
	m_PrintPageOffset = 0;
	m_PrintString = "";
	m_GeneBlockPos = -1;
	m_PrintStringFlag = -1;
	m_PrintShading = FALSE;
	m_PrintFileName = FALSE;
	m_PrintDate = FALSE;
	//}}AFX_DATA_INIT
}

void CPrintProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintProperty)
	DDX_Text(pDX, IDC_BOTTOMBORDER, m_BottomBorder);
	DDX_Text(pDX, IDC_LEFTBORDER, m_LeftBorder);
	DDX_Text(pDX, IDC_RIGHTBORDER, m_RightBorder);
	DDX_Text(pDX, IDC_TOPBORDER, m_TopBorder);
	DDX_Radio(pDX, IDC_ORPORT, m_Orientation);
	DDX_Text(pDX, IDC_PRINTFONTPOINTS, m_PrintFontPoints);
	DDX_Text(pDX, IDC_PRINTFONTNAME, m_PrintFontName);
	DDX_Text(pDX, IDC_PRINTFONTWEIGHT, m_PrintFontWeight);
	DDX_Radio(pDX, IDC_PRINTPAGE0, m_PrintPage);
	DDX_Text(pDX, IDC_PRINTPAGEOFFSET, m_PrintPageOffset);
	DDX_Text(pDX, IDC_PRINTSTRING, m_PrintString);
	DDX_Radio(pDX, IDC_GENEBLOCKPOS0, m_GeneBlockPos);
	DDX_Radio(pDX, IDC_PRINTSTRINGFLAG0, m_PrintStringFlag);
	DDX_Check(pDX, IDC_PRINTSHADE, m_PrintShading);
	DDX_Check(pDX, IDC_PRINTFILENAME, m_PrintFileName);
	DDX_Check(pDX, IDC_PRINTDATE, m_PrintDate);
	//}}AFX_DATA_MAP
}

BOOL CPrintProperty::OnStyleClicked(UINT /*nCmdID*/)
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

BEGIN_MESSAGE_MAP(CPrintProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CPrintProperty)
	ON_EN_CHANGE(IDC_BOTTOMBORDER, OnChangeBottomborder)
	ON_EN_CHANGE(IDC_LEFTBORDER, OnChangeLeftborder)
	ON_EN_CHANGE(IDC_RIGHTBORDER, OnChangeRightborder)
	ON_EN_CHANGE(IDC_TOPBORDER, OnChangeTopborder)
	ON_BN_CLICKED(IDC_ORPORT, OnOrport)
	ON_BN_CLICKED(IDC_ORLAND, OnOrland)
	ON_BN_CLICKED(IDC_PRINTSTRINGFLAG0, OnPrintstringflag0)
	ON_BN_CLICKED(IDC_PRINTSTRINGFLAG1, OnPrintstringflag1)
	ON_BN_CLICKED(IDC_PRINTSTRINGFLAG2, OnPrintstringflag2)
	ON_BN_CLICKED(IDC_GENEBLOCKPOS0, OnGeneblockpos0)
	ON_BN_CLICKED(IDC_GENEBLOCKPOS1, OnGeneblockpos1)
	ON_BN_CLICKED(IDC_GENEBLOCKPOS2, OnGeneblockpos2)
	ON_BN_CLICKED(IDC_PRINTPAGE0, OnPrintpage0)
	ON_BN_CLICKED(IDC_PRINTPAGE1, OnPrintpage1)
	ON_BN_CLICKED(IDC_PRINTPAGE2, OnPrintpage2)
	ON_BN_CLICKED(IDC_PRINTPAGE3, OnPrintpage3)
	ON_BN_CLICKED(IDC_PRINTPAGE4, OnPrintpage4)
	ON_EN_CHANGE(IDC_PRINTSTRING, OnChangePrintstring)
	ON_BN_CLICKED(IDC_CHANGEPRINTFONT, OnChangeprintfont)
	ON_EN_CHANGE(IDC_PRINTPAGEOFFSET, OnChangePrintpageoffset)
	ON_BN_CLICKED(IDC_PRINTSHADE, OnPrintshade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPrintProperty message handlers


BOOL CPrintProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_PrintChanged = 0;
	
//	if ( m_AutoWidth == 0 ) {
//		SendDlgItemMessage ( IDC_EDITWIDTH, WM_ENABLE, (WPARAM)0, (LPARAM)0 );
//	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintProperty::OnChangeBottomborder() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;
}

void CPrintProperty::OnChangeLeftborder() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;
}

void CPrintProperty::OnChangeRightborder() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;
}

void CPrintProperty::OnChangeTopborder() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;
}

void CPrintProperty::OnOrport() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
}

void CPrintProperty::OnOrland() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintstringflag0()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintstringflag1()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintstringflag2()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnGeneblockpos0()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnGeneblockpos1()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnGeneblockpos2()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintpage0()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintpage1()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintpage2()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintpage3()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintpage4()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnChangePrintstring()
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnChangeprintfont()
{
	// TODO: Add your control notification handler code here
	// Pick up and other changed values.
	UpdateData(TRUE);

	LOGFONT lf;

	memset(&lf, 0, sizeof(LOGFONT));
	
	CDC*pDC = GetDC();

	int tPointSize;
	int tFontWeight;
	char tBuff[100];


	strncpy ( lf.lfFaceName, m_PrintFontName, sizeof(lf.lfFaceName) );

	if ( m_PrintFontWeight == "Normal" ) {
		tFontWeight = FW_NORMAL;
	} else {
		tFontWeight = FW_BOLD;
	}
	lf.lfWeight = tFontWeight;

	tPointSize = atoi ( m_PrintFontPoints );
	lf.lfHeight = -MulDiv( tPointSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);

	ReleaseDC(pDC);

	CFontDialog	tFDlg( &lf, CF_SCREENFONTS | CF_EFFECTS, NULL, this );

	if ( tFDlg.DoModal() != IDOK ) return;
	
	m_PrintFontName = tFDlg.GetFaceName();

	tPointSize = tFDlg.GetSize() / 10;
	itoa ( tPointSize, tBuff, 10 );
	m_PrintFontPoints = tBuff;

	tFontWeight = tFDlg.GetWeight();
	if ( tFontWeight == FW_NORMAL ) {
		m_PrintFontWeight = "Normal";
	} else {
		m_PrintFontWeight = "Bold";
	}

	UpdateData(FALSE);
	
	RedrawWindow();

	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnChangePrintpageoffset() 
{
	m_PrintChanged = 1;	
	
}

void CPrintProperty::OnPrintshade() 
{
	// TODO: Add your control notification handler code here
	m_PrintChanged = 1;	
}
