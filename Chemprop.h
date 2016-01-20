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
// chemprop.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CChemPropProperty dialog

class CChemPropProperty : public CPropertyPage
{
// Construction
public:
	CChemPropProperty(CWnd* pParent = NULL);	// standard constructor
//	CGenedocDoc *pDoc;
	int ChemPropEnabled[12];
	stcChemProp ChemGroup[12];
	stcChemProp ChemGroupRed[12];
	stcChemProp ChemCons[3];

	CButton	*m_ButPropEnab;


// Dialog Data
	//{{AFX_DATA(CChemPropProperty)
	enum { IDD = IDD_CHEMPROP };
	CListBox	m_ChemPropList;
	CListBox	m_PropConsList;
	int		m_Cysteine;
	int		m_ShowProperty;
	BOOL	m_PropEnable;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CChemPropProperty)
	virtual BOOL OnInitDialog();
	afx_msg void OnChempropback();
	afx_msg void OnChempropfore();
	afx_msg void OnPropconsback();
	afx_msg void OnPropconsfore();
	afx_msg void OnDblclkChemprop();
	afx_msg void OnDblclkPropcons();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnCysteine();
	afx_msg void OnReduced();
	afx_msg void OnPropenab();
	afx_msg void OnSelchangeChemprop();
	afx_msg void OnDescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
