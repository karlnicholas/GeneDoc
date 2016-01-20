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
// sumview.cpp : implementation of the CSummaryView class
//

#include "stdafx.h"

#ifdef WIN32

#define VIEW_CLIP_LEFT 1
#define VIEW_CLIP_RIGHT 0

#else 

#define VIEW_CLIP_LEFT 0
#define VIEW_CLIP_RIGHT 0

#endif


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSummaryView

IMPLEMENT_DYNCREATE(CSummaryView, CView)

BEGIN_MESSAGE_MAP(CSummaryView, CView)
	//{{AFX_MSG_MAP(CSummaryView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_KEYUP()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDM_GENECREATEWIN, OnGenecreatewin)
	ON_UPDATE_COMMAND_UI(IDM_GENECREATEWIN, OnUpdateGenecreatewin)
	ON_COMMAND(IDM_SELECT, OnSelect)
	ON_UPDATE_COMMAND_UI(IDM_SELECT, OnUpdateSelect)
	ON_COMMAND(IDM_SELECTCOL, OnSelectcol)
	ON_UPDATE_COMMAND_UI(IDM_SELECTCOL, OnUpdateSelectcol)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPYINV, OnEditCopyinv)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYINV, OnUpdateEditCopyinv)
	ON_COMMAND(ID_EDIT_COPY0, OnEditCopy0)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY0, OnUpdateEditCopy0)
	ON_COMMAND(ID_EDIT_COPY8, OnEditCopy8)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY8, OnUpdateEditCopy8)
	ON_COMMAND(ID_EDIT_COPYINV0, OnEditCopyinv0)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYINV0, OnUpdateEditCopyinv0)
	ON_COMMAND(ID_EDIT_COPYINV8, OnEditCopyinv8)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYINV8, OnUpdateEditCopyinv8)
	ON_COMMAND(ID_EDIT_COPYINVBIT, OnEditCopyinvbit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYINVBIT, OnUpdateEditCopyinvbit)
	ON_COMMAND(ID_EDIT_COPYBIT, OnEditCopybit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYBIT, OnUpdateEditCopybit)
	ON_COMMAND(IDM_GENECOPYPICT, OnGenecopypict)
	ON_UPDATE_COMMAND_UI(IDM_GENECOPYPICT, OnUpdateGenecopypict)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(IDM_COPYMETACLIP, OnCopymetaclip)
	ON_COMMAND(IDM_COPYMETAFILE, OnCopymetafile)
	ON_UPDATE_COMMAND_UI(IDM_COPYMETACLIP, OnUpdateCopymetaclip)
	ON_UPDATE_COMMAND_UI(IDM_COPYMETAFILE, OnUpdateCopymetafile)
	ON_COMMAND(IDM_DSTATSCORE, OnDstatscore)
	ON_UPDATE_COMMAND_UI(IDM_DSTATSCORE, OnUpdateDstatscore)
	ON_COMMAND(IDM_DSTATSCOREALL, OnDstatscoreall)
	ON_UPDATE_COMMAND_UI(IDM_DSTATSCOREALL, OnUpdateDstatscoreall)
	//}}AFX_MSG_MAP
#ifdef WIN32
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
#endif
END_MESSAGE_MAP()

	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
/////////////////////////////////////////////////////////////////////////////
// CSummaryView construction/destruction

CSummaryView::CSummaryView()
{
	// TODO: add construction code here

	m_SelectDevice = NONE;
	m_PrintOnly = 0;

#ifdef _MAC
	m_ClipFuncClipFunc = FALSE;
#endif

	ClearMenu();
}

CSummaryView::~CSummaryView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pSummaryView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSummaryView drawing

void
CSummaryView::CleanRowViewList()
{
	while ( !m_RowViewList.IsEmpty() ) {
		CGPSumView *tRV = ( CGPSumView *)m_RowViewList.RemoveHead();
		while ( ! (tRV->ViewDataList.IsEmpty()) ) {
			delete ( CGeneViewBase *)tRV->ViewDataList.RemoveHead();
		}
		delete tRV;
	}
}

void
CSummaryView::AddHeadTail( CGVSummary* tGEt, CGVSummary* tGEh, CGPSumView* tRowView )
{
	char tBuff[128];
	CString *tStr;
	POSITION tPosh;
	POSITION tPost;
	POSITION tPvt;
   	CGeneSegment *tCGSegh;
   	CGeneSegment *tCGSegt;
   	CGeneString *tCGSt;

	CGeneSegBase * tGSBh = tGEh->m_pBase;
	CGeneSegBase * tGSBt = tGEt->m_pBase;


	CGVEditLead* tGEL = new CGVEditLead();
	if ( tGEL == 0 ) {
		AfxMessageBox( "Genedvw:new:fail:1" );
		return;
	}
	CGVEditTail* tGET = new CGVEditTail();
	if ( tGET == 0 ) {
		AfxMessageBox( "sumview:new:fail:2" );
		return;
	}

	tPosh = tGSBh->SegDataList.GetHeadPosition();
	tPost = tGSBt->SegDataList.GetHeadPosition();
	tPvt = tGEt->ViewDataList.GetHeadPosition();

	while ( tPosh != NULL ) {

   		tCGSegh = (CGeneSegment *)tGSBh->SegDataList.GetNext(tPosh);
   		tCGSegt = (CGeneSegment *)tGSBt->SegDataList.GetNext(tPost);
   		tCGSt = (CGeneString *)tGEt->ViewDataList.GetNext(tPvt);

		// Test for comment Row.   		
   		if ( tCGSegh->GetStyle() != LINESEQUENCE ) {
			memset ( tBuff, ' ', m_GVELeadLength );
			tBuff[m_GVELeadLength] = 0;
			tStr = new CString (tBuff);
			if ( tStr == 0 ) {
				AfxMessageBox( "sumview:new:fail:3" );
				return;
			}
			tGEL->AddData ( tStr );
			memset ( tBuff, ' ', m_GVETailLength );
			tBuff[m_GVETailLength] = 0;
			tStr = new CString (tBuff);
			if ( tStr == 0 ) {
				AfxMessageBox( "sumview:new:fail:4" );
				return;
			}
			tGET->AddData ( tStr );
   			continue;
   		}
   		

		CString strTit = tCGSegh->GetTitle();
		while ( strTit.GetLength() < m_NamesLength ) strTit += ' ';
		strcpy ( tBuff, strTit.Left(m_NamesLength) );

		if ( GetDocument()->m_UserVars.m_LocAfterName ) {
			const GeneStor * pStor = *tCGSt;
			int StorSize = tCGSt->GetLength();

			char tChar = toupper ( pStor->CharGene );
			while ( !(tChar >= 'A' && tChar <= 'Z') ) {
				pStor++;
				if ( !(--StorSize) ) {
					break;
				}
				tChar = toupper ( pStor->CharGene );
			}

			char pszTail[32];
			memset ( pszTail, ' ', 32 );
			pszTail[m_IndLength] = 0;

			if ( !StorSize ) {
				// _snprintf( tBuff, m_GVETailLength, "  :%5s", "-" );
				pszTail[m_IndLength - 1] = '-';
			} else {
				// _snprintf( tBuff, m_GVETailLength, "  :%5ld", pStor->GeneSeqNumber );
				char pszConv[32];
				_ltoa( pStor->GeneSeqNumber, pszConv, 10 );
				strcpy( &pszTail[m_IndLength - strlen(pszConv)], pszConv );
			}

			strcat ( tBuff, " " );
			strcat ( tBuff, pszTail );

		}
		
		strcat ( tBuff, GetDocument()->m_UserVars.m_strLead );
		tBuff[m_GVELeadLength] = 0;
		tStr = new CString (tBuff);
		if ( tStr == 0 ) {
			AfxMessageBox( "sumview:new:fail:5" );
			return;
		}
		tGEL->AddData ( tStr );

		if ( GetDocument()->m_UserVars.m_LocAfterSeq) {
			const GeneStor * pStor = *tCGSt;
			int StorSize = tCGSt->GetLength();
			pStor += (StorSize - 1);

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
			pszTail[m_IndLength] = 0;

			if ( !StorSize ) {
				// _snprintf( tBuff, m_GVETailLength, "  :%5s", "-" );
				pszTail[m_IndLength - 1] = '-';
			} else {
				// _snprintf( tBuff, m_GVETailLength, "  :%5ld", pStor->GeneSeqNumber );
				char pszConv[32];
				_ltoa( pStor->GeneSeqNumber, pszConv, 10 );
				strcpy( &pszTail[m_IndLength - strlen(pszConv)], pszConv );
			}

			strcpy ( tBuff, GetDocument()->m_UserVars.m_strTail );
			strcat ( tBuff, pszTail );

			tBuff[m_GVETailLength] = 0;
			tStr = new CString (tBuff);
			if ( tStr == 0 ) {
				AfxMessageBox( "sumview:new:fail:6" );
				return;
			}
			tGET->AddData ( tStr );
		}

	}

	UINT tXPos;
	DWORD tYPos;
	tRowView->GetPosition( &tXPos, &tYPos );
	tGEL->SetPosition ( tXPos, tRowView->m_IntYPos );
	tGEL->pGeneViewParent = tRowView;
	tGEL->SetEnum(m_LeaderSaveEnum);

	tGEL->m_CharWidth = m_CharWidth;
	tGEL->m_LineHeight = m_LineHeight;

	tGEL->CalcDrawSize( m_pDC, &tXPos, &tYPos, m_GVELeadLength );

	tRowView->AddHead(tGEL );

	tGET->SetPosition ( tRowView->m_IntXPos, tRowView->m_IntYPos );
	tGET->pGeneViewParent = tRowView;
	tGET->SetEnum(m_EnumCount++);

	tGET->m_CharWidth = m_CharWidth;
	tGET->m_LineHeight = m_LineHeight;

	tGET->CalcDrawSize( m_pDC, &tXPos, &tYPos, m_GVETailLength );

	tRowView->AddTail(tGET);

}

void
CSummaryView::AddHead( CGVSummary* tGEh, CGPSumView* tRowView )
{
	char tBuff[128];
	CString *tStr;

	CGeneSegBase * tGSBh = tGEh->m_pBase;


	CGVEditLead* tGEL = new CGVEditLead();
	if ( tGEL == 0 ) {
		AfxMessageBox( "sumview:new:fail:7" );
		return;
	}

	POSITION tPosh = tGSBh->SegDataList.GetHeadPosition();

	while ( tPosh != NULL ) {

   		CGeneSegment *tCGSegh = (CGeneSegment *)(tGSBh->SegDataList.GetNext(tPosh));

		// Test for comment Row.   		
   		if ( tCGSegh->GetStyle() != LINESEQUENCE ) {
			memset ( tBuff, ' ', m_GVELeadLength );
			tBuff[m_GVELeadLength] = 0;
			tStr = new CString (tBuff);
			if ( tStr == 0 ) {
				AfxMessageBox( "sumview:new:fail:8" );
				return;
			}
			tGEL->AddData ( tStr );
   			continue;
   		}

		CString strTit = tCGSegh->GetTitle();
		while ( strTit.GetLength() < m_NamesLength ) strTit += ' ';
		strcpy ( tBuff, strTit.Left(m_NamesLength) );
		strcat ( tBuff, GetDocument()->m_UserVars.m_strLead );
		tBuff[m_GVELeadLength] = 0;
		tStr = new CString (tBuff);
		if ( tStr == 0 ) {
			AfxMessageBox( "sumview:new:fail:9" );
			return;
		}
		tGEL->AddData ( tStr );

	}
                            
	UINT tXPos;
	DWORD tYPos;
	tRowView->GetPosition( &tXPos, &tYPos );
	tGEL->SetPosition ( tXPos, tRowView->m_IntYPos );
	tGEL->pGeneViewParent = tRowView;
	tGEL->SetEnum(m_LeaderSaveEnum);

	tGEL->m_CharWidth = m_CharWidth;
	tGEL->m_LineHeight = m_LineHeight;

	tGEL->CalcDrawSize( m_pDC, &tXPos, &tYPos, m_GVELeadLength );

	tRowView->AddHead(tGEL );

}

