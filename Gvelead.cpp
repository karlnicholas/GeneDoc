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
// GVEditLead.cpp : implementation of the CGVEditLead class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVEditLead

IMPLEMENT_DYNCREATE(CGVEditLead, CObject)


CGVEditLead::CGVEditLead(): CGeneViewBase()
{
	// TODO: add construction code here
}


CGVEditLead::~CGVEditLead()
{

	while ( !ViewDataList.IsEmpty() ) {
		delete (CString *) ViewDataList.RemoveHead();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGVEditLead serialization

void CGVEditLead::Serialize(CArchive& ar)
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
// CGVEditLead diagnostics

#ifdef _DEBUG
void CGVEditLead::AssertValid() const
{
	CObject::AssertValid();
}

void CGVEditLead::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 

CGVEditLead::AddData( CString* nString )
{
	ViewDataList.AddTail(nString);
}


void 
CGVEditLead::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int GVELeadLength )
{
	// TODO: calculate the total size of this view
	pGeneViewParent->GetSize(&m_XSize, &m_YSize);
	m_XSize = GVELeadLength * m_CharWidth;

	// m_DataStartPoint = ViewRect.TopLeft();
	*XSize = m_XSize;
	*YSize = m_YSize;

}

void 
CGVEditLead::OnDraw( DrawStruct *DrawStc )
{
	char tOut[2];
	
	tOut[1] = 0;

	CGenedocDoc *pDoc = ((CGenedocView *)DrawStc->pView)->GetDocument();

	if ( DrawStc->pDC->IsPrinting() ) {
		if ( pDoc->m_UserVars.m_PrintShading ) return;
		DrawStc->pDC->SetBkMode ( TRANSPARENT );
	}

//	int ColorNames = (pDoc->m_UserVars.m_GroupDisplayMode && pDoc->m_UserVars.m_ColorSeqNames);
	int ColorNames = pDoc->m_UserVars.m_ColorSeqNames;
	


	CBrush tBrush;

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	POSITION SegPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	
	int StopColor = 0;
	int StopColorCount = pDoc->m_UserVars.m_strLead.GetLength();
	CGeneSegment *tCGSeg;

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(SegPos);


		if ( (CurrentDisplayLoc + m_LineHeight) > DrawStc->ReDrawTop 
//			&& CurrentDisplayLoc <= DrawStc->ReDrawBottom 
			&& CurrentDisplayLoc < DrawStc->ReDrawBottom 
		) {

			StopColor = 0;
			int cCount = tGStr->GetLength();
			for ( int tCount = 0; tCount < cCount; tCount++ ) {

				UINT tXLoc1 = tCount*m_CharWidth + m_CharWidth + m_XPosition;
				UINT tXLoc2 = tCount*m_CharWidth + m_XPosition;

				if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {

					if ( cCount - StopColorCount <= tCount ) StopColor = 1;
					COLORREF TextColor, BkColor;
					if ( ColorNames && tCGSeg->m_DisplayGroup != 0 && !StopColor ) {

						int LocNum = tCGSeg->m_DisplayGroup;
						int GrpNum = 0;
						CDisplayVars *DisplayVars = NULL;
						POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
						while ( tPos != NULL ) {
							DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
							GrpNum++;
							if ( GrpNum == LocNum ) break;
						}
						if ( DisplayVars != NULL ) DisplayVars->GetTitleColors( &TextColor, &BkColor );

					} else {
						pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextColor, &BkColor );
//						if ( StopColor && !DrawStc->pDC->IsPrinting() && ((CGenedocView *)DrawStc->pView)->m_SelectSeq ) {
						if ( StopColor && !DrawStc->pDC->IsPrinting() ) {
							if ( tCGSeg->GetArrangeFlag() ) {
								COLORREF tColor = BkColor;
								BkColor = TextColor;
								TextColor = tColor;
							}
						}
					}

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

					DrawStc->pDC->SetTextColor( TextColor );

					tOut[0] = (*tGStr)[tCount];

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

/*
					DrawStc->pDC->DrawText( tOut, 1, tcRect, 
						DT_CENTER | DT_NOCLIP | DT_SINGLELINE | DT_NOPREFIX 
					);
*/

					// DrawText
				}
			}
		
//			DrawStc->pDC->TextOut( tRect.TopLeft().x, tRect.TopLeft().y, (const char *)*tGStr );
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
CGVEditLead::CopyText(char * tString, DWORD *dwCount, UINT RowNumber )
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
CGVEditLead::CountCopyText(DWORD *dwCount )
{
	CString * tGStr = (CString *)ViewDataList.GetHead();
	*dwCount = tGStr->GetLength();
}

void 
CGVEditLead::WritePict(CPictFile* pPictFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	POSITION SegPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();

	int ColorNames = pDoc->m_UserVars.m_ColorSeqNames;
	int StopColor = 0;
	int StopColorCount = pDoc->m_UserVars.m_strLead.GetLength();
	
	CGeneSegment *tCGSeg;

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(SegPos);

		if ( RowNumber == 0 ) {

			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {

				if ( StrCount - StopColorCount == i ) StopColor = 1;
				COLORREF TextColor, BkColor;
				if ( ColorNames && tCGSeg->m_DisplayGroup != 0 && !StopColor ) {

					int LocNum = tCGSeg->m_DisplayGroup;
					int GrpNum = 0;
					CDisplayVars *DisplayVars = NULL;
					POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos != NULL ) {
						DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
						GrpNum++;
						if ( GrpNum == LocNum ) break;
					}
					if ( DisplayVars != NULL ) DisplayVars->GetTitleColors( &TextColor, &BkColor );

				} else {
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextColor, &BkColor );
				}
				
				pPictFile->CharOut ( (*tGStr)[i], TextColor, BkColor );
			}
			return;
		}
		RowNumber--;
	}
}

