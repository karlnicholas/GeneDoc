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
// GraphSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup dialog

class CGraphSetup : public CDialog
{
// Construction
public:
	CGraphSetup(CWnd* pParent = NULL);   // standard constructor

	LOGFONT m_logFont;

// Dialog Data
	//{{AFX_DATA(CGraphSetup)
	enum { IDD = IDD_GRAPHSETUP };
	float	m_PageHeight;
	float	m_PageWidth;
	int		m_Set1Count;
	int		m_Set2Count;
	int		m_TSide;
	CString	m_ChartTitle;
	int		m_xChtTitPct;
	int		m_yDStatPct;
	int		m_xKSprPct;
	int		m_yKSprPct;
	int		m_LineWidth;
	double	m_RoundingFactor;
	int		m_xXAxTPct;
	int		m_xBorderPct;
	int		m_yBorderPct;
	int		m_yYAxTPct;
	int		m_xDStatPct;
	CString	m_XAxisTitle;
	CString	m_YAxisTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphSetup)
	afx_msg void OnChgfont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
