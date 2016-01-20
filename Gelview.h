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
// CGelView.h : interface of the CGelView class
//
/////////////////////////////////////////////////////////////////////////////


typedef struct {
	CGeneSegment *Sequence;
	CDWordArray arrCutLoc;
	CDWordArray arrGelLoc;
	BOOL bInited;
	int iBandWidth;
} SGel;


class CGelView : public CFormView
{
protected: // create from serialization only
	CGelView();
	DECLARE_DYNCREATE(CGelView)
	void RebuildBox();
	BOOL m_GelView;
	int m_init;

	CPtrList m_listGel;

	SGel *pSGel;	// Working var for NewGel;
	void NewBand( CGeneSegment *Sequence ) { 
		pSGel = new SGel;
		pSGel->Sequence = Sequence;
		pSGel->bInited = 0;
		m_listGel.AddTail(pSGel);
	}
	int m_LineWidth;

	LOGFONT m_logFont;

	int m_PageWidth;
	int m_PageHeight;

	int m_MinY;
	int m_MaxY;

public:
	//{{AFX_DATA(CGelView)
	enum { IDD = IDD_GEL_FORM };
	CListBox	m_listEnzymes;
	CListBox	m_listSequences;
	//}}AFX_DATA

// Attributes
public:
	CGenedocDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGelView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CSize GetGelSize() { return CSize( m_PageWidth, m_PageHeight ); }
	void SetGelSize( int PageWidth, int PageHeight ) {
		m_PageWidth = PageWidth;
		m_PageHeight = PageHeight;
	}
	void SetYScale( int MinY, int MaxY ) { m_MinY = MinY; m_MaxY = MaxY; }
	CFont* SelectDocFont(CDC* pDC, CFont& font, int Escapement);
	void SearchRebaseGel( stcSearch *pSearch, GeneStor *pGeneStor, DWORD OuterCount );
	void DrawGel(CDC* pDC, CRect rcBounds);

// Generated message map functions
protected:
	//{{AFX_MSG(CGelView)
	afx_msg void OnEditCopy();
	afx_msg void OnRungel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGelView.cpp
inline CGenedocDoc* CGelView::GetDocument()
   { return (CGenedocDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
