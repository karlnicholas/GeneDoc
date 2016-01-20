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
// RepDlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepDlg dialog

CRepDlg::CRepDlg() : CPropertyPage(CRepDlg::IDD)
{
	//{{AFX_DATA_INIT(CRepDlg)
	m_RepExactMatch = TRUE;
	m_RepJuxtaposition = TRUE;
	m_RepAlignedGaps = TRUE;
	m_RepAbsoluteVal = TRUE;
	m_RepPercentVal = TRUE;
	m_RepOutMatrix = 0;
	m_RepLabelSingle = 0;
	m_RepLabelTop = 0;
	m_RepIncAA = TRUE;
	//}}AFX_DATA_INIT
}

void CRepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRepDlg)
	DDX_Check(pDX, IDC_EXACTMATCH, m_RepExactMatch);
	DDX_Check(pDX, IDC_JUXTAPOSITION, m_RepJuxtaposition);
	DDX_Check(pDX, IDC_ALIGNEDGAPS, m_RepAlignedGaps);
	DDX_Check(pDX, IDC_ABSOLUTEVAL, m_RepAbsoluteVal);
	DDX_Check(pDX, IDC_PERCENTVAL, m_RepPercentVal);
	DDX_Radio(pDX, IDC_OUTMATRIX, m_RepOutMatrix);
	DDX_Radio(pDX, IDC_LABELSINGLE, m_RepLabelSingle);
	DDX_Radio(pDX, IDC_LABELTOP, m_RepLabelTop);
	DDX_Check(pDX, IDC_INC_AA, m_RepIncAA);
	//}}AFX_DATA_MAP
}

BOOL CRepDlg::OnStyleClicked(UINT /*nCmdID*/)
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

BEGIN_MESSAGE_MAP(CRepDlg, CDialog)
	//{{AFX_MSG_MAP(CRepDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRepDlg message handlers

BOOL CRepDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