void 
CSummaryView::ResetGPSize(CDC* pDC, UINT MaxX )
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CleanRowViewList();

//	m_MaxX = tMaxX;
	m_pDC = pDC;
	m_EnumCount = 0;

	pDoc->BeginWaitCursor(); // Let em know


	CFont m_Font;
	LOGFONT m_LOGFONT;
	memset ( &m_LOGFONT, 0, sizeof(m_LOGFONT) );
	strcpy ( m_LOGFONT.lfFaceName, "Courier New" );
	m_LOGFONT.lfWeight = pDoc->m_UserVars.m_FontWeight;
	m_LOGFONT.lfHeight = -MulDiv( pDoc->m_UserVars.m_FontSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);
	m_Font.CreateFontIndirect( &m_LOGFONT );

	CFont *oFont = (CFont*)pDC->SelectObject( &m_Font);
	CPen *oPen = (CPen*)pDC->SelectStockObject( BLACK_PEN );
	CBrush *oBrush = (CBrush *)pDC->SelectStockObject( BLACK_BRUSH );

	TEXTMETRIC TM;
	pDC->GetTextMetrics( &TM );
	// pDC->GetOutputTextMetrics( &TM );
	m_CharWidth = TM.tmAveCharWidth;
//	m_CharWidth = TM.tmMaxCharWidth;
//	m_LineHeight = TM.tmHeight - TM.tmInternalLeading;
	m_LineHeight = TM.tmHeight;
	// For Pict Files.
	m_Descent = TM.tmDescent;

	int PixInch = pDC->GetDeviceCaps( LOGPIXELSX );		// Pixels Per Inch
	m_SumWidth = PixInch / pDoc->m_UserVars.m_SumColInch;
	if ( m_SumWidth == 0 ) m_SumWidth = 1;
