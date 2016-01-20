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
// propsht.cpp : implementation of the CModalDisplayPropSheet class
//

#include "stdafx.h"

IMPLEMENT_DYNAMIC(CModalDisplayPropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CModalDisplayPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModalDisplayPropSheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModalDisplayPropSheet::CModalDisplayPropSheet(CWnd* pWndParent)
	: CPropertySheet(AFX_IDS_APP_TITLE, pWndParent)
{
	AddPage( &m_DisplayPage );
	AddPage( &m_PrintPage );
	AddPage( &m_ShadeModePage );
	AddPage( &m_ReportPage );
	AddPage( &m_PropertyGroupPage );
	AddPage( &m_SearchPropPage );
	AddPage( &m_StructurePage );
	AddPage( &m_PhysioChemPage );
	AddPage( &m_IdentityPage );
	AddPage( &m_LogOddsPropPage );
	AddPage( &m_ScoreTablePage );
	m_SetActive = FALSE;
	m_SetActivePage = NULL;
}

int CModalDisplayPropSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Add the preview window to the property sheet.

#if !defined(_WIN32) || _MSC_VER < 999
	if ( m_SetActivePage != 0 ) {
		SetActivePage ( m_SetActivePage );
	}
	m_SetActive = TRUE;
#endif
	
	int nReturn;
	if ((nReturn = CPropertySheet::OnCreate(lpCreateStruct))
		!= 0)
		return nReturn;

	CenterWindow();
	return 0;
}


void CModalDisplayPropSheet::OnApplyNow()
{
	CMDIFrameWnd* pMDIFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	ASSERT(pMDIFrameWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
	CView* pView = pMDIFrameWnd->MDIGetActive()->GetActiveView();
//	pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
//	m_stylePage.SetModified(FALSE);
//	m_colorPage.SetModified(FALSE);
}


void CModalDisplayPropSheet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	// TODO: Add your message handler code here
#if defined(_WIN32) && _MSC_VER > 999
	if ( !m_SetActive ) {
		if ( m_SetActivePage != NULL ) {
			SetActivePage ( m_SetActivePage );
		}
		m_SetActive = TRUE;
	}
#endif			
	
	CPropertySheet::OnShowWindow(bShow, nStatus);
	
}
