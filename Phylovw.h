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
// phylovw.h : interface of the CPhylogenView class
//
/////////////////////////////////////////////////////////////////////////////

class CPhylogenView : public CScrollView
{
protected: // create from serialization only
	CPhylogenView();
	DECLARE_DYNCREATE(CPhylogenView)
	
	int m_MaxDepth;
	int m_NumRows;
	CDC *m_DrawpDC;
	int m_CallBackSwitch;
	enum {
		CB_DRAWROWS, 
		CB_GETMAX 
	};

	int m_CharWidth;
	int m_CharHeight;
	void DrawRows(CDC* pDC, CObject *pPSB );
	void GetPhyloGenMax( CObject *p );
	void DoDrawCmd ( CDC*pDC, int DrawCmd, int Depth2, const CString &Name, const CString &Weight, int Number );

	int m_LastKeySelect;
	int ClearSelected(int *Selection);
	void SetSelected(int Selection, int CheckScroll);
	CSize m_ViewSize;
	CPoint m_ScrollPos;
	CSize m_MaxScrolls;
	void SelectFunction();
	void CreateFunction();
	void DeleteFunction();
	int GetFSCount();
	int m_MaxXSize;
	void ClipFunction();
	void DrawNodeBox(CDC*pDC, int StartX, int StartY, int Width, int Height, int Number, const CString& Weight );
	
// Attributes
public:
	CGenedocDoc* GetDocument();
	void CallBackFromSeq(CObject *pPSB);

// Operations
public:

// Implementation
public:
	virtual ~CPhylogenView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint );

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CPhylogenView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPhylodelete();
	afx_msg void OnUpdatePhylodelete(CCmdUI* pCmdUI);
	afx_msg void OnPhyloclear();
	afx_msg void OnPhylocreate();
	afx_msg void OnUpdatePhylocreate(CCmdUI* pCmdUI);
	afx_msg void OnPhylomvdn();
	afx_msg void OnUpdatePhylomvdn(CCmdUI* pCmdUI);
	afx_msg void OnPhylomvup();
	afx_msg void OnUpdatePhylomvup(CCmdUI* pCmdUI);
	afx_msg void OnPhylocopy();
	afx_msg void OnDisptreeweight();
	afx_msg void OnUpdateDisptreeweight(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in phylovw.cpp
inline CGenedocDoc* CPhylogenView::GetDocument()
   { return (CGenedocDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
