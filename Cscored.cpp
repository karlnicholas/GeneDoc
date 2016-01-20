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
// ScoreTablep.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreTableProperty dialog


CScoreTableProperty::CScoreTableProperty() : CPropertyPage(CScoreTableProperty::IDD)
{
	//{{AFX_DATA_INIT(CScoreTableProperty)
	m_CurrentScoreTableString = _T("");
	//}}AFX_DATA_INIT
	m_DialogInited = 0;
}

void CScoreTableProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoreTableProperty)
	DDX_Text(pDX, IDC_CURRENTSCORE, m_CurrentScoreTableString);
	//}}AFX_DATA_MAP
}

BOOL CScoreTableProperty::OnStyleClicked(UINT /*nCmdID*/)
{
	// The CStylePage property page is used for both the
	// CModalShapePropSheet and the CModelessShapePropSheet.
	// Both these versions of the property sheet share a common
	// feature that they immediately update a shape.  In the
	// case of CModalShapePropSheet, the shape is in the preview
	// window.  In the case of CModelessShapePropSheet, the shape
	// is the currently selected shape in the view.

	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();

	if (pPropertySheet->IsKindOf(RUNTIME_CLASS(CModalDisplayPropSheet)))
	{
		UpdateData();
//		((CModalDisplayPropSheet*)pPropertySheet)->m_ShadeGroupPage.SetDefaults();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CScoreTableProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CScoreTableProperty)
	ON_LBN_DBLCLK(IDC_SCORELIST, OnDblclkScorelist)
	ON_BN_CLICKED(IDC_SCORESETCURRENT, OnScoresetcurrent)
	ON_BN_CLICKED(IDC_SCOREDESCR, OnScoredescr)
	ON_BN_CLICKED(IDC_SHADEDELETE, OnShadedelete)
	ON_BN_CLICKED(IDC_SHADEEDIT, OnShadeedit)
	ON_LBN_DBLCLK(IDC_SHADELIST, OnDblclkShadelist)
	ON_BN_CLICKED(IDC_SHADENEW, OnShadenew)
	ON_BN_CLICKED(IDC_SHADEDEFAULT, OnShadedefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScoreTableProperty message handlers

BOOL CScoreTableProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_DialogInited = 1;
	// CListBox	
	m_listScore = (CListBox *)GetDlgItem( IDC_SCORELIST );
	m_listGroup = (CListBox *)GetDlgItem( IDC_SHADELIST );

	ResetData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CScoreTableProperty::ResetData()
{
	if ( !m_DialogInited ) return;

	ReBuildListBox();
	
	if ( m_listGroup->GetCount() ) {
		m_listGroup->SetCurSel(0);
	}
}

void
CScoreTableProperty::ReBuildListBox()
{
	
	char tBuff[128];
	ScoreTableStruct *tSPS;
	
	m_listScore->ResetContent();
	         
	// CListBox
	int count = m_ScoreTableArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ScoreTableStruct *)m_ScoreTableArray[i];
		_snprintf( 
			tBuff, 
			128, 
			"%s", 
			tSPS->Name
		);
		m_listScore->AddString(tBuff);
	}
	if ( count != 0 ) {
		m_CurrentScoreTableString = ((ScoreTableStruct *)pDoc->m_UserVars.m_ScoreTableArray[m_CurrentScoreTable])->Name;
//		if ( pDoc->m_UserVars.m_ProjectType > 1 ) {
		if ( m_ProjectType > 1 ) {
			m_listScore->SetCurSel ( m_CurrentScoreTable - 9 );
		} else {
			m_listScore->SetCurSel ( m_CurrentScoreTable );
		}
		UpdateData(FALSE);
	}
	
	ShadePairStruct *tShPS;
	
	m_listGroup->ResetContent();
	         
	// CListBox
	count = m_ShadePairArray.GetSize();
	for (int i = 0; i < count; ++i ) {
		tShPS = (ShadePairStruct *)m_ShadePairArray[i];
		tShPS->RowNum = i + 1;
		_snprintf( 
			tBuff, 
			MAXSHADEGROUP + 9, 
			"%2d: %s", 
			tShPS->RowNum, 
			tShPS->Group
		);
		m_listGroup->AddString(tBuff);
	}
	
}

void
CScoreTableProperty::SetScoreTableArray(CPtrArray *nScoreTableArray, int ScoreType)
{
	ScoreTableStruct *tSPS;
	ScoreTableStruct *tSPSn;

	int count = m_ScoreTableArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ScoreTableStruct *)m_ScoreTableArray[i];
		delete tSPS;
	}
	m_ScoreTableArray.RemoveAll();
	
	int TypeCheck = ScoreType < 2 ? 0: 1;

	count = nScoreTableArray->GetSize();
	for (int i = 0; i < count; ++i ) { 
		tSPSn = (ScoreTableStruct *)nScoreTableArray->GetAt(i);
		if ( tSPSn->ScoreType == TypeCheck ) {
			tSPS = new ScoreTableStruct;
			
			if ( tSPS == 0 ) {
				AfxMessageBox("SetScoreTable:new:fail:1");
				return;
			}

			tSPS->Name = tSPSn->Name;
			tSPS->ScoreType = i;
	
			m_ScoreTableArray.Add( tSPS );
		}
	}
}	

