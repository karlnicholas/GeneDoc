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
// CGelView.cpp : implementation of the CGelView class
//

#include "stdafx.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGelView

IMPLEMENT_DYNCREATE(CGelView, CFormView)

BEGIN_MESSAGE_MAP(CGelView, CFormView)
	//{{AFX_MSG_MAP(CGelView)
	ON_BN_CLICKED(IDC_RUNGEL, OnRungel)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_EDITCOPY, OnEditCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGelView construction/destruction

CGelView::CGelView()
	: CFormView(CGelView::IDD)
{
	//{{AFX_DATA_INIT(CGelView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
//	m_GelView = FALSE;
	m_init = 0;

	m_PageWidth = 500;
	m_PageHeight = 500;

	m_LineWidth = 2;
	// determine default font for document
	memset(&m_logFont, 0, sizeof m_logFont);
	m_logFont.lfHeight = -8;
	lstrcpy(m_logFont.lfFaceName, _T("Arial"));

	m_MinY = 0;
	m_MaxY = 400;

}

CGelView::~CGelView()
{
	POSITION sPos = m_listGel.GetHeadPosition();
	while ( sPos != NULL ) {
		delete (SGel*)m_listGel.GetNext(sPos);
	}
	m_listGel.RemoveAll();

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pGelView = NULL;
}

void CGelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGelView)
	DDX_Control(pDX, IDC_LISTENZYME, m_listEnzymes);
	DDX_Control(pDX, IDC_LISTSEQUENCE, m_listSequences);
	//}}AFX_DATA_MAP
}

BOOL CGelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGelView printing

BOOL CGelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


/////////////////////////////////////////////////////////////////////////////
// CGelView diagnostics

#ifdef _DEBUG
void CGelView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGenedocDoc* CGelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	return (CGenedocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGelView message handlers

int CGelView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pGelView = this;
	
	return 0;
}

void CGelView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	RebuildBox();
}

void
CGelView::RebuildBox()
{
	CGenedocDoc *pDoc = GetDocument();
	
	m_listSequences.ResetContent();

	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			int loc = m_listSequences.AddString( tCGSeg->GetTitle() );
			m_listSequences.SetItemDataPtr( loc, tCGSeg );
		}
	}
	
	m_listEnzymes.ResetContent();

	tPos = pDoc->m_UserVars.listSearch.GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)pDoc->m_UserVars.listSearch.GetNext(tPos);
		if ( pSearch->iEnabled ) {
			int loc = m_listEnzymes.AddString( pSearch->strName );
			m_listEnzymes.SetItemDataPtr( loc, pSearch );
		}
	}

}

void CGelView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
//	ResizeParentToFit(FALSE);
//	((CMDIChildWnd *)GetParentFrame())->MDIMaximize();

//	m_GelView = TRUE;
	// CButton	m_cDraw;
	CDC* pDC = GetDC();

	CRect ClientRect;
	
	GetClientRect(ClientRect);
	
	CPoint ptl = ClientRect.TopLeft();
	CPoint pbr = ClientRect.BottomRight();

	ptl.x = ptl.x + 220;
	ptl.y = ptl.y + 0;

	pbr.x = pbr.x - 0;
	pbr.y = pbr.y - 0;

	ClientRect.TopLeft() = ptl;
	ClientRect.BottomRight() = pbr;

	int DisplayHeight = ClientRect.Height();
	int DisplayWidth = ClientRect.Width();

	double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpi = pDC->GetDeviceCaps(LOGPIXELSX);

//	WINDOWPLACEMENT wndpl;
//	m_cDraw.GetWindowPlacement( &wndpl );
//	wndpl.rcNormalPosition.bottom = DisplayHeight - 10;
//	wndpl.rcNormalPosition.right = DisplayWidth - 10;
//	m_cDraw.SetWindowPlacement( &wndpl );

	int x = (int)((double)(DisplayWidth - 10) / xpi * 100.0 );
	int y = (int)((double)(DisplayWidth - 10) / ypi * 100.0 );


	SetGelSize( x, y );

//	x = (int)((double)DisplayWidth / xpi * 100.0 );
//	y = (int)((double)DisplayHeight / ypi * 100.0 );

//	pDoc->m_ViewSize =  CSize( x, y );

	ReleaseDC ( pDC );


	m_init = 1;

}
void CGelView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CGenedocDoc *pDoc = GetDocument();


