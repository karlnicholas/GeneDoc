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
// DStatView.cpp : implementation of the CDStatView class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDStatView

IMPLEMENT_DYNCREATE(CDStatView, CScrollView)

BEGIN_MESSAGE_MAP(CDStatView, CScrollView)
	//{{AFX_MSG_MAP(CDStatView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_DSTATCOPY, OnEditCopy)
	ON_COMMAND(IDM_DSTATGRAPHSETUP, OnGraphsetup)
	ON_COMMAND(IDM_DSTATWRITEDATA, OnWriteoutput)
	ON_COMMAND(IDM_DSTATREADSETS, OnDatafile)
	ON_COMMAND(IDM_DSTATREADSET1, OnReadset1)
	ON_COMMAND(IDM_DSTATREADSET2, OnReadset2)
	ON_COMMAND(IDM_DSTATWRITESCORE, OnDstatwritescore)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDStatView construction/destruction

CDStatView::CDStatView()
{
	// TODO: add construction code here
}

CDStatView::~CDStatView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pDStatView = NULL;

}

BOOL CDStatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDStatView drawing

void CDStatView::OnDraw(CDC* pDC)
{
	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->DStatObject.DoDraw( pDC );
}


void CDStatView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDC* pDC = GetDC();
	
	double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpi = pDC->GetDeviceCaps(LOGPIXELSX);

	ReleaseDC(pDC);

	int x = (int)((double)GetDocument()->DStatObject.GetDocSize().cx/100.0 * xpi);
	int y = (int)((double)GetDocument()->DStatObject.GetDocSize().cy/100.0 * ypi);

	SetScrollSizes(MM_TEXT, CSize(x, y) );

	ResizeParentToFit(FALSE);

	CScrollView::OnUpdate( pSender, lHint, pHint);
	
}

/////////////////////////////////////////////////////////////////////////////
// CDStatView printing

BOOL CDStatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDStatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDStatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDStatView diagnostics

#ifdef _DEBUG
void CDStatView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDStatView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGenedocDoc* CDStatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenedocDoc)));
	return (CGenedocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDStatView message handlers

#ifndef _WIN32

void CDStatView::OnEditCopy() 
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

	int x = (int)((double)GetDocument()->DStatObject.GetDocSize().cx/100.0 * xpi);
	int y = (int)((double)GetDocument()->DStatObject.GetDocSize().cy/100.0 * ypi);

	CSize tSize(x,y);
	pDC->DPtoHIMETRIC(&tSize);

	dcMeta.SetAttribDC( pDC->m_hAttribDC );

	OnPrepareDC( &dcMeta );

	OnDraw( &dcMeta );

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

/*
void CDStatView::OnEditCopyfile() 
{
}
*/
#else 

void CDStatView::OnEditCopy() 
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
/*

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double ypid = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpid = pDC->GetDeviceCaps(LOGPIXELSX);

	int tXSize, tYSize;

	tXSize = (int)(((double)GetDocument()->DStatObject.GetDocSize().cx/100.0 * xpid) * xpi * 100.0);

	tYSize = (int)(((double)GetDocument()->DStatObject.GetDocSize().cy/100.0 * ypid) * ypi * 100.0);


	CRect rectView(0,0,tXSize, tYSize );
*/

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double tXSize, tYSize;

	tXSize = GetDocument()->DStatObject.GetDocSize().cx * xpi * 100.0;

	tYSize = GetDocument()->DStatObject.GetDocSize().cy * ypi * 100.0;

	CRect rectView(0,0,(int)tXSize, (int)tYSize );

	CMetaFileDC dcMeta;

	dcMeta.CreateEnhanced(pDC, NULL, rectView, "GeneDoc\0MetaFile\0\0" );

	dcMeta.SetAttribDC( pDC->m_hAttribDC );


	OnPrepareDC( &dcMeta );


//	CMetaFileDC dcMeta;

//	dcMeta.CreateEnhanced(pDC, NULL, rectView, "XYZ Graphics Editor\0Bald Eagle\0\0" );

//	dcMeta.SetAttribDC( pDC->m_hAttribDC );

//	ReleaseDC(pDC);

//	OnPrepareDC( &dcMeta );

	OnDraw( &dcMeta );

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

/*

void CDStatView::OnEditCopyfile() 
{
	static char BASED_CODE szFilter[] = "Meta Files (*.emf)|*.emf|All Files (*.*)|*.*||";

	CGenedocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// CDocument

	CFileDialog tDlg(FALSE, "emf", pDoc->GetTitle(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this );

	if ( tDlg.DoModal() != IDOK ) return;

	CDC* pDC = GetDC();

	double xpi = (double)pDC->GetDeviceCaps(HORZSIZE) / (double)pDC->GetDeviceCaps(HORZRES);
	double ypi = (double)pDC->GetDeviceCaps(VERTSIZE) / (double)pDC->GetDeviceCaps(VERTRES);

	double tXSize, tYSize;

	tXSize = GetDocument()->DStatObject.GetDocSize().cx * xpi * 100.0;

	tYSize = GetDocument()->DStatObject.GetDocSize().cy * ypi * 100.0;

	CRect rectView(0,0,tXSize, tYSize );

	CMetaFileDC dcMeta;

	dcMeta.CreateEnhanced(pDC, tDlg.GetPathName(), rectView, "XYZ Graphics Editor\0Bald Eagle\0\0" );

	dcMeta.SetAttribDC( pDC->m_hAttribDC );

	ReleaseDC(pDC);

	OnPrepareDC( &dcMeta );

	OnDraw( &dcMeta );


	HENHMETAFILE hMeta = dcMeta.CloseEnhanced();

	return;
	
}

*/

#endif

int CDStatView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pDStatView = this;
	
	return 0;
}


