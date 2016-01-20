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
// genedoc.h : main header file for the GENEDOC application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGenedocApp:
// See genedoc.cpp for the implementation of this class
//

class CGenedocApp : public CWinApp
{
public:
	CGenedocApp();

// Overrides
	virtual BOOL InitInstance();
//	virtual CDocument* OpenDocumentFile( LPCSTR lpszFileName );

// Implementation
	CMultiDocTemplate* m_pGenedocTemplate;

	CDocument* CreateNewDocument();
	void SetLandscape(int LSFlag );
	int GetLandscape();
	void OnMyFilePrintSetup();
	int m_OKOrientCheck;
	CMultiDocTemplate *m_pSummaryViewTemplate;
	CMultiDocTemplate *m_pTextViewTemplate;
	CMultiDocTemplate *m_pTreeViewTemplate;
	CMultiDocTemplate *m_pDStatViewTemplate;
	CMultiDocTemplate *m_pGelViewTemplate;
	int ExitInstance();
	
	int m_ReallyNewFlag;


	//{{AFX_MSG(CGenedocApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
