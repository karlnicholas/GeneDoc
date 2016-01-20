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
// confiden.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfIdent dialog

class CConfIdent : public CPropertyPage
{
// Construction
public:
	CConfIdent();	// standard constructor
	
	CPtrList	m_IdentList;
	CPtrList	m_SegList;
	COLORREF	m_rgbText;
	COLORREF	m_rgbBack;

	int m_ModifyAll;
	int m_DialogInited;
	void ResetData();

// Dialog Data
	//{{AFX_DATA(CConfIdent)
	enum { IDD = IDD_CONFIDENT };
	CButton	m_TextButton;
	CButton	m_BackButton;
	CListBox	m_listSequence;
	int		m_IdentDisplayStyle;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CConfIdent)
	afx_msg void OnBackcolor();
	afx_msg void OnTextcolor();
	afx_msg void OnDblclkListsequence();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnToggle();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
