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
// colorbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorBar dialog

class CColorBar : public CDialog
{
// Construction
public:
	CColorBar(CWnd* pParent = NULL);	// standard constructor

	COLORREF m_TextColor;
	COLORREF m_BackColor;
	int m_ShadeLevel;

// Dialog Data
	//{{AFX_DATA(CColorBar)
	enum { IDD = IDD_COLORBAR };
	CListBox	m_ColorList;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	CWnd *m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CColorBar)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDestroy();
	afx_msg void OnDblclkColorlist();
	afx_msg void OnChangeback();
	afx_msg void OnChangetext();
	afx_msg void OnSelchangeColorlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