void
CScoreTableProperty::SetShadePairArray(CPtrArray *nShadePairArray)
{
	ShadePairStruct *tSPS;
	ShadePairStruct *tSPSn;
	int count = m_ShadePairArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ShadePairStruct *)m_ShadePairArray[i];
		delete tSPS;
	}
	m_ShadePairArray.RemoveAll();

	count = nShadePairArray->GetSize();
	for (int i = 0; i < count; ++i ) { 
		tSPS = new ShadePairStruct;
		if ( tSPS == 0 ) {
			AfxMessageBox("setshadepariarray:new:fail:2");
			return;
		}
		tSPSn = (ShadePairStruct *)nShadePairArray->GetAt(i);

		tSPS->RowNum = tSPSn->RowNum;
		strcpy ( tSPS->Group, tSPSn->Group );

		m_ShadePairArray.Add( tSPS );
	}

}	


CScoreTableProperty::~CScoreTableProperty()
{
	ScoreTableStruct *tSPS;
	
	// CListBox
	int count = m_ScoreTableArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ScoreTableStruct *)m_ScoreTableArray[i];
		delete tSPS;
	}

	ShadePairStruct *tShPS;
	
	// CListBox
	count = m_ShadePairArray.GetSize();
	for (int i = 0; i < count; ++i ) {
		tShPS = (ShadePairStruct *)m_ShadePairArray[i];
		delete tShPS;
	}
	// TODO: Add your message handler code here
}