/*
	CSize tSize = pDC->GetTextExtent("D", 1);

	m_LineHeight = tSize.cy;
	m_CharWidth = tSize.cx;
	m_Descent = 0;

*/	

	if ( pDoc->pGSFiller != NULL ) {
		m_NamesLength = 0;

		POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() == LINESEQUENCE ) 
				if ( tCGSeg->GetTitle().GetLength() > m_NamesLength ) 
					m_NamesLength = tCGSeg->GetTitle().GetLength();

		}
		
		if (m_NamesLength > pDoc->m_UserVars.m_MaxNameLength ) {
			m_NamesLength = pDoc->m_UserVars.m_MaxNameLength;
		}

		m_GVELeadLength = m_NamesLength + strlen(pDoc->m_UserVars.m_strLead);
		
		m_IndLength = 0;

		tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				DWORD dwLR = tCGSeg->GetLastResidue();
				int iSize  = 1;
				while ( dwLR >= 10 ) {
					iSize++;
					dwLR /= 10L;
				}
					
				if ( iSize > m_IndLength ) 
					m_IndLength = iSize;
			}

		}
		
		m_GVETailLength = m_IndLength + strlen( pDoc->m_UserVars.m_strTail ); // 8;
		if ( !pDoc->m_UserVars.m_LocAfterSeq ) m_GVETailLength = 0;


		if ( pDoc->m_UserVars.m_LocAfterName && pDoc->m_UserVars.m_ShowTail) {
			m_GVELeadLength += 1 + strlen( pDoc->m_UserVars.m_strTail );
		}
	}

	if ( pDoc->m_UserVars.m_WidthMode == 1 ) {
		MaxX = 
			m_CharWidth * 
			(pDoc->m_UserVars.m_FixedXSize + (m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + (m_GVELeadLength) );
	} else if ( pDoc->m_UserVars.m_WidthMode == 2 ) {
		MaxX = 
			m_CharWidth * 
			( ((CGeneSegment*)pDoc->pGSFiller->SegDataList.GetHead())->GetTextLength() + (m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + (m_GVELeadLength) );
	}
	
	// Test for minimum of XSize = 10 residues + lead and tail.
	if ( MaxX < (UINT)((((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength) * m_CharWidth) + 100) ) {
		MaxX = (((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength) * m_CharWidth ) + 100;
	}
	
	m_TotalWidth = 0;
	m_TotalHeight = 0;

	if ( pDoc->pGSFiller != NULL ) {
		// m_Size = CSize (MaxX, 0 );	
		m_TotalWidth = MaxX;
		m_TotalHeight = 0;

	    ResetGPAdd( pDoc->pGSFiller);
	}

	pDC->SelectObject( oBrush );
	pDC->SelectObject( oPen );
	pDC->SelectObject( oFont);

	pDoc->EndWaitCursor(); // Let em know

	return; // m_Size;
}

void
CSummaryView::ResetGPAdd( CGeneSegBase *pGSBase )
{
    CGPSumView* tRowView;
	
	if ( m_RowViewList.GetCount() == 0 ) {
		tRowView = new CGPSumView;
		if ( tRowView == 0 ) {
			AfxMessageBox( "sumview:new:fail:10" );
			return;
		}
		tRowView->SetPosition( 0, 0 );
		tRowView->SetSize( 0, 0 );
		// The the object internal starting position
		// Make it 10 chars.
		tRowView->m_IntXPos = m_GVELeadLength * m_CharWidth;
		tRowView->m_IntYPos = (DWORD)(0);
		m_RowVEnum = 1;
		tRowView->SetEnum( m_RowVEnum++ );
		
		// Used to be set inital cursor position here.
		// 		// Copy this to the Caret

		UINT XCPos;
		DWORD YCPos;
		m_MyCaret.GetPosition(&XCPos, &YCPos);
		if ( XCPos == UINT_MAX ) {
			m_MyCaret.SetPosition ( tRowView->m_IntXPos, tRowView->m_IntYPos );
		}

		
		tRowView->pGeneViewParent = (CGeneViewBase *)&m_RowViewList;
		
		m_LeaderSaveEnum = m_EnumCount++;
		
		m_RowViewList.AddTail (tRowView );
	}

	BuildRowViews( pGSBase, 0L );


}

void
CSummaryView::BuildRowViews( CGeneSegBase *pGSBase, DWORD StartPos )
{
//	CString *tStr;
	DWORD tnChars;

	// CSize GESize;
	POSITION tPos;

	UINT tWideChars, tiSize;
	CGVSummary* tGE;
    CGPSumView* tRowView;

	if ( m_TotalWidth < (m_CharWidth * 
		((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength)) 
	) return;

	UINT workMaxX = m_TotalWidth 
		- (m_CharWidth * ((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength));

	tnChars = ((CGeneSegment*)pGSBase->SegDataList.GetHead())->GetTextLength() - StartPos;

	do {

		tRowView = (CGPSumView *)m_RowViewList.GetTail();

		// How to allow for scroll bars not being in plane yet?
		UINT tRVXSize;
		DWORD tRVYSize;
		tRowView->GetSize(&tRVXSize, &tRVYSize);
		
		tWideChars = (workMaxX/m_SumWidth) - (tRVXSize/m_SumWidth);

		// Test First Time through?
		if ( tWideChars ==  0 ) {

			// Nope .. Do Head/Tail
			UINT tXPos;
			DWORD tYPos;
			tRowView->GetPosition(&tXPos, &tYPos );
			UINT tXSize;
			DWORD tYSize;
			tRowView->GetSize(&tXSize, &tYSize);

			tYPos += tYSize;
			m_TotalHeight += tYSize;

			if ( GetDocument()->m_UserVars.m_ShowTail ) {
				// Add Head and tail objects
				CGVSummary* tGEt = (CGVSummary*)tRowView->ViewDataList.GetTail();
	    	    CGVSummary* tGEh = (CGVSummary*)tRowView->ViewDataList.GetHead();
				AddHeadTail ( tGEt, tGEh, tRowView );
			} else {
				// Add Head object
	    	    CGVSummary* tGEh = (CGVSummary*)tRowView->ViewDataList.GetHead();
				AddHead ( tGEh, tRowView );
			}
			// Done adding Edit Row Leader

			tRowView = new CGPSumView;
			if ( tRowView == 0 ) {
				AfxMessageBox( "sumview:new:fail:11" );
				return;
			}

			tRowView->SetPosition( 0, tYPos );
			tRowView->SetSize( 0, 0 );

			tRowView->m_IntXPos = m_CharWidth * m_GVELeadLength;
			tRowView->m_IntYPos = tYPos;
			tRowView->SetEnum( m_RowVEnum++ );
			tRowView->pGeneViewParent = (CGeneViewBase *)&m_RowViewList;

			m_RowViewList.AddTail (tRowView );

			m_LeaderSaveEnum = m_EnumCount++;

			// Add in some or all of pGSBase

			tWideChars = (workMaxX / m_SumWidth);
		}


		// Check for partial segment
		if ( tnChars > tWideChars ) {
			// loop and fill out trowview's

			tiSize = tWideChars;

			tGE = new CGVSummary();
			if ( tGE == 0 ) {
				AfxMessageBox( "sumview:new:fail:12" );
				return;
			}

			tGE->SetDataParams( pGSBase, StartPos );

			tPos = pGSBase->SegDataList.GetHeadPosition();
			int tc = 0;
			while ( tPos != NULL ) {
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSBase->SegDataList.GetNext(tPos);
				HANDLE hSeg = tCGSeg->MidText( StartPos, tiSize );
				GeneStor *tStr = (GeneStor *)GlobalLock(hSeg);
				if ( tStr == NULL ) {
					AfxMessageBox("BuildRowViews:GlobalLock:Fail:1" );
					return;
				}

				CGeneString *tGString = new CGeneString;
				if ( tGString == 0 ) {
					AfxMessageBox( "sumview:new:fail:14" );
					return;
				}

				if ( !tGString->SetString( tStr, tiSize, StartPos, tCGSeg, tc++ ) ) {
					return;
				}

				tGE->AddData ( tGString );
				GlobalUnlock(hSeg);
				GlobalFree(hSeg);
			}

			tGE->SetPosition ( tRowView->m_IntXPos, tRowView->m_IntYPos );
			tGE->pGeneViewParent = tRowView;
			tGE->SetEnum(m_EnumCount++);

			tGE->m_CharWidth = m_CharWidth;
			tGE->m_LineHeight = m_LineHeight;
			
			UINT tXSize;
			DWORD tYSize;
			tGE->CalcDrawSize( m_pDC, &tXSize, &tYSize, m_SumWidth );

			tRowView->m_IntXPos += tXSize;
		
			tRowView->AddTail( tGE );

			tnChars -= tiSize;
			StartPos += tiSize;
			
			
		} else {

			tGE = new CGVSummary();
			if ( tGE == 0 ) {
				AfxMessageBox( "sumview:new:fail:15" );
				return;
			}

			tGE->SetDataParams( pGSBase, StartPos );
			
			tPos = pGSBase->SegDataList.GetHeadPosition();
			int tc = 0;
			while ( tPos != NULL ) {
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSBase->SegDataList.GetNext(tPos);
				tiSize = (int)(tCGSeg->GetTextLength() - StartPos);
				HANDLE hSeg = tCGSeg->MidText( StartPos, tiSize );
				GeneStor *tStr = (GeneStor *)GlobalLock(hSeg);
				if ( tStr == NULL ) {
					AfxMessageBox("BuildRowViews:GlobalLock:Fail:2" );
					return;
				}

				CGeneString *tGString = new CGeneString;
				if ( tGString == 0 ) {
					AfxMessageBox( "sumview:new:fail:17" );
					return;
				}

				if ( !tGString->SetString( tStr, tiSize, StartPos, tCGSeg, tc++ ) ) {
					return;
				}

				tGE->AddData ( tGString );
				GlobalUnlock(hSeg);
				GlobalFree(hSeg);
			}

			tGE->SetPosition ( tRowView->m_IntXPos, tRowView->m_IntYPos );
			tGE->pGeneViewParent = tRowView;
			tGE->SetEnum(m_EnumCount++);

			tGE->m_CharWidth = m_CharWidth;
			tGE->m_LineHeight = m_LineHeight;

			UINT tXSize;
			DWORD tYSize;
			tGE->CalcDrawSize( m_pDC, &tXSize, &tYSize, m_SumWidth );

			tRowView->m_IntXPos += tXSize;

			tRowView->AddTail( tGE );

			tnChars = 0;
		}

//		PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE );		// Yield to other apps.
	} while ( tnChars != 0 );

	// clean up.
	tRowView = (CGPSumView *)m_RowViewList.GetTail();
	UINT tXSize;
	DWORD tYSize;
	tRowView->GetSize( &tXSize, &tYSize );
//	m_TotalHeight += tYSize + m_LineHeight;
	m_TotalHeight += tYSize;

	CGeneViewBase* tGVB = (CGeneViewBase*)tRowView->ViewDataList.GetHead();

	if ( !tGVB->IsKindOf( RUNTIME_CLASS(CGVEditLead) ) ) {

		if ( GetDocument()->m_UserVars.m_ShowTail ) {
			CGVSummary* tGEt = (CGVSummary*)tRowView->ViewDataList.GetTail();
	        CGVSummary* tGEh = (CGVSummary*)tGVB;
			AddHeadTail( tGEt, tGEh, tRowView );
		} else {
			// Add Head object
	        CGVSummary* tGEh = (CGVSummary*)tGVB;
			AddHead ( tGEh, tRowView );
		}
	}

	
	// Test for create CGVEditFill
	tRowView = (CGPSumView *)m_RowViewList.GetTail();
	tRowView->GetSize( &tXSize, &tYSize );


	UINT tWidth;
	if ( GetDocument()->m_UserVars.m_WidthMode == 1 ) {
		tWidth = m_CharWidth * 
			( GetDocument()->m_UserVars.m_FixedXSize 
			+ (m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) 
			+ m_GVELeadLength );
	} else if ( GetDocument()->m_UserVars.m_WidthMode == 2 ) {
		tWidth = m_CharWidth * 
			( ((CGeneSegment*)GetDocument()->pGSFiller->SegDataList.GetHead())->GetTextLength() 
			+ (m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) 
			+ m_GVELeadLength );
	} else {
		tWidth = m_TotalWidth;
	}

	
	if ( tXSize < tWidth ) {
		
		CGVEditFill* tGEF = new CGVEditFill();
		if ( tGEF == 0 ) {
			AfxMessageBox( "sumview:new:fail:27" );
			return;
		}
	
		UINT tXPos;
		DWORD tYPos;
		tRowView->GetPosition( &tXPos, &tYPos );
		tGEF->SetPosition ( tXSize, tYPos );
		tGEF->SetSize ( tWidth - tXSize, tYSize );
		tGEF->pGeneViewParent = tRowView;

		tRowView->AddTail(tGEF );
	}


}


//
//
//   UPDATE
//

void CSummaryView::OnUpdate ( CView* pSender, LPARAM lHint, CObject *pHint )
{
	if ( !m_InitialUpdateDone ) return;

	SetScrollVariables();
	
	SetScrollBars();

	CView::OnUpdate( pSender, lHint, pHint );

}


void 
CSummaryView::SetScrollVariables()
{

	// Get Display rect Sizes
	CDC*pDC = GetDC();
	
	CRect ClientRect;
	
	GetClientRect(ClientRect);
	
	m_DisplayHeight = ClientRect.BottomRight().y;
	m_DisplayWidth = ClientRect.BottomRight().x;

	ReleaseDC(pDC);
	
//
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CDC* tDC = GetDC();

	if ( pDoc->m_UserVars.m_WidthMode >= 1) {
		ResetGPSize( tDC, UINT_MAX );
	} else {

		ResetGPSize( tDC, m_DisplayWidth );
	}
	
	ReleaseDC(tDC);


    if ( m_RowViewList.GetCount() ) {
		
		m_PageScrollHeight = m_TotalHeight;

		// This not very good calc ....
		m_PageScrollHeight = m_PageScrollHeight / m_RowViewList.GetCount();
		m_PageScrollHeight = m_PageScrollHeight / m_LineHeight;
		m_PageScrollHeight = m_PageScrollHeight * m_LineHeight;
	
		m_PageScrollWidth = m_DisplayWidth / 2;


		m_MyCaret.SetMaximums ( m_TotalWidth, m_TotalHeight );
		m_MyCaret.SetIncrements( 
			m_SumWidth, 
			m_LineHeight, 
			8 * m_SumWidth, 
			m_PageScrollHeight
		);

	}


//	init local vars .... this stuf was lower ...
	m_SelectDevice = NONE;
	m_CopyFlag = 0;
	m_ColSelBegin = 0;
	m_ColSelStart = 0;
	m_ColSelEnd = 0;

//



	// This should do caret stuff
	// Having these here messes up the stat/scor/info view when switch to it form here.
	// Only if we are the active view CWinApp

	UINT CaretXPos = 0;
	DWORD CaretYPos = 0;

	m_MyCaret.GetPosition(&CaretXPos, &CaretYPos);
	if ( CaretXPos == UINT_MAX ) CaretXPos = 10;


	CaretYPos /= m_LineHeight;
	CaretYPos *= m_LineHeight;

//	CaretXPos /= m_SumWidth;
//	CaretXPos *= m_SumWidth;
		
	m_MyCaret.SetPosition ( CaretXPos, CaretYPos );
		
	m_MyCaret.SetHeight( m_LineHeight );

	m_MyCaret.SetScrollPos( m_DisplayXPosition, m_DisplayYPosition );

	m_MyCaret.CaretPos();

	if ( ((CMainFrame *)AfxGetApp()->m_pMainWnd)->MDIGetActive() == GetParentFrame() ) {

		DestroyCaret();
		RebuildShowCaret();
	}

	// A Check for resize ..
	if ( (m_DisplayYPosition + m_DisplayHeight) > m_TotalHeight )
		if ( m_TotalHeight > m_DisplayHeight )
			m_DisplayYPosition = m_TotalHeight - m_DisplayHeight;
		else 
			m_DisplayYPosition = 0;
	
	if ( (m_DisplayXPosition + m_DisplayWidth) > m_TotalWidth )
		if ( m_TotalWidth > m_DisplayWidth )
			m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
		else 
			m_DisplayXPosition = 0;


}
	

void 
CSummaryView::SetScrollBars()
{

	if ( m_TotalHeight > m_DisplayHeight ) {
		ShowScrollBar(SB_VERT );

		if ( m_TotalHeight > 10000 ) {
			m_ScrollBarRange = 10000;
		} else {
			m_ScrollBarRange = (UINT)(m_TotalHeight - m_DisplayHeight);
		}
		SetScrollRange( SB_VERT, 0, m_ScrollBarRange, FALSE );
		double Mult = (double)m_ScrollBarRange / (double)(m_TotalHeight - m_DisplayHeight);
		UINT ScrollBarPosition = (UINT)((double)m_DisplayYPosition * Mult);
		SetScrollPos(SB_VERT, ScrollBarPosition);
	} else {
		ShowScrollBar(SB_VERT, FALSE );
	}

	if ( m_TotalWidth > m_DisplayWidth ) {
		ShowScrollBar(SB_HORZ);
		SetScrollRange( SB_HORZ, 0, m_TotalWidth - m_DisplayWidth, FALSE );
		SetScrollPos(SB_HORZ, m_DisplayXPosition );
	} else {
		ShowScrollBar(SB_HORZ, FALSE );
	}


}


void CSummaryView::OnInitialUpdate()
{

	m_DisplayXPosition = 0;
	m_DisplayYPosition = 0;


	CView::OnInitialUpdate();

	ClearMenu();

	m_InitialUpdateDone = TRUE;
	

	m_SelectDevice = NONE;
	m_CopyFlag = 0;

	((CMDIChildWnd *)GetParentFrame())->MDIMaximize();


}

void CSummaryView::OnDraw(CDC* pDC)
{
	// A repaint comes before end of printing.
	if ( m_PrintOnly )
		if ( !pDC->IsPrinting() )
			return;

	DoDraw(pDC, TRUE, FALSE);

}

void CSummaryView::DoDraw(CDC* pDC, int InvFlag1, int InvFlag2 )
{

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// This is a special case for if OnDraw gets called and there is no data.
	// this could happen if you delete all the sequences.
	if ( pDoc->pGSFiller == NULL ) {
		return;
	}

	// TODO: add draw code for native data here
	CFont	NormFont;			// This is selected for you.

	LOGFONT tLOGFONT;
	memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

	strcpy ( tLOGFONT.lfFaceName, "Courier New" );
	tLOGFONT.lfWeight = pDoc->m_UserVars.m_FontWeight;
	tLOGFONT.lfHeight = -MulDiv( pDoc->m_UserVars.m_FontSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);

	// Normal Font
	if ( !NormFont.CreateFontIndirect( &tLOGFONT ) ) {
		AfxMessageBox("sumview:CreateFont:Fail:1");
		return;
	}

	CFont *oFont = (CFont*)pDC->SelectObject( &NormFont);
	CPen *oPen = (CPen*)pDC->SelectStockObject( BLACK_PEN );
	CBrush *oBrush = (CBrush *)pDC->SelectStockObject( BLACK_BRUSH );

	// init a Draw Struct
	DrawStruct DrawStc;
	DrawStc.pDC = pDC;

	DrawStc.pView = this;


	DrawStc.DisplayYPosition = m_DisplayYPosition;
	DrawStc.DisplayHeight = m_DisplayHeight;
	DrawStc.DisplayXPosition = m_DisplayXPosition;
	DrawStc.DisplayWidth = m_DisplayWidth;

	DrawStc.ReDrawTop = m_DisplayYPosition;
	DrawStc.ReDrawBottom = m_DisplayYPosition + m_DisplayHeight;
	DrawStc.ReDrawLeft = m_DisplayXPosition;
	DrawStc.ReDrawRight = m_DisplayXPosition + m_DisplayWidth;

	DrawStc.PrintYOffset = 0;


	if ( !pDC->IsPrinting() && InvFlag1 ) {
		CRect rectClip;
	
		int Type = pDC->GetClipBox(&rectClip);

		if ( Type == SIMPLEREGION ) {
			DrawStc.ReDrawTop = m_DisplayYPosition + rectClip.TopLeft().y;
			DrawStc.ReDrawBottom = m_DisplayYPosition + rectClip.BottomRight().y;
			DrawStc.ReDrawLeft = m_DisplayXPosition + rectClip.TopLeft().x;
			DrawStc.ReDrawRight = m_DisplayXPosition + rectClip.BottomRight().x;
		}
	} else {

		DrawStc.PrintYOffset = m_PrintYOffSet;
	}

	DrawStc.ColSelStart = m_ColSelStart;
	DrawStc.ColSelEnd = m_ColSelEnd;
	DrawStc.MenuFunc = GetMenuFunction();
	DrawStc.ColSelBegin = m_ColSelBegin;
	
	// Set Draw Struct Brushes

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGeneViewBase *tGP;

	DWORD CurrentDisplayLoc = 0;
	UINT CurrentBlockXSize;
	DWORD CurrentBlockYSize;

	
	while ( tPos != NULL ) {
		tGP = (CGeneViewBase *)m_RowViewList.GetNext(tPos);
		// CRect rowRect = tGP->GetViewRect();
		tGP->GetSize( &CurrentBlockXSize, &CurrentBlockYSize );

		if ( (CurrentDisplayLoc + CurrentBlockYSize) > DrawStc.ReDrawTop 
			&& CurrentDisplayLoc <= DrawStc.ReDrawBottom
		) {

			tGP->OnDraw(&DrawStc);

			if ( (!pDC->IsPrinting() && InvFlag1) || InvFlag2 ) {
				if ( tGP->IsSelected() || InvFlag2 ) {
					UINT tXP, tXS;
					DWORD tYP, tYS;
					tGP->GetPosition(&tXP, &tYP );
					tGP->GetSize(&tXS, &tYS );
					CRect rowRect( 
						tXP - m_DisplayXPosition, 
						(int)(tYP - m_DisplayYPosition), 
						tXP + tXS - m_DisplayXPosition, 
						(int)(tYP + tYS - m_DisplayYPosition)
					);
					pDC->InvertRect( rowRect);
				}
			}

		}
		 
		CurrentDisplayLoc += CurrentBlockYSize;
		
	}

	pDC->SelectObject( oBrush );
	pDC->SelectObject( oPen );
	pDC->SelectObject( oFont);

}


void CSummaryView::OnSize(UINT nType, int cx, int cy) 
{
	if ( m_InitialUpdateDone ) {

		m_MyCaret.SetViewSize ( (UINT)cx, (DWORD)cy );
			
		OnUpdate( NULL, 0L, NULL );
		
	}

	CView::OnSize(nType, cx, cy);
}


/////////////////////////////////////////////////////////////////////////////
// CSummaryView printing

  
void CSummaryView::OnPrint( CDC *pDC, CPrintInfo *pInfo )
{
	// Print headers and/or footers, if desired.
	// Find portion of document corresponding to pInfo->m_nCurPage.
	// Count pages.


	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_UserVars.m_PrintStringFlag != 0 || pDoc->m_UserVars.m_PrintPageNumber != 0) {

		CFont *oFont = NULL;
		CFont NormFont;
		LOGFONT tLOGFONT;
		memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

		strcpy ( tLOGFONT.lfFaceName, pDoc->m_UserVars.m_PrintFontName );
		tLOGFONT.lfWeight = pDoc->m_UserVars.m_PrintFontWeight;
		tLOGFONT.lfHeight = -MulDiv( pDoc->m_UserVars.m_PrintFontSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);

		// Normal Font
		if ( NormFont.CreateFontIndirect( &tLOGFONT ) ) {
			oFont = (CFont*)pDC->SelectObject( &NormFont);
		}

		if ( pDoc->m_UserVars.m_PrintPageNumber == 1 || pDoc->m_UserVars.m_PrintPageNumber == 2 ) {

			char Buff[20];
			sprintf(Buff, "%d", pInfo->m_nCurPage + pDoc->m_UserVars.m_PrintPageOffset );
			CSize sizeHeader = pDC->GetTextExtent(Buff, strlen(Buff));
			int XLoc;
			if ( pDoc->m_UserVars.m_PrintPageNumber == 1 ) {
				// Center
				XLoc = (m_PageWidth - sizeHeader.cx) / 2;
			} else {
				// Right
				XLoc = m_PageWidth - sizeHeader.cx;
			}
			pDC->TextOut( XLoc, 0, Buff, strlen(Buff) );

			m_PrintYOffSet = sizeHeader.cy;

		} else if ( pDoc->m_UserVars.m_PrintStringFlag == 1 ) {
			CSize sizeHeader = pDC->GetTextExtent(
				(const char *)pDoc->m_UserVars.m_PrintString, 
				pDoc->m_UserVars.m_PrintString.GetLength() 
			);
			int XCenter = (m_PageWidth - sizeHeader.cx) / 2;

			pDC->TextOut( XCenter, 0, pDoc->m_UserVars.m_PrintString );

			m_PrintYOffSet = sizeHeader.cy;
		}

		if ( oFont != NULL ) {
			pDC->SelectObject( oFont );
		}
	}

	
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGeneViewBase *tGP;

//	DWORD Page = 1;
	DWORD Page = 0;
	DWORD tPageAmount = 0;

	if ( m_PartialPrintFlag ) {
	
		tGP = (CGeneViewBase *)m_RowViewList.GetHead();

		UINT Nothing;
		DWORD tPageTop;
		tGP->GetPosition(&Nothing, &tPageTop);
		DWORD tPageBottom = tPageTop + m_PageHeight;
		DWORD oPageTop = tPageTop;

		// Count pages. 
		// Set Position
		POSITION tPos = m_RowViewList.GetHeadPosition();
		// Get first Row
		while ( tPos != NULL ) {
			tGP = (CGeneViewBase *)m_RowViewList.GetNext(tPos);
			while ( !tGP->GetPartialPageSize(tPageTop, tPageBottom, &tPageAmount) ) {
				Page++;
				if ( pInfo->m_nCurPage == Page ) {
					break;
				}
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				tPageAmount = 0;
			} 
			if ( pInfo->m_nCurPage == Page ) {
				break;
			}
			// Print Blocks at top of page?
			if ( pDoc->m_UserVars.m_PrintGeneBlock != 0 ) {
				Page++;
				if ( pInfo->m_nCurPage == Page ) {
					break;
				}
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				tPageAmount = 0;
			} else {
				tPageTop += tPageAmount;
			}
		}

		m_TopPage = oPageTop;
	
	} else {

		tGP = (CGeneViewBase *)m_RowViewList.GetHead();
		UINT Nothing;
		DWORD tPageTop;
		tGP->GetPosition(&Nothing, &tPageTop);

		DWORD tPageBottom = tPageTop + m_PageHeight;
		DWORD oPageTop = tPageTop;
		// Count pages. 
		// Set Position
		POSITION tPos = m_RowViewList.GetHeadPosition();
		// Get first Row
		while ( tPos != NULL ) {
			UINT tXSize;
			DWORD tYSize;
			tGP = (CGeneViewBase *)m_RowViewList.GetNext(tPos);
			tGP->GetSize(&tXSize, &tYSize);
			tPageTop += tYSize;
			// Print One Block per Page?
			if ( pDoc->m_UserVars.m_PrintGeneBlock == 1 ) {
				// Go Ahead and increment page count
				Page++;
				if ( pInfo->m_nCurPage == Page ) {
					tPageTop = oPageTop;
					tPageAmount = tYSize;
					break;
				}
				tPageTop = oPageTop = oPageTop + tYSize;
			} else if ( tPageTop > tPageBottom ) {
				Page++;
				if ( pInfo->m_nCurPage == Page ) {
					tPageTop = oPageTop;
					break;
				}
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				tPageAmount = 0;
				tPageTop += tYSize;
			} 
			tPageAmount += tYSize;
		}
		
		m_TopPage = oPageTop;
	
	}

	m_BottomPage = m_TopPage + m_PageHeight;

	m_DisplayXPosition = 0;
	m_DisplayYPosition = m_TopPage;
	m_DisplayHeight = tPageAmount;
	m_DisplayWidth = m_PageWidth;


	OnDraw( pDC );

	if ( pDoc->m_UserVars.m_PrintStringFlag != 0 || pDoc->m_UserVars.m_PrintPageNumber != 0) {

		CFont *oFont = NULL;
		CFont NormFont;
		LOGFONT tLOGFONT;
		memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

		strcpy ( tLOGFONT.lfFaceName, pDoc->m_UserVars.m_PrintFontName );
		tLOGFONT.lfWeight = pDoc->m_UserVars.m_PrintFontWeight;
		tLOGFONT.lfHeight = -MulDiv( pDoc->m_UserVars.m_PrintFontSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);

		// Normal Font
		if ( NormFont.CreateFontIndirect( &tLOGFONT ) ) {
			oFont = (CFont*)pDC->SelectObject( &NormFont);
		}

		if ( pDoc->m_UserVars.m_PrintPageNumber == 3 || pDoc->m_UserVars.m_PrintPageNumber == 4 ) {

			char Buff[20];
			sprintf(Buff, "%d", pInfo->m_nCurPage + pDoc->m_UserVars.m_PrintPageOffset );
			CSize sizeHeader = pDC->GetTextExtent(Buff, strlen(Buff));
			int XLoc;
			if ( pDoc->m_UserVars.m_PrintPageNumber == 3 ) {
				// Center
				XLoc = (m_PageWidth - sizeHeader.cx) / 2;
			} else {
				// Right
				XLoc = m_PageWidth - sizeHeader.cx;
			}
			pDC->TextOut( XLoc, (int)m_PageHeight + sizeHeader.cy, Buff, strlen(Buff) );


		} else if ( pDoc->m_UserVars.m_PrintStringFlag == 2 ) {
			CSize sizeHeader = pDC->GetTextExtent(
				(const char *)pDoc->m_UserVars.m_PrintString, 
				pDoc->m_UserVars.m_PrintString.GetLength() );
			int XCenter = (m_PageWidth - sizeHeader.cx) / 2;

			pDC->TextOut( XCenter, (int)m_PageHeight + sizeHeader.cy, pDoc->m_UserVars.m_PrintString );

		}

		if ( oFont != NULL ) {
			pDC->SelectObject( oFont );
		}

	}

}

void 
CSummaryView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{

	CView::OnPrepareDC ( pDC, pInfo );

	if ( pInfo != NULL ) {

		pDC->SetViewportOrg( m_LeftView, m_TopView );
	
	}

}


BOOL CSummaryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void 
CSummaryView::CalculateMargins(CDC* pDC)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POINT pt;

	// Start by getting the dimensions of the unprintable part of the
	// page (in device units). GETPRINTINGOFFSET will tell us the left
	// and upper unprintable area.

	pDC->Escape(GETPRINTINGOFFSET, 0, NULL, &pt);
	m_rectMargins.left = pt.x;
	m_rectMargins.top  = pt.y;

	// To get the right and lower unprintable area, we need to take
	// the entire width and height of the paper (GETPHYSPAGESIZE) and
	// subtract everything else.

	pDC->Escape(GETPHYSPAGESIZE, 0, NULL, &pt);

	m_rectMargins.right  = pt.x                     // total paper width
						  - pDC->GetDeviceCaps(HORZRES) // printable width
						  - m_rectMargins.left;   // left unprtable margin

	m_rectMargins.bottom = pt.y                     // total paper height
						  - pDC->GetDeviceCaps(VERTRES) // printable ht
						  - m_rectMargins.top;    // rt unprtable margin

	// At this point, m_rectMargins contains the widths of the
	// unprintable regions on all four sides of the page in device units.

	// subtract the unprintable part we just calculated. 
	// Save the results back in m_rectMargins.

	pt.x = pDC->GetDeviceCaps(LOGPIXELSX);    // dpi in X direction
	pt.y = pDC->GetDeviceCaps(LOGPIXELSY);    // dpi in Y direction

	m_rectMargins.left = ((int)(pDoc->m_UserVars.m_LeftBorder * (double)pt.x)) 
		- m_rectMargins.left;
	m_rectMargins.top = ((int)(pDoc->m_UserVars.m_TopBorder * (double)pt.y)) 
		- m_rectMargins.top;
	m_rectMargins.right = ((int)(pDoc->m_UserVars.m_RightBorder * (double)pt.x)) 
		- m_rectMargins.right;
	m_rectMargins.bottom = ((int)(pDoc->m_UserVars.m_BottomBorder * (double)pt.y)) 
		- m_rectMargins.bottom;

	// m_rectMargins now contains the values used to shrink the printable
	// area of the page. Could check m_rectMargins here for negative values
	// to prevent setting margins outside the printable area of the page.

	// Convert to logical units and we're done!
	// pDC->DPtoLP(m_rectMargins);
}
 

void CSummaryView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_SaveDisplayXPosition = m_DisplayXPosition;
	m_SaveDisplayYPosition = m_DisplayYPosition;

    CView::OnBeginPrinting(pDC, pInfo);

	CalculateMargins(pDC);

	// TODO: add extra initialization before printing
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int res = pDC->GetDeviceCaps( HORZRES );
	m_PageWidth = (UINT)(res - (m_rectMargins.left + m_rectMargins.right));

	res = pDC->GetDeviceCaps( VERTRES );
	m_PageHeight = (UINT)(res - (m_rectMargins.top + m_rectMargins.bottom));

	m_PrintYOffSet = 0;

	if ( pDoc->m_UserVars.m_PrintStringFlag != 0 || pDoc->m_UserVars.m_PrintPageNumber != 0) {

		CFont NormFont;
		CFont *oFont = NULL;
		LOGFONT tLOGFONT;
		memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

		strcpy ( tLOGFONT.lfFaceName, pDoc->m_UserVars.m_PrintFontName );
		tLOGFONT.lfWeight = pDoc->m_UserVars.m_PrintFontWeight;
		tLOGFONT.lfHeight = -MulDiv( pDoc->m_UserVars.m_PrintFontSize , pDC->GetDeviceCaps(LOGPIXELSY), 72);

		// Normal Font
		if ( NormFont.CreateFontIndirect( &tLOGFONT ) ) {
			oFont = (CFont*)pDC->SelectObject( &NormFont);
		}
		CSize sizeHeader = pDC->GetTextExtent("X", 1);

		if ( pDoc->m_UserVars.m_PrintPageNumber == 1 
			|| pDoc->m_UserVars.m_PrintPageNumber == 2 
			|| pDoc->m_UserVars.m_PrintStringFlag == 1 
		) {
			m_PageHeight -= sizeHeader.cy;
		}

		// and for footer
		if ( pDoc->m_UserVars.m_PrintPageNumber == 3 
			|| pDoc->m_UserVars.m_PrintPageNumber == 4 
			|| pDoc->m_UserVars.m_PrintStringFlag == 2 
		) {
			m_PageHeight -= sizeHeader.cy;
		}

		if ( oFont != NULL ) {
			pDC->SelectObject( oFont );
		}
	
	}

	m_LeftView = (UINT)m_rectMargins.left;
	m_TopView = (UINT)m_rectMargins.top;

// Do the Resize
	
	ResetGPSize( pDC, m_PageWidth );
	UINT tXSize;
	DWORD tYSize;
    //

	CGeneViewBase *tGP;
	int Pages;
	if ( pDoc->m_UserVars.m_PrintGeneBlock == 1 ) {
		Pages = 0;
	} else {
		Pages = 1;
	}

	DWORD tPageAmount = 0;
	
	// Lets check for partial Rows on Pages First off
	tGP = (CGeneViewBase *)m_RowViewList.GetHead();
	tGP->GetSize(&tXSize, &tYSize);
	if ( tYSize > m_PageHeight ) {
		// Yup Partial rows on Pages ..
		m_PartialPrintFlag = 1;
		UINT Nothing;
		DWORD tPageTop;
		tGP->GetPosition(&Nothing, &tPageTop);
		DWORD tPageBottom = tPageTop + m_PageHeight;
		DWORD oPageTop = tPageTop;

		// Count pages. 
		// Set Position
		POSITION tPos = m_RowViewList.GetHeadPosition();

		while ( tPos != NULL ) {
			tGP = (CGeneViewBase *)m_RowViewList.GetNext(tPos);
			while ( !tGP->GetPartialPageSize(tPageTop, tPageBottom, &tPageAmount) ) {
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				Pages++;
				tPageAmount = 0;
			} 
			// Print Blocks at top of page?
			if ( pDoc->m_UserVars.m_PrintGeneBlock != 0 ) {
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				Pages++;
				tPageAmount = 0;
			} else {
				tPageTop += tPageAmount;
			}
		}

	} else {
		m_PartialPrintFlag = 0;

		UINT Nothing;
		DWORD tPageTop;
		tGP->GetPosition(&Nothing, &tPageTop);
		DWORD tPageBottom = tPageTop + m_PageHeight;
		DWORD oPageTop = tPageTop;
		// Count pages. 
		// Set Position
		POSITION tPos = m_RowViewList.GetHeadPosition();
		// Special Case
		if ( pDoc->m_UserVars.m_PrintGeneBlock == 1 ) {
			Pages = 0;
		}
		while ( tPos != NULL ) {
			tGP = (CGeneViewBase *)m_RowViewList.GetNext(tPos);
			tGP->GetSize(&tXSize, &tYSize);
			tPageTop += tYSize;
			// Print One Block per Page?
			if ( pDoc->m_UserVars.m_PrintGeneBlock == 1 ) {
				// Go Ahead and increment page count
				Pages++;
			} else if ( tPageTop > tPageBottom ) {
				tPageTop = oPageTop = oPageTop + tPageAmount;
				tPageBottom = tPageTop + m_PageHeight;
				// Go Ahead and increment page count
				Pages++;
				tPageAmount = 0;
				tPageTop += tYSize;
			} 
			tPageAmount += tYSize;
		}
	}
	pInfo->SetMaxPage ( Pages );
}


void CSummaryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo */)
{
	m_DisplayXPosition = m_SaveDisplayXPosition;
	m_DisplayYPosition = m_SaveDisplayYPosition;
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSummaryView diagnostics

#ifdef _DEBUG
void CSummaryView::AssertValid() const
{
	CView::AssertValid();
}

void CSummaryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGenedocDoc* CSummaryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	return (CGenedocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSummaryView message handlers

	

void CSummaryView::OnDestroy() 
{
	CleanRowViewList();

	CView::OnDestroy();

}

int CSummaryView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_pSummaryView = this;

	m_InitialUpdateDone = FALSE;
	
	return 0;
}


void CSummaryView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	DestroyCaret();
	// TODO: Add your message handler code here
}

void CSummaryView::OnSetFocus(CWnd* pOldWnd) 
{

	CView::OnSetFocus(pOldWnd);
	
	if ( !m_PrintOnly ) {

		m_MyCaret.SetScrollPos( m_DisplayXPosition, m_DisplayYPosition );
		m_MyCaret.SetHeight( m_LineHeight );

		RebuildShowCaret();
	}
	
	// TODO: Add your message handler code here
	
}

void
CSummaryView::RebuildShowCaret()
{

	CreateSolidCaret( m_SumWidth, (int)m_LineHeight );

	ShowCaret();

	m_MyCaret.CaretPos();
}


void CSummaryView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_MyCaret.OnKeyDown ( nChar, nRepCnt, nFlags, this);
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSummaryView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_MyCaret.OnKeyUp ( nChar, nRepCnt, nFlags, this);
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void 
CSummaryView::InvalidateRectLP(UINT tXPosition, DWORD tYPosition, UINT tXSize, DWORD tYSize )
{
	CRect InvRect( 
		tXPosition - m_DisplayXPosition, (int)(tYPosition - m_DisplayYPosition), 
		tXPosition + tXSize - m_DisplayXPosition, (int)(tYPosition + tYSize - m_DisplayYPosition)
	);
	InvalidateRect( InvRect, FALSE );

}

void 
CSummaryView::InvalidateGVBLP( CGeneViewBase *pGVB )
{
	UINT tXPosition;
	DWORD tYPosition;
	UINT tXSize;
	DWORD tYSize;

	pGVB->GetPosition(&tXPosition, &tYPosition);
	pGVB->GetSize(&tXSize, &tYSize);

	CRect InvRect( 
		tXPosition - m_DisplayXPosition, (int)(tYPosition - m_DisplayYPosition), 
		tXPosition + tXSize - m_DisplayXPosition, (int)(tYPosition + tYSize - m_DisplayYPosition)
	);
	InvalidateRect( InvRect, FALSE );

}

BOOL CSummaryView::IsVisible( UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize )
{
	if ( (YPosition+YSize)>=m_DisplayYPosition && YPosition<=(m_DisplayYPosition+m_DisplayHeight) ) {
		if ( (XPosition+XSize)>=m_DisplayXPosition && XPosition<=(m_DisplayXPosition+m_DisplayWidth) ) {
			return TRUE;
		}
	}
	return FALSE;
}


void 
CSummaryView::DeSelectAll()
{
	if ( m_GeneSelect == 1 ) {
		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPSumView* tGP;
	
		CClientDC dc(this);
		OnPrepareDC(&dc);
	
		while ( tPos != NULL ) {
			tGP = (CGPSumView* )m_RowViewList.GetNext(tPos);
			if ( tGP->IsSelected() ) {
				tGP->DeSelect();

				InvalidateGVBLP( tGP );
			}
		}
	} else if ( m_GeneSelectCol == 1 ) {
		InvalNewEndPoint( m_ColSelStart, m_ColSelEnd);
		m_ColSelBegin = 0;
	}

	m_CopyFlag = 0;
}



void CSummaryView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	
	DWORD sDisplayYPosition = m_DisplayYPosition;
	
	switch ( nSBCode ) {
	case SB_BOTTOM:
		m_DisplayYPosition = m_TotalHeight - m_DisplayHeight;
		break;
	case SB_TOP:
		m_DisplayYPosition = 0;
		break;
	case SB_ENDSCROLL:
		break;
	case SB_LINEDOWN:
		if ( m_DisplayYPosition + m_LineHeight > m_TotalHeight - m_DisplayHeight) {
			m_DisplayYPosition = m_TotalHeight - m_DisplayHeight;
		} else {
			m_DisplayYPosition += m_LineHeight;
		}
		break;
	case SB_LINEUP:
		if ( m_DisplayYPosition >= m_LineHeight ) {
			m_DisplayYPosition -= m_LineHeight;
		} else {
			m_DisplayYPosition = 0;
		}
		break;
	case SB_PAGEDOWN:
		if ( m_DisplayYPosition + m_PageScrollHeight > m_TotalHeight - m_DisplayHeight ) {
			m_DisplayYPosition = m_TotalHeight - m_DisplayHeight;
		} else {
			m_DisplayYPosition += m_PageScrollHeight;
		}
		break;
	case SB_PAGEUP:
		if ( m_DisplayYPosition >= m_PageScrollHeight )  {
			m_DisplayYPosition -= m_PageScrollHeight;
		} else {
			m_DisplayYPosition = 0;
		}
		break;
	case SB_THUMBPOSITION:
		{
		double Mult = (double)(m_TotalHeight - m_DisplayHeight) / (double)m_ScrollBarRange;
		m_DisplayYPosition = (DWORD)((double)nPos * Mult);
		}
		break;
	case SB_THUMBTRACK:
		{
		double Mult = (double)(m_TotalHeight - m_DisplayHeight) / (double)m_ScrollBarRange;
		m_DisplayYPosition = (DWORD)((double)nPos * Mult);
		}
//		SetScrollPos(SB_VERT, nPos);
		break;	
	}

	if ( m_DisplayYPosition != sDisplayYPosition ) {
		if ( m_DisplayYPosition > sDisplayYPosition ) {
			DWORD Diff = m_DisplayYPosition - sDisplayYPosition;
			if ( Diff > m_DisplayHeight ) {
				Invalidate(FALSE);
			} else {
				ScrollWindowEx( 0, -((int)Diff), NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		} else {
			DWORD Diff = sDisplayYPosition - m_DisplayYPosition;
			if ( Diff > m_DisplayHeight ) {
				Invalidate(FALSE);
			} else {
				ScrollWindowEx( 0, (int)Diff, NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		}
		double Mult = (double)m_ScrollBarRange / (double)(m_TotalHeight - m_DisplayHeight);
		int ScrollBarPosition = (UINT)((double)m_DisplayYPosition * Mult);
		SetScrollPos(SB_VERT, ScrollBarPosition);
	}

	CView::OnVScroll(nSBCode, nPos, pScrollBar);

	m_MyCaret.SetScrollPos( m_DisplayXPosition, m_DisplayYPosition );
	
}

void CSummaryView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	UINT sDisplayXPosition = m_DisplayXPosition;
	
	switch ( nSBCode ) {
	case SB_BOTTOM:
		m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
		break;
	case SB_TOP:
		m_DisplayXPosition = 0;
		break;
	case SB_ENDSCROLL:
		break;
	case SB_LINEDOWN:
		if ( m_DisplayXPosition + 1 > m_TotalWidth - m_DisplayWidth ) 
			m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
		else 
			m_DisplayXPosition += 1;
		break;
	case SB_LINEUP:
		if ( m_DisplayXPosition >= 1 ) 
			m_DisplayXPosition -= 1;
		else 
			m_DisplayXPosition = 0;
		break;
	case SB_PAGEDOWN:
		if ( m_DisplayXPosition + m_PageScrollWidth > m_TotalWidth - m_DisplayWidth ) 
			m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
		else 
			m_DisplayXPosition += m_PageScrollWidth;
		break;
	case SB_PAGEUP:
		if ( m_DisplayXPosition >= m_PageScrollWidth ) 
			m_DisplayXPosition -= m_PageScrollWidth;
		else
			m_DisplayXPosition = 0;
		break;
	case SB_THUMBPOSITION:
		m_DisplayXPosition = nPos;
		break;
	case SB_THUMBTRACK:
		m_DisplayXPosition = nPos;
		// SetScrollPos(SB_HORZ, nPos);
		break;	
	}

	if ( m_DisplayXPosition != sDisplayXPosition ) {
		if ( m_DisplayXPosition > sDisplayXPosition ) {
			DWORD Diff = m_DisplayXPosition - sDisplayXPosition;
			if ( Diff > m_DisplayWidth ) {
				Invalidate( FALSE );
			} else {
				ScrollWindowEx( -((int)Diff), 0, NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		} else {
			DWORD Diff = sDisplayXPosition - m_DisplayXPosition;
			if ( Diff > m_DisplayWidth ) {
				Invalidate( FALSE);
			} else {
				ScrollWindowEx( (int)Diff, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		}
		SetScrollPos(SB_HORZ, m_DisplayXPosition );
	}
	
	CView::OnHScroll(nSBCode, nPos, pScrollBar);

	m_MyCaret.SetScrollPos( m_DisplayXPosition, m_DisplayYPosition );
}



void CSummaryView::ScrollToPosition ( UINT ScrollXPosition, DWORD ScrollYPosition )
{
	
	DWORD sDisplayYPosition = m_DisplayYPosition;
	m_DisplayYPosition = ScrollYPosition;

	if ( m_DisplayYPosition > m_TotalHeight - m_DisplayHeight) {
		m_DisplayYPosition = m_TotalHeight - m_DisplayHeight;
	}

	if ( m_DisplayYPosition != sDisplayYPosition ) {
		if ( m_DisplayYPosition > sDisplayYPosition ) {
			DWORD Diff = m_DisplayYPosition - sDisplayYPosition;
			if ( Diff > m_DisplayHeight ) {
				Invalidate(FALSE);
			} else {
				ScrollWindowEx( 0, -((int)Diff), NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		} else {
			DWORD Diff = sDisplayYPosition - m_DisplayYPosition;
			if ( Diff > m_DisplayHeight ) {
				Invalidate(FALSE);
			} else {
				ScrollWindowEx( 0, (int)Diff, NULL, NULL, NULL, NULL, SW_INVALIDATE );
				UpdateWindow();
			}
		}
		double Mult = (double)m_ScrollBarRange / (double)(m_TotalHeight - m_DisplayHeight);
		int ScrollBarPosition = (UINT)((double)m_DisplayYPosition * Mult);
		SetScrollPos(SB_VERT, ScrollBarPosition);
	}

	UINT sDisplayXPosition = m_DisplayXPosition;
	m_DisplayXPosition = ScrollXPosition;
	
	if ( m_DisplayXPosition > m_TotalWidth - m_DisplayWidth) {
		m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
	}

	if ( m_DisplayXPosition != sDisplayXPosition ) {
		if ( m_DisplayXPosition > sDisplayXPosition ) {
			DWORD Diff = m_DisplayXPosition - sDisplayXPosition;
			if ( Diff > m_DisplayWidth ) {
				Invalidate( FALSE );
			} else {
				ScrollWindowEx( -((int)Diff), 0, NULL, NULL, NULL, NULL, SW_INVALIDATE );
			}
		} else {
			DWORD Diff = sDisplayXPosition - m_DisplayXPosition;
			if ( Diff > m_DisplayWidth ) {
				Invalidate( FALSE);
			} else {
				ScrollWindowEx( (int)Diff, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE );
			}
		}
		SetScrollPos(SB_HORZ, m_DisplayXPosition );
	}
}

void CSummaryView::GetScrollPosition( UINT *ScrollXPosition, DWORD *ScrollYPosition)
{
	*ScrollXPosition = m_DisplayXPosition;
	*ScrollYPosition = m_DisplayYPosition;
}


void 
CSumViewCaret::Select( UINT XPosition, DWORD YPosition, CView* pView )
{

	CSummaryView* pGEView = (CSummaryView*)pView;

	POSITION tPos = pGEView->m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	pGEView->DeSelectAll();

	while ( tPos != NULL ) {

		tGP = (CGPRowView *)pGEView->m_RowViewList.GetNext(tPos);
		if ( tGP->IsPointWithin( XPosition, YPosition ) ) {
			tGP->OnLButtonDblClk(0, XPosition, YPosition, pGEView );
		}
	}

}


int  
CSumViewCaret::Comment( char nChar, UINT XPosition, DWORD YPosition, CView* pView )
{

	CSummaryView* pGEView = (CSummaryView*)pView;

	POSITION tPos = pGEView->m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	pGEView->DeSelectAll();

	while ( tPos != NULL ) {

		tGP = (CGPRowView *)pGEView->m_RowViewList.GetNext(tPos);

		if ( tGP->IsPointWithin(XPosition, YPosition ) ) {
			return tGP->OnComment(nChar, XPosition, YPosition, pGEView );
		}
	}

	return 0;
}

void 
CSumViewCaret::LeftDown( UINT XPosition, DWORD YPosition, CView* pView )
{

	CPoint tPoint ( (int)(XPosition - ((CSummaryView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CSummaryView*)pView)->m_DisplayYPosition));
	((CSummaryView *)pView)->LeftDownFunc( 0, tPoint, CSummaryView::KEYBRD );

}

void 
CSumViewCaret::Move( UINT XPosition, DWORD YPosition, CView* pView )
{
	CPoint tPoint ( (int)(XPosition - ((CSummaryView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CSummaryView*)pView)->m_DisplayYPosition));
	((CSummaryView*)pView)->MoveFunc( 0, tPoint, CSummaryView::KEYBRD );
}

void 
CSumViewCaret::LeftUp( UINT XPosition, DWORD YPosition, CView* pView )
{

	CPoint tPoint ( (int)(XPosition - ((CSummaryView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CSummaryView*)pView)->m_DisplayYPosition));
	((CSummaryView*)pView)->LeftUpFunc( 0, tPoint, CSummaryView::KEYBRD );
}

void CSummaryView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LeftDownFunc ( nFlags, point, MOUSE );

	CView::OnLButtonDown(nFlags, point);
}

void CSummaryView::OnMouseMove(UINT nFlags, CPoint point) 
{
	MoveFunc( nFlags, point, MOUSE);
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}

void CSummaryView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LeftUpFunc(nFlags, point, MOUSE);
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}

void CSummaryView::LeftUpFunc(UINT nFlags, CPoint point, int DDevice) 
{

	if ( (GetCapture() == this) && (m_SelectDevice == DDevice) ) {

		VIEWRETSTRUCT	ViewRet;
		ViewRet.Expanded = 0;
		ViewRet.MenuFunc = GetMenuFunction();
		ViewRet.DDevice = DDevice;

		ViewRet.ColSelStart = m_ColSelStart;
		ViewRet.ColSelEnd = m_ColSelEnd;
		ViewRet.ColSelBegin = m_ColSelBegin;

		UINT PointXPosition;
		DWORD PointYPosition;

		PointXPosition = point.x + m_DisplayXPosition;
		PointYPosition = (DWORD)point.y + m_DisplayYPosition;


		POSITION tPos;

#ifdef _MAC
		if ( !CheckClipCursor( point ) ) goto NoPoint;
#endif

		tPos = m_RowViewList.GetHeadPosition();
		CGPSumView *tGP;
	
		while ( tPos != NULL ) {
			tGP = (CGPSumView *)m_RowViewList.GetNext(tPos);
			if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
				if ( ViewRet.MenuFunc == DEF_GENESELECT ) {
					AdjustEndToPoint( tGP, PointXPosition, PointYPosition, this );
				} else {
					tGP->OnLButtonUp(nFlags, PointXPosition, PointYPosition, this, &ViewRet );

					m_ColSelStart = ViewRet.ColSelStart;
					m_ColSelEnd = ViewRet.ColSelEnd;

				}
				break;
			}
		}


#ifdef _MAC
NoPoint:
#endif
		ReleaseCapture();
//		ClipCursor ( NULL );
//		m_MyCaret.ClipCaret( 0 );
		m_SelectDevice = NONE;
	}
}

void 
CSummaryView::LeftDownFunc( UINT nFlags, CPoint point, int DDevice )
{

	if ( m_SelectDevice != NONE )
		return;


	VIEWRETSTRUCT	ViewRet;
	ViewRet.MenuFunc = GetMenuFunction();
	ViewRet.Expanded = 0;
	ViewRet.DDevice = DDevice;

	ViewRet.ColSelStart = m_ColSelStart;
	ViewRet.ColSelEnd = m_ColSelEnd;
	ViewRet.ColSelBegin = m_ColSelBegin;

	if ( !ViewRet.MenuFunc ) {
		return;
	}

	UINT PointXPosition;
	DWORD PointYPosition;

	PointXPosition = point.x + m_DisplayXPosition;
	PointYPosition = point.y + m_DisplayYPosition;

		
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPSumView *)m_RowViewList.GetNext(tPos);

		if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {

			if ( ViewRet.MenuFunc == DEF_GENESELECT ) {

				if ( (!tGP->IsSelected()) && (m_CopyFlag == 1) ) {
					AdjustEndToPoint( tGP, PointXPosition, PointYPosition, this );
				} else {
					DeSelectAll();
					tGP->Select();
	
					m_StartSelect = tGP->GetEnum();
					m_EndSelect = m_StartSelect;
	
					m_EndPos = m_RowViewList.Find(tGP);
					ASSERT(m_EndPos != NULL );

					InvalidateGVBLP( tGP );

					m_CopyFlag = 1;
				}

				// Set up for Mouse Movement
				SetCapture();
				m_SelectDevice = DDevice;

			} else {

				tGP->OnLButtonDown(nFlags, PointXPosition, PointYPosition, this, &ViewRet );
				
				m_ColSelStart = ViewRet.ColSelStart;
				m_ColSelEnd = ViewRet.ColSelEnd;
				m_ColSelBegin = ViewRet.ColSelBegin;
				if ( ViewRet.MenuFunc == DEF_GENESELECTCOL ) {
					SetCapture();
					m_SelectDevice = DDevice;
				}
			}
		}
	}
}

void
CSummaryView::AdjustEndToPoint( CGPSumView *tGP, UINT PointXPosition, DWORD PointYPosition, CView *pWnd )
{
	CGPSumView* cGP;
	CGPSumView* nGP;

	POSITION tPos;
	
	if ( m_EndSelect != tGP->GetEnum() ) {

		UINT nEnd = tGP->GetEnum();
		while ( m_EndSelect != nEnd ) {

			if ( nEnd < m_EndSelect ) {

				cGP = (CGPSumView *)m_RowViewList.GetPrev(m_EndPos);

				// copy to a temp work 
				tPos = m_EndPos;
				// Get the real next one
				nGP = (CGPSumView *)m_RowViewList.GetPrev(tPos);

				// Check for select or deselect ...
				m_EndSelect = nGP->GetEnum();
				if ( m_EndSelect >= m_StartSelect ) {
					cGP->DeSelect();

					InvalidateGVBLP( cGP );

				} else if ( m_EndSelect < m_StartSelect ) {
					nGP->Select();

					InvalidateGVBLP( nGP );
				}

			} else {

				cGP = (CGPSumView *)m_RowViewList.GetNext(m_EndPos);
				// Copy position to a temp work
				tPos = m_EndPos;
				// Get the real next one
				nGP = (CGPSumView *)m_RowViewList.GetNext(tPos);

				// Check for select or deselect ...
				m_EndSelect = nGP->GetEnum();
				if ( m_EndSelect > m_StartSelect ) {
					nGP->Select();

					InvalidateGVBLP( nGP );

				} else if ( m_EndSelect <= m_StartSelect ) {
					cGP->DeSelect();

					InvalidateGVBLP( cGP );
				}
			}
		}
	}
}




void 
CSummaryView::MoveFunc(UINT nFlags, CPoint point, int DDevice) 
{
	if ( GetCapture() == this && m_SelectDevice == DDevice ) {

		VIEWRETSTRUCT	ViewRet;
		ViewRet.Expanded = 0;
		ViewRet.MenuFunc = GetMenuFunction();
		ViewRet.DDevice = DDevice;

		ViewRet.ColSelStart = m_ColSelStart;
		ViewRet.ColSelEnd = m_ColSelEnd;
		ViewRet.ColSelBegin = m_ColSelBegin;

		int PointXPosition;
		DWORD PointYPosition;

		PointXPosition = point.x + m_DisplayXPosition;
		PointYPosition = (DWORD)point.y + m_DisplayYPosition;

#ifdef _MAC
		if ( !CheckClipCursor( point ) ) return;
#endif

		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPSumView *tGP;

		while ( tPos != NULL ) {
			tGP = (CGPSumView *)m_RowViewList.GetNext(tPos);
			if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
				if ( ViewRet.MenuFunc == DEF_GENESELECT ) {
					AdjustEndToPoint( tGP, PointXPosition, PointYPosition, this );
				} else {
					tGP->OnMouseMove(nFlags, PointXPosition, PointYPosition, this, &ViewRet );

					m_ColSelStart = ViewRet.ColSelStart;
					m_ColSelEnd = ViewRet.ColSelEnd;

				}
				break;
			}
		}

	}

// for status bar updates

	int PointXPosition;
	DWORD PointYPosition;

	PointXPosition = point.x + m_DisplayXPosition;
	PointYPosition = (DWORD)point.y + m_DisplayYPosition;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPSumView *)m_RowViewList.GetNext(tPos);
		if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
			tGP->SetStatusBar(nFlags, PointXPosition, PointYPosition );
			break;
		}
	}

	
}


