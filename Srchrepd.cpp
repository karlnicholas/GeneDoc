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
// srchrepd.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrchRepDlg dialog


CSrchRepDlg::CSrchRepDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrchRepDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrchRepDlg)
	m_CutSites = TRUE;
	m_GroupFrag = TRUE;
	m_SortedCut = TRUE;
	m_SortedFrag = TRUE;
	m_SimPer = 5;
	m_UniqPer = 20;
	m_UniqFragPer = 20;
	m_UniqFrag = TRUE;
	//}}AFX_DATA_INIT
}

void CSrchRepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrchRepDlg)
	DDX_Check(pDX, IDC_CUTSITES, m_CutSites);
	DDX_Check(pDX, IDC_GROUPFRAG, m_GroupFrag);
	DDX_Check(pDX, IDC_SORTEDCUT, m_SortedCut);
	DDX_Check(pDX, IDC_SORTEDFRAG, m_SortedFrag);
	DDX_Text(pDX, IDC_SIMPER, m_SimPer);
	DDV_MinMaxUInt(pDX, m_SimPer, 0, 100);
	DDX_Text(pDX, IDC_UNIQPER, m_UniqPer);
	DDX_Text(pDX, IDC_UNIQFRAGPER, m_UniqFragPer);
	DDX_Check(pDX, IDC_UNIQUEFRAG, m_UniqFrag);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrchRepDlg, CDialog)
	//{{AFX_MSG_MAP(CSrchRepDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSrchRepDlg message handlers
