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
// searchdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchPropPage dialog

class CSearchPropPage : public CPropertyPage
{
// Construction
public:
	CSearchPropPage();	// standard constructor

	CGenedocDoc *pDoc;
	int m_SearchChanged;
	CPtrList m_listCopy;
	COLORREF m_OverlapColor;

// Dialog Data
	//{{AFX_DATA(CSearchPropPage)
	enum { IDD = IDD_SEARCH };
	CListBox	m_listSearch;
	int		m_ProSite;
	BOOL	m_iEnabled;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSearchPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnEdit();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnTextcolor();
	afx_msg void OnBackcolor();
	afx_msg void OnProsite();
	afx_msg void OnDblclkSearchlist();
	afx_msg void OnLoadfile();
	afx_msg void OnLoadrebase();
	afx_msg void OnMovedown();
	afx_msg void OnMoveup();
	afx_msg void OnOverlap();
	afx_msg void OnWritere();
	afx_msg void OnRebase();
	afx_msg void OnSelchangeSearchlist();
	afx_msg void OnEnabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ReBuildListBox();
	void ColorCopyList();
};
