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
// genedvw.cpp : implementation of the CGenedocView class
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
// CGenedocView

IMPLEMENT_DYNCREATE(CGenedocView, CView)

BEGIN_MESSAGE_MAP(CGenedocView, CView)
	//{{AFX_MSG_MAP(CGenedocView)
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
	ON_COMMAND(IDM_GENEARRANGE, OnGenearrange)
	ON_UPDATE_COMMAND_UI(IDM_GENEARRANGE, OnUpdateGenearrange)
	ON_COMMAND(IDM_SELECT, OnSelect)
	ON_UPDATE_COMMAND_UI(IDM_SELECT, OnUpdateSelect)
	ON_COMMAND(IDM_GENEDELETEDASH, OnGenedeletedash)
	ON_UPDATE_COMMAND_UI(IDM_GENEDELETEDASH, OnUpdateGenedeletedash)
	ON_COMMAND(IDM_GENEINSERTDASH, OnGeneinsertdash)
	ON_UPDATE_COMMAND_UI(IDM_GENEINSERTDASH, OnUpdateGeneinsertdash)
	ON_COMMAND(IDM_SELECTCOL, OnSelectcol)
	ON_UPDATE_COMMAND_UI(IDM_SELECTCOL, OnUpdateSelectcol)
	ON_COMMAND(IDM_GENECREATEWIN, OnGenecreatewin)
	ON_COMMAND(IDM_GENESCORE, OnGenescore)
	ON_COMMAND(IDM_GENEINSERTOTHER, OnGeneinsertother)
	ON_UPDATE_COMMAND_UI(IDM_GENEINSERTOTHER, OnUpdateGeneinsertother)
	ON_COMMAND(IDM_GENEDELETEOTHER, OnGenedeleteother)
	ON_UPDATE_COMMAND_UI(IDM_GENEDELETEOTHER, OnUpdateGenedeleteother)
	ON_COMMAND(IDM_GENEINSERTFILL, OnGeneinsertfill)
	ON_COMMAND(IDM_GENEDELETEFILL, OnGenedeletefill)
	ON_COMMAND(IDM_GENESCOREKEY, OnGenescorekey)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPYINV, OnEditCopyinv)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYINV, OnUpdateEditCopyinv)
	ON_COMMAND(IDM_MANUALSHADE, OnManualshade)
	ON_UPDATE_COMMAND_UI(IDM_MANUALSHADE, OnUpdateManualshade)
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
	ON_COMMAND(IDM_GENECLEARSCORE, OnGeneclearscore)
	ON_COMMAND(IDM_COPYTEXT, OnCopytext)
	ON_COMMAND(IDM_GENECOPYPICT, OnGenecopypict)
	ON_UPDATE_COMMAND_UI(IDM_GENECOPYPICT, OnUpdateGenecopypict)
	ON_COMMAND(IDM_GENEEDITMODE, OnGeneeditmode)
	ON_UPDATE_COMMAND_UI(IDM_GENEEDITMODE, OnUpdateGeneeditmode)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(IDM_COPYMETACLIP, OnCopymetaclip)
	ON_COMMAND(IDM_COPYMETAFILE, OnCopymetafile)
	ON_UPDATE_COMMAND_UI(IDM_COPYMETACLIP, OnUpdateCopymetaclip)
	ON_UPDATE_COMMAND_UI(IDM_COPYMETAFILE, OnUpdateCopymetafile)
	ON_UPDATE_COMMAND_UI(IDM_GENEDELETEFILL, OnUpdateGenedeletefill)
	ON_UPDATE_COMMAND_UI(IDM_GENEINSERTFILL, OnUpdateGeneinsertfill)
	ON_UPDATE_COMMAND_UI(IDM_GENESCORE, OnUpdateGenescore)
	ON_COMMAND(IDM_DSTATSCORE, OnDstatscore)
	ON_UPDATE_COMMAND_UI(IDM_DSTATSCORE, OnUpdateDstatscore)
	ON_COMMAND(IDM_DSTATSCOREALL, OnDstatscoreall)
	ON_UPDATE_COMMAND_UI(IDM_DSTATSCOREALL, OnUpdateDstatscoreall)
	ON_COMMAND(IDM_GENEFINDREPLACE, OnGenefindreplace)
	ON_UPDATE_COMMAND_UI(IDM_GENECREATEWIN, OnUpdateGenecreatewin)
	ON_COMMAND(IDM_GENECOPYSEQ, OnGenecopyseq)
	ON_UPDATE_COMMAND_UI(IDM_GENECOPYSEQ, OnUpdateGenecopyseq)
	ON_COMMAND(IDM_GENECOPYHTML, OnGenecopyhtml)
	ON_UPDATE_COMMAND_UI(IDM_GENECOPYHTML, OnUpdateGenecopyhtml)
	ON_COMMAND(IDM_GENECOPYRTF, OnGenecopyrtf)
	ON_UPDATE_COMMAND_UI(IDM_GENECOPYRTF, OnUpdateGenecopyrtf)
	ON_COMMAND(IDM_GENEWRITELOGODDS, OnGenewritelogodds)
	ON_UPDATE_COMMAND_UI(IDM_GENEWRITELOGODDS, OnUpdateGenewritelogodds)
	ON_COMMAND(IDM_GENEMOVE, OnGenemove)
	ON_UPDATE_COMMAND_UI(IDM_GENEMOVE, OnUpdateGenemove)
	ON_COMMAND(IDM_DELCOLUMNS, OnDelcolumns)
	ON_UPDATE_COMMAND_UI(IDM_DELCOLUMNS, OnUpdateDelcolumns)
	ON_COMMAND(IDM_FIND, OnFind)
	ON_COMMAND(IDM_FINDNEXT, OnFindnext)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(IDM_REPLACEFROMPROJ, OnReplacefromproj)
	ON_UPDATE_COMMAND_UI(IDM_REPLACEFROMPROJ, OnUpdateReplacefromproj)
	ON_COMMAND(IDM_GENEINSERTONE, OnGeneinsertone)
	ON_UPDATE_COMMAND_UI(IDM_GENEINSERTONE, OnUpdateGeneinsertone)
	ON_COMMAND(IDM_DNATRANS, OnDnatrans)
	ON_COMMAND(IDM_GENEDELETEONE, OnGenedeleteone)
	ON_UPDATE_COMMAND_UI(IDM_GENEDELETEONE, OnUpdateGenedeleteone)
	ON_COMMAND(IDM_DNAFFREQREP, OnDnaffreqrep)
	ON_UPDATE_COMMAND_UI(IDM_DNAFFREQREP, OnUpdateDnaffreqrep)
	ON_COMMAND(IDM_DNACOLFREQREP, OnDnacolfreqrep)
	ON_UPDATE_COMMAND_UI(IDM_DNACOLFREQREP, OnUpdateDnacolfreqrep)
	ON_COMMAND(IDM_DNACOLFRWREP, OnDnacolfrwrep)
	ON_UPDATE_COMMAND_UI(IDM_DNACOLFRWREP, OnUpdateDnacolfrwrep)
	//}}AFX_MSG_MAP
#ifdef WIN32
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
#endif
END_MESSAGE_MAP()

	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
/////////////////////////////////////////////////////////////////////////////
// CGenedocView construction/destruction

CGenedocView::CGenedocView()
{
	// TODO: add construction code here

	m_SelectDevice = NONE;
	m_PrintOnly = 0;
	m_ShadeTextColor = RGB(0,0,0);
	m_ShadeBackColor = RGB(255,255,255);

	m_iReadShift = 0;
	m_TransColumns = 0;
	m_TransFixed = 0;
	m_TransFltStart = 0;

#ifdef _MAC
	m_ClipFuncClipFunc = FALSE;
#endif

	ClearMenu();
}

CGenedocView::~CGenedocView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pGeneView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CGenedocView drawing

void
CGenedocView::CleanRowViewList()
{
	while ( !m_RowViewList.IsEmpty() ) {
		CGPRowView *tRV = ( CGPRowView *)m_RowViewList.RemoveHead();
		while ( ! (tRV->ViewDataList.IsEmpty()) ) {
			delete ( CGeneViewBase *)tRV->ViewDataList.RemoveHead();
		}
		delete tRV;
	}
}

