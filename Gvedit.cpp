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
// GVEdit.cpp : implementation of the CGPEdit class
//

#include "stdafx.h"

#ifdef WIN32

#define EDIT_CLIP_LEFT 2
#define EDIT_CLIP_RIGHT 0

#define EDIT_CHECK_LEFT 2
#define EDIT_CHECK_RIGHT 3

#else 

#define EDIT_CLIP_LEFT 1
#define EDIT_CLIP_RIGHT 0

#define EDIT_CHECK_LEFT 1
#define EDIT_CHECK_RIGHT 2

#endif


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVEdit

IMPLEMENT_DYNCREATE(CGVEdit, CObject)


CGVEdit::CGVEdit(): CGeneViewBase()
{
	// TODO: add construction code here
	m_MoveString = NULL;
}


CGVEdit::~CGVEdit()
{

	while ( !ViewDataList.IsEmpty() ) {
		delete (CGeneString *) ViewDataList.RemoveHead();
	}

	while ( !ViewHeaderList.IsEmpty() ) {
		delete (CString *) ViewHeaderList.RemoveHead();
	}

}


/////////////////////////////////////////////////////////////////////////////
// CGVEdit serialization

void CGVEdit::Serialize(CArchive& ar)
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
// CGVEdit diagnostics

#ifdef _DEBUG
void CGVEdit::AssertValid() const
{
	CObject::AssertValid();
}

void CGVEdit::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CGVEdit::AddHeader( CString* nString )
{
	ViewHeaderList.AddTail( nString );
}

void 
CGVEdit::AddData( CGeneString* nString )
{
	ViewDataList.AddTail(nString);
}

void 
CGVEdit::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int)
{
	// TODO: calculate the total size of this view

	m_YSize = ViewDataList.GetCount() * m_LineHeight;
	m_XSize = ((CGeneString *)ViewDataList.GetHead())->GetLength() * m_CharWidth;

	*YSize = m_YSize;
	*XSize = m_XSize;

	return;
}

int 
CGVEdit::GetGVEditRows()
{
	CGeneString * tGStr;
	switch ( m_GVEditRowCount++ ) {
	case 0:
		return 0;
	case 1:
		m_GVEditRowPos = ViewDataList.GetHeadPosition();
		if ( m_GVEditRowPos != NULL ) {
			tGStr = (CGeneString *)ViewDataList.GetNext(m_GVEditRowPos);
		} else {
			return 1;
		}
		m_GVRYPosition += m_YInc;
		return 0;
	default:
		if ( m_GVEditRowPos != NULL ) {
			tGStr = (CGeneString *)ViewDataList.GetNext(m_GVEditRowPos);
		} else {
			return 1;
		}
		m_GVRYPosition += m_YInc;
		return 0;
	}
	return 0;
}	


int 
CGVEdit::GetPartialPageSize(
	DWORD tPageTop, 
	DWORD tPageBottom, 
	DWORD *tPageAmount)
{

	// Init GetGVEditRows	
	int tRet;
	// int
	m_YInc = m_LineHeight;

	m_GVRYPosition = m_YPosition;
	// int
	m_GVEditRowCount = 0;

	// First we move past the top
	while ( 1 ) {
		if ( tRet = GetGVEditRows() ) {
			break;
		}
		if ( m_GVRYPosition >= tPageTop ) {
			break;
		}
	}

//	*tPageAmount += m_YInc;
	
	// Dont do this if already the end, but should never really happen?
	while ( tRet == 0 ) {
		if ( tRet = GetGVEditRows() ) {
			break;
		}
		if ( m_GVRYPosition > tPageBottom ) {
			break;
		}
		*tPageAmount += m_YInc;
	}

	return tRet;
}