void CScoreTableProperty::OnShadedelete() 
{
	// TODO: Add your control notification handler code here
	// CListBox	
	int CurSel;
	if ( (CurSel = m_listGroup->GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}
	
	// CPtrArray
	delete (ShadePairStruct *)m_ShadePairArray[CurSel];
	m_ShadePairArray.RemoveAt(CurSel);
	
	ReBuildListBox();
	
	if ( m_listGroup->GetCount() != CurSel ) {
		m_listGroup->SetCurSel ( CurSel );
	} else {
		m_listGroup->SetCurSel ( CurSel - 1);
	}
	m_listGroup->SetFocus();

}

void CScoreTableProperty::OnShadenew() 
{
	// TODO: Add your control notification handler code here
	int count = m_ShadePairArray.GetSize();
	count++;
	char tBuff[10];
	itoa(count, tBuff, 10);

	CShadeEditDlg	tDlg;
	
	tDlg.m_ShadeNum = tBuff;
    tDlg.m_ShadeCont = "";
    
    if ( tDlg.DoModal() != IDOK ) {
    	return;
    }
    
	ShadePairStruct *tSPS;
	tSPS = new ShadePairStruct;
	if ( tSPS == 0 ) {
		AfxMessageBox("onshadenew:new:fail:1");
		return;
	}
	tSPS->RowNum = count;

	strncpy ( tSPS->Group, tDlg.m_ShadeCont, MAXSHADEGROUP );
	char *pc = tSPS->Group;
	while (*pc != 0 ) {
		*pc = toupper(*pc);
		pc++;
	}

	m_ShadePairArray.Add( tSPS );
    
	ReBuildListBox();

	m_listGroup->SetCurSel ( m_listGroup->GetCount() - 1);
	m_listGroup->SetFocus();

}

void CScoreTableProperty::OnDblclkShadelist() 
{
	// TODO: Add your control notification handler code here
	OnShadeedit();
}

void CScoreTableProperty::OnShadeedit() 
{
	// TODO: Add your control notification handler code here
	
	int CurSel;
	if ( (CurSel = m_listGroup->GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}

	ShadePairStruct *tSPS = (ShadePairStruct *)m_ShadePairArray[CurSel];

	char tBuff[10];
	itoa(tSPS->RowNum, tBuff, 10);

	CShadeEditDlg	tDlg;
	
	tDlg.m_ShadeNum = tBuff;
	tDlg.m_ShadeCont = tSPS->Group;
    
    if ( tDlg.DoModal() != IDOK ) {
    	return;
    }

	strncpy ( tSPS->Group, tDlg.m_ShadeCont, MAXSHADEGROUP );
	char *pc = tSPS->Group;
	while (*pc != 0 ) {
		*pc = toupper(*pc);
		pc++;
	}

	m_ShadePairArray.SetAt(CurSel, tSPS );
    
	ReBuildListBox();
	
	m_listGroup->SetCurSel( CurSel );
	
}


void CScoreTableProperty::OnDblclkScorelist() 
{
	// TODO: Add your control notification handler code here
	// OnScoredescr();
	OnScoresetcurrent();
	
}

void CScoreTableProperty::OnScoresetcurrent() 
{
	// TODO: Add your control notification handler code here
	if ( m_listScore->GetCurSel() != LB_ERR ) {

//		if ( pDoc->m_UserVars.m_ProjectType > 1 ) {
//			m_CurrentScoreTable = m_listScore->GetCurSel() + 9;
//		} else {
//			m_CurrentScoreTable = m_listScore->GetCurSel();
//		}

		m_CurrentScoreTable =  ((ScoreTableStruct *)m_ScoreTableArray[m_listScore->GetCurSel()])->ScoreType;

		m_CurrentScoreTableString = ((ScoreTableStruct *)pDoc->m_UserVars.m_ScoreTableArray[m_CurrentScoreTable])->Name;
		

		// Goto ShadeGroup Page and reset defaults
		SetDefaults(m_CurrentScoreTable);
		
		UpdateData(FALSE);
	}
}

void CScoreTableProperty::OnScoredescr() 
{
	// TODO: Add your control notification handler code here
	if ( m_listScore->GetCurSel() != LB_ERR ) {
		int tScoreTable =  m_listScore->GetCurSel();
		int TableLoc = ((ScoreTableStruct *)m_ScoreTableArray.GetAt(tScoreTable))->ScoreType;
		
		AfxMessageBox ( pDoc->GetScoreTableDescr( TableLoc ), MB_ICONINFORMATION  );

	}
	
}

void CScoreTableProperty::OnShadedefault() 
{
	// TODO: Add your control notification handler code here

	// Goto ShadeGroup Page and reset defaults
	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();
	ASSERT (pPropertySheet->IsKindOf(RUNTIME_CLASS(CModalDisplayPropSheet)));
	
	pDoc->SetShadeGroupDefault( 
		&m_ShadePairArray, 
		((CModalDisplayPropSheet*)pPropertySheet)->m_ScoreTablePage.m_CurrentScoreTable
	);

	ReBuildListBox();

	if ( m_listGroup->GetCount() ) {
		m_listGroup->SetCurSel(0);
	}

}

void
CScoreTableProperty::SetDefaults(int NewScoreTable)
{
	pDoc->SetShadeGroupDefault( &m_ShadePairArray, NewScoreTable );

	if ( m_listGroup != NULL ) {
		ReBuildListBox();

		if ( m_listGroup->GetCount() ) {
			m_listGroup->SetCurSel(0);
		}
	}

}
