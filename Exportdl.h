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
// exportdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog

class CExportDlg : public CDialog
{
// Construction
public:
	CExportDlg(CWnd* pParent = NULL);	// standard constructor
	CGenedocDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CExportDlg)
	enum { IDD = IDD_EXPORTDLG };
	CListBox	m_listSequence;
	int		m_Device;
	int		m_SelAllSeq;
	int		m_ExportType;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CExportDlg)
	afx_msg void OnExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelallseq();
	afx_msg void OnSellistseq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
