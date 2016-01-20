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
// titlingf.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitlingFDialog dialog


CTitlingFDialog::CTitlingFDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTitlingFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitlingFDialog)
	m_ExtendGap = "";
	m_OpenGap = "";
	m_Program = "";
	m_ScoreMatrix = "";
	//}}AFX_DATA_INIT
}

void CTitlingFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitlingFDialog)
	DDX_Control(pDX, IDC_TITLEEDIT, m_CommentEdit);
	DDX_Text(pDX, IDC_TITLEEXTENDGAP, m_ExtendGap);
	DDV_MaxChars(pDX, m_ExtendGap, 20);
	DDX_Text(pDX, IDC_TITLEOPENGAP, m_OpenGap);
	DDV_MaxChars(pDX, m_OpenGap, 20);
	DDX_Text(pDX, IDC_TITLEPROGRAM, m_Program);
	DDV_MaxChars(pDX, m_Program, 20);
	DDX_Text(pDX, IDC_TITLESCORE, m_ScoreMatrix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTitlingFDialog, CDialog)
	//{{AFX_MSG_MAP(CTitlingFDialog)
	ON_EN_CHANGE(IDC_TITLEEDIT, OnChangeTitleedit)
	ON_EN_CHANGE(IDC_TITLEEXTENDGAP, OnChangeTitleextendgap)
	ON_EN_CHANGE(IDC_TITLEOPENGAP, OnChangeTitleopengap)
	ON_EN_CHANGE(IDC_TITLEPROGRAM, OnChangeTitleprogram)
	ON_EN_CHANGE(IDC_TITLESCORE, OnChangeTitlescore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTitlingFDialog message handlers

void CTitlingFDialog::OnChangeTitleedit()
{
	// TODO: Add your control notification handler code here
	m_CTChanged = 1;
}

void CTitlingFDialog::OnChangeTitleextendgap()
{
	// TODO: Add your control notification handler code here
	m_ICChanged = 1;
}

void CTitlingFDialog::OnChangeTitleopengap()
{
	// TODO: Add your control notification handler code here
	m_ICChanged = 1;
	
}

void CTitlingFDialog::OnChangeTitleprogram()
{
	// TODO: Add your control notification handler code here
	m_ICChanged = 1;
	
}

void CTitlingFDialog::OnChangeTitlescore()
{
	// TODO: Add your control notification handler code here
	m_ICChanged = 1;
	
}

BOOL CTitlingFDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_CommentEdit.SetWindowText( m_CommentText );
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTitlingFDialog::OnOK()
{
	// TODO: Add extra validation here
	m_CommentEdit.GetWindowText( m_CommentText );
	
	CDialog::OnOK();
}
