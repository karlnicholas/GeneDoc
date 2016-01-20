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
// ScoreTablep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoreTableProperty dialog

class CScoreTableProperty : public CPropertyPage
{
// Construction
public:
	CScoreTableProperty();	// standard constructor
	~CScoreTableProperty();	// destructor

// Dialog Data
	//{{AFX_DATA(CScoreTableProperty)
	enum { IDD = IDD_CONFSCORETABLES };
	CString	m_CurrentScoreTableString;
	//}}AFX_DATA

	CPtrArray m_ScoreTableArray;		// Hoding a list of ShadePairStruct's
	int m_CurrentScoreTable;
	CListBox *m_listScore;
	void SetScoreTableArray(CPtrArray *nScoreTableArray, int ScoreType);
	CGenedocDoc *pDoc;					// Filled out at init Time.
	int m_ProjectType;

	CPtrArray m_ShadePairArray;		// Hoding a list of ShadePairStruct's
	CListBox *m_listGroup;
	void SetShadePairArray(CPtrArray *nShadePairArray);
	void SetDefaults(int NewScoreTable );			// For when Scoring Table Changes ...
	void ReBuildListBox();
	void ResetData();


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog(); 
	int m_DialogInited;


	// Generated message map functions
	//{{AFX_MSG(CScoreTableProperty)
	afx_msg void OnDblclkScorelist();
	afx_msg void OnScoresetcurrent();
	afx_msg void OnScoredescr();
	afx_msg void OnShadedelete();
	afx_msg void OnShadeedit();
	afx_msg void OnDblclkShadelist();
	afx_msg void OnShadenew();
	afx_msg void OnShadedefault();
	//}}AFX_MSG

	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
