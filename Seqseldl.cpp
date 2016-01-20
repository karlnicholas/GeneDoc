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
// seqseldl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqSelDlg dialog


CSeqSelDlg::CSeqSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeqSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeqSelDlg)
	m_dLogOddsMPC = 0.0;
	m_iLogOddsOutTab = -1;
	m_iLogOddsBack = -1;
	m_dLogOddsStA = 0.0;
	m_dLogOddsStC = 0.0;
	m_dLogOddsStG = 0.0;
	m_dLogOddsStT = 0.0;
	//}}AFX_DATA_INIT
}

void CSeqSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeqSelDlg)
	DDX_Control(pDX, IDC_OUTTAB, m_cbOutTab);
	DDX_Control(pDX, IDC_LISTSEQUENCE, m_listSequence);
	DDX_Text(pDX, IDC_MPC, m_dLogOddsMPC);
	DDX_CBIndex(pDX, IDC_OUTTAB, m_iLogOddsOutTab);
	DDX_Radio(pDX, IDC_BACKGROUND2, m_iLogOddsBack);
	DDX_Text(pDX, IDC_STATICA, m_dLogOddsStA);
	DDX_Text(pDX, IDC_STATICC, m_dLogOddsStC);
	DDX_Text(pDX, IDC_STATICG, m_dLogOddsStG);
	DDX_Text(pDX, IDC_STATICT, m_dLogOddsStT);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeqSelDlg, CDialog)
	//{{AFX_MSG_MAP(CSeqSelDlg)
	ON_CBN_SELCHANGE(IDC_OUTTAB, OnSelchangeOuttab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSeqSelDlg message handlers

BOOL CSeqSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( pDoc->m_UserVars.m_ProjectType > 1 ) {
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "1:1:Pam30" );
		m_cbOutTab.AddString( "1:1:Pam60" );
		m_cbOutTab.AddString( "1:1:Pam90" );
		m_cbOutTab.AddString( "3:1:Pam30" );
		m_cbOutTab.AddString( "3:1:Pam60" );
		m_cbOutTab.AddString( "3:1:Pam90" );
		m_cbOutTab.AddString( "Pam30:pseudo" );
		m_cbOutTab.AddString( "Pam60:pseudo" );
		m_cbOutTab.AddString( "Pam90:pseudo" );

	} else {
		// CComboBox
		m_cbOutTab.ResetContent();
		m_cbOutTab.AddString( "BloSum30" );
		m_cbOutTab.AddString( "BloSum50" );
		m_cbOutTab.AddString( "BloSum62" );
		m_cbOutTab.AddString( "BloSum75" );
	}
	// TODO: Add extra initialization here
	m_listSequence.ResetContent();
	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			m_listSequence.AddString(tCGSeg->GetTitle());
		}
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeqSelDlg::OnOK() 
{
	// TODO: Add extra validation here
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tCGSeg->SetExportFlag(0);

	}

	int SelCount = m_listSequence.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		CDialog::OnOK();
		return;
	}
			   
	int *SelArray = new int[SelCount];
	
	m_listSequence.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list

		POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->SetExportFlag(1);

	}

	delete SelArray;
	
	CDialog::OnOK();
}

void CSeqSelDlg::OnSelchangeOuttab() 
{
	// TODO: Add your control notification handler code here
	if ( pDoc->m_UserVars.m_ProjectType > 1 ) {

		m_iLogOddsOutTab = m_cbOutTab.GetCurSel();

		switch ( m_iLogOddsOutTab ) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_dLogOddsStA = 250000;
			m_dLogOddsStC = 250000;
			m_dLogOddsStG = 250000;
			m_dLogOddsStT = 250000;
			break;
		case 6:
		case 7:
		case 8:
			m_dLogOddsStA = 244000;
			m_dLogOddsStC = 254000;
			m_dLogOddsStG = 263000;
			m_dLogOddsStT = 239000;
			break;
		}
		UpdateData(FALSE);
	}
	
}
