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
// seqinput.cpp : implementation file
//

#include "stdafx.h"
#include <ctype.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqInput dialog


CSeqInput::CSeqInput(CWnd* pParent /*=NULL*/)
	: CDialog(CSeqInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeqInput)
	m_SeqName = _T("");
	m_Descr = _T("");
	//}}AFX_DATA_INIT
}

void CSeqInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeqInput)
	DDX_Control(pDX, IDC_SEQEDIT, m_SeqInput);
	DDX_Text(pDX, IDC_SEQUENCENAME, m_SeqName);
	DDX_Text(pDX, IDC_DESCR, m_Descr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeqInput, CDialog)
	//{{AFX_MSG_MAP(CSeqInput)
	ON_BN_CLICKED(IDC_PASTE, OnPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSeqInput message handlers

void CSeqInput::OnOK() 
{
	// TODO: Add extra validation here
	// CEdit
	int Len = m_SeqInput.GetLineCount();
	for ( int i=0; i < Len; ++i ) {
		CString tStr;
		char *pc = tStr.GetBuffer( m_SeqInput.LineLength(m_SeqInput.LineIndex(i)) );
		m_SeqInput.GetLine(i, pc, m_SeqInput.LineLength(m_SeqInput.LineIndex(i)) );
		tStr.ReleaseBuffer(m_SeqInput.LineLength(m_SeqInput.LineIndex(i)));
		int sLen = tStr.GetLength();
		for ( int j=0; j < sLen; ++j ) {
			char cd = tStr[j];
			if ( isgraph(cd) ) m_DataString += cd;
		}
	}

	
	CDialog::OnOK();
}

void CSeqInput::OnPaste() 
{
	// TODO: Add your control notification handler code here
	m_SeqInput.Paste();
	
}

BOOL CSeqInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	// Just in case ...
	m_DataString.Empty();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
