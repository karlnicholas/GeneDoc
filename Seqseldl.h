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
// seqseldl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqSelDlg dialog

class CSeqSelDlg : public CDialog
{
// Construction
public:
	CSeqSelDlg(CWnd* pParent = NULL);	// standard constructor

	CGenedocDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CSeqSelDlg)
	enum { IDD = IDD_SEQSEL };
	CComboBox	m_cbOutTab;
	CListBox	m_listSequence;
	double	m_dLogOddsMPC;
	int		m_iLogOddsOutTab;
	int		m_iLogOddsBack;
	double	m_dLogOddsStA;
	double	m_dLogOddsStC;
	double	m_dLogOddsStG;
	double	m_dLogOddsStT;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSeqSelDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeOuttab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