void 
CSummaryView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	int MenuFunc = GetMenuFunction();

	if ( MenuFunc == DEF_GENESELECT || MenuFunc == DEF_GENESELECTCOL ) {

		UINT PointXPosition;
		DWORD PointYPosition;

		PointXPosition = point.x + m_DisplayXPosition;
		PointYPosition = (DWORD)point.y + m_DisplayYPosition;

		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPSumView *tGP;
	
		DeSelectAll();
	
		while ( tPos != NULL ) {
	
			tGP = (CGPSumView *)m_RowViewList.GetNext(tPos);
	
			if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
				tGP->OnLButtonDblClk(nFlags, PointXPosition, PointYPosition, this );
			}
		}
		
		// All done here!
		return;
	}

	// Check for doubleclick on a score line

	UINT PointXPosition;
	DWORD PointYPosition;

	PointXPosition = point.x + m_DisplayXPosition;
	PointYPosition = (DWORD)point.y + m_DisplayYPosition;

	m_MyCaret.FollowMouse( PointXPosition, PointYPosition );

	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDblClk(nFlags, point);
}

void
CSummaryView::ClearMenu()
{
	m_GeneSelect = 0;
	m_GeneSelectCol = 0;
	
}

unsigned int 
CSummaryView::GetMenuFunction()
{
	int ret = 0;

	ret += m_GeneSelect * DEF_GENESELECT;
	ret += m_GeneSelectCol * DEF_GENESELECTCOL;

	return ret;
}


