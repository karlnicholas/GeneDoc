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
// displayp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty dialog


CDisplayProperty::CDisplayProperty() : CPropertyPage(CDisplayProperty::IDD)
{
	//{{AFX_DATA_INIT(CDisplayProperty)
	m_AutoWidth = -1;
	m_FixedWidth = 0;
	m_ShowTail = -1;
	m_GapInd = -1;
	m_ProjectType = -1;
	m_ScoringMethod = -1;
	m_ConsensusLine = -1;
	m_PictHeight = 0;
	m_PictAscent = 0;
	m_PictWidth = 0;
	m_FontWeight = "";
	m_FontSize = 0;
	m_DNAAmbEn = -1;
	m_MarkerSpacing = 0;
	m_MarkerEnable = FALSE;
	m_MarkerReplace = 0;
	m_MarkerStart = 0;
	m_MarkerSymb = _T("");
	m_ConservedGap = _T("");
	m_ResidueUpper = -1;
	m_MaxNameLength = 0;
	m_strTail = _T("");
	m_strLead = _T("");
	m_SumColInch = 0;
	m_Sum2Wid = -1;
	m_SumDefDis = FALSE;
	m_SumColInchDis = 0;
	m_SumTextBlack = FALSE;
	m_TransTilde = FALSE;
	m_ShowManShade = FALSE;
	m_ShowComments = FALSE;
	m_MakeBackups = TRUE;
	m_LocAfterSeq = TRUE;
	m_LocAfterName = FALSE;
	//}}AFX_DATA_INIT
}

void CDisplayProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayProperty)
	DDX_Radio(pDX, IDC_GENEAUTOWIDTH, m_AutoWidth);
	DDX_Text(pDX, IDC_EDITWIDTH, m_FixedWidth);
	DDV_MinMaxInt(pDX, m_FixedWidth, 10, 1000000);
	DDX_Radio(pDX, IDC_SEQINDON, m_ShowTail);
	DDX_Radio(pDX, IDC_GAPDASH, m_GapInd);
	DDX_Radio(pDX, IDC_TYPEPROTEIN, m_ProjectType);
	DDX_Radio(pDX, IDC_SCOREPAIR, m_ScoringMethod);
	DDX_Radio(pDX, IDC_CONSENSUSLINE, m_ConsensusLine);
	DDX_Text(pDX, IDC_PICTHEIGHT, m_PictHeight);
	DDV_MinMaxInt(pDX, m_PictHeight, -9, 9);
	DDX_Text(pDX, IDC_PICTASCENT, m_PictAscent);
	DDV_MinMaxInt(pDX, m_PictAscent, -9, 9);
	DDX_Text(pDX, IDC_PICTWIDTH, m_PictWidth);
	DDV_MinMaxInt(pDX, m_PictWidth, -9, 9);
	DDX_CBString(pDX, IDC_FONTWEIGHT, m_FontWeight);
	DDX_Text(pDX, IDC_EDITFONTPOINTS, m_FontSize);
	DDX_Radio(pDX, IDC_DNAAMBDIS, m_DNAAmbEn);
	DDX_Text(pDX, IDC_MARKERCOUNT, m_MarkerSpacing);
	DDX_Check(pDX, IDC_MARKERENABLED, m_MarkerEnable);
	DDX_Text(pDX, IDC_MARKERREPLACE, m_MarkerReplace);
	DDX_Text(pDX, IDC_MARKERSTART, m_MarkerStart);
	DDX_Text(pDX, IDC_MARKERSYMBOL, m_MarkerSymb);
	DDV_MaxChars(pDX, m_MarkerSymb, 1);
	DDX_Text(pDX, IDC_CONSERVEDGAP, m_ConservedGap);
	DDV_MaxChars(pDX, m_ConservedGap, 1);
	DDX_Radio(pDX, IDC_RESIDUENORMAL, m_ResidueUpper);
	DDX_Text(pDX, IDC_MAXNAME, m_MaxNameLength);
	DDV_MinMaxInt(pDX, m_MaxNameLength, 0, 50);
	DDX_Text(pDX, IDC_INDSEP, m_strTail);
	DDV_MaxChars(pDX, m_strTail, 10);
	DDX_Text(pDX, IDC_NAMESEP, m_strLead);
	DDV_MaxChars(pDX, m_strLead, 10);
	DDX_Text(pDX, IDC_SUMCOLINCH, m_SumColInch);
	DDX_Radio(pDX, IDC_COL2WID11, m_Sum2Wid);
	DDX_Check(pDX, IDC_SUMDEFDIS, m_SumDefDis);
	DDX_Text(pDX, IDC_SUMCOLINCHDIS, m_SumColInchDis);
	DDX_Check(pDX, IDC_SUMTEXTBLACK, m_SumTextBlack);
	DDX_Check(pDX, IDC_TRANSTIDLE, m_TransTilde);
	DDX_Check(pDX, IDC_SHOWMANSHADE, m_ShowManShade);
	DDX_Check(pDX, IDC_SHOWCOMMENTS, m_ShowComments);
	DDX_Check(pDX, IDC_MAKEBACKUPS, m_MakeBackups);
	DDX_Check(pDX, IDC_LOCAFTERSEQ, m_LocAfterSeq);
	DDX_Check(pDX, IDC_LOCAFTERNAME, m_LocAfterName);
	//}}AFX_DATA_MAP
}

