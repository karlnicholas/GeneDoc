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
// pdbdialo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPDBDialog dialog

typedef struct {
	COLORREF rgbText;
	COLORREF rgbBack;
} stcPDBCOLOR;

class CPDBDialog : public CDialog
{
// Construction
public:
	CPDBDialog(CWnd* pParent = NULL);	// standard constructor
	CPtrList m_ColorList;

// Dialog Data
	//{{AFX_DATA(CPDBDialog)
	enum { IDD = IDD_PDBDIALOG };
	CListBox	m_SideColorList;
	BOOL	m_ClearAll;
	BOOL	m_IncludeBase;
	BOOL	m_SafeMode;
	int		m_PDBOffset;
	BOOL	m_DispSidechain;
	CString	m_SideDisp;
	CString	m_ComboBack;
	int		m_ShadeWhich;
	BOOL	m_ExcludeO;
	BOOL	m_GroupSel;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPDBDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnOK();
	afx_msg void OnDispside();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