void
CGenedocView::AddHeadTail( CGVEdit* tGEt, CGVEdit* tGEh, CGPRowView* tRowView )
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
		AfxMessageBox( "Genedvw:new:fail:2" );
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
				AfxMessageBox( "genedvw:new:fail:3" );
				return;
			}
			tGEL->AddData ( tStr );
			memset ( tBuff, ' ', m_GVETailLength );
			tBuff[m_GVETailLength] = 0;
			tStr = new CString (tBuff);
			if ( tStr == 0 ) {
				AfxMessageBox( "genedvw:new:fail:4" );
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
			AfxMessageBox( "genedvw:new:fail:5" );
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
				AfxMessageBox( "genedvw:new:fail:6" );
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
CGenedocView::AddHead( CGVEdit* tGEh, CGPRowView* tRowView )
{
	char tBuff[128];
	CString *tStr;

	CGeneSegBase * tGSBh = tGEh->m_pBase;


	CGVEditLead* tGEL = new CGVEditLead();
	if ( tGEL == 0 ) {
		AfxMessageBox( "Genedvw:new:fail:7" );
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
				AfxMessageBox( "genedvw:new:fail:8" );
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
			AfxMessageBox( "genedvw:new:fail:9" );
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
CGenedocView::ResetGPSize(CDC* pDC, UINT MaxX )
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
//	pDC->GetOutputTextMetrics( &TM );
	m_CharWidth = TM.tmAveCharWidth;
//	m_CharWidth = TM.tmMaxCharWidth;
//	m_LineHeight = TM.tmHeight - TM.tmInternalLeading;
	m_LineHeight = TM.tmHeight;
//	For Pict Files.
	m_Descent = TM.tmDescent;

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
		MaxX = m_CharWidth * 
			( pDoc->m_UserVars.m_FixedXSize 
			+ (m_GVETailLength * pDoc->m_UserVars.m_ShowTail) 
			+ m_GVELeadLength );
//			+ m_GVELeadLength + 1);
//		m_MaxX = tMaxX;
	} else if ( pDoc->m_UserVars.m_WidthMode == 2 ) {
		MaxX = m_CharWidth * 
			( ((CGeneSegment*)pDoc->pGSFiller->SegDataList.GetHead())->GetTextLength() 
			+ (m_GVETailLength * pDoc->m_UserVars.m_ShowTail) 
			+ m_GVELeadLength );

	}

	
	// Test for minimum of XSize = 10 residues + lead and tail.
//	if ( MaxX < (m_CharWidth * ((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength + 1 + 10)) ) {
//		MaxX = m_CharWidth * ((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength + 1 + 10);
	if ( MaxX < (m_CharWidth * ((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength + 10)) ) {
		MaxX = m_CharWidth * ((m_GVETailLength * pDoc->m_UserVars.m_ShowTail) + m_GVELeadLength + 10);
//		m_MaxX = tMaxX;
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
CGenedocView::ResetGPAdd( CGeneSegBase *pGSBase )
{
    CGPRowView* tRowView;
	
	if ( m_RowViewList.GetCount() == 0 ) {
		tRowView = new CGPRowView;
		if ( tRowView == 0 ) {
			AfxMessageBox( "Genedvw:new:fail:10" );
			return;
		}
//		tRowView->SetPosition( m_CharWidth / 2, m_LineHeight / 2 );
		tRowView->SetPosition( 0, 0 );
		tRowView->SetSize( 0, 0 );
		// The the object internal starting position
		// Make it 10 chars.
//		tRowView->m_IntXPos = (m_CharWidth * m_GVELeadLength) + (m_CharWidth / 2);
		tRowView->m_IntXPos = (m_CharWidth * m_GVELeadLength);
//		tRowView->m_IntYPos = (DWORD)(m_LineHeight / 2);
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
CGenedocView::BuildRowViews( CGeneSegBase *pGSBase, DWORD StartPos )
{
//	CString *tStr;
	DWORD tnChars;

	// CSize GESize;
	POSITION tPos;

	UINT tWideChars, tiSize;
	CGVEdit* tGE;
    CGPRowView* tRowView;

	if ( m_TotalWidth < (m_CharWidth * 
		((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength)) 
	) return;

	UINT workMaxX = m_TotalWidth 
		- (m_CharWidth * ((m_GVETailLength * GetDocument()->m_UserVars.m_ShowTail) + m_GVELeadLength));

	tnChars = ((CGeneSegment*)pGSBase->SegDataList.GetHead())->GetTextLength() - StartPos;

	do {

		tRowView = (CGPRowView *)m_RowViewList.GetTail();

		// How to allow for scroll bars not being in plane yet?
		UINT tRVXSize;
		DWORD tRVYSize;
		tRowView->GetSize(&tRVXSize, &tRVYSize);
		
		tWideChars = (workMaxX / m_CharWidth) - (tRVXSize / m_CharWidth);

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
				CGVEdit* tGEt = (CGVEdit*)tRowView->ViewDataList.GetTail();
	    	    CGVEdit* tGEh = (CGVEdit*)tRowView->ViewDataList.GetHead();
				AddHeadTail ( tGEt, tGEh, tRowView );
			} else {
				// Add Head object
	    	    CGVEdit* tGEh = (CGVEdit*)tRowView->ViewDataList.GetHead();
				AddHead ( tGEh, tRowView );
			}
			// Done adding Edit Row Leader

			tRowView = new CGPRowView;
			if ( tRowView == 0 ) {
				AfxMessageBox( "Genedvw:new:fail:11" );
				return;
			}

			tRowView->SetPosition( 0, tYPos );
			tRowView->SetSize( 0, 0 );

			tRowView->m_IntXPos = (m_CharWidth * m_GVELeadLength);
			tRowView->m_IntYPos = tYPos;
			tRowView->SetEnum( m_RowVEnum++ );
			tRowView->pGeneViewParent = (CGeneViewBase *)&m_RowViewList;

			m_RowViewList.AddTail (tRowView );

			m_LeaderSaveEnum = m_EnumCount++;

			// Add in some or all of pGSBase

			tWideChars = (workMaxX / m_CharWidth);
		}


		// Check for partial segment
		if ( tnChars > tWideChars ) {
			// loop and fill out trowview's

			tiSize = tWideChars;

			tGE = new CGVEdit();
			if ( tGE == 0 ) {
				AfxMessageBox( "Genedvw:new:fail:12" );
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
					AfxMessageBox( "Genedvw:new:fail:14" );
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
			tGE->CalcDrawSize( m_pDC, &tXSize, &tYSize, 0 );

			tRowView->m_IntXPos += tXSize;
		
			tRowView->AddTail( tGE );

			tnChars -= tiSize;
			StartPos += tiSize;
			
			
		} else {

			tGE = new CGVEdit();
			if ( tGE == 0 ) {
				AfxMessageBox( "Genedvw:new:fail:15" );
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
					AfxMessageBox( "Genedvw:new:fail:17" );
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
			tGE->CalcDrawSize( m_pDC, &tXSize, &tYSize, 0 );

			tRowView->m_IntXPos += tXSize;

			tRowView->AddTail( tGE );

			tnChars = 0;
		}

//		PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE );		// Yield to other apps.
	} while ( tnChars != 0 );

	// clean up.
	tRowView = (CGPRowView *)m_RowViewList.GetTail();
	UINT tXSize;
	DWORD tYSize;
	tRowView->GetSize( &tXSize, &tYSize );
//	m_TotalHeight += tYSize + m_LineHeight;
	m_TotalHeight += tYSize;

	CGeneViewBase* tGVB = (CGeneViewBase*)tRowView->ViewDataList.GetHead();

	if ( !tGVB->IsKindOf( RUNTIME_CLASS(CGVEditLead) ) ) {

		if ( GetDocument()->m_UserVars.m_ShowTail ) {
			CGVEdit* tGEt = (CGVEdit*)tRowView->ViewDataList.GetTail();
	        CGVEdit* tGEh = (CGVEdit*)tGVB;
			AddHeadTail( tGEt, tGEh, tRowView );
		} else {
			// Add Head object
	        CGVEdit* tGEh = (CGVEdit*)tGVB;
			AddHead ( tGEh, tRowView );
		}
	}

	
	// Test for create CGVEditFill
	tRowView = (CGPRowView *)m_RowViewList.GetTail();
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
		tWidth = m_TotalWidth / m_CharWidth;
		tWidth *= m_CharWidth;
	}

	
	if ( tXSize < tWidth ) {
		
		CGVEditFill* tGEF = new CGVEditFill();
		if ( tGEF == 0 ) {
			AfxMessageBox( "Genedvw:new:fail:27" );
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


void 
CGenedocView::ExpandedSegments(VIEWRETSTRUCT *pViewRet)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    CGPRowView* tRowView, *spRowView;
    // CSize sm_Size = m_Size;
    DWORD tTotalHeight = m_TotalHeight;
	
	// clean up.
	tRowView = (CGPRowView *)m_RowViewList.GetTail();
	spRowView = tRowView;

	UINT stXPosition;
	DWORD stYPosition;
	UINT stXSize;
	DWORD stYSize;

	tRowView->GetPosition(&stXPosition, &stYPosition);
	tRowView->GetSize(&stXSize, &stYSize);
	m_TotalHeight -= stYSize;


	tRowView->SetPosition ( 0, stYPosition );

	tRowView->m_IntXPos = (m_CharWidth * m_GVELeadLength );
	tRowView->m_IntYPos = stYPosition;


	CGeneViewBase* tGVB;

	// Remove the old Filler ..
	tGVB = (CGeneViewBase*)tRowView->ViewDataList.GetTail();
	if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEditFill)) ) {
		delete (CGVEditFill *)tRowView->ViewDataList.RemoveTail();
	}

	// trash the old tailer
	UINT sTailXPosition;
	DWORD sTailYPosition;
	UINT sTailXSize;
	DWORD sTailYSize;

	if ( pDoc->m_UserVars.m_ShowTail ) {
		tGVB = (CGeneViewBase*)tRowView->ViewDataList.RemoveTail();
		tGVB->GetPosition(&sTailXPosition, &sTailYPosition);
		tGVB->GetSize(&sTailXSize, &sTailYSize);
		delete tGVB;
	}
                                                                           
	// Save the old GVEdit
	tGVB = (CGeneViewBase*)tRowView->ViewDataList.RemoveTail();
	ASSERT ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit)));
	CGVEdit* tGVEdit = (CGVEdit*)tGVB;

	m_EnumCount = tGVEdit->GetEnum();
    CGeneSegBase * pGSBase = tGVEdit->m_pBase;
	DWORD StartPos = tGVEdit->m_StartPos;

	UINT tsGStrEnum;
	DWORD tsMovePoint;
	int tEditResFlag = 0;
	DWORD tsStartSelect;
	if ( tGVEdit->m_MoveString != NULL ) {
		tsGStrEnum = tGVEdit->m_MoveString->GetEnum();  /// hmmm .. not right row ..
		tsMovePoint = tGVEdit->m_MovePoint;
		tsStartSelect = tGVEdit->m_StartSelect;

		tEditResFlag = 1;
	}

	delete tGVEdit;

	// trash the old Header
	tGVB = (CGeneViewBase*)tRowView->ViewDataList.RemoveTail();
	m_LeaderSaveEnum = tGVB->GetEnum();
	delete tGVB;

	// So as filler and detect size ..
	tRowView->SetSize( 0, 0 );
	// purposely leave the old RowView On list.	

	BuildRowViews( pGSBase, StartPos );


	// clean up.
	tRowView = (CGPRowView *)m_RowViewList.GetTail();
	pViewRet->Clip = 0;

	if ( tEditResFlag ) {

		// Restore GVEdit Work Stuff.
		POSITION tPos = spRowView->ViewDataList.GetHeadPosition();
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)spRowView->ViewDataList.GetNext(tPos);
			if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVEdit)) ) {
				tGVEdit = (CGVEdit *)tGVB;
				break;
			}
		}
	
		tGVEdit->m_StartPos = StartPos;
		tGVEdit->m_MovePoint = tsMovePoint;
		tGVEdit->m_StartSelect = tsStartSelect;
		
		UINT tXLoc;
		DWORD tYLoc;
		tGVEdit->GetPosition(&tXLoc, &tYLoc );

		tPos = tGVEdit->ViewDataList.GetHeadPosition();
		CGeneString *tGStr;
		UINT tc = tsGStrEnum;
		while ( tPos != NULL ) {
			tGStr = (CGeneString *)tGVEdit->ViewDataList.GetNext(tPos);
			if ( !tc-- ) {
				break;
			}
			tYLoc += (DWORD)m_LineHeight;
		}
		tGVEdit->m_MoveString = tGStr;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();

		tXLoc += 1;
		tXSize += 1;


		tGVEdit->m_ClipXPosition = tXLoc;
		tGVEdit->m_ClipYPosition = tYLoc;
		tGVEdit->m_ClipXSize = tXSize;
		tGVEdit->m_ClipYSize = tYSize;

		pViewRet->ClipXPosition = tXLoc;
		pViewRet->ClipYPosition = tYLoc;
		pViewRet->ClipXSize = tXSize;
		pViewRet->ClipYSize = tYSize;

		pViewRet->Clip = 1;
		//
	}
	
	UINT tXPosition;
	DWORD tYPosition;
	UINT tXSize;
	DWORD tYSize;

	tRowView->GetPosition(&tXPosition, &tYPosition);
	tRowView->GetSize(&tXSize, &tYSize);

	// Invalidate New Area
	if ( tRowView->IsVisible( m_DisplayXPosition, m_DisplayYPosition, 
		m_DisplayXPosition + m_DisplayWidth, m_DisplayYPosition + m_DisplayHeight)
	) {
		if ( tRowView == spRowView ) {
			// Subtract Rect
			if ( tXPosition < stXPosition && tXSize > stXSize) {
				tXPosition = stXPosition;
				tXSize = stXSize;
			}
			if ( tYPosition < stYPosition && tYSize > stYSize) {
				tYPosition = stYPosition;
				tYSize = stYSize;
			}
			if ( pDoc->m_UserVars.m_ShowTail ) {
				// tRect.UnionRect ( tRect, sTailRect );
				if ( tXPosition > sTailXPosition ) tXPosition = sTailXPosition;
				if ( tXSize < sTailXSize ) tXSize = sTailXSize;
			}
		}
		InvalidateRectLP( tXPosition, tYPosition, tXPosition + tXSize, tYPosition + tYSize);
	}			

	if ( tRowView != spRowView ) {
		spRowView->GetPosition(&tXPosition, &tYPosition);
		spRowView->GetSize(&tXSize, &tYSize);
		if ( spRowView->IsVisible( m_DisplayXPosition, m_DisplayYPosition, 
			m_DisplayXPosition + m_DisplayWidth, m_DisplayYPosition + m_DisplayHeight)
		) {
			if ( tXPosition < stXPosition && tXSize > stXSize) {
				tXPosition = stXPosition;
				tXSize = stXSize;
			}
			if ( tYPosition < stYPosition && tYSize > stYSize) {
				tYPosition = stYPosition;
				tYSize = stYSize;
			}
			if ( pDoc->m_UserVars.m_ShowTail ) {
				// tRect.UnionRect ( tRect, sTailRect );
				if ( tXPosition > sTailXPosition ) tXPosition = sTailXPosition;
				if ( tXSize < sTailXSize ) tXSize = sTailXSize;
			}
			InvalidateRectLP( tXPosition, tYPosition, tXPosition + tXSize, tYPosition + tYSize);
		}
	}

		
	if ( tTotalHeight != m_TotalHeight ) {

		m_ExpandedResize = 1;

	}
	
}


//
//
//   UPDATE
//

void CGenedocView::OnUpdate ( CView* pSender, LPARAM lHint, CObject *pHint )
{
	if ( !m_InitialUpdateDone ) return;

	SetScrollVariables();
	
	SetScrollBars();

	CView::OnUpdate( pSender, lHint, pHint );

}


void 
CGenedocView::SetScrollVariables()
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
			m_CharWidth, 
			m_LineHeight, 
			8 * m_CharWidth, 
			m_PageScrollHeight
		);

	}

	// If its a new opened file, scroll back to the top ..
	if ( m_FileOpenFlag == 1 ) { 
		m_DisplayXPosition = 0;
		m_DisplayYPosition = 0;

		m_FileOpenFlag = 0;
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

	CaretXPos /= m_CharWidth;
	CaretXPos *= m_CharWidth;
		
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
CGenedocView::SetScrollBars()
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


void CGenedocView::OnInitialUpdate()
{

	m_DisplayXPosition = 0;
	m_DisplayYPosition = 0;


	CView::OnInitialUpdate();

	ClearMenu();

	m_InitialUpdateDone = TRUE;
	

	m_SelectDevice = NONE;
	m_CopyFlag = 0;

	((CMDIChildWnd *)GetParentFrame())->MDIMaximize();

	if ( GetDocument()->m_UserVars.m_SumDefDis && !GetDocument()->m_SummaryMessaged ) {
		GetDocument()->m_SummaryMessaged = 1;
		PostMessage( WM_COMMAND, IDM_SUMMARYVIEW );
	}

}

void CGenedocView::OnDraw(CDC* pDC)
{
	// A repaint comes before end of printing.
	if ( m_PrintOnly )
		if ( !pDC->IsPrinting() )
			return;

	DoDraw(pDC, TRUE, FALSE);

}

void CGenedocView::DoDraw(CDC* pDC, int InvFlag1, int InvFlag2 )
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
		AfxMessageBox("genedvw:CreateFont:Fail:1");
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


void CGenedocView::OnSize(UINT nType, int cx, int cy) 
{
	if ( m_InitialUpdateDone ) {

		m_MyCaret.SetViewSize ( (UINT)cx, (DWORD)cy );
			
		OnUpdate( NULL, 0L, NULL );
		
	}

	CView::OnSize(nType, cx, cy);
}


/////////////////////////////////////////////////////////////////////////////
// CGenedocView printing
extern char	*MSFFILEmonths[];

  
void CGenedocView::OnPrint( CDC *pDC, CPrintInfo *pInfo )
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

			char Buff[1024];
			char bExtra0[1024];
			char bExtra1[1024];
			bExtra0[0] = 0;
			bExtra1[0] = 0;
			if ( pDoc->m_UserVars.m_PrintFileName ) {
				sprintf ( bExtra0, "%s", pDoc->ConvertPathname( ".msf" ) );
			}
			if ( pDoc->m_UserVars.m_PrintDate ) {
#ifdef _WIN32
				SYSTEMTIME LocTime;
#else
				time_t	cur;		/*	Current time	*/
				struct tm	*cur_tm;	/*	Time struct	*/
#endif

#ifdef _WIN32
				GetLocalTime ( &LocTime );
				sprintf(bExtra1, "%s %d, %d  %02d:%02d", MSFFILEmonths[LocTime.wMonth - 1],
					LocTime.wDay, LocTime.wYear, LocTime.wHour,	LocTime.wMinute );
#else
				cur = time(NULL);
				cur_tm = localtime(&cur);
				sprintf(bExtra1, "%s %d, %d  %02d:%02d", MSFFILEmonths[cur_tm->tm_mon],
					cur_tm->tm_mday, cur_tm->tm_year + 1900, cur_tm->tm_hour,
					cur_tm->tm_min);
#endif
			}

			sprintf(Buff, "%d %s %s", pInfo->m_nCurPage + pDoc->m_UserVars.m_PrintPageOffset, bExtra0, bExtra1 );
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

			char Buff[1024];
			char bExtra0[1024];
			char bExtra1[1024];
			bExtra0[0] = 0;
			bExtra1[0] = 0;
			if ( pDoc->m_UserVars.m_PrintFileName ) {
				sprintf ( bExtra0, "%s", pDoc->ConvertPathname( ".msf" ) );
			}
			if ( pDoc->m_UserVars.m_PrintDate ) {
#ifdef _WIN32
				SYSTEMTIME LocTime;
#else
				time_t	cur;		/*	Current time	*/
				struct tm	*cur_tm;	/*	Time struct	*/
#endif

#ifdef _WIN32
				GetLocalTime ( &LocTime );
				sprintf(bExtra1, "%s %d, %d  %02d:%02d", MSFFILEmonths[LocTime.wMonth - 1],
					LocTime.wDay, LocTime.wYear, LocTime.wHour,	LocTime.wMinute );
#else
				cur = time(NULL);
				cur_tm = localtime(&cur);
				sprintf(bExtra1, "%s %d, %d  %02d:%02d", MSFFILEmonths[cur_tm->tm_mon],
					cur_tm->tm_mday, cur_tm->tm_year + 1900, cur_tm->tm_hour,
					cur_tm->tm_min);
#endif
			}

			sprintf(Buff, "%d %s %s", pInfo->m_nCurPage + pDoc->m_UserVars.m_PrintPageOffset, bExtra0, bExtra1 );
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
CGenedocView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{

	CView::OnPrepareDC ( pDC, pInfo );

	if ( pInfo != NULL ) {

		pDC->SetViewportOrg( m_LeftView, m_TopView );
	
	}

}


BOOL CGenedocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void 
CGenedocView::CalculateMargins(CDC* pDC)
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
 

void CGenedocView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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


void CGenedocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo */)
{
	m_DisplayXPosition = m_SaveDisplayXPosition;
	m_DisplayYPosition = m_SaveDisplayYPosition;
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGenedocView diagnostics

#ifdef _DEBUG
void CGenedocView::AssertValid() const
{
	CView::AssertValid();
}

void CGenedocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGenedocDoc* CGenedocView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	return (CGenedocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenedocView message handlers

	

void CGenedocView::OnDestroy() 
{
	CleanRowViewList();

	CView::OnDestroy();

}

int CGenedocView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_pGeneView = this;

	m_InitialUpdateDone = FALSE;
	
	return 0;
}


void CGenedocView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	DestroyCaret();
	// TODO: Add your message handler code here
}

void CGenedocView::OnSetFocus(CWnd* pOldWnd) 
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
CGenedocView::RebuildShowCaret()
{

	if ( m_GeneEditMode == 0 ) {
		CreateSolidCaret( 2, (int)m_LineHeight );
	} else {
		CreateSolidCaret( m_CharWidth, (int)m_LineHeight );
	}

	ShowCaret();

//	TRACE( "ShowCaret\n");
	
	m_MyCaret.CaretPos();
}


