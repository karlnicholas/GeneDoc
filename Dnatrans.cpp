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
// dnatrans.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDNATrans dialog


CDNATrans::CDNATrans(CWnd* pParent /*=NULL*/)
	: CDialog(CDNATrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDNATrans)
	m_iReadShift = -1;
	m_AltCodon = _T("");
	m_AltProt = _T("");
	m_AltStart = _T("");
	m_TransColumns = -1;
	m_TransFixed = -1;
	m_TransFltStart = FALSE;
	//}}AFX_DATA_INIT
	VERIFY(m_Font.CreateFont(12,0,0,0,400,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		FIXED_PITCH,"Courier"));
	
}

void CDNATrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDNATrans)
	DDX_Control(pDX, IDC_TRANSFLTSTART, m_cTransFltStart);
	DDX_Control(pDX, IDC_SHIFT0, m_cShift0);
	DDX_Control(pDX, IDC_SHIFT2, m_cShift1);
	DDX_Control(pDX, IDC_SHIFT1, m_cShift2);
	DDX_Control(pDX, IDC_TRANSCOLUMNS, m_cTransColumns);
	DDX_Control(pDX, IDC_TRANSFIXEDSTART, m_cTransFixedStart);
	DDX_Control(pDX, IDC_LISTCODON, m_listCodon);
	DDX_Control(pDX, IDC_COMBCODON, m_comboCodon);
	DDX_Radio(pDX, IDC_SHIFT0, m_iReadShift);
	DDX_Text(pDX, IDC_ALTCODON, m_AltCodon);
	DDX_Text(pDX, IDC_ALTPROT, m_AltProt);
	DDV_MaxChars(pDX, m_AltProt, 1);
	DDX_Text(pDX, IDC_ALTSTART, m_AltStart);
	DDV_MaxChars(pDX, m_AltStart, 1);
	DDX_Radio(pDX, IDC_TRANSCOLUMNS, m_TransColumns);
	DDX_Radio(pDX, IDC_TRANSFIXED, m_TransFixed);
	DDX_Check(pDX, IDC_TRANSFLTSTART, m_TransFltStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDNATrans, CDialog)
	//{{AFX_MSG_MAP(CDNATrans)
	ON_CBN_SELCHANGE(IDC_COMBCODON, OnSelchangeCombcodon)
	ON_LBN_SELCHANGE(IDC_LISTCODON, OnSelchangeListcodon)
	ON_BN_CLICKED(IDC_TRANSFIXED, OnTransfixed)
	ON_BN_CLICKED(IDC_TRANSFLOAT, OnTransfloat)
	ON_BN_CLICKED(IDC_TRANSCOLUMNS, OnTranscolumns)
	ON_BN_CLICKED(IDC_TRANSFIXEDSTART, OnTransfixedstart)
	ON_CBN_EDITCHANGE(IDC_COMBCODON, OnEditchangeCombcodon)
	ON_EN_CHANGE(IDC_ALTSTART, OnChangeAltstart)
	ON_EN_CHANGE(IDC_ALTPROT, OnChangeAltprot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDNATrans message handlers

struct DNATrans { 
	char Name[128];
	char Prot[65];
	char Start[65];
} iDNATrans[] = 
{ 
	{
  "Standard" ,
  "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
  "Vertebrate Mitochondrial" ,
  "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIMMTTTTNNKKSS**VVVVAAAADDEEGGGG",
  "--------------------------------MMMM---------------M------------"
 },
 {
  "Yeast Mitochondrial" ,
  "FFLLSSSSYY**CCWWTTTTPPPPHHQQRRRRIIMMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
    "Mold Mitochondrial; Protozoan Mitochondrial; Coelenterate Mitochondrial; Mycoplasma; Spiroplasma" ,
  "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "--MM---------------M------------MMMM---------------M------------"
 },
 {
  "Invertebrate Mitochondrial" ,
  "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIMMTTTTNNKKSSSSVVVVAAAADDEEGGGG",
  "---M----------------------------MMMM---------------M------------"
 },
 {
  "Ciliate Nuclear; Dasycladacean Nuclear; Hexamita Nuclear" ,
  "FFLLSSSSYYQQCC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
  "Echinoderm Mitochondrial" ,
  "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIIMTTTTNNNKSSSSVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
  "Euplotid Nuclear" ,
  "FFLLSSSSYY**CCCWLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
  "Bacterial" ,
  "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "---M---------------M------------M--M---------------M------------"
 },
 {
  "Alternative Yeast Nuclear" ,
  "FFLLSSSSYY**CC*WLLLSPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-------------------M---------------M----------------------------"
 },
 {
  "Ascidian Mitochondrial" ,
  "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIMMTTTTNNKKSSGGVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 },
 {
  "Flatworm Mitochondrial" ,
  "FFLLSSSSYYY*CCWWLLLLPPPPHHQQRRRRIIIMTTTTNNNKSSSSVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
 } ,
 {
  "Blepharisma Macronuclear" ,
  "FFLLSSSSYY*QCC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG",
  "-----------------------------------M----------------------------"
  },{ "", "" }
};

	


BOOL CDNATrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( m_TransFixed == 0 ) {
		OnTransfixed() ;
	} else {
		OnTransfloat();
	}

	m_comboCodon.ResetContent();

	struct DNATrans *pDNATrans = iDNATrans;

	while ( strlen( pDNATrans->Name ) != 0 ) {
		m_comboCodon.AddString( pDNATrans->Name);
		pDNATrans++;
	}
	m_comboCodon.SetWindowText( pDoc->m_UserVars.m_DNATransName );

	// CComboBox
	UpdateListCodon();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDNATrans::UpdateListCodon()
{
	// TODO: Add your control notification handler code here
	m_listCodon.ResetContent();
	m_listCodon.SetFont( &m_Font, FALSE );

	char tTran[] = "TCAG";

	for ( int i = 0; i < 64; ++ i ) {
		CString tStr;

		tStr += tTran[i/(64/4)];
		tStr += tTran[(i/(64/(4*4)))%4];
		tStr += tTran[(i/(64/(4*4*4)))%4];

		tStr += "  ";
		tStr += pDoc->m_UserVars.m_DNATrans[i];

		tStr += " ";
		tStr += pDoc->m_UserVars.m_DNATransStart[i];
		m_listCodon.AddString( tStr );

	}
	
}

void CDNATrans::OnSelchangeCombcodon() 
{
	struct DNATrans *pDNATrans = iDNATrans;

	pDoc->m_UserVars.m_DNATransName = pDNATrans[m_comboCodon.GetCurSel()].Name;
	pDoc->m_UserVars.m_DNATrans = pDNATrans[m_comboCodon.GetCurSel()].Prot;
	pDoc->m_UserVars.m_DNATransStart = pDNATrans[m_comboCodon.GetCurSel()].Start;

	UpdateListCodon();

}

void CDNATrans::OnEditchangeCombcodon() 
{
	// TODO: Add your control notification handler code here
	m_comboCodon.GetWindowText(pDoc->m_UserVars.m_DNATransName);

}

void CDNATrans::OnSelchangeListcodon() 
{
	// TODO: Add your control notification handler code here
	char tTran[] = "TCAG";

	int i = m_listCodon.GetCurSel();
	if ( i == LB_ERR ) return;
	CString tStr;

	tStr = tTran[i/(64/4)];
	tStr += tTran[(i/(64/(4*4)))%4];
	tStr += tTran[(i/(64/(4*4*4)))%4];
	m_AltCodon = tStr;

	tStr = pDoc->m_UserVars.m_DNATrans[i];
	m_AltProt = tStr;

	tStr = pDoc->m_UserVars.m_DNATransStart[i];
	m_AltStart = tStr;
	
	UpdateData(FALSE);
}

void CDNATrans::OnTransfixed() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_cTransColumns.EnableWindow(TRUE);
	m_cTransFixedStart.EnableWindow(TRUE);
	m_cTransFltStart.EnableWindow(FALSE);
	
	if ( m_TransColumns == 0 ) {
		m_cShift0.EnableWindow(TRUE);
		m_cShift1.EnableWindow(TRUE);
		m_cShift2.EnableWindow(TRUE);
	} else {
		m_cShift0.EnableWindow(FALSE);
		m_cShift1.EnableWindow(FALSE);
		m_cShift2.EnableWindow(FALSE);
	}
}

void CDNATrans::OnTransfloat() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_cTransColumns.EnableWindow(FALSE);
	m_cTransFixedStart.EnableWindow(FALSE);
	m_cTransFltStart.EnableWindow(TRUE);

	m_cShift0.EnableWindow(FALSE);
	m_cShift1.EnableWindow(FALSE);
	m_cShift2.EnableWindow(FALSE);
}


