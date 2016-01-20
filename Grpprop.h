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
// CGroupProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupProp dialog

class CGroupProp : public CPropertyPage
{
// Construction
public:
	CGroupProp();	// standard constructor
	~CGroupProp();	// standard destructor
	
	CGenedocDoc *pDoc;

	CString m_CurrentGroupName;
	
	CString m_InitSimilarities;

// Dialog Data
	//{{AFX_DATA(CGroupProp)
	enum { IDD = IDD_GROUPPROP };
	CComboBox	m_PCRSimilarities;
	CButton	m_DeleteGroup;
	CButton	m_RemoveSeq;
	CButton	m_SeqAdd;
	CButton	m_GroupColor;
	CComboBox	m_GroupCombo;
	CListBox	m_SequenceList;
	BOOL	m_ModifyAll;
	BOOL	m_ColorSeqNames;
	double	m_GroupConsLevel;
	double	m_PCRLevel;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void SetDisplayGroup( const CString& GroupName );

	typedef struct sGroupDisplay {
		int	DisplayGroup;
		COLORREF TextColor;
		COLORREF BkColor;
		CGeneSegment *pCGSeg;
	} GroupDisplay;

	void SetSeqColors();
	int m_SaveCurSel;


	// Generated message map functions
	//{{AFX_MSG(CGroupProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewgroup();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnGrouptextcolor();
	afx_msg void OnGroupbackcolor();
	afx_msg void OnDblclkSeqlist();
	afx_msg void OnSelchangeGroupcombo();
	afx_msg void OnDestroy();
	afx_msg void OnModifyall();
	afx_msg void OnSelchangeSeqlist();
	afx_msg void OnSeqadd();
	afx_msg void OnSelcancelSeqlist();
	afx_msg void OnRemoveseq();
	afx_msg void OnDeletegroup();
	afx_msg void OnColorseqnames();
	afx_msg void OnChangeGroupconslevel();
	afx_msg void OnChangeGrouppcrlevel();
	afx_msg void OnEditchangeGrouppcrsim();
	afx_msg void OnSelchangeGrouppcrsim();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()

};
