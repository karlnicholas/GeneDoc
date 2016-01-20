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
// CGroupProp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupProp dialog


CGroupProp::CGroupProp():CPropertyPage(CGroupProp::IDD)
{

	//{{AFX_DATA_INIT(CGroupProp)
	m_ModifyAll = FALSE;
	m_ColorSeqNames = FALSE;
	m_GroupConsLevel = 0;
	m_PCRLevel = 0;
	//}}AFX_DATA_INIT
}


CGroupProp::~CGroupProp()
{
}

void CGroupProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupProp)
	DDX_Control(pDX, IDC_GROUPPCRSIM, m_PCRSimilarities);
	DDX_Control(pDX, IDC_DELETEGROUP, m_DeleteGroup);
	DDX_Control(pDX, IDC_REMOVESEQ, m_RemoveSeq);
	DDX_Control(pDX, IDC_SEQADD, m_SeqAdd);
	DDX_Control(pDX, IDC_GROUPCOLOR, m_GroupColor);
	DDX_Control(pDX, IDC_GROUPCOMBO, m_GroupCombo);
	DDX_Control(pDX, IDC_SEQLIST, m_SequenceList);
	DDX_Check(pDX, IDC_MODIFYALL, m_ModifyAll);
	DDX_Check(pDX, IDC_COLORSEQNAMES, m_ColorSeqNames);
	DDX_Text(pDX, IDC_GROUPCONSLEVEL, m_GroupConsLevel);
	DDV_MinMaxDouble(pDX, m_GroupConsLevel, 0., 100.);
	DDX_Text(pDX, IDC_GROUPPCRLEVEL, m_PCRLevel);
	DDV_MinMaxDouble(pDX, m_PCRLevel, 0., 100.);
	//}}AFX_DATA_MAP
}

BOOL CGroupProp::OnStyleClicked(UINT /*nCmdID*/)
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

BEGIN_MESSAGE_MAP(CGroupProp, CPropertyPage)
	//{{AFX_MSG_MAP(CGroupProp)
	ON_BN_CLICKED(IDC_NEWGROUP, OnNewgroup)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_GROUPTEXTCOLOR, OnGrouptextcolor)
	ON_BN_CLICKED(IDC_GROUPBACKCOLOR, OnGroupbackcolor)
	ON_LBN_DBLCLK(IDC_SEQLIST, OnDblclkSeqlist)
	ON_CBN_SELCHANGE(IDC_GROUPCOMBO, OnSelchangeGroupcombo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MODIFYALL, OnModifyall)
	ON_LBN_SELCHANGE(IDC_SEQLIST, OnSelchangeSeqlist)
	ON_BN_CLICKED(IDC_SEQADD, OnSeqadd)
	ON_LBN_SELCANCEL(IDC_SEQLIST, OnSelcancelSeqlist)
	ON_BN_CLICKED(IDC_REMOVESEQ, OnRemoveseq)
	ON_BN_CLICKED(IDC_DELETEGROUP, OnDeletegroup)
	ON_BN_CLICKED(IDC_COLORSEQNAMES, OnColorseqnames)
	ON_EN_CHANGE(IDC_GROUPCONSLEVEL, OnChangeGroupconslevel)
	ON_EN_CHANGE(IDC_GROUPPCRLEVEL, OnChangeGrouppcrlevel)
	ON_CBN_EDITCHANGE(IDC_GROUPPCRSIM, OnEditchangeGrouppcrsim)
	ON_CBN_SELCHANGE(IDC_GROUPPCRSIM, OnSelchangeGrouppcrsim)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGroupProp message handlers

BOOL CGroupProp::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	POSITION tPos;
	//
	CDisplayVars *DisplayVars;
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list

	if ( pGSFiller != NULL ) {

		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			
			GroupDisplay *pGD = new GroupDisplay;
			pGD->DisplayGroup = tCGSeg->m_DisplayGroup;
			pGD->pCGSeg = tCGSeg;
				
			if ( tCGSeg->m_DisplayGroup != 0 ) {

				DisplayVars = (CDisplayVars*)pDoc->m_UserVars.m_DisplayVars.GetAt( 
					pDoc->m_UserVars.m_DisplayVars.FindIndex( pGD->DisplayGroup -1 )
				);
				
				DisplayVars->GetTitleColors( &pGD->TextColor, &pGD->BkColor );
			} else {
				pGD->TextColor = RGB(0,0,0);
				pGD->BkColor = RGB(255,255,255);
			}
				
			// CListBox
			int idx = m_SequenceList.AddString ( (const char *)tCGSeg->GetTitle() );

			m_SequenceList.SetItemDataPtr( idx, pGD );
	
		}
	}

	

	// CPtrList
	tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
	int i = 0;
	
	CString CurrentGroup;
	
	while ( tPos != NULL ) {

		DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);

		if ( i == 0 ) {
			CurrentGroup = DisplayVars->GetGroupName();
		}

		// CComboBox
		int iind = m_GroupCombo.AddString( DisplayVars->GetGroupName() );
		m_GroupCombo.SetItemDataPtr( iind, DisplayVars );
		
		i++;

	}
	
	if ( CurrentGroup.GetLength() != 0 ) {
		m_DeleteGroup.EnableWindow(TRUE);
	} else {
		m_DeleteGroup.EnableWindow(FALSE);
	}


	SetDisplayGroup( CurrentGroup );

	m_SeqAdd.EnableWindow(FALSE);
	m_RemoveSeq.EnableWindow(FALSE);

	if ( m_ModifyAll ) {
		m_GroupCombo.SetCurSel(-1);
	
		// CComboBox
		m_GroupCombo.EnableWindow(FALSE);
	}

	CenterWindow();
	
	m_PCRSimilarities.SendMessage( WM_SETTEXT, 0, (LPARAM)((const char *)m_InitSimilarities) );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void 
