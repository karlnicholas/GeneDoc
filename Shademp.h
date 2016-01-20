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
// ShadeModep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShadeModeProperty dialog

class CShadeModeProperty : public CPropertyPage
{
// Construction
public:
	CShadeModeProperty();	// standard constructor

	COLORREF	m_ForeColor100;
	COLORREF	m_ForeColor80;
	COLORREF	m_ForeColor60;
	COLORREF	m_ForeColor0;

	COLORREF	m_BackColor100;
	COLORREF	m_BackColor80;
	COLORREF	m_BackColor60;
	COLORREF	m_BackColor0;

	int m_FontWeight;
	int m_FontSize;

	void ResetData();

// Dialog Data
	//{{AFX_DATA(CShadeModeProperty)
	enum { IDD = IDD_CONFMODESTYLE };
	int		m_ModeConserved;
	double	m_PrimaryLevel;
	double	m_SecondaryLevel;
	double	m_TertiaryLevel;
	int		m_DiffMode;
	int		m_ResidueMode;
	int		m_ShadeLevel;
	BOOL	m_GroupEnabled;
	int		m_ConsSubStyle;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog(); 

	int m_DialogInited;

	// Generated message map functions
	//{{AFX_MSG(CShadeModeProperty)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnChangeback0();
	afx_msg void OnChangeback100();
	afx_msg void OnChangeback60();
	afx_msg void OnChangeback80();
	afx_msg void OnChangefore0();
	afx_msg void OnChangefore100();
	afx_msg void OnChangefore60();
	afx_msg void OnChangefore80();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