//	if ( pDoc->IsEmbedded() && m_GelView ) {

	if ( m_init ) {

		CDC* pDC = GetDC();
		
		CRect ClientRect;
		
		GetClientRect(ClientRect);
		
		CPoint ptl = ClientRect.TopLeft();
		CPoint pbr = ClientRect.BottomRight();

		ptl.x = ptl.x + 220;
		ptl.y = ptl.y + 0;

		pbr.x = pbr.x - 0;
		pbr.y = pbr.y - 0;

		ClientRect.TopLeft() = ptl;
		ClientRect.BottomRight() = pbr;

		int DisplayHeight = ClientRect.Height();
		int DisplayWidth = ClientRect.Width();

		double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
		double xpi = pDC->GetDeviceCaps(LOGPIXELSX);


//		WINDOWPLACEMENT wndpl;
//		m_cDraw.GetWindowPlacement( &wndpl );
//		wndpl.rcNormalPosition.bottom = DisplayHeight - 10;
//		wndpl.rcNormalPosition.right = DisplayWidth - 10;
//		m_cDraw.SetWindowPlacement( &wndpl );

		int x = (int)((double)(DisplayWidth - 10) / xpi * 100.0 );
		int y = (int)((double)(DisplayHeight - 10) / ypi * 100.0 );

		SetGelSize( x, y );
		
//		x = (int)((double)DisplayWidth / xpi * 100.0 );
//		y = (int)((double)DisplayHeight / ypi * 100.0 );

//		pDoc->m_ViewSize =  CSize( x, y );

		ReleaseDC(pDC);
	}

}

extern CString BuildRebaseSrch( const CString& iSearch );

