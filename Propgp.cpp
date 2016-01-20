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
// PropGp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyGroupProperty dialog


CPropertyGroupProperty::CPropertyGroupProperty() : CPropertyPage(CPropertyGroupProperty::IDD)
{
	m_DialogInited = 0;

	//{{AFX_DATA_INIT(CPropertyGroupProperty)
	m_PropStyle = -1;
	//}}AFX_DATA_INIT
}

void CPropertyGroupProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyGroupProperty)
	DDX_Control(pDX, IDC_PROPLEVEL3, m_PropLevel3But);
	DDX_Control(pDX, IDC_PROPLEVEL2, m_PropLevel2But);
	DDX_Control(pDX, IDC_PROPLEVEL1, m_PropLevel1But);
	DDX_Control(pDX, IDC_PROPERTYLIST, m_ListBox);
	DDX_Radio(pDX, IDC_PROPCONSERVED, m_PropStyle);
	//}}AFX_DATA_MAP
}

BOOL CPropertyGroupProperty::OnStyleClicked(UINT /*nCmdID*/)
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

BEGIN_MESSAGE_MAP(CPropertyGroupProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyGroupProperty)
	ON_BN_CLICKED(IDC_PROPDEL, OnPropdel)
	ON_BN_CLICKED(IDC_PROPEDIT, OnPropedit)
	ON_LBN_DBLCLK(IDC_PROPERTYLIST, OnDblclkPropertylist)
	ON_BN_CLICKED(IDC_PROPLEVEL1, OnProplevel1)
	ON_BN_CLICKED(IDC_PROPLEVEL2, OnProplevel2)
	ON_BN_CLICKED(IDC_PROPLEVEL3, OnProplevel3)
	ON_BN_CLICKED(IDC_PROPNEW, OnPropnew)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_PROPTEXTCOLOR, OnProptextcolor)
	ON_BN_CLICKED(IDC_PROPBKCOLOR, OnPropbkcolor)
	ON_BN_CLICKED(IDC_LEVELDEFAULTS, OnLeveldefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropertyGroupProperty message handlers
// CreateBitmap

BOOL CPropertyGroupProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_DialogInited = 1;

	ResetData();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CPropertyGroupProperty::ResetData()
{

	if ( !m_DialogInited) return;

	ReBuildListBox(m_CurrentPropLevel);
	
	if ( m_ListBox.GetCount() ) {
		m_ListBox.SetCurSel(0);
	}
	
	if ( m_DialogInited ) UpdateData(FALSE);

}

void
CPropertyGroupProperty::ReBuildListBox(int PropLevel)
{
	char tBuff[MAXPROPERTYGROUP + 10];
	PropertyStruct *tPS;
	
	m_ListBox.ResetContent();
	m_CurrentPropLevel = PropLevel;
	         
	// CListBox
	int count = m_PropertyArray[PropLevel].GetSize();
	for ( int i = 0; i < count; ++i ) {
		tPS = (PropertyStruct *)m_PropertyArray[PropLevel][i];
		tPS->RowNum = i + 1;
		sprintf( tBuff, "%s", tPS->Group );
		m_ListBox.AddString ( tBuff );
		m_ListBox.SetItemDataPtr ( i, tPS );
	}

	// Set Buttons to indicate which prop level
	// CButton
	if ( PropLevel == 0 ) {
		m_PropLevel1But.SetState(1);
		m_PropLevel2But.SetState(0);
		m_PropLevel3But.SetState(0);
	} else if ( PropLevel == 1 ) {
		m_PropLevel1But.SetState(0);
		m_PropLevel2But.SetState(1);
		m_PropLevel3But.SetState(0);
	} else if ( PropLevel == 2 ) {
		m_PropLevel1But.SetState(0);
		m_PropLevel2But.SetState(0);
		m_PropLevel3But.SetState(1);
	}

	UpdateData(FALSE);

}


CPropertyGroupProperty::~CPropertyGroupProperty()
{
	PropertyStruct *tPS;
	
	// CListBox
	for ( int PropLevel = 0; PropLevel < 3; ++PropLevel ) {
		int count = m_PropertyArray[PropLevel].GetSize();
		for ( int i = 0; i < count; ++i ) {
			tPS = (PropertyStruct *)m_PropertyArray[PropLevel][i];
			delete tPS;
		}
	}

	// TODO: Add your message handler code here
}

void CPropertyGroupProperty::OnPropdel()
{
	// TODO: Add your control notification handler code here
	
	// CListBox	
	int CurSel;
	if ( (CurSel = m_ListBox.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}
	
	// CPtrArray
	delete (PropertyStruct *)m_PropertyArray[m_CurrentPropLevel][CurSel];
	m_PropertyArray[m_CurrentPropLevel].RemoveAt(CurSel);
	
	ReBuildListBox(m_CurrentPropLevel);
	
	if ( m_ListBox.GetCount() != CurSel ) {
		m_ListBox.SetCurSel ( CurSel );
	} else {
		m_ListBox.SetCurSel ( CurSel - 1);
	}
	m_ListBox.SetFocus();

}

void CPropertyGroupProperty::OnPropedit()
{
	// TODO: Add your control notification handler code here
	
	int CurSel;
	if ( (CurSel = m_ListBox.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}

	PropertyStruct *tPS = (PropertyStruct *)m_PropertyArray[m_CurrentPropLevel][CurSel];

	char tBuff[10];
	itoa(tPS->RowNum, tBuff, 10);

	CPropertyEditDlg	tDlg;
	
	tDlg.m_PropNum = tBuff;
	tDlg.m_PropCont = tPS->Group;
    
    if ( tDlg.DoModal() != IDOK ) {
    	return;
    }

	strncpy ( tPS->Group, tDlg.m_PropCont, MAXPROPERTYGROUP );
	char *pc = tPS->Group;
	while (*pc != 0 ) {
		*pc = toupper(*pc);
		pc++;
	}

	m_PropertyArray[m_CurrentPropLevel].SetAt(CurSel, tPS );
    
	ReBuildListBox(m_CurrentPropLevel);
	
	m_ListBox.SetCurSel( CurSel );
	m_ListBox.SetFocus();

}

void CPropertyGroupProperty::OnDblclkPropertylist()
{
	// TODO: Add your control notification handler code here
	OnPropedit();
}

void CPropertyGroupProperty::OnProplevel1()
{
	// TODO: Add your control notification handler code here

	// Do set list box to level 1 values

	ReBuildListBox(0);

	m_ListBox.SetCurSel(0);
	m_ListBox.SetFocus();
}

void CPropertyGroupProperty::OnProplevel2()
{
	// TODO: Add your control notification handler code here
	// Do set list box to level 2 values
	
	
	ReBuildListBox(1);

	m_ListBox.SetCurSel(0);
	m_ListBox.SetFocus();

}

void CPropertyGroupProperty::OnProplevel3()
{
	// TODO: Add your control notification handler code here
	// Do set list box to level 3 values

	ReBuildListBox(2);

	m_ListBox.SetCurSel(0);
	m_ListBox.SetFocus();
	
}

void CPropertyGroupProperty::OnPropnew()
{
	// TODO: Add your control notification handler code here
	int count = m_PropertyArray[m_CurrentPropLevel].GetSize();
	count++;
	char tBuff[10];
	itoa(count, tBuff, 10);

	CPropertyEditDlg	tDlg;
	
	tDlg.m_PropNum = tBuff;
    tDlg.m_PropCont = "";
    
    if ( tDlg.DoModal() != IDOK ) {
    	return;
    }
    
	PropertyStruct *tPS;
	tPS = new PropertyStruct;
	if ( tPS == 0 ) {
		AfxMessageBox("OnPropNew:new:fail:1");
		return;
	}
	tPS->RowNum = count;
	tPS->TextColor = RGB(255,255,255);
	tPS->BkColor = RGB(0,0,0);

	strncpy ( tPS->Group, tDlg.m_PropCont, MAXPROPERTYGROUP );
	char *pc = tPS->Group;
	while (*pc != 0 ) {
		*pc = toupper(*pc);
		pc++;
	}

	m_PropertyArray[m_CurrentPropLevel].Add( tPS );
    
	ReBuildListBox(m_CurrentPropLevel);

	m_ListBox.SetCurSel ( m_ListBox.GetCount() - 1 );
	m_ListBox.SetFocus();

}


void CPropertyGroupProperty::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
    char tchBuffer[256]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    PropertyStruct * tPS;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_PROPERTYLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 2;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			tPS = (PropertyStruct *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%2d:", tPS->RowNum );
			
//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));
			
			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				3
			);
			
			m_ListBox.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, tPS->BkColor );
			SetTextColor ( lpDrawItemStruct->hDC, tPS->TextColor );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left + OffSet, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);
			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 

			break;
 
		case ODA_SELECT:
 
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);
			
			break; 
		}
	
	}