CGroupProp::SetSeqColors()
{

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list

	if ( pGSFiller != NULL ) {

		int idx = 0;

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			
			GroupDisplay *pGD = (GroupDisplay *)m_SequenceList.GetItemDataPtr(idx);

			pGD->DisplayGroup = tCGSeg->m_DisplayGroup;
			pGD->pCGSeg = tCGSeg;

			if ( tCGSeg->m_DisplayGroup != 0 ) {

				CDisplayVars *DisplayVars = (CDisplayVars*)pDoc->m_UserVars.m_DisplayVars.GetAt( 
					pDoc->m_UserVars.m_DisplayVars.FindIndex( pGD->DisplayGroup-1 )
				);
				
				DisplayVars->GetTitleColors( &pGD->TextColor, &pGD->BkColor );
			} else {
				pGD->TextColor = RGB(0,0,0);
				pGD->BkColor = RGB(255,255,255);
			}
			
			idx++;
				
			// CListBox
		}
	}

}

void 
CGroupProp::SetDisplayGroup( const CString& GroupName )
{
	CDisplayVars *DisplayVars;

	if ( GroupName.GetLength() == 0 && m_CurrentGroupName.GetLength() == 0 ) return;
	
	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();
	CGroupPropertySheet *pPS = (CGroupPropertySheet *)pPropertySheet;

	if ( m_CurrentGroupName.GetLength() == 0 ) {
		// Add Property Sheets for first time
		if ( pPS->GetPageCount() == 1 ) {
			pPS->AddPage( &pPS->m_ShadeModePage );
			pPS->AddPage( &pPS->m_PropertyGroupPage );
			pPS->AddPage( &pPS->m_StructurePage );
			pPS->AddPage( &pPS->m_IdentityPage );
		}
		
	} else {
		// Here to save changes on old group.
		
		if ( m_ModifyAll ) {

			POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
		
				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[0], 
					DisplayVars->GetProperty().GetArray(0) 
				);
		
				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[1], 
					DisplayVars->GetProperty().GetArray(1) 
				);

				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[2], 
					DisplayVars->GetProperty().GetArray(2) 
				);
				
				DisplayVars->SetPropStyle( pPS->m_PropertyGroupPage.m_PropStyle );
		
				if ( DisplayVars->GetModeConserved() == SHADEPROPERTY ) {
					DisplayVars->SetLastShadeLevel( pPS->m_PropertyGroupPage.m_CurrentPropLevel	+ SHADELEVEL2);
				}

				DisplayVars->SetPrimaryLevel( pPS->m_ShadeModePage.m_PrimaryLevel );
				DisplayVars->SetSecondaryLevel( pPS->m_ShadeModePage.m_SecondaryLevel );
				DisplayVars->SetTertiaryLevel( pPS->m_ShadeModePage.m_TertiaryLevel );
				
				DisplayVars->SetModeConserved( pPS->m_ShadeModePage.m_ModeConserved );
				DisplayVars->SetDiffMode( pPS->m_ShadeModePage.m_DiffMode );
				DisplayVars->SetResidueMode( pPS->m_ShadeModePage.m_ResidueMode );
				DisplayVars->SetLastShadeLevel( pPS->m_ShadeModePage.m_ShadeLevel );
				DisplayVars->SetGroupEnabled( pPS->m_ShadeModePage.m_GroupEnabled );

				DisplayVars->SetConsSubStyle( pPS->m_ShadeModePage.m_ConsSubStyle );

 				// Identity Page
				CPtrList *pList = DisplayVars->GetIdentList();
				pList->RemoveAll();
				POSITION xPos = pPS->m_IdentityPage.m_IdentList.GetHeadPosition();
				while ( xPos != NULL ) {
					pList->AddTail( pPS->m_IdentityPage.m_IdentList.GetNext(xPos));
				}
				DisplayVars->SetIdentColors( pPS->m_IdentityPage.m_rgbText, pPS->m_IdentityPage.m_rgbBack );
				DisplayVars->SetIdentDisplayStyle( pPS->m_IdentityPage.m_IdentDisplayStyle );
				
				pDoc->SetModifiedFlag();
			
			}

		} else {
			POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
			DisplayVars = NULL;
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
				if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
			}
	
			if ( DisplayVars != NULL ) {

				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[0], 
					DisplayVars->GetProperty().GetArray(0) 
				);
		
				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[1], 
					DisplayVars->GetProperty().GetArray(1) 
				);
		
				SetPropertyArray ( 
					&pPS->m_PropertyGroupPage.m_PropertyArray[2], 
					DisplayVars->GetProperty().GetArray(2) 
				);
				
				DisplayVars->SetPropStyle( pPS->m_PropertyGroupPage.m_PropStyle );
		
				if ( DisplayVars->GetModeConserved() == SHADEPROPERTY ) {
					DisplayVars->SetLastShadeLevel( pPS->m_PropertyGroupPage.m_CurrentPropLevel	+ SHADELEVEL2);
				}

				pDoc->SetModifiedFlag();
		
			
				DisplayVars->SetPrimaryLevel( pPS->m_ShadeModePage.m_PrimaryLevel );
				DisplayVars->SetSecondaryLevel( pPS->m_ShadeModePage.m_SecondaryLevel );
				DisplayVars->SetTertiaryLevel( pPS->m_ShadeModePage.m_TertiaryLevel );
				
				DisplayVars->SetModeConserved( pPS->m_ShadeModePage.m_ModeConserved );
				DisplayVars->SetDiffMode( pPS->m_ShadeModePage.m_DiffMode );
				DisplayVars->SetResidueMode( pPS->m_ShadeModePage.m_ResidueMode );
				DisplayVars->SetLastShadeLevel( pPS->m_ShadeModePage.m_ShadeLevel );
				DisplayVars->SetGroupEnabled( pPS->m_ShadeModePage.m_GroupEnabled );

				DisplayVars->SetConsSubStyle( pPS->m_ShadeModePage.m_ConsSubStyle );

				// Identity Page
				CPtrList *pList = DisplayVars->GetIdentList();
				pList->RemoveAll();
				tPos = pPS->m_IdentityPage.m_IdentList.GetHeadPosition();
				while ( tPos != NULL ) {
					pList->AddTail( pPS->m_IdentityPage.m_IdentList.GetNext(tPos));
				}
				DisplayVars->SetIdentColors( pPS->m_IdentityPage.m_rgbText, pPS->m_IdentityPage.m_rgbBack );
				DisplayVars->SetIdentDisplayStyle( pPS->m_IdentityPage.m_IdentDisplayStyle );

			}
		
		}
		pDoc->m_UserVars.m_BackColor0 = pPS->m_ShadeModePage.m_BackColor0;
		pDoc->m_UserVars.m_ForeColor0 = pPS->m_ShadeModePage.m_ForeColor0;
		pDoc->m_UserVars.m_BackColor60 = pPS->m_ShadeModePage.m_BackColor60;
		pDoc->m_UserVars.m_ForeColor60 = pPS->m_ShadeModePage.m_ForeColor60;
		pDoc->m_UserVars.m_BackColor80 = pPS->m_ShadeModePage.m_BackColor80;
		pDoc->m_UserVars.m_ForeColor80 = pPS->m_ShadeModePage.m_ForeColor80;
		pDoc->m_UserVars.m_BackColor100 = pPS->m_ShadeModePage.m_BackColor100;
		pDoc->m_UserVars.m_ForeColor100 = pPS->m_ShadeModePage.m_ForeColor100;
	}


	m_CurrentGroupName = GroupName;
	
	// Get New DisplayVars ...
	DisplayVars = NULL;
	POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);

		if ( GroupName == DisplayVars->GetGroupName() ) break;
		
	}
	
	if ( DisplayVars != NULL ) {
		// init the PropertyPages with current values.
		// TODO: Need more work
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(0), &pPS->m_PropertyGroupPage.m_PropertyArray[0] );
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(1), &pPS->m_PropertyGroupPage.m_PropertyArray[1] );
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(2), &pPS->m_PropertyGroupPage.m_PropertyArray[2] );

		pPS->m_PropertyGroupPage.m_PropStyle = DisplayVars->GetPropStyle();
		pPS->m_PropertyGroupPage.pDoc = pDoc;
		if ( DisplayVars->GetLastShadeLevel() != SHADELEVEL0 ) {
			pPS->m_PropertyGroupPage.m_CurrentPropLevel	= DisplayVars->GetLastShadeLevel() - SHADELEVEL2;
		} else {
			pPS->m_PropertyGroupPage.m_CurrentPropLevel	= 0;
		}

		pPS->m_PropertyGroupPage.ResetData();
		
		// Structure Page.
		pPS->m_StructurePage.pDoc = pDoc;
		pPS->m_StructurePage.m_DisplayVars = DisplayVars;
		pPS->m_StructurePage.m_ModifyAll = m_ModifyAll;
		pPS->m_StructurePage.ResetData();
		
		// Identity Page
		CPtrList *pList = DisplayVars->GetGroupList();
		pPS->m_IdentityPage.m_SegList.RemoveAll();
		tPos = pList->GetHeadPosition();
		while (tPos != NULL ) {
			CGeneSegment *pCGSeg = (CGeneSegment *)pList->GetNext(tPos);
			if ( pCGSeg->GetStyle() == LINESEQUENCE ) {
				pPS->m_IdentityPage.m_SegList.AddTail(pCGSeg);
			}
		}

		pList = DisplayVars->GetIdentList();
		pPS->m_IdentityPage.m_IdentList.RemoveAll();
		tPos = pList->GetHeadPosition();
		while ( tPos != NULL ) {
			pPS->m_IdentityPage.m_IdentList.AddTail( pList->GetNext(tPos));
		}
		DisplayVars->GetIdentColors( &pPS->m_IdentityPage.m_rgbText, &pPS->m_IdentityPage.m_rgbBack );
		pPS->m_IdentityPage.m_IdentDisplayStyle  = DisplayVars->GetIdentDisplayStyle();

		pPS->m_IdentityPage.m_ModifyAll = m_ModifyAll;
		pPS->m_IdentityPage.ResetData();
				

		// Mode/Style Page
		pPS->m_ShadeModePage.m_PrimaryLevel = DisplayVars->GetPrimaryLevel();
		pPS->m_ShadeModePage.m_SecondaryLevel = DisplayVars->GetSecondaryLevel();
		pPS->m_ShadeModePage.m_TertiaryLevel = DisplayVars->GetTertiaryLevel();
		pPS->m_ShadeModePage.m_ModeConserved = DisplayVars->GetModeConserved();
		pPS->m_ShadeModePage.m_DiffMode = DisplayVars->GetDiffMode();
		pPS->m_ShadeModePage.m_ResidueMode = DisplayVars->GetResidueMode();
		pPS->m_ShadeModePage.m_ShadeLevel  = DisplayVars->GetLastShadeLevel();
		pPS->m_ShadeModePage.m_GroupEnabled = DisplayVars->GetGroupEnabled();
		pPS->m_ShadeModePage.m_ConsSubStyle = DisplayVars->GetConsSubStyle();
		
		pPS->m_ShadeModePage.m_BackColor0 = pDoc->m_UserVars.m_BackColor0;
		pPS->m_ShadeModePage.m_ForeColor0 = pDoc->m_UserVars.m_ForeColor0;
		pPS->m_ShadeModePage.m_BackColor60 = pDoc->m_UserVars.m_BackColor60;
		pPS->m_ShadeModePage.m_ForeColor60 = pDoc->m_UserVars.m_ForeColor60;
		pPS->m_ShadeModePage.m_BackColor80 = pDoc->m_UserVars.m_BackColor80;
		pPS->m_ShadeModePage.m_ForeColor80 = pDoc->m_UserVars.m_ForeColor80;
		pPS->m_ShadeModePage.m_BackColor100 = pDoc->m_UserVars.m_BackColor100;
		pPS->m_ShadeModePage.m_ForeColor100 = pDoc->m_UserVars.m_ForeColor100;

		pPS->m_ShadeModePage.m_FontWeight = pDoc->m_UserVars.m_FontWeight;
		pPS->m_ShadeModePage.m_FontSize = pDoc->m_UserVars.m_FontSize;

		pPS->m_ShadeModePage.ResetData();

	}	
	// CComboBox
	m_GroupCombo.SelectString( -1, GroupName );

}



