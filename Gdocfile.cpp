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


#include "stdafx.h"
#include <ctype.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
int i;

int   
CGenedocDoc::ReadGenbankFile( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.
	CString LOCUS;
	CString DEFINITION;
	CString ACCESSION;
	CString NID;
	CString PID;
	CString Trans;
	CString Origin;

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	
	int EOFFLAG = 0;
	int gettingorigin = 0;
	int gettingtrans = 0;
	int Loc;

	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( !tString.GetLength() ) continue;

		if ( gettingtrans == 1 ) {
			Trans += tString;
			if ( Trans.Find( "\"" ) != -1 ) {
				gettingtrans = 0;
			}
		} else if ( gettingorigin == 1 ) {
			if ( Trans.Find( "//" ) != -1 ) {
				gettingorigin = 0;
			} else {
				Origin += tString;
			}
		}

		if ( tString.Find("LOCUS") != -1 ) {
			char *pc = LOCUS.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			LOCUS.ReleaseBuffer();
		} else if ( tString.Find("DEFINITION") != -1 ) {
			DEFINITION = tString.Mid( 12 );
		} else if ( tString.Find("ACCESSION") != -1 ) {
			char *pc = ACCESSION.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			ACCESSION.ReleaseBuffer();
		} else if ( tString.Find("NID") != -1 ) {
			char *pc = NID.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			NID.ReleaseBuffer();
		} else if ( tString.Find("PID") != -1 ) {
			char *pc = PID.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			PID.ReleaseBuffer();
		} else if ( (Loc = tString.Find("/translation=")) != -1 ) {
			Trans = tString.Mid( Loc + 14 );
			if ( Trans.Find( "\"" ) == -1 ) {
				gettingtrans = 1;
			}
		} else if ( (Loc = tString.Find("ORIGIN")) != -1 ) {
			gettingorigin = 1;
		}




	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	rFile.Close();

	gMaxStrSize = 0;

	CGenbank Dlg;
	Dlg.LOCUS = LOCUS;
	Dlg.ACCESSION = ACCESSION;
	Dlg.NID = NID;
	Dlg.PID = PID;
	if ( Dlg.DoModal() != IDOK ) return 0;

	tSNS = new SeqNameStruct;

	switch (Dlg.m_Locus) {
		case 0:
		tSNS->Name = LOCUS;
		break;
	case 1:
		tSNS->Name = ACCESSION;
		break;
	case 2:
		tSNS->Name = NID;
		break;
	case 3:
		tSNS->Name = PID;
		break;
	}

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( CString(tSNS1->Name) == tSNS->Name ) {
			char ErrBuff[256];
			sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)tSNS->Name );
			delete tSNS;
			AfxMessageBox( ErrBuff );
			return 0;
		}
	}

	tSNS->Descr = DEFINITION;
	tSNS->Len = 0;
	tSNS->Start = 1;
	tSNS->Check = 1234;
	tSNS->Weight = 1.0;

	CString *data;
	switch ( Dlg.m_Trans ) {
	case 0:
		data = &Trans;
		break;
	case 1:
		data = &Origin;
		break;
	}
	CString dString;
	i = 0;
	int End = data->GetLength();
	while ( i < End ) {
		char tChar = toupper((*data)[i]);
		if ( tChar >= 'A' && tChar <= 'Z' ) dString += (*data)[i];
		i++;
	}
	if ( dString.GetLength() ) {
		tSNS->Len = dString.GetLength();
		tSNS->hText = GlobalAlloc( GMEM_FLAG, tSNS->Len);
		char *pRes = (char *)GlobalLock(tSNS->hText);
		char *pnRes = dString.GetBuffer(tSNS->Len);
		int MoveCount = tSNS->Len;
		while (MoveCount--) {
			*pRes++ = *pnRes++;
		}
		GlobalUnlock(tSNS->hText);
		dString.ReleaseBuffer();
	}

	gMaxStrSize = tSNS->Len;

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("TEXT Data not Found");
		return 0;
	}

	SequenceList->AddTail( tSNS );

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}



int   
CGenedocDoc::ReadFasNTFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	int NoRead = 0;

	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			if ( !NoRead ) {
				tString.Empty();
				char *tStr = tString.GetBuffer(1024);
				if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
					// Done .. break out
					EOFFLAG = 1;
					break;
				}
				tString.ReleaseBuffer();
				tString = tString.SpanExcluding("\n\r");
			} else {
				NoRead = 0;
			}

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();

		// Skip initial spaces ..
		for ( i=1; i<End; ++i ) {
			if ( tString[i] != ' ' ) break;
		}
		
		// Skip Now get names ..
		CString strName;
		CString strDescr;
		for ( ; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}
		if ( strName.GetLength() > 50 ) strName = strName.Left(50);
		strDescr = tString.Mid( strName.GetLength() + 1 );

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Descr = strDescr;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->Weight = 1.0;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );

		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			if ( tString[0] == '>' ) {
				NoRead = 1;
				EOFDATA = 1;
				break;
			}
			if ( tString[0] == ';' ) continue;

			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

//		if ( EOFFLAG ) {
//			delete (SeqNameStruct*)SequenceList->RemoveTail();
//			break;
//		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("FASTA Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenedocDoc::WriteFasNTFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, ">%s %s\n;\n;\n", (const char *)(pWS[i]).pCGSeg->GetTitle(), (const char *)(pWS[i]).pCGSeg->GetDescr());
			
		wFile.WriteString( BuildBuff );
	
		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				if ( tgs->CharGene == tGapChar ) {
					DataBlock[j] = '-';
				} else {
					DataBlock[j] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			if ( tgs->CharGene == tGapChar ) {
				DataBlock[j] = '-';
			} else {
				DataBlock[j] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int   
CGenedocDoc::ReadTextFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName, 
	const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	
	int EOFFLAG = 0;
	int NoRead = 0;

	tSNS = new SeqNameStruct;
	tSNS->Name = SeqName;
	tSNS->Descr = Descr;
	tSNS->Len = 0;
	tSNS->Start = TextStart;
	tSNS->Check = 1234;
	tSNS->Weight = SeqWeight;
	tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
	// Abort if alloc fails
	if ( tSNS->hText == NULL ) {
		AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
		rFile.Abort();
		return 0;
	}

	SequenceList->AddTail( tSNS );

	int EOFDATA = 0;
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
			break;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( !tString.GetLength() ) continue;

		int End = tString.GetLength();
		CString dString;
		i = 0;
		while ( i < End ) {
			if ( IUPAC ) {
				char tChar = toupper(tString[i]);
				if ( tChar >= 'A' && tChar <= 'Z' ) dString += tString[i];
			} else {
				if ( isgraph(tString[i]) ) dString += tString[i];
			}
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();
		}

	// Loop until end of file now.
	} while ( EOFDATA == 0 );

	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("TEXT Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}

int 
CGenedocDoc::WriteTextFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		wFile.WriteString( "\n" );

		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				if ( tgs->CharGene == tGapChar ) {
					DataBlock[j] = '-';
				} else {
					DataBlock[j] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			if ( tgs->CharGene == tGapChar ) {
				DataBlock[j] = '-';
			} else {
				DataBlock[j] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int 
CGenedocDoc::WriteTNoGapFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		wFile.WriteString( "\n" );

		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {

			DWORD DCount = 0;
			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				char tChar = toupper(tgs->CharGene);
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					DataBlock[DCount++] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[DCount] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

//			CurPos += DCount;
			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		
		DWORD DCount = 0;
		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( DWORD j = 0; j < Len; ++j ) {
			char tChar = toupper(tgs->CharGene);
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				DataBlock[DCount++] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[DCount] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );

		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int   
CGenedocDoc::ReadPhylipIFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;
	int SeqCount;
	DWORD ResCount;
	int OptCount = 0;
	CString OptString;

	CStdioFile rFile(PathName, CFile::modeRead );


	tString.Empty();
	char *tStr = tString.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// Done .. break out
		rFile.Abort();
		AfxMessageBox(" Unexpected End Of File!" );
		return 0;
	}
	tString.ReleaseBuffer();

	// CopyMemory
	// Skip OPtions ..
	if ( sscanf( (const char *)tString, "%ld%ld", &SeqCount, &ResCount ) != 2 ) {
		rFile.Abort();
		AfxMessageBox("First Line bad!" );
		return 0;
	}


	for ( i=0; i < tString.GetLength(); ++i ) {
		if ( isalpha(tString.GetAt(i) ) ) {
			if ( tString.GetAt(i) != 'U' && tString.GetAt(i) != 'u' ) {
				OptCount++;
				OptString += "" + toupper(tString.GetAt(i));
			}
		}
	}

	for ( i=0; i < OptCount; ++i ) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			rFile.Abort();
			AfxMessageBox(" Unexpected End Of File!" );
			return 0;
		}
		tString.ReleaseBuffer();

		if ( OptString.Find ( toupper(tString.GetAt(0)) ) == - 1 ) {
			rFile.Abort();
			AfxMessageBox("Error Parsing Input Options!" );
			return 0;
		}
	}

	int EOFFLAG = 0;
	
	// Now we are looking for data
	for ( int SeqLoop=0; SeqLoop < SeqCount; ++SeqLoop ) {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( EOFFLAG ) {
			rFile.Abort();
			AfxMessageBox("Error Parsing First Set of Sequences!" );
			return 0;
		}

		// Check Again Blank Line
		int End = tString.GetLength();
		for ( i=0; i < End; ++i ) {
			if ( tString[i] != ' ' && tString[i] != '\n' ) break;
		}

		// if blank line, then skip it
		if ( i == tString.GetLength() ) {
			--SeqLoop;
			continue;
		}

		CString strName;
		for ( i=0; i<tString.GetLength(); ++i ) {
			if ( tString[i] == ' ' ) break;
			if ( i == 10 ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				tSNS = tSNS1;
			}
		}

		if ( tSNS != NULL ) {
			rFile.Abort();
			char ErrBuff[256];
			sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", tSNS->Name );
			AfxMessageBox( ErrBuff );
			return 0;
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->Weight = 1.0;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadPhylipFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}
		SequenceList->AddTail( tSNS );

		// Skip Whates left of name
		for ( ; i<tString.GetLength(); ++i ) {
			if ( tString[i] != ' ' ) break;
			if ( i == 10 ) break;
		}

		CString dString;
		while ( i < End ) {
			if ( isgraph(tString[i]) ) dString += tString[i];
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();

		}

		// Loop until end of file now.
	}

	do {


		POSITION SeqPOS = SequenceList->GetHeadPosition();

		for (int SeqLoop = 0; SeqLoop < SeqCount; ++SeqLoop ) {

			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( EOFFLAG ) {
				rFile.Abort();
				AfxMessageBox("Unexpected EOF Parsing Sequences!" );
				return 0;
			}

			// Check Again Blank Line
			int End = tString.GetLength();
			for ( i=0; i < End; ++i ) {
				if ( tString[i] != ' ' && tString[i] != '\n' ) break;
			}

			// if blank line, then skip it
			if ( i == tString.GetLength() ) {
				--SeqLoop;
				continue;
			}


			tSNS = (SeqNameStruct*)SequenceList->GetNext(SeqPOS);

			CString dString;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();

			}
		}

		// Loop until end of file now.

	} while ( tSNS->Len != ResCount );

	tSNS = (SeqNameStruct*)SequenceList->GetHead();

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len != tSNS->Len ) {
			AfxMessageBox("Sequence Length Problems!");
			return 0;
		}
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}