//	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);

}

void CPropertyGroupProperty::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( (
		lpMeasureItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpMeasureItemStruct->CtlID == IDC_PROPERTYLIST)
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	}

//	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CPropertyGroupProperty::OnProptextcolor()
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ListBox.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}

	PropertyStruct *tPS = (PropertyStruct *)m_PropertyArray[m_CurrentPropLevel][CurSel];

	CColorDialog tDlg(tPS->TextColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	tPS->TextColor = tDlg.GetColor();

	ReBuildListBox(m_CurrentPropLevel);
	
	m_ListBox.SetCurSel(CurSel);
	m_ListBox.SetFocus();
}

void CPropertyGroupProperty::OnPropbkcolor()
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ( (CurSel = m_ListBox.GetCurSel()) == LB_ERR ) {
		AfxMessageBox( "Need to Select a Group to Delete" );
		return;
	}

	PropertyStruct *tPS = (PropertyStruct *)m_PropertyArray[m_CurrentPropLevel][CurSel];

	CColorDialog tDlg(tPS->BkColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	tPS->BkColor = tDlg.GetColor();

	ReBuildListBox(m_CurrentPropLevel);
	
	m_ListBox.SetCurSel(CurSel);
	m_ListBox.SetFocus();
	
}


void CPropertyGroupProperty::OnLeveldefaults() 
{
	// TODO: Add your control notification handler code here
	
	SetPropertyDefault( &m_PropertyArray[m_CurrentPropLevel], m_CurrentPropLevel, pDoc->m_UserVars.m_ProjectType );
	
	ReBuildListBox(m_CurrentPropLevel);

	m_ListBox.SetCurSel(0);
	m_ListBox.SetFocus();
	
}
