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

class CGVSummary: public CGeneViewBase 
{
private:

    // int m_SaveSetShade;
//	COLORREF m_SaveShadeText, m_SaveShadeBack;
//
	int GetGVEditRows();
//
	DWORD m_YInc;
	DWORD m_GVRYPosition;
	UINT m_GVEditRowCount;
	POSITION m_GVEditRowPos;
	int m_SumWidth;
//

public:
    CGeneSegBase *m_pBase;
    DWORD m_StartPos;
	DWORD m_StartSelect;

//    CGeneString* m_MoveString;
//    DWORD m_MovePoint;
    // CPoint m_DataStartPoint;                // Set by OnDraw Function
    // CRect m_ClipRect;

    CGVSummary();
    DECLARE_DYNCREATE(CGVSummary)
    ~CGVSummary();

    void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    void AssertValid() const;
    void Dump(CDumpContext& dc) const;
#endif
//
    void OnDraw( DrawStruct *DrawStc );
    void CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int SumWidth);
    
    void OnLButtonDown(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnMouseMove(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnLButtonUp(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnLButtonDblClk(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd);
//
	void InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2);
	int GetPartialPageSize(DWORD tPageTop, DWORD tPageBottom, DWORD *tPageAmount);

//
    void AddHeader( CString* nString );
    void AddData( CGeneString* nString );

    void SetDataParams( CGeneSegBase *npBase, unsigned long StartPos ) {
            m_pBase = npBase;
            m_StartPos = StartPos;
    }
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenedocDoc* pDoc );
	void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint );

//
};

