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
// displayp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty dialog

class CDisplayProperty : public CPropertyPage
{
// Construction
public:
	CDisplayProperty();	// standard constructor
	CGenedocDoc *pDoc;

	// Dialog Data
	//{{AFX_DATA(CDisplayProperty)
	enum { IDD = IDD_CONFDISPLAY };
	int		m_AutoWidth;
	int		m_FixedWidth;
	int		m_ShowTail;
	int		m_GapInd;
	int		m_ProjectType;
	int		m_ScoringMethod;
	int		m_ConsensusLine;
	int		m_PictHeight;
	int		m_PictAscent;
	int		m_PictWidth;
	CString	m_FontWeight;
	int		m_FontSize;
	int		m_DNAAmbEn;
	int		m_MarkerSpacing;
	BOOL	m_MarkerEnable;
	int		m_MarkerReplace;
	int		m_MarkerStart;
	CString	m_MarkerSymb;
	CString	m_ConservedGap;
	int		m_ResidueUpper;
	int		m_MaxNameLength;
	CString	m_strTail;
	CString	m_strLead;
	int		m_SumColInch;
	int		m_Sum2Wid;
	BOOL	m_SumDefDis;
	int		m_SumColInchDis;
	BOOL	m_SumTextBlack;
	BOOL	m_TransTilde;
	BOOL	m_ShowManShade;
	BOOL	m_ShowComments;
	BOOL	m_MakeBackups;
	BOOL	m_LocAfterSeq;
	BOOL	m_LocAfterName;
	//}}AFX_DATA

// Implementation

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	void ChangeProjectType();

	// Generated message map functions
	//{{AFX_MSG(CDisplayProperty)
	afx_msg void OnTypeprotein();
	afx_msg void OnTyperna();
	afx_msg void OnTypedna();
	afx_msg void OnTypemixednucleic();
	afx_msg void OnChangeSumcolinch();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
