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
// refiltdl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReFiltDlg dialog


CReFiltDlg::CReFiltDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReFiltDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReFiltDlg)
	m_Exclude = _T("");
	m_Include = _T("");
	m_Maxlen = 0;
	m_Minlen = 0;
	m_NonAmbig = FALSE;
	m_Palin = FALSE;
	m_Occur = 0;
	m_ExclDup = FALSE;
	//}}AFX_DATA_INIT
}

void CReFiltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReFiltDlg)
	DDX_Text(pDX, IDC_EXCLUDE, m_Exclude);
	DDX_Text(pDX, IDC_INCLUDE, m_Include);
	DDX_Text(pDX, IDC_MAXLEN, m_Maxlen);
	DDX_Text(pDX, IDC_MINLEN, m_Minlen);
	DDX_Check(pDX, IDC_NONAMBIG, m_NonAmbig);
	DDX_Check(pDX, IDC_PALIN, m_Palin);
	DDX_Text(pDX, IDC_OCCUR, m_Occur);
	DDX_Check(pDX, IDC_EXCLDUP, m_ExclDup);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReFiltDlg, CDialog)
	//{{AFX_MSG_MAP(CReFiltDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReFiltDlg message handlers
