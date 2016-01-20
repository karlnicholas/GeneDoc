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
// phylodlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog dialog


CPhyloGenDialog::CPhyloGenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPhyloGenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhyloGenDialog)
	m_ParseString = "";
	//}}AFX_DATA_INIT
}

void CPhyloGenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhyloGenDialog)
	DDX_Control(pDX, IDC_PHYLOEDIT, m_PhyloEdit);
	DDX_Text(pDX, IDC_PHYLOEDIT, m_ParseString);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPhyloGenDialog, CDialog)
	//{{AFX_MSG_MAP(CPhyloGenDialog)
	ON_BN_CLICKED(IDC_PHYLOEXPORT, OnPhyloexport)
	ON_BN_CLICKED(IDC_PHYLOIMPORT, OnPhyloimport)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PHYLOCOPY, OnPhylocopy)
	ON_BN_CLICKED(IDC_PHYLOPASTE, OnPhylopaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog message handlers

void CPhyloGenDialog::OnPhyloexport()
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "Phylogen Files (*.ph|*.ph|All Files (*.*)|*.*||";

	CFileDialog tDlg( FALSE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		Filter, NULL
	);
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	
	// Start, Open the file
	// CFile
TRY {

	CStdioFile wFile ( tDlg.GetPathName(), CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	wFile.WriteString( m_ParseString );
	
	wFile.Close();
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

void CPhyloGenDialog::GetParseFile( const CString& FileName )
{
	// TODO: Add your control notification handler code here
TRY {
#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif
	CString tString;
	CString BuildString;
	// Start, Open the file
	CStdioFile iFile ( FileName, CFile::modeRead | CFile::typeText );
	
	while (1) {
		// clear out temp string.
		tString.Empty();
#if !defined(_WIN32) || _MSC_VER < 999
		if ( iFile.ReadString( rbuff, sizeof(rbuff)) == NULL ) {
			break;		
		}
		tString = rbuff;
#else
		if ( !iFile.ReadString( tString ) ) {
			break;		
		}
#endif		
//		tString.SetAt(tString.GetLength() - 1, '\r');
		tString += '\r';
		tString += '\n';
		BuildString += tString;

//		if ( tString.Find(";") != -1 ) {
//			break;
//		}
	}

	iFile.Close();
	
	m_ParseString = BuildString;
	
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

void CPhyloGenDialog::OnPhyloimport()
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "Tree Files (*.ph)|*.ph|All Files (*.*)|*.*||";


	CFileDialog tDlg( TRUE, NULL, NULL, 
		OFN_HIDEREADONLY, 
		Filter, NULL
	);

	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	GetParseFile ( tDlg.GetPathName() );

	UpdateData(FALSE);

}



int CPhyloGenDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CenterWindow();
	
	return 0;
}

void CPhyloGenDialog::OnPhylocopy()
{
	// TODO: Add your control notification handler code here
	m_PhyloEdit.Copy();
	
}

void CPhyloGenDialog::OnPhylopaste()
{
	// TODO: Add your control notification handler code here
	m_PhyloEdit.Paste();
	
}
