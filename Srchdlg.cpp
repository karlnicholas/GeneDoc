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
// srchdlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrchDlg dialog


CSrchDlg::CSrchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrchDlg)
	m_Descrip = _T("");
	m_Motif = _T("");
	m_Name = _T("");
	m_iEnabled = TRUE;
	//}}AFX_DATA_INIT
}

void CSrchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrchDlg)
	DDX_Text(pDX, IDC_DECRIP, m_Descrip);
	DDX_Text(pDX, IDC_MOTIF, m_Motif);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Check(pDX, IDC_ENABLED, m_iEnabled);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrchDlg, CDialog)
	//{{AFX_MSG_MAP(CSrchDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSrchDlg message handlers