void CGenedocView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_MyCaret.OnKeyDown ( nChar, nRepCnt, nFlags, this);
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGenedocView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_MyCaret.OnKeyUp ( nChar, nRepCnt, nFlags, this);
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void 
CGDocViewCaret::Select( UINT XPosition, DWORD YPosition, CView* pView )
{

	CGenedocView* pGEView = (CGenedocView*)pView;

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


void 
CGenedocView::InvalidateRectLP(UINT tXPosition, DWORD tYPosition, UINT tXSize, DWORD tYSize )
{
	CRect InvRect( 
		tXPosition - m_DisplayXPosition, (int)(tYPosition - m_DisplayYPosition), 
		tXPosition + tXSize - m_DisplayXPosition, (int)(tYPosition + tYSize - m_DisplayYPosition)
	);
	InvalidateRect( InvRect, FALSE );

}

void 
CGenedocView::InvalidateGVBLP( CGeneViewBase *pGVB )
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

BOOL CGenedocView::IsVisible( UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize )
{
	if ( (YPosition+YSize)>=m_DisplayYPosition && YPosition<=(m_DisplayYPosition+m_DisplayHeight) ) {
		if ( (XPosition+XSize)>=m_DisplayXPosition && XPosition<=(m_DisplayXPosition+m_DisplayWidth) ) {
			return TRUE;
		}
	}
	return FALSE;
}


void 
CGenedocView::DeSelectAll()
{
	if ( m_GeneSelect == 1 ) {
		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPRowView* tGP;
	
		CClientDC dc(this);
		OnPrepareDC(&dc);
	
		while ( tPos != NULL ) {
			tGP = (CGPRowView* )m_RowViewList.GetNext(tPos);
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



int  
CGDocViewCaret::Comment( char nChar, UINT XPosition, DWORD YPosition, CView* pView )
{

	CGenedocView* pGEView = (CGenedocView*)pView;

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
CGDocViewCaret::InsKey( UINT XPosition, DWORD YPosition, CView* pView )
{
	int sGeneShade = ((CGenedocView *)pView)->m_GeneShade;
	int sGeneArrange = ((CGenedocView *)pView)->m_GeneArrange;
	int sGeneMove = ((CGenedocView *)pView)->m_GeneMove;
	int sGeneInsertDash = ((CGenedocView *)pView)->m_GeneInsertDash;
	int sGeneDeleteDash = ((CGenedocView *)pView)->m_GeneDeleteDash;
	int sGeneInsertOther = ((CGenedocView *)pView)->m_GeneInsertOther;
	int sGeneDeleteOther = ((CGenedocView *)pView)->m_GeneDeleteOther;
	int sGeneInsertOne = ((CGenedocView *)pView)->m_GeneInsertOne;
	int sGeneDeleteOne = ((CGenedocView *)pView)->m_GeneDeleteOne;
	int sGeneEditMode = ((CGenedocView *)pView)->m_GeneEditMode;

	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));
	((CGenedocView *)pView)->m_GeneShade = 0;
	((CGenedocView *)pView)->m_GeneArrange = 0;
	((CGenedocView *)pView)->m_GeneMove = 0;
	((CGenedocView *)pView)->m_GeneInsertDash = 0;
	((CGenedocView *)pView)->m_GeneDeleteDash = 0;
	((CGenedocView *)pView)->m_GeneInsertOther = 0;
	((CGenedocView *)pView)->m_GeneDeleteOther = 0;
	((CGenedocView *)pView)->m_GeneInsertOne = 0;
	((CGenedocView *)pView)->m_GeneDeleteOne = 0;
	((CGenedocView *)pView)->m_GeneEditMode = 0;

	((CGenedocView *)pView)->m_GeneInsertDash = 1;

	((CGenedocView *)pView)->LeftDownFunc( 0, tPoint, CGenedocView::KEYBRD );

	((CGenedocView *)pView)->m_GeneShade = sGeneShade;
	((CGenedocView *)pView)->m_GeneArrange = sGeneArrange;
	((CGenedocView *)pView)->m_GeneMove = sGeneMove;
	((CGenedocView *)pView)->m_GeneInsertDash = sGeneInsertDash;
	((CGenedocView *)pView)->m_GeneDeleteDash = sGeneDeleteDash;
	((CGenedocView *)pView)->m_GeneInsertOther = sGeneInsertOther;
	((CGenedocView *)pView)->m_GeneDeleteOther = sGeneDeleteOther;
	((CGenedocView *)pView)->m_GeneInsertOne = sGeneInsertOne;
	((CGenedocView *)pView)->m_GeneDeleteOne = sGeneDeleteOne;
	((CGenedocView *)pView)->m_GeneEditMode = sGeneEditMode;

}

void 
CGDocViewCaret::DelKey( UINT XPosition, DWORD YPosition, CView* pView )
{
	int sGeneShade = ((CGenedocView *)pView)->m_GeneShade;
	int sGeneArrange = ((CGenedocView *)pView)->m_GeneArrange;
	int sGeneMove = ((CGenedocView *)pView)->m_GeneMove;
	int sGeneInsertDash = ((CGenedocView *)pView)->m_GeneInsertDash;
	int sGeneDeleteDash = ((CGenedocView *)pView)->m_GeneDeleteDash;
	int sGeneInsertOther = ((CGenedocView *)pView)->m_GeneInsertOther;
	int sGeneDeleteOther = ((CGenedocView *)pView)->m_GeneDeleteOther;
	int sGeneInsertOne = ((CGenedocView *)pView)->m_GeneInsertOne;
	int sGeneDeleteOne = ((CGenedocView *)pView)->m_GeneDeleteOne;
	int sGeneEditMode = ((CGenedocView *)pView)->m_GeneEditMode;

	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));
	((CGenedocView *)pView)->m_GeneShade = 0;
	((CGenedocView *)pView)->m_GeneArrange = 0;
	((CGenedocView *)pView)->m_GeneMove = 0;
	((CGenedocView *)pView)->m_GeneInsertDash = 0;
	((CGenedocView *)pView)->m_GeneDeleteDash = 0;
	((CGenedocView *)pView)->m_GeneInsertOther = 0;
	((CGenedocView *)pView)->m_GeneDeleteOther = 0;
	((CGenedocView *)pView)->m_GeneInsertOne = 0;
	((CGenedocView *)pView)->m_GeneDeleteOne = 0;
	((CGenedocView *)pView)->m_GeneEditMode = 0;

	((CGenedocView *)pView)->m_GeneDeleteDash = 1;

	((CGenedocView *)pView)->LeftDownFunc( 0, tPoint, CGenedocView::KEYBRD );

	((CGenedocView *)pView)->m_GeneShade = sGeneShade;
	((CGenedocView *)pView)->m_GeneArrange = sGeneArrange;
	((CGenedocView *)pView)->m_GeneMove = sGeneMove;
	((CGenedocView *)pView)->m_GeneInsertDash = sGeneInsertDash;
	((CGenedocView *)pView)->m_GeneDeleteDash = sGeneDeleteDash;
	((CGenedocView *)pView)->m_GeneInsertOther = sGeneInsertOther;
	((CGenedocView *)pView)->m_GeneDeleteOther = sGeneDeleteOther;
	((CGenedocView *)pView)->m_GeneInsertOne = sGeneInsertOne;
	((CGenedocView *)pView)->m_GeneDeleteOne = sGeneDeleteOne;
	((CGenedocView *)pView)->m_GeneEditMode = sGeneEditMode;

}

void 
CGDocViewCaret::LeftDown( UINT XPosition, DWORD YPosition, CView* pView )
{

	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));
	((CGenedocView *)pView)->LeftDownFunc( 0, tPoint, CGenedocView::KEYBRD );

}

void 
CGDocViewCaret::RightDown( UINT XPosition, DWORD YPosition, CView* pView )
{

	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));

	((CGenedocView *)pView)->RightDownFunc( 0, tPoint, CGenedocView::KEYBRD );

}

void 
CGenedocView::LeftDownFunc( UINT nFlags, CPoint point, int DDevice )
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

		
	m_ExpandedResize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);

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

				if ( (ViewRet.MenuFunc == DEF_GENEINSERTDASH)
					|| (ViewRet.MenuFunc == DEF_GENEDELETEDASH) 
					|| (ViewRet.MenuFunc == DEF_GENEINSERTOTHER) 
					|| (ViewRet.MenuFunc == DEF_GENEDELETEOTHER) 
					|| (ViewRet.MenuFunc == DEF_GENEINSERTONE) 
				) {
					GetDocument()->SetModifiedFlag();     // Modfied!

					if ( ViewRet.Expanded ) {
						ExpandedSegments(&ViewRet);
						if ( m_ExpandedResize ) {
							
							SetScrollBars();

						}
					}
				} else if ( ViewRet.MenuFunc == DEF_GENEARRANGE 
					|| ViewRet.MenuFunc == DEF_GENEMOVE 
					|| ViewRet.MenuFunc == DEF_SHADE 
				) {
					// Here we are grabbing and dragging
					if ( ViewRet.Clip ) {
	
						if ( DDevice == MOUSE ) {
		
							CRect ClipRect(
								(int)(ViewRet.ClipXPosition - m_DisplayXPosition), 
								(int)(ViewRet.ClipYPosition - m_DisplayYPosition), 
								(int)(ViewRet.ClipXPosition - m_DisplayXPosition + ViewRet.ClipXSize), 
								(int)(ViewRet.ClipYPosition - m_DisplayYPosition + ViewRet.ClipYSize)
							);

					        // ClipCursor
					        CRect WindowRect;
					        
					        // Check for additional Clipping.
					        GetClientRect( &WindowRect );
							if ( WindowRect.BottomRight().x < ClipRect.BottomRight().x ) {
								ClipRect.BottomRight().x = WindowRect.BottomRight().x;
							}
	
							// Get correct screen position
							GetWindowRect( &WindowRect );
							ClipRect = ClipRect + WindowRect.TopLeft();
			
							ClipCursor ( ClipRect );
							
						} else {

							ViewRet.ClipXPosition -= VIEW_CLIP_LEFT;
							ViewRet.ClipXSize += VIEW_CLIP_RIGHT;

							m_MyCaret.ClipCaret( 1, 
								ViewRet.ClipXPosition, 
								ViewRet.ClipYPosition, 
								ViewRet.ClipXSize, 
								ViewRet.ClipYSize 
							);


						}
						SetCapture();
						m_SelectDevice = DDevice;
					}
					if ( ViewRet.MenuFunc == DEF_SHADE ) {
						// Special Flag set in CGEdit
						if ( !ViewRet.Expanded ) {
							SetCapture();
							m_SelectDevice = DDevice;
						}
					}
				} else if ( ViewRet.MenuFunc == DEF_GENEEDITMODE ) {
					// follow the mouse man!
					m_MyCaret.FollowMouse( PointXPosition, PointYPosition );
				}
			}
		}
	}
}

void 
CGDocViewCaret::Move( UINT XPosition, DWORD YPosition, CView* pView )
{
	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));
	((CGenedocView*)pView)->MoveFunc( 0, tPoint, CGenedocView::KEYBRD );
}

void
CGenedocView::AdjustEndToPoint( CGPRowView *tGP, UINT PointXPosition, DWORD PointYPosition, CView *pWnd )
{
	CGPRowView* cGP;
	CGPRowView* nGP;

	POSITION tPos;
	
	if ( m_EndSelect != tGP->GetEnum() ) {

		UINT nEnd = tGP->GetEnum();
		while ( m_EndSelect != nEnd ) {

			if ( nEnd < m_EndSelect ) {

				cGP = (CGPRowView *)m_RowViewList.GetPrev(m_EndPos);

				// copy to a temp work 
				tPos = m_EndPos;
				// Get the real next one
				nGP = (CGPRowView *)m_RowViewList.GetPrev(tPos);

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

				cGP = (CGPRowView *)m_RowViewList.GetNext(m_EndPos);
				// Copy position to a temp work
				tPos = m_EndPos;
				// Get the real next one
				nGP = (CGPRowView *)m_RowViewList.GetNext(tPos);

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
CGenedocView::MoveFunc(UINT nFlags, CPoint point, int DDevice) 
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
		CGPRowView *tGP;

		while ( tPos != NULL ) {
			tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
			if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
				if ( ViewRet.MenuFunc == DEF_GENESELECT ) {
					AdjustEndToPoint( tGP, PointXPosition, PointYPosition, this );
				} else {
					tGP->OnMouseMove(nFlags, PointXPosition, PointYPosition, this, &ViewRet );
					
					if ( ViewRet.MenuFunc == DEF_GENEARRANGE 
						|| ViewRet.MenuFunc == DEF_GENEARRANGE 
					) {
						GetDocument()->SetModifiedFlag();     // Modfied!
					}

					m_ColSelStart = ViewRet.ColSelStart;
					m_ColSelEnd = ViewRet.ColSelEnd;

				}
				break;
			}
		}

		if ( ViewRet.Expanded ) {
			ExpandedSegments(&ViewRet);

			if ( ViewRet.Clip ) {
				if ( DDevice == MOUSE ) {

					CRect ClipRect(
						(int)(ViewRet.ClipXPosition - m_DisplayXPosition), 
						(int)(ViewRet.ClipYPosition - m_DisplayYPosition), 
						(int)(ViewRet.ClipXPosition - m_DisplayXPosition + ViewRet.ClipXSize), 
						(int)(ViewRet.ClipYPosition - m_DisplayYPosition + ViewRet.ClipYSize)
					);

					// ClipCursor
			        CRect WindowRect;

			        // Check for additional Clipping.
			        GetClientRect( &WindowRect );
					if ( WindowRect.BottomRight().x < ClipRect.BottomRight().x ) {
						ClipRect.BottomRight().x = WindowRect.BottomRight().x;
					}

					GetWindowRect( &WindowRect );
					ClipRect = ClipRect + WindowRect.TopLeft();
					ClipCursor ( ClipRect );
				} else {
					m_MyCaret.ClipCaret( 1, 
						ViewRet.ClipXPosition, 
						ViewRet.ClipYPosition, 
						ViewRet.ClipXSize, 
						ViewRet.ClipYSize
					);
				}
			}
		}
	}


// for status bar updates

	int PointXPosition;
	DWORD PointYPosition;

	PointXPosition = point.x + m_DisplayXPosition;
	PointYPosition = (DWORD)point.y + m_DisplayYPosition;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
		if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
			tGP->SetStatusBar(nFlags, PointXPosition, PointYPosition );
			break;
		}
	}

	
}


void 
CGDocViewCaret::LeftUp( UINT XPosition, DWORD YPosition, CView* pView )
{

	CPoint tPoint ( (int)(XPosition - ((CGenedocView*)pView)->m_DisplayXPosition), (int)(YPosition - ((CGenedocView*)pView)->m_DisplayYPosition));
	((CGenedocView*)pView)->LeftUpFunc( 0, tPoint, CGenedocView::KEYBRD );
}