void CGroupProp::OnNewgroup()
{
	// TODO: Add your control notification handler code here
	
	CDisplayGroupNameDialog tDlg;
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	CString strGroupName = tDlg.m_GroupName;
	int i;
	for ( i=0; i < strGroupName.GetLength(); ++i ) {
		if ( strGroupName[i] != ' ' ) break;
	}
	strGroupName = strGroupName.Right(strGroupName.GetLength() - i);
	if ( strGroupName.GetLength() != 0 ) {
		char *pc = strGroupName.GetBuffer(strGroupName.GetLength());
		pc += strGroupName.GetLength() - 1;
		while ( *pc == ' ' ) *pc-- = 0;
		strGroupName.ReleaseBuffer();
	}

	if ( strGroupName.IsEmpty() ) {
		AfxMessageBox( "Must Name the Group" );
		return;
	}
	
	CDisplayVars *DisplayVars;
	POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
		if ( strGroupName == DisplayVars->GetGroupName() ) {
			AfxMessageBox( "Duplicate Group Name" );
			return;
		}
	}

	COLORREF TextColor = RGB(0,0,0);
	COLORREF BkColor = RGB(255,255,255);

	CColorDialog    cDlg(BkColor);
	
	while (1) {
        
		if ( cDlg.DoModal() != IDOK ) {
			return;
		}
	        
		BkColor = cDlg.GetColor();
		
		if ( (GetRValue(BkColor) == 255) && (GetGValue(BkColor) == 255) && (GetBValue(BkColor) == 255) ) {
			AfxMessageBox( "Pick a Non White Color please." );
		} else {
			break;
		}
	}
	

	DisplayVars = new CDisplayVars;
	pDoc->m_UserVars.m_DisplayVars.AddTail( DisplayVars );

	// Load User Defaults
	pDoc->GetIniDisplayVars(DisplayVars);

	DisplayVars->SetTitleColors( TextColor, BkColor );
	
	DisplayVars->SetGroupName( strGroupName );
	
	// Project Type flag ...
	
	// CComboBox
	int iind = m_GroupCombo.AddString( strGroupName );
	m_GroupCombo.SetItemDataPtr( iind, DisplayVars );
	
	SetDisplayGroup( strGroupName );

    m_GroupColor.Invalidate();

	m_DeleteGroup.EnableWindow(TRUE);
	// CLIstBox
	if ( m_SequenceList.GetSelCount() ) {
		m_SeqAdd.EnableWindow(TRUE);
		m_RemoveSeq.EnableWindow(TRUE);
	}
}

