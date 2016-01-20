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
// htmlpicd.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTMLPicDlg dialog


CHTMLPicDlg::CHTMLPicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHTMLPicDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHTMLPicDlg)
	m_HTMLType = 0;
	m_FullWeb = 0;
	//}}AFX_DATA_INIT
}

void CHTMLPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTMLPicDlg)
	DDX_Radio(pDX, IDC_FULLTABLE, m_HTMLType);
	DDX_Radio(pDX, IDC_FULLWEB, m_FullWeb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHTMLPicDlg, CDialog)
	//{{AFX_MSG_MAP(CHTMLPicDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHTMLPicDlg message handlers