void CGenedocView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void CGenedocView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		if ( m_DisplayXPosition + m_CharWidth > m_TotalWidth - m_DisplayWidth ) 
			m_DisplayXPosition = m_TotalWidth - m_DisplayWidth;
		else 
			m_DisplayXPosition += m_CharWidth;
		break;
	case SB_LINEUP:
		if ( m_DisplayXPosition >= m_CharWidth ) 
			m_DisplayXPosition -= m_CharWidth;
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



void CGenedocView::ScrollToPosition ( UINT ScrollXPosition, DWORD ScrollYPosition )
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

void CGenedocView::GetScrollPosition( UINT *ScrollXPosition, DWORD *ScrollYPosition)
{
	*ScrollXPosition = m_DisplayXPosition;
	*ScrollYPosition = m_DisplayYPosition;
}


void CGenedocView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RightDownFunc( nFlags, point, MOUSE );
	
	CView::OnRButtonDblClk(nFlags, point);
}

void CGenedocView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RightDownFunc( nFlags, point, MOUSE );

	CView::OnRButtonDown(nFlags, point);
}

void CGenedocView::RightDownFunc( UINT nFlags, CPoint point, int DDevice )
{
	int MenuFunc = GetMenuFunction();
	if ( MenuFunc == DEF_GENEINSERTDASH 
		|| MenuFunc == DEF_GENEDELETEDASH 
		|| MenuFunc == DEF_GENEINSERTOTHER
		|| MenuFunc == DEF_GENEDELETEOTHER 
		|| MenuFunc == DEF_GENEINSERTONE 
		|| MenuFunc == DEF_GENEDELETEONE 
	) {
		int sGeneShade = m_GeneShade;
		int sGeneArrange = m_GeneArrange;
		int sGeneMove = m_GeneMove;
		int sGeneInsertDash = m_GeneInsertDash;
		int sGeneDeleteDash = m_GeneDeleteDash;
		int sGeneInsertOther = m_GeneInsertOther;
		int sGeneDeleteOther = m_GeneDeleteOther;
		int sGeneInsertOne = m_GeneInsertOne;
		int sGeneDeleteOne = m_GeneDeleteOne;

		m_GeneShade = 0;
		m_GeneArrange = 0;
		m_GeneMove = 0;
		m_GeneInsertDash = 0;
		m_GeneDeleteDash = 0;
		m_GeneInsertOther = 0;
		m_GeneDeleteOther = 0;
		m_GeneInsertOne = 0;
		m_GeneDeleteOne = 0;

		switch( MenuFunc) {
		case DEF_GENEINSERTDASH:
			m_GeneDeleteDash = 1;
			break;
		case DEF_GENEDELETEDASH:
			m_GeneInsertDash = 1;
			break;
		case DEF_GENEINSERTOTHER:
			m_GeneDeleteOther = 1;
			break;
		case DEF_GENEDELETEOTHER:
			m_GeneInsertOther = 1;
			break;
		case DEF_GENEINSERTONE:
			m_GeneDeleteOne = 1;
			break;
		case DEF_GENEDELETEONE:
			m_GeneInsertOne = 1;
			break;
		}

		LeftDownFunc ( nFlags, point, DDevice );
		// LeftDownFunc( 0, tPoint, KEYBRD );

		m_GeneShade = sGeneShade;
		m_GeneArrange = sGeneArrange;
		m_GeneMove = sGeneMove;
		m_GeneInsertDash = sGeneInsertDash;
		m_GeneDeleteDash = sGeneDeleteDash;
		m_GeneInsertOther = sGeneInsertOther;
		m_GeneDeleteOther = sGeneDeleteOther;
		m_GeneInsertOne = sGeneInsertOne;
		m_GeneDeleteOne = sGeneDeleteOne;

	}
}

void CGenedocView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LeftDownFunc ( nFlags, point, MOUSE );

	CView::OnLButtonDown(nFlags, point);
}

void CGenedocView::OnMouseMove(UINT nFlags, CPoint point) 
{
	MoveFunc( nFlags, point, MOUSE);
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}

void CGenedocView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LeftUpFunc(nFlags, point, MOUSE);
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}


#ifdef _MAC

void 
CGenedocView::ClipCursor(const CRect& cRect )
{
	m_ClipFuncClipFunc = TRUE;
	m_ClipFuncClipRect = cRect;
}

void 
CGenedocView::ClipCursor(const int iVal )
{
	m_ClipFuncClipFunc = FALSE;
}

BOOL 
CGenedocView::CheckClipCursor(const CPoint& point )
{
	if ( m_ClipFuncClipFunc == TRUE ) {
		CRect WindowRect;
		GetWindowRect( &WindowRect );
		return m_ClipFuncClipRect.PtInRect( point + WindowRect.TopLeft() );
	}

	return TRUE;
}


#endif

void CGenedocView::LeftUpFunc(UINT nFlags, CPoint point, int DDevice) 
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
		CGPRowView *tGP;
	
		while ( tPos != NULL ) {
			tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
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

		if ( ViewRet.Expanded ) {
			ExpandedSegments(&ViewRet);
		}
		
		if ( m_ExpandedResize ) {

			SetScrollBars();

		}

#ifdef _MAC
NoPoint:
#endif
		ReleaseCapture();
		ClipCursor ( NULL );
		m_MyCaret.ClipCaret( 0 );
		m_SelectDevice = NONE;
	}
}

void 
CGenedocView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	int MenuFunc = GetMenuFunction();

	if ( MenuFunc == DEF_GENESELECT || MenuFunc == DEF_GENESELECTCOL ) {

		UINT PointXPosition;
		DWORD PointYPosition;

		PointXPosition = point.x + m_DisplayXPosition;
		PointYPosition = (DWORD)point.y + m_DisplayYPosition;

		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPRowView *tGP;
	
		DeSelectAll();
	
		while ( tPos != NULL ) {
	
			tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
	
			if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {
				tGP->OnLButtonDblClk(nFlags, PointXPosition, PointYPosition, this );
			}
		}
		
		// All done here!
		return;
	}

	// Check for doubleclick on a score line
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	UINT PointXPosition;
	DWORD PointYPosition;

	PointXPosition = point.x + m_DisplayXPosition;
	PointYPosition = (DWORD)point.y + m_DisplayYPosition;


	while ( tPos != NULL ) {
	
		tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
	
		if ( tGP->IsPointWithin( PointXPosition, PointYPosition ) ) {

			UINT tXPosition;
			DWORD tYPosition;
			UINT tXSize;
			DWORD tYSize;

			tGP->GetPosition(&tXPosition, &tYPosition);
			tGP->GetSize(&tXSize, &tYSize);
			tYSize = tYPosition + (DWORD)m_LineHeight;
			if ( (PointXPosition >= tXPosition && PointXPosition < (tXPosition + tXSize)) 
				&&
				(PointYPosition >= tYPosition && PointYPosition < (tYPosition + tYSize))
			) {
				if ( tGP->ReScoreFunction( PointXPosition, PointYPosition, this ) ) {
					return;
				}
			}
			break;
		}
	}

	if ( (MenuFunc == DEF_GENEINSERTDASH)
		|| (MenuFunc == DEF_GENEDELETEDASH) 
		|| (MenuFunc == DEF_GENEINSERTOTHER) 
		|| (MenuFunc == DEF_GENEDELETEOTHER) 
		|| (MenuFunc == DEF_GENEINSERTONE) 
		|| (MenuFunc == DEF_GENEDELETEONE) 
	) {

		PointXPosition -= m_DisplayXPosition;
		PointYPosition -= m_DisplayYPosition;

		LeftDownFunc( nFlags, point, MOUSE );
		
	} else {

		m_MyCaret.FollowMouse( PointXPosition, PointYPosition );
		// For find again ..	
		CGenedocDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->m_pFS.PrevSeq = -1;
	}

	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDblClk(nFlags, point);
}


void 
CGenedocView::CheckMoveRanges( CGeneSegment *pCGSeg, int Row )
{

	// TODO: add draw code for native data here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Do score pre inval function
	int InvScore = 0;
	DWORD tStartRange = pCGSeg->m_StartRange;
	DWORD tEndRange = pCGSeg->m_EndRange;
	

	int RowCount = pDoc->pGSFiller->SegDataList.GetCount();
	
	if ( (Row != 0 ) && (Row != 1) && (Row != (RowCount - 1)) ) {
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		InvScore = tGSeg->InvalScore( &tStartRange, &tEndRange );
	}


	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGPRV;
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		tGPRV->CheckMoveRanges( this, pCGSeg, Row, InvScore, tStartRange, tEndRange );
	}
}


void 
CGenedocView::InvalNewEndPoint( DWORD Range1, DWORD Range2)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGPRV;
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		tGPRV->InvalNewEndPoint( this, Range1, Range2);
	}
}


void
CGenedocView::ClearMenu()
{
	m_GeneShade = 0;
	m_GeneArrange = 0;
	m_GeneMove = 0;
	m_GeneInsertDash = 0;
	m_GeneDeleteDash = 0;
	m_GeneInsertOther = 0;
	m_GeneDeleteOther = 0;
	m_GeneInsertOne = 0;
	m_GeneDeleteOne = 0;
	m_GeneSelect = 0;
	m_GeneSelectCol = 0;
	
	if ( m_GeneEditMode == 1 ) {
		m_GeneEditMode = 0;
		DestroyCaret();
		RebuildShowCaret();
	}
	m_GeneEditMode = 0;

	m_ShadeLevel = 0;
}

unsigned int 
CGenedocView::GetMenuFunction()
{
	int ret = 0;
	ret += m_GeneShade * DEF_SHADE;
	ret += m_GeneArrange * DEF_GENEARRANGE;
	ret += m_GeneMove * DEF_GENEMOVE;
	ret += m_GeneInsertDash * DEF_GENEINSERTDASH;
	ret += m_GeneDeleteDash * DEF_GENEDELETEDASH;
	ret += m_GeneInsertOther * DEF_GENEINSERTOTHER;
	ret += m_GeneDeleteOther  * DEF_GENEDELETEOTHER;
	ret += m_GeneInsertOne * DEF_GENEINSERTONE;
	ret += m_GeneDeleteOne * DEF_GENEDELETEONE;
	ret += m_GeneSelect * DEF_GENESELECT;
	ret += m_GeneSelectCol * DEF_GENESELECTCOL;
	ret += m_GeneEditMode * DEF_GENEEDITMODE;

	return ret;
}

void CGenedocView::OnGenearrange() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneArrange == 0 ) {
		ClearMenu();
		m_GeneArrange = 1;
	} else {
		m_GeneArrange = 0;
	}
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGenearrange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneArrange );
	
}

void CGenedocView::OnGenemove() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneMove == 0 ) {
		ClearMenu();
		m_GeneMove = 1;
	} else {
		m_GeneMove = 0;
	}
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGenemove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneMove );
	
}

void CGenedocView::OnSelect() 
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

void CGenedocView::OnUpdateSelect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneSelect );
}

void CGenedocView::OnGenedeletedash()
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneDeleteDash == 0 ) {
		ClearMenu();
		m_GeneDeleteDash = 1;
	} else {
		m_GeneDeleteDash = 0;
	}
	Invalidate(FALSE);
	
}

void CGenedocView::OnUpdateGenedeletedash(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneDeleteDash );
}

void CGenedocView::OnGeneinsertdash()
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneInsertDash == 0 ) {
		ClearMenu();
		m_GeneInsertDash = 1;
	} else {
		m_GeneInsertDash = 0;
	}
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGeneinsertdash(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneInsertDash );
	
}


void CGenedocView::OnGeneinsertother() 
{
	// TODO: Add your command handler code here
	
	DeSelectAll();
	if ( m_GeneInsertOther == 0 ) {
		ClearMenu();
		m_GeneInsertOther = 1;
	} else {
		m_GeneInsertOther = 0;
	}
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGeneinsertother(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneInsertOther );
	
}

void CGenedocView::OnGenedeleteother() 
{
	// TODO: Add your command handler code here
	
	DeSelectAll();
	if ( m_GeneDeleteOther == 0 ) {
		ClearMenu();
		m_GeneDeleteOther = 1;
	} else {
		m_GeneDeleteOther = 0;
	}
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGenedeleteother(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneDeleteOther );
}

void CGenedocView::OnGeneinsertone() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneInsertOne == 0 ) {
		ClearMenu();
		m_GeneInsertOne = 1;
	} else {
		m_GeneInsertOne = 0;
	}
	Invalidate(FALSE);
	
}

void CGenedocView::OnUpdateGeneinsertone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneInsertOne );
}

void CGenedocView::OnGenedeleteone() 
{
	// TODO: Add your command handler code here
	DeSelectAll();
	if ( m_GeneDeleteOne == 0 ) {
		ClearMenu();
		m_GeneDeleteOne = 1;
	} else {
		m_GeneDeleteOne = 0;
	}
	Invalidate(FALSE);
	
}

void CGenedocView::OnUpdateGenedeleteone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneDeleteOne );
	
}
//
// SHADING
//
void CGenedocView::OnSelectcol() 
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
	Invalidate(FALSE);
	
}

void CGenedocView::OnUpdateSelectcol(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneSelectCol );
}

void CGenedocView::OnGenecreatewin() 
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
		AfxMessageBox( "Genedvw:new:fail:19" );
		return;
	}

	// Put the data rows on the list

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		
		CGeneSegment *tnCGSeg = new CGeneSegment();
		if ( tnCGSeg == 0 ) {
			AfxMessageBox( "Genedvw:new:fail:20" );
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
			AfxMessageBox( "Genedvw:new:fail:22" );
			return;
		}
		pnGSFiller->AddHeader( tStr );
	}

	pnDoc->CopyGSFiller( pnGSFiller );
	
//	pnDoc->CopyUserVars( &pnDoc->m_UserVars, &pDoc->m_UserVars );	// To <- From

	pnDoc->ParseTree( pDoc->m_UserVars.m_ParseString, 0 );

	pnDoc->GetUserDefaults();	// To <- From

	pnDoc->AutoShade(-1);
}

void CGenedocView::OnUpdateGenecreatewin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}

void CGenedocView::OnGenescorekey()
{

	// TODO: Add your command handler code here
	if ( !m_ColSelBegin ) {
		UINT XPoint;
		DWORD YPoint;
		m_MyCaret.GetPosition(&XPoint, &YPoint);


		// Check for doubleclick on a score line
		POSITION tPos = m_RowViewList.GetHeadPosition();
		CGPRowView *tGP;
	
		while ( tPos != NULL ) {
		
			tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);
		
			if ( tGP->IsPointWithin(XPoint, YPoint) ) {
				if ( tGP->ReScoreFunction( XPoint, YPoint, this ) ) {
					return;
				}
				break;
			}
		}
	}

	OnGenescore();	
}


void CGenedocView::OnGenescore() 
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
	

	pDoc->Score ( &StartRange, &EndRange );	
	
	CGeneSegment * tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
	tCGSeg->m_StartRange = StartRange;
	tCGSeg->m_EndRange = EndRange;
	
	CheckMoveRanges( tCGSeg, 0 );

	DeSelectAll();


}

void CGenedocView::OnUpdateGenescore(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
}

void CGenedocView::OnGeneinsertfill()
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
	

	pDoc->InsertFillerRange( StartRange, EndRange );

}