void CGroupProp::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
		// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( 
		( nIDCtl == IDC_SEQLIST 
		|| nIDCtl == IDC_GROUPCOMBO ) 
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	}

//	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);

}

void CGroupProp::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	char tchBuffer[256]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    GroupDisplay *pGD;
	CDisplayVars *pDV;
    CGeneSegment *pCGSeg;

	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_SEQLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics(lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 7;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pGD = (GroupDisplay *)lpDrawItemStruct->itemData;
			pCGSeg = pGD->pCGSeg;

			m_SequenceList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;
//			sprintf ( tchBuffer, "%s",  (const char *)pCGSeg->GetTitle() );


			SetBkColor ( lpDrawItemStruct->hDC, pGD->BkColor );
			SetTextColor ( lpDrawItemStruct->hDC, pGD->TextColor );

			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
			ExtTextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				ETO_CLIPPED, 
				&rect, 
				tchBuffer, 
				strlen(tchBuffer), 
				NULL
			);

//			TextOut(lpDrawItemStruct->hDC, 
				// lpDrawItemStruct->rcItem.left + OffSet, 
//				lpDrawItemStruct->rcItem.left, 
//				lpDrawItemStruct->rcItem.top, 
//				tchBuffer, 
//				strlen(tchBuffer)
//			);
			
			// Bingo ..
			strncpy ( tchBuffer, pCGSeg->GetDescr(), pCGSeg->GetDescr().GetLength() );
			tchBuffer[pCGSeg->GetDescr().GetLength()] = 0;
			
			for ( i = strlen ( tchBuffer ); i < 100; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left + OffSet, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);

			// 			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.right; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 

			break;
 
		case ODA_SELECT:

			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.right; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);

			break; 
		}
	} else if ( 
		nIDCtl == IDC_GROUPCOLOR  
		&& lpDrawItemStruct->itemID != -1
	) {

                TEXTMETRIC m_TM;
                HGDIOBJ tFont;
                LOGFONT tLOGFONT;
                int tPointSize;
                int tFontWeight;
                memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );


                if ( pDoc->m_UserVars.m_FontWeight == FW_NORMAL) {
                        tFontWeight = FW_NORMAL;
                } else {
                        tFontWeight = FW_BOLD;
                }
        
                tPointSize = pDoc->m_UserVars.m_FontSize;


                strcpy ( tLOGFONT.lfFaceName, "Courier New" );
                tLOGFONT.lfWeight = tFontWeight;
                tLOGFONT.lfHeight = -MulDiv( tPointSize , GetDeviceCaps(lpDrawItemStruct->hDC, LOGPIXELSY), 72);
        
                tFont = CreateFontIndirect( &tLOGFONT );
        
                HGDIOBJ oFont = SelectObject( lpDrawItemStruct->hDC, tFont);

                GetTextMetrics( lpDrawItemStruct->hDC, &m_TM );

                MoveToEx ( lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.left, 
                        lpDrawItemStruct->rcItem.top, 
                        NULL
                );

                LineTo ( lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.left, 
                        lpDrawItemStruct->rcItem.bottom - 1 
                );

                LineTo ( lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.right - 1, 
                        lpDrawItemStruct->rcItem.bottom - 1 
                );

                LineTo ( lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.right - 1, 
                        lpDrawItemStruct->rcItem.top 
                );

                LineTo ( lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.left, 
                        lpDrawItemStruct->rcItem.top 
                );
                
                int hx = (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / 2;
                int hy = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / 2;
                hx -= m_TM.tmAveCharWidth / 2;
                hy -= (m_TM.tmHeight - m_TM.tmInternalLeading) / 2;
                
				COLORREF TextColor, BkColor;
				
				CDisplayVars *DisplayVars = NULL;
				POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
				while ( tPos != NULL ) {
					DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
			
					if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
			
				}
				
				if ( DisplayVars != NULL ) {
					DisplayVars->GetTitleColors( &TextColor, &BkColor );
				} else {
					BkColor = pDoc->m_UserVars.m_BackColor0;
					TextColor = pDoc->m_UserVars.m_ForeColor0;
				}
    
				SetBkColor( lpDrawItemStruct->hDC, BkColor );
				SetTextColor( lpDrawItemStruct->hDC, TextColor );
                // RECT

                TextOut (
                        lpDrawItemStruct->hDC, 
                        lpDrawItemStruct->rcItem.left + hx, 
                        lpDrawItemStruct->rcItem.top + hy, 
                        "G", 1
                );
                

                if ( oFont != NULL ) {
					SelectObject( lpDrawItemStruct->hDC, oFont);
                }

	} else if ( (lpDrawItemStruct->CtlType == ODT_COMBOBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_GROUPCOMBO)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics(lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pDV = (CDisplayVars *)lpDrawItemStruct->itemData;

			// CComboBox
			m_GroupCombo.GetLBText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;
			COLORREF rgbText, rgbBack;
			pDV->GetTitleColors( &rgbText, &rgbBack );
			SetBkColor ( lpDrawItemStruct->hDC, rgbBack );
			SetTextColor ( lpDrawItemStruct->hDC, rgbText );


			TextOut(lpDrawItemStruct->hDC, 
				// lpDrawItemStruct->rcItem.left + OffSet, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);
			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.right; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 

				DrawFocusRect(lpDrawItemStruct->hDC, &rect);
				
			} 

			break;
 
		case ODA_SELECT:

			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.right; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
//			DrawFocusRect(lpDrawItemStruct->hDC, &rect);
			DrawFocusRect(lpDrawItemStruct->hDC, &rect);


			break; 
		}
	}


