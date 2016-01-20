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
// prints.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintProperty dialog

class CPrintProperty : public CPropertyPage
{
// Construction
public:
	CPrintProperty();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintProperty)
	enum { IDD = IDD_CONFPRINT };
	double	m_BottomBorder;
	double	m_LeftBorder;
	double	m_RightBorder;
	double	m_TopBorder;
	int		m_Orientation;
	CString	m_PrintFontPoints;
	CString	m_PrintFontName;
	CString	m_PrintFontWeight;
	int		m_PrintPage;
	UINT	m_PrintPageOffset;
	CString	m_PrintString;
	int		m_GeneBlockPos;
	int		m_PrintStringFlag;
	BOOL	m_PrintShading;
	BOOL	m_PrintFileName;
	BOOL	m_PrintDate;
	//}}AFX_DATA

// Implementation
	int m_PrintChanged;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CPrintProperty)
	afx_msg void OnChangeBottomborder();
	afx_msg void OnChangeLeftborder();
	afx_msg void OnChangeRightborder();
	afx_msg void OnChangeTopborder();
	afx_msg void OnOrport();
	afx_msg void OnOrland();
	afx_msg void OnPrintstringflag0();
	afx_msg void OnPrintstringflag1();
	afx_msg void OnPrintstringflag2();
	afx_msg void OnGeneblockpos0();
	afx_msg void OnGeneblockpos1();
	afx_msg void OnGeneblockpos2();
	afx_msg void OnPrintpage0();
	afx_msg void OnPrintpage1();
	afx_msg void OnPrintpage2();
	afx_msg void OnPrintpage3();
	afx_msg void OnPrintpage4();
	afx_msg void OnChangePrintstring();
	afx_msg void OnChangeprintfont();
	afx_msg void OnChangePrintpageoffset();
	afx_msg void OnPrintshade();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
