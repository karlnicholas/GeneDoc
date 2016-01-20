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


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVSummary

IMPLEMENT_DYNCREATE(CGVSummary, CObject)


CGVSummary::CGVSummary(): CGeneViewBase()
{
	// TODO: add construction code here
}


CGVSummary::~CGVSummary()
{

	while ( !ViewDataList.IsEmpty() ) {
		delete (CGeneString *) ViewDataList.RemoveHead();
	}

	while ( !ViewHeaderList.IsEmpty() ) {
		delete (CString *) ViewHeaderList.RemoveHead();
	}

}


/////////////////////////////////////////////////////////////////////////////
// CGVSummary serialization

void CGVSummary::Serialize(CArchive& ar)
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
// CGVSummary diagnostics

#ifdef _DEBUG
void CGVSummary::AssertValid() const
{
	CObject::AssertValid();
}

void CGVSummary::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CGVSummary::AddHeader( CString* nString )
{
	ViewHeaderList.AddTail( nString );
}

void 
CGVSummary::AddData( CGeneString* nString )
{
	ViewDataList.AddTail(nString);
}

void 
CGVSummary::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int SumWidth)
{
	// TODO: calculate the total size of this view

	m_SumWidth = SumWidth;
	m_YSize = ViewDataList.GetCount() * m_LineHeight;
	m_XSize = ((CGeneString *)ViewDataList.GetHead())->GetLength() * SumWidth;

	*YSize = m_YSize;
	*XSize = m_XSize;

	return;
}

