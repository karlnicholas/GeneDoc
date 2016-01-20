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
// phylovw.cpp : implementation of the CPhylogenView class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhylogenView

IMPLEMENT_DYNCREATE(CPhylogenView, CScrollView)

BEGIN_MESSAGE_MAP(CPhylogenView, CScrollView)
	//{{AFX_MSG_MAP(CPhylogenView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_COMMAND(IDM_PHYLODELETE, OnPhylodelete)
	ON_UPDATE_COMMAND_UI(IDM_PHYLODELETE, OnUpdatePhylodelete)
	ON_COMMAND(IDM_PHYLOCLEAR, OnPhyloclear)
	ON_COMMAND(IDM_PHYLOCREATE, OnPhylocreate)
	ON_UPDATE_COMMAND_UI(IDM_PHYLOCREATE, OnUpdatePhylocreate)
	ON_COMMAND(IDM_PHYLOMVDN, OnPhylomvdn)
	ON_UPDATE_COMMAND_UI(IDM_PHYLOMVDN, OnUpdatePhylomvdn)
	ON_COMMAND(IDM_PHYLOMVUP, OnPhylomvup)
	ON_UPDATE_COMMAND_UI(IDM_PHYLOMVUP, OnUpdatePhylomvup)
	ON_COMMAND(IDM_PHYLOCOPY, OnPhylocopy)
	ON_COMMAND(IDM_DISPTREEWEIGHT, OnDisptreeweight)
	ON_UPDATE_COMMAND_UI(IDM_DISPTREEWEIGHT, OnUpdateDisptreeweight)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhylogenView construction/destruction

CPhylogenView::CPhylogenView()
{
	// TODO: add construction code here
}

CPhylogenView::~CPhylogenView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pTreeView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CPhylogenView drawing


void 
CPhylogenView::CallBackFromSeq(CObject *pPSB)
{
	switch ( m_CallBackSwitch ) {
	case CB_DRAWROWS:
		DrawRows(m_DrawpDC, pPSB );
		break;
	case CB_GETMAX:
		GetPhyloGenMax( pPSB );
		break;
	}

}


void 
CPhylogenView::DrawRows(CDC* pDC, CObject *p )
{
	
	ASSERT( p->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) );
	CPhyloSeq *pPS = (CPhyloSeq *)p;

	CPhyloGenBase *pPSB = pPS;
	CString Name = pPS->GetName();
	CString Weight = pPS->m_Weight;
	CPhyloGenBase *pPNPLast = pPSB;
	int tDepth = m_MaxDepth;
	int DrawCmd;  
	int Depth2;

	char NameBuff[20];
	if ( GetDocument()->m_UserVars.m_DispTreeWeight ) {
		_snprintf(NameBuff, 20, ".%05ld: %s", (long)(atof(pPSB->m_Weight)*100000.0), (const char *)Name );
	} else {
		_snprintf(NameBuff, 20, "%d: %s", pPSB->m_Number, (const char *)Name );
	}
	NameBuff[19] = 0;


	while ( pPSB != NULL ) {
		Depth2 = pPSB->m_Depth * 2;
		int DrawY = (m_NumRows * m_CharHeight);

		if ( pPSB->IsKindOf( RUNTIME_CLASS(CPhyloSeq) ) ) {
			if ( pPSB->m_Depth > 1 ) {
				while ( tDepth > pPSB->m_Depth ) {
					if ( tDepth == m_MaxDepth ) {
						DrawCmd = CPhyloGenBase::DLABEL;
					} else if ( tDepth >= pPSB->m_Depth ) {
						DrawCmd = CPhyloGenBase::DEXTEND;
					}
					DoDrawCmd( pDC, DrawCmd, ((tDepth -1) * 2), Name, pPSB->m_Weight, pPSB->m_Number );
					tDepth--;
				}

				pPNPLast = pPSB;
				pPSB = pPSB->m_pPGParent;
				
				continue;
				
			}
		}

		DrawCmd = pPSB->DetermineDraw( pPNPLast );
			
		DoDrawCmd( pDC, DrawCmd, Depth2, Name, pPSB->m_Weight, pPSB->m_Number );
		
		if ( (pPSB->m_DrawType == CPhyloGenBase::DLABEL 
			|| pPSB->m_DrawType == CPhyloGenBase::DNODEEL
			|| pPSB->m_DrawType == CPhyloGenBase::DNODESU )
			&&
			( pPSB->m_Depth == 1 ) 
		) {
			CRect tRect ( 
				m_CharWidth * (Depth2), 
				DrawY, 
				m_CharWidth * (Depth2 + 2) + (m_CharWidth /2), 
				DrawY + m_CharHeight 
			);
			
			if ( pPSB->m_DrawType == CPhyloGenBase::DLABEL ) {
				pPSB->m_ClientRect = 
					(CRect ( 
						CPoint( m_CharWidth * (Depth2), DrawY) , 
						pDC->GetTextExtent( NameBuff, strlen(NameBuff))  + CSize( m_CharWidth, 0)
					)) | tRect
				;
			} else {
				pPSB->m_ClientRect = tRect;
			}
		}

		pPNPLast = pPSB;
		pPSB = pPSB->m_pPGParent;
		
	}

	m_NumRows++;
}

