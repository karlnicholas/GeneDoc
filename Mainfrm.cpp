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
// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_POS, OnUpdatePos)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
	ID_CONTEXT_HELP,
		ID_SEPARATOR,
	IDM_CONFIGURE,
	IDM_GENEEDITSEQ, 
	IDM_EDITGROUPPROP, 
		ID_SEPARATOR,
	IDM_GENEVIEW,
	IDM_SUMMARYVIEW, 
	IDM_GENEREPORTVIEW, 
	IDM_PHYLOVIEW, 
	IDM_GENEDSTATVIEW, 
	IDM_GENEGELVIEW, 
		ID_SEPARATOR,
	IDM_GENESTATFILE,
	IDM_GENESCOREFILE, 
	IDM_DNAFFREQREP, 
		ID_SEPARATOR,
	IDM_SHOWMANSHADE, 
	IDM_SHOWCOMMENTS 
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	strPosSeqName[0] = 0;
	dwPosLoc = 0L;

}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnUpdatePos(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    char szText[40];
    if ( dwPosLoc == 0L && strPosSeqName[0] == 0) {
    	szText[0] = 0;
    } else if ( dwPosLoc == 0L ) {
    	_snprintf(szText, 40, "%s:", strPosSeqName ); 
    } else {
    	_snprintf(szText, 40, "%s: %ld", strPosSeqName, dwPosLoc ); 
	}    
    pCmdUI->SetText( szText); 
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
#ifdef _WIN32
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS) ||
#else
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP) ||
#endif
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/////////////////////////////////////////////////////////////////////////////
// Helpers for saving/restoring window state

static TCHAR BASED_CODE szSection[] = _T("Settings");
static TCHAR BASED_CODE szWindowPos[] = _T("WindowPos");
static TCHAR szFormat[] = _T("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d");

static BOOL PASCAL NEAR ReadWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	CString strBuffer = AfxGetApp()->GetProfileString(szSection, szWindowPos);
	if (strBuffer.IsEmpty())
		return FALSE;

	WINDOWPLACEMENT wp;
	int nRead = _stscanf(strBuffer, szFormat,
		&wp.flags, &wp.showCmd,
		&wp.ptMinPosition.x, &wp.ptMinPosition.y,
		&wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
		&wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
		&wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

	if (nRead != 10)
		return FALSE;

	wp.length = sizeof wp;
	*pwp = wp;
	return TRUE;
}

static void PASCAL NEAR WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
	// write a window placement to settings section of app's ini file
{
	TCHAR szBuffer[256];

	wsprintf(szBuffer, szFormat,
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
	AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}

/////////////////////////////////////////////////////////////////////////////

void CMainFrame::InitialShowWindow(UINT nCmdShow)
{
	WINDOWPLACEMENT wp;
	if (!ReadWindowPlacement(&wp))
	{
		ShowWindow(nCmdShow);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
	SetWindowPlacement(&wp);
	ShowWindow(wp.showCmd);
}

void CMainFrame::OnClose()
{
	// before it is destroyed, save the position of the window
	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		wp.flags = 0;
		if (IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the .INI file
		WriteWindowPlacement(&wp);
	}

	CMDIFrameWnd::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
void 
CMainFrame::OpenSummaryView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Create Summary View Fails 1: File Only", MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pSummaryViewTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Summary View Fails 2: File Only", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}

void
GetTempFileName (CString& PathName )
{
#ifdef _WIN32
		CString TempPath;
		char *pcp = TempPath.GetBuffer(MAX_PATH);
		::GetTempPath( MAX_PATH, pcp );
		char * pcn = PathName.GetBuffer(MAX_PATH);
		::GetTempFileName( pcp, "gdc", 0, pcn );
		TempPath.ReleaseBuffer();
		PathName.ReleaseBuffer();
#else
		char * pcn = PathName.GetBuffer(1024);
		::GetTempFileName( 0, "gdc", 0, pcn );
		PathName.ReleaseBuffer();

#endif
}

void
DeleteTempFile(CString& PathName )
{
	CFile::Remove( PathName );
}

void 
CMainFrame::OpenTextView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Create Text View Fails: File Only", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pTextViewTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Text View Fails: File Only", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}


void 
CMainFrame::OpenTreeView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Unknown Active Document", MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pTreeViewTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Tree View Fails", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}

void 
CMainFrame::OpenGeneView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Unknown Active Document", MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pGenedocTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Tree View Fails", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}

void 
CMainFrame::OpenDStatView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Create Score Info View Fails 1: File Only", MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pDStatViewTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Score Info View Fails 2: File Only", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}

void 
CMainFrame::OpenGelView()
{
	CMDIChildWnd *pActiveChild = MDIGetActive();
	CDocument *pDocument;
	if ( pActiveChild == NULL ||
		(pDocument = pActiveChild->GetActiveDocument()) == NULL ) 
	{
		AfxMessageBox( "Create Score Info View Fails 1: File Only", MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	// Create new frame
	CDocTemplate *pTemplate = ((CGenedocApp *) AfxGetApp())->m_pGelViewTemplate;
	ASSERT_VALID(pTemplate);
	CFrameWnd *pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);

	if ( pFrame == NULL )
	{
		AfxMessageBox("Create Score Info View Fails 2: File Only", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	pTemplate->InitialUpdateFrame( pFrame, pDocument );
}

