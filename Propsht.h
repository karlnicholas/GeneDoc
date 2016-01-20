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
// propsht.h : interface of the CModalDisplayPropSheet class
//
/////////////////////////////////////////////////////////////////////////////

class CModalDisplayPropSheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CModalDisplayPropSheet)
	CModalDisplayPropSheet(CWnd* pWndParent = NULL);

// Attributes
	CDisplayProperty m_DisplayPage;
	CPrintProperty m_PrintPage;
	CShadeModeProperty m_ShadeModePage;
	CRepDlg m_ReportPage;
	CPropertyGroupProperty m_PropertyGroupPage;
	CSearchPropPage m_SearchPropPage;
	CStructurePropDialog m_StructurePage;
	CChemPropProperty m_PhysioChemPage;
	CConfIdent m_IdentityPage;
	CLogOddsPropPage m_LogOddsPropPage;
	CScoreTableProperty m_ScoreTablePage;

#if defined(_WIN32) && _MSC_VER > 999
	CPropertyPage* m_SetActivePage;
#else
	int m_SetActivePage;
#endif

// Operations

protected:
	//{{AFX_MSG(CModalDisplayPropSheet)
	afx_msg void OnApplyNow();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_SetActive;


};