//	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CGroupProp::OnGrouptextcolor()
{
	// TODO: Add your control notification handler code here

		COLORREF TextColor, BkColor;
				
		CDisplayVars *DisplayVars = NULL;
		POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
		while ( tPos != NULL ) {
			DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
			if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
			
		}

		if ( DisplayVars == NULL ) return;

		DisplayVars->GetTitleColors( &TextColor, &BkColor );

        CColorDialog    tDlg(TextColor);
        
        if ( tDlg.DoModal() != IDOK ) {
                return;
        }
        
        TextColor = tDlg.GetColor();

		DisplayVars->SetTitleColors( TextColor, BkColor );

		SetSeqColors();

		m_GroupColor.Invalidate();
		m_SequenceList.Invalidate();
		m_GroupCombo.Invalidate();
}

void CGroupProp::OnGroupbackcolor()
{
	// TODO: Add your control notification handler code here
		COLORREF TextColor, BkColor;
				
		CDisplayVars *DisplayVars = NULL;
		POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
		while ( tPos != NULL ) {
			DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
			if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
			
		}

		if ( DisplayVars == NULL ) return;

		DisplayVars->GetTitleColors( &TextColor, &BkColor );

        CColorDialog    tDlg(BkColor);

		while (1) {
        
	        if ( tDlg.DoModal() != IDOK ) {
	                return;
	        }
	        
	        BkColor = tDlg.GetColor();
	
			if ( (GetRValue(BkColor) == 255) && (GetGValue(BkColor) == 255) && (GetBValue(BkColor) == 255) ) {
				AfxMessageBox( "Pick a Non White Color please." );
			} else {
				break;
			}
		}

		DisplayVars->SetTitleColors( TextColor, BkColor );

		SetSeqColors();

		m_GroupColor.Invalidate();
		m_SequenceList.Invalidate();
		m_GroupCombo.Invalidate();
}

