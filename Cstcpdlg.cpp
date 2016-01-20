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
// cstcpdlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStructurePropDialog dialog

CStructurePropDialog::CStructurePropDialog() : CPropertyPage(CStructurePropDialog::IDD)
{
	m_DialogInited = 0;
	m_ModifyAll = 0;
	//{{AFX_DATA_INIT(CStructurePropDialog)
	//}}AFX_DATA_INIT
}


CStructurePropDialog::~CStructurePropDialog()
{

}

void CStructurePropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStructurePropDialog)
	DDX_Control(pDX, IDC_STCLOADDATA, m_StcLoadData);
	DDX_Control(pDX, IDC_COMBOMASTER, m_ComboMaster);
	DDX_Control(pDX, IDC_DataTypeList, m_DataTypeList);
	//}}AFX_DATA_MAP
}

BOOL CStructurePropDialog::OnStyleClicked(UINT /*nCmdID*/)
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
//		((CModalPropertyGroupPropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CStructurePropDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CStructurePropDialog)
	ON_BN_CLICKED(IDC_STCLOADDATA, OnStcloaddata)
	ON_LBN_SELCHANGE(IDC_DataTypeList, OnSelchangeDataTypeList)
	ON_BN_CLICKED(IDC_DATASETDET, OnDatasetdet)
	ON_LBN_DBLCLK(IDC_DataTypeList, OnDblclkDataTypeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStructurePropDialog message handlers

BOOL CStructurePropDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	
	m_DialogInited = 1;

	ResetData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void
CStructurePropDialog::ResetData()
{

	if ( !m_DialogInited) return;

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list

	m_ComboMaster.ResetContent();

	if ( m_DisplayVars->GetGroupName() != "" ) {

		CPtrList* SeqGroupList = (CPtrList*) m_DisplayVars->GetGroupList();

		POSITION tPos = SeqGroupList->GetHeadPosition();
		while (tPos != NULL ) {
		
			CGeneSegment *tCGSeg = (CGeneSegment *)SeqGroupList->GetNext(tPos);
		
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
		
			// CComboBox
			m_ComboMaster.AddString ( (const char *)tCGSeg->GetTitle() );

		}

	} else if ( pGSFiller != NULL ) {

		CPtrList* SeqGroupList = &pGSFiller->SegDataList;

		POSITION tPos = SeqGroupList->GetHeadPosition();
		while (tPos != NULL ) {
		
			CGeneSegment *tCGSeg = (CGeneSegment *)SeqGroupList->GetNext(tPos);
		
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
		
			// CComboBox
			m_ComboMaster.AddString ( (const char *)tCGSeg->GetTitle() );

		}
	}
		
	m_ComboMaster.SelectString( -1, m_DisplayVars->GetStcGroup().GetMasterSeq() );
	
	// TODO: Add your specialized creation code here
	const CPtrList& DataTypeList = pDoc->m_UserVars.m_Stc.GetDataTypeList();
	
	m_DataLabelList.RemoveAll();

	POSITION Pos = DataTypeList.GetHeadPosition();
	
	while ( Pos != NULL ) {

		StcDataType *pDT = (StcDataType *)DataTypeList.GetNext(Pos);

		m_DataLabelList.AddTail( pDT );
	}

	InitDataTypeList();

	if ( m_ModifyAll ) {
		m_ComboMaster.EnableWindow(FALSE);
		// CButton
		m_StcLoadData.EnableWindow(FALSE);
	} else {
		m_ComboMaster.EnableWindow(TRUE);
		// CButton
		m_StcLoadData.EnableWindow(TRUE);
	}

	if ( m_DialogInited ) UpdateData(FALSE);
	
}

void CStructurePropDialog::InitDataTypeList()
{
	// CListBox
	m_DataTypeList.ResetContent();
	
	int Selection = -1, i=0;

	POSITION Pos = m_DataLabelList.GetHeadPosition();
	while ( Pos != NULL ) {
		CString Label;
		StcDataType *pDT = (StcDataType *)m_DataLabelList.GetNext(Pos);
		// CListBox
		Label = *pDT->LongLabel;
		
		StcDataValues *pDV;

		// Test if this label has any data
		if ( !m_DisplayVars->GetStcGroup().LookupDataValues( *pDT->DataType, &pDV ) ) {
			Label += "  **No Data**";
		}
		m_DataTypeList.AddString( Label );
		// Test if this is the current Struct Selection
		if ( *pDT->DataType == m_DisplayVars->GetStcGroup().GetCurrentDataType() ) {
			Selection = i;
		}
		i++;
			
	}
		
	m_DataTypeList.SetCurSel(Selection);
	// Lookup
	
	if ( m_DialogInited ) UpdateData(FALSE);

}

void CStructurePropDialog::OnStcloaddata()
{
	// TODO: Add your control notification handler code here
	CString MasterSeq;

	int MasterSel;

	if ( (MasterSel = m_ComboMaster.GetCurSel()) != LB_ERR ) {
	
		m_ComboMaster.GetLBText( MasterSel , MasterSeq );

	}
	
	if ( MasterSeq.IsEmpty() ) {
		AfxMessageBox("Must Select a Master Sequence");
		return;
	}
	
	m_DisplayVars->GetStcGroup().SetMasterSeq( MasterSeq );

#ifdef _WIN32
	static char Filter[] = 
"PDB (*.pdb*)|*.pdb*|\
Protein Pred (*.phd*)|*.phd*|\
Preditor (*.prd*)|*.prd*|\
SS Pred (*.ssp*)|*.ssp*|\
DSSP Files (*.dss*)|*.dss*|\
PSDB Files (*.psd*)|*.psd*|\
User Defined (*.stu*)|*.stu*|\
All Files (*.*)|*.*||";
#else
	static char Filter[] = 
"PDB (*.pdb)|*.pdb|\
Protein Pred (*.phd)|*.phd|\
Preditor (*.prd)|*.prd|\
SS Pred (*.ssp)|*.ssp|\
DSSP Files (*.dss)|*.dss|\
PSDB Files (*.psd)|*.psd|\
User Defined (*.stu)|*.stu|\
All Files (*.*)|*.*||";
#endif

	CFileDialog tDlg( TRUE, NULL, NULL, 
		OFN_HIDEREADONLY, 
		Filter, NULL
	);
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	
	if ( !pDoc->GetDataTypeValuesFile( tDlg.GetPathName(), &m_DisplayVars->GetStcGroup() ) ) {
		AfxMessageBox ("Get Data Type Values Fails" );
		return;
	}

	if ( !pDoc->SetStructureAlignment(m_DisplayVars) ) {
		AfxMessageBox("Set Structure Alignment Fails" );
		return;
	}

#ifndef _WIN32
	m_DisplayVars->GetStcGroup().AddFileName( tDlg.GetFileTitle() );
#else
	m_DisplayVars->GetStcGroup().AddFileName( tDlg.GetFileName() );
#endif

	ResetData();
//	InitDataTypeList();

	pDoc->SetModifiedFlag();

}


void CStructurePropDialog::OnSelchangeDataTypeList()
{
	// TODO: Add your control notification handler code here
	if ( !m_ModifyAll ) {
		int Count = m_DataTypeList.GetCurSel();
		if (Count != LB_ERR ) {
			POSITION Pos = m_DataLabelList.GetHeadPosition();
			while ( Pos != NULL ) {
				StcDataType *pDT = (StcDataType *)m_DataLabelList.GetNext(Pos);
				// CListBox
				if ( Count-- == 0 ) {
					m_DisplayVars->GetStcGroup().SetCurrentDataType( *pDT->DataType );
					break;
				}
			}
		}
	} else {

		StcDataType *pDT;
		int Count = m_DataTypeList.GetCurSel();
		if (Count != LB_ERR ) {
			POSITION Pos = m_DataLabelList.GetHeadPosition();
			while ( Pos != NULL ) {
				pDT = (StcDataType *)m_DataLabelList.GetNext(Pos);
				// CListBox
				if ( Count-- == 0 ) {
					break;
				}
			}

			Pos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( Pos != NULL ) {
				CDisplayVars *pDV = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(Pos);
				// CListBox
				pDV->GetStcGroup().SetCurrentDataType( *pDT->DataType );
			}
		}

	}

	pDoc->SetModifiedFlag();
	
}

void CStructurePropDialog::OnDatasetdet()
{
	// TODO: Add your control notification handler code here
	OnDblclkDataTypeList();
}

void CStructurePropDialog::OnDblclkDataTypeList()
{
	// TODO: Add your control notification handler code here
	int CurSel;

	if ( (CurSel = m_DataTypeList.GetCurSel()) == LB_ERR ) return;

	int i=0;
	
	StcDataType *pDT;

	POSITION Pos = m_DataLabelList.GetHeadPosition();
	while ( Pos != NULL ) {
		pDT = (StcDataType *)m_DataLabelList.GetNext(Pos);
		
		if ( i == CurSel ) break;

		i++;
			
	}

	CMapWordToPtr *ColorMap = pDT->ColorMap;	// Convience pointer

	CStcDataDet tDlg;
	
	tDlg.m_ColorMap = ColorMap;
	
	tDlg.DoModal();
	
}
