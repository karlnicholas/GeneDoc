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
// showtabl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowTableDialog dialog


CShowTableDialog::CShowTableDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShowTableDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowTableDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CShowTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowTableDialog)
	DDX_Control(pDX, IDC_SHOWEDIT, m_ShowEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowTableDialog, CDialog)
	//{{AFX_MSG_MAP(CShowTableDialog)
	ON_BN_CLICKED(IDC_SHOWTABLECOPY, OnShowtablecopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShowTableDialog message handlers

BOOL CShowTableDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ShowEdit.SetWindowText(m_ShowEditString);
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShowTableDialog::OnShowtablecopy()
{
	// TODO: Add your control notification handler code here
	
	m_ShowEdit.SetSel(0,-1);
	m_ShowEdit.Copy();
	
}