void
CPhylogenView::DrawNodeBox(CDC*pDC, int StartX, int StartY, int Width, int Height, int Number, const CString& Weight ) 
{
	char Buff[10];
	if ( GetDocument()->m_UserVars.m_DispTreeWeight ) {
		_snprintf( Buff, 10, ".%05ld", (long)(atof(Weight) * 100000.0) );
	} else {
		_snprintf( Buff, 10, "%d", Number );
	}
	Buff[9] = 0;
	pDC->TextOut( StartX + 1, StartY, Buff, strlen(Buff) );

	pDC->MoveTo( StartX, StartY );
	pDC->LineTo( StartX, StartY + Height - 1 );
	pDC->LineTo( StartX + Width, StartY + Height - 1 );
	pDC->LineTo( StartX + Width, StartY);
	pDC->LineTo( StartX, StartY);
}

void
CPhylogenView::DoDrawCmd ( CDC*pDC, int DrawCmd, int Depth2, const CString &Name, const CString &Weight, int Number )
{
	int HalfHeight = (m_CharHeight / 2);
	int HalfWidth = (m_CharWidth / 2);
	int DrawY = (m_NumRows * m_CharHeight);
	char NameBuff[20];

	switch ( DrawCmd ) {    
	case CPhyloGenBase::DLABEL:
		if ( GetDocument()->m_UserVars.m_DispTreeWeight ) {
			_snprintf(NameBuff, 20, ".%05ld: %s", (long)(atof(Weight) * 100000.0), (const char *)Name );
		} else {
			_snprintf(NameBuff, 20, "%d: %s", Number, (const char *)Name );
		}
		NameBuff[19] = 0;
		pDC->TextOut ( m_CharWidth * (Depth2 + 1), DrawY, NameBuff, strlen(NameBuff) );
			
		// Draw a line through the middle
		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
		pDC->LineTo( (m_CharWidth * (Depth2 + 1)), DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODESU:
		// Draw Node Indicator

		DrawNodeBox(pDC, m_CharWidth * Depth2 + HalfWidth, DrawY, m_CharWidth + HalfWidth, m_CharHeight, Number, Weight );

		// Draw a line through the middle, second spot
		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODESL:
		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * (Depth2 + 1) + m_CharWidth, DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODET:
		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * (Depth2 + 2), DrawY + HalfHeight );


		break;
	case CPhyloGenBase::DNODEM:
		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + m_CharHeight );

		break;
	case CPhyloGenBase::DNODEEU:
		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY );
		pDC->LineTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );

		pDC->MoveTo( m_CharWidth * (Depth2 + 1) + HalfWidth, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * (Depth2 + 2), DrawY + HalfHeight );

		break;
	case CPhyloGenBase::DNODEEL:

		DrawNodeBox(pDC, m_CharWidth * Depth2 + HalfWidth, DrawY, m_CharWidth + HalfWidth, m_CharHeight, Number, Weight );

		// Draw a line through the middle, second spot
		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );
		break;
	case CPhyloGenBase::DNOTHING:
		break;
	case CPhyloGenBase::DEXTEND:
		// Extension line
		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * (Depth2 + 3), DrawY + HalfHeight );
		break;
	case CPhyloGenBase::DNODER:		// Root Node
		// Extension line
		DrawNodeBox(pDC, m_CharWidth * Depth2 + HalfWidth, DrawY, m_CharWidth + HalfWidth, m_CharHeight, Number, Weight );

		// Draw a line through the middle, second spot
		pDC->MoveTo( m_CharWidth * Depth2, DrawY + HalfHeight );
		pDC->LineTo( m_CharWidth * Depth2 + HalfWidth, DrawY + HalfHeight );
		

		break;
			
	}
}