void CGenedocView::OnUpdateGeneinsertfill(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
}

void CGenedocView::OnGenedeletefill()
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
	

	pDoc->DeleteFillerRange( StartRange, EndRange, 0 );

}

void CGenedocView::OnUpdateGenedeletefill(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
}

void 
CGenedocView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
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


void CGenedocView::OnManualshade()
{
	// TODO: Add your command handler code here
	DoManualShade();
}

void 
CGenedocView::DoManualShade()
{
	CGenedocDoc *pDoc = GetDocument();

	CColorBar tDlg(this);	// CDialog

	m_SaveShadeLevels = pDoc->GetNumColors( &pDoc->m_UserVars.m_Vars );
	
	if ( m_ShadeLevel < m_SaveShadeLevels ) {
		tDlg.m_TextColor = m_ShadeTextColor;
		tDlg.m_BackColor = m_ShadeBackColor;
		tDlg.m_ShadeLevel = m_ShadeLevel;
	} else {
		tDlg.m_ShadeLevel = SHADELEVEL0;
		pDoc->GetLevelColors( &pDoc->m_UserVars.m_Vars, 0, &tDlg.m_TextColor, &tDlg.m_BackColor );
	}
	
	ClearMenu();	// As well m_ShadeLevel
	                               
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	m_ShadeLevel = tDlg.m_ShadeLevel;
	m_ShadeTextColor = tDlg.m_TextColor;
	m_ShadeBackColor = tDlg.m_BackColor;
	m_GeneShade = 1;

	Invalidate(FALSE);

}

void CGenedocView::OnUpdateManualshade(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_GeneShade);
	
}

void CGenedocView::OnGeneclearscore()
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// Zero flag is for clearing.
	pDoc->ClearScore();

	// Do score pre inval function
	DWORD tStartRange = 0;
	DWORD tEndRange;
	
	CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
	tEndRange = tGSeg->GetTextLength() - 1;
	
	tGSeg->m_StartRange = tStartRange;
	tGSeg->m_EndRange = tEndRange;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGPRV;
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		tGPRV->CheckMoveRanges( this, tGSeg, 0, 0, 0, 0 );
	}

}


void CGenedocView::OnGeneeditmode()
{
	// TODO: Add your command handler code here

	DeSelectAll();
	
	if ( m_GeneEditMode == 0 ) {
		ClearMenu();
		m_GeneEditMode = 1;
	} else {
		m_GeneEditMode = 0;
	}

	DestroyCaret();
	RebuildShowCaret();
	Invalidate(FALSE);
}

void CGenedocView::OnUpdateGeneeditmode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_GeneEditMode );
	
}

void CGenedocView::OnFilePrint()
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
CGenedocView::OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView )
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

void CGenedocView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	
	m_PrintOnly = 1;

	CView::OnFilePrintPreview();

}



void CGenedocView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 4, 0 );
	
}

void CGenedocView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopyinv() 
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 4, 0 );
	
}

void CGenedocView::OnUpdateEditCopyinv(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopy0()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 0, 0 );
}

void CGenedocView::OnUpdateEditCopy0(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopy8()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 8, 0 );
}

void CGenedocView::OnUpdateEditCopy8(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopyinv0()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 0, 0 );
}

void CGenedocView::OnUpdateEditCopyinv0(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopyinv8()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 8, 0 );
}

void CGenedocView::OnUpdateEditCopyinv8(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopyinvbit()
{
	// TODO: Add your command handler code here
	ClipFunction( 1, 0, 1 );
	
}

void CGenedocView::OnUpdateEditCopyinvbit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnEditCopybit()
{
	// TODO: Add your command handler code here
	ClipFunction( 0, 0, 1 );
	
}

void CGenedocView::OnUpdateEditCopybit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}


//
//
//
//


/* Macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i)   ((i+31)/32*4)

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : DibNumColors(VOID FAR * pv)                                *
 *                                                                          *
 *  PURPOSE    : Determines the number of colors in the DIB by looking at   *
 *               the BitCount filed in the info block.                      *
 *                                                                          *
 *  RETURNS    : The number of colors in the DIB.                           *
 *                                                                          *
 ****************************************************************************/
WORD DibNumColors (VOID FAR * pv)
{
    int                 bits;
    LPBITMAPINFOHEADER  lpbi;
    LPBITMAPCOREHEADER  lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*  With the BITMAPINFO format headers, the size of the palette
     *  is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *  is dependent on the bits per pixel ( = 2 raised to the power of
     *  bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits){
        case 1:
                return 2;
        case 4:
                return 16;
        case 8:
                return 256;
        default:
                /* A 24 bitcount DIB has no color table */
                return 0;
    }
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   :  PaletteSize(VOID FAR * pv)                                *
 *                                                                          *
 *  PURPOSE    :  Calculates the palette size in bytes. If the info. block  *
 *                is of the BITMAPCOREHEADER type, the number of colors is  *
 *                multiplied by 3 to give the palette size, otherwise the   *
 *                number of colors is multiplied by 4.                      *
 *                                                                          *
 *  RETURNS    :  Palette size in number of bytes.                          *
 *                                                                          *
 ****************************************************************************/

WORD PaletteSize (VOID FAR * pv)
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = DibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else
        return (WORD)(NumColors * sizeof(RGBQUAD));
}



HANDLE DibFromBitmap (
    HBITMAP      hbm,
    DWORD            biStyle,
    WORD             biBits,
    HPALETTE     hpal)
{
    BITMAP               bm;
    BITMAPINFOHEADER     bi;
    BITMAPINFOHEADER FAR *lpbi;
    DWORD                dwLen;
    HANDLE               hdib;
    HANDLE               h;
    HDC                  hdc;

    if (!hbm)
        return NULL;

    if (hpal == NULL)
        hpal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

    GetObject(hbm,sizeof(bm),(LPSTR)&bm);

    if (biBits == 0)
        biBits =  bm.bmPlanes * bm.bmBitsPixel;

    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = biBits;
    bi.biCompression        = biStyle;
    bi.biSizeImage          = 0;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = 0;
    bi.biClrImportant       = 0;

    dwLen  = bi.biSize + PaletteSize(&bi);

    hdc = GetDC(NULL);
    hpal = SelectPalette(hdc,hpal,FALSE);
         RealizePalette(hdc);

    hdib = GlobalAlloc(GMEM_FLAG,dwLen);

    if (!hdib){
        SelectPalette(hdc,hpal,FALSE);
        ReleaseDC(NULL,hdc);
        return NULL;
    }

    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    *lpbi = bi;

    /*  call GetDIBits with a NULL lpBits param, so it will calculate the
     *  biSizeImage field for us
     */
    GetDIBits(hdc, hbm, 0L, (UINT)bi.biHeight,
        (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);

    /* If the driver did not fill in the biSizeImage field, make one up */
    if (bi.biSizeImage == 0){
        bi.biSizeImage = WIDTHBYTES((DWORD)bm.bmWidth * biBits) * bm.bmHeight;

        if (biStyle != BI_RGB)
            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
    }

    /*  realloc the buffer big enough to hold all the bits */
    dwLen = bi.biSize + PaletteSize(&bi) + bi.biSizeImage;
    if (h = GlobalReAlloc(hdib,dwLen,GMEM_MOVEABLE))
        hdib = h;
    else{
        GlobalFree(hdib);
        hdib = NULL;

        SelectPalette(hdc,hpal,FALSE);
        ReleaseDC(NULL,hdc);
        return hdib;
    }

    /*  call GetDIBits with a NON-NULL lpBits param, and actualy get the
     *  bits this time
     */
    lpbi = (BITMAPINFOHEADER *)GlobalLock(hdib);

    if (GetDIBits( hdc,
                   hbm,
                   0L,
                   (UINT)bi.biHeight,
                   (LPBYTE)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi),
                   (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS) == 0){
         GlobalUnlock(hdib);
         hdib = NULL;
         SelectPalette(hdc,hpal,FALSE);
         ReleaseDC(NULL,hdc);
         return NULL;
    }

    bi = *lpbi;
    GlobalUnlock(hdib);

    SelectPalette(hdc,hpal,FALSE);
    ReleaseDC(NULL,hdc);
    return hdib;
}




void 
CGenedocView::ClipFunction( int InvFlag, int ResFlag, int BitFlag )
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
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
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

void CGenedocView::OnCopytext()
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( !OpenClipboard() ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	pDoc->BeginWaitCursor(); // Let em know
	
	HANDLE hText;

	DWORD dwCount = 0;
	char *pText;
	

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGPRV;
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		tGPRV->CountCopyText( &dwCount );
	}

	hText = GlobalAlloc( GMEM_FLAG, dwCount + 1 );
	if ( hText == NULL ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox("GlobalAlloc Fails");
		return;
	}
	
	pText = (char *)GlobalLock ( hText );
	if ( pText == NULL ) {
		pDoc->EndWaitCursor(); // Let em know
		AfxMessageBox("GlobalLock Fails");
		GlobalFree(hText);
		return;
	}
	
	dwCount = 0;

	tPos = m_RowViewList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		tGPRV->CopyText( pText, &dwCount, 0 );
	}

	pText[dwCount] = 0;

	GlobalUnlock( hText );
	

	if ( SetClipboardData ( CF_TEXT, hText ) == NULL ) {
		AfxMessageBox( "SetClipboardData Fails" );
	}
	
	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}
	
	pDoc->EndWaitCursor(); // Let em know
	
}

void CGenedocView::OnGenecopypict()
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
	
	CGPRowView *tGPRV;

//	SizeRect.SetRectEmpty();
//	UINT SizeXPosition = (UINT)-1;
//	DWORD SizeYPosition = (DWORD)-1;
	UINT SizeXSize = 0;
	DWORD SizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
		if ( tGPRV->IsSelected() ) {
			UINT tXSize;;
			DWORD tYSize;
			// SizeRect |= tGPRV->GetViewRect();
			tGPRV->GetSize(&tXSize, &tYSize);
			if ( tXSize > SizeXSize ) SizeXSize = tXSize;
			SizeYSize += tYSize;
		}
	}


	
	if ( !tPictFile.PictInit( 
		(int)SizeXSize, 
		(int)(SizeYSize + m_LineHeight), 
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
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		if ( tGPRV->IsSelected() ) {
			tGPRV->WritePict (&tPictFile, 0, pDoc);
		}
	}

	tPictFile.Exit();

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know
	
}


void CGenedocView::OnUpdateGenecopypict(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
}

void CGenedocView::OnGenecopyhtml() 
{
	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "HTML Files (*.htm)|*.htm|All Files (*.*)|*.*||";

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CDocument

	CHTMLPicDlg	hDlg;
	if ( hDlg.DoModal() != IDOK ) return;

	CString possName = pDoc->ConvertPathname ( ".htm" );

	CFileDialog tDlg(FALSE, "htm", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;
	pDoc->BeginWaitCursor(); // Let em know
	
	CHTMLFile	tHTMLFile;
	CRect SizeRect;

	int Bold;
	if ( pDoc->m_UserVars.m_FontWeight == FW_NORMAL ) {
		Bold = 0;;
	} else {
		Bold = 1;
	}

	CString PathName = tDlg.GetPathName();
	
	CGPRowView *tGPRV;

//	SizeRect.SetRectEmpty();
//	UINT SizeXPosition = (UINT)-1;
//	DWORD SizeYPosition = (DWORD)-1;
	UINT SizeXSize = 0;
	DWORD SizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
		if ( tGPRV->IsSelected() ) {
			UINT tXSize;;
			DWORD tYSize;
			// SizeRect |= tGPRV->GetViewRect();
			tGPRV->GetSize(&tXSize, &tYSize);
			if ( tXSize > SizeXSize ) SizeXSize = tXSize;
			SizeYSize += tYSize;
		}
	}


	
	if ( !tHTMLFile.HTMLInit( 
		(int)SizeXSize, 
		(int)(SizeYSize + m_LineHeight), 
		pDoc->m_UserVars.m_FontSize, 
		(int)m_CharWidth, 
		(int)m_LineHeight, 
		(int)m_Descent, 
		Bold, 
		"Courier New", 
		PathName, 
		pDoc->m_UserVars.m_BackColor0, 
		pDoc->m_UserVars.m_ForeColor0, 
		hDlg.m_HTMLType, 
		hDlg.m_FullWeb
	) ) {
		AfxMessageBox("Error Pict File Open!" );
		return;
	}

	tPos = m_RowViewList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		if ( tGPRV->IsSelected() ) {
			tGPRV->WriteHTML (&tHTMLFile, 0, pDoc);
		}
	}

	tHTMLFile.Exit();

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know
	
	
}

void CGenedocView::OnUpdateGenecopyhtml(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

void CGenedocView::OnCopymetaclip() 
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
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
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

/*
	SetMapMode	// 8
	SetViewPortExt	//121 3d
	SetWindowExt	// 121 3d
	SetWindowOrg	// 0 0
	SetWindowExt	// 385 bd
	SetBkMode		// 1
*/

	DoDraw(&dcMeta, FALSE, FALSE );

	ReleaseDC(pDC);

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


void CGenedocView::OnUpdateCopymetaclip(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _WIN32	
	pCmdUI->Enable(m_CopyFlag);
#else
	pCmdUI->Enable(FALSE);
#endif

}

void CGenedocView::OnCopymetafile() 
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
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
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

void CGenedocView::OnUpdateCopymetafile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _WIN32	
	pCmdUI->Enable(m_CopyFlag);
#else
	pCmdUI->Enable(FALSE);
#endif
	
}


void CGenedocView::OnDstatscore()
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

void CGenedocView::OnUpdateDstatscore(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}

void CGenedocView::OnDstatscoreall()
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

void CGenedocView::OnUpdateDstatscoreall(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}

void CGenedocView::OnGenefindreplace() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_MyCaret.ClearKeys();

	
//	if ( !m_ColSelBegin ) {
//		AfxMessageBox("Must Select with Edit/Select Column first!" );
//		return;
//	}

	DWORD StartRange, EndRange;

	if ( m_ColSelBegin ) {
		if ( m_ColSelStart < m_ColSelEnd ) {
			StartRange = m_ColSelStart;
			EndRange = m_ColSelEnd;
		} else {
			StartRange = m_ColSelEnd;
			EndRange = m_ColSelStart;
		}
	} else {
		StartRange = 0;
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		EndRange = tGSeg->GetTextLength() - 1;
	}

	CFindReplaceDlg tDlg;

	if ( tDlg.DoModal() != IDOK ) return;

	if ( tDlg.m_FindString.GetLength() != tDlg.m_ReplaceString.GetLength() ) {
		AfxMessageBox("Strings Must be Same Length!" );
		return;
	}

	BeginWaitCursor();
	
	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		tCGSeg->FindAndReplace( tDlg.m_FindString, tDlg.m_ReplaceString, StartRange, EndRange );

	}

//	DWORD MaxLength = 0;

//	tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
//	while (tPos != NULL ) {
//		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
//		if ( tCGSeg->GetTextLength() > MaxLength ) {
//    		MaxLength = tCGSeg->GetTextLength();
//		}
//	}

	// Here we gots increase sizes of strings.