BOOL CDisplayProperty::OnStyleClicked(UINT /*nCmdID*/)
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
//		((CModalDisplayPropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDisplayProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CDisplayProperty)
	ON_BN_CLICKED(IDC_TYPEPROTEIN, OnTypeprotein)
	ON_BN_CLICKED(IDC_TYPERNA, OnTyperna)
	ON_BN_CLICKED(IDC_TYPEDNA, OnTypedna)
	ON_BN_CLICKED(IDC_TYPEMIXEDNUCLEIC, OnTypemixednucleic)
	ON_EN_CHANGE(IDC_SUMCOLINCH, OnChangeSumcolinch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty message handlers


BOOL CDisplayProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnChangeSumcolinch();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDisplayProperty::OnTypeprotein() 
{
	// TODO: Add your control notification handler code here
	ChangeProjectType();
}

void CDisplayProperty::OnTyperna() 
{
	// TODO: Add your control notification handler code here
	ChangeProjectType();
}

void CDisplayProperty::OnTypedna() 
{
	// TODO: Add your control notification handler code here
	ChangeProjectType();
}

void CDisplayProperty::OnTypemixednucleic() 
{
	// TODO: Add your control notification handler code here
	ChangeProjectType();
}

void
CDisplayProperty::ChangeProjectType()
{

	CModalDisplayPropSheet* pPropertySheet = (CModalDisplayPropSheet*)GetParent();

	UpdateData();
	
	for ( int i = 0; i < 3; ++i ) {

		SetPropertyDefault( 
			&pPropertySheet->m_PropertyGroupPage.m_PropertyArray[i], 
			i, m_ProjectType + 1
		);
	}
	
	pPropertySheet->m_PropertyGroupPage.ResetData();

	pPropertySheet->m_ScoreTablePage.m_ProjectType = m_ProjectType + 1;

	pPropertySheet->m_ScoreTablePage.SetScoreTableArray( &pDoc->m_UserVars.m_ScoreTableArray, m_ProjectType + 1);

	if ( m_ProjectType ) {
		pPropertySheet->m_ScoreTablePage.m_CurrentScoreTable = 13;
	} else {
		pPropertySheet->m_ScoreTablePage.m_CurrentScoreTable = 2;
	}
	pDoc->SetShadeGroupDefault( 
		&pPropertySheet->m_ScoreTablePage.m_ShadePairArray, 
		pPropertySheet->m_ScoreTablePage.m_CurrentScoreTable 
	);

	pPropertySheet->m_ScoreTablePage.ResetData();

	pPropertySheet->m_LogOddsPropPage.ChangeProjectType(m_ProjectType + 1);

}


void CDisplayProperty::OnChangeSumcolinch() 
{
	// TODO: Add your control notification handler code here

//	UpdateData();
	CWnd *pWnd = GetDlgItem( IDC_SUMCOLINCH );
	CString strVal;
	pWnd->GetWindowText( strVal );
	int SumColInch = atoi ( (const char *)strVal );
	if ( SumColInch == 0 ) return;

	CDC *cDC = GetDC();
	int PixInch = cDC->GetDeviceCaps( LOGPIXELSX );		// Pixels Per Inch

	int SumWidth = PixInch / SumColInch;
	if ( SumWidth == 0 ) SumWidth = 1;
	PixInch = PixInch / SumWidth;

	char str[20];
	_itoa( PixInch, str, 10 );

	pWnd = GetDlgItem( IDC_SUMCOLINCHDIS );
	pWnd->SetWindowText( str );
	pWnd->Invalidate();
	ReleaseDC(cDC);
//	UpdateData(FALSE);
	
}