void 
CGVEditLead::WriteHTML(CHTMLFile* pHTMLFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	POSITION SegPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();

	int ColorNames = pDoc->m_UserVars.m_ColorSeqNames;
	int StopColor = 0;
	int StopColorCount = pDoc->m_UserVars.m_strLead.GetLength();
	
	CGeneSegment *tCGSeg;

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(SegPos);

		if ( RowNumber == 0 ) {

			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {

				if ( StrCount - StopColorCount == i ) StopColor = 1;
				COLORREF TextColor, BkColor;
				if ( ColorNames && tCGSeg->m_DisplayGroup != 0 && !StopColor ) {

					int LocNum = tCGSeg->m_DisplayGroup;
					int GrpNum = 0;
					CDisplayVars *DisplayVars = NULL;
					POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos != NULL ) {
						DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
						GrpNum++;
						if ( GrpNum == LocNum ) break;
					}
					if ( DisplayVars != NULL ) DisplayVars->GetTitleColors( &TextColor, &BkColor );

				} else {
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextColor, &BkColor );
				}
				
				pHTMLFile->CharOut ( (*tGStr)[i], TextColor, BkColor );
			}
			return;
		}
		RowNumber--;
	}
}


void 
CGVEditLead::WriteRTF(CRTFFile* pRTFFile, UINT RowNumber, CGenedocDoc *pDoc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	POSITION SegPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();

	int ColorNames = pDoc->m_UserVars.m_ColorSeqNames;
	int StopColor = 0;
	int StopColorCount = pDoc->m_UserVars.m_strLead.GetLength();
	
	CGeneSegment *tCGSeg;

	while ( tPos != NULL ) {
		CString * tGStr = (CString *)ViewDataList.GetNext(tPos);
		tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(SegPos);

		if ( RowNumber == 0 ) {

			int StrCount = tGStr->GetLength();
			for ( int i = 0; i < StrCount; ++i ) {

				if ( StrCount - StopColorCount == i ) StopColor = 1;
				COLORREF TextColor, BkColor;
				if ( ColorNames && tCGSeg->m_DisplayGroup != 0 && !StopColor ) {

					int LocNum = tCGSeg->m_DisplayGroup;
					int GrpNum = 0;
					CDisplayVars *DisplayVars = NULL;
					POSITION tPos = pDoc->m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos != NULL ) {
						DisplayVars = (CDisplayVars *)pDoc->m_UserVars.m_DisplayVars.GetNext(tPos);
						GrpNum++;
						if ( GrpNum == LocNum ) break;
					}
					if ( DisplayVars != NULL ) DisplayVars->GetTitleColors( &TextColor, &BkColor );

				} else {
					pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &TextColor, &BkColor );
				}
				
				pRTFFile->CharOut ( (*tGStr)[i], TextColor, BkColor );
			}
			return;
		}
		RowNumber--;
	}
}

