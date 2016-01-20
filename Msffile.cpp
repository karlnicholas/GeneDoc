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

// This read .msf gene sequence files.

// First accept free comments and find group names, sizes and
// checksums.
// look for the // for data start.
//

// List of free comments
// List of names, sizes, checks and weights.
// List of sequences


#include "stdafx.h"

#include <ctype.h>

static long CheckSeq(const char *strand, DWORD Len);


int
CGenedocDoc::ReadMSFFile( 
	CPtrList *CommentList, 
	CPtrList *SequenceList, 
	const char *FileName
) {


	int i, rc;
TRY {

	SeqNameStruct *tSNS;
	int AllSumsOk = 1;
	CString *cStr;


#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif	
	char rbuff[1024];
	CString tString;

#ifdef _WIN32
	CStdioFile rFile( FileName, CFile::modeRead | CFile::typeText | CFile::shareDenyNone );
#else
	CStdioFile rFile( FileName, CFile::modeRead | CFile::typeText );
#endif

	// First loop looks for comments
	while (1) {
		// clear out temp string.
		tString.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( rFile.ReadString( rbuff, sizeof(rbuff) ) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		// CString
		tString = CString(rbuff).SpanExcluding("\n\r");
#else
		if ( !rFile.ReadString( tString ) ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
#endif

		// Must be a comment
		CommentList->AddTail( new CString ( tString ) );

		// Check if we are done with comments
		if ( tString.Find( ".." ) != -1 && (tString.Find( "MSF:" ) != -1 || tString.Find( "msf:" ) != -1) ) {
			break;		// Found the Start Data Flag
		}
	}
	
	// Second loop looks for seqence names 
	while (1) {
		// clear out temp string.
		tString.Empty();
#if !defined(_WIN32) || _MSC_VER < 999
		if ( rFile.ReadString( rbuff, sizeof(rbuff)) == NULL ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
		tString = CString(rbuff).SpanExcluding("\n\r");
#else
		if ( !rFile.ReadString( tString ) ) {
			// EOF too early
			AfxMessageBox("Unexpected End Of File" );
			// fclose( File );
			rFile.Abort();
			return 0;
		}
#endif
		// Check if we are done with sequence names
		if ( tString.Find( "//" ) != -1 ) {
			break;		// Found the Start Data Flag
		}
		// See if this is a comment or a name
		if ( tString.Find("Name:") == -1 ) {
			// Loop again, its not a name. (error?)
			continue;
		}

		// Must be a name line
		// Allocate a name storage structure
		tSNS = new SeqNameStruct;
		
		if ( tSNS == 0 ) {
			AfxMessageBox("readmsffile:new:fail:1");
			return 0;
		}
		
		// Get the name out
		int tLoc = tString.Find("Name:");
		tLoc += 6;
		int tSNLoc = 0;
		int tstrLen = tString.GetLength();
//		do {
//			i = tSNS->Name[tSNLoc++] = tString[tLoc++];
//			if ( tSNLoc == 10 && tString[tLoc]!= ' ' ) {
//				NameTrunc = 1;
//				tSNLoc++;
//				break;
//			}
//		}

		while ( tString[tLoc] != ' ' ) {
			tSNS->Name += tString[tLoc++];
			if ( tLoc >= tstrLen ) break;
		}

		if ( tSNS->Name.GetLength() == 0 ) {
			if ( AfxMessageBox( "Empty Name, Skipping line.", MB_OKCANCEL ) == IDCANCEL ) {
				rFile.Abort();
				return 0;
			}
			continue;
		}

//		tSNLoc--;
//		tSNS->Name[tSNLoc] = 0;

		// Get the Length out
		tLoc = tString.Find( "Len:" );
		if ( tLoc == -1 ) {
			if ( AfxMessageBox( "'Len:' field not found in .MSF file", MB_OKCANCEL ) == IDCANCEL ) {
				rFile.Abort();
				return 0;
			}
		} else {
			tLoc += 4;
			tSNS->Len = atoi( (const char *)tString + tLoc );
			tSNS->Start = 1;
			tSNS->UseLen = 0L;
		}
		
		// Get the 'check' (checksum?) out
		tLoc = tString.Find( "Check:" );
		if ( tLoc == -1 ) {
			if ( AfxMessageBox(" 'Check:' field not found in .MSF file", MB_OKCANCEL ) == IDCANCEL ) {
				rFile.Abort();
				return 0;
			}
		} else {
			tLoc += 6;
			tSNS->Check = atoi( (const char *)tString + tLoc );
		}
		
		// Get the 'weight' out
		tLoc = tString.Find( "Weight:" );
		if ( tLoc == -1 ) {
			if ( AfxMessageBox(" 'Weight:' field not found in .MSF file", MB_OKCANCEL ) == IDCANCEL ) {
				rFile.Abort();
				return 0;
			}
		} else {
			tLoc += 7;
			tSNS->Weight = atof( (const char *)tString + tLoc );
		}
		// Put the name structure on the list

		// Check for duplicates ..
		POSITION tPos1 = SequenceList->GetHeadPosition();
		while ( tPos1 != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos1);
			if ( CString(tSNS1->Name) == tSNS->Name ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", tSNS->Name );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}
		SequenceList->AddTail( tSNS );
	}


	// Here we are if the Data Marker has been found.
	// Just make sure we did get some names
	int SeqCount = SequenceList->GetCount();
	if ( SeqCount == 0 ) {
		AfxMessageBox( "SeqCount 0. Not Right!" );
		rFile.Abort();
		// fclose( File );
		return 0;
	}
	
	// Allocate memory for subsequent sequence data
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		tSNS = (SeqNameStruct*)SequenceList->GetNext(tPos);
		// Allocate it
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, tSNS->Len );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadMsfFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}
		// Lock it down
		tSNS->tpc = (char *)GlobalLock( tSNS->hText);
		// Abort if that fails
		if ( tSNS->tpc == NULL ) {
			AfxMessageBox("ReadMsfFile:GlobalLock:Fail 1");
			rFile.Abort();
			return 0;
		}
		// Save it for later.
		tSNS->pText = tSNS->tpc;
	}

	int EOFFLAG = 0;
	int StartPos;
	CString t2Str;
	rc = 1;

	int linecount = 0;

	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
#if !defined(_WIN32) || _MSC_VER < 999
		if ( rFile.ReadString( rbuff, sizeof(rbuff) ) == NULL) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString = CString(rbuff).SpanExcluding("\n\r");
#else
		BOOL MYVAR = rFile.ReadString( tString );
		if ( ! MYVAR ) {
			// Done .. break out
			EOFFLAG = 1;
		}

#endif

		linecount++;

		// Search all the name structures for a match
		tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			tSNS = (SeqNameStruct*)SequenceList->GetNext(tPos);
			// Test for this anme
			if ( (StartPos = tString.Find(tSNS->Name)) == -1 ) {
				continue;
			}
			

			if ( StartPos > 0 ) {
				if ( tString[StartPos - 1] != ' ' ) {
					continue;
				}
			}

			// Point past name
			int StrLength = tSNS->Name.GetLength();
			StartPos += StrLength;

			// Make sure this really is the right name, not a substring
			// Also Test if the Name is 10 chars in size.
			if ( tString[StartPos] != ' ' ) {
				continue;
			}

			// Get to proper Start of Data
			while ( tString[StartPos] == ' ' ) { StartPos++; }
				              
			// Clear out temp storage string.
			t2Str.Empty();

			// Compute proper Length
			StrLength = tString.GetLength();
			while ( 
				tString[StrLength-1] == ' ' 
				|| tString[StrLength-1] == '\n' 
				|| tString[StrLength-1] == '\r'
			) { --StrLength; }

			// Copy length 10 pieces
			while ( (StartPos + 10) < StrLength ) {
				t2Str += tString.Mid(StartPos,10);
				if ( tString[StartPos+10] != ' ' ) {
					StartPos += 10;
//					AfxMessageBox( "Space Expected but not found in Data Rows!");
//					rc = 0;
//					goto Error;
				} else {
					StartPos += 11;
				}
			}
			// Copy Left over piece, if any
			int tLen = StrLength - StartPos;
			if ( tLen != 0 ) {
				t2Str += tString.Mid(StartPos,tLen);
			}

			// Copy the chars into global mem
			// Convert '.' to '-'
			const char *pc2 = t2Str;
			i = t2Str.GetLength();
			while ( i-- ) { 
				// Check no memory leak too
				if ( tSNS->UseLen++ >= tSNS->Len ) {
					AfxMessageBox( "Received more bytes in data than indicated by header Len: Field" );
					rc = 0;
					i = 0;
					goto Error;
				}

				if ( *pc2 == ' ' ) {
					AfxMessageBox( "Unexpected space in Data Rows!" );
					rc = 0;
					i = 0;
					goto Error;
				}
				
//				if ( !isalpha(*pc2) && (*pc2 != '.' ) ) {
//					AfxMessageBox( 
//						"Non-Alpha/Non-Dot character in Data Rows! (Likely cause is a Stop DNA translation char \'*\' in the Data File.)"
//					);
//					rc = 0;
//					goto Error;
//				}

				if ( (*tSNS->tpc = *pc2) == '.' ) {
					if ( m_UserVars.m_GapInd == 0 ) {
						*tSNS->tpc = '-';
					} else {
						*tSNS->tpc = '.';
					}
				}
				tSNS->tpc++;
				pc2++;
			}
			// Done with this data line
			break;
		}
	// Loop until end of file now.
	} while ( EOFFLAG == 0 );
	
	// Sanity Checks ..
	
	AllSumsOk = 1;
	// Unlock sequence storage
	tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		tSNS = (SeqNameStruct*)SequenceList->GetNext(tPos);
    
		if ( tSNS->UseLen != tSNS->Len ) {
			rc = 0;
			if ( AfxMessageBox( "Not as many bytes in data as indicated by Len!", MB_OKCANCEL ) == IDCANCEL ) goto Error;
		}
		
		// Yea, we have a working checksum rountine!
		if ( CheckSeq ( tSNS->pText, tSNS->Len ) != tSNS->Check ) {
			AllSumsOk = 0;
		}
	}

    if ( !AllSumsOk ) {
		AfxMessageBox( "At Least One Checksum Check failed!", MB_OK );
	}


	cStr = (CString *)CommentList->GetTail();
	// Looking for Master Checksum location ...

	if ( (rc = cStr->Find("Check:")) != -1 ) {
			
		int OldSum = atoi ( ((const char *)*cStr) + rc + 7 );

		long NewSum = 0;
		POSITION tPos2 = SequenceList->GetHeadPosition();
			
		while ( tPos2 != NULL ) {
			tSNS = (SeqNameStruct*)SequenceList->GetNext(tPos2);
			NewSum += CheckSeq ( tSNS->pText, tSNS->Len );
		}

		NewSum = NewSum % 10000L;
			
		if ( OldSum != (int)NewSum) {
			AfxMessageBox ( "Project Checksum does not match!", MB_OK );
		}
	} else {
		AfxMessageBox ( "Project Checksum Not Found!", MB_OK );
	}
			

