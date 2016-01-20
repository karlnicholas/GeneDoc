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
// GVEditTail.cpp : implementation of the CGVEditTail class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVEditTail

IMPLEMENT_DYNCREATE(CGVEditTail, CObject)


CGVEditTail::CGVEditTail(): CGeneViewBase()
{
	// TODO: add construction code here
}


CGVEditTail::~CGVEditTail()
{

	while ( !ViewDataList.IsEmpty() ) {
		delete (CString *) ViewDataList.RemoveHead();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGVEditTail serialization

void CGVEditTail::Serialize(CArchive& ar)
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
// CGVEditTail diagnostics

#ifdef _DEBUG
void CGVEditTail::AssertValid() const
{
	CObject::AssertValid();
}

void CGVEditTail::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 

CGVEditTail::AddData( CString* nString )
{
	ViewDataList.AddTail(nString);
}


void 
CGVEditTail::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int GVETailLength )
{
	// TODO: calculate the total size of this view
	pGeneViewParent->GetSize(&m_XSize, &m_YSize);
	m_XSize = GVETailLength * m_CharWidth;

	*YSize = m_YSize;
	*XSize = m_XSize;

	
	return;
}

void 
CGVEditTail::OnDraw( DrawStruct *DrawStc )
{
	char tOut[2];

	CBrush	tBrush;
	
	tOut[1] = 0;

	CGenedocDoc *pDoc = ((CGenedocView *)DrawStc->pView)->GetDocument();


	if ( DrawStc->pDC->IsPrinting() ) {
		if ( pDoc->m_UserVars.m_PrintShading ) return;
		DrawStc->pDC->SetBkMode ( TRANSPARENT );
	}

	POSITION tPos = ViewDataList.GetHeadPosition();
	
	DWORD CurrentDisplayLoc = m_YPosition;

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);

		if ( (CurrentDisplayLoc + m_LineHeight) > DrawStc->ReDrawTop 
//			&& CurrentDisplayLoc <= DrawStc->ReDrawBottom 
			&& CurrentDisplayLoc < DrawStc->ReDrawBottom 
		) {

			int cCount = tGStr->GetLength();
			for ( int tCount = 0; tCount < cCount; tCount++ ) {

				UINT tXLoc1 = tCount*m_CharWidth + m_CharWidth + m_XPosition;
				UINT tXLoc2 = tCount*m_CharWidth + m_XPosition;

				if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {

					COLORREF TextColor, BkColor;

					pDoc->GetLevelColors(&pDoc->m_UserVars.m_Vars, 0, &TextColor, &BkColor );

					CRect tcRect( 
						tXLoc2 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
						tXLoc1 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc + m_LineHeight - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset
					);

					if ( DrawStc->pDC->IsPrinting() ) {

						tBrush.CreateSolidBrush( BkColor );
						DrawStc->pDC->FillRect ( tcRect, &tBrush );
						tBrush.DeleteObject();

					}

					DrawStc->pDC->SetBkColor( BkColor );

					tOut[0] = (*tGStr)[tCount];

					DrawStc->pDC->SetTextColor( TextColor );

					if ( DrawStc->pDC->IsPrinting() ) {
						DrawStc->pDC->TextOut( 
							tXLoc2 - DrawStc->DisplayXPosition, 
							(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
							tOut, 1 
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

//					DrawStc->pDC->DrawText( tOut, 1, tcRect, 
//						DT_CENTER | DT_NOCLIP | DT_SINGLELINE | DT_NOPREFIX 
//					);

				}
			}
		}
		CurrentDisplayLoc += m_LineHeight;
	}

/*
	if ( !DrawStc->pDC->IsPrinting() ) {
		if ( Selected ) {
			DrawStc->pDC->InvertRect( ViewRect);
		}
	}
*/

}



void 
CGVEditTail::UpdateGeneRange(CGVEdit *tEdit, int eval, CView *pWnd)
{

	char tBuff[128];
	POSITION tPose = tEdit->ViewDataList.GetHeadPosition();
	POSITION tPost = ViewDataList.GetHeadPosition();

	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	// sLoc.x += (m_CharWidth * 3);
	sXLoc += (m_CharWidth * 3);

	CGeneString* tCGSt;
	CString *tStr;

	while ( tPose != NULL ) {
   		tCGSt = (CGeneString*)(tEdit->ViewDataList.GetNext(tPose));
   		tStr = (CString *)ViewDataList.GetNext(tPost);
   		if ( !eval-- ) {
   			break;
   		}
		sYLoc += m_LineHeight;
   	}
   	
   	if ( tCGSt->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {
   		return;
   	}

	DWORD lastval = atol(((const char *)(*tStr))+3);
	int redrawflag = 0;

	const GeneStor * pStor = *tCGSt;
	int StorSize = tCGSt->GetLength();
	pStor += (StorSize - 1);

	// while ( (pStor->CharGene == '-') || (pStor->CharGene == '.') ) {
	char tChar = toupper ( pStor->CharGene );
	while ( !(tChar >= 'A' && tChar <= 'Z') ) {
		pStor--;
		if ( !(--StorSize) ) {
			break;
		}
		tChar = toupper ( pStor->CharGene );
	}

	char pszTail[32];
	memset ( pszTail, ' ', 32 );
	pszTail[((CGenedocView*)pWnd)->m_IndLength] = 0;

	if ( !StorSize ) {
		// _snprintf( tBuff, m_GVETailLength, "  :%5s", "-" );
		pszTail[((CGenedocView*)pWnd)->m_IndLength - 1] = '-';
	} else {
		// _snprintf( tBuff, m_GVETailLength, "  :%5ld", pStor->GeneSeqNumber );
		char pszConv[32];
		_ltoa( pStor->GeneSeqNumber, pszConv, 10 );
		strcpy( &pszTail[((CGenedocView*)pWnd)->m_IndLength - strlen(pszConv)], pszConv );
	}

	strcpy ( tBuff, ((CGenedocView*)pWnd)->GetDocument()->m_UserVars.m_strTail );
	strcat ( tBuff, pszTail );

	*tStr = tBuff;


	if ( redrawflag ) {

		UINT XSize = m_CharWidth * (((CGenedocView*)pWnd)->m_GVETailLength - 3);
		DWORD YSize = m_LineHeight;
		
		if ( ((CGenedocView*)pWnd)->IsVisible( sXLoc, sYLoc, XSize, YSize ) ) {
			((CGenedocView*)pWnd)->InvalidateRectLP( sXLoc, sYLoc, XSize, YSize );
		}
	}
}


void 
CGVEditTail::CopyText(char * tString, DWORD *dwCount, UINT RowNumber )
{

	POSITION tPos = ViewDataList.GetHeadPosition();

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {
				tString[*dwCount] = (*tGStr)[i];
				(*dwCount)++;
			}
			return;
		}
		RowNumber--;
	}
}

void 
CGVEditTail::CountCopyText(DWORD *dwCount)
{
	CString * tGStr = (CString *)ViewDataList.GetHead();
	*dwCount = tGStr->GetLength();
}


void 
CGVEditTail::WritePict(CPictFile* pPictFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {
				pPictFile->CharOut ( 
					(*tGStr)[i], 
					pDoc->m_UserVars.m_ForeColor0, 
					pDoc->m_UserVars.m_BackColor0
				);
			}
			return;
		}
		RowNumber--;
	}
}


void 
CGVEditTail::WriteHTML(CHTMLFile* pHTMLFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {
				pHTMLFile->CharOut ( 
					(*tGStr)[i], 
					pDoc->m_UserVars.m_ForeColor0, 
					pDoc->m_UserVars.m_BackColor0
				);
			}
			return;
		}
		RowNumber--;
	}
}


void 
CGVEditTail::WriteRTF(CRTFFile* pRTFFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {
				pRTFFile->CharOut ( 
					(*tGStr)[i], 
					pDoc->m_UserVars.m_ForeColor0, 
					pDoc->m_UserVars.m_BackColor0
				);
			}
			return;
		}
		RowNumber--;
	}
}