void CSummaryView::OnSelect() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneSelect == 0 ) {
		ClearMenu();
		m_GeneSelect = 1;
	} else {
		m_GeneSelect = 0;
	}
}

void CSummaryView::OnUpdateSelect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneSelect );
}

//
// SHADING
//
void CSummaryView::OnSelectcol() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	m_ColSelStart = m_ColSelEnd = m_ColSelBegin = 0;
	if ( m_GeneSelectCol == 0 ) {
		ClearMenu();
		m_GeneSelectCol = 1;
	} else {
		m_GeneSelectCol = 0;
	}
	
}

void CSummaryView::OnUpdateSelectcol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneSelectCol );
}

void CSummaryView::OnGenecreatewin() 
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	DWORD tStart, tLen;
	if ( m_ColSelStart < m_ColSelEnd ) {
		tStart = m_ColSelStart;
		tLen = m_ColSelEnd - m_ColSelStart + 1;
	} else {
		tStart = m_ColSelEnd;
		tLen = m_ColSelStart - m_ColSelEnd + 1;
	}

	CGSFiller *pGSFiller = pDoc->pGSFiller;

	CGenedocDoc* pnDoc = (CGenedocDoc *)((CGenedocApp *)AfxGetApp())->CreateNewDocument();
	ASSERT ( pnDoc->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	
	CGSFiller * pnGSFiller;
	pnGSFiller = new CGSFiller;
	if ( pnGSFiller == 0 ) {
		AfxMessageBox( "sumview:new:fail:19" );
		return;
	}

	// Put the data rows on the list

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		
		CGeneSegment *tnCGSeg = new CGeneSegment();
		if ( tnCGSeg == 0 ) {
			AfxMessageBox( "sumview:new:fail:20" );
			return;
		}
		
		tnCGSeg->CreateCopy( tCGSeg, tStart, tLen );
//			tCGSeg->GetStyle(), 
//			tCGSeg->GetTitle(),
//			tCGSeg->GetDescr(), 
//			tCGSeg->GetWeight(), 
//			tCGSeg->MidText(tStart, tLen), 
//			tLen, 
//			tCGSeg->GetTextStart() + tStart, 
//			tCGSeg->GetGapChar(), 
//			tCGSeg->TextColor, 
//			tCGSeg->BackColor, 
//			tCGSeg->m_DisplayGroup
//		);

		pnGSFiller->AddData( tnCGSeg );

	}
	
	pnGSFiller->pGeneSegParent = NULL;

	pDoc->SetUserDefaults();

	
	// copy comments into GFiller head list
	tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while (tPos != NULL ) {
		CString * tStr = new CString ( *(CString *)pGSFiller->SegHeaderList.GetNext(tPos) );
		if ( tStr == 0 ) {
			AfxMessageBox( "sumview:new:fail:22" );
			return;
		}
		pnGSFiller->AddHeader( tStr );
	}

	pnDoc->CopyGSFiller( pnGSFiller );
	
