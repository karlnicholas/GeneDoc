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
// genbank.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenbank dialog

class CGenbank : public CDialog
{
// Construction
public:
	CGenbank(CWnd* pParent = NULL);	// standard constructor

	CString LOCUS;
	CString ACCESSION;
	CString NID;
	CString PID;
// Dialog Data
	//{{AFX_DATA(CGenbank)
	enum { IDD = IDD_GENBANK };
	int		m_Locus;
	int		m_Trans;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGenbank)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
