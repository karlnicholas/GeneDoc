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
// PropGp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyGroupProperty dialog

class CPropertyGroupProperty : public CPropertyPage
{
// Construction
public:
	CPropertyGroupProperty();	// standard constructor
	~CPropertyGroupProperty();	// standard destructor

	void ResetData();

// Dialog Data
	//{{AFX_DATA(CPropertyGroupProperty)
	enum { IDD = IDD_CONFPROPERTY };
	CButton	m_PropLevel3But;
	CButton	m_PropLevel2But;
	CButton	m_PropLevel1But;
	CListBox	m_ListBox;
	int		m_PropStyle;
	//}}AFX_DATA

	CPtrArray m_PropertyArray[3]; // Hoding a list of ShadePairStruct's
	int m_CurrentPropLevel;
	CGenedocDoc *pDoc;
	void ReBuildListBox(int PropLevel);
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog(); 

	int m_DialogInited;

	// Generated message map functions
	//{{AFX_MSG(CPropertyGroupProperty)
	afx_msg void OnPropdel();
	afx_msg void OnPropedit();
	afx_msg void OnDblclkPropertylist();
	afx_msg void OnProplevel1();
	afx_msg void OnProplevel2();
	afx_msg void OnProplevel3();
	afx_msg void OnPropnew();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnProptextcolor();
	afx_msg void OnPropbkcolor();
	afx_msg void OnLeveldefaults();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