int 
CGVSummary::GetGVEditRows()
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
CGVSummary::GetPartialPageSize(
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
CGVSummary::OnDraw( DrawStruct *DrawStc )
{

	char tOut[2];
	CGenedocDoc *pDoc = ((CSummaryView *)DrawStc->pView)->GetDocument();
	
	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;
	CBrush tBrush;
	CBrush bBrush;

	DWORD SumWidth = ((CSummaryView *)DrawStc->pView)->m_SumWidth;
	DWORD wl, wc, wr;

	switch ( SumWidth ) {
	case 1:
		wl = 0;
		wc = 1;
		wr = 0;
		break;
	case 2:
		if ( !pDoc->m_UserVars.m_Sum2Wid ) {
			wl = 1;
			wc = 1;
			wr = 0;
		} else {
			wl = 0;
			wc = 2;
			wr = 0;
		}
		break;
	default:
		wc = wl = SumWidth / 3;
		wr = SumWidth - (2 * (SumWidth / 3));
		break;
	}

	typedef struct {
		DWORD OffSet;
		DWORD Size;
		CBrush* pBrush;
	} stcColDEnt;

	// Blank
	stcColDEnt Y11 = {0, m_LineHeight, &bBrush };

	// Single Dot
	stcColDEnt Y21 = {0, (m_LineHeight - wc) / 2, &bBrush};
	stcColDEnt Y22 = {(m_LineHeight - wc) / 2, wc, &tBrush};
	stcColDEnt Y23 = {((m_LineHeight - wc) / 2) + wc, m_LineHeight - (((m_LineHeight - wc) / 2) + wc), &bBrush};
	
	DWORD D1 = (m_LineHeight - (2 * wc)) / 4;

	// Double Dot
	stcColDEnt Y31 = { 0, D1, &bBrush };
	stcColDEnt Y32 = { D1, wc, &tBrush };
	stcColDEnt Y33 = { D1 + wc, m_LineHeight - (2 * wc) - (2 * D1), &bBrush };
	stcColDEnt Y34 = { m_LineHeight - D1 - wc, wc, &tBrush };
	stcColDEnt Y35 = { m_LineHeight - D1, D1, &bBrush };

	// Dash
	stcColDEnt Y41 = { 0, D1, &bBrush };
	stcColDEnt Y42 = { D1, m_LineHeight - (2 * D1), &tBrush };
	stcColDEnt Y43 = { m_LineHeight - D1, D1, &bBrush };

	tOut[1] = 0;


	UINT RowNum = 0;
	UINT ConsensusCount = -1;
	// Is consensus top?

	int tRC = ViewDataList.GetCount();
	if ( pDoc->m_UserVars.m_ConsensusLine == 0 ) {
		// Use Top Consensus Row
		ConsensusCount = 1;
	} else if ( pDoc->m_UserVars.m_ConsensusLine == 1 ) {
		// Use Bottom Consensus Row
		ConsensusCount = tRC - 1;
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

				UINT tXLoc1 = tCount*m_SumWidth + m_SumWidth + m_XPosition;
				UINT tXLoc2 = tCount*m_SumWidth + m_XPosition;

				if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {
		
					// i is set to chading level
					COLORREF TextColor, BkColor;
					TextColor = tStr[tCount].TextColor;
					BkColor = tStr[tCount].BackColor;

					if ( pDoc->m_UserVars.m_SumTextBlack ) {
						tBrush.CreateSolidBrush( RGB(0,0,0) );
					} else {
						tBrush.CreateSolidBrush( TextColor );
					}
					bBrush.CreateSolidBrush( BkColor );

					char tOut = tStr[tCount].CharDisplay;
					tOut = toupper(tOut);

					DWORD Y = (CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset;
					UINT X = tXLoc2 - DrawStc->DisplayXPosition;

					// Blank Area.
					if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE && RowNum != ConsensusCount) {
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y), CSize(SumWidth, m_LineHeight)),  &bBrush );
						tBrush.DeleteObject();
						bBrush.DeleteObject();
						continue;
					}

					// Center Gap - 2, 2, 2
					if ( !(tOut >= 'A' && tOut <= 'Z' || tOut >= '0' && tOut <= '9') ) {
						if ( wl != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wl, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wl, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wl, Y23.Size)),  Y23.pBrush );
						}
						// wc
						X += wl;
						// Y21
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wc, Y21.Size)),  Y21.pBrush );
						// Y22
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wc, Y22.Size)),  Y22.pBrush );
						// Y23
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wc, Y23.Size)),  Y23.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wr, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wr, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wr, Y23.Size)),  Y23.pBrush );
						}

						tBrush.DeleteObject();
						bBrush.DeleteObject();
						continue;
					}

					// PG = 8, NG = 4, PE = 2, NE = 1
					int sc = 0;

					if ( tCount == 0 ) {
						sc += 2;
					} else {
						char tp = toupper( tStr[tCount-1].CharDisplay );
						if ( !(tp >= 'A' && tp <= 'Z' || tp >= '0' && tp <= '9') ) {
							sc += 8;
						}
					}

					if ( tCount == tMax - 1 ) {
						sc += 1;
					} else {
						char tp = toupper( tStr[tCount+1].CharDisplay );
						if ( !(tp >= 'A' && tp <= 'Z' || tp >= '0' && tp <= '9') ) {
							sc += 4;
						}
					}

					switch ( sc ) {
					case 0:
						if ( wl != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wl, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wl, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wl, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wl, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wl, Y35.Size)),  Y35.pBrush );
						}
						// wc
						X += wl;
						// Y31
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wc, Y31.Size)),  Y31.pBrush );
						// Y32
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wc, Y32.Size)),  Y32.pBrush );
						// Y33
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wc, Y33.Size)),  Y33.pBrush );
						// Y34
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wc, Y34.Size)),  Y34.pBrush );
						// Y35
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wc, Y35.Size)),  Y35.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wr, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wr, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wr, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wr, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wr, Y35.Size)),  Y35.pBrush );
						}
						break;
					case 4:
						if ( wl != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wl, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wl, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wl, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wl, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wl, Y35.Size)),  Y35.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wr, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wr, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wr, Y23.Size)),  Y23.pBrush );
						}
						break;
					case 8:
						if ( wl != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wl, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wl, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wl, Y23.Size)),  Y23.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wr, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wr, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wr, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wr, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wr, Y35.Size)),  Y35.pBrush );
						}
						break;
					case 12:
						if ( wl != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wl, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wl, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wl, Y23.Size)),  Y23.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wr, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wr, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wr, Y23.Size)),  Y23.pBrush );
						}
						break;
					case 2:
						if ( wl != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wl, Y11.Size)),  Y11.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wr, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wr, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wr, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wr, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wr, Y35.Size)),  Y35.pBrush );
						}
						break;
					case 1:
						if ( wl != 0 ) {
							// Y31
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y31.OffSet + Y), CSize(wl, Y31.Size)),  Y31.pBrush );
							// Y32
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y32.OffSet + Y), CSize(wl, Y32.Size)),  Y32.pBrush );
							// Y33
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y33.OffSet + Y), CSize(wl, Y33.Size)),  Y33.pBrush );
							// Y34
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y34.OffSet + Y), CSize(wl, Y34.Size)),  Y34.pBrush );
							// Y35
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y35.OffSet + Y), CSize(wl, Y35.Size)),  Y35.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wr, Y11.Size)),  Y11.pBrush );
						}
						break;
					case 3:
						if ( wl != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wl, Y11.Size)),  Y11.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wr, Y11.Size)),  Y11.pBrush );
						}
						break;
					case 9:
						if ( wl != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wl, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wl, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wl, Y23.Size)),  Y23.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wr, Y11.Size)),  Y11.pBrush );
						}
						break;
					case 6:
						if ( wl != 0 ) {
							// Y11
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y11.OffSet + Y), CSize(wl, Y11.Size)),  Y11.pBrush );
						}
						// wc
						X += wl;
						// Y41
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y41.OffSet + Y), CSize(wc, Y41.Size)),  Y41.pBrush );
						// Y42
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y42.OffSet + Y), CSize(wc, Y42.Size)),  Y42.pBrush );
						// Y43
						DrawStc->pDC->FillRect( CRect( CPoint(X, Y43.OffSet + Y), CSize(wc, Y43.Size)),  Y43.pBrush );

						X += wc;
						if ( wr != 0 ) {
							// Y21
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y21.OffSet + Y), CSize(wr, Y21.Size)),  Y21.pBrush );
							// Y22
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y22.OffSet + Y), CSize(wr, Y22.Size)),  Y22.pBrush );
							// Y23
							DrawStc->pDC->FillRect( CRect( CPoint(X, Y23.OffSet + Y), CSize(wr, Y23.Size)),  Y23.pBrush );
						}
						break;
					}

					tBrush.DeleteObject();
					bBrush.DeleteObject();

				}
			}
		}

		CurrentDisplayLoc += m_LineHeight;
		RowNum++;

	}
	
	// Check for Column Inverse
	
	if ( 
		DrawStc->MenuFunc == CSummaryView::DEF_GENESELECTCOL  
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
					tcRect.TopLeft().x + (int)((EndRange + 1 - tGStr->GetStartPos()) * m_SumWidth);
			}
	
			if ( StartRange > tGStr->GetStartPos() ) {
				tcRect.TopLeft().x += (int)((StartRange - tGStr->GetStartPos()) * m_SumWidth);
			}
		
			DrawStc->pDC->InvertRect( tcRect );
		}
	}
}