void 
CGVEdit::OnDraw( DrawStruct *DrawStc )
{

	char tOut[2];
	CGenedocDoc *pDoc = ((CGenedocView *)DrawStc->pView)->GetDocument();
	
	CBrush	tBrush;

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	tOut[1] = 0;

	DWORD sScore;
	UINT RowNum = 0;
	UINT PrintTop = 1;
	// Is consensus top?


	// int RowCount = ViewDataList.GetCount();
	if ( DrawStc->pDC->IsPrinting() ) {
		DrawStc->pDC->SetBkMode ( TRANSPARENT );
		if ( pDoc->m_UserVars.m_ConsensusLine != 0 ) {
			// Then use score line
			PrintTop = 2;
		}
	}

	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		if ( (CurrentDisplayLoc + m_LineHeight) > DrawStc->ReDrawTop 
//			&& CurrentDisplayLoc <= DrawStc->ReDrawBottom // Changed because of printing lipid10
			&& CurrentDisplayLoc < DrawStc->ReDrawBottom 
		) {

			int i = 0;	
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			// Outter String Transverse Loop
			for ( UINT tCount = 0; tCount < tMax; tCount++ ) {

				UINT tXLoc1 = tCount*m_CharWidth + m_CharWidth + m_XPosition;
				UINT tXLoc2 = tCount*m_CharWidth + m_XPosition;

				if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {
		
					// i is set to chading level
					COLORREF TextColor, BkColor;
					TextColor = tStr[tCount].TextColor;
					BkColor = tStr[tCount].BackColor;
					CRect tcRect( 
						tXLoc2 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
						tXLoc1 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc + m_LineHeight - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset
					);

					if ( DrawStc->pDC->IsPrinting() ) {

						switch ( BkColor ) {
						case  1:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_BDIAGONAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  2:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_CROSS, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  3:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_DIAGCROSS, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  4:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_FDIAGONAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  5:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_HORIZONTAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case 6:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							tBrush.CreateHatchBrush( HS_VERTICAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						default:
							tBrush.CreateSolidBrush( BkColor );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						}

					}

					DrawStc->pDC->SetBkColor( BkColor );

					DrawStc->pDC->SetTextColor( TextColor );
					tOut[0] = (tStr + tCount)->CharDisplay;

					if ( DrawStc->pDC->IsPrinting() ) {
						if ( !pDoc->m_UserVars.m_PrintShading || RowNum < PrintTop ) {
							DrawStc->pDC->TextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								tOut, 1 
							);
						}
					} else {

						// HS_BDIAGONAL   Downward hatch (left to right) at 45 degrees
						// HS_CROSS   Horizontal and vertical crosshatch
						// HS_DIAGCROSS   Crosshatch at 45 degrees
						// HS_FDIAGONAL   Upward hatch (left to right) at 45 degrees
						// HS_HORIZONTAL   Horizontal hatch
						// HS_VERTICAL   Vertical hatch

						switch ( BkColor ) {
						case  1:
							tBrush.CreateHatchBrush( HS_BDIAGONAL, RGB(0,0,0) );
							break;
						case  2:
							tBrush.CreateHatchBrush( HS_CROSS, RGB(0,0,0) );
							break;
						case  3:
							tBrush.CreateHatchBrush( HS_DIAGCROSS, RGB(0,0,0) );
							break;
						case  4:
							tBrush.CreateHatchBrush( HS_FDIAGONAL, RGB(0,0,0) );
							break;
						case  5:
							tBrush.CreateHatchBrush( HS_HORIZONTAL, RGB(0,0,0) );
							break;
						case 6:
							tBrush.CreateHatchBrush( HS_VERTICAL, RGB(0,0,0) );
							break;
						}

						if ( BkColor >= 1 && BkColor <= 6 ) {

							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor0 );
							DrawStc->pDC->SetBkMode ( TRANSPARENT );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();

							DrawStc->pDC->ExtTextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								NULL, 
								tcRect, 
								tOut, 1 , (int *)(&m_CharWidth) 
							);
						} else {
							DrawStc->pDC->ExtTextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								ETO_OPAQUE, 
								tcRect, 
								tOut, 1 , (int *)(&m_CharWidth) 

							);
						}
					}

					if ( RowNum == 0 ) {
						sScore = (tStr + tCount)->CharScore;
						if ( sScore != 0 ) {
							if ( (sScore%2) == 1 ) {
								DrawStc->pDC->MoveTo( 
									tcRect.TopLeft().x, 
									tcRect.BottomRight().y - 1
								);
								DrawStc->pDC->LineTo( 
									tcRect.TopLeft().x + m_CharWidth, 
									tcRect.BottomRight().y - 1
								);
							} else {
								int half = (tcRect.BottomRight().y - tcRect.TopLeft().y) / 2;
								DrawStc->pDC->MoveTo( 
									tcRect.TopLeft().x, 
									tcRect.TopLeft().y + half - 2
								);
								DrawStc->pDC->LineTo( 
									tcRect.TopLeft().x + m_CharWidth, 
									tcRect.TopLeft().y + half - 2
								);
							}
								
							if ( sScore == 3 || sScore == 4 ) {
								DrawStc->pDC->MoveTo( 
									tcRect.TopLeft().x, 
									tcRect.TopLeft().y
								);
								DrawStc->pDC->LineTo( 
									tcRect.TopLeft().x, 
									tcRect.BottomRight().y - 1
								);
							}
							if ( sScore == 5 || sScore == 6 ) {
								DrawStc->pDC->MoveTo( 
									tcRect.TopLeft().x + m_CharWidth - 1, 
									tcRect.TopLeft().y
								);
								DrawStc->pDC->LineTo( 
									tcRect.TopLeft().x + m_CharWidth - 1, 
									tcRect.BottomRight().y - 1
								);
							}
						}
					}
				}
			}
		}

		CurrentDisplayLoc += m_LineHeight;
		RowNum++;

	}
	
	// Check for Column Inverse
	
	if ( 
		DrawStc->MenuFunc == CGenedocView::DEF_GENESELECTCOL  
		&& DrawStc->ColSelBegin
		&& (!DrawStc->pDC->IsPrinting()) 
	) {
		DWORD StartRange;
		DWORD EndRange;
		if ( DrawStc->ColSelStart < DrawStc->ColSelEnd ) {
			StartRange = DrawStc->ColSelStart;
			EndRange = DrawStc->ColSelEnd;
		} else {
			StartRange = DrawStc->ColSelEnd;
			EndRange = DrawStc->ColSelStart;
		}

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		
		// Test if range hits this string.    
	    if ( ! 
	    	(
		    	(
		    		(StartRange < tGStr->GetStartPos() ) 
		    		&& (EndRange < tGStr->GetStartPos() )
		    	) || (
		    		(StartRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
		    		&& (EndRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
				)
			)
	    ) {
	
			CRect tcRect( 
				m_XPosition - DrawStc->DisplayXPosition, 
				(int)(m_YPosition - DrawStc->DisplayYPosition), 
				m_XPosition + m_XSize - DrawStc->DisplayXPosition, 
				(int)(m_YPosition + m_YSize - DrawStc->DisplayYPosition)
			);
	
			if ( EndRange < (tGStr->GetStartPos() + tGStr->GetLength() ) ) {
				tcRect.BottomRight().x = 
					tcRect.TopLeft().x + (int)((EndRange + 1 - tGStr->GetStartPos()) * m_CharWidth);
			}
	
			if ( StartRange > tGStr->GetStartPos() ) {
				tcRect.TopLeft().x += (int)((StartRange - tGStr->GetStartPos()) * m_CharWidth);
			}
		
			DrawStc->pDC->InvertRect( tcRect );
		}
	}
}

void 
CGVEdit::InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2)
{
	DWORD StartRange;
	DWORD EndRange;

	if ( Range1 < Range2 ) {
		StartRange = Range1;
		EndRange = Range2;
	} else {
		StartRange = Range2;
		EndRange = Range1;
	}
	
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	
	// Test if range hits this string.    
    if ( ! 
    	(
	    	(
	    		(StartRange < tGStr->GetStartPos() ) 
	    		&& (EndRange < tGStr->GetStartPos() )
	    	) || (
	    		(StartRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
	    		&& (EndRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
			)
		)
    ) {


		// CRect tRect = GetViewRect();
		UINT tXPosition, tXSize;
		DWORD tYPosition, tYSize;
		GetPosition( &tXPosition, &tYPosition );
		GetSize( &tXSize, &tYSize );

		if ( ((CGenedocView*)pWnd)->IsVisible( tXPosition, tYPosition, tXSize, tYSize ) ) {

			if ( EndRange < (tGStr->GetStartPos() + tGStr->GetLength() ) ) {
				// tXSize = (UINT)((EndRange + 1 - tGStr->GetStartPos()) * m_CharWidth);
				tXSize = (UINT)((EndRange + 1 - StartRange) * m_CharWidth);
			}

			if ( StartRange > tGStr->GetStartPos() ) {
				tXPosition += (UINT)((StartRange - tGStr->GetStartPos()) * m_CharWidth);
			}
			((CGenedocView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

		}
	}
}

//
void 
CGVEdit::OnLButtonDown(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{
	int move;
//	int OnlyExp = 0;

	DeSelect();		// Clear return flag
	pViewRet->Clip = 0;
	
	if ( !m_pBase->IsKindOf(RUNTIME_CLASS(CGSFiller)) )
		return;

	if ( pViewRet->MenuFunc == 0 ) {
		return;
	}
	
	if ( pViewRet->MenuFunc == CGenedocView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( pViewRet->ColSelBegin == 0 ) {

			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;
			pViewRet->ColSelBegin = 1;

			UINT tXPosition, tXSize;
			DWORD tYPosition, tYSize;
			GetPosition( &tXPosition, &tYPosition );
			GetSize( &tXSize, &tYSize );

			tXPosition += (tCount * m_CharWidth);
			tXSize = m_CharWidth;
	
			((CGenedocView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );
			
			// All Done here
			return;
		
		}

		DWORD StartRange;
		DWORD EndRange;
	
		if ( pViewRet->ColSelStart < pViewRet->ColSelEnd ) {
			StartRange = pViewRet->ColSelStart;
			EndRange = pViewRet->ColSelEnd;
		} else {
			StartRange = pViewRet->ColSelEnd;
			EndRange = pViewRet->ColSelStart;
		}
		
		if ( (gloc >= StartRange) && (gloc <= EndRange) ) {

			((CGenedocView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelStart, pViewRet->ColSelEnd);
			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;

		} else {
			((CGenedocView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
		return;
	}

	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;

	POSITION tPos = ViewDataList.GetHeadPosition();
	
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		
		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();

		if ( pViewRet->DDevice == CGenedocView::KEYBRD ) {
			tXSize += 1;
		}

		// Dont shade comment seg's
		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
			&& 
			( tGStr->GetGeneSegment()->GetStyle() == LINESEQUENCE )
		) {


			// Here we do gene arrange
			if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEDASH
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEINSERTDASH 
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEOTHER 
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEINSERTOTHER 
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEINSERTONE 
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEONE 
			) {

				int Expanded;
				POSITION tPos2;

				switch ( pViewRet->MenuFunc ) {
				case CGenedocView::DEF_GENEDELETEDASH:
				case CGenedocView::DEF_GENEINSERTDASH:

					if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEDASH ) {
				        move = tGStr->GetGeneSegment()->DeleteDash( 
				        	tGStr->GetStartPos() + 
				        	((PointXPosition - sXLoc) / m_CharWidth)  
				        );
				    } else {
			        
				        move = tGStr->GetGeneSegment()->InsertDash( 
				        	tGStr->GetStartPos() + 
				        	((PointXPosition - sXLoc) / m_CharWidth)  
				        );
				    }

			        Expanded = tGStr->GetGeneSegment()->m_Expanded;
			        if ( Expanded ) {
			        	// Here we gotts increase sizes of all strings.
						tPos2 = ViewDataList.GetHeadPosition();
						UINT tc = tGStr->GetEnum();
						while ( tPos2 != NULL ) {
							CGeneString *tGStr2 = (CGeneString *)ViewDataList.GetNext(tPos2);
							if ( !tc-- ) {
								continue;
							}
							tGStr2->GetGeneSegment()->AppendFiller( Expanded );
						}
						pViewRet->Expanded = 1;
					}
			        if ( move != 0 ) {
						((CGenedocView*)pWnd)->CheckMoveRanges(
							tGStr->GetGeneSegment(), tGStr->GetEnum() 
						);
					}

					((CGenedocView*)pWnd)->GetDocument()->ReSizeRows();
					// Done here
			        break;
				case CGenedocView::DEF_GENEINSERTOTHER:
					((CGenedocView*)pWnd)->GetDocument()->BeginWaitCursor();
					Expanded = 0;
					tPos2 = ViewDataList.GetHeadPosition();
					while ( tPos2 != NULL ) {
						CGeneString *t2GStr = (CGeneString *)ViewDataList.GetNext(tPos2);
						if ( t2GStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) continue;
						if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEINSERTOTHER ) {
							if ( t2GStr == tGStr ) continue;
						}
//						if ( ((CGenedocView*)pWnd)->m_SelectSeq ) {
							if ( t2GStr->GetGeneSegment()->GetArrangeFlag() != tGStr->GetGeneSegment()->GetArrangeFlag() ) {
								t2GStr->GetGeneSegment()->m_Expanded = 0;
								continue;
							}
//						}
				        move = t2GStr->GetGeneSegment()->InsertDash( 
				        	t2GStr->GetStartPos() + 
				        	((PointXPosition - sXLoc) / m_CharWidth)  
				        );
					    Expanded |= t2GStr->GetGeneSegment()->m_Expanded;
    			        if ( move != 0 ) {
							((CGenedocView*)pWnd)->CheckMoveRanges(
								t2GStr->GetGeneSegment(), t2GStr->GetEnum() 
							);
						}

					}

			        if ( Expanded ) {
			        	// Here we gotts increase sizes of all strings.
						tPos2 = ViewDataList.GetHeadPosition();
						UINT tc = tGStr->GetEnum();
						while ( tPos2 != NULL ) {
							CGeneString *tGStr2 = (CGeneString *)ViewDataList.GetNext(tPos2);
							if ( !tc-- ) {
								tGStr2->GetGeneSegment()->AppendFiller( 1 );
							} else if ( !tGStr2->GetGeneSegment()->m_Expanded ) {
								tGStr2->GetGeneSegment()->AppendFiller( 1 );
							}
						}
						pViewRet->Expanded = 1;
					}
					((CGenedocView*)pWnd)->GetDocument()->ReSizeRows();
					((CGenedocView*)pWnd)->GetDocument()->EndWaitCursor();
					// Done here
			        break;
				case CGenedocView::DEF_GENEINSERTONE:

					((CGenedocView*)pWnd)->GetDocument()->BeginWaitCursor();
					Expanded = 0;
					tPos2 = ViewDataList.GetHeadPosition();
					while ( tPos2 != NULL ) {
						CGeneString *t2GStr = (CGeneString *)ViewDataList.GetNext(tPos2);
						if ( t2GStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) continue;
						if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEINSERTOTHER ) {
							if ( t2GStr == tGStr ) continue;
						}
//						if ( ((CGenedocView*)pWnd)->m_SelectSeq ) {
							if ( t2GStr->GetGeneSegment()->GetArrangeFlag() != tGStr->GetGeneSegment()->GetArrangeFlag() ) {
								t2GStr->GetGeneSegment()->m_Expanded = 0;
								continue;
							}
//						}
				        move = t2GStr->GetGeneSegment()->InsertDash( 
				        	t2GStr->GetStartPos() + 
				        	((PointXPosition - sXLoc) / m_CharWidth)  
				        );
					    Expanded |= t2GStr->GetGeneSegment()->m_Expanded;
    			        if ( move != 0 ) {
							((CGenedocView*)pWnd)->CheckMoveRanges(
								t2GStr->GetGeneSegment(), t2GStr->GetEnum() 
							);
						}

					}

			        if ( Expanded ) {
			        	// Here we gotts increase sizes of all strings.
						tPos2 = ViewDataList.GetHeadPosition();
						UINT tc = tGStr->GetEnum();
						while ( tPos2 != NULL ) {
							CGeneString *tGStr2 = (CGeneString *)ViewDataList.GetNext(tPos2);
							if ( !tGStr2->GetGeneSegment()->m_Expanded ) {
								tGStr2->GetGeneSegment()->AppendFiller( 1 );
							}
						}
						pViewRet->Expanded = 1;
					}
					((CGenedocView*)pWnd)->GetDocument()->ReSizeRows();
					((CGenedocView*)pWnd)->GetDocument()->EndWaitCursor();
					// Done here

			        break;
				case CGenedocView::DEF_GENEDELETEOTHER:
				case CGenedocView::DEF_GENEDELETEONE:
					// Test for OK to delete

					((CGenedocView*)pWnd)->GetDocument()->BeginWaitCursor();
					tPos2 = ViewDataList.GetHeadPosition();
					while ( tPos2 != NULL ) {
						CGeneString *t2GStr = (CGeneString *)ViewDataList.GetNext(tPos2);
						if ( t2GStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) continue;
						if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEOTHER ) {
							if ( t2GStr == tGStr ) continue;
						}
//						if ( ((CGenedocView*)pWnd)->m_SelectSeq ) {
							if ( t2GStr->GetGeneSegment()->GetArrangeFlag() != tGStr->GetGeneSegment()->GetArrangeFlag() ) {
								t2GStr->GetGeneSegment()->m_Expanded = 0;
								continue;
							}
//						}

						move = t2GStr->GetGeneSegment()->TestDeleteFillerRange( 
			        		t2GStr->GetStartPos() + 
			        		((PointXPosition - sXLoc) / m_CharWidth),
			        		t2GStr->GetStartPos() + 
			        		((PointXPosition - sXLoc) / m_CharWidth)  
				        		
						);
						if ( !move ) {
//			        		AfxMessageBox( "A Residue has been detected in delete range" );
//							Beep( 600, 50 );
			        		return;
						}
					}

					tPos2 = ViewDataList.GetHeadPosition();
					while ( tPos2 != NULL ) {
						CGeneString *t2GStr = (CGeneString *)ViewDataList.GetNext(tPos2);
						if ( t2GStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) continue;
						
						if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEDELETEOTHER ) {
							if ( t2GStr == tGStr ) continue;
						}
//						if ( ((CGenedocView*)pWnd)->m_SelectSeq ) {
							if ( t2GStr->GetGeneSegment()->GetArrangeFlag() != tGStr->GetGeneSegment()->GetArrangeFlag() ) {
								t2GStr->GetGeneSegment()->m_Expanded = 0;
								continue;
							}
//						}

						move = t2GStr->GetGeneSegment()->DeleteDash( 
				        	t2GStr->GetStartPos() + 
				        	((PointXPosition - sXLoc) / m_CharWidth)  
				        );
    			        if ( move != 0 ) {
							((CGenedocView*)pWnd)->CheckMoveRanges(
								t2GStr->GetGeneSegment(), t2GStr->GetEnum() 
							);
						}
					}
					((CGenedocView*)pWnd)->GetDocument()->ReSizeRows();
					((CGenedocView*)pWnd)->GetDocument()->EndWaitCursor();
					break;

				}

			} else if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEARRANGE 
				|| pViewRet->MenuFunc == CGenedocView::DEF_GENEMOVE 
			) {
				// Here we do gene arrange
	
				m_MovePoint = PointXPosition;
				m_MoveString  = tGStr;

				sXLoc += EDIT_CLIP_LEFT;
				tXSize += EDIT_CLIP_RIGHT;

				// Store before converting to DP for caret stuff
				pViewRet->Clip = 1;

				pViewRet->ClipXPosition = sXLoc;
				pViewRet->ClipYPosition = sYLoc;
				pViewRet->ClipXSize = tXSize;
				pViewRet->ClipYSize = tYSize;

				m_ClipXPosition = sXLoc;
				m_ClipYPosition = sYLoc;
				m_ClipXSize = tXSize;
				m_ClipYSize = tYSize;

	
				// Fill out selection stuff
				m_StartSelect = ((PointXPosition - m_XPosition)) / m_CharWidth;
	
				break;
			} else if ( pViewRet->MenuFunc == CGenedocView::DEF_SHADE ) { 
				// here we do Shading.
				// Fill out selection stuff
				
				
				CGenedocView *pView = ((CGenedocView*)pWnd);
				COLORREF ShadeTextColor, ShadeBackColor;
				ShadeTextColor = pView->m_ShadeTextColor;
				ShadeBackColor = pView->m_ShadeBackColor;

				CGenedocDoc *pDoc = pView->GetDocument();
				pViewRet->Expanded = 0;

				if ( pDoc->GetNumColors( &pDoc->m_UserVars.m_Vars ) != pView->m_SaveShadeLevels ) {
					pView->DoManualShade();
					pViewRet->Expanded = 1;
					break;
				}

				UINT tCount = (PointXPosition - sXLoc) / m_CharWidth;
				COLORREF TextColor, BackColor;
				tGStr->GetShade( tCount, &TextColor, &BackColor );
				if ( TextColor == ShadeTextColor && BackColor == ShadeBackColor ) { 
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &m_SaveShadeText, &m_SaveShadeBack );
					AddRemShade = 0;
				} else {
					m_SaveShadeText = ShadeTextColor;
					m_SaveShadeBack = ShadeBackColor;
					AddRemShade = 1;
				}
				tGStr->SetShade( tCount, m_SaveShadeText, m_SaveShadeBack );
				tGStr->GetGeneSegment()->SetShade ( 
					(DWORD)(tGStr->GetStartPos() + tCount), 
					m_SaveShadeText, m_SaveShadeBack, AddRemShade 
				);

				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tCount * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenedocView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );
				
				break;

			} 
				
		}

//		sLoc.y += m_LineHeight;
		sYLoc += m_LineHeight;
	}		
}

