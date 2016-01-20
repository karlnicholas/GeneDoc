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
// exportdl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog


CExportDlg::CExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportDlg)
	m_Device = -1;
	m_SelAllSeq = -1;
	m_ExportType = -1;
	//}}AFX_DATA_INIT
}

void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDlg)
	DDX_Control(pDX, IDC_LISTSEQUENCE, m_listSequence);
	DDX_Radio(pDX, IDC_FILE, m_Device);
	DDX_Radio(pDX, IDC_SELALLSEQ, m_SelAllSeq);
	DDX_Radio(pDX, IDC_EXPORTTYPE, m_ExportType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportDlg, CDialog)
	//{{AFX_MSG_MAP(CExportDlg)
	ON_BN_CLICKED(IDEXPORT, OnExport)
	ON_BN_CLICKED(IDC_SELALLSEQ, OnSelallseq)
	ON_BN_CLICKED(IDC_SELLISTSEQ, OnSellistseq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExportDlg message handlers

void CExportDlg::OnExport() 
{
	// TODO: Add your control notification handler code here

	int Selected = 0;
	int *SelArray = NULL;

	UpdateData();

	if ( m_SelAllSeq ) {

		int SelCount = m_listSequence.GetSelCount();
		
		if ( SelCount == 0 || SelCount == LB_ERR ) return;
				   
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list

		if ( pGSFiller == NULL ) return;

		SelArray = new int[SelCount];
		
		m_listSequence.GetSelItems( SelCount, SelArray );

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			tCGSeg->SetExportFlag(0);

		}

		for ( int i=SelCount-1; i >=0; --i ) {

			int SeqSel = SelArray[i];
			
			CGSFiller *pGSFiller = pDoc->pGSFiller;
			// Put the data rows on the list

			POSITION tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

			tCGSeg->SetExportFlag(1);

		}

		Selected = TRUE;
	}
	
	CString PathName;
	//	static char Filter[] = 
//		"Phylip (*.phy)|*.phy|Clustal (*.aln)|*.aln|PIR (*.pir)|*.pir|Fasta (Pearson)(*.aa)|*.aa||";

    if ( m_Device == 0 ) {
		CString possName = pDoc->GetTitle().SpanExcluding(".");
		CFileDialog tDlg( FALSE, NULL, possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
		
		if ( tDlg.DoModal() != IDOK ) {
			return;
		}
		PathName = tDlg.GetPathName();

		if ( m_ExportType == 0  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".aa";
		} else if ( m_ExportType == 1  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".aln";
		} else if ( m_ExportType == 2  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".phy";
		} else if ( m_ExportType == 3  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".pir";
		} else if ( m_ExportType == 4  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".txt";
		} else if ( m_ExportType == 5  ) {
			if ( tDlg.GetFileExt() == "" ) PathName += ".txt";
		}

	} else {

		GetTempFileName(PathName);
	}
	
	
	BeginWaitCursor();
	                                     
	// OPENFILENAME
	
	if ( m_ExportType == 0  ) {
		pDoc->WriteFastaFile ( PathName, Selected );
	} else if ( m_ExportType == 1  ) {
		pDoc->WriteALNFile ( PathName, Selected );
	} else if ( m_ExportType == 2  ) {
		pDoc->WritePhylipFile ( PathName, Selected );
	} else if ( m_ExportType == 3  ) {
		pDoc->WritePIRFile ( PathName, Selected );
	} else if ( m_ExportType == 4  ) {
		pDoc->WriteTextFile ( PathName, Selected );
	} else if ( m_ExportType == 5  ) {
		pDoc->WriteTNoGapFile ( PathName, Selected );
	} else if ( m_ExportType == 6  ) {
		pDoc->WriteFasNTFile ( PathName, Selected );
	}
	
    if ( m_Device != 0 ) {
		if ( !OpenClipboard() ) {
			AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		
		
		if ( !EmptyClipboard() ) {
			AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
			return;
		}


		HANDLE hText;

		DWORD dwCount = 0;
		char *pText;
		

TRY {

		CFile oFile( (const char *)PathName, CFile::modeRead | CFile::typeBinary );
		dwCount = oFile.GetLength();


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
		

		oFile.Read( pText, dwCount );

		GlobalUnlock( hText );

		oFile.Close();
		
		CFile::Remove((const char *)PathName);

		if ( SetClipboardData ( CF_TEXT, hText ) == NULL ) {
			AfxMessageBox( "SetClipboardData Fails" );
		}
		
		if ( !CloseClipboard() ) {
			AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
		}

} 
CATCH (CFileException, e ) {
	if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	GlobalUnlock( hText );
	return;
}
END_CATCH

	}
	EndWaitCursor(); // Let em know

	if ( m_SelAllSeq ) {
		m_listSequence.SelItemRange(FALSE, 0, m_listSequence.GetCount()-1 );

		if ( SelArray != NULL ) delete SelArray;
	}

    m_listSequence.Invalidate();
	
	return;
	
}


BOOL CExportDlg::OnInitDialog() 
{
	m_SelAllSeq = 0;	// Set True.
	m_Device = 0;
	m_ExportType = 0;
	CDialog::OnInitDialog();
	
	m_listSequence.EnableWindow(FALSE);
	// TODO: Add extra initialization here

	m_listSequence.ResetContent();
	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			m_listSequence.AddString(tCGSeg->GetTitle());
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportDlg::OnSelallseq() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_listSequence.Invalidate();
	m_listSequence.EnableWindow(FALSE);
	
}

void CExportDlg::OnSellistseq() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_listSequence.Invalidate();
	m_listSequence.EnableWindow(TRUE);
	
}
