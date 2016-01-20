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
// groupsel.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupSelect dialog


CGroupSelect::CGroupSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CGroupSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupSelect)
	DDX_Control(pDX, IDC_OTHERLIST, m_OtherList);
	DDX_Control(pDX, IDC_GROUPLIST, m_GroupList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGroupSelect, CDialog)
	//{{AFX_MSG_MAP(CGroupSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGroupSelect message handlers

BOOL CGroupSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	if ( GroupSeq == 0 ) {
		// TODO: Add extra initialization here
		POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();

		while ( tPos != NULL ) {

			CDisplayVars *DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);

			m_GroupList.AddString( DisplayVars->GetGroupName() );
			
		}
		
		m_OtherList.AddString( "<All Other>" );

		tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();

		while ( tPos != NULL ) {

			CDisplayVars *DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);

			m_OtherList.AddString( DisplayVars->GetGroupName() );
			
		}
	} else {
		// TODO: Add extra initialization here
		POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			m_GroupList.AddString( tCGSeg->GetTitle() );
			
		}
		
		tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			m_OtherList.AddString( tCGSeg->GetTitle() );
			
		}
	}

	GroupNum1 = 0;
	GroupNum2 = 0;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGroupSelect::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_GroupList.GetCurSel() != LB_ERR ) {
		GroupNum1 = m_GroupList.GetCurSel() + 1;
		m_GroupList.GetText(GroupNum1 - 1, GroupName1);
	}
	
	if ( m_OtherList.GetCurSel() != LB_ERR ) {
		GroupNum2 = m_OtherList.GetCurSel() + 1;
		m_OtherList.GetText(GroupNum2 - 1, GroupName2);
	}
	CDialog::OnOK();
}