void 
CGVEdit::OnMouseMove(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{
	if ( pViewRet->MenuFunc == CGenedocView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( gloc != pViewRet->ColSelEnd ) {
			((CGenedocView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	} else if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEARRANGE 
		|| pViewRet->MenuFunc == CGenedocView::DEF_GENEMOVE 
	) {
		CheckMove( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	} else if ( pViewRet->MenuFunc == CGenedocView::DEF_SHADE ) {
		CheckShade( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	}
}

void
CGVEdit::CheckShade( UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	
	POSITION tPos = ViewDataList.GetHeadPosition();
		
	while ( tPos != NULL ) {
	
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
	
		DWORD tYSize = m_LineHeight;
		int tXSize = m_CharWidth * tGStr->GetLength();

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {
			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {
				break;
			}

			UINT tLoc = (PointXPosition - m_XPosition) / m_CharWidth;

			COLORREF TextColor, BackColor;
			tGStr->GetShade(tLoc, &TextColor, &BackColor);

			if ( TextColor != m_SaveShadeText || BackColor != m_SaveShadeBack ) {
				tGStr->SetShade( tLoc, m_SaveShadeText, m_SaveShadeBack );
				tGStr->GetGeneSegment()->SetShade ( 
					(DWORD)(tGStr->GetStartPos() + tLoc), 
					m_SaveShadeText, m_SaveShadeBack, AddRemShade 
				);
					
				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tLoc * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenedocView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

			}
				
			break;
		}
		sYLoc += m_LineHeight;
	}
}

void 
CGVEdit::CheckMove( UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{

	DWORD move;
	int mx;
	if ( m_MoveString == NULL ) return;
	
	
	mx = (((int)PointXPosition - (int)m_MovePoint) / (int)m_CharWidth);

	if ( 
		(PointXPosition == (m_ClipXPosition - EDIT_CHECK_LEFT)) 
		&& (PointXPosition <= m_MovePoint) 
		&& ( m_MovePoint >= (m_ClipXPosition - EDIT_CHECK_LEFT)) 
		&& ( pViewRet->DDevice != CGenedocView::KEYBRD)
	) {
		mx -= 1;
	}

	if ( 
		(PointXPosition == (m_ClipXPosition + m_ClipXSize - EDIT_CHECK_RIGHT )) 
		&& (PointXPosition >= m_MovePoint) 
		&& (m_MovePoint <= (m_ClipXPosition + m_ClipXSize - EDIT_CHECK_RIGHT )) 
		&& ( pViewRet->DDevice != CGenedocView::KEYBRD)
	) {
		mx += 1;
	}

	if ( (mx < 0) || (mx > 0) ) {
        
        DWORD KbdOffSet = 0;
        if ( mx < 0 && pViewRet->DDevice == CGenedocView::KEYBRD ) {
        	KbdOffSet = (DWORD)-1L;
        }

		if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEARRANGE ) {
      
			move = m_MoveString->GetGeneSegment()->MoveText( 
        		(DWORD)m_MoveString->GetStartPos() + m_StartSelect + KbdOffSet, 
        		mx 
			);
		} else {
			move = m_MoveString->GetGeneSegment()->SlideText( 
        		(DWORD)m_MoveString->GetStartPos() + m_StartSelect + KbdOffSet, 
        		mx 
			);
		}
        
        if ( m_MoveString->GetGeneSegment()->m_Expanded ) {
        	// Here we gotts increase sizes of all strings.
			POSITION tPos = ViewDataList.GetHeadPosition();
			CGeneString *tGStr;
			UINT tc = m_MoveString->GetEnum();
			while ( tPos != NULL ) {
				tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
				if ( !tc-- ) {
					continue;
				}
				tGStr->GetGeneSegment()->AppendFiller( m_MoveString->GetGeneSegment()->m_Expanded );
			}
			pViewRet->Expanded = 1;
		}
		((CGenedocView*)pWnd)->GetDocument()->ReSizeRows();
		

        if ( move != 0 ) {
            
	        m_StartSelect += move;
			m_MovePoint= m_MovePoint + ( move * m_CharWidth);
			
			((CGenedocView*)pWnd)->CheckMoveRanges(
				m_MoveString->GetGeneSegment(), 
				m_MoveString->GetEnum()
			);
		}
	}
}

int
CGVEdit::CheckMoveRanges(
	CView *pWnd, 
	CGeneSegment *pCGSeg, 
	UINT Row, 
	int InvalScore, 
	DWORD ScoreStart, 
	DWORD ScoreEnd 
)
{
	int rc = 0;
	CGeneSegment *tCGSeg = pCGSeg;
	CGenedocView *pView = (CGenedocView *)pWnd;
	CGenedocDoc *pDoc = pView->GetDocument();
	ASSERT_VALID( pDoc );

	// CPoint	sLoc = ViewRect.TopLeft();
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	CGeneString *tGStr;

	CGeneString *RowGStr;
	// CPoint RowLoc;
	UINT XRowLoc;
	DWORD YRowLoc;

	CGeneString *ScoreGStr;
	// CPoint ScoreLoc;
	UINT XScoreLoc;
	DWORD YScoreLoc;

	CGeneString *ConsGStr = NULL;
	// CPoint ConsLoc;
	UINT XConsLoc;
	DWORD YConsLoc;

	POSITION tPos = ViewDataList.GetHeadPosition();
	UINT RowCount = ViewDataList.GetCount();

	for ( UINT i =0; tPos != NULL; ++i ) {
		tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( i == 0 ) {
			ScoreGStr = tGStr;
			// ScoreLoc = sLoc;
			XScoreLoc = sXLoc;
			YScoreLoc = sYLoc;
		}
		if ( pDoc->m_UserVars.m_ConsensusLine == 0 ) {
			if ( i == 1 ) {
				ConsGStr = tGStr;
				// ConsLoc = sLoc;
				XConsLoc = sXLoc;
				YConsLoc = sYLoc;
			}
		}
		if ( i == Row ) {
			RowGStr = tGStr;
			// RowLoc = sLoc;
			XRowLoc = sXLoc;
			YRowLoc = sYLoc;
		}
		sYLoc += m_LineHeight;
	}

	if ( ConsGStr == NULL ) {
		ConsGStr = tGStr;
		// ConsLoc = sLoc;
		XConsLoc = sXLoc;
		YConsLoc = sYLoc;
		// ConsLoc.y -= m_LineHeight;
		YConsLoc -= m_LineHeight;
	}

	DWORD tYSize;
	UINT tXSize;

	DWORD tStartRange, tEndRange;
	HANDLE hSeg;

	if ( InvalScore ) {
		// Test if range hits this string.    
		if ( ! 
    		(
	    		(
	    			(ScoreStart < ScoreGStr->GetStartPos() ) 
	    			&& (ScoreEnd < ScoreGStr->GetStartPos() )
	    		) || (
	    			(ScoreStart > (ScoreGStr->GetStartPos() + ScoreGStr->GetLength() ))
	    			&& (ScoreEnd > (ScoreGStr->GetStartPos() + ScoreGStr->GetLength() ))
				)
			)
		) {

			// Needs ScoreGStr, tEndRange, tStartRange, ScoreLoc, dc, pWnd
			hSeg = ScoreGStr->GetGeneSegment()->MidText( ScoreGStr->GetStartPos(), ScoreGStr->GetLength() );
			GeneStor *tStor = (GeneStor *)GlobalLock(hSeg);
			if ( tStor == NULL ) {
				AfxMessageBox("CheckMoveRanges:GlobalLock:Fail:1");
				return 0;
			}
			ScoreGStr->SetNewString( tStor, ScoreGStr->GetLength() );
			GlobalUnlock(hSeg);
			GlobalFree(hSeg);


			tStartRange = ScoreGStr->GetStartPos();
			tEndRange = tStartRange + ScoreGStr->GetLength() - 1;

			if ( ScoreEnd < tEndRange ) {
				tEndRange = ScoreEnd;
			}

			if ( ScoreStart > tStartRange ) {
				tStartRange = ScoreStart;
			}
			
			tYSize = m_LineHeight;
			tXSize = m_CharWidth * (UINT)(tEndRange - tStartRange + 1);
			XScoreLoc += m_CharWidth * (UINT)(tStartRange - ScoreGStr->GetStartPos());

			((CGenedocView*)pWnd)->InvalidateRectLP( XScoreLoc, YScoreLoc, tXSize, tYSize );


		}
	}



	// Test if range hits this string.    
    if ( ! 
    	(
	    	(
	    		(tCGSeg->m_StartRange < RowGStr->GetStartPos() ) 
	    		&& (tCGSeg->m_EndRange < RowGStr->GetStartPos() )
	    	) || (
	    		(tCGSeg->m_StartRange > (RowGStr->GetStartPos() + RowGStr->GetLength() ))
	    		&& (tCGSeg->m_EndRange > (RowGStr->GetStartPos() + RowGStr->GetLength() ))
			)
		)
    ) {



		if ( Row != 0 ) {
			
			int flag = 1;
			if ( pDoc->m_UserVars.m_ConsensusLine == 0 ) {
				// Upper
				if ( Row == (RowCount - 1) ) {
					flag = 0;
				}
			} else if ( Row == 1 ) {
				flag = 0;
			}

			if ( flag ) {
				tStartRange = ConsGStr->GetStartPos();
				tEndRange = tStartRange + ConsGStr->GetLength() - 1;

				if ( tCGSeg->m_EndRange < tEndRange ) {
					tEndRange = tCGSeg->m_EndRange;
				}

				if ( tCGSeg->m_StartRange > tStartRange ) {
					tStartRange = tCGSeg->m_StartRange;
				}
                
				// Hmmmmm .. last shade level only a nicety here ..
				if ( pDoc->m_UserVars.m_ConsensusLine < 2 ) {

					if ( ConsGStr->GetGeneSegment()->InvalConsensus( &tStartRange, &tEndRange ) ) {
						hSeg = ConsGStr->GetGeneSegment()->MidText( ConsGStr->GetStartPos(), ConsGStr->GetLength() );
						GeneStor *tStor = (GeneStor *)GlobalLock(hSeg);
						if ( tStor == NULL ) {
							AfxMessageBox("CheckMoveRanges:GlobalLock:Fail:1");
							return 0;
						}
						ConsGStr->SetNewString( tStor, ConsGStr->GetLength() );
						GlobalUnlock(hSeg);
						GlobalFree(hSeg);
	
						tYSize = m_LineHeight;
						tXSize = m_CharWidth * (UINT)(tEndRange - tStartRange + 1);
						XConsLoc += m_CharWidth * (UINT)(tStartRange - ConsGStr->GetStartPos());

						((CGenedocView*)pWnd)->InvalidateRectLP( XConsLoc, YConsLoc, tXSize, tYSize );

					}
				}
			}
		}



		hSeg = tCGSeg->MidText( RowGStr->GetStartPos(), RowGStr->GetLength() );
		GeneStor *tStor = (GeneStor *)GlobalLock(hSeg);
		if ( tStor == NULL ) {
			AfxMessageBox("CheckMoveRanges:GlobalLock:Fail:1");
			return 0;
		}

		RowGStr->SetNewString( tStor, RowGStr->GetLength() );
		GlobalUnlock(hSeg);
		GlobalFree(hSeg);

		tYSize = m_LineHeight;
		tXSize = m_CharWidth * RowGStr->GetLength();
//		tRect = CRect( RowLoc, tSize );
		
		rc = 1;

		if ( ((CGenedocView*)pWnd)->IsVisible( XRowLoc, YRowLoc, tXSize, tYSize ) ) {

			if ( tCGSeg->m_EndRange < (tGStr->GetStartPos() + tGStr->GetLength() ) ) {
				tXSize = (UINT)((tCGSeg->m_EndRange + 1 - RowGStr->GetStartPos()) * m_CharWidth);
			}

			if ( tCGSeg->m_StartRange > tGStr->GetStartPos() ) {
				XRowLoc += (UINT)((tCGSeg->m_StartRange - RowGStr->GetStartPos()) * m_CharWidth);
			}
			// the plus and minus one corrects for an oversided chars in courier new bold font
			((CGenedocView*)pWnd)->InvalidateRectLP( XRowLoc - 1, YRowLoc, tXSize + 1, tYSize );

		}

	}
	return rc;
}

void 
CGVEdit::OnLButtonUp(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{
	if ( pViewRet->MenuFunc == CGenedocView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( gloc != pViewRet->ColSelEnd ) {
			((CGenedocView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	} else if ( pViewRet->MenuFunc == CGenedocView::DEF_GENEARRANGE 
		|| pViewRet->MenuFunc == CGenedocView::DEF_GENEMOVE 
	) {
		CheckMove( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	} else if ( pViewRet->MenuFunc == CGenedocView::DEF_SHADE ) {
		CheckShade( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	}
	m_MoveString = NULL;
}


void 
CGVEdit::OnLButtonDblClk(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{
}

int
CGVEdit::ReScoreFunction( UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{

	int rc = 0;
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();

	UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
	DWORD StartRange, EndRange;

	rc = ((CGenedocView*)pWnd)->GetDocument()->FindScore ( 
		(DWORD)(tGStr->GetStartPos() + tCount),
		&StartRange, &EndRange 
	);

	if ( rc ) {
		((CGenedocView*)pWnd)->GetDocument()->Score ( &StartRange, &EndRange );

		if ( ViewDataList.GetCount() ) {
			CGeneSegment * tCGSeg = tGStr->GetGeneSegment();
			tCGSeg->m_StartRange = StartRange;
			tCGSeg->m_EndRange = EndRange;
		
			((CGenedocView*)pWnd)->CheckMoveRanges( tCGSeg, 0 );
		}
	}
			
	return rc;
}

int 
CGVEdit::OnComment(char nChar, UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	

	ASSERT ( pWnd->IsKindOf(RUNTIME_CLASS(CGenedocView)));
	CGenedocView* pView = (CGenedocView* )pWnd;
	
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();
		// CRect tRect ( sLoc, tSize );

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {

			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {

				// Fill out selection stuff
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;

				tGStr->SetComment( tCount, nChar );
				tGStr->GetGeneSegment()->SetComment ( 
					(DWORD)(tGStr->GetStartPos() + tCount), 
					nChar
				);

				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tCount * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenedocView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

				return 1;

			} else if ( pView->GetMenuFunction() == CGenedocView::DEF_GENEEDITMODE ) {
				// Change the Residue Character!!
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
                
				nChar = toupper(nChar);
				// Dont allow spaces in the data area ..
				if ( nChar == ' ' ) return 0;

				tGStr->SetResidue( tCount, nChar );
				tGStr->GetGeneSegment()->SetResidue ( 
					(DWORD)(tGStr->GetStartPos() + tCount), 
					nChar
				);

				tGStr->GetGeneSegment()->m_StartRange = tGStr->GetStartPos() + tCount;
				tGStr->GetGeneSegment()->m_EndRange = tGStr->GetStartPos() + tCount;
				
				pView->CheckMoveRanges( tGStr->GetGeneSegment(), tGStr->GetEnum() );
				
				pView->GetDocument()->SetModifiedFlag();

				return 1;
			}

			return 0;
		}
		sYLoc += m_LineHeight;
	}
	
	return 0;
}


void 
CGVEdit::CopyText(char * tString, DWORD *dwCount, UINT RowNumber )
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				tString[*dwCount] = tStr->CharDisplay;
				(*dwCount)++;
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}
 

void 
CGVEdit::CountCopyText( DWORD *dwCount )
{
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	*dwCount = tGStr->GetLength();
}


void 
CGVEdit::WritePict( CPictFile* pPictFile, UINT RowNumber, CGenedocDoc *pDoc )
{
	UINT sRowNum = RowNumber;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				COLORREF TextC, BkC;
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextC, &BkC );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					TextC = tStr->TextColor;
					BkC = tStr->BackColor;
				}

				pPictFile->CharOut( tStr->CharDisplay, TextC, BkC );

				// Lets do something for scoring.
				DWORD sScore = tStr->CharScore;
				if ( sScore != 0 && sRowNum == 0 ) {
					if ( (sScore%2) == 1 ) {
						pPictFile->LineBottom();
					} else {
						pPictFile->LineMiddle();
					}
					if ( sScore == 3 || sScore == 4 ) {
						pPictFile->LineLeft();
					}
					if ( sScore == 5 || sScore == 6 ) {
						pPictFile->LineRight();
					}
				}

				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}
 
void 
CGVEdit::WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenedocDoc *pDoc )
{
	UINT sRowNum = RowNumber;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				COLORREF TextC, BkC;
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextC, &BkC );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					TextC = tStr->TextColor;
					BkC = tStr->BackColor;
				}

				pHTMLFile->CharOut( tStr->CharDisplay, TextC, BkC );

				// Lets do something for scoring.
/*
				DWORD sScore = tStr->CharScore;
				if ( sScore != 0 && sRowNum == 0 ) {
					if ( (sScore%2) == 1 ) {
						pHTMLFile->LineBottom();
					} else {
						pHTMLFile->LineMiddle();
					}
					if ( sScore == 3 || sScore == 4 ) {
						pHTMLFile->LineLeft();
					}
					if ( sScore == 5 || sScore == 6 ) {
						pHTMLFile->LineRight();
					}
				}
*/
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}

 
void 
CGVEdit::WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenedocDoc *pDoc )
{
	UINT sRowNum = RowNumber;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				COLORREF TextC, BkC;
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextC, &BkC );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					TextC = tStr->TextColor;
					BkC = tStr->BackColor;
				}

				pRTFFile->CharOut( tStr->CharDisplay, TextC, BkC );

				// Lets do something for scoring.
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}

void  
CGVEdit::SetStatusBar(UINT nFlags, UINT PointXPosition, DWORD PointYPosition ) 
{
	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();
		// CRect tRect ( sLoc, tSize );

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {

			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {

				// Fill out selection stuff
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;

                ((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = (DWORD)(tGStr->GetStartPos() + tCount + 1);
				strncpy( 
					((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName, 
					"Column", 
					10 );
				((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[10] = 0;

			} else  {
				// Find Which residue ...
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
				const GeneStor * pg = *tGStr;
				pg += tCount;
                
                ((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = (DWORD)(pg->GeneSeqNumber);
				strncpy( 
					((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName, 
					(const char *)tGStr->GetGeneSegment()->GetTitle(), 
					10 );
				((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[10] = 0;

			}

			return;
		}
		sYLoc += m_LineHeight;
	}
}

DWORD 
CGVEdit::ColPosFromCaret(UINT XPosition, DWORD YPosition ) 
{
	// CPoint	sLoc = m_DataStartPoint;
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	if ( XPosition < m_XPosition ) {
		return tGStr->GetStartPos();
	} else if ( XPosition > (m_XPosition + (m_CharWidth * tGStr->GetLength())) ) {
		return tGStr->GetStartPos() + tGStr->GetLength();
	}

	UINT tCount = (XPosition - m_XPosition) / m_CharWidth;
    return (DWORD)(tGStr->GetStartPos() + tCount);
}

BOOL 
CGVEdit::CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos )
{
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();

	UINT sXLoc = m_XPosition + ( tGStr->GetStartPos() * m_CharWidth);

	UINT tXSize = m_CharWidth * tGStr->GetLength();
	// CRect tRect ( sLoc, tSize );
	tCount = (tCount * m_CharWidth) + m_XPosition;

	if ( tCount >= sXLoc && tCount < (sXLoc + tXSize) ) {
		*XPos = tCount - sXLoc + m_XPosition;

		UINT sXLoc = m_XPosition;
		DWORD sYLoc = m_YPosition;

		POSITION tPos = ViewDataList.GetHeadPosition();
		while ( tPos != NULL ) {

			CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

			// SIZE tSize;
			DWORD tYSize = m_LineHeight;
			UINT tXSize = m_CharWidth * tGStr->GetLength();
			// CRect tRect ( sLoc, tSize );

			if ( tGStr->GetGeneSegment() == pCGSeg ) {
				*YPos = sYLoc;
				return 1;
			}
			sYLoc += m_LineHeight;
		}
		return 1;
	}
	return 0;
}