void 
CGVSummary::InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2)
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

		if ( ((CSummaryView*)pWnd)->IsVisible( tXPosition, tYPosition, tXSize, tYSize ) ) {

			if ( EndRange < (tGStr->GetStartPos() + tGStr->GetLength() ) ) {
				// tXSize = (UINT)((EndRange + 1 - tGStr->GetStartPos()) * m_SumWidth);
				tXSize = (UINT)((EndRange + 1 - StartRange) * m_SumWidth);
			}

			if ( StartRange > tGStr->GetStartPos() ) {
				tXPosition += (UINT)((StartRange - tGStr->GetStartPos()) * m_SumWidth);
			}
			((CSummaryView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

		}
	}
}

//
void 
CGVSummary::OnLButtonDown(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{

	DeSelect();		// Clear return flag
	pViewRet->Clip = 0;
	
	if ( !m_pBase->IsKindOf(RUNTIME_CLASS(CGSFiller)) )
		return;

	if ( pViewRet->MenuFunc == 0 ) {
		return;
	}
	
	if ( pViewRet->MenuFunc == CSummaryView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_SumWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( pViewRet->ColSelBegin == 0 ) {

			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;
			pViewRet->ColSelBegin = 1;

			UINT tXPosition, tXSize;
			DWORD tYPosition, tYSize;
			GetPosition( &tXPosition, &tYPosition );
			GetSize( &tXSize, &tYSize );

			tXPosition += (tCount * m_SumWidth);
			tXSize = m_SumWidth;
	
			((CSummaryView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );
			
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

			((CSummaryView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelStart, pViewRet->ColSelEnd);
			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;

		} else {
			((CSummaryView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
		return;
	}

}

void 
CGVSummary::OnMouseMove(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{
	if ( pViewRet->MenuFunc == CSummaryView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_SumWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( gloc != pViewRet->ColSelEnd ) {
			((CSummaryView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	}
}


void 
CGVSummary::OnLButtonUp(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{
	if ( pViewRet->MenuFunc == CSummaryView::DEF_GENESELECTCOL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_SumWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();
		
		if ( gloc != pViewRet->ColSelEnd ) {
			((CSummaryView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	}
}


void 
CGVSummary::OnLButtonDblClk(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{
}

void 
CGVSummary::WritePict( CPictFile* pPictFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	COLORREF tBrush;
	COLORREF bBrush;
	int wl, wc, wr;

	int Height = pPictFile->m_dev_ysize;
	int Width = 72 / pDoc->m_UserVars.m_SumColInch;
	if ( Width == 0 ) Width = 1;

	switch ( Width ) {
	case 1:
		wl = 0;
		wc = 1;
		wr = 0;
		break;
	case 2:
		if ( !pDoc->m_UserVars.m_Sum2Wid ) {
			wl = 1;
			wc = 1;
			wr = 0;
		} else {
			wl = 0;
			wc = 2;
			wr = 0;
		}
		break;
	default:
		wc = wl = Width / 3;
		wr = Width - (2 * (Width / 3));
		break;
	}

	typedef struct {
		int OffSet;
		int Size;
		COLORREF *pBrush;
	} stcColDEnt;

	stcColDEnt Y11 = {0, Height, &bBrush };

	stcColDEnt Y21 = {0, (Height - wc) / 2, &bBrush};
	stcColDEnt Y22 = {(Height - wc) / 2, wc, &tBrush};
	stcColDEnt Y23 = {((Height - wc) / 2) + wc, Height - (((Height - wc) / 2) + wc), &bBrush};
	
	int D1 = (Height - (2 * wc)) / 4;

	stcColDEnt Y31 = { 0, D1, &bBrush };
	stcColDEnt Y32 = { D1, wc, &tBrush };
	stcColDEnt Y33 = { D1 + wc, Height - (2 * wc) - (2 * D1), &bBrush };
	stcColDEnt Y34 = { Height - D1 - wc, wc, &tBrush };
	stcColDEnt Y35 = { Height - D1, D1, &bBrush };

	stcColDEnt Y41 = { 0, D1, &bBrush };
	stcColDEnt Y42 = { D1, Height - (2 * D1), &tBrush };
	stcColDEnt Y43 = { Height - D1, D1, &bBrush };

	UINT sRowNum = RowNumber;

	UINT ConsensusCount = -1;
	int tRC = ViewDataList.GetCount();
	if ( pDoc->m_UserVars.m_ConsensusLine == 0 ) {
		// Use Top Consensus Row
		ConsensusCount = 1;
	} else if ( pDoc->m_UserVars.m_ConsensusLine == 1 ) {
		// Use Bottom Consensus Row
		ConsensusCount = tRC - 1;
	}

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &tBrush, &bBrush );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					tBrush = tStr->TextColor;
					bBrush = tStr->BackColor;
				}

				if ( pDoc->m_UserVars.m_SumTextBlack ) {
					tBrush = RGB(0,0,0);
				}

//				pPictFile->CharOut( tStr->CharDisplay, TextC, BkC );
//
//
				UINT X = 0;
				char tOut = toupper(tStr->CharDisplay);

				if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE && sRowNum != ConsensusCount) {
					pPictFile->SumFillRect( CRect( CPoint(X, 0), CSize(Width, Height)),  &bBrush );
					pPictFile->SumChar(Width);
					tStr++;
					continue;
				}

				// Center Gap - 2, 2, 2
				if ( !(tOut >= 'A' && tOut <= 'Z' || tOut >= '0' && tOut <= '9') ) {
					if ( wl != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wl, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wl, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wl, Y23.Size)),  Y23.pBrush );
					}
					// wc
					X += wl;
					// Y21
					pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wc, Y21.Size)),  Y21.pBrush );
					// Y22
					pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wc, Y22.Size)),  Y22.pBrush );
					// Y23
					pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wc, Y23.Size)),  Y23.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wr, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wr, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wr, Y23.Size)),  Y23.pBrush );
					}

					pPictFile->SumChar(Width);
					tStr++;
					continue;
				}

				// PG = 8, NG = 4, PE = 2, NE = 1
				int sc = 0;

				if ( i == 0 ) {
					sc += 2;
				} else {
					char tp = toupper( (tStr-1)->CharDisplay );
					if ( !(tp >= 'A' && tp <= 'Z' || tp >= '0' && tp <= '9') ) {
						sc += 8;
					}
				}

				if ( i == tMax - 1 ) {
					sc += 1;
				} else {
					char tp = toupper( (tStr+1)->CharDisplay );
					if ( !(tp >= 'A' && tp <= 'Z' || tp >= '0' && tp <= '9') ) {
						sc += 4;
					}
				}

				switch ( sc ) {
				case 0:
					if ( wl != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wl, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wl, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wl, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wl, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wl, Y35.Size)),  Y35.pBrush );
					}
					// wc
					X += wl;
					// Y31
					pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wc, Y31.Size)),  Y31.pBrush );
					// Y32
					pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wc, Y32.Size)),  Y32.pBrush );
					// Y33
					pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wc, Y33.Size)),  Y33.pBrush );
					// Y34
					pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wc, Y34.Size)),  Y34.pBrush );
					// Y35
					pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wc, Y35.Size)),  Y35.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wr, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wr, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wr, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wr, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wr, Y35.Size)),  Y35.pBrush );
					}
					break;
				case 4:
					if ( wl != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wl, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wl, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wl, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wl, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wl, Y35.Size)),  Y35.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wr, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wr, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wr, Y23.Size)),  Y23.pBrush );
					}
					break;
				case 8:
					if ( wl != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wl, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wl, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wl, Y23.Size)),  Y23.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wr, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wr, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wr, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wr, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wr, Y35.Size)),  Y35.pBrush );
					}
					break;
				case 12:
					if ( wl != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wl, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wl, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wl, Y23.Size)),  Y23.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wr, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wr, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wr, Y23.Size)),  Y23.pBrush );
					}
					break;
				case 2:
					if ( wl != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wl, Y11.Size)),  Y11.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wr, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wr, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wr, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wr, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wr, Y35.Size)),  Y35.pBrush );
					}
					break;
				case 1:
					if ( wl != 0 ) {
						// Y31
						pPictFile->SumFillRect( CRect( CPoint(X, Y31.OffSet), CSize(wl, Y31.Size)),  Y31.pBrush );
						// Y32
						pPictFile->SumFillRect( CRect( CPoint(X, Y32.OffSet), CSize(wl, Y32.Size)),  Y32.pBrush );
						// Y33
						pPictFile->SumFillRect( CRect( CPoint(X, Y33.OffSet), CSize(wl, Y33.Size)),  Y33.pBrush );
						// Y34
						pPictFile->SumFillRect( CRect( CPoint(X, Y34.OffSet), CSize(wl, Y34.Size)),  Y34.pBrush );
						// Y35
						pPictFile->SumFillRect( CRect( CPoint(X, Y35.OffSet), CSize(wl, Y35.Size)),  Y35.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wr, Y11.Size)),  Y11.pBrush );
					}
					break;
				case 3:
					if ( wl != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wl, Y11.Size)),  Y11.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wr, Y11.Size)),  Y11.pBrush );
					}
					break;
				case 9:
					if ( wl != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wl, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wl, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wl, Y23.Size)),  Y23.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wr, Y11.Size)),  Y11.pBrush );
					}
					break;
				case 6:
					if ( wl != 0 ) {
						// Y11
						pPictFile->SumFillRect( CRect( CPoint(X, Y11.OffSet), CSize(wl, Y11.Size)),  Y11.pBrush );
					}
					// wc
					X += wl;
					// Y41
					pPictFile->SumFillRect( CRect( CPoint(X, Y41.OffSet), CSize(wc, Y41.Size)),  Y41.pBrush );
					// Y42
					pPictFile->SumFillRect( CRect( CPoint(X, Y42.OffSet), CSize(wc, Y42.Size)),  Y42.pBrush );
					// Y43
					pPictFile->SumFillRect( CRect( CPoint(X, Y43.OffSet), CSize(wc, Y43.Size)),  Y43.pBrush );

					X += wc;
					if ( wr != 0 ) {
						// Y21
						pPictFile->SumFillRect( CRect( CPoint(X, Y21.OffSet), CSize(wr, Y21.Size)),  Y21.pBrush );
						// Y22
						pPictFile->SumFillRect( CRect( CPoint(X, Y22.OffSet), CSize(wr, Y22.Size)),  Y22.pBrush );
						// Y23
						pPictFile->SumFillRect( CRect( CPoint(X, Y23.OffSet), CSize(wr, Y23.Size)),  Y23.pBrush );
					}
					break;
				}
//
//
				pPictFile->SumChar(Width);
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}

void  
CGVSummary::SetStatusBar(UINT nFlags, UINT PointXPosition, DWORD PointYPosition ) 
{
	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_SumWidth * tGStr->GetLength();
		// CRect tRect ( sLoc, tSize );

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {

			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {

				// Fill out selection stuff
				UINT tCount = (PointXPosition - m_XPosition) / m_SumWidth;

                ((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = (DWORD)(tGStr->GetStartPos() + tCount + 1);
				strncpy( 
					((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName, 
					"Column", 
					10 );
				((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[10] = 0;

			} else  {
				// Find Which residue ...
				UINT tCount = (PointXPosition - m_XPosition) / m_SumWidth;
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

