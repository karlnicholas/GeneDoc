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
// proped.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditDlg dialog


CPropertyEditDlg::CPropertyEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertyEditDlg)
	m_PropCont = "";
	m_PropNum = "";
	//}}AFX_DATA_INIT
}

void CPropertyEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyEditDlg)
	DDX_Text(pDX, IDC_PROPEDITCONT, m_PropCont);
	DDX_Text(pDX, IDC_PROPEDITNUM, m_PropNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertyEditDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertyEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropertyEditDlg message handlers
