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
// TextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextView view

class CTextView : public VIEWBASE
{
	DECLARE_DYNCREATE(CTextView)
protected:
	CTextView();			// protected constructor used by dynamic creation
	CFont *m_pFont;


// Attributes
public:
	void LoadFile(CString& PathName);
	void SaveFile(CString& PathName);

// Operations
public:

// Implementation
protected:
	virtual ~CTextView();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual	CDocument *GetDocument();
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);


	// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRepsavefile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
