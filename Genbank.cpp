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
// genbank.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenbank dialog


CGenbank::CGenbank(CWnd* pParent /*=NULL*/)
	: CDialog(CGenbank::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenbank)
	m_Locus = 0;
	m_Trans = 0;
	//}}AFX_DATA_INIT
}

void CGenbank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenbank)
	DDX_Radio(pDX, IDC_LOCUS, m_Locus);
	DDX_Radio(pDX, IDC_TRANSLATION, m_Trans);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGenbank, CDialog)
	//{{AFX_MSG_MAP(CGenbank)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGenbank message handlers

BOOL CGenbank::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *pWnd = GetDlgItem( IDC_LOCUS );
	pWnd->SetWindowText( "LOCUS: " + LOCUS );
	
	pWnd = GetDlgItem( IDC_ACCESSION );
	pWnd->SetWindowText( "ACCESSION: " + ACCESSION );

	pWnd = GetDlgItem( IDC_NID );
	pWnd->SetWindowText( "NID: " + NID );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
