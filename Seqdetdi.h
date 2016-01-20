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
// seqdetdi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqDetDialog dialog

class CSeqDetDialog : public CDialog
{
// Construction
public:
	CSeqDetDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeqDetDialog)
	enum { IDD = IDD_SEQDETAILS };
	CString	m_SeqName;
	double	m_SeqWeight;
	CString	m_Instruct;
	DWORD	m_TextStart;
	CString	m_Descr;
	//}}AFX_DATA

	int m_NameChanged;
	int m_DescrChanged;
	int m_WeightChanged;
	int m_StartChanged;

// Overrides
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeqDetDialog)
	afx_msg void OnChangeSeqdetname();
	afx_msg void OnChangeSeqdetweight();
	afx_msg void OnChangeTextstart();
	afx_msg void OnChangeDescr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