Error:

	// Unlock sequence storage
	tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		tSNS = (SeqNameStruct*)SequenceList->GetNext(tPos);
		GlobalUnlock (tSNS->hText );
	}
    
	rFile.Close();
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

static const int MSFFILEtable[256] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 
    0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 
    0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 
    0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 
    0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
  };
  

// 
static 
long
CheckSeq(const char *strand, DWORD Len) 
{
	long check;
	long count;

  /* this table is designed as a cheap way to perform toupper() */

  for(check = 0, count = 1; Len--; strand++) {
  	if ( (*strand == '-') || (*strand == '.') ) {
	    check = (check + count * MSFFILEtable[(int)'.']) % 10000L;
  	} else {
	    check = (check + count * MSFFILEtable[(int) *strand]) % 10000L;
	}
    if(count == 57) 
      count = 1;
    else
      count++;
  }
  return check;

} /* end CheckSeq */

// 
static
long CheckGStor( GeneStor *pGS, DWORD Len )
{
	long check;
	long count;

	/* this table is designed as a cheap way to perform toupper() */

	check = 0;
	count = 1;
	while ( Len-- ) {
		if ( (pGS->CharGene == '-') || (pGS->CharGene == '.' ) ) {
		    check = (check + count * MSFFILEtable[(unsigned char)'.']) % 10000L;
	  	} else {
		    check = (check + count * MSFFILEtable[(unsigned char) pGS->CharGene]) % 10000L;
		}
		if(count == 57) 
			count = 1;
		else
			count++;
		pGS++;
	}
	return check;
}
/* end CheckSeq */

