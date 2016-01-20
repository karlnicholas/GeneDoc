// ScoreInfoEdit.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreInfoEditView

IMPLEMENT_DYNCREATE(CScoreInfoEditView, CEditView)

CScoreInfoEditView::CScoreInfoEditView()
{
	m_pFont = new CFont;
	if ( m_pFont == NULL ) {
		AfxMessageBox("ScoreInfoEditview:new:fail");
	}
}

CScoreInfoEditView::~CScoreInfoEditView()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pScoreInfoView = NULL;
	delete m_pFont;
}


BEGIN_MESSAGE_MAP(CScoreInfoEditView, CEditView)
	//{{AFX_MSG_MAP(CScoreInfoEditView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScoreInfoEditView drawing

/*
void CScoreInfoEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

*/

/////////////////////////////////////////////////////////////////////////////
// CScoreInfoEditView message handlers
 
void CScoreInfoEditView::LoadFile()
{
	CGenedocDoc* pDoc = (CGenedocDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CFile theFile;

	CString PathName = pDoc->ConvertPathname( ".tsd" );
    
	if ( theFile.Open(PathName, CFile::modeRead) ) {
		CArchive archive(&theFile, CArchive::load);

		SerializeRaw( archive );
	}

	pDoc->m_pScoreInfoView = this;

}

int CScoreInfoEditView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_pFont->CreateFont(12,0,0,0,400,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		FIXED_PITCH,"Courier"));
	SetFont(m_pFont);

	// TODO: Add your specialized creation code here
	LoadFile();	

	return 0;
}
