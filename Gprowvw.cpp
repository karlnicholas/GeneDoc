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
// gpRowView.cpp : implementation of the CGPRowView class
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPRowView

IMPLEMENT_DYNCREATE(CGPRowView, CObject)

void 
CGPRowView::AddHead( CGeneViewBase * pGP )
{

	UINT XSize;
	DWORD YSize;
	pGP->GetSize(&XSize, &YSize);

	m_XSize += XSize;
	m_YSize = YSize;

	ViewDataList.AddHead( pGP );
}



void 
CGPRowView::AddTail( CGeneViewBase * pGP )
{

	UINT XSize;
	DWORD YSize;
	pGP->GetSize(&XSize, &YSize);

	m_XSize += XSize;
	m_YSize = YSize;

	ViewDataList.AddTail( pGP );
}


CGPRowView::CGPRowView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGPRowView serialization

void CGPRowView::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGPRowView diagnostics

#ifdef _DEBUG
void CGPRowView::AssertValid() const
{
	CObject::AssertValid();
}

void CGPRowView::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


int 
CGPRowView::GetPartialPageSize(
	DWORD tPageTop, 
	DWORD tPageBottom, 
	DWORD *tPageAmount
) {
	
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit) ) ) {
			return tGVB->GetPartialPageSize( tPageTop, tPageBottom, tPageAmount );
		}
	}
	return 0;
}

void 
CGPRowView::OnDraw( DrawStruct *m_DrawStc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	int FirstDraw = 0;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

		tGVB->OnDraw( m_DrawStc );

	}
}

//
void 
CGPRowView::OnLButtonDown(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet )
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenedocView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit))
		) {
			tGVB->OnLButtonDown(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {

			tGVB->OnLButtonDown(nFlags, XPoint, YPoint, pWnd, pViewRet );

			break;
		}
	}
}

void 
CGPRowView::OnMouseMove(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenedocView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit))
		) {
			tGVB->OnMouseMove(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
//		} else if ( tRect.PtInRect(point) ) {
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->OnMouseMove(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
		}
	}
}

void 
CGPRowView::OnLButtonUp(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenedocView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit))
		) {
			tGVB->OnLButtonUp(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
//		} else if ( tRect.PtInRect(point) ) {
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {

			tGVB->OnLButtonUp(nFlags, XPoint, YPoint, pWnd, pViewRet );

			break;
		}
	}
}

void 
CGPRowView::OnLButtonDblClk(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd)
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
//		if ( tRect.PtInRect(point) ) {
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->OnLButtonDblClk(nFlags, XPoint, YPoint, pWnd );
			break;
		}
	}

}

int 
CGPRowView::ReScoreFunction(UINT XPoint, DWORD YPoint, CView *pWnd)
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
//		if ( tRect.PtInRect(point) ) {
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			return tGVB->ReScoreFunction( XPoint, YPoint, pWnd );
		}
	}
	return 0;
}

int 
CGPRowView::OnComment(char nChar, UINT XPoint, DWORD YPoint, CView *pWnd)
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
//		if ( tRect.PtInRect(point) ) {
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			return tGVB->OnComment(nChar, XPoint, YPoint, pWnd );
		}
	}
	return 0;
}

void 
CGPRowView::CheckMoveRanges( CView *pWnd, CGeneSegment *pCGSeg, UINT Row, 
	int InvScore, DWORD ScoreStart, DWORD ScoreEnd)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit) ) ) {
			if ( ((CGVEdit*)tGVB)->CheckMoveRanges( pWnd, pCGSeg, Row, InvScore, ScoreStart, ScoreEnd ) ) {

				CGenedocDoc* pDoc = ((CGenedocView *)pWnd)->GetDocument();
				ASSERT_VALID(pDoc);

				// Check this.	
				if ( pDoc->m_UserVars.m_ShowTail ) {
					CGVEditTail *tGVET = (CGVEditTail *)ViewDataList.GetNext(tPos);
					tGVET->UpdateGeneRange((CGVEdit*)tGVB, Row, pWnd);
				}
			}
		}
	}
}

void 
CGPRowView::InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit) ) ) {
			((CGVEdit*)tGVB)->InvalNewEndPoint( pWnd, Range1, Range2 );
		}
	}
}



// RowNumber not used here

void 
CGPRowView::CopyText(char *tString, DWORD *dwCount, UINT RowNumber )
{
	CGeneViewBase *tGVB;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	UINT Count = tGVB->ViewDataList.GetCount();

	for ( UINT i=0; i < Count; ++i ) {

		POSITION tPos = ViewDataList.GetHeadPosition();
	
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

			tGVB->CopyText(tString, dwCount, i );
		}
		
		// Add the CR/LF
		tString[*dwCount] = '\r';
		(*dwCount)++;
		tString[*dwCount] = '\n';
		(*dwCount)++;

	}
}

void 
CGPRowView::CountCopyText(DWORD *dwCount )
{       
	CGeneViewBase *tGVB;
	
	DWORD dwTempCount1;
	DWORD dwTempCount2 = 0;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	int Count = tGVB->ViewDataList.GetCount();

	POSITION tPos = ViewDataList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

		tGVB->CountCopyText( &dwTempCount1 );
		
		dwTempCount2 += dwTempCount1;
	}
	
	dwTempCount2 += 2;
	
	dwTempCount2 *= (DWORD)Count;
	
	*dwCount += dwTempCount2;

}


// RowNumber Not Used Here
void 
CGPRowView::WritePict( CPictFile* pPictFile, UINT RowNumber, CGenedocDoc* pDoc )
{
	CGeneViewBase *tGVB;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	UINT Count = tGVB->ViewDataList.GetCount();

	for ( UINT i=0; i < Count; ++i ) {

		POSITION tPos = ViewDataList.GetHeadPosition();
	
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

			tGVB->WritePict( pPictFile, i, pDoc );
		}
		
		// Add the CR/LF
		pPictFile->NewLine();
	}
}

void 
CGPRowView::WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenedocDoc* pDoc )
{
	CGeneViewBase *tGVB;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	UINT Count = tGVB->ViewDataList.GetCount();

	pHTMLFile->StartBlock();

	for ( UINT i=0; i < Count; ++i ) {

		pHTMLFile->StartLine();

		POSITION tPos = ViewDataList.GetHeadPosition();
	
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

			tGVB->WriteHTML( pHTMLFile, i, pDoc );
		}
		
		// Add the CR/LF
		pHTMLFile->EndLine();
	}
	pHTMLFile->EndBlock();
}

void 
CGPRowView::WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenedocDoc* pDoc )
{
	CGeneViewBase *tGVB;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	UINT Count = tGVB->ViewDataList.GetCount();

	for ( UINT i=0; i < Count; ++i ) {

		pRTFFile->StartLine();

		POSITION tPos = ViewDataList.GetHeadPosition();
	
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

			tGVB->WriteRTF( pRTFFile, i, pDoc );
		}
		
		// Add the CR/LF
		pRTFFile->EndLine();
	}
}



void 
CGPRowView::SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->SetStatusBar(nFlags, XPoint, YPoint );
			break;
		}
	}
}

DWORD 
CGPRowView::ColPosFromCaret(UINT XPosition, DWORD YPosition ) 
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit) ) ) {
			return tGVB->ColPosFromCaret(XPosition, YPosition );
		}
	}
	return 0;
}

BOOL 
CGPRowView::CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos )
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->CaretPosFromColSeq( tCount, pCGSeg, XPos, YPos ) ) return 1;
	}

	return 0;
}