//	tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
//	while (tPos != NULL ) {
//		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
//		if ( tCGSeg->GetTextLength() < MaxLength ) {
//			tCGSeg->AppendFiller( MaxLength - tCGSeg->GetTextLength() );
//		}
//	}

	
	EndWaitCursor();

	pDoc->SetModifiedFlag();

	pDoc->AutoShade( -1, 1 );

	
}


void CGenedocView::OnGenecopyseq() 
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

	CGroupSelect tDlg;
	tDlg.GroupSeq = 1;
	tDlg.pDoc = pDoc;

	if ( tDlg.DoModal() != IDOK ) return;

	if ( tDlg.GroupNum1 == 0 ) return;
	if ( tDlg.GroupNum2 == 0 ) return;

	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	CGeneSegment *GetCGSeg;
	while (tPos != NULL ) {

		GetCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( GetCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( GetCGSeg->GetTitle() == tDlg.GroupName1 ) break;

	}

	tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( tCGSeg->GetTitle() == tDlg.GroupName2 ) {
			HANDLE tHan = GetCGSeg->MidText( StartRange, EndRange - StartRange + 1 );
			tCGSeg->SetResidueText( tHan, StartRange, EndRange );
			GlobalFree(tHan);
			break;
		}

	}

	pDoc->SetModifiedFlag();

	pDoc->AutoShade( -1, 1 );

	
}

void CGenedocView::OnUpdateGenecopyseq(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}


void CGenedocView::OnGenecopyrtf() 
{
	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "RTF Files (*.rtf)|*.rtf|All Files (*.*)|*.*||";

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CDocument

//	CRTFPicDlg	hDlg;
//	if ( hDlg.DoModal() != IDOK ) return;

	CString possName = pDoc->ConvertPathname ( ".rtf" );

	CFileDialog tDlg(FALSE, "rtf", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;
	pDoc->BeginWaitCursor(); // Let em know
	
	CRTFFile	tRTFFile;
	CRect SizeRect;

	int Bold;
	if ( pDoc->m_UserVars.m_FontWeight == FW_NORMAL ) {
		Bold = 0;
	} else {
		Bold = 1;
	}

	CString PathName = tDlg.GetPathName();
	
	CGPRowView *tGPRV;

//	SizeRect.SetRectEmpty();
//	UINT SizeXPosition = (UINT)-1;
//	DWORD SizeYPosition = (DWORD)-1;
	UINT SizeXSize = 0;
	DWORD SizeYSize = 0;

	POSITION tPos = m_RowViewList.GetHeadPosition();
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView*)m_RowViewList.GetNext(tPos);
	
		if ( tGPRV->IsSelected() ) {
			UINT tXSize;;
			DWORD tYSize;
			// SizeRect |= tGPRV->GetViewRect();
			tGPRV->GetSize(&tXSize, &tYSize);
			if ( tXSize > SizeXSize ) SizeXSize = tXSize;
			SizeYSize += tYSize;
		}
	}

	CPtrList m_ColorList;

	tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		GeneStor *pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
		DWORD tCount = tCGSeg->GetTextLength();

		// Fill out color list.
		for ( DWORD i = 0; i < tCount; ++i ) {
			POSITION cPos = m_ColorList.GetHeadPosition();
			int found = 0;
			while ( cPos != NULL ) {
				stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)m_ColorList.GetNext(cPos);
				if ( pPDBC->rgbText == pGS[i].TextColor
					&& pPDBC->rgbBack == pGS[i].BackColor
				) {
					found = 1;
					break;
				}
			}
			if ( !found  ) {
				stcPDBCOLOR *pPDBC = new stcPDBCOLOR;
				pPDBC->rgbText = pGS[i].TextColor;
				pPDBC->rgbBack = pGS[i].BackColor;
				m_ColorList.AddTail( pPDBC );
			}
		}
	}

	if ( !tRTFFile.RTFInit( 
		(int)SizeXSize, 
		(int)(SizeYSize + m_LineHeight), 
		pDoc->m_UserVars.m_FontSize, 
		(int)m_CharWidth, 
		(int)m_LineHeight, 
		(int)m_Descent, 
		Bold, 
		PathName, 
		pDoc->m_UserVars.m_BackColor0, 
		pDoc->m_UserVars.m_ForeColor0, 
		0, 
		&m_ColorList 
	) ) {
		AfxMessageBox("Error RTF File Open!" );
		return;
	}

	tPos = m_RowViewList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		tGPRV = (CGPRowView *)m_RowViewList.GetNext(tPos);
		if ( tGPRV->IsSelected() ) {
			tGPRV->WriteRTF (&tRTFFile, 0, pDoc);
		}
	}

	tRTFFile.Exit();

	POSITION cPos = m_ColorList.GetHeadPosition();
	while ( cPos != NULL ) {
		delete (stcPDBCOLOR *)m_ColorList.GetNext(cPos);
	}

	DeSelectAll();

	pDoc->EndWaitCursor(); // Let em know
	
	
}

void CGenedocView::OnUpdateGenecopyrtf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_CopyFlag);	
	
}

#include <math.h>

int qijBlosum30[] = {
96,
38,109,
31,19,55,
43,26,27,95,
14,11,10,10,70,
31,31,14,18,7,39,
44,31,24,37,18,28,94,
52,32,32,35,11,20,35,173,
16,14,11,11,4,10,18,15,60,
40,22,24,18,12,16,23,36,12,72,
56,39,32,43,23,27,51,51,22,66,139,
44,43,27,32,10,21,53,39,13,26,44,63,
18,12,9,8,4,7,12,13,8,14,27,17,12,
27,23,17,11,8,10,16,22,8,27,55,23,8,77,
28,21,12,21,7,15,30,30,14,17,27,29,5,11,91,
56,35,28,34,13,21,38,51,17,33,47,42,10,27,24,75,
40,19,24,24,9,16,23,28,10,27,46,25,10,16,20,41,46,
5,7,2,4,3,4,7,11,2,5,9,6,2,7,4,5,3,27,
14,22,8,15,4,11,16,16,10,18,45,17,7,24,11,17,14,9,44,
56,31,22,27,12,15,26,33,12,63,74,30,15,32,17,36,36,5,24,83
};

int qijBlosum50[] = {
192,
27,152,
24,20,101,
26,19,35,161,
15,5,6,5,91,
22,25,16,17,4,57,
34,29,23,48,6,33,141,
62,20,31,28,9,17,23,316,
12,13,15,11,3,10,13,11,64,
35,15,13,12,8,11,15,18,7,140,
48,28,17,18,14,19,26,27,13,104,304,
33,64,27,26,6,29,43,28,14,17,27,130,
16,9,7,5,4,8,8,9,5,22,42,10,29,
20,12,9,8,6,7,12,15,9,30,58,12,12,154,
22,11,11,15,4,11,19,19,6,13,17,18,5,7,171,
62,25,32,28,11,22,30,44,12,21,29,31,10,16,18,111,
39,21,26,22,10,15,24,25,9,29,38,26,11,15,16,47,100,
5,4,2,2,1,3,4,5,2,5,8,4,3,9,2,3,4,59,
15,13,9,9,4,9,12,12,13,18,27,13,7,39,6,13,12,8,77,
54,20,15,16,13,14,20,22,7,107,92,22,21,30,16,29,41,5,18,164
};

int qijBlosum62[] = {
215,
23,178,
19,20,141,
22,16,37,213,
16,4,4,4,119,
19,25,15,16,3,73,
30,27,22,49,4,35,161,
58,17,29,25,8,14,19,378,
11,12,14,10,2,10,14,10,93,
32,12,10,12,11,9,12,14,6,184,
44,24,14,15,16,16,20,21,10,114,371,
33,62,24,24,5,31,41,25,12,16,25,161,
13,8,5,5,4,7,7,7,4,25,49,9,40,
16,9,8,8,5,5,9,12,8,30,54,9,12,183,
22,10,9,12,4,8,14,14,5,10,14,16,4,5,191,
63,23,31,28,10,19,30,38,11,17,24,31,9,12,17,126,
37,18,22,19,9,14,20,22,7,27,33,23,10,12,14,47,125,
4,3,2,2,1,2,3,4,2,4,7,3,2,8,1,3,3,65,
13,9,7,6,3,7,9,8,15,14,22,10,6,42,5,10,9,9,102,
51,16,12,13,14,12,17,18,6,120,95,19,23,26,12,24,36,4,15,196
};

int qijBlosum75[] = {
245,
21,204,
17,17,162,
18,13,36,253,
16,4,4,4,152,
17,24,14,14,3,90,
28,24,20,48,3,34,194,
55,15,26,23,6,11,17,436,
10,12,13,8,2,11,13,8,100,
28,11,8,9,12,7,10,11,5,210,
39,19,11,11,15,14,16,17,8,115,433,
30,62,23,21,4,29,37,22,11,12,21,180,
12,7,4,4,4,7,6,6,3,26,52,8,49,
14,7,6,6,6,5,7,10,7,28,55,8,11,206,
22,9,7,10,3,7,12,11,4,8,12,13,4,5,214,
64,21,28,25,10,17,27,35,10,15,22,26,7,10,15,153,
36,16,20,17,9,12,19,20,7,24,29,21,10,11,11,46,143,
3,2,1,1,1,2,2,3,2,4,7,2,2,8,1,2,2,80,
12,8,6,5,3,6,7,6,16,14,21,9,5,44,4,9,8,10,136,
47,14,10,10,14,10,15,15,6,122,93,16,22,24,11,21,33,4,14,230
};



void HCount( double MPC, double *Frac, 
	double (*q)[26][26], double *QSum, 
	double DiffRes, double TotalRes  )
{
	int aa, i;

	double BC;
	double bca[26];

	BC = MPC * DiffRes;

//
// ***   Compute the pseudocounts for each cell
//
	for ( aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'V':
		case 'W':
		case 'Y':
			bca[aa] = 0.0;
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					bca[aa] = bca[aa] + (( Frac[i] / TotalRes) * ( (*q)[i][aa] / QSum[i] ));
				}
			}
			bca[aa] = bca[aa] * BC;
		}
	}
	//
	// ***   Compute the weighted average of the observed counts and pseudocounts
	//
	for ( aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'V':
		case 'W':
		case 'Y':
			Frac[aa] = ((TotalRes / (TotalRes + BC)) * (Frac[aa]/TotalRes)) + ((BC / (TotalRes + BC)) * (bca[aa] / BC));
		}
	}
	//
}

void HCountDNA( double MPC, double *Frac, 
	double (*q)[26][26], double *QSum, 
	double DiffRes, double TotalRes  )
{
	int aa, i;

	double BC;
	double bca[26];

	BC = MPC * DiffRes;

//
// ***   Compute the pseudocounts for each cell
//
	for ( aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'G':
		case 'T':
			bca[aa] = 0.0;
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					bca[aa] = bca[aa] + (( Frac[i] / TotalRes) * ( (*q)[i][aa] / QSum[i] ));
				}
			}
			bca[aa] = bca[aa] * BC;
		}
	}
	//
	// ***   Compute the weighted average of the observed counts and pseudocounts
	//
	for ( aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'G':
		case 'T':
			Frac[aa] = ((TotalRes / (TotalRes + BC)) * (Frac[aa]/TotalRes)) + ((BC / (TotalRes + BC)) * (bca[aa] / BC));
		}
	}
	//
}

extern char ProteinLocArray[];


void CGenedocView::OnGenewritelogodds() 
{

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_UserVars.m_ProjectType > 1 ) {
		DoDNALO();
	} else {
		DoProtLO();
	}
}
	
void CGenedocView::DoProtLO()
{
	// TODO: Add your command handler code here
	
	double qij[26][26];

	double dArr[26];
	double dBackFrac[26];
	double dForeFrac[26];
	int i;
	double MPC;
	DWORD di;

	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	CSeqSelDlg sDlg;
	sDlg.m_iLogOddsBack = pDoc->m_UserVars.m_iLogOddsBack;
	sDlg.m_iLogOddsOutTab = pDoc->m_UserVars.m_iLogOddsOutTab;
	sDlg.m_dLogOddsMPC = pDoc->m_UserVars.m_dLogOddsMPC;
	sDlg.m_dLogOddsStA = pDoc->m_UserVars.m_dLogOddsStA;
	sDlg.m_dLogOddsStC = pDoc->m_UserVars.m_dLogOddsStC;
	sDlg.m_dLogOddsStG = pDoc->m_UserVars.m_dLogOddsStG;
	sDlg.m_dLogOddsStT = pDoc->m_UserVars.m_dLogOddsStT;
	sDlg.pDoc = pDoc;

	if ( sDlg.DoModal() != IDOK ) return;

	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "Meme Files (*.mem)|*.mem|All Files (*.*)|*.*||";

	// CDocument
	MPC = sDlg.m_dLogOddsMPC;

	CString possName = pDoc->ConvertPathname ( ".mem" );

	CFileDialog tDlg(FALSE, "mem", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;

	double QSum[26];
	int *pqij;
	memset ( QSum, 0, sizeof(QSum) );
	// Do this sum thing .. wasted CPU time
	switch ( sDlg.m_iLogOddsOutTab ) {
	case 0:
		pqij = qijBlosum30;
		break;
	case 1:
		pqij = qijBlosum50;
		break;
	case 2:
		pqij = qijBlosum62;
		break;
	case 3:
		pqij = qijBlosum75;
		break;
	default:
		pqij = qijBlosum62;
		break;
	}

	memset ( qij, 0, sizeof(qij) );
	int k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( int j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
			qij[Res1][Res2] = (double)pqij[k] / 10000.0;
			qij[Res2][Res1] = (double)pqij[k] / 10000.0;
			k++;
		}
	}

	for ( int aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'V':
		case 'W':
		case 'Y':
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					QSum[aa] = QSum[aa] + qij[aa][i];
				}
			}
		}
	}
	