void 
CPhylogenView::OnDraw(CDC* pDC)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	if ( pDoc->m_pPGBase != NULL ) {
		CSize TextSize;
		if ( pDoc->m_UserVars.m_DispTreeWeight ) {
			TextSize = pDC->GetTextExtent( "0000", 4 );
		} else {
			TextSize = pDC->GetTextExtent( "00", 2 );
		}
		m_CharWidth = TextSize.cx;
		m_CharHeight = TextSize.cy;
		
//		CSize WinSize = GetTotalSize();
		
		m_DrawpDC = pDC;
		m_NumRows = 0;
		m_CallBackSwitch = CB_DRAWROWS;

		pDoc->m_pPGBase->CallFromSeq( this );

		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		POSITION Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_Selected == 1 ) {
				pDC->DrawFocusRect(pPGB->m_ClientRect);
			}
			if ( pPGB->m_FirstSelection == 1 ) {
				pDC->InvertRect(pPGB->m_ClientRect);
			}
		}

	}

}



void 
CPhylogenView::OnInitialUpdate()
{

	CRect tRect;
	GetClientRect( tRect );
	SetScrollSizes(MM_TEXT, 
		CSize( 
			tRect.BottomRight().x, 
			tRect.BottomRight().y
		)
	);


	CScrollView::OnInitialUpdate();

	m_LastKeySelect = 0;
}

void 
CPhylogenView::GetPhyloGenMax( CObject *p )
{
	ASSERT( p->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) );
	CPhyloSeq *pPS = (CPhyloSeq *)p;

	if ( pPS->m_Depth > m_MaxDepth ) {
		m_MaxDepth = pPS->m_Depth;
	}
	CDC *pDC = GetDC();
	char NameBuff[20];
	if ( GetDocument()->m_UserVars.m_DispTreeWeight ) {
		_snprintf(NameBuff, 20, ".%05ld: %s", (long)(atof(pPS->m_Weight) * 100000.0), (const char *)pPS->GetName() );
	} else {
		_snprintf(NameBuff, 20, "%d: %s", pPS->m_Number, (const char *)pPS->GetName() );
	}
	NameBuff[19] = 0;

	int XSize = 
		(pPS->m_Depth * m_CharWidth * 2) 
		+ m_CharWidth 
		+ (pDC->GetTextExtent( NameBuff, strlen(NameBuff) )).cx;

	ReleaseDC( pDC );

	if ( XSize > m_MaxScrolls.cx ) m_MaxScrolls.cx = XSize;

	m_NumRows++;
}

void CPhylogenView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {

		CDC *pDC = GetDC();

		CSize TextSize;
		if ( pDoc->m_UserVars.m_DispTreeWeight ) {
			TextSize = pDC->GetTextExtent( "0000", 4 );
		} else {
			TextSize = pDC->GetTextExtent( "00", 2 );
		}
		m_CharWidth = TextSize.cx;
		m_CharHeight = TextSize.cy;

		ReleaseDC( pDC );

		m_MaxDepth = 0;
		m_NumRows = 0;
		m_MaxScrolls.cx = 0;
		
		m_CallBackSwitch = CB_GETMAX;
	
		pDoc->m_pPGBase->CallFromSeq( this );
		
		m_MaxDepth++;

		
		sizeTotal.cx = m_MaxScrolls.cx;
		sizeTotal.cy = m_NumRows * m_CharHeight;
		
		SetScrollSizes(MM_TEXT, sizeTotal);
		
		m_MaxScrolls.cy = sizeTotal.cy;

		

		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		POSITION Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			pPGB->m_Selected = 0;
			pPGB->m_FirstSelection = 0;
		}
		
		Invalidate();

	}
	
	CView::OnUpdate( pSender, lHint, pHint );
	
}


/////////////////////////////////////////////////////////////////////////////
// CPhylogenView printing

BOOL CPhylogenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhylogenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPhylogenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPhylogenView diagnostics

