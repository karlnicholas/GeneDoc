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
// seqdialo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqDialog dialog

class CSeqDialog : public CDialog
{

private:
	CPhyloSeq *m_pPGSeq;

	int MoveUpFunc();
	int MoveDownFunc();

// Construction
public:
	CSeqDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeqDialog)
	enum { IDD = IDD_SEQDIALOG };
	CStatic	m_CountSel;
	CStatic	m_strSeqCount;
	CListBox	m_SeqList;
	//}}AFX_DATA

	int m_Modify;
	CGenedocDoc *pDoc;
	void CallSDFromNamedSeq( CObject *p );
// Overrides
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeqDialog)
	afx_msg void OnSeqdelete();
	afx_msg void OnSeqdetails();
	afx_msg void OnSeqimport();
	afx_msg void OnSeqmovedown();
	afx_msg void OnSeqmoveup();
	afx_msg void OnDblclkList1();
	afx_msg void OnMovebott();
	afx_msg void OnMovetop();
	afx_msg void OnCompliment();
	afx_msg void OnReverse();
	afx_msg void OnSeqexport();
	afx_msg void OnDuplicate();
	afx_msg void OnWritescr();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSortname();
	afx_msg void OnSavesort();
	afx_msg void OnLoadsort();
	afx_msg void OnSortdesc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
