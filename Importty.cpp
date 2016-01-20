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
// importty.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportTypeDlg dialog


CImportTypeDlg::CImportTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportTypeDlg)
	m_ImportType = -1;
	m_Device = -1;
	//}}AFX_DATA_INIT
}

void CImportTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportTypeDlg)
	DDX_Radio(pDX, IDC_IMPORTTYPE0, m_ImportType);
	DDX_Radio(pDX, IDC_FILE, m_Device);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImportTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CImportTypeDlg)
	ON_BN_CLICKED(IDIMPORT, OnImport)
	ON_BN_CLICKED(IDC_INPUT, OnInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CImportTypeDlg message handlers

BOOL CImportTypeDlg::OnInitDialog() 
{
	m_Device = 0;
	m_ImportType = 0;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportTypeDlg::OnImport() 
{
	// TODO: Add your control notification handler code here
	CString PathName;
	CString SegSug;
	UpdateData();

	if ( m_Device == 0 ) {

		static char Filter[] = 
			"All Files (*.*)|*.*||";

		CFileDialog tDlg( TRUE, NULL, NULL, 
			OFN_HIDEREADONLY, 
			Filter, NULL
		);

		if ( tDlg.DoModal() != IDOK ) {
			return;
		}

		PathName = tDlg.GetPathName();
		SegSug = tDlg.GetFileTitle();
	} else {

		if ( !OpenClipboard() ) {
			AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		

		HANDLE hText;

		
		if ( (hText = GetClipboardData ( CF_TEXT )) == NULL ) {
			AfxMessageBox( "GetClipboardData Fails" );
		}

		DWORD Count = GlobalSize( hText );

		char *pText = (char *)GlobalLock ( hText );
		if ( pText == NULL ) {
			EndWaitCursor(); // Let em know
			AfxMessageBox("GlobalLock Fails");
			GlobalFree(hText);
			return;
		}

		GetTempFileName(PathName);

TRY {

		CFile oFile( (const char *)PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary );

		oFile.Write ( pText, (int)Count );

		oFile.Close();
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


		GlobalUnlock( hText );
		
		if ( !CloseClipboard() ) {
			AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
		}

	}

	BeginWaitCursor(); // Let em know

	switch ( m_ImportType ) {
	case 0:
		pDoc->GetFastaFile ( PathName, 1 );
		break;
	case 1:
		pDoc->GetALNFile ( PathName, 1 );
		break;
	case 2:
		pDoc->GetPhylipFile ( PathName, 1 );
		break;
	case 3:
		pDoc->GetFasNTFile ( PathName, 1 );
		break;
	case 4:
		pDoc->GetPIRFile ( PathName, 1 );
		break;
	case 5:
		pDoc->GetMSFFile ( PathName, 1 );
		break;
	case 6:
		{
			EndWaitCursor(); // Let em know
			CSeqDetDialog sDlg;
			sDlg.m_SeqWeight = 1.0;
			sDlg.m_TextStart = 1;
			sDlg.m_SeqName = SegSug;
			if ( sDlg.DoModal() != IDOK ) {
				return;
			}
			if ( !sDlg.m_SeqName.GetLength() ) {
				AfxMessageBox("Need to enter sequence name");
				return;
			}
			BeginWaitCursor(); // Let em know
			pDoc->GetTextFile ( PathName, 1, 
				sDlg.m_SeqName, sDlg.m_SeqWeight, sDlg.m_TextStart, sDlg.m_Descr, 0 );
		}
		break;
	case 7:
		{
			EndWaitCursor(); // Let em know
			CSeqDetDialog sDlg;
			sDlg.m_SeqWeight = 1.0;
			sDlg.m_TextStart = 1;
			sDlg.m_SeqName = SegSug;
			if ( sDlg.DoModal() != IDOK ) {
				return;
			}
			if ( !sDlg.m_SeqName.GetLength() ) {
				AfxMessageBox("Need to enter sequence name");
				return;
			}
			BeginWaitCursor(); // Let em know
			pDoc->GetTextFile ( PathName, 1, 
				sDlg.m_SeqName, sDlg.m_SeqWeight, sDlg.m_TextStart, sDlg.m_Descr, 1 );
		}
		break;
	case 8:
		pDoc->GetGenbankFile ( PathName, 1 );
		break;
	}

	EndWaitCursor(); // Let em know
	
	if ( m_Device ) {

TRY {

		CFile::Remove( (const char *)PathName );

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "Delete File Not Found Error" );
	else
		AfxMessageBox( "Delete File Error" );

	return;
}
END_CATCH
	}


}


/*
#ifdef _WIN32
	static char Filter[] = 
		"Fasta (*.aa*)|*.aa*|Clustal (*.aln*)|*.aln*|Phylip (*.phy*)|*.phy*|PIR (*.pir*)|*.pir*|GCG MSF(*.msf*)|*.msf*|All Files (*.*)|*.*||";
#else
	static char Filter[] = 
		"Fasta (*.aa)|*.aa|Clustal (*.aln)|*.aln|Phylip (*.phy*)|*.phy*|PIR (*.pir)|*.pir|GCG MSF(*.msf)|*.msf|All Files (*.*)|*.*||";
#endif

	CFileDialog tDlg( TRUE, NULL, NULL, 
		OFN_HIDEREADONLY, 
		Filter, NULL
	);

	if ( tDlg.DoModal() != IDOK ) {
		return 0;
	}

	int rc = 1;

	BeginWaitCursor(); // Let em know

	if ( tDlg.GetFileExt().CompareNoCase( "MSF" ) == 0 || tDlg.m_ofn.nFilterIndex == 5 ) {
		if ( !GetMSFFile ( tDlg.GetPathName(), 1 ) ) {
			rc = 0;
		}
	} else if ( tDlg.GetFileExt().CompareNoCase( "AA" ) == 0 || tDlg.m_ofn.nFilterIndex == 1) {
		if ( !GetFastaFile ( tDlg.GetPathName(), 1 ) ) {
			rc = 0;
		}
	} else if ( tDlg.GetFileExt().CompareNoCase( "ALN" ) == 0 || tDlg.m_ofn.nFilterIndex == 2 ) {
		if ( !GetALNFile ( tDlg.GetPathName(), 1 ) ) {
			rc = 0;
		}
	} else if ( tDlg.GetFileExt().CompareNoCase( "PHY" ) == 0 || tDlg.m_ofn.nFilterIndex == 3 ) {
		if ( !GetPhylipFile ( tDlg.GetPathName(), 1 ) ) {
			rc = 0;
		}
	} else if ( tDlg.GetFileExt().CompareNoCase( "PIR" ) == 0 || tDlg.m_ofn.nFilterIndex == 4 ) {
		if ( !GetPIRFile ( tDlg.GetPathName(), 1 ) ) {
			rc = 0;
		}
	} else {
		CImportTypeDlg typeDlg;
		if ( typeDlg.DoModal() == IDOK ) {
*/

void CImportTypeDlg::OnInput() 
{
	// TODO: Add your control notification handler code here

	CSeqInput tDlg;

	if ( tDlg.DoModal() != IDOK ) return;

//	if ( !pDoc->SequenceImport() ) return;
	CPtrList CommentList;
	CPtrList SequenceList;

	// CEdit
	if ( tDlg.m_DataString.GetLength() == 0 ) return;

	SeqNameStruct *tSNS;
	tSNS = new SeqNameStruct;
	tSNS->Name = tDlg.m_SeqName;
	tSNS->Descr = tDlg.m_Descr;
	tSNS->Check = 1234;
	tSNS->Weight = 1.0;

	tSNS->Len = tDlg.m_DataString.GetLength();
	tSNS->Start = 1;
	tSNS->hText = GlobalAlloc ( GMEM_FLAG, tSNS->Len );
	// Abort if alloc fails
	if ( tSNS->hText == NULL ) {
		AfxMessageBox("Input Seq:GlobalAlloc:Fail 1");
		return;
	}

	char *pc = (char *)GlobalLock(tSNS->hText);
	memcpy ( pc, (const char *)tDlg.m_DataString, (unsigned int)tSNS->Len );
	char tGapChar = pDoc->m_UserVars.m_GapInd ? '.' : '-';
	DWORD cLen = tSNS->Len;
	while ( cLen-- ) {
		if ( *pc == '.' || * pc == '|' ) *pc = tGapChar;
		pc++;
	}

	GlobalUnlock( tSNS->hText );

	pDoc->gMaxStrSize = tSNS->Len;

	SequenceList.AddTail( tSNS );

	if ( !pDoc->ProcessRows( CommentList, SequenceList, 1 ) ) {
		delete tSNS;
		return;
	}
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	if ( pGSFiller == NULL ) {
		delete tSNS;
		return;
	}
}