#ifdef _DEBUG
void CPhylogenView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPhylogenView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGenedocDoc* CPhylogenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	return (CGenedocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPhylogenView message handlers

void CPhylogenView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	// TODO: Add your message handler code here and/or call default CView

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		POSITION Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);

			if ( pPGB->m_Selected == 1 ) {
				if ( !pPGB->m_ClientRect.PtInRect ( point ) ) {
					CDC* pDC = GetDC();
					CRect tRect = pPGB->m_ClientRect;
					dc.LPtoDP( &tRect );
					pDC->DrawFocusRect( tRect );
					pPGB->m_Selected = 0;
					ReleaseDC( pDC );
				}
			}

			if ( pPGB->m_ClientRect.PtInRect ( point ) ) {
				if ( pPGB->m_Selected == 0 ) {
					CDC* pDC = GetDC();
    				pPGB->m_Selected = 1;	
					CRect tRect = pPGB->m_ClientRect;
					dc.LPtoDP( &tRect );
					pDC->DrawFocusRect( tRect );
					ReleaseDC( pDC );
				}
			}
		}
	}

}

void CPhylogenView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	// TODO: Add your message handler code here and/or call default

	SelectFunction();
	
}


void 
CPhylogenView::SelectFunction()
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION Pos;
	CPhyloNode *pPNDoc;
	CPhyloGenBase * pPGB;

	CClientDC dc(this);
	OnPrepareDC(&dc);


	if ( pDoc->m_pPGBase != NULL ) {
		pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				if ( pPGB->m_Selected ) {
					pPGB->m_FirstSelection = 0;
					CRect tRect = pPGB->m_ClientRect;
					dc.LPtoDP( &tRect );
					InvalidateRect( tRect );
					return;
				}
			}
		}

		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_Selected ) {
				pPGB->m_FirstSelection = 1;
				CRect tRect = pPGB->m_ClientRect;
				dc.LPtoDP( &tRect );
				InvalidateRect( tRect );
				break;
			}
		}
	}
}

void CPhylogenView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDblClk(nFlags, point);

	// TODO: Add your message handler code here and/or call default

	CPhyloGenBase * pPGB;

	int Flag = 0;

	POSITION Pos;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				Flag++;
			}
		}
	
		if ( Flag == 1) {
			DeleteFunction();
		} else if ( Flag == 2 ) {
			CreateFunction();
		} else {
			OnUpdate( NULL, 0, NULL );
		}
	}
}

void 
CPhylogenView::DeleteFunction()
{
	POSITION Pos;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection ) {
				if ( pPGB->IsKindOf( RUNTIME_CLASS(CPhyloNode) ) ) {
					CPhyloNode *pPN = (CPhyloNode *)pPGB;
					Pos = pPNDoc->m_PhyloList.Find( pPGB );

					CPhyloGenBase *pPB2 = (CPhyloGenBase*)pPN->m_PhyloList.RemoveHead();
					pPB2->m_pPGParent = pPNDoc;
					pPB2->m_FirstSelection = 0;
					pPNDoc->m_PhyloList.SetAt( Pos, pPB2 );

					pPB2 = (CPhyloGenBase*)pPN->m_PhyloList.RemoveHead();
					pPB2->m_pPGParent = pPNDoc;
					pPB2->m_FirstSelection = 0;
					pPNDoc->m_PhyloList.InsertAfter( Pos, pPB2 );
					
					delete pPN;

					pDoc->SetDepths();
					pDoc->WriteString();

					pDoc->SetModifiedFlag();

				}
			}
		}
		OnUpdate( NULL, 0, NULL );
	}
}

int 
CPhylogenView::ClearSelected(int *Selection)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	*Selection = 0;
	CClientDC dc(this);
	OnPrepareDC(&dc);

	POSITION Pos;
	Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase * pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
		if ( pPGB->m_Selected == 1 ) {
			CDC* pDC = GetDC();
			pPGB->m_Selected = 0;
			CRect tRect = pPGB->m_ClientRect;
			dc.LPtoDP( &tRect );
			pDC->DrawFocusRect( tRect );
			ReleaseDC( pDC );
			return 1;
		}
		(*Selection)++;
	}
	return 0;
}