//	pnDoc->CopyUserVars( &pnDoc->m_UserVars, &pDoc->m_UserVars );	// To <- From

	pnDoc->ParseTree( pDoc->m_UserVars.m_ParseString, 0 );

	pnDoc->GetUserDefaults();	// To <- From

}

void CSummaryView::OnUpdateGenecreatewin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}


void 
CSummaryView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
{
	CView::OnActivateView( bActivate, pActivateView, pDeactiveView );

	if ( bActivate && !m_PrintOnly) {
		if ( ((CGenedocApp *)AfxGetApp())->m_OKOrientCheck ) {
			CGenedocDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			((CGenedocApp *)AfxGetApp())->SetLandscape( pDoc->m_UserVars.m_Orientation );
		}
	}

}


void CSummaryView::OnFilePrint()
{
	// TODO: Add your command handler code here // CView
	
	m_PrintOnly = 1;

	CView::OnFilePrint();

	m_PrintOnly = 0;

	OnUpdate( NULL, 0L, NULL );
	
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->CheckOrientation();

}

void 
CSummaryView::OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView )
{
// pDC    Points to the printer device context.
// pInfo    Points to a CPrintInfo structure that describes the current print job. 
// point    Specifies the point on the page that was last displayed in preview mode.
// pView    Points to the view object used for previewing.

	m_PrintOnly = 0;

	OnUpdate( NULL, 0L, NULL );
	
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->CheckOrientation();


	CView::OnEndPrintPreview( pDC, pInfo,point, pView );
}

