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
// genedvw.h : interface of the CSummaryView class
//
/////////////////////////////////////////////////////////////////////////////

class CSumViewCaret: public CBSumCaret
{
public:
	CSumViewCaret() {}
	void Select( UINT XPosition, DWORD YPosition, CView *pView );
	void LeftDown( UINT XPosition, DWORD YPosition, CView *pView );
	void Move( UINT XPosition, DWORD YPosition, CView *pView );
	void LeftUp( UINT XPosition, DWORD YPosition, CView *pView );
	int Comment( char nChar, UINT XPosition, DWORD YPosition, CView *pView );
};

class CSummaryView : public CView
{
protected: // create from serialization only
	CSummaryView();
	DECLARE_DYNCREATE(CSummaryView)
	
	friend CSumViewCaret;
	CSumViewCaret m_MyCaret;

	UINT m_Descent;		// For Pict Files.


	void ResetGPAdd( CGeneSegBase *pGSBase );
	void BuildRowViews( CGeneSegBase *pGSBase, DWORD StartPos );

	void AddHeadTail( CGVSummary* tGEt, CGVSummary* tGEh, CGPSumView* tRowView );
	void AddHead( CGVSummary* tGEh, CGPSumView* tRowView );
        
// scrolling vars.

	DWORD m_LineHeight;
	UINT m_CharWidth;

	DWORD m_PageScrollHeight;
	UINT m_PageScrollWidth;

	DWORD m_TotalHeight;
	UINT m_TotalWidth;
	
	UINT m_DisplayXPosition;
	DWORD m_DisplayYPosition;
	
	UINT m_SaveDisplayXPosition;
	DWORD m_SaveDisplayYPosition;

	DWORD m_DisplayHeight;
	UINT m_DisplayWidth;
	
	UINT m_ScrollBarRange;

	void SetScrollVariables();
	
	void SetScrollBars();

	void DoDraw(CDC* pDC, int InvFlag1, int InvFlag2 );
// scrolling vars.

	CDC *m_pDC;

	UINT m_EnumCount;
	UINT m_RowVEnum;
	UINT m_LeaderSaveEnum;
//	int m_ExpandedResize;
//	int m_FileOpenFlag;
	void InvalNewEndPoint( DWORD Range1, DWORD Range2);

	// Global vars

	POSITION m_EndPos;
	UINT m_StartSelect;
	UINT m_EndSelect;


	UINT m_LeftView;
	UINT m_TopView;

	DWORD m_PageHeight;
	UINT m_PageWidth;
	DWORD m_TopPage;
	DWORD m_BottomPage;

	int m_PartialPrintFlag;
	int m_PrintOnly;

	CRect m_rectMargins;
	void CalculateMargins(CDC* pDC);
	int m_PrintYOffSet;


	enum { NONE, KEYBRD, MOUSE };
	int m_SelectDevice;
	
	void GetGroupHeader( const CString &GLabel, CGSFiller* pGSFiller );
	int m_CopyFlag;

	int m_InitialUpdateDone;
	
	int m_GeneSelect;
	int m_GeneSelectCol;
	
	enum { 
		DEF_NULL,
	//
		DEF_GENESELECT,
		DEF_GENESELECTCOL,
	};

	void ClearMenu();
	unsigned int GetMenuFunction();
	void LeftDownFunc( UINT nFlags, CPoint point, int DDevice );
	void MoveFunc(UINT nFlags, CPoint point, int DDevice);
	void LeftUpFunc(UINT nFlags, CPoint point, int DDevice);

	void DeSelectAll();
	void ClipFunction( int InvFlag, int ResFlag, int BitFlag );
	void AdjustEndToPoint( CGPSumView *tGP, UINT PointXPosition, DWORD PointYPosition, CView *pWnd );
	
	DWORD m_ColSelStart;
	DWORD m_ColSelEnd;
	int   m_ColSelBegin;
	
	void RebuildShowCaret();

	int m_NamesLength;

// Attributes
public:
	CGenedocDoc* GetDocument();

	CObList m_RowViewList;
	void CleanRowViewList();

	int m_GVETailLength;
	int m_GVELeadLength;
	int m_IndLength;
	int m_SumWidth;

	void ResetGPSize( CDC* pDC, UINT MaxX );

	void InvalidateRectLP(UINT tXPosition, DWORD tYPosition, UINT tXSize, DWORD tYSize );
	void InvalidateGVBLP( CGeneViewBase *pGVB );
	BOOL IsVisible( UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize );

	void ScrollToPosition ( UINT ScrollXPosition, DWORD ScrollYPosition );
	void GetScrollPosition( UINT *ScrollXPosition, DWORD *ScrollYPosition);

// Operations
public:

// Implementation
public:
	virtual ~CSummaryView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate ( CView* pSender, LPARAM lHint, CObject *pHint );
	// Printing support
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	virtual void OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView );
// My Message Handlers

// Generated message map functions
protected:
	//{{AFX_MSG(CSummaryView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnGenecreatewin();
	afx_msg void OnUpdateGenecreatewin(CCmdUI* pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnSelectcol();
	afx_msg void OnUpdateSelectcol(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinv();
	afx_msg void OnUpdateEditCopyinv(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy0();
	afx_msg void OnUpdateEditCopy0(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy8();
	afx_msg void OnUpdateEditCopy8(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinv0();
	afx_msg void OnUpdateEditCopyinv0(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinv8();
	afx_msg void OnUpdateEditCopyinv8(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinvbit();
	afx_msg void OnUpdateEditCopyinvbit(CCmdUI* pCmdUI);
	afx_msg void OnEditCopybit();
	afx_msg void OnUpdateEditCopybit(CCmdUI* pCmdUI);
	afx_msg void OnGenecopypict();
	afx_msg void OnUpdateGenecopypict(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnCopymetaclip();
	afx_msg void OnCopymetafile();
	afx_msg void OnUpdateCopymetaclip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopymetafile(CCmdUI* pCmdUI);
	afx_msg void OnDstatscore();
	afx_msg void OnUpdateDstatscore(CCmdUI* pCmdUI);
	afx_msg void OnDstatscoreall();
	afx_msg void OnUpdateDstatscoreall(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in genedvw.cpp
inline CGenedocDoc* CSummaryView::GetDocument()
   { return (CGenedocDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