void CGroupProp::OnDblclkSeqlist()
{
	// TODO: Add your control notification handler code here
	// int SelIdx = m_SequenceList.GetCurSel();
	
	int SelCount = m_SequenceList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_SequenceList.GetSelItems( SelCount, SelArray );
	
	for ( int i=0; i < SelCount; ++i ) {
	
		int SelIdx = SelArray[i];
	
		int Count = 0;
		
		// TODO: Add extra initialization here
		POSITION tPos;
		//
	
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list
	
		if ( pGSFiller != NULL ) {
	
			tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
		
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
				if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
					continue;
				}
	
				if ( Count == SelIdx ) {			
	
					// Manage DisplayVars GroupList
					
					// Is it in a group already?
					if ( tCGSeg->m_DisplayGroup != 0 ) {
						CDisplayVars *DisplayVars = NULL;
						int GrpNum = 0;
						POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
						while ( tPos != NULL ) {
							DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
							GrpNum++;
							if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
						}

						if ( DisplayVars != NULL ) {
							CPtrList *pDVGL = DisplayVars->GetGroupList();
							POSITION oPos = pDVGL->Find( tCGSeg );
							if ( oPos != NULL ) pDVGL->RemoveAt( oPos );
						}
					}
	
					int GrpNum = 0;
					CDisplayVars *DisplayVars;
					POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos != NULL ) {
						DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
						GrpNum++;
						if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
					}
					
					// Check to see if its the same as it was, if so, reset to nogroup.
	
					if ( tCGSeg->m_DisplayGroup == GrpNum ) {
						tCGSeg->m_DisplayGroup = 0;
						GrpNum = 0;
					} else {
	
						CPtrList *pDVGL = DisplayVars->GetGroupList();
						
						pDVGL->AddTail( tCGSeg );
						
						tCGSeg->m_DisplayGroup = GrpNum;
					}
	
					((GroupDisplay*)m_SequenceList.GetItemDataPtr(SelIdx))->DisplayGroup = GrpNum;
					
					break;
				}
				
				Count++;
			}
		}

	}
	
	delete SelArray;

	m_SequenceList.SelItemRange(FALSE, 0, m_SequenceList.GetCount()-1 );

	m_SeqAdd.EnableWindow(FALSE);
	m_RemoveSeq.EnableWindow(FALSE);
	
	SetSeqColors();

	SetDisplayGroup(m_CurrentGroupName);
    
    // CListBox
    m_SequenceList.Invalidate();
}


void CGroupProp::OnSelchangeGroupcombo()
{
	// TODO: Add your control notification handler code here
	
	// CComboBox GetLBText
//	int GrpNum = 0;
//	CDisplayVars *DisplayVars;
//	POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
//	while ( tPos != NULL ) {
//		DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
//		if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
//		GrpNum++;
//	}

	int CurSel = m_GroupCombo.GetCurSel();
	
	CString GroupName;
	
	m_GroupCombo.GetLBText( CurSel, GroupName );

	SetDisplayGroup( GroupName );
	
    m_GroupColor.Invalidate();
	// RedrawWindow();
	
}