int 
CGenedocDoc::WritePhylipFile( const CString& PathName, int Selected )
{

	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
		CString *Title;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];


	for ( i=0; i < Count; ++i ) {
		(pWS[i]).Title = new CString;
	}

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	
	// Put a title Line
	sprintf ( BuildBuff, "%3d %5ld\n", Count, (const char *)(pWS[0]).pCGSeg->GetTextLength() );

	// Three blank lines.
	wFile.WriteString ( BuildBuff );

	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, "%-10s", (const char *)(pWS[i]).pCGSeg->GetTitle() );
		BuildBuff[10] = 0;
		*(pWS[i]).Title = BuildBuff;
	}
			
	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = (pWS[0]).pCGSeg->GetTextLength();
	int LineNum;
	int FirstThrough = 1;

	while ( (CurPos + 50L) < Len ) {

		LineNum = 0;

		while ( LineNum < Count ) {

			// clear out temp string.
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

			// Build data blocks
			GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
			for ( int j = 0; j < 50; ++j ) {
				if ( tgs->CharGene == tGapChar ) {
					DataBlock[j] = '-';
				} else {
					DataBlock[j] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[50] = 0;

			if ( FirstThrough ) {
				sprintf ( BuildBuff, "%s%s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
			} else {
				sprintf ( BuildBuff, "%s\n", DataBlock );
			}
			wFile.WriteString( BuildBuff );
			
			LineNum++;
		}

		FirstThrough = 0;
		wFile.WriteString( "\n" );
	
		CurPos += 50L;

	};
	
	// Do Last set of lines 

	Len = (pWS[0]).pCGSeg->GetTextLength() - CurPos;
	
	LineNum = 0;

	while ( LineNum < Count ) {
	
			// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// Build data blocks
		GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			if ( tgs->CharGene == tGapChar ) {
				DataBlock[j] = '-';
			} else {
				DataBlock[j] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
	
		LineNum++;
	}
	
	
	wFile.WriteString( "\n" );

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	for ( i=0; i < Count; ++i ) {
		delete (pWS[i]).Title;
	}

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}



int   
CGenedocDoc::ReadPIRFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	
	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();
		CString strName;
		for ( i=4; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->Weight = 1.0;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadPIRFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );


		// Skip over comment line
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			tString.ReleaseBuffer();
			rFile.Abort();
			AfxMessageBox("UnExpected End Of File" );
			return 0;
		}
		tString.ReleaseBuffer();


		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( tString[i] == '*' ) {
					EOFDATA = 1;
					break;
				}
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

		if ( EOFFLAG ) {
			delete (SeqNameStruct*)SequenceList->RemoveTail();
			break;
		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("PIR Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenedocDoc::WritePIRFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();

	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	Count = i;
	
	
	// Build Names and Len ...
	for ( int Line = 0; Line < Count; ++Line ) {
		
		sprintf( BuildBuff, ">P1;%s\n", (const char *)(pWS[Line]).pCGSeg->GetTitle() );
		wFile.WriteString( BuildBuff );
	
		sprintf( BuildBuff, "    Length = %ld\n", (const char *)(pWS[Line]).pCGSeg->GetTextLength() );
		wFile.WriteString( BuildBuff );

		DWORD CurPos = 0;

		char DataBlock[6][11];
		DWORD Len = (pWS[Line]).pCGSeg->GetTextLength();

		while ( (CurPos + 59L) < Len ) {
			int j;
			// Build data blocks
			for ( i=0; i < 6; ++i ) {
				GeneStor *tgs = ((pWS[Line]).pText) + CurPos + (i * 10 );
				for ( j = 0; j < 10; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '-';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = 0;
			}

			sprintf ( BuildBuff, 
				"%s %s %s %s %s %s\n", 
				DataBlock[0], 
				DataBlock[1], 
				DataBlock[2], 
				DataBlock[3], 
				DataBlock[4],
				DataBlock[5]
			);
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[Line]).pCGSeg->GetTextLength() - CurPos;

		
		int tCount10 = (int)Len / 10;
		int tCountr = (int)Len % 10;
		int j;
		for ( i=0; i < 6; ++i ) {
			if ( i < tCount10 ) {
				GeneStor *tgs = (GeneStor *)((pWS[Line]).pText) + CurPos + (i * 10);
				for ( int j = 0; j < 10; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '-';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = 0;
			} else if ( i == tCount10 ) {

				GeneStor *tgs = (GeneStor *)((pWS[Line]).pText) + CurPos + (i * 10);
				for ( int j = 0; j < tCountr; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '-';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = '*';
				j++;
				DataBlock[i][j] = 0;
			} else {
				DataBlock[i][0] = 0;
			}

		}
			
		sprintf ( BuildBuff, 
			"%s %s %s %s %s %s\n", 
			DataBlock[0], 
			DataBlock[1], 
			DataBlock[2], 
			DataBlock[3], 
			DataBlock[4], 
			DataBlock[5]
		);
		wFile.WriteString( BuildBuff );

	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int   
CGenedocDoc::ReadFastaFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	int NoRead = 0;

	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			if ( !NoRead ) {
				tString.Empty();
				char *tStr = tString.GetBuffer(1024);
				if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
					// Done .. break out
					EOFFLAG = 1;
					break;
				}
				tString.ReleaseBuffer();
				tString = tString.SpanExcluding("\n\r");
			} else {
				NoRead = 0;
			}

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();

		// Skip initial spaces ..
		for ( i=1; i<End; ++i ) {
			if ( tString[i] != ' ' ) break;
		}
		
		// Skip Now get names ..
		CString strName;
		CString strDescr;
		for ( ; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}
		if ( strName.GetLength() > 50 ) strName = strName.Left(50);
		strDescr = tString.Mid( strName.GetLength() + 1 );

		// Skip initial spaces ..
		for ( i=0; i<strDescr.GetLength(); ++i ) {
			if ( strDescr[i] != ' ' ) break;
		}
		strDescr = strDescr.Mid( i );

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Descr = strDescr;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->Weight = 1.0;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );

		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			if ( tString[0] == '>' ) {
				NoRead = 1;
				EOFDATA = 1;
				break;
			}
			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

//		if ( EOFFLAG ) {
//			delete (SeqNameStruct*)SequenceList->RemoveTail();
//			break;
//		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("FASTA Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenedocDoc::WriteFastaFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, ">%s %s.\n", (const char *)(pWS[i]).pCGSeg->GetTitle(), (const char *)(pWS[i]).pCGSeg->GetDescr() );
			
		wFile.WriteString( BuildBuff );
	
		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				if ( tgs->CharGene == tGapChar ) {
					DataBlock[j] = '-';
				} else {
					DataBlock[j] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			if ( tgs->CharGene == tGapChar ) {
				DataBlock[j] = '-';
			} else {
				DataBlock[j] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int 
CGenedocDoc::WriteALNFile( const CString& PathName, int Selected )
{

	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
		CString *Title;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];


	for ( i=0; i < Count; ++i ) {
		(pWS[i]).Title = new CString;
	}

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	
	// Put a title Line
	wFile.WriteString ( "CLUSTAL W(1.60) multiple sequence alignment\n" );

	// Three blank lines.
	wFile.WriteString ( "\n" );
	wFile.WriteString ( "\n" );
	wFile.WriteString ( "\n" );

	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, "%-15s", (const char *)(pWS[i]).pCGSeg->GetTitle() );
		*(pWS[i]).Title = BuildBuff;
	}
			
	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = (pWS[0]).pCGSeg->GetTextLength();
	int LineNum;

	while ( (CurPos + 60L) < Len ) {

		LineNum = 0;

		while ( LineNum < Count ) {

			// clear out temp string.
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

			// Build data blocks
			GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				if ( tgs->CharGene == tGapChar ) {
					DataBlock[j] = '-';
				} else {
					DataBlock[j] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s %s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
			wFile.WriteString( BuildBuff );
			
			LineNum++;
		}

		wFile.WriteString( "\n" );
	
		wFile.WriteString( "\n" );

		CurPos += 60L;

	};
	
	// Do Last set of lines 

	Len = (pWS[0]).pCGSeg->GetTextLength() - CurPos;
	
	LineNum = 0;

	while ( LineNum < Count ) {
	
			// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// Build data blocks
		GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			if ( tgs->CharGene == tGapChar ) {
				DataBlock[j] = '-';
			} else {
				DataBlock[j] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s %s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
		wFile.WriteString( BuildBuff );
	
		LineNum++;
	}
	
	
	wFile.WriteString( "\n" );

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	for ( i=0; i < Count; ++i ) {
		delete (pWS[i]).Title;
	}

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int 
CGenedocDoc::ReadALNFile( CPtrList* CommentList, CPtrList* SequenceList, CString& PathName )
{

	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );


	tString.Empty();
	char *tStr = tString.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// Done .. break out
		AfxMessageBox(" Unexpected End Of File!" );
		return 0;
	}
	tString.ReleaseBuffer();

	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		// Check Blank Line
		if (tString.GetLength() < 3 ) continue;

		if ( tString.GetAt(0) == ' ' ) continue;

		// Check Again Blank Line
		int End = tString.GetLength();
		for ( i=0; i < End; ++i ) {
			char tchar = toupper(tString[i]);
			if ( tchar != ' ' ) break;
		}
		if ( i == End ) continue;

		CString strName;
		for ( i=0; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				tSNS = tSNS1;
			}
		}

		if ( tSNS == NULL ) {
			tSNS = new SeqNameStruct;
			tSNS->Name = strName;
			tSNS->Len = 0;
			tSNS->Start = 1;
			tSNS->Check = 1234;
			tSNS->Weight = 1.0;
			tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
			// Abort if alloc fails
			if ( tSNS->hText == NULL ) {
				AfxMessageBox("ReadALNFile:GlobalAlloc:Fail 1");
				rFile.Abort();
				return 0;
			}

			SequenceList->AddTail( tSNS );
		}
		while ( i < End ) {
			if ( tString[i] != ' ' ) break;
			i++;
		}

		CString dString;
		while ( i < End ) {
			if ( tString[i] == ' ' ) break;
			if ( isgraph(tString[i]) ) dString += tString[i];
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();
		}

	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	tSNS = (SeqNameStruct*)SequenceList->GetHead();
	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len != tSNS->Len ) {
			AfxMessageBox("Sequence Length Problems: Duplicate Sequence Names?");
			return 0;
		}
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}


BOOL
CGenedocDoc::GetDataTypeValuesFile( const CString& szFilename, CStcGroup *StcGroup )
{

	CString tFile = szFilename;
	tFile.MakeUpper();
	if ( tFile.Find( ".STU" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFileStu( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find( ".PRD" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFilePrd( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find( ".SSP" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFileSsp( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find( ".PHD" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFilePhd( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find(".PSD" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFileSeq( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find(".PDB" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFilePDB( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else if ( tFile.Find( ".DSS" ) != -1 ) {
		BeginWaitCursor();
		if ( !GetDataTypeValuesFileDss( szFilename, StcGroup ) ) {
			EndWaitCursor();
			AfxMessageBox ("Get Data Type Values Fails" );
			return FALSE;
		}
		EndWaitCursor();
	} else {
		AfxMessageBox ("Secondary Structure File Type Unknown" );
		return FALSE;
	}

	return TRUE;
}

/*
"COLORMAP,PREDSS,\"sheet\",E,255,255,0,0",
"COLORMAP,PREDSS,\"no pred\", ,255,255,255,0",
"COLORMAP,PREDSS,\"helix\",H,0,0,255,1",
*/


void CGenedocDoc::OnStcloaduserfile() 
{
	// TODO: Add your command handler code here

#ifdef _WIN32
	static char Filter[] = 
"User Defined (*.sdu*)|*.sdu*|\
All Files (*.*)|*.*||";
#else
	static char Filter[] = 
"User Defined (*.sdu)|*.sdu|\
All Files (*.*)|*.*||";
#endif

	CFileDialog tDlg( TRUE, NULL, NULL, 
		OFN_HIDEREADONLY, 
		Filter, NULL
	);
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	
#ifndef _WIN32
	if ( LoadUserSduFile( tDlg.GetFileTitle() ) ) 
		m_UserVars.m_StcDefUser.AddTail( tDlg.GetFileTitle() );
#else
	if ( LoadUserSduFile( tDlg.GetFileName() ) ) 
		m_UserVars.m_StcDefUser.AddTail( tDlg.GetFileName() );
#endif

	return;
}

BOOL 
CGenedocDoc::LoadUserSduFile(const CString& PathName)
{

TRY {

	CString tString;

	CStdioFile rFile( PathName, CFile::modeRead );

	int EOFFLAG = 0;
	
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();

		if ( !m_UserVars.m_Stc.StcParseString( tString ) ) break;
		// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	//     fclose(fd);
	rFile.Close();
	
	POSITION tPos = m_UserVars.m_StcDefUser.GetHeadPosition();
	while ( tPos != NULL ) {
		POSITION sPos = tPos;
		if ( m_UserVars.m_StcDefUser.GetNext(tPos) == PathName ) {
			m_UserVars.m_StcDefUser.RemoveAt(sPos);
		}
	}

	AutoShade( -1 );
	
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}



BOOL
CGenedocDoc::GetDataTypeValuesFileStu( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.

TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile(szFilename, CFile::modeRead );

	CString ChainName = "User";

	// Take name from middle of first line ...

	CString Description = "User";

	struct stPred {
		CString *sId;
		int iDataStart, iDataAmount;
		CString *sValues;
		HGLOBAL hValues;
		DWORD Total;
	};

	const CMapStringToPtr& DTM = m_UserVars.m_Stc.GetDataTypeMap();

	int TestCount = 0;
	POSITION tPos = DTM.GetStartPosition();
	CString strKey;
	void *ptrValue;
	while ( tPos != NULL ) {
		DTM.GetNextAssoc( tPos, strKey, ptrValue );
		if ( ((StcDataType*)ptrValue)->DataAmount != 0 ) TestCount++;
	}

	if ( TestCount == 0 ) {
		rFile.Abort();
		return 0;
	}
	
	struct stPred *stPP = new struct stPred[TestCount];

	tPos = DTM.GetStartPosition();
	int i=0;
	while ( tPos != NULL ) {
		DTM.GetNextAssoc( tPos, strKey, ptrValue );
		if ( ((StcDataType*)ptrValue)->DataAmount != 0 ) {
			stPP[i].hValues = GlobalAlloc( GMEM_FLAG, 0L );
			stPP[i].sId = new CString( strKey );
			stPP[i].iDataStart = ((StcDataType*)ptrValue)->DataStart;
			stPP[i].iDataAmount = ((StcDataType*)ptrValue)->DataAmount;
			stPP[i].sValues = new CString;
			stPP[i].Total = 0;
			i++;
		}
	}

	struct stPred stPPRes;
	stPPRes.hValues = GlobalAlloc( GMEM_FLAG, 0L );
	stPPRes.sId = new CString("Sequence|");
	stPPRes.iDataStart = stPP[0].iDataStart;
	stPPRes.iDataAmount = stPP[0].iDataAmount;
	stPPRes.sValues = new CString;
	stPPRes.Total = 0;


	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		
		if (tString.GetLength() < 3 ) continue;

		int FindLoc;

		struct stPred *stThisPP = NULL;
		if ( (FindLoc = tString.Find( *stPPRes.sId )) != -1 ) {
			stThisPP = &stPPRes;
		} else {
			for ( int i=0; i < TestCount; ++i ) {
				if ( (FindLoc = tString.Find( *stPP[i].sId )) != -1 ) {
					stThisPP = &stPP[i];
					break;
				}
			}
		}

		if ( stThisPP == NULL ) continue;

		*stThisPP->sValues += tString.Mid(stThisPP->iDataStart - 1, stThisPP->iDataAmount );

		if ( stThisPP->sValues->GetLength() < stPPRes.sValues->GetLength() ) {
			for ( int count = stPPRes.sValues->GetLength() - stThisPP->sValues->GetLength(); count; --count ) {
				*stThisPP->sValues += ' ';
			}
		}

		if ( stThisPP->sValues->GetLength() > 1024 ) {
			int MoveCount = stThisPP->sValues->GetLength();
			stThisPP->hValues = GlobalReAlloc( stThisPP->hValues, stThisPP->Total + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(stThisPP->hValues);
			pRes += stThisPP->Total;
			stThisPP->Total += MoveCount;
			char *pnRes = stThisPP->sValues->GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(stThisPP->hValues);
			stThisPP->sValues->ReleaseBuffer();
			stThisPP->sValues->Empty();
		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );


	if ( stPPRes.sValues->GetLength() ) {
		int MoveCount = stPPRes.sValues->GetLength();
		stPPRes.hValues = GlobalReAlloc( stPPRes.hValues, stPPRes.Total+MoveCount, GMEM_MOVEABLE);
		char *pData = (char *)GlobalLock(stPPRes.hValues);
		pData += stPPRes.Total;
		stPPRes.Total += MoveCount;
		char *pnData = stPPRes.sValues->GetBuffer(MoveCount);
		while (MoveCount--) {
			*pData++ = *pnData++;
		}
		GlobalUnlock(stPPRes.hValues);
		stPPRes.sValues->ReleaseBuffer();
		stPPRes.sValues->Empty();
	}

	for ( i=0; i < TestCount; ++i ) {

		if ( stPP[i].sValues->GetLength() ) {
			int MoveCount = stPP[i].sValues->GetLength();
			stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total+MoveCount, GMEM_MOVEABLE);
			char *pData = (char *)GlobalLock(stPP[i].hValues);
			pData += stPP[i].Total;
			stPP[i].Total += MoveCount;
			char *pnData = stPP[i].sValues->GetBuffer(MoveCount);
			while (MoveCount--) {
				*pData++ = *pnData++;
			}
			GlobalUnlock(stPP[i].hValues);
			stPP[i].sValues->ReleaseBuffer();
			stPP[i].sValues->Empty();
		}
	}
	StcDataType *pDT;

	if ( stPPRes.Total != 0 ) {

		char *pValuesRes = (char *)GlobalLock(stPPRes.hValues);

		char **pValues = new char *[TestCount];
		for ( int i=0; i < TestCount; ++i ) {
			pValues[i] = (char *)GlobalLock(stPP[i].hValues);
		}

		char *pValues2Res = pValuesRes;
		char **pValues2 = new char *[TestCount];
		for ( i=0; i < TestCount; ++i ) {
			if ( stPP[i].Total != 0 ) {
				pValues2[i] = pValues[i];
			}
		}

		DWORD Total = stPPRes.Total;
		DWORD NewTotal = 0;

		for ( UINT C=0; C < Total; ++C ) {
			char vrChar = toupper( *(pValuesRes) );
			if ( vrChar >= 'A' && vrChar <='Z' ) {
				*(pValues2Res++) = *(pValuesRes);
				for ( i=0; i < TestCount; ++i ) {
					if ( stPP[i].Total != 0 ) {
						*(pValues2[i]++) = *(pValues[i]);
					}
				}

				NewTotal++;
			}
			pValuesRes++;
			for ( i=0; i < TestCount; ++i ) {
				if ( stPP[i].Total != 0 ) {
					pValues[i]++;
				}
			}
		}

		GlobalUnlock(stPPRes.hValues);
		for ( i=0; i < TestCount; ++i ) {
			GlobalUnlock(stPP[i].hValues);
		}

		if ( NewTotal != stPPRes.Total ) {
			stPPRes.hValues = GlobalReAlloc( stPPRes.hValues, NewTotal, GMEM_MOVEABLE );
			stPPRes.Total = NewTotal;
		}

		for ( i=0; i < TestCount; ++i ) {
			if ( NewTotal != stPP[i].Total ) {
				if ( stPP[i].Total != 0 ) {
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, NewTotal, GMEM_MOVEABLE );
					stPP[i].Total = NewTotal;
				}
			}
		}

		delete pValues;
		delete pValues2;
	}


	if ( stPPRes.Total ) {

		StcGroup->SetNameDescription( ChainName, Description );
		StcGroup->SetResidues( stPPRes.hValues, stPPRes.Total );

		for ( int i=0; i < TestCount; ++i ) {
			if ( stPP[i].Total != 0 ) {
				if ( m_UserVars.m_Stc.LookupDataType( *stPP[i].sId, &pDT ) ) {
					StcGroup->SetDataTypeValues( *stPP[i].sId, pDT->ColorMap, stPP[i].hValues, stPP[i].Total );
				}
			}
		}
	} else {
		for ( i=0; i < TestCount; ++i ) {
			if ( stPP[i].Total != 0 ) {
				GlobalFree(stPP[i].hValues);
			}
		}
	}

	if ( stPPRes.Total == 0 ) {
		GlobalFree(stPPRes.hValues);
	}
	delete stPPRes.sId;
	delete stPPRes.sValues;

	for ( i=0; i < TestCount; ++i ) {
		if ( stPP[i].Total == 0 ) {
			GlobalFree(stPP[i].hValues);
		}
		delete stPP[i].sId;
		delete stPP[i].sValues;
	}

	delete stPP;

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}








BOOL
CGenedocDoc::GetDataTypeValuesFilePrd( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.

TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile(szFilename, CFile::modeRead );

	CString ChainName = "Predator";

	// Take name from middle of first line ...

/*
 *	the second line contains a description of the protein.
 *	we'll want to save that...We'll also strip off trailing
 *	spaces.
 */

	CString Description = "Predator";

/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */



	struct {
		CString *sId;
		CString *sValues;
		HGLOBAL hValues;
		DWORD Total;
	} stPP[2];

	for ( int i=0; i < 2; ++i ) {
		stPP[i].hValues = GlobalAlloc( GMEM_FLAG, 0L );
		stPP[i].sId = new CString;
		stPP[i].sValues = new CString;
		stPP[i].Total = 0;
	}

	*stPP[0].sId = "Sequence|";
	*stPP[1].sId = "PREDATOR";

	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");
		
		if (tString.GetLength() < 3 ) continue;

		if ( tString[0] > '0' && tString[0] < '9' ) {

			int End = tString.GetLength() - 1;
			while ( tString[End] < 'A' || tString[End] > 'Z' ) if (--End == 0 ) break;
			if ( End < 5 ) continue;
			End = End - 5 + 1;
			int sEnd = End;
			*stPP[0].sValues += tString.Mid(5,End);

			if ( stPP[0].sValues->GetLength() > 1024 ) {
				int MoveCount = stPP[0].sValues->GetLength();
				stPP[0].hValues = GlobalReAlloc( stPP[0].hValues, stPP[0].Total + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(stPP[0].hValues);
				pRes += stPP[0].Total;
				stPP[0].Total += MoveCount;
				char *pnRes = stPP[0].sValues->GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(stPP[0].hValues);
				stPP[0].sValues->ReleaseBuffer();
				stPP[0].sValues->Empty();
			}

			tString.Empty();
			tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			End = tString.GetLength() - 1;
			if ( End < 5 ) {
				AfxMessageBox("Internal Error Reading Predator File 1" );
				goto EndOut;
			}
			while ( tString[End] != 'H' && tString[End] != 'E' && tString[End] != '_' ) if ( --End == 0 ) break;
			End = End - 5 + 1;
			if ( sEnd != End ) {
				AfxMessageBox("Internal Error Reading Predator File 2" );
				goto EndOut;
			}
			*stPP[1].sValues += tString.Mid(5,End);

			if ( stPP[1].sValues->GetLength() > 1024 ) {
				int MoveCount = stPP[1].sValues->GetLength();
				stPP[1].hValues = GlobalReAlloc( stPP[1].hValues, stPP[1].Total + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(stPP[1].hValues);
				pRes += stPP[1].Total;
				stPP[1].Total += MoveCount;
				char *pnRes = stPP[1].sValues->GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(stPP[1].hValues);
				stPP[1].sValues->ReleaseBuffer();
				stPP[1].sValues->Empty();
			}

		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	
	for (int i=0; i < 2; ++i ) {

		if ( stPP[i].sValues->GetLength() ) {
			int MoveCount = stPP[i].sValues->GetLength();
			stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total+MoveCount, GMEM_MOVEABLE);
			char *pData = (char *)GlobalLock(stPP[i].hValues);
			pData += stPP[i].Total;
			stPP[i].Total += MoveCount;
			char *pnData = stPP[i].sValues->GetBuffer(MoveCount);
			while (MoveCount--) {
				*pData++ = *pnData++;
			}
			GlobalUnlock(stPP[i].hValues);
			stPP[i].sValues->ReleaseBuffer();
			stPP[i].sValues->Empty();
		}
	}
	StcDataType *pDT;

	if ( stPP[0].Total != 0 ) {
		int i;
		char *pValues[2];
		for ( int i=0; i < 2; ++i ) {
			pValues[i] = (char *)GlobalLock(stPP[i].hValues);
		}

		char *pValues2[2];
		for (int i=0; i < 2; ++i ) {
			if ( stPP[i].Total != 0 ) {
				pValues2[i] = pValues[i];
			}
		}

		DWORD Total = stPP[0].Total;
		DWORD NewTotal = 0;
		
		for ( UINT C=0; C < Total; ++C ) {
			if ( *(pValues[0]) >= 'A' && *(pValues[0]) <='Z' ) {
				for (int i=0; i < 2; ++i ) {
					if ( stPP[i].Total != 0 ) {
						*(pValues2[i]++) = *(pValues[i]);
					}
				}

				NewTotal++;
			}
			for ( i=0; i < 2; ++i ) {
				if ( stPP[i].Total != 0 ) {
					pValues[i]++;
				}
			}
		}
		int t;
		for ( i=0; i < 2; ++i ) {
			GlobalUnlock(stPP[i].hValues);
		}

		if ( NewTotal != stPP[0].Total ) {
			for ( i=0; i < 2; ++i ) {
				if ( stPP[i].Total != 0 ) {
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, NewTotal, GMEM_MOVEABLE );
					stPP[i].Total = NewTotal;
				}
			}
		}
	}


	if ( stPP[0].Total ) {

		// Test if Definition Loaded ..
		if ( !m_UserVars.m_Stc.SCMIEMBLLoaded() ) {
			if ( !m_UserVars.m_Stc.LoadSCMIEMBL() ) {
				AfxMessageBox("Prot Pred Definition Load Fails");
				goto EndOut;
			}
		}


		StcGroup->SetNameDescription( ChainName, Description );
		StcGroup->SetResidues( stPP[0].hValues, stPP[0].Total );

		for ( int i=1; i < 2; ++i ) {
			if ( stPP[i].Total != 0 ) {
				if ( m_UserVars.m_Stc.LookupDataType( *stPP[i].sId, &pDT ) ) {
					StcGroup->SetDataTypeValues( *stPP[i].sId, pDT->ColorMap, stPP[i].hValues, stPP[i].Total );
				}
			}
		}
	} else {
EndOut:
		int i;
		for ( i=0; i < 2; ++i ) {
			if ( stPP[i].Total != 0 ) {
				GlobalFree(stPP[i].hValues);
			}
		}
	}

	for (int i=0; i < 2; ++i ) {
		if ( stPP[i].Total == 0 ) {
			GlobalFree(stPP[i].hValues);
		}
		delete stPP[i].sId;
		delete stPP[i].sValues;
	}


	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}





BOOL
CGenedocDoc::GetDataTypeValuesFileSsp( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.

TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile( szFilename, CFile::modeRead );


	CString ChainName = "SSPRED";

	// Take name from middle of first line ...

/*
 *	the second line contains a description of the protein.
 *	we'll want to save that...We'll also strip off trailing
 *	spaces.
 */

	CString Description = "SS Prediction";

/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */



	struct {
		CString *sId;
		CString *sValues;
		HGLOBAL hValues;
		DWORD Total;
	} stPP[3];

	for ( int i=0; i < 3; ++i ) {
		stPP[i].hValues = GlobalAlloc( GMEM_FLAG, 0L );
		stPP[i].sId = new CString;
		stPP[i].sValues = new CString;
		stPP[i].Total = 0;
	}

	*stPP[0].sId = "Sequence|";
	*stPP[1].sId = "Pred SS |";
	*stPP[2].sId = "Clean SS|";

	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char * tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");
		
		if (tString.GetLength() < 3 ) continue;

		int FindLoc;

		for ( int i=0; i < 3; ++i ) {

			if ( (FindLoc = tString.Find( *stPP[i].sId )) != -1 ) {

				int End = tString.GetLength();
				End = End - FindLoc - stPP[i].sId->GetLength();
				*stPP[i].sValues += tString.Mid(FindLoc + stPP[i].sId->GetLength(),End);

				if ( stPP[i].sValues->GetLength() > 1024 ) {
					int MoveCount = stPP[i].sValues->GetLength();
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total + MoveCount, GMEM_MOVEABLE);
					char *pRes = (char *)GlobalLock(stPP[i].hValues);
					pRes += stPP[i].Total;
					stPP[i].Total += MoveCount;
					char *pnRes = stPP[i].sValues->GetBuffer(MoveCount);
					while (MoveCount--) {
						*pRes++ = *pnRes++;
					}
					GlobalUnlock(stPP[i].hValues);
					stPP[i].sValues->ReleaseBuffer();
					stPP[i].sValues->Empty();
				}
				break;
			}
		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );


	for (int i=0; i < 3; ++i ) {

		if ( stPP[i].sValues->GetLength() ) {
			int MoveCount = stPP[i].sValues->GetLength();
			stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total+MoveCount, GMEM_MOVEABLE);
			char *pData = (char *)GlobalLock(stPP[i].hValues);
			pData += stPP[i].Total;
			stPP[i].Total += MoveCount;
			char *pnData = stPP[i].sValues->GetBuffer(MoveCount);
			while (MoveCount--) {
				*pData++ = *pnData++;
			}
			GlobalUnlock(stPP[i].hValues);
			stPP[i].sValues->ReleaseBuffer();
			stPP[i].sValues->Empty();
		}
	}
	StcDataType *pDT;

	if ( stPP[0].Total != 0 ) {

		char *pValues[3];
		for ( int i=0; i < 3; ++i ) {
			pValues[i] = (char *)GlobalLock(stPP[i].hValues);
		}

		char *pValues2[3];
		for ( i=0; i < 3; ++i ) {
			if ( stPP[i].Total != 0 ) {
				pValues2[i] = pValues[i];
			}
		}

		DWORD Total = stPP[0].Total;
		DWORD NewTotal = 0;

		for ( UINT C=0; C < Total; ++C ) {
			if ( *(pValues[0]) >= 'A' && *(pValues[0]) <='Z' ) {
				for ( i=0; i < 3; ++i ) {
					if ( stPP[i].Total != 0 ) {
						*(pValues2[i]++) = *(pValues[i]);
					}
				}

				NewTotal++;
			}
			for ( i=0; i < 3; ++i ) {
				if ( stPP[i].Total != 0 ) {
					pValues[i]++;
				}
			}
		}

		for ( i=0; i < 3; ++i ) {
			GlobalUnlock(stPP[i].hValues);
		}

		if ( NewTotal != stPP[0].Total ) {
			for ( i=0; i < 3; ++i ) {
				if ( stPP[i].Total != 0 ) {
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, NewTotal, GMEM_MOVEABLE );
					stPP[i].Total = NewTotal;
				}
			}
		}
	}


	if ( stPP[0].Total ) {

		// Test if Definition Loaded ..
		if ( !m_UserVars.m_Stc.SCMIEMBLLoaded() ) {
			if ( !m_UserVars.m_Stc.LoadSCMIEMBL() ) {
				AfxMessageBox("Prot Pred Definition Load Fails");
				goto EndOut;
			}
		}


		StcGroup->SetNameDescription( ChainName, Description );
		StcGroup->SetResidues( stPP[0].hValues, stPP[0].Total );

		for ( int i=1; i < 3; ++i ) {
			if ( stPP[i].Total != 0 ) {
				if ( m_UserVars.m_Stc.LookupDataType( *stPP[i].sId, &pDT ) ) {
					StcGroup->SetDataTypeValues( *stPP[i].sId, pDT->ColorMap, stPP[i].hValues, stPP[i].Total );
				}
			}
		}
	} else {
EndOut:
		for ( i=0; i < 3; ++i ) {
			if ( stPP[i].Total != 0 ) {
				GlobalFree(stPP[i].hValues);
			}
		}
	}

	for ( i=0; i < 3; ++i ) {
		if ( stPP[i].Total == 0 ) {
			GlobalFree(stPP[i].hValues);
		}
		delete stPP[i].sId;
		delete stPP[i].sValues;
	}


	//     fclose(fd);
	rFile.Close();

}
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}





BOOL
CGenedocDoc::GetDataTypeValuesFilePhd( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.

TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile( szFilename, CFile::modeRead );


/*
 *	the first line contains the name of the protein with a chain
 *	id....The chain name line takes the form >F1;1xxxa where a i
 *	the chain id...
 */

/*
                  ....,....1....,....2....,....3....,....4....,....5....,....6
         AA      |.......................ACPKGASY.EAGIVCRITKPALLVLNQETAKVVQTAF|
         PHD sec |   HHH     HHHHHHHHHHHHHH           EEEEE  HHHHHHHHHHHHHHHHH|
         Rel sec |903122143421346799999876213543347661568835312446576789999999|
 detail:
         prH sec |043455433245567788888877443211111110000002345667777789999999|
         prE sec |000000000000000000000001101122321114678850000011000000000000|
         prL sec |945443565654321100000011355655567774211136643221212110000000|
 subset: SUB sec |L.............HHHHHHHHHH...L....LLL.EEEE.L.....HHHHHHHHHHHHH|

 3st:    P_3 acc |ebbbbbbbbbbbbee bbeee eeebbbbb bbeebbbbbbeebbebbbbbbe be eeb|
 10st:   PHD acc |900000000000076500887586700000500670000007700700000065074770|
         Rel acc |314727769642131065474032555769181236656407516846227211251340|
 subset: SUB acc |..bb.bbbbbb.....bbeee...ebbbbb.b...bbbbb.ee.bebb..b....e..e.|

         PHD htm |    HHHHH                                                   |
         Rel htm |778888887677899999999999998877768873225688998999999999999999|
 detail:         |                                                            |
         prH htm |110000001111000000000000000011110013332100000000000000000000|
         prL htm |889999998888999999999999999988889986667899999999999999999999|
 subset:         |                                                            |
         SUB htm |LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL...LLLLLLLLLLLLLLLLLLLLLL|
*/

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		
		// Look for data start string
		
		if ( tString.Find( "protein:       " ) != -1 ) 
			break;
	}



	CString ChainName;

	// Take name from middle of first line ...
	ChainName = tString.Mid( 15, 10 );


/*
 *	the second line contains a description of the protein.
 *	we'll want to save that...We'll also strip off trailing
 *	spaces.
 */

	CString Description = "Protein Prediction";

/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();

		// Look for data start string
		
		if ( tString.Find( "....,....1" ) != -1 ) 
			break;
	}



	struct {
		CString *sId;
		CString *sValues;
		HGLOBAL hValues;
		DWORD Total;
	} stPP[16];

	for ( int i=0; i < 16; ++i ) {
		stPP[i].hValues = GlobalAlloc( GMEM_FLAG, 0L );
		stPP[i].sId = new CString;
		stPP[i].sValues = new CString;
		stPP[i].Total = 0;
	}

	*stPP[0].sId = "AA      |";
	*stPP[1].sId = "PHD sec |";
	*stPP[2].sId = "Rel sec |";
	*stPP[3].sId = "prH sec |";
	*stPP[4].sId = "prE sec |";
	*stPP[5].sId = "prL sec |";
	*stPP[6].sId = "SUB sec |";
	*stPP[7].sId = "P_3 acc |";
	*stPP[8].sId = "PHD acc |";
	*stPP[9].sId = "Rel acc |";
	*stPP[10].sId = "SUB acc |";
	*stPP[11].sId = "PHD htm |";
	*stPP[12].sId = "Rel htm |";
	*stPP[13].sId = "prH htm |";
	*stPP[14].sId = "prL htm |";
	*stPP[15].sId = "SUB htm |";

	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();

		if (tString.GetLength() < 3 ) continue;

		int FindLoc;

		for ( int i=0; i < 16; ++i ) {

			if ( (FindLoc = tString.Find( *stPP[i].sId )) != -1 ) {

				int End = tString.ReverseFind('|');
				if ( End == -1 ) continue;
				End = End - FindLoc - 9;
				*stPP[i].sValues += tString.Mid(18,End);

				if ( stPP[i].sValues->GetLength() > 1024 ) {
					int MoveCount = stPP[i].sValues->GetLength();
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total + MoveCount, GMEM_MOVEABLE);
					char *pRes = (char *)GlobalLock(stPP[i].hValues);
					pRes += stPP[i].Total;
					stPP[i].Total += MoveCount;
					char *pnRes = stPP[i].sValues->GetBuffer(MoveCount);
					while (MoveCount--) {
						*pRes++ = *pnRes++;
					}
					GlobalUnlock(stPP[i].hValues);
					stPP[i].sValues->ReleaseBuffer();
					stPP[i].sValues->Empty();
				}
				break;
			}
		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );


	for ( i=0; i < 16; ++i ) {

		if ( stPP[i].sValues->GetLength() ) {
			int MoveCount = stPP[i].sValues->GetLength();
			stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, stPP[i].Total+MoveCount, GMEM_MOVEABLE);
			char *pData = (char *)GlobalLock(stPP[i].hValues);
			pData += stPP[i].Total;
			stPP[i].Total += MoveCount;
			char *pnData = stPP[i].sValues->GetBuffer(MoveCount);
			while (MoveCount--) {
				*pData++ = *pnData++;
			}
			GlobalUnlock(stPP[i].hValues);
			stPP[i].sValues->ReleaseBuffer();
			stPP[i].sValues->Empty();
		}
	}
	StcDataType *pDT;

	if ( stPP[0].Total != 0 ) {

		char *pValues[16];
		for ( int i=0; i < 16; ++i ) {
			pValues[i] = (char *)GlobalLock(stPP[i].hValues);
		}

		char *pValues2[16];
		for ( i=0; i < 16; ++i ) {
			if ( stPP[i].Total != 0 ) {
				pValues2[i] = pValues[i];
			}
		}

		DWORD Total = stPP[0].Total;
		DWORD NewTotal = 0;

		for ( UINT C=0; C < Total; ++C ) {
			if ( *(pValues[0]) >= 'A' && *(pValues[0]) <='Z' ) {
				for ( i=0; i < 16; ++i ) {
					if ( stPP[i].Total != 0 ) {
						*(pValues2[i]++) = *(pValues[i]);
					}
				}

				NewTotal++;
			}
			for ( i=0; i < 16; ++i ) {
				if ( stPP[i].Total != 0 ) {
					pValues[i]++;
				}
			}
		}

		for ( i=0; i < 16; ++i ) {
			GlobalUnlock(stPP[i].hValues);
		}

		if ( NewTotal != stPP[0].Total ) {
			for ( i=0; i < 16; ++i ) {
				if ( stPP[i].Total != 0 ) {
					stPP[i].hValues = GlobalReAlloc( stPP[i].hValues, NewTotal, GMEM_MOVEABLE );
					stPP[i].Total = NewTotal;
				}
			}
		}
	}


	if ( stPP[0].Total ) {

		// Test if Definition Loaded ..
		if ( !m_UserVars.m_Stc.SCMIEMBLLoaded() ) {
			if ( !m_UserVars.m_Stc.LoadSCMIEMBL() ) {
				AfxMessageBox("Prot Pred Definition Load Fails");
				goto EndOut;
			}
		}


		StcGroup->SetNameDescription( ChainName, Description );
		StcGroup->SetResidues( stPP[0].hValues, stPP[0].Total );

		for ( int i=1; i < 16; ++i ) {
			if ( stPP[i].Total != 0 ) {
				if ( m_UserVars.m_Stc.LookupDataType( *stPP[i].sId, &pDT ) ) {
					StcGroup->SetDataTypeValues( *stPP[i].sId, pDT->ColorMap, stPP[i].hValues, stPP[i].Total );
				}
			}
		}
	} else {
EndOut:
		for ( i=0; i < 16; ++i ) {
			if ( stPP[i].Total != 0 ) {
				GlobalFree(stPP[i].hValues);
			}
		}
	}

	for ( i=0; i < 16; ++i ) {
		if ( stPP[i].Total == 0 ) {
			GlobalFree(stPP[i].hValues);
		}
		delete stPP[i].sId;
		delete stPP[i].sValues;
	}


	//     fclose(fd);
	rFile.Close();

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}




BOOL
CGenedocDoc::GetDataTypeValuesFileDss( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.

TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile( szFilename, CFile::modeRead );

/*
 *	the first line contains the name of the protein with a chain
 *	id....The chain name line takes the form >F1;1xxxa where a i
 *	the chain id...
 */

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		
		// Look for data start string
		
		if ( tString.Find( "HEADER" ) != -1 ) 
			break;
	}



	CString ChainName;

	// Take name from middle of first line ...
	ChainName = tString.Mid( 62, 10 );


/*
 *	the second line contains a description of the protein.
 *	we'll want to save that...We'll also strip off trailing
 *	spaces.
 */

	CString Description;

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		
		// Look for data start string
		
		if ( tString.Find( "COMPND" ) != -1 ) 
			break;
	}


	Description = tString.Mid( 10, 60 );

/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		
		// Look for data start string
		
		if ( tString.Find( "  #  RESIDUE AA STRUCTURE" ) != -1 ) 
			break;
	}


	CString CurrentDataType = "/2_STR:DSS";		// This from stccmapi.h

	CString sCurrentDataValues;
	HGLOBAL hCurrentDataValues = GlobalAlloc( GMEM_FLAG, 0L );
	DWORD DataCount = 0;
	DWORD CurrentDataTotal = 0;

	CString sResidues;
	HGLOBAL hResidues = GlobalAlloc( GMEM_FLAG, 0L );
	DWORD ResCount = 0;
	DWORD CurrentResTotal = 0;

	
	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		
		if (tString.GetLength() < 18 ) continue;

/*
 *		This third character will be either 
 * 		/ or a number.  / means some sort of feature
 *		where a number specifies disulfide bonds or author's
 *		2ndary structure classification.
 */     

 		char tChar;
/* 		
 		int ResLoc = atoi ( tString.Mid( 5, 5 ) );

		ResCount++;
		
		while ( ResCount < ResLoc ) {
			Residues += ' ';
			CurrentDataValues += ' ';
			ResCount++;
		}
*/ 		

		tChar = tString[13];

		if ( tChar == '!' ) continue;
		
		if ( !isupper(tChar) ) tChar = 'C';
		
		sResidues += tChar;
		ResCount++;

		if ( sResidues.GetLength() > 1024 ) {
			int MoveCount = sResidues.GetLength();
			hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(hResidues);
			pRes += CurrentResTotal;
			CurrentResTotal += MoveCount;
			char *pnRes = sResidues.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(hResidues);
			sResidues.ReleaseBuffer();
			sResidues.Empty();
		}
		
		tChar = tString[16];
		
		if ( tChar == ' ' ) tChar = '-';
		
		sCurrentDataValues += tChar;
		DataCount++;

		if ( sCurrentDataValues.GetLength() > 1024 ) {
			int MoveCount = sCurrentDataValues.GetLength();
			hCurrentDataValues = GlobalReAlloc( hCurrentDataValues, DataCount, GMEM_MOVEABLE);
			char *pData = (char *)GlobalLock(hCurrentDataValues);
			pData += CurrentDataTotal;
			CurrentDataTotal += MoveCount;
			char *pnData = sCurrentDataValues.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pData++ = *pnData++;
			}
			GlobalUnlock(hCurrentDataValues);
			sCurrentDataValues.ReleaseBuffer();
			sCurrentDataValues.Empty();
		}

		
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );


	if ( sResidues.GetLength() ) {
		int MoveCount = sResidues.GetLength();
		hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
		char *pRes = (char *)GlobalLock(hResidues);
		pRes += CurrentResTotal;
		CurrentResTotal += MoveCount;
		char *pnRes = sResidues.GetBuffer(MoveCount);
		while (MoveCount--) {
			*pRes++ = *pnRes++;
		}
		GlobalUnlock(hResidues);
		sResidues.ReleaseBuffer();
		sResidues.Empty();
	}


	if ( sCurrentDataValues.GetLength() ) {
		int MoveCount = sCurrentDataValues.GetLength();
		hCurrentDataValues = GlobalReAlloc( hCurrentDataValues, DataCount, GMEM_MOVEABLE);
		char *pData = (char *)GlobalLock(hCurrentDataValues);
		pData += CurrentDataTotal;
		CurrentDataTotal += MoveCount;
		char *pnData = sCurrentDataValues.GetBuffer(MoveCount);
		while (MoveCount--) {
			*pData++ = *pnData++;
		}
		GlobalUnlock(hCurrentDataValues);
		sCurrentDataValues.ReleaseBuffer();
		sCurrentDataValues.Empty();
	}


	if ( DataCount ) {

		// Test if Definition Loaded ..
		if ( !m_UserVars.m_Stc.SCMIEMBLLoaded() ) {
			if ( !m_UserVars.m_Stc.LoadSCMIEMBL() ) {
				AfxMessageBox("EMBL Definition Load Fails");
				goto EndOut;
			}
		}

		StcGroup->SetNameDescription( ChainName, Description );
		StcGroup->SetResidues( hResidues, ResCount );

		StcDataType *pDT;
		if ( m_UserVars.m_Stc.LookupDataType( CurrentDataType, &pDT ) ) {
			StcGroup->SetDataTypeValues( CurrentDataType, pDT->ColorMap, hCurrentDataValues, DataCount );
		}
	} else {
EndOut:
		GlobalFree(hResidues);
		GlobalFree(hCurrentDataValues);
	}


	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return 1;
}


BOOL
CGenedocDoc::GetDataTypeValuesFileSeq( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.
TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile( szFilename, CFile::modeRead );
	

/*
 *	the first line contains the name of the protein with a chain
 *	id....The chain name line takes the form >F1;1xxxa where a i
 *	the chain id...
 */
	CString ChainName;

	char *tStr = ChainName.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// EOF too early
		AfxMessageBox("Unexpected End Of File" );
		// fclose( File );
		rFile.Abort();
		return 0;
	}
	ChainName.ReleaseBuffer();


/*
 *	the second line contains a description of the protein.
 *	we'll want to save that...We'll also strip off trailing
 *	spaces.
 */

	CString Description;

	tStr = Description.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// EOF too early
		AfxMessageBox("Unexpected End Of File" );
		// fclose( File );
		rFile.Abort();
		return 0;
	}
	Description.ReleaseBuffer();


/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */

	CString sResidues;
	HGLOBAL hResidues = GlobalAlloc( GMEM_FLAG, 0L );
	DWORD ResCount = 0;
	DWORD CurrentResTotal = 0;

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();

		int Count = 0;
		int Length = tString.GetLength();
		// Get Residues Values
		while( 1 ) {
//			if ( (tString[Count] >= 'A' && tString[Count] <= 'Z') || tString[Count] == '/' ) sResidues += tString[Count];
			if ( tString[Count] >= 'A' && tString[Count] <= 'Z' ) sResidues += tString[Count];
			++ResCount;
			if ( ++Count >= Length ) break;
		}

		if ( sResidues.GetLength() > 1024 ) {
			int MoveCount = sResidues.GetLength();
			hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(hResidues);
			pRes += CurrentResTotal;
			CurrentResTotal += MoveCount;
			char *pnRes = sResidues.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(hResidues);
			sResidues.ReleaseBuffer();
			sResidues.Empty();
		}

		if ( tString.Find("*") != -1 ) {
			break;
		}
	}


	if ( sResidues.GetLength() ) {
		int MoveCount = sResidues.GetLength();
		hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
		char *pRes = (char *)GlobalLock(hResidues);
		pRes += CurrentResTotal;
		CurrentResTotal += MoveCount;
		char *pnRes = sResidues.GetBuffer(MoveCount);
		while (MoveCount--) {
			*pRes++ = *pnRes++;
		}
		GlobalUnlock(hResidues);
		sResidues.ReleaseBuffer();
		sResidues.Empty();
	}


	// Test if Definition Loaded ..
	if ( !m_UserVars.m_Stc.SCMIPSDBLoaded() ) {
		if ( !m_UserVars.m_Stc.LoadSCMIPSDB() ) {
			AfxMessageBox("PSDB Definition Load Fails");
			GlobalFree ( hResidues );
			rFile.Abort();
			return 0;
		}
	}


	StcGroup->SetNameDescription( ChainName, Description );
	StcGroup->SetResidues( hResidues, ResCount );

	CString CurrentDataType;

	CString sCurrentDataValues;
	HGLOBAL hCurrentDataValues = GlobalAlloc( GMEM_FLAG, 0L );
	DWORD DataCount = 0L;
	DWORD CurrentDataTotal = 0L;

	
	int EOFFLAG = 0;

	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();

		if (tString.GetLength() < 3 ) continue;

		if (tString[0] == '>') break;

		if (tString[0] != 'F') continue;

/*
 *		This third character will be either 
 * 		/ or a number.  / means some sort of feature
 *		where a number specifies disulfide bonds or author's
 *		2ndary structure classification.
 */
		if (tString[2] != '/') {

			// this is a disulfide bond.
			continue;
		}
		else {
			CString DataType;
			int Count = 2;
			int Length = tString.GetLength();
			// Get Red Value
			while( tString[Count] != ' ' && tString[Count] != '\t' ) {
				DataType += tString[Count];
				if ( ++Count >= Length ) break;
			}

			if ( CurrentDataType.IsEmpty() ) {
				CurrentDataType = DataType;
				// CString
			} else if ( CurrentDataType != DataType || EOFFLAG == 1 ) {
				StcDataType *pDT;
				if ( !m_UserVars.m_Stc.LookupDataType( CurrentDataType, &pDT ) ) {
					sCurrentDataValues.Empty();
					GlobalFree( hCurrentDataValues );
					hCurrentDataValues = GlobalAlloc( GMEM_FLAG, 0L );
					CurrentDataTotal = 0L;
					DataCount = 0L;
					continue;
				}

				if ( sCurrentDataValues.GetLength() ) {
					int MoveCount = sCurrentDataValues.GetLength();
					hCurrentDataValues = GlobalReAlloc( hCurrentDataValues, DataCount, GMEM_MOVEABLE);
					char *pData = (char *)GlobalLock(hCurrentDataValues);
					pData += CurrentDataTotal;
					CurrentDataTotal += MoveCount;
					char *pnData = sCurrentDataValues.GetBuffer(MoveCount);
					while( MoveCount-- ) {
						*pData++ = *pnData++;
					}
					GlobalUnlock(hCurrentDataValues);
					sCurrentDataValues.ReleaseBuffer();
					sCurrentDataValues.Empty();
				}

				StcGroup->SetDataTypeValues( CurrentDataType, pDT->ColorMap, hCurrentDataValues, DataCount );
				CurrentDataType = DataType;
				sCurrentDataValues.Empty();
				hCurrentDataValues = GlobalAlloc( GMEM_FLAG, 0L );
				CurrentDataTotal = 0L;
				DataCount = 0L;
			}

			tString = tString.Right( Length - Count );

			// Get White Space
			Count = 0;
			Length = tString.GetLength();
			while( tString[Count] == ' ' || tString[Count] == '\t' ) {
				if ( ++Count >= Length ) break;
			}

			// Trim right hand white space ..
			while( tString[Length-1] == ' ' || tString[Length-1] == '\t' || tString[Length-1] == '\r' || tString[Length-1] == '\n') {
				if ( --Length == 0 ) break;
			}

			// Get Current Data Values
			// sets of 10, 50 at a time
			while( 1 ) {
				if ( (Count + 10 ) >= Length ) {
//					sCurrentDataValues += tString.Mid( Count, Length - Count );
//					DataCount += Length - Count;
					for ( int tc=0; tc<Length - Count; ++tc ) {
						if ( tString[Count+tc] != '/' ) {
							sCurrentDataValues += tString[Count+tc];
							DataCount++;
						}
					}
					break;
				}
//				sCurrentDataValues += tString.Mid( Count, 10 );
				for ( int tc=0; tc<10; ++tc ) {
					if ( tString[Count+tc] != '/' ) {
						sCurrentDataValues += tString[Count+tc];
						DataCount++;
					}
				}
				Count += 10;

				if ( sCurrentDataValues.GetLength() > 1024 ) {
					int MoveCount = sCurrentDataValues.GetLength();
					hCurrentDataValues = GlobalReAlloc( hCurrentDataValues, DataCount, GMEM_MOVEABLE);
					char *pData = (char *)GlobalLock(hCurrentDataValues);
					pData += CurrentDataTotal;
					CurrentDataTotal += MoveCount;
					char *pnData = sCurrentDataValues.GetBuffer(MoveCount);
					while (MoveCount--) {
						*pData++ = *pnData++;
					}
					GlobalUnlock(hCurrentDataValues);
					sCurrentDataValues.ReleaseBuffer();
					sCurrentDataValues.Empty();
				}

				// Skip over seperator
				if ( ++Count >= Length ) break;
			}
		}

	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	if ( DataCount ) {

		StcDataType *pDT;

		if ( m_UserVars.m_Stc.LookupDataType( CurrentDataType, &pDT ) ) {
			if ( sCurrentDataValues.GetLength() ) {
				int MoveCount = sCurrentDataValues.GetLength();
				hCurrentDataValues = GlobalReAlloc( hCurrentDataValues, DataCount, GMEM_MOVEABLE);
				char *pData = (char *)GlobalLock(hCurrentDataValues);
				pData += CurrentDataTotal;
				CurrentDataTotal += MoveCount;
				char *pnData = sCurrentDataValues.GetBuffer(MoveCount);
				while( MoveCount-- ) {
					*pData++ = *pnData++;
				}
				GlobalUnlock(hCurrentDataValues);
				sCurrentDataValues.ReleaseBuffer();
				sCurrentDataValues.Empty();
			}

			StcGroup->SetDataTypeValues( CurrentDataType, pDT->ColorMap, hCurrentDataValues, DataCount );
		} else {
			GlobalFree ( hCurrentDataValues );
		}
	} else {
		GlobalFree ( hCurrentDataValues );
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}


DWORD  
MakeLoc( const CPtrList& listChain, char cChain, const CString& strLoc )
{
	typedef struct {
		char chain;
		DWORD count;
	} stcChain;

	DWORD offset = 0;

	POSITION tPos = listChain.GetHeadPosition();
	while ( tPos ) {
		stcChain *pCH = (stcChain *)listChain.GetNext(tPos);
		if ( cChain == pCH->chain ) break;
		offset += pCH->count;
	}

	return offset + atol( (const char *)strLoc );
	
}

char
GetRes( const CString& ResStr )
{

	static char *aatrans[] = {
		"Ala", "", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile", "", "Lys",
		"Leu", "Met", "Asn", "", "Pro", "Gln", "Arg", "Ser", "Thr", "", "Val",
		"Trp", "Xxx", "Tyr", "Glx" 
	};

	int r;
	// CString
	for ( r = 0; r < 26; ++r ) {
		if ( ResStr.CompareNoCase( aatrans[r]) == 0  ) break;
	}

	if ( r == 26 ) return 0;

	return 'A' + r;

}



BOOL
CGenedocDoc::GetDataTypeValuesFilePDB( const CString& szFilename, CStcGroup *StcGroup )
{

	// Determine File Type.
TRY {

    nErrno = 0;
	CString tString;

	CStdioFile rFile( szFilename, CFile::modeRead );
	

	int hLoc;

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		
		// Look for data start string
		
		if ( (hLoc = tString.Find( "HEADER" )) != -1 ) 
			break;
	}



	if ( tString.GetLength() < hLoc + 67 ) {
		AfxMessageBox("Unexpected End Of File" );
		// fclose( File );
		rFile.Abort();
		return 0;
	}


	// Take name from middle of first line ...
	CString ChainName = tString.Mid( hLoc + 62, 4 );
	CString ChainDesc = tString.Mid( hLoc + 10, 39);


/*
 *	next group of lines will be the actual residue
 *	sequence.  These residues will be grouped in groups 
 *	of 10, terminated by a *...as we go through the sequence,
 *	we will keep track of the number of residues.
 */

	CString sResidues;
	HGLOBAL hResidues = GlobalAlloc( GMEM_FLAG, 0L );
	DWORD ResCount = 0;
	DWORD CurrentResTotal = 0;
	int resFound = 0;

	char curchain = 0;
	typedef struct {
		char chain;
		DWORD count;
	} stcChain;
	CPtrList listChain;

	while (1) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString.ReleaseBuffer();
		int sLoc;

		if ( ( sLoc = tString.Find ("SEQRES")) != -1 ) {
			resFound = 1;
			int Count = 0;
			int Length = tString.GetLength();
			char res;
			// Get Residues Values
			if ( tString.GetLength() < sLoc + 71 ) continue;

			if ( curchain != tString.GetAt(11) ) {
				stcChain* pCH = new stcChain;
				pCH->chain = tString.GetAt(11);
				pCH->count = atol ( tString.Mid(13,4) );
				listChain.AddTail( pCH );
				curchain = tString.GetAt(11);
			}

			res = GetRes( tString.Mid(sLoc + 19,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 23,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 27,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 31,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 35,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 39,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 43,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 47,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 51,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 55,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 59,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 63,3) );
			if ( res ) { sResidues += res; ResCount++; }
			res = GetRes( tString.Mid(sLoc + 67,3) );
			if ( res ) { sResidues += res; ResCount++; }

		} else if ( resFound ) {
			break;
		}
		if ( sResidues.GetLength() > 1024 ) {
			int MoveCount = sResidues.GetLength();
			hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(hResidues);
			pRes += CurrentResTotal;
			CurrentResTotal += MoveCount;
			char *pnRes = sResidues.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(hResidues);
			sResidues.ReleaseBuffer();
			sResidues.Empty();
		}

	}

	if ( sResidues.GetLength() ) {
		int MoveCount = sResidues.GetLength();
		hResidues = GlobalReAlloc( hResidues, ResCount, GMEM_MOVEABLE);
		char *pRes = (char *)GlobalLock(hResidues);
		pRes += CurrentResTotal;
		CurrentResTotal += MoveCount;
		char *pnRes = sResidues.GetBuffer(MoveCount);
		while (MoveCount--) {
			*pRes++ = *pnRes++;
		}
		GlobalUnlock(hResidues);
		sResidues.ReleaseBuffer();
		sResidues.Empty();
	}


	// Test if Definition Loaded ..
	if ( !m_UserVars.m_Stc.SCMIPDBLoaded() ) {
		if ( !m_UserVars.m_Stc.LoadSCMIPDB() ) {
			AfxMessageBox("PDB Definition Load Fails");
			GlobalFree ( hResidues );
			rFile.Abort();
			return 0;
		}
	}


	StcGroup->SetNameDescription( ChainName, ChainDesc );
	StcGroup->SetResidues( hResidues, ResCount );

	CString CurrentDataType;

	CString sCurrentDataValues;
	HGLOBAL hCurrentDataValues = GlobalAlloc( GMEM_FLAG, ResCount );
	char *pData = (char *)GlobalLock(hCurrentDataValues);
	char *spData = pData;
	DWORD rCount = ResCount;
	while ( rCount-- ) *spData++ = ' ';
	DWORD loc1, loc2;

	int EOFFLAG = 0;

	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();

//		if ( tString .Find("ATOM") != -1 ) break;
		if ( tString.Left(4) == "ATOM" ) break;

		int sLoc;

		// Get Current Data Values
		// sets of 10, 50 at a time
		if ( (sLoc = tString.Find( "HELIX" )) != -1 ) {
			loc1 = MakeLoc( listChain, tString.GetAt(19), tString.Mid( sLoc + 21, 4 ) ) - 1;
			loc2 = MakeLoc( listChain, tString.GetAt(31), tString.Mid( sLoc + 33, 4 ) ) - 1;
			if ( loc1 >= ResCount || loc2 >= ResCount ) continue;
			if ( loc1 < 0 || loc2 < 0 ) continue;
			for ( DWORD l = loc1; l <= loc2; ++l ) {
				pData[l] = 'H';
			}
		} else if ( (sLoc = tString.Find( "SHEET" )) != -1 ) {
			loc1 = MakeLoc( listChain, tString.GetAt(21), tString.Mid( sLoc + 22, 4 ) ) - 1;
			loc2 = MakeLoc( listChain, tString.GetAt(32), tString.Mid( sLoc + 33, 4 ) ) - 1;
			if ( loc1 >= ResCount || loc2 >= ResCount ) continue;
			if ( loc1 < 0 || loc2 < 0 ) continue;
			for ( DWORD l = loc1; l < loc2; ++l ) {
				pData[l] = 'S';
			}
		} else if ( (sLoc = tString.Find( "TURN" )) != -1 ) {
			loc1 = MakeLoc( listChain, tString.GetAt(19), tString.Mid( sLoc + 20, 4 ) ) - 1;
			loc2 = MakeLoc( listChain, tString.GetAt(30), tString.Mid( sLoc + 31, 4 ) ) - 1;
			if ( loc1 >= ResCount || loc2 >= ResCount ) continue;
			if ( loc1 < 0 || loc2 < 0 ) continue;
			for ( DWORD l = loc1; l < loc2; ++l ) {
				pData[l] = 'T';
			}
		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	GlobalUnlock( hCurrentDataValues );

	StcDataType *pDT;
	if ( m_UserVars.m_Stc.LookupDataType( "PDB", &pDT ) ) {
		StcGroup->SetDataTypeValues( "PDB", pDT->ColorMap, hCurrentDataValues, ResCount );
	} else {
		GlobalFree ( hCurrentDataValues );
	}

	POSITION tPos = listChain.GetHeadPosition();
	while ( tPos ) {
		delete (stcChain *)listChain.GetNext(tPos);
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}



