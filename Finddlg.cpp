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
// finddlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_FindStr = _T("");
	m_InsDel = 0;
	m_MisMatch = 0;
	m_FindFrom = -1;
	//}}AFX_DATA_INIT
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
	DDX_Control(pDX, IDC_LISTSEQUENCES, m_listSequence);
	DDX_Text(pDX, IDC_FINDSTR, m_FindStr);
	DDX_Text(pDX, IDC_INSDEL, m_InsDel);
	DDX_Text(pDX, IDC_MISMATCH, m_MisMatch);
	DDX_Radio(pDX, IDC_FINDFROM, m_FindFrom);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	ON_BN_CLICKED(IDC_RGBBACK, OnRgbback)
	ON_BN_CLICKED(IDC_RGBTEXT, OnRgbtext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFindDlg message handlers

BOOL CFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listSequence.ResetContent();
	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			m_listSequence.AddString(tCGSeg->GetTitle());
		}
	}

	int Sel = 0;
	int idx = 0;
	tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			if ( tCGSeg->GetExportFlag() ) {
				m_listSequence.SetSel( idx );
				Sel = 1;
			}
			idx++;
		}
	}
	if ( !Sel ) {
		m_listSequence.SetSel( -1 );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindDlg::OnOK() 
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

		tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->SetExportFlag(1);

	}

	delete SelArray;
	
	CDialog::OnOK();
}

void CFindDlg::OnRgbback() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cDlg(pDoc->m_pFS.rgbBack);
	if ( cDlg.DoModal() != IDOK ) return;
	pDoc->m_pFS.rgbBack = cDlg.GetColor();
}

void CFindDlg::OnRgbtext() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cDlg(pDoc->m_pFS.rgbText);
	if ( cDlg.DoModal() != IDOK ) return;
	pDoc->m_pFS.rgbText = cDlg.GetColor();
	
}
