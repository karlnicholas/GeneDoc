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
// aligndlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlignDlg dialog

class CAlignDlg : public CDialog
{
// Construction
public:
	CAlignDlg(CWnd* pParent = NULL);	// standard constructor
	CGenedocDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CAlignDlg)
	enum { IDD = IDD_SEQALIGN };
	CListBox	m_listSequence;
	int		m_GapExtend;
	int		m_GapLen;
	int		m_GapOpen;
	int		m_AlignMeth;
	CString	m_ScoreTable;
	BOOL	m_DeGap;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CAlignDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