void 
CPhylogenView::SetSelected(int Selection, int CheckScroll )
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_LastKeySelect = Selection;
	CPhyloGenBase * pPGB;

	POSITION Pos;
	Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
		if ( !Selection-- ) break;
	}
	CDC* pDC = GetDC();

	CRect fRect = pPGB->m_ClientRect;

	if ( CheckScroll ) {
	
		// Check if Scroll Call need to be made.
		CRect tRect ( m_ScrollPos, m_ViewSize );
		CPoint Position1 = fRect.TopLeft();
		Position1.x = 0;
		CPoint Position2 = fRect.BottomRight();
		Position2.x = 0;
	
		if ( (!tRect.PtInRect ( Position1 )) || (!tRect.PtInRect ( Position2 )) ) {
			CPoint tPos = m_ScrollPos;
			int YPos = Position1.y;
			if ( (YPos - (m_ViewSize.cy / 2)) < 0 ) {
				YPos = 0;
			} else {
				YPos = (YPos - (m_ViewSize.cy / 2));
			}
			tPos.y = YPos < (m_MaxScrolls.cy - m_ViewSize.cy) ? YPos: (m_MaxScrolls.cy - m_ViewSize.cy);
			tPos.x = Position1.x < (m_MaxScrolls.cx - m_ViewSize.cx) ? Position1.x: (m_MaxScrolls.cx - m_ViewSize.cx);
			ScrollToPosition ( tPos );
	    	m_ScrollPos = GetScrollPosition();
		}
	}

	CClientDC dc(this);
	OnPrepareDC(&dc);
	pPGB->m_Selected = 1;
	dc.LPtoDP( &fRect );
	pDC->DrawFocusRect( fRect );
	ReleaseDC( pDC );
	
}

void CPhylogenView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	POSITION Pos;
	CPhyloGenBase *pPGB;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	int Selection;
	
	switch ( nChar ) {
	case VK_DOWN:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect;
		Selection += 1;
		if ( Selection >= pDoc->m_pPGBase->m_PhyloList.GetCount() ) Selection = 0;
		SetSelected(Selection, 1);
		break;
	case VK_UP:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect; 
		Selection -= 1;
		if ( Selection < 0 ) Selection = pDoc->m_pPGBase->m_PhyloList.GetCount() - 1;
		SetSelected(Selection, 1);
		break;
	case VK_NEXT:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect;
		Selection += 5;
		if ( Selection >= pDoc->m_pPGBase->m_PhyloList.GetCount() ) Selection = 0;
		SetSelected(Selection, 1);
		break;
	case VK_PRIOR:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect; 
		Selection -= 5;
		if ( Selection < 0 ) Selection = pDoc->m_pPGBase->m_PhyloList.GetCount() - 1;
		SetSelected(Selection, 1);
		break;
	case VK_HOME:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect; 
		Selection = 0;
		SetSelected(Selection, 1);
		break;
	case VK_END:
		if ( !ClearSelected(&Selection) ) Selection = m_LastKeySelect; 
		Selection = pDoc->m_pPGBase->m_PhyloList.GetCount() - 1;
		SetSelected(Selection, 1);
		break;
	case VK_RETURN:
		Selection = 0;
		Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_Selected == 1 ) break;
			Selection++;
		}
		Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_Selected ) {
				pPGB->m_FirstSelection = 1;
				break;
			}
		}
		CreateFunction();
		SetSelected(Selection, 0 );
		break;
	case VK_SHIFT:
	case VK_SPACE:
		SelectFunction();
		break;
	case VK_DELETE:
		Selection = 0;
		Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_Selected == 1 ) break;
			Selection++;
		}
		DeleteFunction();
		SetSelected(Selection, 0 );
		break;
	case VK_ESCAPE:
		Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				pPGB->m_FirstSelection = 0;
				CRect tRect = pPGB->m_ClientRect;
				dc.LPtoDP( &tRect );
				InvalidateRect( tRect );
			}
		}
		break;
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPhylogenView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	m_ViewSize = CSize(cx,cy);
}

void CPhylogenView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int Selection;
	int SelFlag;
	
	SelFlag = ClearSelected(&Selection);
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

	m_ScrollPos = GetScrollPosition();

	if ( SelFlag ) {
		SetSelected(Selection, 0);
	}
}