void CGroupProp::OnDestroy()
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	if ( !m_CurrentGroupName.IsEmpty() ) {
		SetDisplayGroup("");
	}

	int Count = m_SequenceList.GetCount();
		
	for ( int i =0; i < Count; ++i ) {
		// CLIstBox
		delete (GroupDisplay* )m_SequenceList.GetItemDataPtr(i);
	}
	
}


void CGroupProp::OnModifyall()
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	if ( m_ModifyAll ) {
		m_SaveCurSel = m_GroupCombo.GetCurSel();
	
		m_GroupCombo.SetCurSel(-1);
	
		// CComboBox
		m_GroupCombo.EnableWindow(FALSE);
	
		SetDisplayGroup(m_CurrentGroupName);
		
	} else {
	
		m_GroupCombo.EnableWindow();
		
		m_GroupCombo.SetCurSel( m_SaveCurSel );

		int CurSel = m_GroupCombo.GetCurSel();
		
		CString GroupName;

		if ( CurSel != LB_ERR ) {
		
			m_GroupCombo.GetLBText( CurSel, GroupName );
		    
		    // Force a save of anything done already ...
			m_ModifyAll = 1;
			SetDisplayGroup( GroupName );
		    // switch to new group ...
			m_ModifyAll = 0;
			SetDisplayGroup( GroupName );
		}
		
	    m_GroupColor.Invalidate();
	
	}
	
}

void CGroupProp::OnSelchangeSeqlist()
{
	// TODO: Add your control notification handler code here
	
	int Count = m_SequenceList.GetSelCount();
	
	if ( Count && pDoc->m_UserVars.m_DisplayVars.GetCount() ) {
		m_SeqAdd.EnableWindow(TRUE);
		m_RemoveSeq.EnableWindow(TRUE);
	} else {
		m_SeqAdd.EnableWindow(FALSE);
		m_RemoveSeq.EnableWindow(FALSE);
	}	
}

void CGroupProp::OnSelcancelSeqlist()
{
	// TODO: Add your control notification handler code here
	int Count = m_SequenceList.GetSelCount();
	
	if ( Count && pDoc->m_UserVars.m_DisplayVars.GetCount() ) {
		m_SeqAdd.EnableWindow(TRUE);
		m_RemoveSeq.EnableWindow(TRUE);
	} else {
		m_SeqAdd.EnableWindow(FALSE);
		m_RemoveSeq.EnableWindow(FALSE);
	}	
}

void CGroupProp::OnSeqadd()
{

	// TODO: Add your control notification handler code here
	if ( !pDoc->m_UserVars.m_DisplayVars.GetCount() ) return;

	int SelCount = m_SequenceList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_SequenceList.GetSelItems( SelCount, SelArray );
	
	for ( int i=0; i < SelCount; ++i ) {
	
		int SelIdx = SelArray[i];
	
		int Count = 0;
		
		// TODO: Add extra initialization here
		POSITION tPos;
		//
	
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list
	
		if ( pGSFiller != NULL ) {
	
			tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
		
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
				if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
					continue;
				}
	
				if ( Count == SelIdx ) {			
	
					// Manage DisplayVars GroupList
					
					// Is it in a group already?
					if ( tCGSeg->m_DisplayGroup != 0 ) {
						int GrpNum = 0;
						CDisplayVars *DisplayVars;
						POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
						while ( tPos != NULL ) {
							DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
							GrpNum++;
							if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
						}
					
						CPtrList *pDVGL = DisplayVars->GetGroupList();
						
						POSITION oPos = pDVGL->Find( tCGSeg );
						
						if ( oPos != NULL ) pDVGL->RemoveAt( oPos );
						
					}
	
					int GrpNum = 0;
					CDisplayVars *DisplayVars;
					POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos != NULL ) {
						DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
						GrpNum++;
						if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
					}
					
					// Check to see if its the same as it was, if so, reset to nogroup.
	
					CPtrList *pDVGL = DisplayVars->GetGroupList();
						
					pDVGL->AddTail( tCGSeg );
						
					tCGSeg->m_DisplayGroup = GrpNum;
	
					((GroupDisplay*)m_SequenceList.GetItemDataPtr(SelIdx))->DisplayGroup = GrpNum;
					
					break;
				}
				
				Count++;
			}
		}

	}
	
	delete SelArray;

	m_SequenceList.SelItemRange(FALSE, 0, m_SequenceList.GetCount()-1 );

	m_SeqAdd.EnableWindow(FALSE);
	m_RemoveSeq.EnableWindow(FALSE);
	
	SetSeqColors();

	SetDisplayGroup(m_CurrentGroupName);
    
    // CListBox
    m_SequenceList.Invalidate();
	// RedrawWindow();
	
}