void CSummaryView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	
	m_PrintOnly = 1;

	CView::OnFilePrintPreview();

}

void 
CSummaryView::InvalNewEndPoint( DWORD Range1, DWORD Range2)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGPRV;
	
	while ( tPos != NULL ) {
		tGPRV = (CGPSumView *)m_RowViewList.GetNext(tPos);
		tGPRV->InvalNewEndPoint( this, Range1, Range2);
	}
}


void CSummaryView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 4, 0 );
	
}

void CSummaryView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopyinv() 
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 4, 0 );
	
}

void CSummaryView::OnUpdateEditCopyinv(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopy0()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 0, 0 );
}

void CSummaryView::OnUpdateEditCopy0(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopy8()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 8, 0 );
}

void CSummaryView::OnUpdateEditCopy8(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopyinv0()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 0, 0 );
}

void CSummaryView::OnUpdateEditCopyinv0(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopyinv8()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 8, 0 );
}

void CSummaryView::OnUpdateEditCopyinv8(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopyinvbit()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 0, 1 );
	
}

void CSummaryView::OnUpdateEditCopyinvbit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CSummaryView::OnEditCopybit()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 0, 1 );
	
}

void CSummaryView::OnUpdateEditCopybit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}


//
//
//
//


extern WORD DibNumColors (VOID FAR * pv);
extern WORD PaletteSize (VOID FAR * pv);
extern HANDLE DibFromBitmap (
    HBITMAP      hbm,
    DWORD            biStyle,
    WORD             biBits,
    HPALETTE     hpal);


void 
CSummaryView::ClipFunction( int InvFlag, int ResFlag, int BitFlag )
{

	UINT sizeXPos = (UINT)-1, sizeXSize = 0;
	DWORD sizeYPos = (DWORD)-1, sizeYSize = 0;

//	CRect SizeRect;

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

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPSumView*)m_RowViewList.GetNext(tPos);
	
		if ( tGP->IsSelected() ) {
				
			UINT tXPos, tXSize;
			DWORD tYPos, tYSize;
			tGP->GetPosition(&tXPos, &tYPos);
			tGP->GetSize(&tXSize, &tYSize);

			if ( sizeXPos > tXPos ) sizeXPos = tXPos;
			if ( sizeYPos > tYPos ) sizeYPos = tYPos;

			if ( sizeXSize < tXPos + tXSize ) sizeXSize = tXPos + tXSize;
			if ( sizeYSize < tYPos + tYSize ) sizeYSize = tYPos + tYSize;
		}
	}

#ifdef _WIN32

	if ( (sizeYSize - sizeYPos) > 32767 ) {
		AfxMessageBox("Select too large!");
		return;
	}
