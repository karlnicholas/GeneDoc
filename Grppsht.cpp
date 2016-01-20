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
// grppsht.cpp : implementation of the CGroupPropertySheet class
//

#include "stdafx.h"

IMPLEMENT_DYNAMIC(CGroupPropertySheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CGroupPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGroupPropertySheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGroupPropertySheet::CGroupPropertySheet(CWnd* pWndParent)
	: CPropertySheet(AFX_IDS_APP_TITLE, pWndParent)
{
	AddPage( &m_GroupPropPage );
	AddPage( &m_ShadeModePage );
	AddPage( &m_PropertyGroupPage );
	AddPage( &m_StructurePage );
	AddPage( &m_IdentityPage );

	m_SetActive = FALSE;
	m_SetActivePage = NULL;

}

CGroupPropertySheet::~CGroupPropertySheet()
{
}


int CGroupPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Add the preview window to the property sheet.
	// Get New DisplayVars ...

#if !defined(_WIN32) || _MSC_VER < 999
	if ( m_SetActivePage != 0 ) {
		SetActivePage ( 0 );
		SetActivePage ( m_SetActivePage );
	} else {
		RemovePage( &m_ShadeModePage );
		RemovePage( &m_PropertyGroupPage );
		RemovePage( &m_StructurePage );
		RemovePage( &m_IdentityPage );
	}
#endif
/*
	if ( !m_SetActive ) {
		if ( m_SetActivePage != 0 ) {
			SetActivePage ( m_SetActivePage );
		}
		m_SetActive = TRUE;
	}
*/

	int nReturn;
	if ((nReturn = CPropertySheet::OnCreate(lpCreateStruct))
		!= 0)
		return nReturn;

	CenterWindow();
	return 0;
}


void CGroupPropertySheet::OnApplyNow()
{
	CMDIFrameWnd* pMDIFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	ASSERT(pMDIFrameWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
	CView* pView = pMDIFrameWnd->MDIGetActive()->GetActiveView();
//	pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
//	m_stylePage.SetModified(FALSE);
//	m_colorPage.SetModified(FALSE);
}

void CGroupPropertySheet::OnShowWindow(BOOL bShow, UINT nStatus) 
{

#if defined(_WIN32) && _MSC_VER > 999
	if ( !m_SetActive ) {
		if ( m_SetActivePage != NULL ) {
			SetActivePage ( m_SetActivePage );
		} else if ( !m_NumGroups ) {
			RemovePage( &m_ShadeModePage );
			RemovePage( &m_PropertyGroupPage );
			RemovePage( &m_StructurePage );
			RemovePage( &m_IdentityPage );
		}
		m_SetActive = TRUE;
	}
#endif


	CPropertySheet::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
