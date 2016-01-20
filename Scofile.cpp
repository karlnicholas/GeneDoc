
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



char	*Scoremonths[] = {
    "JAN",
    "FEB",
    "MAR",
    "APR",
    "MAY",
    "JUN",
    "JUL",
    "AUG",
    "SEP",
    "OCT",
    "NOV",
    "DEC"
};

 
#pragma optimize ("", off )


int
CGenedocDoc::WriteScoreFile( 
	const char *FileName
) {

	int i, j, rc = 1;

TRY {

	char * BuildBuff;
	char LeadBuff[512];
	char ScoreBuff[33];
	// First loop writes comments
	GeneStor *GOut;
	GeneStor *GInner;
	unsigned long Score;
	DWORD Length;
	DWORD tCount;

	GeneStor tGStor;

#ifdef _WIN32
	SYSTEMTIME LocTime;
#else
	time_t	cur;		/*	Current time	*/
	struct tm	*cur_tm;	/*	Time struct	*/
#endif


	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;
	
	POSITION tPos;
	
	CStdioFile wFile ( FileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	HANDLE hBuildBuff = GlobalAlloc ( GMEM_FLAG, Count * 20 + 1024 );
	if ( hBuildBuff == NULL ) {
		AfxMessageBox("writescorefile:globalalloc:fail:1");
		delete pWS;
		return 0;
	}
	BuildBuff = (char *)GlobalLock ( hBuildBuff );
	if ( hBuildBuff == NULL ) {
		AfxMessageBox("writescorefile:globallock:fail:1");
		delete pWS;
		return 0;
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
		if ( (pWS[i]).pText == NULL ) {
			AfxMessageBox("writescorefile:globallock:fail:2");
			delete pWS;
			return 0;
		}
		i++;
		if ( tCGSeg->GetTitle().GetLength() > MaxTitle ) {
			MaxTitle = tCGSeg->GetTitle().GetLength();
		}
	}

	// only sequences now ..
	
	
	// Some Header Stuff for File.
//	sprintf(BuildBuff, "%s\n", FileName );
//	wFile.WriteString( BuildBuff );

#ifdef _WIN32
	GetLocalTime ( &LocTime );
	sprintf(BuildBuff, "%d-%s-%d  %02d:%02d\n", LocTime.wDay, Scoremonths[LocTime.wMonth - 1],
		LocTime.wYear, LocTime.wHour,	LocTime.wMinute );
#else
	cur = time(NULL);
	cur_tm = localtime(&cur);
	sprintf(BuildBuff, "%d-%s-%d  %02d:%02d\n", cur_tm->tm_mday, Scoremonths[cur_tm->tm_mon],
		cur_tm->tm_year + 1900, cur_tm->tm_hour,
		cur_tm->tm_min);
#endif

	wFile.WriteString ( BuildBuff );


	BuildBuff[0] = 0;

	wFile.WriteString( "\n" );

	strcat ( BuildBuff, "          " );

	for ( j = 1; j < Count; j+=2 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%20s", (const char *)pWS[j].pCGSeg->GetTitle() );
		LeadBuff[sizeof(LeadBuff)-1] = 0;
		strcat ( BuildBuff, LeadBuff );
	}

	strcat ( BuildBuff, "\n" );
	wFile.WriteString( BuildBuff );

	BuildBuff[0] = 0;

	wFile.WriteString( "\n" );

	for ( j = 0; j < Count; j+=2 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%20s", (const char *)pWS[j].pCGSeg->GetTitle() );
		LeadBuff[sizeof(LeadBuff)-1] = 0;
		strcat ( BuildBuff, LeadBuff );
	}

	strcat ( BuildBuff, "\n" );
	wFile.WriteString( BuildBuff );
	
	BuildBuff[0] = 0;

	wFile.WriteString( "\n" );

	BuildBuff[0] = 0;
	strcat ( BuildBuff, "          " );

	for ( j = 0; j < Count; ++j ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%10d", j + 1 );
		LeadBuff[sizeof(LeadBuff)-1] = 0;
		strcat ( BuildBuff, LeadBuff );
	}
	strcat ( BuildBuff, "\n" );
	wFile.WriteString( BuildBuff );

	BuildBuff[0] = 0;

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GOut = (pWS[i]).pText;

		BuildBuff[0] = 0;
		sprintf ( BuildBuff, "%-10d", i + 1 );

		for ( j = 0; j < Count; ++j ) {

			if ( j > i ) {
				continue;
			}

			GInner = (pWS[j]).pText;
			Score = 0;
			
			// First Number
			// This Section for Absolute Similarity
			// Here we have Absoulte Calc's
			Length = pWS[j].pCGSeg->GetTextLength();

			int OpenGp = 0, TopGap = 0;
			
			tCount = 0; 
			while ( tCount < Length ) {
			
				tGStor = GInner[tCount];	// Indexed from Loop B
				char Nuc1 = toupper(tGStor.CharGene);
				tGStor = GOut[tCount];	// Indexed from Loop A
				char Nuc2 = toupper(tGStor.CharGene);
			
				int gc1 = !(Nuc1 >= 'A' && Nuc1 <= 'Z');
				int gc2 = !(Nuc2 >= 'A' && Nuc2 <= 'Z');

				if ( !gc1 && !gc2 ) {
					Score += ScoreCurrentArray(Nuc1, Nuc2 );
					OpenGp = 0;
				} else if ( gc1 && !gc2 ) {
					Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						Score += NewGap;
						TopGap = 1;
					} else {
						if ( !TopGap ) {
							Score += NewGap;
							TopGap = 1;
						}
					}
				} else if ( !gc1 && gc2 ) {
					Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						Score += NewGap;
						TopGap = 0;
					} else {
						if ( TopGap ) {
							Score += NewGap;
							TopGap = 0;
						}
					}
				}
				tCount = tCount + 1L;
			}
            
            _ultoa( Score, ScoreBuff, 10 );
			_snprintf( LeadBuff, sizeof(LeadBuff), "%10s", ScoreBuff );

//			_snprintf( LeadBuff, sizeof(LeadBuff), "%10ld", Score );
//			LeadBuff[sizeof(LeadBuff)-1] = 0;

			strcat ( BuildBuff, LeadBuff );
		}

		strcat ( BuildBuff, "\n" );
		wFile.WriteString( BuildBuff );
		wFile.WriteString( "\n" );

	}
	
	BuildBuff[0] = 0;
	strcat ( BuildBuff, "          " );

	for ( j = 0; j < Count; ++j ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%10d", j + 1 );
		LeadBuff[sizeof(LeadBuff)-1] = 0;
		strcat ( BuildBuff, LeadBuff );
	}
	strcat ( BuildBuff, "\n" );
	wFile.WriteString( BuildBuff );

	wFile.WriteString( "\n" );
	wFile.WriteString( "\n" );

	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	// End routine Checks.
	GlobalUnlock ( hBuildBuff );
	GlobalFree ( hBuildBuff );
	delete pWS;

	wFile.Close();

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

#pragma optimize ("", on )