#endif


	CBitmap CopyBmp;

	CDC * pDC = GetDC();

	CDC cDC;

	if ( ! cDC.CreateCompatibleDC( pDC ) ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox( "Create CompatibleDC fails", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		return;
	}

	if ( !CopyBmp.CreateCompatibleBitmap( pDC, (int)(sizeXSize - sizeXPos), (int)(sizeYSize - sizeYPos) ) ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox( "CreateBitmap fails", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		return;
	}


	CBitmap* oBmp = cDC.SelectObject ( &CopyBmp );
	
	if ( oBmp == NULL ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox ( "Cannot Select Bitmap", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		return;
	}

	// Clear out the new bitmap
	if ( !cDC.BitBlt( 0, 0, (int)(sizeXSize - sizeXPos), (int)(sizeYSize - sizeYPos), NULL, 0, 0, WHITENESS ) ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox ( "Error in BitBlt WHITENESS", MB_OK | MB_ICONEXCLAMATION );
		CloseClipboard();
		ReleaseDC(pDC);
		return;
	}


//	cDC.SetWindowOrg( (int)sizeXPos, (int)sizeYPos );

	UINT sDisplayXPos = m_DisplayXPosition;
	DWORD sDisplayYPos = m_DisplayYPosition;
	UINT sDisplayWidth = m_DisplayWidth;
	DWORD sDisplayHeight = m_DisplayHeight;

	m_DisplayXPosition = sizeXPos;
	m_DisplayYPosition = sizeYPos;
	m_DisplayWidth = sizeXSize - sizeXPos;
	m_DisplayHeight = sizeYSize - sizeYPos - 1;
//	m_DisplayWidth = sizeXSize;
//	m_DisplayHeight = sizeYSize;

	m_PrintYOffSet = 0;

	// Call Drawing Functions
	DoDraw(&cDC, FALSE, InvFlag);

	m_DisplayXPosition = sDisplayXPos;
	m_DisplayYPosition = sDisplayYPos;
	m_DisplayWidth = sDisplayWidth;
	m_DisplayHeight = sDisplayHeight;

	ReleaseDC(pDC);

	cDC.SelectObject(oBmp);

//
	if ( BitFlag ) {
		HBITMAP hBmp = (HBITMAP)CopyBmp.Detach();
		if ( hBmp == NULL ) {
			AfxMessageBox("Detach Fails" );
		} else {
			if ( SetClipboardData(CF_BITMAP, hBmp) == NULL ) {
				AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
			}
		}
	
	} else {
		
		HANDLE hdib = DibFromBitmap ( (HBITMAP)CopyBmp.m_hObject, BI_RGB, ResFlag, NULL );
	
		if ( hdib != NULL ) {
			if ( SetClipboardData(CF_DIB, hdib) == NULL ) {
				AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
			}
		} else {
			AfxMessageBox( "Convert to DIB Failed" );
		}
	}

// CBitmap
//

	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know
	
	return;
}

void CSummaryView::OnGenecopypict()
{
	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "Pict Files (*.pct)|*.pct|All Files (*.*)|*.*||";

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CDocument

	CString possName = pDoc->ConvertPathname ( ".pct" );

	CFileDialog tDlg(FALSE, "pct", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;
	pDoc->BeginWaitCursor(); // Let em know
	
	CPictFile	tPictFile;
	CRect SizeRect;

	int Bold;
	if ( pDoc->m_UserVars.m_FontWeight == FW_NORMAL ) {
		Bold = 0;;
	} else {
		Bold = 1;
	}

	CString PathName = tDlg.GetPathName();
	
	CGPSumView *tGPRV;

//	SizeRect.SetRectEmpty();
//	UINT SizeXPosition = (UINT)-1;
//	DWORD SizeYPosition = (DWORD)-1;
	UINT SizeXSize = 0;
	DWORD SizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	while ( tPos != NULL ) {
		tGPRV = (CGPSumView*)m_RowViewList.GetNext(tPos);
	
		if ( tGPRV->IsSelected() ) {
			UINT tXSize;
			DWORD tYSize;
			// SizeRect |= tGPRV->GetViewRect();
			tGPRV->GetSize(&tXSize, &tYSize);
			if ( tXSize > SizeXSize ) SizeXSize = tXSize;
			SizeYSize += tYSize;
		}
	}

	int numcols = SizeXSize - 
	( m_CharWidth * ((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength));
	numcols /= m_SumWidth;

	if ( !tPictFile.SumPictInit( 
		(int)SizeXSize, 
		(int)(SizeYSize + m_LineHeight), 

		((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength), 
		numcols, 
		pDoc->m_UserVars.m_SumColInch, 

		pDoc->m_UserVars.m_FontSize, 
		(int)m_CharWidth, 
		(int)m_LineHeight, 
		(int)m_Descent, 
		Bold, 
		"Courier New", 
		PathName, 
		pDoc->m_UserVars.m_PictWidth, 
		pDoc->m_UserVars.m_PictHeight, 
		pDoc->m_UserVars.m_PictAscent
	) ) {
		AfxMessageBox("Error Pict File Open!" );
		return;
	}

	tPos = m_RowViewList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		tGPRV = (CGPSumView *)m_RowViewList.GetNext(tPos);
		if ( tGPRV->IsSelected() ) {
			tGPRV->WritePict (&tPictFile, 0, pDoc);
		}
	}

	tPictFile.Exit();

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know
	
}


void CSummaryView::OnUpdateGenecopypict(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
}


void CSummaryView::OnCopymetaclip() 
{

#ifdef _WIN32

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

	CDC* pDC = GetDC();

	pDoc->BeginWaitCursor(); // Let em know

	UINT sizeXPos = (UINT)(-1), sizeXSize = 0;
	DWORD sizeYPos = (DWORD)(-1L), sizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPSumView*)m_RowViewList.GetNext(tPos);
	
		if ( tGP->IsSelected() ) {
				
			UINT tXPos, tXSize;
			DWORD tYPos, tYSize;
			tGP->GetPosition(&tXPos, &tYPos);
			tGP->GetSize(&tXSize, &tYSize);

			if ( sizeXPos > tXPos ) sizeXPos = tXPos;
			if ( sizeYPos > tYPos ) sizeYPos = tYPos;

			if ( sizeXSize < tXPos + tXSize ) sizeXSize = tXPos + tXSize;
			if ( sizeYSize < tYPos + tYSize ) sizeYSize = tYPos + tYSize;
		}
	}

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double tXSize, tYSize;

	tXSize = (sizeXSize - sizeXPos) * xpi * 100.0;

	tYSize = (sizeYSize - sizeYPos) * ypi * 100.0;

	CRect rectView(0,0,(int)tXSize, (int)tYSize );

	CMetaFileDC dcMeta;

	dcMeta.CreateEnhanced(pDC, NULL, rectView, "GeneDoc\0MetaFile\0\0" );

	dcMeta.SetAttribDC( pDC->m_hAttribDC );

	ReleaseDC(pDC);

	OnPrepareDC( &dcMeta );

	UINT sDisplayXPos = m_DisplayXPosition;
	DWORD sDisplayYPos = m_DisplayYPosition;
	UINT sDisplayWidth = m_DisplayWidth;
	DWORD sDisplayHeight = m_DisplayHeight;

	m_DisplayXPosition = sizeXPos;
	m_DisplayYPosition = sizeYPos;
	m_DisplayWidth = sizeXSize - sizeXPos;
	m_DisplayHeight = sizeYSize - sizeYPos;

	m_PrintYOffSet = 0;

	// Call Drawing Functions

	DoDraw(&dcMeta, FALSE, FALSE );

	m_DisplayXPosition = sDisplayXPos;
	m_DisplayYPosition = sDisplayYPos;
	m_DisplayWidth = sDisplayWidth;
	m_DisplayHeight = sDisplayHeight;


	HENHMETAFILE hMeta = dcMeta.CloseEnhanced();


	if ( SetClipboardData(CF_ENHMETAFILE, hMeta) == NULL ) {
		AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
	}


	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know

#endif

	return;

	
}

void CSummaryView::OnUpdateCopymetaclip(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _WIN32	
	pCmdUI->Enable(m_CopyFlag);
#else
	pCmdUI->Enable(FALSE);
#endif

}

void CSummaryView::OnCopymetafile() 
{

#ifdef _WIN32
	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "Meta Files (*.emf)|*.emf|All Files (*.*)|*.*||";

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CDocument

	CString possName = pDoc->ConvertPathname ( ".emf" );

	CFileDialog tDlg(FALSE, "emf", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;
	
	CDC* pDC = GetDC();

	pDoc->BeginWaitCursor(); // Let em know

	UINT sizeXPos = (UINT)(-1), sizeXSize = 0;
	DWORD sizeYPos = (DWORD)(-1L), sizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPSumView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPSumView*)m_RowViewList.GetNext(tPos);
	
		if ( tGP->IsSelected() ) {
				
			UINT tXPos, tXSize;
			DWORD tYPos, tYSize;
			tGP->GetPosition(&tXPos, &tYPos);
			tGP->GetSize(&tXSize, &tYSize);

			if ( sizeXPos > tXPos ) sizeXPos = tXPos;
			if ( sizeYPos > tYPos ) sizeYPos = tYPos;

			if ( sizeXSize < tXPos + tXSize ) sizeXSize = tXPos + tXSize;
			if ( sizeYSize < tYPos + tYSize ) sizeYSize = tYPos + tYSize;
		}
	}

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double tXSize, tYSize;

	tXSize = (sizeXSize - sizeXPos) * xpi * 100.0;

	tYSize = (sizeYSize - sizeYPos) * ypi * 100.0;

	CRect rectView(0,0,(int)tXSize, (int)tYSize );

	CMetaFileDC dcMeta;

	dcMeta.CreateEnhanced(pDC, tDlg.GetPathName(), rectView, "GeneDoc\0MetaFile\0\0" );

	dcMeta.SetAttribDC( pDC->m_hAttribDC );

	ReleaseDC(pDC);

	OnPrepareDC( &dcMeta );

	UINT sDisplayXPos = m_DisplayXPosition;
	DWORD sDisplayYPos = m_DisplayYPosition;
	UINT sDisplayWidth = m_DisplayWidth;
	DWORD sDisplayHeight = m_DisplayHeight;

	m_DisplayXPosition = sizeXPos;
	m_DisplayYPosition = sizeYPos;
	m_DisplayWidth = sizeXSize - sizeXPos;
	m_DisplayHeight = sizeYSize - sizeYPos;

	m_PrintYOffSet = 0;

	// Call Drawing Functions
	DoDraw(&dcMeta, FALSE, FALSE );

	m_DisplayXPosition = sDisplayXPos;
	m_DisplayYPosition = sDisplayYPos;
	m_DisplayWidth = sDisplayWidth;
	m_DisplayHeight = sDisplayHeight;


	HENHMETAFILE hMeta = dcMeta.CloseEnhanced();

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know

#endif

}

void CSummaryView::OnUpdateCopymetafile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _WIN32	
	pCmdUI->Enable(m_CopyFlag);
#else
	pCmdUI->Enable(FALSE);
#endif
	
}


void CSummaryView::OnDstatscore()
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	DWORD StartRange, EndRange;
	if ( m_ColSelStart < m_ColSelEnd ) {
		StartRange = m_ColSelStart;
		EndRange = m_ColSelEnd;
	} else {
		StartRange = m_ColSelEnd;
		EndRange = m_ColSelStart;
	}
	
	pDoc->DStatScore ( StartRange, EndRange, 1 );

	DeSelectAll();
}

void CSummaryView::OnUpdateDstatscore(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}

void CSummaryView::OnDstatscoreall()
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	DWORD StartRange, EndRange;
	if ( m_ColSelStart < m_ColSelEnd ) {
		StartRange = m_ColSelStart;
		EndRange = m_ColSelEnd;
	} else {
		StartRange = m_ColSelEnd;
		EndRange = m_ColSelStart;
	}
	
	pDoc->DStatScore ( StartRange, EndRange, 0 );

	DeSelectAll();
	
}

void CSummaryView::OnUpdateDstatscoreall(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}