char	*MSFFILEmonths[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

int
CGenedocDoc::WriteMSFFile( 
	const char *FileName
) {


	int i, rc = 1;
	// Lets just make sure the data is correct before we save ...
	ReSizeRows();

	// Rename original to backup file
	if ( m_UserVars.m_MakeBackups ) {
		CString NewName( FileName );
		if ( NewName.Right( 3 ).CompareNoCase( "MSF" ) == 0 || NewName.Right( 3 ).CompareNoCase( "MSB" ) == 0 ) {
			NewName.SetAt(NewName.GetLength() - 1, 'B');
		} else {
			NewName += ".MSB";
		}
		TRY {
			CFile::Remove( NewName );
		}  CATCH (CFileException, e ) {
			// do nothing
		} END_CATCH

		TRY {
			CFile::Rename( FileName, NewName );
		}  CATCH (CFileException, e ) {
			// do nothing
		} END_CATCH
	}


TRY {

	
	char BuildBuff[1024];
	char LeadBuff[512];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
		CString *Title;
	} *pWS;

	POSITION tPos;

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';

	CStdioFile wFile( FileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	i = 0;
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
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
	
	int MaxTitle = 0;
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
		if ( tCGSeg->GetTitle().GetLength() > MaxTitle ) {
			MaxTitle = tCGSeg->GetTitle().GetLength();
		}
	}
	
	
	// First loop writes comments
	CString *cStr;
	tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while (tPos != NULL ) {

		cStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
//		*cStr += '\n';
		
		// Looking for Master Checksum location ...
		if ( cStr->Find("..") != -1 && cStr->Find("MSF:") != -1 ) {

			DWORD	longest = 0;	/*	Longest alignment	*/
			char	date[30];	/*	Holds the current date & time	*/
#ifdef _WIN32
			SYSTEMTIME LocTime;
#else
			time_t	cur;		/*	Current time	*/
			struct tm	*cur_tm;	/*	Time struct	*/
#endif
			long NewSum = 0;

			for ( i = 0; i < Count; ++i ) {
				NewSum += CheckGStor( (pWS[i]).pText, (pWS[i]).pCGSeg->GetTextLength() );
				longest = max(longest, (pWS[i]).pCGSeg->GetTextLength() );
			}
			NewSum = NewSum % 10000L;

			date[0] = '\0';

#ifdef _WIN32
			GetLocalTime ( &LocTime );
			sprintf(date, "%s %d, %d  %02d:%02d", MSFFILEmonths[LocTime.wMonth - 1],
				LocTime.wDay, LocTime.wYear, LocTime.wHour,	LocTime.wMinute );
#else
			cur = time(NULL);
			cur_tm = localtime(&cur);
			sprintf(date, "%s %d, %d  %02d:%02d", MSFFILEmonths[cur_tm->tm_mon],
				cur_tm->tm_mday, cur_tm->tm_year + 1900, cur_tm->tm_hour,
				cur_tm->tm_min);
#endif
			char *pFile = (char *)FileName + strlen (FileName );
			while ( (--pFile) != FileName ) {
				if (*pFile == '\\' ) break;
				if (*pFile == '/' ) break;
				if (*pFile == ':' ) break;
				if (*pFile == ' ' ) break;
			}
			++pFile;
			
			char ProjType = m_UserVars.m_ProjectType == 1 ? 'P' : 'N' ;
		
			_snprintf(BuildBuff, sizeof(BuildBuff), " %s  MSF: %d  Type: %c  %s  Check: %4d ..\n",
				pFile, (int)longest, ProjType, date, (int)NewSum);

			//
			wFile.WriteString( BuildBuff );

		} else {
			wFile.WriteString( *cStr + "\n" );
		}
	}
	
	// Put a blank line
	wFile.WriteString ( "\n" );

	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		memset ( BuildBuff, ' ', MaxTitle );
		
		const char *tcp = (pWS[i]).pCGSeg->GetTitle();
		int tLen = (pWS[i]).pCGSeg->GetTitle().GetLength();
		memcpy ( 
			BuildBuff + MaxTitle - tLen, 
			tcp,
			tLen
		);
		BuildBuff[MaxTitle] = 0;
		*(pWS[i]).Title = BuildBuff;
	}
			
	memset( LeadBuff, ' ', sizeof(LeadBuff));
	LeadBuff[MaxTitle +2] = 0;
		
	
	// Second loop writes sequence names and lines.
	for ( i = 0; i < Count; ++i ) {
		
		_snprintf ( BuildBuff, sizeof(BuildBuff), 
			" Name: %-16s Len: %5ld  Check: %-4d  Weight: %6.2f\n", 
			(const char *)(pWS[i]).pCGSeg->GetTitle(), 
			(pWS[i]).pCGSeg->GetTextLength(), 
			(int)CheckGStor( (pWS[i]).pText, (pWS[i]).pCGSeg->GetTextLength() ), 
			(pWS[i]).pCGSeg->GetWeight()
		);
		
		wFile.WriteString ( BuildBuff );
	}
	
	wFile.WriteString( "\n" );

	// Put in data seperator
	_snprintf ( BuildBuff, sizeof(BuildBuff), "//\n" );
	wFile.WriteString( BuildBuff );

	DWORD CurPos = 0;
	char DataBlock[5][11];
	DWORD Len = (pWS[0]).pCGSeg->GetTextLength();
	int LineNum;

	while ( (CurPos + 50L) < Len ) {

		LineNum = 0;

		while ( LineNum < Count ) {
			// clear out temp string.
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

			if ( LineNum == 0 ) {
				wFile.WriteString( "\n" );
				_snprintf ( BuildBuff, sizeof(BuildBuff), 
					"%s%-5ld                                            %5ld \n", 
					LeadBuff, 
					CurPos + 1, 
					CurPos + 50L
				);
				wFile.WriteString( BuildBuff );
				memset ( BuildBuff, ' ', sizeof(BuildBuff));

			}
			int j;
			// Build data blocks
			for ( i=0; i < 5; ++i ) {
				GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos + (i * 10 );
				for ( j = 0; j < 10; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '.';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = 0;
			}

			sprintf ( BuildBuff, 
				"%s  %s %s %s %s %s \n", 
				(const char *)*(pWS[LineNum]).Title, 
				DataBlock[0], 
				DataBlock[1], 
				DataBlock[2], 
				DataBlock[3], 
				DataBlock[4]
			);
			wFile.WriteString( BuildBuff );
			
			LineNum++;
		}

		CurPos += 50L;

	};
	
	// Do Last set of lines 

	Len = (pWS[0]).pCGSeg->GetTextLength() - CurPos;
	
	int tCount10 = (int)Len / 10;
	int tCountr = (int)Len % 10;

	LineNum = 0;

	while ( LineNum < Count ) {
	
			// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		if ( LineNum == 0 ) {
			// a null newline
			wFile.WriteString( "\n" );

			char spacebuff[50];
			memset ( spacebuff, ' ', sizeof(spacebuff));

			int SpaceLen = (11 * tCount10) + tCountr;

			if ( SpaceLen <= 10 ) {
				SpaceLen = 1;
			} else {
				SpaceLen -= 10;
			}
			spacebuff[SpaceLen] = 0;

			_snprintf ( BuildBuff, sizeof(BuildBuff), 
				"%s%-5ld%s%5ld \n", 
				LeadBuff, 
				CurPos + 1, 
				spacebuff, 
				CurPos + Len
			);

			wFile.WriteString( BuildBuff );
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

		}
		int j;
		for ( i=0; i < 5; ++i ) {
			if ( i < tCount10 ) {
				GeneStor *tgs = (GeneStor *)((pWS[LineNum]).pText) + CurPos + (i * 10);
				for ( j = 0; j < 10; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '.';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = 0;
			} else if ( i == tCount10 ) {

				GeneStor *tgs = (GeneStor *)((pWS[LineNum]).pText) + CurPos + (i * 10);
				for ( j = 0; j < tCountr; ++j ) {
					if ( tgs->CharGene == tGapChar ) {
						DataBlock[i][j] = '.';
					} else {
						DataBlock[i][j] = tgs->CharGene;
					}
					tgs++;
				}
				DataBlock[i][j] = 0;
			} else {
				DataBlock[i][0] = 0;
			}
		}
			
		sprintf ( BuildBuff, 
			"%s  %s %s %s %s %s \n", 
			(const char *)*(pWS[LineNum]).Title, 
			DataBlock[0], 
			DataBlock[1], 
			DataBlock[2], 
			DataBlock[3], 
			DataBlock[4]
		);
		wFile.WriteString( BuildBuff );
	
		LineNum++;
	}
	
	
	wFile.WriteString( "\n" );

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	for ( i=0; i < Count-3; ++i ) {
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