TRY {

	CStdioFile oFile( tDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText );


	DWORD StartRange, EndRange;
	if ( m_ColSelStart < m_ColSelEnd ) {
		StartRange = m_ColSelStart;
		EndRange = m_ColSelEnd;
	} else {
		StartRange = m_ColSelEnd;
		EndRange = m_ColSelStart;
	}

	BeginWaitCursor(); // Let em know


	int RowCount = pDoc->pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
	
	ShadeSegStc *pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here


	DWORD SeqCount = 0;
	DWORD SeqLength;

	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( tCGSeg->GetExportFlag()  ) continue;
	
		SeqLength = tCGSeg->GetTextLength();
		// Lock it down
		pSegArr[SeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
		pSegArr[SeqCount].pCGSeg = tCGSeg;
		SeqCount++;
	}


	if ( sDlg.m_iLogOddsBack ) {
		memset ( dArr, 0, sizeof(dArr) );

		for ( di=0; di < SeqCount; ++di ) {

			for ( DWORD dwl = 0; dwl < SeqLength; ++dwl ) {

				if ( dwl >= StartRange && dwl <= EndRange ) continue;

				char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					if ( tChar == 'B' ) {
						dArr['D' - 'A'] += pSegArr[di].pCGSeg->GetWeight() / 2.0;
						dArr['N' - 'A'] += pSegArr[di].pCGSeg->GetWeight() / 2.0;
					} else if ( tChar == 'Z' ) {
						dArr['Q' - 'A'] += pSegArr[di].pCGSeg->GetWeight() / 2.0;
						dArr['E' - 'A'] += pSegArr[di].pCGSeg->GetWeight() / 2.0;
					} else if ( tChar == 'X' ) {
					} else {
						dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
					}
				}
			}
		}




		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dBackFrac[i] = dArr[i];
		}

		HCount( MPC, dBackFrac, &qij, QSum, Diff, Total );

	} else {

		memset ( dBackFrac, 0, sizeof(dBackFrac) );

		dBackFrac['A' - 'A'] = 2524164;
		dBackFrac['R' - 'A'] =  1730512;
		dBackFrac['N' - 'A'] =  1517425 + ( 563 / 2 );
		dBackFrac['D' - 'A'] =  1773646 + ( 563 / 2 );
		dBackFrac['C' - 'A'] =   553677;
		dBackFrac['Q' - 'A'] =  1364672 + ( 566 / 2 );
		dBackFrac['E' - 'A'] =  2178113 + ( 566 / 2 );
		dBackFrac['G' - 'A'] =  2328203;
		dBackFrac['H' - 'A'] =   741736;
		dBackFrac['I' - 'A'] = 1966290;
		dBackFrac['L' - 'A'] = 3187735;
		dBackFrac['K' - 'A'] = 2035929;
		dBackFrac['M' - 'A'] =  787779;
		dBackFrac['F' - 'A'] = 1376891;
		dBackFrac['P' - 'A'] = 1664006;
		dBackFrac['S' - 'A'] = 2445578;
		dBackFrac['T' - 'A'] = 1929025;
		dBackFrac['W' - 'A'] =  423051;
		dBackFrac['Y' - 'A'] = 1103471;
		dBackFrac['V' - 'A'] = 2211262;


		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dBackFrac[i] != 0.0 ) Diff += 1.0;
			Total += dBackFrac[i];
		}
		HCount( MPC, dBackFrac, &qij, QSum, Diff, Total );
	}

	char outbuf[256];

	oFile.WriteString("ALPHABET= ACDEFGHIKLMNPQRSTVWY\n" );

	_snprintf( outbuf, sizeof(outbuf), "log-odds matrix: alength= 20 w= %ld\n", EndRange - StartRange + 1 );
	oFile.WriteString(outbuf);

	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		for ( di=0; di < SeqCount; ++di ) {
			char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
			}
		}

		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dForeFrac[i] = dArr[i];
		}

		HCount( MPC, dForeFrac, &qij, QSum, Diff, Total );

		for ( i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'V':
			case 'W':
			case 'Y':
				{
					if ( dForeFrac[i] == 0.0 ) {
						oFile.WriteString( " -6.000 " );
					} else {
						double res = dForeFrac[i] / dBackFrac[i];
						res = ( (1.0/log(2.0)) * log(res) );
						_snprintf ( outbuf, sizeof(outbuf), " % 5.3lf ", res );
						oFile.WriteString( outbuf );
					}
					break;
				}
			}
		}
		oFile.WriteString( "\n" );
	}

	oFile.Close();


	for ( di=0; di < SeqCount; ++di ) {
		GlobalUnlock( pSegArr[di].pCGSeg->GetTextHandle() );
	}

	delete [] pSegArr;

	DeSelectAll();

	EndWaitCursor(); // Let em know

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH

}

int i11PAM30[] = {
7514,828,828,828, 
828,7514,828,828, 
828,828,7514,828, 
828,828,828,7514, 
};
int i11PAM60[] = {
5851,1381,1381,1381, 
1381,5851,1381,1381, 
1381,1381,5851,1381, 
1381,1381,1381,5851, 
};
int i11PAM90[] = {
4739,1751,1751,1751, 
1751,4739,1751,1751, 
1751,1751,4739,1751, 
1751,1751,1751,4739, 
};
int i31PAM30[] = {
7547,535,1383,535, 
535,7547,535,1383, 
1383,535,7547,535, 
535,1383,535,7547, 
};
int i31PAM60[] = {
5944,956,2144,956, 
956,5944,956,2144, 
2144,956,5944,956, 
956,2144,956,5944, 
};
int i31PAM90[] = {
4884,1287,2542,1287, 
1287,4884,1287,2542, 
2542,1287,4884,1287, 
1287,2542,1287,4884, 
};
int iPAM30pseudo[] = {
3197,1954,2579,2132, 
2174,2764,2011,3010, 
2962,2010,2763,2194, 
2070,2589,1916,3328, 
};
int iPAM60pseudo[] = {
2652,2235,2339,2545, 
2515,2372,2249,2738, 
2656,2257,2352,2572, 
2481,2366,2221,2748, 
};
int iPAM90pseudo[] = {
2553,2265,2267,2598, 
2552,2308,2271,2655, 
2569,2281,2282,2618, 
2534,2297,2256,2643, 
};


void CGenedocView::DoDNALO()
{
	// TODO: Add your command handler code here
	
	double qij[26][26];

	double dArr[26];
	double dBackFrac[26];
	double dForeFrac[26];
	int i;
	double MPC;
	DWORD di;

	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	CSeqSelDlg sDlg;
	sDlg.m_iLogOddsBack = pDoc->m_UserVars.m_iLogOddsBack;
	sDlg.m_iLogOddsOutTab = pDoc->m_UserVars.m_iLogOddsOutTab;
	sDlg.m_dLogOddsMPC = pDoc->m_UserVars.m_dLogOddsMPC;
	sDlg.m_dLogOddsStA = pDoc->m_UserVars.m_dLogOddsStA;
	sDlg.m_dLogOddsStC = pDoc->m_UserVars.m_dLogOddsStC;
	sDlg.m_dLogOddsStG = pDoc->m_UserVars.m_dLogOddsStG;
	sDlg.m_dLogOddsStT = pDoc->m_UserVars.m_dLogOddsStT;
	sDlg.pDoc = pDoc;

	if ( sDlg.DoModal() != IDOK ) return;

	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "Meme Files (*.mem)|*.mem|All Files (*.*)|*.*||";

	// CDocument
	MPC = sDlg.m_dLogOddsMPC;

	CString possName = pDoc->ConvertPathname ( ".mem" );

	CFileDialog tDlg(FALSE, "mem", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;

	double QSum[26];
	int *pqij;
	memset ( QSum, 0, sizeof(QSum) );
	// Do this sum thing .. wasted CPU time
	switch ( sDlg.m_iLogOddsOutTab ) {
	case 0:
		pqij = i11PAM30;
		break;
	case 1:
		pqij = i11PAM60;
		break;
	case 2:
		pqij = i11PAM90;
		break;
	case 3:
		pqij = i31PAM30;
		break;
	case 4:
		pqij = i31PAM60;
		break;
	case 5:
		pqij = i31PAM90;
		break;
	case 6:
		pqij = iPAM30pseudo;
		break;
	case 7:
		pqij = iPAM60pseudo;
		break;
	case 8:
		pqij = iPAM90pseudo;
		break;
	default:
		pqij = i11PAM60;
		break;
	}

	memset ( qij, 0, sizeof(qij) );
	int k = 0;
	for ( i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 4; ++ j ) {
			char Res1 = DNALocArray[i];
			char Res2 = DNALocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
			qij[Res1][Res2] = (double)pqij[k] / 10000.0;
//			qij[Res2][Res1] = (double)pqij[k] / 10000.0;
			k++;
		}
	}

	for ( int aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'G':
		case 'T':
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					QSum[aa] = QSum[aa] + qij[aa][i];
				}
			}
		}
	}
	

TRY {

	CStdioFile oFile( tDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText );


	DWORD StartRange, EndRange;
	if ( m_ColSelStart < m_ColSelEnd ) {
		StartRange = m_ColSelStart;
		EndRange = m_ColSelEnd;
	} else {
		StartRange = m_ColSelEnd;
		EndRange = m_ColSelStart;
	}

	BeginWaitCursor(); // Let em know


	int RowCount = pDoc->pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
	
	ShadeSegStc *pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here


	DWORD SeqCount = 0;
	DWORD SeqLength;

	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( tCGSeg->GetExportFlag()  ) continue;
	
		SeqLength = tCGSeg->GetTextLength();
		// Lock it down
		pSegArr[SeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
		pSegArr[SeqCount].pCGSeg = tCGSeg;
		SeqCount++;
	}


	if ( sDlg.m_iLogOddsBack ) {
		memset ( dArr, 0, sizeof(dArr) );

		for ( di=0; di < SeqCount; ++di ) {

			for ( DWORD dwl = 0; dwl < SeqLength; ++dwl ) {

				if ( dwl >= StartRange && dwl <= EndRange ) continue;

				char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					switch ( tChar ) {
					case 'A':
					case 'C':
					case 'G':
					case 'T':
						dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
						break;
					case 'U':
						dArr['T' - 'A'] += pSegArr[di].pCGSeg->GetWeight();
						break;
					}
				}
			}
		}

		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dBackFrac[i] = dArr[i];
		}

		HCountDNA( MPC, dBackFrac, &qij, QSum, Diff, Total );

	} else {

		memset ( dBackFrac, 0, sizeof(dBackFrac) );
		
		dBackFrac['A' - 'A'] = sDlg.m_dLogOddsStA;
		dBackFrac['C' - 'A'] = sDlg.m_dLogOddsStC;
		dBackFrac['G' - 'A'] = sDlg.m_dLogOddsStG;
		dBackFrac['T' - 'A'] = sDlg.m_dLogOddsStT;


		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dBackFrac[i] != 0.0 ) Diff += 1.0;
			Total += dBackFrac[i];
		}
		HCountDNA( MPC, dBackFrac, &qij, QSum, Diff, Total );
	}

	char outbuf[256];

	oFile.WriteString("ALPHABET= ACGT\n" );

	_snprintf( outbuf, sizeof(outbuf), "log-odds matrix: alength= 4 w= %ld\n", EndRange - StartRange + 1 );
	oFile.WriteString(outbuf);

	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		for ( di=0; di < SeqCount; ++di ) {
			char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				switch ( tChar ) {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
					break;
				case 'U':
					dArr['T' - 'A'] += pSegArr[di].pCGSeg->GetWeight();
					break;
				}
			}
		}

//		double Total = 0.0;
//		for ( i=0; i < 26; ++i ) {
//			Total += dArr[i];
//		}

		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dForeFrac[i] = dArr[i];
		}

		HCountDNA( MPC, dForeFrac, &qij, QSum, Diff, Total );
//		for ( i=0; i < 26; ++i ) {
//			dForeFrac[i] = dArr[i] / Total;
//		}

		for ( i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'G':
			case 'T':
				{
					if ( dForeFrac[i] == 0.0 ) {
						oFile.WriteString( " -6.000 " );
					} else {
						double res = dForeFrac[i] / dBackFrac[i];
						res = ( (1.0/log(2.0)) * log(res) );
						_snprintf ( outbuf, sizeof(outbuf), " % 5.3lf ", res );
						oFile.WriteString( outbuf );
					}
					break;
				}
			}
		}
		oFile.WriteString( "\n" );
	}

	oFile.Close();


	for ( di=0; di < SeqCount; ++di ) {
		GlobalUnlock( pSegArr[di].pCGSeg->GetTextHandle() );
	}

	delete [] pSegArr;

	DeSelectAll();

	EndWaitCursor(); // Let em know

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH

}

void CGenedocView::OnUpdateGenewritelogodds(CCmdUI* pCmdUI) 
{

	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}


void CGenedocView::OnDelcolumns() 
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
	

	pDoc->DeleteFillerRange( StartRange, EndRange, 1 );
	pDoc->SetModifiedFlag();
	
}

void CGenedocView::OnUpdateDelcolumns(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}


void CGenedocView::OnFindnext() 
{
	// TODO: Add your command handler code here
	m_MyCaret.ClearKeys();

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// If From From Begin, then set to find foward.
	if ( pDoc->m_pFS.FindFrom == 2 ) {
		pDoc->m_pFS.FindFrom = 0;
	}

	BeginWaitCursor();
	int Found = pDoc->OnFind(this);
	EndWaitCursor();
	if ( !Found ) {
		AfxMessageBox("String Not Found!" );
	}
}

void CGenedocView::OnFind() 
{
	// TODO: Add your command handler code here
	m_MyCaret.ClearKeys();

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CFindDlg fDlg;
	fDlg.pDoc = pDoc;

	fDlg.m_FindStr = pDoc->m_pFS.FindStr;
	fDlg.m_FindFrom = pDoc->m_pFS.FindFrom;
	fDlg.m_MisMatch = pDoc->m_pFS.MisMatch;
	fDlg.m_InsDel = pDoc->m_pFS.InsDel;

	if ( fDlg.DoModal() != IDOK ) return;

	pDoc->m_pFS.FindStr = fDlg.m_FindStr;
	pDoc->m_pFS.FindFrom = fDlg.m_FindFrom;
	pDoc->m_pFS.MisMatch = fDlg.m_MisMatch;
	pDoc->m_pFS.InsDel = fDlg.m_InsDel;
	pDoc->m_pFS.PrevSeq = -1;

	BeginWaitCursor();
	int Found = pDoc->OnFind(this);
	EndWaitCursor();
	if ( pDoc->m_pFS.FindFrom == 3 ) {
		pDoc->UpdateAllViews(NULL);
	}

	if ( !Found ) {
		AfxMessageBox("String Not Found!" );
	}


}

DWORD CGenedocView::ColPosFromCaret(UINT XPosition, DWORD YPosition ) 
{

	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	while ( tPos != NULL ) {

		tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);

		if ( tGP->IsPointWithin(XPosition, YPosition ) ) {
			return tGP->ColPosFromCaret(XPosition, YPosition );
		}
	}
	return 0;
}

void CGenedocView::CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg )
{
	POSITION tPos = m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;
	UINT XPos;
	DWORD YPos;

	while ( tPos != NULL ) {

		tGP = (CGPRowView *)m_RowViewList.GetNext(tPos);

		if ( tGP->CaretPosFromColSeq( tCount, pCGSeg, &XPos, &YPos ) ) break;
	}

	UINT ScrollXPosition = m_DisplayXPosition;
	DWORD ScrollYPosition = m_DisplayYPosition;


	if ( YPos > (m_DisplayHeight / 2 ) ) {
		ScrollYPosition = YPos - (m_DisplayHeight / 2);
		if ( (ScrollYPosition + m_DisplayHeight ) > m_TotalHeight ) {
			ScrollYPosition = m_TotalHeight - m_DisplayHeight;
		}
	} else {
		ScrollYPosition = 0;
	}

	if ( XPos < ScrollXPosition || XPos > (ScrollXPosition + m_DisplayWidth ) ) {
		if ( XPos > (m_DisplayWidth / 2) ) {
			ScrollXPosition = XPos - (m_DisplayWidth / 2);
			if ( (ScrollXPosition + m_DisplayWidth ) > m_TotalWidth ) {
				ScrollXPosition = m_TotalWidth - m_DisplayWidth;
			}
		} else {
			ScrollXPosition = 0;
		}
	}


	ScrollToPosition ( ScrollXPosition, ScrollYPosition );

	DWORD CYPos = YPos - m_DisplayYPosition;
	UINT CXPos = XPos - m_DisplayXPosition;

	m_MyCaret.SetScrollPos( m_DisplayXPosition, m_DisplayYPosition );
	m_MyCaret.SetPosition ( XPos, YPos );
	m_MyCaret.CaretPos();
}