void CPhylogenView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int Selection;
	int SelFlag;
	
	SelFlag = ClearSelected(&Selection);
	
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

	m_ScrollPos = GetScrollPosition();

	if ( SelFlag ) {
		SetSelected(Selection, 0);
	}
}


int CPhylogenView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pTreeView = this;
	
	return 0;
}

void CPhylogenView::OnPhylodelete()
{
	// TODO: Add your command handler code here
	DeleteFunction();
}

void CPhylogenView::OnUpdatePhylodelete(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	int Flag = 0;

	POSITION Pos;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->IsKindOf(RUNTIME_CLASS(CPhyloNode)) ) {
				if ( pPGB->m_FirstSelection == 1 ) {
					Flag = 1;
					break;
				}
			}
		}
	}
	
	pCmdUI->Enable(Flag);
	
}

void CPhylogenView::OnPhyloclear()
{
	// TODO: Add your command handler code here
	if ( AfxMessageBox( "OK to Delete ALL nodes?", MB_OKCANCEL ) != IDOK ) return;

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		pDoc->ResetTree();
		pDoc->SetModifiedFlag();

	}
	
}

void CPhylogenView::OnPhylocreate()
{
	// TODO: Add your command handler code here
	CreateFunction();
}

void
CPhylogenView::CreateFunction()
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	CPhyloGenBase * pPGBFirst = NULL;
	CPhyloNode * pPN;
	CPhyloGenBase * pPGB;

	int Flag = 0;

	POSITION Pos;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				if ( pPGBFirst == NULL ) pPGBFirst = pPGB;
				Flag++;
			}
		}

		if ( Flag == 2 ) {
			if ( pPNDoc->m_PhyloList.GetCount() < 3 ) {
				Pos = pPNDoc->m_PhyloList.GetHeadPosition();
				while ( Pos != NULL ) {
					pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
					if ( pPGB->m_FirstSelection == 1 ) {
						pPGB->m_FirstSelection = 0;
						CRect tRect = pPGB->m_ClientRect;
						dc.LPtoDP( &tRect );
						InvalidateRect( tRect );
					}
				}
				return;
			}
			Pos = pPNDoc->m_PhyloList.GetHeadPosition();
			while ( Pos != NULL ) {
				pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
				if ( pPGB->m_FirstSelection == 1 && pPGBFirst != pPGB ) {
					pPN = new CPhyloNode();
					pPN->m_pPGParent = pPNDoc;
					pPGBFirst->m_pPGParent = pPN;
					pPGBFirst->m_FirstSelection = 0;
					pPN->m_PhyloList.AddTail( pPGBFirst );
					pPGB->m_pPGParent = pPN;
					pPGB->m_FirstSelection = 0;
					pPN->m_PhyloList.AddTail( pPGB );
					POSITION Pos2 = pPNDoc->m_PhyloList.Find( pPGB );
					pPNDoc->m_PhyloList.RemoveAt( Pos2 );
					Pos2 = pPNDoc->m_PhyloList.Find( pPGBFirst );
					pPNDoc->m_PhyloList.SetAt( Pos2, pPN );
	
					pDoc->SetDepths();
					pDoc->WriteString();
	
					pDoc->SetModifiedFlag();

					OnUpdate( NULL, 0, NULL );
					return;
	
				}
			}
		}
		OnUpdate( NULL, 0, NULL );
	}
}

void CPhylogenView::OnUpdatePhylocreate(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(GetFSCount() == 2);
}

int
CPhylogenView::GetFSCount()
{
	int Flag = 0;

	POSITION Pos;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				Flag++;
			}
		}
	}
	
	return Flag;
}


void CPhylogenView::OnPhylomvdn()
{
	// TODO: Add your command handler code here
	POSITION Pos, PosFirst;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			PosFirst = Pos;
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				if ( Pos != NULL ) {
					pPNDoc->m_PhyloList.RemoveAt (PosFirst);
					pPNDoc->m_PhyloList.InsertAfter ( Pos, pPGB );

					pDoc->SetDepths();
					pDoc->WriteString();

					pDoc->SetModifiedFlag();

					Invalidate();
					return;
				}
			}
		}
	}

}

void CPhylogenView::OnUpdatePhylomvdn(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	
	pCmdUI->Enable(GetFSCount() == 1);
}

