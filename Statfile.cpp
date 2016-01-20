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


char	*Statmonths[] = {
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

/*
	BOOL	m_RepExactMatch;
	BOOL	m_RepJuxtaposition;
	BOOL	m_RepAlignedGaps;

	BOOL	m_RepAbsoluteVal;
	BOOL	m_RepPercentVal;

	int		m_RepOutMatrix; // 0 yes 1=no

	int		m_RepLabelTop;  // Top, Top and Side
	int		m_RepLabelSingle; // Double horizontal lines?
*/

int
CGenedocDoc::WriteStatFile( 
	const char *FileName
) {

	int i, j, rc = 1;
TRY {
	char *BuildBuff1;
	char *BuildBuff2;
	char *BuildBuff3;
	char LeadBuff[512];

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

	HANDLE hBuildBuff1 = GlobalAlloc ( GMEM_FLAG, Count * 20 + 1024 );
	if ( hBuildBuff1 == NULL ) {
		AfxMessageBox("writestatfile:globalalloc:fail:1");
		delete pWS;
		return 0;
	}
	BuildBuff1 = (char *)GlobalLock ( hBuildBuff1 );
	if ( hBuildBuff1 == NULL ) {
		AfxMessageBox("writestatfile:globallock:fail:1");
		delete pWS;
		return 0;
	}

	HANDLE hBuildBuff2 = GlobalAlloc ( GMEM_FLAG, Count * 20 + 1024 );
	if ( hBuildBuff2 == NULL ) {
		AfxMessageBox("writestatfile:globalalloc:fail:1");
		delete pWS;
		return 0;
	}
	BuildBuff2 = (char *)GlobalLock ( hBuildBuff2 );
	if ( hBuildBuff2 == NULL ) {
		AfxMessageBox("writestatfile:globallock:fail:1");
		delete pWS;
		return 0;
	}

	HANDLE hBuildBuff3 = GlobalAlloc ( GMEM_FLAG, Count * 20 + 1024 );
	if ( hBuildBuff3 == NULL ) {
		AfxMessageBox("writestatfile:globalalloc:fail:1");
		delete pWS;
		return 0;
	}
	BuildBuff3 = (char *)GlobalLock ( hBuildBuff3 );
	if ( hBuildBuff3 == NULL ) {
		AfxMessageBox("writestatfile:globallock:fail:1");
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
			AfxMessageBox("writestatfile:globallock:fail:2");
			delete pWS;
			return 0;
		}
		i++;
		if ( tCGSeg->GetTitle().GetLength() > MaxTitle ) {
			MaxTitle = tCGSeg->GetTitle().GetLength();
		}
	}
	
	// only sequences now ..
	
	
	// First loop writes comments
	GeneStor *GOut;
	GeneStor *GInner;
	long ScoreA;
	long ScoreS;
	long ScoreG;
	DWORD Length;
	DWORD Total;

	// Some Header Stuff for File.
//	sprintf(BuildBuff1, "%s\n", FileName );
//	wFile.WriteString( BuildBuff1 );

#ifdef _WIN32
	GetLocalTime ( &LocTime );
	sprintf(BuildBuff1, "%d-%s-%d  %02d:%02d\n\n", LocTime.wDay, Statmonths[LocTime.wMonth - 1],
		LocTime.wYear, LocTime.wHour,	LocTime.wMinute );
#else
	cur = time(NULL);
	cur_tm = localtime(&cur);
	sprintf(BuildBuff1, "%d-%s-%d  %02d:%02d\n\n", cur_tm->tm_mday, Statmonths[cur_tm->tm_mon],
		cur_tm->tm_year + 1900, cur_tm->tm_hour,
		cur_tm->tm_min);
#endif
	wFile.WriteString( BuildBuff1 );

/*
	for ( j = 0; j < Count; ++j ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%6d ", j + 1 );
		LeadBuff[sizeof(LeadBuff)-1] = 0;
		strcat ( BuildBuff1, LeadBuff );
	}
	wFile.WriteString( BuildBuff1 );
	wFile.WriteString( "\n" );
	wFile.WriteString( "\n" );
*/

	if ( MaxTitle  < 7 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%6s " );
	} else {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%%ds ", ((MaxTitle /2) *2) + 2 );
	}
	CString strPrintTitle( LeadBuff );

	if ( MaxTitle  < 7 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%6d " );
	} else {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%%dd ", ((MaxTitle /2) *2) + 2 );
	}
	CString strPrintVal( LeadBuff );

	if ( MaxTitle  < 7 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%6d%%%%" );
	} else {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%%dd%%%%", ((MaxTitle /2) *2) + 2 );
	}
	CString strPrintPer( LeadBuff );
	
	if ( MaxTitle  < 7 ) {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%-%ds%%-%ds%%6s%%6d\n", ((MaxTitle /2) *2) + 2, ((MaxTitle /2) *2) + 2 );
	} else {
		_snprintf( LeadBuff, sizeof(LeadBuff), "%%-%ds%%-%ds%%6s%%%dd\n", ((MaxTitle /2) *2) + 2, ((MaxTitle /2) *2) + 2, ((MaxTitle /2) *2) + 2 );
	}
	CString strPrintRowVal( LeadBuff );

	if ( MaxTitle  < 7 ) {
		memset( LeadBuff, ' ', 7 );
		LeadBuff[7] = 0;
	} else {
		memset( LeadBuff, ' ', (((MaxTitle /2) *2) + 2) + 1 );
		LeadBuff[(((MaxTitle /2) *2) + 2) + 1] = 0;
	}
	CString strPrintSpace( LeadBuff );


	if ( m_UserVars.m_RepLabelSingle == 0 && m_UserVars.m_RepOutMatrix == 0 ) {

		BuildBuff1[0] = 0;
		strcat ( BuildBuff1, (const char *)strPrintSpace );

		for ( j = 0; j < Count; j++ ) {
			_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintTitle, (const char *)pWS[j].pCGSeg->GetTitle() );
			LeadBuff[sizeof(LeadBuff)-1] = 0;
			strcat ( BuildBuff1, LeadBuff );
		}

		wFile.WriteString( BuildBuff1 );
		wFile.WriteString( "\n" );
		wFile.WriteString( "\n" );

	} else if ( m_UserVars.m_RepLabelSingle == 1 && m_UserVars.m_RepOutMatrix == 0 ) {



		BuildBuff1[0] = 0;
		strcat ( BuildBuff1, (const char *)strPrintSpace  );

		for ( j = 1; j < Count; j+=2 ) {
			_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintTitle, (const char *)pWS[j].pCGSeg->GetTitle() );
			LeadBuff[sizeof(LeadBuff)-1] = 0;
			strcat ( BuildBuff1, (const char *)strPrintSpace );
			strcat ( BuildBuff1, LeadBuff );
		}

		wFile.WriteString( BuildBuff1 );
		wFile.WriteString( "\n" );

		BuildBuff1[0] = 0;

		for ( j = 0; j < Count; j+=2 ) {
			_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintTitle, (const char *)pWS[j].pCGSeg->GetTitle() );
			LeadBuff[sizeof(LeadBuff)-1] = 0;
			strcat ( BuildBuff1, (const char *)strPrintSpace );
			strcat ( BuildBuff1, LeadBuff );
		}

		wFile.WriteString( BuildBuff1 );
		wFile.WriteString( "\n" );
		wFile.WriteString( "\n" );
	}

	
	
	for ( i = 0; i < Count; ++i ) {
		GOut = (pWS[i]).pText;


		if ( m_UserVars.m_RepOutMatrix == 0 && (m_UserVars.m_RepLabelTop==0 ) ) {
			BOOL Name = TRUE;
			if ( m_UserVars.m_RepExactMatch ) {
				if ( !Name ) {
					_snprintf( BuildBuff1, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
				} else {
					_snprintf( BuildBuff1, Count * 20 + 1024, (const char *)strPrintTitle, (const char *)pWS[i].pCGSeg->GetTitle() );
					Name=FALSE;
				}			
			}
			if ( m_UserVars.m_RepJuxtaposition ) {
				if ( !Name ) {
					_snprintf( BuildBuff2, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
				} else {
					_snprintf( BuildBuff2, Count * 20 + 1024, (const char *)strPrintTitle, (const char *)pWS[i].pCGSeg->GetTitle() );
					Name=FALSE;
				}			
			}
			if ( m_UserVars.m_RepAlignedGaps ) {
				if ( !Name ) {
					_snprintf( BuildBuff3, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
				} else {
					_snprintf( BuildBuff3, Count * 20 + 1024, (const char *)strPrintTitle, (const char *)pWS[i].pCGSeg->GetTitle() );
					Name=FALSE;
				}			
			}
		} else if ( m_UserVars.m_RepOutMatrix == 0 ) {
			_snprintf( BuildBuff1, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
			_snprintf( BuildBuff2, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
			_snprintf( BuildBuff3, Count * 20 + 1024, "%s", (const char *)strPrintSpace );
		}

		

		for ( j = 0; j < Count; ++j ) {
			GInner = (pWS[j]).pText;
			ScoreA = 0;
			ScoreS = 0;
			ScoreG = 0;
			Total = 0;
			
			// This Section for Absolute Similarity
			if ( j != i ) {
				// Here we have Absoulte Calc's
				Length = pWS[j].pCGSeg->GetTextLength();
				while (Length--) {

					char cInner = toupper(GInner[Length].CharGene);
					char cOuter = toupper(GOut[Length].CharGene);

					if ( (cInner >= 'A' && cInner <= 'Z') || (cOuter >= 'A' && cOuter <= 'Z') ) {
						Total++;
						if ( cInner == cOuter ) {
							ScoreA++;
						}
						if ( (cInner >= 'A' && cInner <= 'Z') && (cOuter >= 'A' && cOuter <= 'Z') ) {
							if ( ScoreCurrentArray(cInner, cOuter) < CurrentZeroDistance ) {
								ScoreS++;
							}
						}
						if ( (!(cInner >= 'A' && cInner <= 'Z')) || (!(cOuter >= 'A' && cOuter <= 'Z')) ) {
							ScoreG++;
						}
					}

				}
			} else {
				// Here we are the same, have numbers
				Length = pWS[j].pCGSeg->GetTextLength();
				while (Length--) {
					char cInner = toupper(GInner[Length].CharGene);
					if ( cInner >= 'A' && cInner <= 'Z') {
						ScoreA++;
					}
				}
				Total = ScoreA;

			}
		


			if ( m_UserVars.m_RepOutMatrix == 0 ) {
				if ( m_UserVars.m_RepAbsoluteVal && m_UserVars.m_RepPercentVal ) {
					if ( j > i ) {
						ScoreA = (ScoreA * 100L) / (Total);
						ScoreS = (ScoreS * 100L) / (Total);
						ScoreG = (ScoreG * 100L) / (Total);

						if ( m_UserVars.m_RepExactMatch ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreA );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreS );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreG );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff3, LeadBuff );
						}
					} else {
						if ( m_UserVars.m_RepExactMatch ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreA );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreS );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreG );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff3, LeadBuff );
						}
					}
				} else if ( m_UserVars.m_RepPercentVal ) {
					if ( j > i ) {

						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintSpace );
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						if ( m_UserVars.m_RepExactMatch ) {
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							strcat ( BuildBuff3, LeadBuff );
						}
					} else {
						ScoreA = (ScoreA * 100L) / (Total);
						ScoreS = (ScoreS * 100L) / (Total);
						ScoreG = (ScoreG * 100L) / (Total);

						if ( m_UserVars.m_RepExactMatch ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreA );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreS );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintPer, ScoreG );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff3, LeadBuff );
						}
					}
				} else {
					if ( j > i ) {

						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintSpace );
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						if ( m_UserVars.m_RepExactMatch ) {
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							strcat ( BuildBuff3, LeadBuff );
						}
					} else {

						if ( m_UserVars.m_RepExactMatch ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreA );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff1, LeadBuff );
						}
						if ( m_UserVars.m_RepJuxtaposition ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreS );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff2, LeadBuff );
						}
						if ( m_UserVars.m_RepAlignedGaps ) {
							_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintVal, ScoreG );
							LeadBuff[sizeof(LeadBuff)-1] = 0;
							strcat ( BuildBuff3, LeadBuff );
						}
					}
				}

			} else {
				if ( m_UserVars.m_RepAbsoluteVal ) {
					if ( m_UserVars.m_RepExactMatch ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal, 
							(pWS[i]).pCGSeg->GetTitle(), (pWS[j]).pCGSeg->GetTitle(), 
							"Exact", ScoreA 
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
					if ( m_UserVars.m_RepJuxtaposition ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal, 
							(pWS[i]).pCGSeg->GetTitle(), 
							(pWS[j]).pCGSeg->GetTitle(), 
							"Score", ScoreS 
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
					if ( m_UserVars.m_RepAlignedGaps ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal,
							(pWS[i]).pCGSeg->GetTitle(), 
							(pWS[j]).pCGSeg->GetTitle(), 
							"Gap", ScoreG 
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
				}
				if ( m_UserVars.m_RepPercentVal ) {

					ScoreA = (ScoreA * 100L) / (Total);
					ScoreS = (ScoreS * 100L) / (Total);
					ScoreG = (ScoreG * 100L) / (Total);

					if ( m_UserVars.m_RepExactMatch ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal, 
							(pWS[i]).pCGSeg->GetTitle(), 
							(pWS[j]).pCGSeg->GetTitle(), 
							"%Exact", ScoreA
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
					if ( m_UserVars.m_RepJuxtaposition ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal, 
							(pWS[i]).pCGSeg->GetTitle(), 
							(pWS[j]).pCGSeg->GetTitle(), 
							"%Score", ScoreS
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
					if ( m_UserVars.m_RepAlignedGaps ) {
						_snprintf( LeadBuff, sizeof(LeadBuff), (const char *)strPrintRowVal, 
							(pWS[i]).pCGSeg->GetTitle(), 
							(pWS[j]).pCGSeg->GetTitle(), 
							"%Gap", ScoreG
						);
						LeadBuff[sizeof(LeadBuff)-1] = 0;
						wFile.WriteString( LeadBuff );
					}
				}
			}
		}
		if ( m_UserVars.m_RepOutMatrix == 0 ) {
			if ( m_UserVars.m_RepExactMatch ) {
				wFile.WriteString( BuildBuff1 );
				wFile.WriteString( "\n" );
			}
			if ( m_UserVars.m_RepJuxtaposition ) {
				wFile.WriteString( BuildBuff2 );
				wFile.WriteString( "\n" );
			}
			if ( m_UserVars.m_RepAlignedGaps ) {
				wFile.WriteString( BuildBuff3 );
				wFile.WriteString( "\n" );
			}
			wFile.WriteString( "\n" );
		}
	}


	wFile.Close();
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	// End routine Checks.
	GlobalUnlock ( hBuildBuff1 );
	GlobalFree ( hBuildBuff1 );
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

