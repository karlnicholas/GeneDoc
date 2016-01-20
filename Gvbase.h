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

class CGeneViewBase: public CObject
{
protected:
	int Selected;
	// CRect ViewRect;
	UINT EnumVal;
	
	UINT m_XPosition;
	DWORD m_YPosition;
	//
	UINT m_XSize;
	DWORD m_YSize;

public:

	CGeneViewBase*		pGeneViewParent;
	CPtrList			ViewHeaderList;
	CPtrList			ViewDataList;
//
	UINT	m_CharWidth;
	DWORD	m_LineHeight;
//	TEXTMETRIC m_TM;

//
	CGeneViewBase() { Selected = 0; pGeneViewParent = NULL; }
	virtual ~CGeneViewBase() {}
//
//
	//virtual 
	int	IsSelected() { return Selected; }
	// virtual 
	void DeSelect() { Selected = 0; }
	// virtual 
	void Select() { Selected = 1; }
//
	// virtual 
	UINT	GetEnum() { return EnumVal; }
	// virtual 
	void SetEnum(UINT nEnumVal) { EnumVal = nEnumVal; }
//
	// virtual 
	void SetPosition(UINT nx, DWORD ny ) { 
		m_XPosition = nx; 
		m_YPosition = ny; 
	}

	// virtual 
	void GetPosition(UINT *XPosition, DWORD* YPosition) { 
		*XPosition = m_XPosition;
		*YPosition = m_YPosition;
	}

	void GetSize(UINT *XSize, DWORD* YSize) {
		*XSize = m_XSize;
		*YSize = m_YSize;
	}

	void SetSize(UINT nXSize, DWORD nYSize) {
		m_XSize = nXSize;
		m_YSize = nYSize;
	}
	
	BOOL IsPointWithin( UINT XPosition, DWORD YPosition ) {
		if ( (XPosition >= m_XPosition) && (XPosition < (m_XPosition + m_XSize)) )
			if ( (YPosition >= m_YPosition) && (YPosition < (m_YPosition + m_YSize)) )
				return TRUE;
			
		return FALSE;
	}

	BOOL IsVisible( UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize ) {

		if ( (YPosition+YSize)>=m_YPosition && YPosition<=(m_YPosition+m_YSize) ) {
			if ( (XPosition+XSize)>=m_XPosition && XPosition<=(m_XPosition+m_XSize) ) {
				return TRUE;
			}
		}
		return FALSE;
	}

	// const CRect& GetViewRect() { return ViewRect; }

//
	virtual void OnDraw( DrawStruct *m_DrawStc ) = 0;
	virtual void CalcDrawSize(CDC* pDC, UINT* XSize, DWORD* YSize, int Length ) = 0;

//
	virtual void OnLButtonDown(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet) {}
	virtual void OnMouseMove(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet) {}
	virtual void OnLButtonUp(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet) {}
	virtual void OnLButtonDblClk(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd) {}
	
	virtual void AddGroup() {}
	virtual int OnComment(char nChar, UINT XPoint, DWORD YPoint, CView *pWnd) { return 0;}
	virtual int ReScoreFunction( UINT XPoint, DWORD YPoint, CView *pWnd ) {return 0;}
	virtual int GetPartialPageSize(DWORD tPageTop, DWORD tPageBottom, DWORD *tPageAmount) {return 0;}
//
	virtual void CountCopyText(DWORD *dwCount ) { return; }
	virtual void CopyText(char *tString, DWORD *dwCount, UINT RowNumber ) { return; }
	virtual void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenedocDoc* pDoc )  { return; }
	virtual void WriteHTML( CHTMLFile* pPictFile, UINT RowNumber, CGenedocDoc* pDoc ) { return; }
	virtual void WriteRTF( CRTFFile* pPictFile, UINT RowNumber, CGenedocDoc* pDoc ) { return; }
	
	virtual void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint ) {
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = 0L;
		((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[0] = 0;
	}

	virtual DWORD ColPosFromCaret(UINT XPosition, DWORD YPosition ) {return 0;}
	virtual BOOL CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos ) {return 0;}

};