void CDNATrans::OnTranscolumns() 
{
	// TODO: Add your control notification handler code here
	m_cShift0.EnableWindow(TRUE);
	m_cShift1.EnableWindow(TRUE);
	m_cShift2.EnableWindow(TRUE);
}

void CDNATrans::OnTransfixedstart() 
{
	// TODO: Add your control notification handler code here
	m_cShift0.EnableWindow(FALSE);
	m_cShift1.EnableWindow(FALSE);
	m_cShift2.EnableWindow(FALSE);
	
}

void CDNATrans::OnChangeAltstart() 
{
	int i = m_listCodon.GetCurSel();
	if ( i == LB_ERR ) return;

	UpdateData();
	if ( m_AltStart.GetLength() == 0 ) return;
	pDoc->m_UserVars.m_DNATransStart.SetAt(i, toupper(m_AltStart.GetAt(0)) );

	UpdateListCodon();
	m_listCodon.SetCurSel(i);
	
}

void CDNATrans::OnChangeAltprot() 
{
	int i = m_listCodon.GetCurSel();
	if ( i == LB_ERR ) return;

	UpdateData();
	if ( m_AltProt.GetLength() == 0 ) return;
	pDoc->m_UserVars.m_DNATrans.SetAt(i, toupper(m_AltProt.GetAt(0)) );

	UpdateListCodon();
	m_listCodon.SetCurSel(i);

}