void CGenedocView::OnReplacefromproj() 
{
	// TODO: Add your command handler code here
	if ( !m_ColSelBegin ) {
		AfxMessageBox("Must Select with Edit/Select Column first!" );
		return;
	}

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	DWORD StartRange, EndRange;
	if ( m_ColSelStart < m_ColSelEnd ) {
		StartRange = m_ColSelStart;
		EndRange = m_ColSelEnd;
	} else {
		StartRange = m_ColSelEnd;
		EndRange = m_ColSelStart;
	}

	BeginWaitCursor();
	pDoc->ReplaceFromProj( StartRange, EndRange );
	EndWaitCursor();
}

void CGenedocView::OnUpdateReplacefromproj(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ColSelBegin);
	
}


char GetDNATrans(GeneStor *pc, DWORD tCount, CGenedocDoc *pDoc)
{

	int loc = 0;
	int mult = 16;
	for ( int i = 0; i < 3; ++i ) {
		switch ( toupper(pc[tCount+i].CharGene) ) {
		case 'T':
		case 'U':
			loc += 0 * mult;
			break;
		case 'C':
			loc += 1 * mult;
			break;
		case 'A':
			loc += 2 * mult;
			break;
		case 'G':
			loc += 3 * mult;
			break;
		default:
			loc = -1;
			break;
		}
		if ( loc == -1 ) break;
		mult /= 4;
	}
	if ( loc == -1 ) {
		return '?';
	} else {
		return pDoc->m_UserVars.m_DNATrans[loc];
	}
	return '?';
}

char GetDNATransStart(GeneStor *pc, DWORD tCount, CGenedocDoc *pDoc)
{

	int loc = 0;
	int mult = 16;
	for ( int i = 0; i < 3; ++i ) {
		switch ( toupper(pc[tCount+i].CharGene) ) {
		case 'T':
		case 'U':
			loc += 0 * mult;
			break;
		case 'C':
			loc += 1 * mult;
			break;
		case 'A':
			loc += 2 * mult;
			break;
		case 'G':
			loc += 3 * mult;
			break;
		default:
			loc = -1;
			break;
		}
		if ( loc == -1 ) break;
		mult /= 4;
	}
	if ( loc == -1 ) {
		return '-';
	} else {
		return pDoc->m_UserVars.m_DNATransStart[loc];
	}
	return '-';
}

void CGenedocView::OnDnatrans() 
{

	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	char tGapChar = pDoc->m_UserVars.m_GapInd ? '.' : '-';

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	if ( pGSFiller == NULL ) return;

	m_MyCaret.ClearKeys();

	
//	if ( !m_ColSelBegin ) {
//		AfxMessageBox("Must Select with Edit/Select Column first!" );
//		return;
//	}

	DWORD StartRange, EndRange;

	if ( m_ColSelBegin ) {
		if ( m_ColSelStart < m_ColSelEnd ) {
			StartRange = m_ColSelStart;
			EndRange = m_ColSelEnd;
		} else {
			StartRange = m_ColSelEnd;
			EndRange = m_ColSelStart;
		}
	} else {
		StartRange = 0;
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		EndRange = tGSeg->GetTextLength() - 1;
	}

	DeSelectAll();
	
	CDNATrans tDlg;
	tDlg.pDoc = pDoc;
	tDlg.m_iReadShift = m_iReadShift;
	tDlg.m_TransColumns = m_TransColumns;
	tDlg.m_TransFixed = m_TransFixed;
	tDlg.m_TransFltStart = m_TransFltStart;

	if ( tDlg.DoModal() != IDOK ) return;

	m_iReadShift = tDlg.m_iReadShift;
	m_TransColumns = tDlg.m_TransColumns;
	m_TransFixed = tDlg.m_TransFixed;
	m_TransFltStart = tDlg.m_TransFltStart;

	
	CGSFiller * pnGSFiller;
	pnGSFiller = new CGSFiller;


	// Put the data rows on the list
	SeqNameStruct tSNS;

	DWORD tLen = EndRange - StartRange + 1;
	if ( tLen < 3 ) return;

	CGenedocDoc* pnDoc = (CGenedocDoc *)((CGenedocApp *)AfxGetApp())->CreateNewDocument();
	ASSERT ( pnDoc->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	

	BeginWaitCursor();

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
//			HANDLE hComSeg = GlobalAlloc( GMEM_FLAG, tLen / 3 + 1);
			HANDLE hComSeg = GlobalAlloc( GMEM_FLAG, tLen / 3);
			char *pc = (char *)GlobalLock( hComSeg );
			DWORD tCnt = tLen / 3;
			while ( tCnt-- ) {
				*pc++ = ' ';
			}
			GlobalUnlock ( hComSeg );
			
			CGeneSegment *tnCGSeg = new CGeneSegment();

			tnCGSeg->Create( 
				LINECOMMENT, 
				tCGSeg->GetTitle() , 
				tCGSeg->GetDescr(), 
				0.0, 
				hComSeg, 
				tLen / 3, 
				1, 
				tGapChar, 
				&pDoc->m_UserVars.m_ForeColor0, 
				&pDoc->m_UserVars.m_BackColor0 
			);
			
			pnGSFiller->AddData( tnCGSeg );

			continue;
		}

		HANDLE hText = tCGSeg->GetTextHandle();
		GeneStor * pc = (GeneStor* )GlobalLock(hText);
	
		// Fill Out tSNS
		tSNS.Name = tCGSeg->GetTitle();
		tSNS.Descr = tCGSeg->GetDescr();
		tSNS.Start = tCGSeg->GetTextStart();
		tSNS.Len = 0;
		tSNS.Weight = tCGSeg->GetWeight();
//		tSNS.hText = GlobalAlloc ( GMEM_FLAG, (tLen / 3 + 1) );
		tSNS.hText = GlobalAlloc ( GMEM_FLAG, (tLen / 3 ) );
		char * npc = (char* )GlobalLock(tSNS.hText);

		if ( m_TransFixed == 0 ) {
			DWORD tCount = StartRange + m_iReadShift;
			// If this not zero, then look for start
			if ( m_TransColumns ) {
				for ( ; tCount <= EndRange; tCount++ ) {
					if ( tCount + 2 > EndRange ) break;
					char sChar;
					if ( (sChar = GetDNATransStart( pc, tCount, pDoc )) != '-' ) {
						*npc = sChar;
						npc++;
						tSNS.Len++;
						tCount += 3;
						break;
					}
					if ( ((tCount - (StartRange + m_iReadShift))%3) == 2 ) {
						*npc = tGapChar;
						npc++;
						tSNS.Len++;
					}
				}
			}

			for ( ; tCount < EndRange; tCount += 3 ) {
				if ( tCount + 2 > EndRange ) break;
				if ( pc[tCount].CharGene == tGapChar && pc[tCount+1].CharGene == tGapChar && pc[tCount+2].CharGene == tGapChar ) {
					*npc = tGapChar;
				} else {
					*npc = GetDNATrans( pc, tCount, pDoc );
				}
				npc++;
				tSNS.Len++;
			}
			if ( tSNS.Len < tLen/3) {
				*npc = '-';
				npc++;
				tSNS.Len++;
			}
		} else {
			DWORD tCount = StartRange + m_iReadShift;
			CString Trans;
			CString Gaps;
			if ( m_TransFltStart ) {
				for ( ; tCount <= EndRange; tCount++ ) {
					char sChar;
					sChar = toupper(pc[tCount].CharGene);
					if ( sChar >= 'A' && sChar <= 'Z' ) {
						Trans += sChar;
					}
					if ( Trans.GetLength() >= 3 ) {
						int loc = 0;
						int mult = 16;
						for ( int i = 0; i < 3; ++i ) {
							switch ( Trans[i] ) {
							case 'T':
							case 'U':
								loc += 0 * mult;
								break;
							case 'C':
								loc += 1 * mult;
								break;
							case 'A':
								loc += 2 * mult;
								break;
							case 'G':
								loc += 3 * mult;
								break;
							default:
								loc = -1;
								break;
							}
							if ( loc == -1 ) break;
							mult /= 4;
						}
						if ( loc == -1 ) {
							sChar = '-';
						} else {
							sChar = pDoc->m_UserVars.m_DNATransStart[loc];
						}
						if ( sChar != '-' ) {
							*npc = sChar;
							npc++;
							tSNS.Len++;
							Trans.Empty();
							Gaps.Empty();
							tCount++;
							break;
						}
						// CString
						Gaps += Trans[0];
						Trans = Trans.Right(2);
						if ( tSNS.Len > tLen/3 ) {
							AfxMessageBox(" Length Exceeded");
							break;
						}
					}
					if ( Gaps.GetLength() >= 3 ) {
						*npc = '-';
						npc++;
						tSNS.Len++;
						Gaps.Empty();
						if ( tSNS.Len > tLen/3 ) {
							AfxMessageBox(" Length Exceeded");
							break;
						}
					}
				}
			}
			for ( ; tCount <= EndRange; tCount++ ) {
				char sChar;
				sChar = toupper(pc[tCount].CharGene);
				if ( sChar >= 'A' && sChar <= 'Z' ) {
					Trans += sChar;
				} else {
					Gaps += sChar;
				}
				if ( Trans.GetLength() >= 3 ) {
					int loc = 0;
					int mult = 16;
					for ( int i = 0; i < 3; ++i ) {
						switch ( Trans[i] ) {
						case 'T':
						case 'U':
							loc += 0 * mult;
							break;
						case 'C':
							loc += 1 * mult;
							break;
						case 'A':
							loc += 2 * mult;
							break;
						case 'G':
							loc += 3 * mult;
							break;
						default:
							loc = -1;
							break;
						}
						if ( loc == -1 ) break;
						mult /= 4;
					}
					if ( loc == -1 ) {
						*npc = '?';
					} else {
						*npc = pDoc->m_UserVars.m_DNATrans[loc];
					}
					npc++;
					tSNS.Len++;
					Trans.Empty();
					if ( tSNS.Len > tLen/3 ) {
						AfxMessageBox(" Length Exceeded");
						break;
					}
				}
				if ( Gaps.GetLength() >= 3 ) {
					*npc = '-';
					npc++;
					tSNS.Len++;
					Gaps.Empty();
					if ( tSNS.Len > tLen/3 ) {
						AfxMessageBox(" Length Exceeded");
						break;
					}
				}
			}
			while ( tSNS.Len < tLen/3) {
				*npc = '-';
				npc++;
				tSNS.Len++;
			}

		}


		GlobalUnlock(tSNS.hText);
		GlobalUnlock(hText);
		
		CGeneSegment *tnCGSeg = new CGeneSegment();
		if ( tnCGSeg == 0 ) {
			AfxMessageBox( "Genedvw:new:fail:20" );
			return;
		}
		
		if ( !tnCGSeg->Create( 
			LINESEQUENCE, 
			tSNS.Name, 
			tSNS.Descr, 
			tSNS.Weight, 
			tSNS.hText, 
			tSNS.Len, 
			tSNS.Start, 
			tGapChar, 
			&pDoc->m_UserVars.m_ForeColor0, 
			&pDoc->m_UserVars.m_BackColor0 ) 
		) {
			AfxMessageBox("Create Sequence Fails");
			return;
		}


		pnGSFiller->AddData( tnCGSeg );

	}

	pnGSFiller->pGeneSegParent = NULL;

	pDoc->SetUserDefaults();

	// copy comments into GFiller head list
	tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while (tPos != NULL ) {
		CString * tStr = new CString ( *(CString *)pGSFiller->SegHeaderList.GetNext(tPos) );
		if ( tStr == 0 ) {
			AfxMessageBox( "Genedvw:new:fail:22" );
			return;
		}
		pnGSFiller->AddHeader( tStr );
	}

	pnDoc->CopyGSFiller( pnGSFiller );

	
//	pnDoc->CopyUserVars( &pnDoc->m_UserVars, &pDoc->m_UserVars );	// To <- From

	pnDoc->ParseTree( pDoc->m_UserVars.m_ParseString, 0 );

	pnDoc->GetUserDefaults();	// To <- From

	// Set to Protein project.
	pnDoc->m_UserVars.m_ProjectType = 0;

	EndWaitCursor();

	pnDoc->AutoShade(-1);

}


void CGenedocView::OnDnaffreqrep() 
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	if ( pGSFiller == NULL ) return;

	m_MyCaret.ClearKeys();

	DWORD StartRange, EndRange;

	if ( m_ColSelBegin ) {
		if ( m_ColSelStart < m_ColSelEnd ) {
			StartRange = m_ColSelStart;
			EndRange = m_ColSelEnd;
		} else {
			StartRange = m_ColSelEnd;
			EndRange = m_ColSelStart;
		}
	} else {
		StartRange = 0;
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		EndRange = tGSeg->GetTextLength() - 1;
	}

	DeSelectAll();

	pDoc->DNAFreqRep( StartRange, EndRange );
}

void CGenedocView::OnUpdateDnaffreqrep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGenedocDoc* pDoc = GetDocument();
	pCmdUI->Enable(	pDoc->pGSFiller != NULL );
	
}

void CGenedocView::OnDnacolfreqrep() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	if ( pGSFiller == NULL ) return;

	m_MyCaret.ClearKeys();

	DWORD StartRange, EndRange;

	if ( m_ColSelBegin ) {
		if ( m_ColSelStart < m_ColSelEnd ) {
			StartRange = m_ColSelStart;
			EndRange = m_ColSelEnd;
		} else {
			StartRange = m_ColSelEnd;
			EndRange = m_ColSelStart;
		}
	} else {
		StartRange = 0;
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		EndRange = tGSeg->GetTextLength() - 1;
	}

	DeSelectAll();

	pDoc->ColFreqRep( StartRange, EndRange, 0 );
	
}

void CGenedocView::OnUpdateDnacolfreqrep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGenedocDoc* pDoc = GetDocument();
	pCmdUI->Enable(	pDoc->pGSFiller != NULL );
}	

void CGenedocView::OnDnacolfrwrep() 
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CGSFiller *pGSFiller = pDoc->pGSFiller;
	if ( pGSFiller == NULL ) return;

	m_MyCaret.ClearKeys();

	DWORD StartRange, EndRange;

	if ( m_ColSelBegin ) {
		if ( m_ColSelStart < m_ColSelEnd ) {
			StartRange = m_ColSelStart;
			EndRange = m_ColSelEnd;
		} else {
			StartRange = m_ColSelEnd;
			EndRange = m_ColSelStart;
		}
	} else {
		StartRange = 0;
		CGeneSegment *tGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		EndRange = tGSeg->GetTextLength() - 1;
	}

	DeSelectAll();

	pDoc->ColFreqRep( StartRange, EndRange, 1 );
	
}

void CGenedocView::OnUpdateDnacolfrwrep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CGenedocDoc* pDoc = GetDocument();
	pCmdUI->Enable(	pDoc->pGSFiller != NULL );
}