void CDStatView::OnGraphsetup()
{
	// TODO: Add your command handler code here

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->DStatObject.OnGraphsetup();

	Invalidate();
	
}

void CDStatView::OnDstatwritescore()
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	static char Filter[] = "Sco Files (*.sco)|*.sco||";

	CString possName = pDoc->ConvertPathname ( ".sco" );
	
	CFileDialog tDlg( FALSE, "sco", possName, OFN_OVERWRITEPROMPT, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	pDoc->DStatObject.WriteData(tDlg.GetPathName() ); 
     
}

void CDStatView::OnWriteoutput() 
{
	// TODO: Add your command handler code here
	// CDocument

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

//	if ( pDoc->DStatObject.m_ScoreCount1 == 0 ||  pDoc->DStatObject.m_ScoreCount2  == 0 ) {
//		AfxMessageBox("One or More Score Arrays have a zero Count!" );
//		return;
//	}

	static char Filter[] = "Plt Files (*.plt)|*.plt|All Files (*.*)|*.*||";

	CString possName = pDoc->ConvertPathname ( ".plt" );
	CFileDialog tDlg( FALSE, "plt", possName, OFN_OVERWRITEPROMPT, Filter, NULL );

	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	pDoc->DStatObject.OnWriteoutput(tDlg.GetPathName() ); 

}

void CDStatView::OnDatafile() 
{
	// TODO: Add your command handler code here
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, "sco", pDoc->GetTitle(), 0, Filter, NULL );
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	pDoc->DStatObject.DeleteContents();
	
/*
	CTSide tsDlg;

	tsDlg.m_TSide = DStatObject.GetTSide();

	if ( tsDlg.DoModal() == IDOK ) {
		DStatObject.SetTSide ( tsDlg.m_TSide );
	}
*/
	pDoc->DStatObject.OnDatafile( tDlg.GetPathName() );

	Invalidate();
}


void CDStatView::OnReadset1() 
{
	// TODO: Add your command handler code here
	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, NULL, NULL, 0, Filter, NULL );

	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->DStatObject.DeleteSet1();
	
	pDoc->DStatObject.OnSet1( tDlg.GetPathName() );

	Invalidate();
	
}

void CDStatView::OnReadset2() 
{
	// TODO: Add your command handler code here
	static char Filter[] = "All Files (*.*)|*.*||";
	CFileDialog tDlg( TRUE, NULL, NULL, 0, Filter, NULL );
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->DStatObject.DeleteSet2();
	
	pDoc->DStatObject.OnSet2( tDlg.GetPathName() );

	Invalidate();
}