void CGroupProp::OnRemoveseq()
{
	// TODO: Add your control notification handler code here
	if ( !pDoc->m_UserVars.m_DisplayVars.GetCount() ) return;

	int SelCount = m_SequenceList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) return;
	           
	int *SelArray = new int[SelCount];
	
	m_SequenceList.GetSelItems( SelCount, SelArray );
	
	for ( int i=0; i < SelCount; ++i ) {
	
		int SelIdx = SelArray[i];
	
		int Count = 0;
		
		// TODO: Add extra initialization here
		POSITION tPos;
		//
	
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list
	
		if ( pGSFiller != NULL ) {
	
			tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
		
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
				if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
					continue;
				}
	
				if ( Count == SelIdx ) {			
	
					// Manage DisplayVars GroupList
					
					// Is it in a group already?
					if ( tCGSeg->m_DisplayGroup != 0 ) {
						int GrpNum = 0;
						CDisplayVars *DisplayVars;
						POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
						while ( tPos != NULL ) {
							DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
							GrpNum++;
							if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
						}
						
						tCGSeg->m_DisplayGroup = 0;
					
						CPtrList *pDVGL = DisplayVars->GetGroupList();
						
						POSITION oPos = pDVGL->Find( tCGSeg );
						
						if ( oPos != NULL ) pDVGL->RemoveAt( oPos );
						
					}
	
					break;
				}
				
				Count++;
			}
		}

	}
	
	delete SelArray;

	m_SequenceList.SelItemRange(FALSE, 0, m_SequenceList.GetCount()-1 );

	m_SeqAdd.EnableWindow(FALSE);
	m_RemoveSeq.EnableWindow(FALSE);
	
	SetSeqColors();

	SetDisplayGroup(m_CurrentGroupName);
    
    // CListBox
    m_SequenceList.Invalidate();
	// RedrawWindow();
}

void CGroupProp::OnDeletegroup()
{
	// TODO: Add your control notification handler code here

	// TODO: Add extra initialization here
	POSITION tPos;
	//

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	int GrpNum = 0;
	CDisplayVars *DisplayVars = NULL;
	tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
		GrpNum++;
		if ( m_CurrentGroupName == DisplayVars->GetGroupName() ) break;
	}

	if ( pGSFiller != NULL ) {

		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}

			// Is it in a group already?
			if ( tCGSeg->m_DisplayGroup != 0 && tCGSeg->m_DisplayGroup >= GrpNum ) {
				tCGSeg->m_DisplayGroup -= 1;
			}
		}
	}


	CPtrList* GroupList = DisplayVars->GetGroupList();
	tPos = GroupList->GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment*pSeg = (CGeneSegment *)GroupList->GetNext(tPos);
		pSeg->m_DisplayGroup = 0;
	}
	
	CString GroupName = DisplayVars->GetGroupName();


	pDoc->m_UserVars.m_DisplayVars.RemoveAt( pDoc->m_UserVars.m_DisplayVars.Find( DisplayVars ) );

	delete DisplayVars;

	m_GroupCombo.DeleteString( m_GroupCombo.FindString( -1, GroupName) );
	
	if ( m_GroupCombo.GetCount() ) {
	
		m_GroupCombo.GetLBText( 0, GroupName );
		
		m_GroupCombo.SelectString(-1,GroupName);
		
	} else {
		GroupName.Empty();
		
		m_DeleteGroup.EnableWindow(FALSE);
		
		m_SeqAdd.EnableWindow(FALSE);
		m_RemoveSeq.EnableWindow(FALSE);
	}
	
	SetDisplayGroup( GroupName );

	m_GroupColor.Invalidate();

	if ( GroupName.IsEmpty() ) {

		CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();
		CGroupPropertySheet *pPS = (CGroupPropertySheet *)pPropertySheet;

		pPS->RemovePage( &pPS->m_ShadeModePage );
		pPS->RemovePage( &pPS->m_PropertyGroupPage );
		pPS->RemovePage( &pPS->m_StructurePage );
		pPS->RemovePage( &pPS->m_IdentityPage );

	}

	SetSeqColors();

//	Invalidate();
	m_SequenceList.Invalidate();

}

void CGroupProp::OnColorseqnames()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_ColorSeqNames ) {
		pDoc->m_UserVars.m_ColorSeqNames = 1;
	} else {
		pDoc->m_UserVars.m_ColorSeqNames = 0;
	}
	pDoc->SetModifiedFlag();

}

void CGroupProp::OnChangeGroupconslevel()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	pDoc->m_UserVars.m_GroupConsLevel = m_GroupConsLevel;
	pDoc->SetModifiedFlag();
}

void CGroupProp::OnChangeGrouppcrlevel()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	pDoc->m_UserVars.m_PCRLevel = m_PCRLevel;
	pDoc->SetModifiedFlag();
}

void CGroupProp::OnEditchangeGrouppcrsim()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	char Text[32];
	                                     
	m_PCRSimilarities.SendMessage( WM_GETTEXT, 32, (LPARAM)Text );
	pDoc->m_UserVars.m_PCRSimilarities = Text;

	pDoc->SetModifiedFlag();
}

void CGroupProp::OnSelchangeGrouppcrsim()
{
	// TODO: Add your control notification handler code here
		
	int Sel;
	if ( (Sel = m_PCRSimilarities.GetCurSel()) != LB_ERR ) {
		m_PCRSimilarities.GetLBText( Sel, pDoc->m_UserVars.m_PCRSimilarities );
		pDoc->SetModifiedFlag();
	}
	
}