void 
CGelView::SearchRebaseGel( 
	stcSearch *pSearch, 
	GeneStor *pGeneStor, 
	DWORD OuterCount )
{

	CString strSearch = BuildRebaseSrch( pSearch->strSearch );
	int match = 0;

	int coff;
	coff = pSearch->strSearch.Find( '\'');
	if ( coff == -1 ) coff = 0;
	if ( pSearch->strSearch.Find( '_') < coff ) {
		if ( pSearch->strSearch.Find( '_') != -1 ) if ( coff ) coff--;
	}

	// end for ..
	int sLen = strSearch.GetLength();
	if ( sLen == 0 ) return;
	int mCount = 0;
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;
		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;
		// for report.
		DWORD sCount = 0;
		for ( int j = 0; j < sLen; ++j ) {
			char tChar;
			do { 
				if ( tCount + sCount > OuterCount ) break;
				tChar = toupper(pGeneStor[tCount + sCount].CharGene);
				sCount++;
			} while ( !(tChar >= 'A' && tChar <= 'Z' ) );
			if ( tCount + sCount > OuterCount ) {
				match = 0;
				break;
			}
			char sChar = strSearch[j];
			switch( sChar ) {
			case 'A': match = (tChar == 'A'); break;
			case 'G': match = (tChar == 'G'); break;
			case 'C': match = (tChar == 'C'); break;
			case 'T': match = (tChar == 'T'); break;
			case 'U': match = (tChar == 'U'); break;
			case 'Y': match = (tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'R': match = (tChar == 'A' || tChar == 'G' ); break;
			case 'W': match = (tChar == 'A' || tChar == 'T' || tChar == 'U' ); break;
			case 'S': match = (tChar == 'C' || tChar == 'G' ); break;
			case 'K': match = (tChar == 'T' || tChar == 'U' || tChar == 'G' ); break;
			case 'M': match = (tChar == 'C' || tChar == 'A' ); break;
			case 'B': match = (tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'D': match = (tChar == 'A' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'H': match = (tChar == 'A' || tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'V': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' ); break;
			case 'N': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'X': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			}
			if ( !match ) break;
		}

		// Test if Should do Colors.
		if ( match ) {
			DWORD cLoc = pGeneStor[tCount].GeneSeqNumber;
			cLoc += coff;

			pSGel->arrCutLoc.Add( cLoc );
		}
	}
	return;
}



void CGelView::OnRungel() 
{
	// TODO: Add your control notification handler code here
	CGenedocDoc *pDoc = GetDocument();

//	MakeGel(m_listSequences, m_listEnzymes);
//	pDoc->SetModifiedFlag();

	// CListBox
	int iSeqCount, iEnzCount;

	iSeqCount = m_listSequences.GetSelCount();
	iEnzCount = m_listEnzymes.GetSelCount();

	if ( iSeqCount < 1 || iEnzCount < 1 ) {
		return;
	}

	BeginWaitCursor();

	int *arrSeq = new int[iSeqCount];
	int *arrEnz = new int[iEnzCount];

	m_listSequences.GetSelItems( iSeqCount, arrSeq );
	m_listEnzymes.GetSelItems( iEnzCount, arrEnz );


	POSITION sPos = m_listGel.GetHeadPosition();
	while ( sPos != NULL ) {
		delete (SGel*)m_listGel.GetNext(sPos);
	}
	m_listGel.RemoveAll();

	int s, e;

	for ( s=0; s < iSeqCount; ++s ) {
		POSITION aPos = pDoc->pGSFiller->SegDataList.FindIndex( arrSeq[s] + 2 );
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetAt(aPos);

		GeneStor *pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );
		// CList
		NewBand(tCGSeg);
		for ( e=0; e < iEnzCount; ++e ) {
			POSITION ePos =  pDoc->m_UserVars.listSearch.FindIndex( arrEnz[e] );
			stcSearch *Enzyme = (stcSearch *)pDoc->m_UserVars.listSearch.GetAt(ePos);

			SearchRebaseGel( Enzyme, pGS, tCGSeg->GetTextLength() );

		}
		GlobalUnlock( tCGSeg->GetTextHandle() );
	}


	CUIntArray arrFrags;

	DWORD MaxLength = 0;
	sPos = m_listGel.GetHeadPosition();
	while ( sPos != NULL ) {
		SGel *pSGel = (SGel *)m_listGel.GetNext(sPos);
		DWORD iLen = pSGel->Sequence->GetLastResidue();
		if ( iLen > MaxLength ) MaxLength = iLen;
	}

	SetYScale ( 0, MaxLength );

	sPos = m_listGel.GetHeadPosition();
	while ( sPos != NULL ) {
		SGel *pSGel = (SGel *)m_listGel.GetNext(sPos);

		int iArr = pSGel->arrCutLoc.GetSize();
		// This code sorts the cut locations
		for ( int ti=0; ti < iArr - 1; ++ti ) {
			for ( int tj=0; tj < iArr - 1; ++tj ) {
				if ( pSGel->arrCutLoc[tj] > pSGel->arrCutLoc[tj+1] ) {
					int t = pSGel->arrCutLoc[tj];
					pSGel->arrCutLoc[tj] = pSGel->arrCutLoc[tj+1];
					pSGel->arrCutLoc[tj+1] = t;
				}
			}
		}
		// Calculate Fragment lengths ..
		DWORD LastCutLoc = 0;
		int i;
		for ( i=0; i < iArr; ++i ) {
			if ( pSGel->arrCutLoc[i] == LastCutLoc ) continue;
			int cl = pSGel->arrCutLoc[i] - LastCutLoc;
			arrFrags.Add( cl );
			LastCutLoc = pSGel->arrCutLoc[i];
		}
		arrFrags.Add( pSGel->Sequence->GetLastResidue() - LastCutLoc );

		// This code sorts the fragment lengths in case that is useful.
//		for ( ti=0; ti < arrFrags.GetSize() - 1; ++ti ) {
//			for ( int tj=0; tj < arrFrags.GetSize()-1; ++tj ) {
//				if ( arrFrags[tj] > arrFrags[tj+1] ) {
//					int t = arrFrags[tj];
//					arrFrags[tj] = arrFrags[tj+1];
//					arrFrags[tj+1] = t;
//				}
//			}
//		}

		iArr = arrFrags.GetSize();
		for ( i=0; i < iArr; ++i ) {
			int iFragLength = arrFrags[i];
			// Normalize fragments to 0 to 1.0
//			double GelLocPerc = 1.0 - (log((double)iFragLength) / log((double)MaxLength));
//			double GelLocPerc = 1.0 - ((double)iFragLength / (double)MaxLength);
			DWORD GelLocPerc = (DWORD)(((double)iFragLength / (double)MaxLength) * 100000000.0);
			// Put Normalized resuls into array for GelObject to draw.
			pSGel->arrGelLoc.Add(GelLocPerc);
		}

		arrFrags.RemoveAll();
	}


	delete arrSeq;
	delete arrEnz;

	EndWaitCursor();
	
	Invalidate();

}


void CGelView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CView::OnDraw( pDC );

	CRect rcBounds;
	GetClientRect( rcBounds );
	CPoint ptl = rcBounds.TopLeft();
	CPoint pbr = rcBounds.BottomRight();

	ptl.x = ptl.x + 220;
	ptl.y = ptl.y + 0;

	pbr.x = pbr.x - 0;
	pbr.y = pbr.y - 0;

	rcBounds.TopLeft() = ptl;
	rcBounds.BottomRight() = pbr;


	DrawGel( pDC, rcBounds );
}

void CGelView::DrawGel(CDC* pDC, CRect rcBounds) 
{
	char tBuff[128];
    
    CBrush bBrush;
	bBrush.CreateSolidBrush( RGB(255,255,255) );
	pDC->FillRect( &rcBounds, &bBrush );
	pDC->SetBkColor( RGB(255,255,255) );

	CSize docSize = GetGelSize();

	double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpi = pDC->GetDeviceCaps(LOGPIXELSX);

	int x = (int)((double)docSize.cx/100.0 * xpi);
	int y = (int)((double)docSize.cy/100.0 * ypi);

	int xoff = rcBounds.TopLeft().x;
	int yoff = rcBounds.TopLeft().y;

	int YSpace = (int)(ypi / 24.0);
	int XSpace = (int)(xpi / 24.0);

	// Lets draw graph always ...
	//
	CFont fontTmp;
	CFont* pOldFont = SelectDocFont(pDC, fontTmp, 900);

	CPen nPen( PS_SOLID, m_LineWidth, RGB(0,0,0) );
    CPen* oPen = pDC->SelectObject(&nPen);


	CSize fontSize = pDC->GetTextExtent( "X", 1 );
	int NamesHeight = 0;
	POSITION gPos = m_listGel.GetHeadPosition();
	while ( gPos != NULL ) {
		SGel *pSGel = (SGel *)m_listGel.GetNext(gPos);
		CString strName = pSGel->Sequence->GetTitle();
		strName = strName.Left(10);

		CSize fontSize = pDC->GetTextExtent( strName, strName.GetLength() );
		int iHeight = fontSize.cx;
		if ( iHeight > NamesHeight ) NamesHeight = iHeight;

	}


//	int xborder = (int)((double)x * .05);

  	_snprintf( tBuff, 127, "%d", m_MaxY );	// = "1.0";
	CSize tstrsz;
	tstrsz = pDC->GetTextExtent( tBuff, strlen(tBuff) );
	int xborder = tstrsz.cx + XSpace;

	int yborder = (int)(xpi / 24.0);

	yborder += m_LineWidth;


	pDC->MoveTo(xoff + (xborder), yoff + (NamesHeight + YSpace - m_LineWidth) );
	pDC->LineTo(xoff + (xborder),yoff + (y - yborder));
	pDC->LineTo(xoff + (x - XSpace),yoff + (y - yborder));
	pDC->LineTo(xoff + (x - XSpace),yoff + ( NamesHeight + YSpace - m_LineWidth ));
	pDC->LineTo(xoff + (xborder ),yoff + (NamesHeight + YSpace - m_LineWidth ));

	int GraphWidth = (x - XSpace) - xborder;


	int drl = 1;
	while ( drl < m_MinY ) {
		if ( drl * 10 > m_MinY ) break;
		drl = drl * 10;
	}
	double YRange = m_MaxY - (double)drl + 1;

	double dblYMult = (double)y - (yborder + NamesHeight + YSpace);


	
	if ( m_listGel.GetCount() != 0 ) {

		int GelCount = m_listGel.GetCount();
		int dWidth = GraphWidth - ( GelCount * m_LineWidth * 2 );
		int BandWidth = dWidth / GelCount;

		int Band = 0;

		gPos = m_listGel.GetHeadPosition();
		while ( gPos != NULL ) {
			SGel *pSGel = (SGel *)m_listGel.GetNext(gPos);
			CString strName = pSGel->Sequence->GetTitle();
			strName = strName.Left(10);

			double dblXVal = (Band * BandWidth) + (Band * m_LineWidth * 2) - (m_LineWidth * 2);

			pDC->ExtTextOut( 
				1 + xoff + ((int)dblXVal + xborder) + ( BandWidth / 2 ) - ( fontSize.cx / 2 ),
				yoff + (NamesHeight + YSpace - m_LineWidth - 2), 
				ETO_CLIPPED, CRect ( xoff, yoff, xoff + x, yoff + y ), 
				strName, strName.GetLength(), NULL
			);

			Band++;

			int wdrl = drl;
			int inc = drl;
			while ( wdrl < m_MaxY ) {

				double dblYVal = 1.0 - (log (double( wdrl - drl + 1)) / log(YRange));


				dblYVal *= dblYMult;
				int tyloc = yoff + (NamesHeight + YSpace + (int)dblYVal - 1);

				pDC->MoveTo(
					1 + xoff + ((int)dblXVal + BandWidth + xborder + m_LineWidth+ m_LineWidth), 
					tyloc);
				pDC->LineTo(
					1 + xoff + ((int)dblXVal + BandWidth + xborder + m_LineWidth+ m_LineWidth + m_LineWidth), 
					tyloc);
				pDC->LineTo(
					1 + xoff + ((int)dblXVal + BandWidth + xborder + m_LineWidth+ m_LineWidth), 
					tyloc);


				wdrl += inc;
				if ( wdrl == inc * 10 ) {
					inc = inc * 10;
				}


			}


		}

		pDC->SelectObject( pOldFont );
		fontTmp.DeleteObject();
		pOldFont = SelectDocFont(pDC, fontTmp, 0);

		int yinc = ((y - yborder) - (NamesHeight + YSpace ))/4;

		pDC->MoveTo(xoff + (xborder),yoff + ( NamesHeight + YSpace ));
		pDC->LineTo(xoff + (xborder - XSpace),yoff + ( NamesHeight + YSpace ));
		pDC->LineTo(xoff + (xborder),yoff + ( NamesHeight + YSpace ));


  		_snprintf( tBuff, 127, "%d", m_MaxY );	// = "1.0";
		CSize tstrsz;
		tstrsz = pDC->GetTextExtent( tBuff, strlen(tBuff) );
		// pDC->LPtoDP( &tstrsz );

		pDC->ExtTextOut( 
			xoff + (xborder - XSpace - tstrsz.cx), 
			yoff + (NamesHeight + YSpace) - tstrsz.cy,  
			ETO_CLIPPED, CRect ( xoff, yoff, xoff + x, yoff + y ), 
			tBuff, strlen(tBuff), NULL 
		);




		int wdrl = drl;
		int inc = drl;
		while ( wdrl < m_MaxY ) {

			double dblYVal = 1.0 - (log (double( wdrl - drl + 1)) / log(YRange));


			dblYVal *= dblYMult;
			int tyloc = yoff + (NamesHeight + YSpace + (int)dblYVal - 1);

			pDC->MoveTo(xoff + (xborder),tyloc);
			pDC->LineTo(xoff + (xborder - XSpace),tyloc);
			pDC->LineTo(xoff + (xborder),tyloc);

			if ( wdrl == inc || wdrl == inc *5 ) {
				pDC->MoveTo(xoff + (xborder),tyloc);
				pDC->LineTo(xoff + (xborder - XSpace),tyloc);
				pDC->LineTo(xoff + (xborder),tyloc);
				
				_snprintf( tBuff, 127, "%d", wdrl );	// = ".75";
				tstrsz = pDC->GetTextExtent( tBuff, strlen(tBuff) );

				pDC->ExtTextOut( 
					xoff + (xborder - XSpace - tstrsz.cx), 
					tyloc -(tstrsz.cy/2),  
					ETO_CLIPPED, CRect ( xoff, tyloc-(tstrsz.cy/2), xoff + x, (tyloc -(tstrsz.cy/2)) + y ), 
					tBuff, strlen(tBuff), NULL 
				);
			}

			wdrl += inc;
			if ( wdrl == inc * 10 ) {
				inc = inc * 10;
			}
		}

		// For assumed Y Scale = 0 - 1.0
		// Create a red pen.
		pDC->SelectObject( oPen );
		nPen.DeleteObject();
		nPen.CreatePen( PS_SOLID, m_LineWidth, RGB(255,0,0) );
		oPen = pDC->SelectObject(&nPen);

		Band = 0;

		gPos = m_listGel.GetHeadPosition();
		while ( gPos != NULL ) {
			SGel *pSGel = (SGel *)m_listGel.GetNext(gPos);

			double dblXVal = (Band * BandWidth) + (Band * m_LineWidth * 2);

			int FragCount = pSGel->arrGelLoc.GetSize();

			for ( int i=0; i < FragCount; ++i ) {
				
				double ss = pSGel->arrGelLoc[i] / 100000000.0;
				double dblYVal = 1.0 - (log( (ss * YRange) - drl + 1) / log(YRange));

				dblYVal *= dblYMult;

				pDC->MoveTo( 
					1 + xoff + ((int)dblXVal + xborder), 
					yoff + (NamesHeight + YSpace + (int)dblYVal - 1)
				);
				pDC->LineTo( 
					1 + xoff + ((int)dblXVal + BandWidth + xborder) - (m_LineWidth * 2),
					yoff + (NamesHeight + YSpace +  (int)dblYVal - 1)
				);
				pDC->LineTo( 
					1 + xoff + ((int)dblXVal + xborder), 
					yoff + (NamesHeight + YSpace + (int)dblYVal - 1)
				);

			}

			Band++;
		}

	}

	pDC->SelectObject( oPen );
	nPen.DeleteObject();



	pDC->SelectObject( pOldFont );
	fontTmp.DeleteObject();


}

CFont* CGelView::SelectDocFont(CDC* pDC, CFont& font, int Escapement )
{
	// convert points in m_logfont.lfHeight to device
	LOGFONT logfont = m_logFont;
	logfont.lfHeight = -::MulDiv(-logfont.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	logfont.lfEscapement = Escapement;
	// create the font object
	if (!font.CreateFontIndirect(&logfont))
		return NULL;

	// select the font
	return pDC->SelectObject(&font);
}


#ifndef _WIN32

void CGelView::OnEditCopy() 
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

	CMetaFileDC dcMeta;

	dcMeta.Create();

	CDC* pDC = GetDC();


	double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpi = pDC->GetDeviceCaps(LOGPIXELSX);

	int x = (int)((double)GetGelSize().cx/100.0 * xpi);
	int y = (int)((double)GetGelSize().cy/100.0 * ypi);

	CSize tSize(x,y);
	pDC->DPtoHIMETRIC(&tSize);

	dcMeta.SetAttribDC( pDC->m_hAttribDC );

	OnPrepareDC( &dcMeta );

	DrawGel( &dcMeta, CRect( 0, 0, tSize.cx, tSize.cy ) );

	HGLOBAL hMF = GlobalAlloc( GMEM_DDESHARE | GMEM_ZEROINIT | GMEM_MOVEABLE , sizeof(METAFILEPICT) );

	METAFILEPICT *pMFP = (METAFILEPICT *)GlobalLock( hMF );

	pMFP->mm = MM_ANISOTROPIC;
	pMFP->xExt = tSize.cx;
	pMFP->yExt = tSize.cy;

	HMETAFILE hMeta = dcMeta.Close();

	pMFP->hMF = hMeta;

	GlobalUnlock( hMF );

	if ( SetClipboardData(CF_METAFILEPICT, hMF) == NULL ) {
		AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
	}

// CBitmap
//
	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}

	ReleaseDC( pDC );	// Moved this down here, needs testing.

	return;

}

#else 

void CGelView::OnEditCopy() 
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

	CDC* pDC = GetDC();

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double tXSize, tYSize;

	tXSize = GetGelSize().cx * xpi * 100.0;

	tYSize = GetGelSize().cy * ypi * 100.0;

	CRect rectView(0,0,(int)tXSize, (int)tYSize );

	CMetaFileDC dcMeta;

	dcMeta.CreateEnhanced(pDC, NULL, rectView, "GeneDoc\0MetaFile\0\0" );

	dcMeta.SetAttribDC( pDC->m_hAttribDC );


	OnPrepareDC( &dcMeta );

	DrawGel( &dcMeta, rectView );

	HENHMETAFILE hMeta = dcMeta.CloseEnhanced();


	if ( SetClipboardData(CF_ENHMETAFILE, hMeta) == NULL ) {
		AfxMessageBox( "Select Failed in SetClipBoardData", MB_OK | MB_ICONEXCLAMATION );
	}

// CBitmap
//
	if ( !CloseClipboard() ) {
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}

	ReleaseDC(pDC);	// Moved this down here so nt4.0 would work.
	return;

}

#endif
