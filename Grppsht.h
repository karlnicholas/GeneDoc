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
// grppsht.h : interface of the CGroupPropertySheet class
//
/////////////////////////////////////////////////////////////////////////////

class CGroupPropertySheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CGroupPropertySheet)
	CGroupPropertySheet(CWnd* pWndParent = NULL);
	~CGroupPropertySheet();

// Attributes
	CGroupProp		m_GroupPropPage;

	CShadeModeProperty m_ShadeModePage;
	CPropertyGroupProperty m_PropertyGroupPage;
	CStructurePropDialog	m_StructurePage;
	CConfIdent			m_IdentityPage;

#if defined(_WIN32) && _MSC_VER > 999
	CPropertyPage *m_SetActivePage;
#else
	int m_SetActivePage;
#endif

	int m_SetActive;
	int m_NumGroups;
	
// Operations

protected:
	//{{AFX_MSG(CGroupPropertySheet)
	afx_msg void OnApplyNow();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