void CPhylogenView::OnPhylomvup()
{
	// TODO: Add your command handler code here
	POSITION Pos, PosLast = NULL, PosPrev = NULL;
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if ( pDoc->m_pPGBase != NULL ) {
		CPhyloNode *pPNDoc = pDoc->m_pPGBase;
		Pos = pPNDoc->m_PhyloList.GetHeadPosition();
		while ( Pos != NULL ) {
			PosPrev = PosLast;
			PosLast = Pos;
			CPhyloGenBase * pPGB = (CPhyloGenBase *)pPNDoc->m_PhyloList.GetNext(Pos);
			if ( pPGB->m_FirstSelection == 1 ) {
				if ( PosPrev != NULL ) {
					pPNDoc->m_PhyloList.RemoveAt (PosLast);
					pPNDoc->m_PhyloList.InsertBefore ( PosPrev, pPGB );

					pDoc->SetDepths();
					pDoc->WriteString();

					pDoc->SetModifiedFlag();

					Invalidate();
					return;
				}
			}
		}
	}
	
}

void CPhylogenView::OnUpdatePhylomvup(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(GetFSCount() == 1);
}


void 
CPhylogenView::ClipFunction()
{
	if ( !OpenClipboard() ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->BeginWaitCursor(); // Let em know


	// Size of Bitmap

	CBitmap CopyBmp;

	CDC * pDC = GetDC();

	CDC cDC;

	if ( ! cDC.CreateCompatibleDC( pDC ) ) {
		AfxMessageBox( "Create CompatibleDC fails", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		pDoc->EndWaitCursor(); // Let em know
		return;
	}

	if ( !CopyBmp.CreateCompatibleBitmap( pDC, m_MaxScrolls.cx, m_MaxScrolls.cy ) ) {
		AfxMessageBox( "CreateBitmap fails", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		pDoc->EndWaitCursor(); // Let em know
		return;
	}


	CBitmap* oBmp = cDC.SelectObject ( &CopyBmp );
	
	if ( oBmp == NULL ) {
		AfxMessageBox ( "Cannot Select Bitmap", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		pDoc->EndWaitCursor(); // Let em know
		return;
	}

	// Clear out the new bitmap
	if ( !cDC.BitBlt( 0, 0, m_MaxScrolls.cx, m_MaxScrolls.cy, NULL, 0, 0, WHITENESS ) ) {
		AfxMessageBox ( "Error in BitBlt WHITENESS", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		pDoc->EndWaitCursor(); // Let em know
		return;
	}


	// TODO: add draw code for native data here
	if ( pDoc->m_pPGBase != NULL ) {

		CSize TextSize;
		if ( pDoc->m_UserVars.m_DispTreeWeight ) {
			TextSize = pDC->GetTextExtent( "0000", 4 );
		} else {
			TextSize = pDC->GetTextExtent( "00", 2 );
		}
		m_CharWidth = TextSize.cx;
		m_CharHeight = TextSize.cy;
		
//		CSize WinSize = GetTotalSize();
		
		m_DrawpDC = &cDC;
		m_NumRows = 0;
		m_CallBackSwitch = CB_DRAWROWS;

		pDoc->m_pPGBase->CallFromSeq( this );

	}


	ReleaseDC(pDC);

	cDC.SelectObject(oBmp);

//
	extern HANDLE DibFromBitmap (
    HBITMAP      hbm,
    DWORD            biStyle,
    WORD             biBits,
    HPALETTE     hpal);

	HANDLE hdib = DibFromBitmap ( (HBITMAP)CopyBmp.m_hObject, BI_RGB, 1, NULL );
	
	if ( hdib != NULL ) {
		if ( SetClipboardData(CF_DIB, hdib) == NULL ) {
			AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
		}
	} else {
		AfxMessageBox( "Convert to DIB Failed" );
	}

//
	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}


	pDoc->EndWaitCursor(); // Let em know

	return;

}



void CPhylogenView::OnPhylocopy()
{
	// TODO: Add your command handler code here
	ClipFunction();
}


void CPhylogenView::OnDisptreeweight() 
{
	// TODO: Add your command handler code here
	GetDocument()->m_UserVars.m_DispTreeWeight = !GetDocument()->m_UserVars.m_DispTreeWeight;
	Invalidate();
}

void CPhylogenView::OnUpdateDisptreeweight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( GetDocument()->m_UserVars.m_DispTreeWeight );
	
}
