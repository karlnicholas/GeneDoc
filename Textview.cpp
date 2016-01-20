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
// TextView.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, VIEWBASE)

CTextView::CTextView()
{
	m_pFont = new CFont;
	if ( m_pFont == NULL ) {
		AfxMessageBox("textview:new:fail");
	}
}

CTextView::~CTextView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pTextView = NULL;
	delete m_pFont;
}


BEGIN_MESSAGE_MAP(CTextView, VIEWBASE)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_REPSAVEFILE, OnRepsavefile)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, VIEWBASE::OnFilePrint)
#ifdef WIN32
	ON_COMMAND(ID_FILE_PRINT_DIRECT, VIEWBASE::OnFilePrint)
#endif
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, VIEWBASE::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnInitialUpdate()
{
	VIEWBASE::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
#ifdef WIN32
	SetMargins(CRect(720, 720, 720, 720));
#endif
	
}


BOOL CTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

/*
void CTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

*/
CDocument *CTextView::GetDocument()
{
	return m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

#ifdef WIN32

CFile *txtFile;


DWORD CALLBACK TextRead(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// CFile
	*pcb = txtFile->Read(pbBuff, cb );
	return 0;
}

 
void CTextView::LoadFile(CString& PathName)
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	txtFile = new CFile();
   
	txtFile->Open(PathName, CFile::modeRead );
//	CArchive archive(&txtFile, CArchive::load);

//	SerializeRaw( archive );

	EDITSTREAM es;
	es.pfnCallback = TextRead;

	GetRichEditCtrl().StreamIn( SF_TEXT, es );

	txtFile->Close();
	delete txtFile;

}

#else

void CTextView::LoadFile(CString& PathName)
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFile txtFile;

	txtFile.Open(PathName, CFile::modeRead );

	CArchive archive(&txtFile, CArchive::load);

	SerializeRaw( archive );

//	txtFile.Close();

}

#endif

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{                               
#ifdef WIN32
	m_nWordWrap = VIEWBASE::WrapNone;
#endif

	if (VIEWBASE::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_pFont->CreateFont(14,0,0,0,400,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		FIXED_PITCH,"Courier New"));
	SetFont(m_pFont);

#ifdef WIN32
	GetRichEditCtrl().SetOptions( ECOOP_OR, ECO_READONLY );
#else
	GetEditCtrl().SetReadOnly();
#endif
  
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_pTextView = this;

	return 0;
}

void CTextView::OnRepsavefile() 
{
	// TODO: Add your command handler code here
	CFileDialog tDlg(FALSE);

	if ( tDlg.DoModal() != IDOK ) return;


	SaveFile( tDlg.GetPathName() ); // Let em know



	
}
#ifdef WIN32


DWORD CALLBACK TextWrite(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// CFile
	txtFile->Write(pbBuff, cb );
	*pcb = cb;
	return 0;
}

void CTextView::SaveFile(CString& PathName)
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	txtFile = new CFile();
   
	txtFile->Open( PathName, CFile::modeCreate | CFile::modeWrite );

	//	CArchive archive(&txtFile, CArchive::load);

//	SerializeRaw( archive );

	EDITSTREAM es;
	es.pfnCallback = TextWrite;

	GetRichEditCtrl().StreamOut( SF_TEXT, es );

	txtFile->Close();
	delete txtFile;

}

#else

void CTextView::SaveFile(CString& PathName)
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFile txtFile;

	txtFile.Open( PathName, CFile::modeCreate | CFile::modeWrite );

	CArchive archive(&txtFile, CArchive::store);

	SerializeRaw( archive );

	txtFile.Close();
}

#endif
