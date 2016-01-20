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
// phylodlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog dialog

class CPhyloGenDialog : public CDialog
{
// Construction
public:
	CPhyloGenDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPhyloGenDialog)
	enum { IDD = IDD_PHYLOGEN };
	CEdit	m_PhyloEdit;
	CString	m_ParseString;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void GetParseFile( const CString& FileName );
	

	// Generated message map functions
	//{{AFX_MSG(CPhyloGenDialog)
	afx_msg void OnPhyloexport();
	afx_msg void OnPhyloimport();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPhylocopy();
	afx_msg void OnPhylopaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
