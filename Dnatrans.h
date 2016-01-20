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
// dnatrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDNATrans dialog

class CDNATrans : public CDialog
{
// Construction
public:
	CDNATrans(CWnd* pParent = NULL);	// standard constructor
	CGenedocDoc* pDoc;

	CFont m_Font;

// Dialog Data
	//{{AFX_DATA(CDNATrans)
	enum { IDD = IDD_DNATRANS };
	CButton	m_cTransFltStart;
	CButton	m_cShift0;
	CButton	m_cShift1;
	CButton	m_cShift2;
	CButton	m_cTransColumns;
	CButton	m_cTransFixedStart;
	CListBox	m_listCodon;
	CComboBox	m_comboCodon;
	int		m_iReadShift;
	CString	m_AltCodon;
	CString	m_AltProt;
	CString	m_AltStart;
	int		m_TransColumns;
	int		m_TransFixed;
	BOOL	m_TransFltStart;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void UpdateListCodon();


	// Generated message map functions
	//{{AFX_MSG(CDNATrans)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombcodon();
	afx_msg void OnSelchangeListcodon();
	afx_msg void OnTransfixed();
	afx_msg void OnTransfloat();
	afx_msg void OnTranscolumns();
	afx_msg void OnTransfixedstart();
	afx_msg void OnEditchangeCombcodon();
	afx_msg void OnChangeAltstart();
	afx_msg void OnChangeAltprot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
