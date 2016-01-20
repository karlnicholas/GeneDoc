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
// titlingf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitlingFDialog dialog

class CTitlingFDialog : public CDialog
{
// Construction
public:
	CTitlingFDialog(CWnd* pParent = NULL);	// standard constructor
	
	CString m_CommentText;
	int m_CTChanged;
	int m_ICChanged;		// Initial Creation

// Dialog Data
	//{{AFX_DATA(CTitlingFDialog)
	enum { IDD = IDD_TITLINGF };
	CEdit	m_CommentEdit;
	CString	m_ExtendGap;
	CString	m_OpenGap;
	CString	m_Program;
	CString	m_ScoreMatrix;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTitlingFDialog)
	afx_msg void OnChangeTitleedit();
	afx_msg void OnChangeTitleextendgap();
	afx_msg void OnChangeTitleopengap();
	afx_msg void OnChangeTitleprogram();
	afx_msg void OnChangeTitlescore();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
