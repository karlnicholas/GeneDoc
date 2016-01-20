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
// seqdetdi.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqDetDialog dialog


CSeqDetDialog::CSeqDetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSeqDetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeqDetDialog)
	m_SeqName = _T("");
	m_SeqWeight = 0;
	m_Instruct = _T("");
	m_TextStart = 0;
	m_Descr = _T("");
	//}}AFX_DATA_INIT
}


void CSeqDetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeqDetDialog)
	DDX_Text(pDX, IDC_SEQDETNAME, m_SeqName);
	DDV_MaxChars(pDX, m_SeqName, 50);
	DDX_Text(pDX, IDC_SEQDETWEIGHT, m_SeqWeight);
	DDX_Text(pDX, IDC_INSTRUCT, m_Instruct);
	DDX_Text(pDX, IDC_TEXTSTART, m_TextStart);
	DDX_Text(pDX, IDC_DESCR, m_Descr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeqDetDialog, CDialog)
	//{{AFX_MSG_MAP(CSeqDetDialog)
	ON_EN_CHANGE(IDC_SEQDETNAME, OnChangeSeqdetname)
	ON_EN_CHANGE(IDC_SEQDETWEIGHT, OnChangeSeqdetweight)
	ON_EN_CHANGE(IDC_TEXTSTART, OnChangeTextstart)
	ON_EN_CHANGE(IDC_DESCR, OnChangeDescr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSeqDetDialog message handlers

BOOL CSeqDetDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_NameChanged = 0;
	m_DescrChanged = 0;
	m_WeightChanged = 0;
	m_StartChanged = 0;
	
	return TRUE;
}

void CSeqDetDialog::OnChangeSeqdetname() 
{
	// TODO: Add your control notification handler code here

	m_NameChanged = 1;	
}

void CSeqDetDialog::OnChangeSeqdetweight()
{
	// TODO: Add your control notification handler code here
	m_WeightChanged = 1;
}

void CSeqDetDialog::OnChangeTextstart() 
{
	m_StartChanged = 1;
	
}

void CSeqDetDialog::OnChangeDescr() 
{
	m_DescrChanged = 1;	
	
}

