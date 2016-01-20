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



CString BuildRebaseSrch( const CString& iSearch )
{
	CString oSearch;
	int sLen = iSearch.GetLength();

	for ( int j=0; j < sLen; ++j ) {
		char tChar = toupper(iSearch[j]);
		switch( tChar ) {
		case 'A':
		case 'G':
		case 'C':
		case 'T':
		case 'U':
		case 'Y':
		case 'R':
		case 'W':
		case 'S':
		case 'K':
		case 'M':
		case 'B':
		case 'D':
		case 'H':
		case 'V':
		case 'N':
		case 'X':
			oSearch += tChar;
			break;
		}
	}
	return oSearch;
}

void 
CGenedocDoc::PlotUniqueFrags()
{

	ShadeSegStc *pSegArr = NULL;

	if ( !m_UserVars.m_ProSite ) return;

	BeginWaitCursor();

	typedef struct {
		DWORD dwCutLoc;
		CGeneSegment *pCGSeg;
		stcSearch *pSearch;
	} SRep;

	CPtrArray RepArr;

	int counter = 0, i;

	int pSegCount = 0;

	DWORD SeqLength;
	pSegArr = new ShadeSegStc[pGSFiller->SegDataList.GetCount()];

		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			SeqLength = tCGSeg->GetTextLength();
			pSegArr[pSegCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			pSegArr[pSegCount].pCGSeg = tCGSeg;
			pSegCount++;
		}
	}

	POSITION sPos = m_UserVars.listSearch.GetHeadPosition();
	while ( sPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(sPos);
		for ( i=0; i < pSegCount; ++i ) {
			SearchRebaseReport( pSearch, &pSegArr[i], RepArr, SeqLength );
		}
	}


	delete pSegArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
		}
	}

	// Cute Sites
	CDWordArray cArr;
	CDWordArray oArr;

	CString strOut;
	int CutCount;
	DWORD dwLastCutLoc;
	DWORD dwFrag;

	CGeneSegment *cpCGSeg = NULL;
	CGeneSegment *spCGSeg = NULL;
	stcSearch *cpSearch = NULL;
	stcSearch *spSearch = NULL;

	int iArr = RepArr.GetSize();

	for ( i=0; i < iArr; ++i ) {
		//
		cpSearch = ((SRep*)RepArr[i])->pSearch;
		if ( cpSearch != spSearch ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] > cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				DWORD twplus, twminus;
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					twplus = cArr[ti] + (cArr[ti] / (100/20));
					twminus = cArr[ti] - (cArr[ti] / (100/20));
					if ( ti == 0 ) {
						if ( cArr[1] > twplus ) {
							oArr.Add( cArr[ti] );
						}
					} else if ( ti == cArr.GetSize() - 1) {
						if ( cArr[cArr.GetSize() - 2] < twminus ) {
							oArr.Add( cArr[ti] );
						}
					} else {
						if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
							oArr.Add( cArr[ti] );
						}
					}
				}
				// Out Code
			}
			spCGSeg = NULL;

			spSearch = cpSearch;

		}

		cpCGSeg = ((SRep*)RepArr[i])->pCGSeg;
		if ( cpCGSeg != spCGSeg ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] > cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				DWORD twplus, twminus;
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					twplus = cArr[ti] + (cArr[ti] / (100/20));
					twminus = cArr[ti] - (cArr[ti] / (100/20));
					if ( ti == 0 ) {
						if ( cArr[1] > twplus ) {
							oArr.Add( cArr[ti] );
						}
					} else if ( ti == cArr.GetSize() - 1) {
						if ( cArr[cArr.GetSize() - 2] < twminus ) {
							oArr.Add( cArr[ti] );
						}
					} else {
						if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
							oArr.Add( cArr[ti] );
						}
					}
				}
				// Out Code
			}
			spCGSeg = cpCGSeg;
			CutCount = 0;
			dwLastCutLoc = 0;
			cArr.RemoveAll();
		}
		if ( CutCount == 0 ) {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		} else {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		}
		CutCount++;
	}
	if ( spCGSeg != NULL ) {
		// Out Code
		dwFrag = spCGSeg->GetLastResidue();
		dwFrag = dwFrag	- dwLastCutLoc;
		cArr.Add( dwFrag );
		strOut.Empty();
		for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
			for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
				if ( cArr[tj] > cArr[tj+1] ) {
					DWORD t = cArr[tj];
					cArr[tj] = cArr[tj+1];
					cArr[tj+1] = t;
				}
			}
		}
		DWORD twplus, twminus;
		for (int ti=0; ti < cArr.GetSize(); ++ti ) {
			twplus = cArr[ti] + (cArr[ti] / (100/20));
			twminus = cArr[ti] - (cArr[ti] / (100/20));
			if ( ti == 0 ) {
				if ( cArr[1] > twplus ) {
					oArr.Add( cArr[ti] );
				}
			} else if ( ti == cArr.GetSize() - 1) {
				if ( cArr[cArr.GetSize() - 2] < twminus ) {
					oArr.Add( cArr[ti] );
				}
			} else {
				if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
					oArr.Add( cArr[ti] );
				}
			}
		}
		// Out Code
	}

	iArr = RepArr.GetSize();
	for ( i=0; i < iArr; ++i ) {
		delete (SRep*)RepArr[i];
	}

	// First loop writes comments

	// Count Unique Frags ...
	int ScoreCount = oArr.GetSize();

	DStatObject.DeleteContents();
	DStatObject.m_ScoreCount1 = ScoreCount;
	DStatObject.m_ScoreArray1 = new double[ScoreCount];

	DStatObject.m_RoundingFactor = 10.0;
	DStatObject.m_TSide = 2;

	DStatObject.m_NameSet1 = "";
	DStatObject.m_NameSet2 = "";

	DStatObject.m_XAxisTitle = "% Unique Fragments";
	DStatObject.m_xXAxTPct = .45;

	for ( i = 0; i < ScoreCount; ++i ) {
		DStatObject.m_ScoreArray1[i] = oArr[i];
	}

	DStatObject.MyDocDStat();

	EndWaitCursor();
}

		typedef struct {
			CDisplayVars *pDV;
			int GroupCount;
			CPtrList listFrag;
		} stcGArr;


BOOL 
CGenedocDoc::RebaseReport(CString& PathName)
{

	ShadeSegStc *pSegArr = NULL;

	if ( !m_UserVars.m_ProSite ) {
		AfxMessageBox("Need Search/ReBase syntax motifs for this report!");
		return 0;
	}

	CSrchRepDlg tDlg;
	if ( tDlg.DoModal() != IDOK ) return 0;
	if ( !(tDlg.m_CutSites 
		|| tDlg.m_SortedFrag 
		|| tDlg.m_UniqFrag 
		|| tDlg.m_GroupFrag 
		|| tDlg.m_SortedCut )
	) return 0;

	BeginWaitCursor();

TRY {

	typedef struct {
		DWORD dwCutLoc;
		CGeneSegment *pCGSeg;
		stcSearch *pSearch;
	} SRep;

	CPtrArray RepArr;

	int counter = 0, i;

	int pSegCount = 0;

	DWORD SeqLength;
	pSegArr = new ShadeSegStc[pGSFiller->SegDataList.GetCount()];

		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			SeqLength = tCGSeg->GetTextLength();
			pSegArr[pSegCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			pSegArr[pSegCount].pCGSeg = tCGSeg;
			pSegCount++;
		}
	}

	POSITION sPos = m_UserVars.listSearch.GetHeadPosition();
	while ( sPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(sPos);
		for ( i=0; i < pSegCount; ++i ) {
			SearchRebaseReport( pSearch, &pSegArr[i], RepArr, SeqLength );
		}
	}


	delete [] pSegArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
		}
	}


	// We've got our Rep Array ..
	CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	char cbuff[128];
	char obuff[1024];


//		sprintf ( outbuf, "\n%s  %s\n", (const char *)pSearch->strName, (const char *)pSearch->strSearch );
//		oFile.WriteString(outbuf);

	// Cute Sites
	CDWordArray cArr;
	CString strOut;
	int CutCount;
	DWORD dwLastCutLoc;
	DWORD dwFrag;

	CGeneSegment *cpCGSeg = NULL;
	CGeneSegment *spCGSeg = NULL;
	stcSearch *cpSearch = NULL;
	stcSearch *spSearch = NULL;

	int iArr = RepArr.GetSize();

	if ( tDlg.m_CutSites ) {
	for ( i=0; i < iArr; ++i ) {
		//
		cpSearch = ((SRep*)RepArr[i])->pSearch;
		if ( cpSearch != spSearch ) {
			if ( spCGSeg != NULL ) {
				_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
					(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
				oFile.WriteString( obuff );
			}
			spCGSeg = NULL;

			spSearch = cpSearch;

			_snprintf( obuff, 1023, "\n\n%s %s\n", 
				(const char *)spSearch->strName, 
				(const char *)spSearch->strSearch
				);
			oFile.WriteString( obuff );
			oFile.WriteString( "------------------- CUT SITES -------------------------------------\n" );
		}

		cpCGSeg = ((SRep*)RepArr[i])->pCGSeg;
		if ( cpCGSeg != spCGSeg ) {
			if ( spCGSeg != NULL ) {
				_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
					(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
				oFile.WriteString( obuff );
			}
			spCGSeg = cpCGSeg;
			strOut.Empty();
		}
		_ultoa( ((SRep*)RepArr[i])->dwCutLoc, cbuff, 10 );
		strOut += CString(cbuff) + " ";
	}
	if ( spCGSeg != NULL ) {
		_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
			(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
		oFile.WriteString( obuff );
	}
	}


	if ( tDlg.m_SortedFrag ) {
	// Sorted Fragment lengths ..
	cpCGSeg = NULL;
	spCGSeg = NULL;
	cpSearch = NULL;
	spSearch = NULL;

	iArr = RepArr.GetSize();
	for ( i=0; i < iArr; ++i ) {
		//
		cpSearch = ((SRep*)RepArr[i])->pSearch;
		if ( cpSearch != spSearch ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] < cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					_ultoa( cArr[ti], cbuff, 10 );
					strOut += CString(cbuff) + " ";
				}
				_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
					(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
				oFile.WriteString( obuff );
				// Out Code
			}
			spCGSeg = NULL;

			spSearch = cpSearch;

			_snprintf( obuff, 1023, "\n\n%s %s\n", 
				(const char *)spSearch->strName, 
				(const char *)spSearch->strSearch
				);
			oFile.WriteString( obuff );
			oFile.WriteString( "---------------- SORTED FRAGMENT LENGTHS --------------------------\n" );
		}

		cpCGSeg = ((SRep*)RepArr[i])->pCGSeg;
		if ( cpCGSeg != spCGSeg ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] < cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					_ultoa( cArr[ti], cbuff, 10 );
					strOut += CString(cbuff) + " ";
				}

				_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
					(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
				oFile.WriteString( obuff );
				// Out Code
			}
			spCGSeg = cpCGSeg;
			cArr.RemoveAll();
			CutCount = 0;
			dwLastCutLoc = 0;
		}
		if ( CutCount == 0 ) {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		} else {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		}
		CutCount++;
	}
	if ( spCGSeg != NULL ) {
		// Out Code
		dwFrag = spCGSeg->GetLastResidue();
		dwFrag = dwFrag	- dwLastCutLoc;
		cArr.Add( dwFrag );
		strOut.Empty();
		for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
			for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
				if ( cArr[tj] < cArr[tj+1] ) {
					DWORD t = cArr[tj];
					cArr[tj] = cArr[tj+1];
					cArr[tj+1] = t;
				}
			}
		}
		for (int ti=0; ti < cArr.GetSize(); ++ti ) {
			_ultoa( cArr[ti], cbuff, 10 );
			strOut += CString(cbuff) + " ";
		}

		_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
			(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
		oFile.WriteString( obuff );
		// Out Code
	}
	}

	if ( tDlg.m_UniqFrag ) {
	// Unique Fragment lengths ..
	cpCGSeg = NULL;
	spCGSeg = NULL;
	cpSearch = NULL;
	spSearch = NULL;

	iArr = RepArr.GetSize();
	for ( i=0; i < iArr; ++i ) {
		//
		cpSearch = ((SRep*)RepArr[i])->pSearch;
		if ( cpSearch != spSearch ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] > cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				DWORD twplus, twminus;
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					twplus = cArr[ti] + (cArr[ti] / (100/tDlg.m_UniqFragPer));
					twminus = cArr[ti] - (cArr[ti] / (100/tDlg.m_UniqFragPer));
					if ( ti == 0 ) {
						if ( cArr[1] > twplus ) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					} else if ( ti == cArr.GetSize() - 1) {
						if ( cArr[cArr.GetSize() - 2] < twminus ) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					} else {
						if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					}
				}
				if ( !strOut.IsEmpty() ) {
					_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
						(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
					oFile.WriteString( obuff );
				}
				// Out Code
			}
			spCGSeg = NULL;

			spSearch = cpSearch;

			_snprintf( obuff, 1023, "\n\n%s %s\n", 
				(const char *)spSearch->strName, 
				(const char *)spSearch->strSearch
				);
			oFile.WriteString( obuff );
			oFile.WriteString( "---------------- UNIQUE FRAGMENT LENGTHS --------------------------\n" );
		}

		cpCGSeg = ((SRep*)RepArr[i])->pCGSeg;
		if ( cpCGSeg != spCGSeg ) {
			if ( spCGSeg != NULL ) {
				// Out Code
				dwFrag = spCGSeg->GetLastResidue();
				dwFrag = dwFrag	- dwLastCutLoc;
				cArr.Add( dwFrag );
				strOut.Empty();
				for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
					for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
						if ( cArr[tj] > cArr[tj+1] ) {
							DWORD t = cArr[tj];
							cArr[tj] = cArr[tj+1];
							cArr[tj+1] = t;
						}
					}
				}
				DWORD twplus, twminus;
				for (int ti=0; ti < cArr.GetSize(); ++ti ) {
					twplus = cArr[ti] + (cArr[ti] / (100/tDlg.m_UniqFragPer));
					twminus = cArr[ti] - (cArr[ti] / (100/tDlg.m_UniqFragPer));
					if ( ti == 0 ) {
						if ( cArr[1] > twplus ) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					} else if ( ti == cArr.GetSize() - 1) {
						if ( cArr[cArr.GetSize() - 2] < twminus ) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					} else {
						if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
							_ultoa( cArr[ti], cbuff, 10 );
							strOut += CString(cbuff) + " ";
						}
					}
				}
				if ( !strOut.IsEmpty() ) {
					_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
						(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
					oFile.WriteString( obuff );
				}
				// Out Code
			}
			spCGSeg = cpCGSeg;
			CutCount = 0;
			dwLastCutLoc = 0;
			cArr.RemoveAll();
		}
		if ( CutCount == 0 ) {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		} else {
			cArr.Add( ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc );
			dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
		}
		CutCount++;
	}
	if ( spCGSeg != NULL ) {
		// Out Code
		dwFrag = spCGSeg->GetLastResidue();
		dwFrag = dwFrag	- dwLastCutLoc;
		cArr.Add( dwFrag );
		strOut.Empty();
		for ( int ti=0; ti < cArr.GetSize() - 1; ++ti ) {
			for ( int tj=0; tj < cArr.GetSize()-1; ++tj ) {
				if ( cArr[tj] > cArr[tj+1] ) {
					DWORD t = cArr[tj];
					cArr[tj] = cArr[tj+1];
					cArr[tj+1] = t;
				}
			}
		}
		DWORD twplus, twminus;
		for (int ti=0; ti < cArr.GetSize(); ++ti ) {
			twplus = cArr[ti] + (cArr[ti] / (100/tDlg.m_UniqFragPer));
			twminus = cArr[ti] - (cArr[ti] / (100/tDlg.m_UniqFragPer));
			if ( ti == 0 ) {
				if ( cArr[1] > twplus ) {
					_ultoa( cArr[ti], cbuff, 10 );
					strOut += CString(cbuff) + " ";
				}
			} else if ( ti == cArr.GetSize() - 1) {
				if ( cArr[cArr.GetSize() - 2] < twminus ) {
					_ultoa( cArr[ti], cbuff, 10 );
					strOut += CString(cbuff) + " ";
				}
			} else {
				if ( cArr[ti-1] < twminus && cArr[ti+1] > twplus) {
					_ultoa( cArr[ti], cbuff, 10 );
					strOut += CString(cbuff) + " ";
				}
			}
		}
		if ( !strOut.IsEmpty() ) {
			_snprintf( obuff, 1023, "%-10s[%ld] %s\n", 
				(const char *)spCGSeg->GetTitle(), spCGSeg->GetLastResidue(), (const char *)strOut );
			oFile.WriteString( obuff );
		}
		// Out Code
	}
	}

//////////////////////////////////////


	if ( tDlg.m_GroupFrag ) {
	// in groups Unique 
	int gcount = m_UserVars.m_DisplayVars.GetCount();
	if ( gcount ) {

		typedef struct {
			DWORD Min;
			DWORD Max;
			int Count;
		} stcFragBin;

		stcGArr *pGArr = new stcGArr[gcount + 1];

		pGArr[0].GroupCount = 0;
		pGArr[0].pDV = &m_UserVars.m_Vars;

		int GrpCnt = 1;
		POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
		while ( tPos != NULL ) {
			CDisplayVars* pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
			pGArr[GrpCnt].GroupCount = pDV->GetGroupList()->GetCount();
			pGArr[GrpCnt].pDV = pDV;
			GrpCnt++;
		}

	
		cpCGSeg = NULL;
		spCGSeg = NULL;
		cpSearch = NULL;
		spSearch = NULL;
		int WriteTitle;


		iArr = RepArr.GetSize();
		for ( i=0; i < iArr; ++i ) {
			//
			cpSearch = ((SRep*)RepArr[i])->pSearch;
			if ( cpSearch != spSearch ) {
				if ( spCGSeg != NULL ) {
					dwFrag = spCGSeg->GetLastResidue();
					dwFrag = dwFrag	- dwLastCutLoc;
					// Add new fragment
					int gnum = spCGSeg->m_DisplayGroup;
					POSITION fPos = pGArr[gnum].listFrag.GetHeadPosition();
					stcFragBin *pstcFB = NULL;
					int added = 0;
					while ( fPos != NULL ) {
						pstcFB = (stcFragBin *)pGArr[gnum].listFrag.GetNext(fPos);
						DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_SimPer));
						DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_SimPer));
						if ( dwFrag >= dwMin && dwFrag <= dwMax ) {
							pstcFB->Count++;
							if ( dwFrag > pstcFB->Max ) pstcFB->Max = dwFrag;
							if ( dwFrag < pstcFB->Min ) pstcFB->Min = dwFrag;
							added = 1;
							break;
						}
					}
					if ( !added ) {
						pstcFB = new stcFragBin;
						pstcFB->Min = dwFrag;
						pstcFB->Max = dwFrag;
						pstcFB->Count = 1;
						pGArr[gnum].listFrag.AddTail(pstcFB);
					}
					// Add new fragment
					// Do Output ..
					for ( int g = 1; g <= gcount; ++g ) {
						POSITION fPos = pGArr[g].listFrag.GetHeadPosition();
						while ( fPos != NULL ) {
							stcFragBin *pstcFB = (stcFragBin *)pGArr[g].listFrag.GetNext(fPos);
							DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_UniqPer));
							DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_UniqPer));
							if ( pstcFB->Count == pGArr[g].GroupCount ) {
								int isgood1 = 1;
								for ( int gt = 0; gt <= gcount; ++gt ) {
									int isgood2 = 1;
									POSITION ftPos = pGArr[gt].listFrag.GetHeadPosition();
									while ( ftPos != NULL ) {
										stcFragBin *pstcFBT = (stcFragBin *)pGArr[gt].listFrag.GetNext(ftPos);
										if ( pstcFBT != pstcFB ) {
											if ( pstcFBT->Max >= dwMin && pstcFBT->Max <= dwMax) {
												isgood2 = 0;
												break;
											}
											if ( pstcFBT->Min >= dwMin && pstcFBT->Min <= dwMax) {
												isgood2 = 0;
												break;
											}
										}
									}
									if ( !isgood2 ) {
										// Flag bad found .. quit this length ..
										isgood1 = 0;
										break;
									}
								}
								// test isgood1 .. nothing bad found?
								if ( isgood1 ) {
									if ( WriteTitle ) {
										_snprintf( obuff, 1023, "\n\n%s %s\n", 
											(const char *)spSearch->strName, 
											(const char *)spSearch->strSearch
											);
										oFile.WriteString( obuff );
										oFile.WriteString( "---------------- GROUP SPECIFIC FRAGMENT LENGTHS ----------------\n" );
										WriteTitle = 0;
									}

									// Search Name
									_snprintf( obuff, 1023, "%s: %ld %ld\n", 
										(const char *)pGArr[g].pDV->GetGroupName(),
										pstcFB->Min,
										pstcFB->Max
									);
									oFile.WriteString( obuff );
								}
							}
						}
					}
					// Clear Old Output ...
					for (int g = 0; g <= gcount; ++g ) {
						POSITION fPos = pGArr[g].listFrag.GetHeadPosition();
						while ( fPos != NULL ) {
							delete (stcFragBin *)pGArr[g].listFrag.GetNext(fPos);
						}
						// CPtrLIst
						pGArr[g].listFrag.RemoveAll();
					}

				}
				spCGSeg = NULL;

				spSearch = cpSearch;

				WriteTitle = 1;

			}

			cpCGSeg = ((SRep*)RepArr[i])->pCGSeg;

			if ( cpCGSeg != spCGSeg ) {
				if ( spCGSeg != NULL ) {
					// Out Code
					dwFrag = spCGSeg->GetLastResidue();
					dwFrag = dwFrag	- dwLastCutLoc;
					// Add new fragment
					int gnum = spCGSeg->m_DisplayGroup;
					POSITION fPos = pGArr[gnum].listFrag.GetHeadPosition();
					stcFragBin *pstcFB = NULL;
					int added = 0;
					while ( fPos != NULL ) {
						pstcFB = (stcFragBin *)pGArr[gnum].listFrag.GetNext(fPos);
						DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_SimPer));
						DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_SimPer));
						if ( dwFrag >= dwMin && dwFrag <= dwMax ) {
							pstcFB->Count++;
							if ( dwFrag > pstcFB->Max ) pstcFB->Max = dwFrag;
							if ( dwFrag < pstcFB->Min ) pstcFB->Min = dwFrag;
							added = 1;
							break;
						}
					}
					if ( !added ) {
						pstcFB = new stcFragBin;
						pstcFB->Min = dwFrag;
						pstcFB->Max = dwFrag;
						pstcFB->Count = 1;
						pGArr[gnum].listFrag.AddTail(pstcFB);
					}
					// Add new fragment

				}
				spCGSeg = cpCGSeg;
				dwLastCutLoc = 0;
				CutCount = 0;
			}

			if ( CutCount == 0 ) {
				dwFrag = ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc;
				dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;
			} else {
				dwFrag = ((SRep*)RepArr[i])->dwCutLoc - dwLastCutLoc;
				dwLastCutLoc = ((SRep*)RepArr[i])->dwCutLoc;

			}
			CutCount++;
			// Add new fragment
			int gnum = spCGSeg->m_DisplayGroup;
			POSITION fPos = pGArr[gnum].listFrag.GetHeadPosition();
			stcFragBin *pstcFB = NULL;
			int added = 0;
			while ( fPos != NULL ) {
				pstcFB = (stcFragBin *)pGArr[gnum].listFrag.GetNext(fPos);
				DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_SimPer));
				DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_SimPer));
				if ( dwFrag >= dwMin && dwFrag <= dwMax ) {
					pstcFB->Count++;
					if ( dwFrag > pstcFB->Max ) pstcFB->Max = dwFrag;
					if ( dwFrag < pstcFB->Min ) pstcFB->Min = dwFrag;
					added = 1;
					break;
				}
			}
			if ( !added ) {
				pstcFB = new stcFragBin;
				pstcFB->Min = dwFrag;
				pstcFB->Max = dwFrag;
				pstcFB->Count = 1;
				pGArr[gnum].listFrag.AddTail(pstcFB);
			}
			// Add new fragment


		}
		if ( spCGSeg != NULL ) {
			dwFrag = spCGSeg->GetLastResidue();
			dwFrag = dwFrag	- dwLastCutLoc;
			// Add new fragment
			int gnum = spCGSeg->m_DisplayGroup;
			POSITION fPos = pGArr[gnum].listFrag.GetHeadPosition();
			stcFragBin *pstcFB = NULL;
			int added = 0;
			while ( fPos != NULL ) {
				pstcFB = (stcFragBin *)pGArr[gnum].listFrag.GetNext(fPos);
				DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_SimPer));
				DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_SimPer));
				if ( dwFrag >= dwMin && dwFrag <= dwMax ) {
					pstcFB->Count++;
					if ( dwFrag > pstcFB->Max ) pstcFB->Max = dwFrag;
					if ( dwFrag < pstcFB->Min ) pstcFB->Min = dwFrag;
					added = 1;
					break;
				}
			}
			if ( !added ) {
				pstcFB = new stcFragBin;
				pstcFB->Min = dwFrag;
				pstcFB->Max = dwFrag;
				pstcFB->Count = 1;
				pGArr[gnum].listFrag.AddTail(pstcFB);
			}
			// Add new fragment
			// Out Code
			// Do Output ..
			for ( int g = 1; g <= gcount; ++g ) {
				POSITION fPos = pGArr[g].listFrag.GetHeadPosition();
				while ( fPos != NULL ) {
					stcFragBin *pstcFB = (stcFragBin *)pGArr[g].listFrag.GetNext(fPos);
					DWORD dwMin = pstcFB->Min - (pstcFB->Min / (100/tDlg.m_UniqPer));
					DWORD dwMax = pstcFB->Max + (pstcFB->Max / (100/tDlg.m_UniqPer));
					if ( pstcFB->Count == pGArr[g].GroupCount ) {
						int isgood1 = 1;
						for ( int gt = 0; gt <= gcount; ++gt ) {
							int isgood2 = 1;
							POSITION ftPos = pGArr[gt].listFrag.GetHeadPosition();
							while ( ftPos != NULL ) {
								stcFragBin *pstcFBT = (stcFragBin *)pGArr[gt].listFrag.GetNext(ftPos);
								if ( pstcFBT != pstcFB ) {
									if ( pstcFBT->Max >= dwMin && pstcFBT->Max <= dwMax) {
										isgood2 = 0;
										break;
									}
									if ( pstcFBT->Min >= dwMin && pstcFBT->Min <= dwMax) {
										isgood2 = 0;
										break;
									}
								}
							}
							if ( !isgood2 ) {
								// Flag bad found .. quit this length ..
								isgood1 = 0;
								break;
							}
						}
						// test isgood1 .. nothing bad found?
						if ( isgood1 ) {
							if ( WriteTitle ) {
								_snprintf( obuff, 1023, "\n\n%s %s\n", 
									(const char *)spSearch->strName, 
									(const char *)spSearch->strSearch
									);
								oFile.WriteString( obuff );
								oFile.WriteString( "---------------- GROUP SPECIFIC FRAGMENT LENGTHS ----------------\n" );
								WriteTitle = 0;
							}

							// Search Name
							_snprintf( obuff, 1023, "%s: %ld %ld\n", 
								(const char *)pGArr[g].pDV->GetGroupName(),
								pstcFB->Min,
								pstcFB->Max
							);
							oFile.WriteString( obuff );
						}
					}
				}
			}
			// Clear Old Output ...
			for (int g = 0; g <= gcount; ++g ) {
				POSITION fPos = pGArr[g].listFrag.GetHeadPosition();
				while ( fPos != NULL ) {
					delete (stcFragBin *)pGArr[g].listFrag.GetNext(fPos);
				}
				// CPtrLIst
				pGArr[g].listFrag.RemoveAll();
			}
		}
		delete [] pGArr;
	}
	}

	

////////////////////////////////
	if ( tDlg.m_SortedCut ) {
	//
	for ( int ti=0; ti < RepArr.GetSize() - 1; ++ti ) {
		for ( int tj=0; tj < RepArr.GetSize()-1; ++tj ) {
			if ( ((SRep*)RepArr[tj])->dwCutLoc > ((SRep*)RepArr[tj+1])->dwCutLoc ) {
				SRep* t = (SRep*)RepArr[tj];
				RepArr[tj] = RepArr[tj+1];
				RepArr[tj+1] = t;
			}
		}
	}

	oFile.WriteString( "\n\n---------------- SORTED CUT SITES ---------------------------------\n" );
	iArr = RepArr.GetSize();
	for ( i=0; i < iArr; ++i ) {
		_snprintf( obuff, 1023, "%5ld %-10s %s[%ld]\n", 
			((SRep*)RepArr[i])->dwCutLoc, 
			(const char *)((SRep*)RepArr[i])->pSearch->strName, 
			(const char *)((SRep*)RepArr[i])->pCGSeg->GetTitle() , ((SRep*)RepArr[i])->pCGSeg->GetLastResidue() 
		);
		oFile.WriteString( obuff );
	}
	oFile.WriteString( "---------------- SORTED CUT SITES ---------------------------------\n" );
	}

	//
	iArr = RepArr.GetSize();
	for ( i=0; i < iArr; ++i ) {
		delete (SRep*)RepArr[i];
	}
	RepArr.RemoveAll();

	oFile.Close();

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	if ( pSegArr != NULL ) delete pSegArr;
	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	if ( pSegArr != NULL ) delete pSegArr;
	return 0;
}
END_CATCH

	EndWaitCursor();

	return 1;
}


void 
CGenedocDoc::SearchRebaseReport( 
	stcSearch *pSearch, 
	ShadeSegStc *pSegArr, 
	CPtrArray& RepArr, 
	DWORD OuterCount )
{
	typedef struct {
		DWORD dwCutLoc;
		CGeneSegment *pCGSeg;
		stcSearch *pSearch;
	} SRep;

	int coff;
	coff = pSearch->strSearch.Find( '\'');
	if ( coff == -1 ) coff = 0;
	if ( pSearch->strSearch.Find( '_') < coff ) {
		if ( pSearch->strSearch.Find( '_') != -1 ) if ( coff ) coff--;
	}

	CString strSearch = BuildRebaseSrch( pSearch->strSearch );
	int match = 0;

	// end for ..
	int sLen = strSearch.GetLength();
	if ( sLen == 0 ) return;
	int mCount = 0;
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;
		char tChar = toupper(pSegArr->pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;
		// for report.
		DWORD sCount = 0;
		for ( int j = 0; j < sLen; ++j ) {
			char tChar;
			do { 
				if ( tCount + sCount > OuterCount ) break;
				tChar = toupper(pSegArr->pGeneStor[tCount + sCount].CharGene);
				sCount++;
			} while ( !(tChar >= 'A' && tChar <= 'Z' ) );
			if ( tCount + sCount > OuterCount ) {
				match = 0;
				break;
			}
			char sChar = strSearch[j];
			switch( sChar ) {
			case 'A': match = (tChar == 'A'); break;
			case 'G': match = (tChar == 'G'); break;
			case 'C': match = (tChar == 'C'); break;
			case 'T': match = (tChar == 'T'); break;
			case 'U': match = (tChar == 'U'); break;
			case 'Y': match = (tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'R': match = (tChar == 'A' || tChar == 'G' ); break;
			case 'W': match = (tChar == 'A' || tChar == 'T' || tChar == 'U' ); break;
			case 'S': match = (tChar == 'C' || tChar == 'G' ); break;
			case 'K': match = (tChar == 'T' || tChar == 'U' || tChar == 'G' ); break;
			case 'M': match = (tChar == 'C' || tChar == 'A' ); break;
			case 'B': match = (tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'D': match = (tChar == 'A' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'H': match = (tChar == 'A' || tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'V': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' ); break;
			case 'N': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'X': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			}
			if ( !match ) break;
		}

		if ( match ) {
			DWORD cLoc = pSegArr->pGeneStor[tCount].GeneSeqNumber;
			cLoc += coff;
			SRep *pSRep = new SRep;
			pSRep->dwCutLoc = cLoc;
			pSRep->pCGSeg = pSegArr->pCGSeg;
			pSRep->pSearch = pSearch;
			RepArr.Add( pSRep );
		}
	}

	return;
}


int 
CGenedocDoc::SearchRebase( 
	stcSearch *pSearch, 
	GeneStor *pGeneStor, 
	DWORD OuterCount, 
	int Test )
{

	CString strSearch = BuildRebaseSrch( pSearch->strSearch );
	int match = 0;

	// end for ..
	int sLen = strSearch.GetLength();
	if ( sLen == 0 ) return 0;
	int mCount = 0;
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;
		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;
		// for report.
		DWORD sCount = 0;
		for ( int j = 0; j < sLen; ++j ) {
			char tChar;
			do { 
				if ( tCount + sCount > OuterCount ) break;
				tChar = toupper(pGeneStor[tCount + sCount].CharGene);
				sCount++;
			} while ( !(tChar >= 'A' && tChar <= 'Z' ) );
			if ( tCount + sCount > OuterCount ) {
				match = 0;
				break;
			}
			char sChar = strSearch[j];
			switch( sChar ) {
			case 'A': match = (tChar == 'A'); break;
			case 'G': match = (tChar == 'G'); break;
			case 'C': match = (tChar == 'C'); break;
			case 'T': match = (tChar == 'T'); break;
			case 'U': match = (tChar == 'U'); break;
			case 'Y': match = (tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'R': match = (tChar == 'A' || tChar == 'G' ); break;
			case 'W': match = (tChar == 'A' || tChar == 'T' || tChar == 'U' ); break;
			case 'S': match = (tChar == 'C' || tChar == 'G' ); break;
			case 'K': match = (tChar == 'T' || tChar == 'U' || tChar == 'G' ); break;
			case 'M': match = (tChar == 'C' || tChar == 'A' ); break;
			case 'B': match = (tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'D': match = (tChar == 'A' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'H': match = (tChar == 'A' || tChar == 'C' || tChar == 'T' || tChar == 'U' ); break;
			case 'V': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' ); break;
			case 'N': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			case 'X': match = (tChar == 'A' || tChar == 'C' || tChar == 'G' || tChar == 'T' || tChar == 'U' ); break;
			}
			if ( !match ) break;
		}

		// Test if Should do Colors.
		if ( match && !Test) {

			sCount = 0;
			for (int j = 0; j < sLen; ++j ) {
				char tChar;
				do { 
					tChar = toupper(pGeneStor[tCount + sCount].CharGene);
					sCount++;
				} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

				if ( pGeneStor[tCount + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
					pGeneStor[tCount + sCount - 1].TextColor = RGB(0,0,0);
					pGeneStor[tCount + sCount - 1].BackColor = m_UserVars.m_OverlapColor;
				} else {
					pGeneStor[tCount + sCount - 1].TextColor = pSearch->rgbText;
					pGeneStor[tCount + sCount - 1].BackColor = pSearch->rgbBack;
				}
			}
		} else if ( match && Test ) {
			return 1;
		}
	}
	return mCount;
}

int 
CGenedocDoc::ScanRebaseFile(const CString& PathName, CPtrList *listSearch)
{

	GeneStor ** pGSArr = NULL;

	CReFiltDlg	tDlg;
	if ( tDlg.DoModal() != IDOK ) {
		return 0;
	}
	BeginWaitCursor();

	int Filter = 0;
	if ( 
		tDlg.m_Minlen 
		|| tDlg.m_Maxlen 
		|| !tDlg.m_Exclude.IsEmpty()
		|| !tDlg.m_Include.IsEmpty()
		|| tDlg.m_NonAmbig
		|| tDlg.m_Palin
		|| tDlg.m_ExclDup
	) Filter = 1;


TRY {

    int counter = 0, i;

    CString search;
    CString name;
    CString back;
    CString fore;

	CString tString;

	CStdioFile rFile(PathName, CFile::modeRead );


    while( 1 )
    {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			rFile.Abort();
			AfxMessageBox(" Unexpected End Of File looking for '..'!" );
			return 0;
		}
		tString.ReleaseBuffer();

		if( tString.Find("..") != -1 ) 
             break;
    }

	while ( !listSearch->IsEmpty() ) {
		stcSearch *ps = (stcSearch *)listSearch->RemoveHead();
		delete ps;
	}

	int pSegCount = 0;

	DWORD SeqLength;
	pGSArr = new GeneStor*[pGSFiller->SegDataList.GetCount()];
	if ( pGSArr == 0 ) {
		AfxMessageBox("AutoShadeQuantify:New Fail 1");
		return 0;
	}

		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			SeqLength = tCGSeg->GetTextLength();
			pGSArr[pSegCount] = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			if ( pGSArr[pSegCount] == NULL) {
				AfxMessageBox("AutoShade:GlobalLock:Fail:1");
				delete pGSArr;
				return 0;
			}
			pSegCount++;
		}
	}

    while( 1 )
    {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			break;
		}
		tString.ReleaseBuffer();

		// Always clear this out for test.
		search.Empty();
		name.Empty();
		back.Empty();
		fore.Empty();

		if( tString.IsEmpty() ) continue;
		if( tString[0] == ' ' ) continue;
		if( tString[0] == ';' ) continue;
		
		int count = tString.GetLength();
		for ( i=0; i < count; ++i ) {
			if ( isspace(tString[i]) ) break;
			name += tString[i];
		}

		for ( ; i < count; ++i ) {
			if ( !isspace(tString[i]) ) break;
		}

		for ( ; i < count; ++i ) {
			if ( isspace(tString[i]) ) break;
		}

		for ( ; i < count; ++i ) {
			if ( !isspace(tString[i]) ) break;
		}

		for ( ; i < count; ++i ) {
			if ( isspace(tString[i]) ) break;
			search += tString[i];
		}
		// Search for possible color indicators ..
		int fs = tString.Find('[');
		int fe = tString.Find(']');
		if ( fs != -1 && fe != -1 && fe > fs + 2 ) {
			back = tString.Mid(fs+1, fe - fs - 1 );
		}

		if ( fe != -1 ) {
			tString = tString.Mid(fe);
			fs = tString.Find('[');
			fe = tString.Find(']');
			if ( fs != -1 && fe != -1 && fe > fs + 2 ) {
				fore = tString.Mid(fs+1, fe - fs - 1 );
			}
		}
			

		if( search.GetLength() != 0  ) {
			// Test Against DlgFlags.
			if ( Filter ) {
				// Check for Dups?
				if ( tDlg.m_ExclDup ) {
					POSITION dPos = listSearch->GetHeadPosition();
					int df = 0;
					while ( dPos != NULL ) {
						stcSearch *dSearch = (stcSearch *)listSearch->GetNext( dPos );
						if ( dSearch->strSearch == search ) {
							df = 1;
							break;
						}
					}
					if ( df ) continue;
				}

				CString strRe = BuildRebaseSrch( search );
				if ( tDlg.m_Minlen ) if ( strRe.GetLength() < tDlg.m_Minlen ) continue;
				if ( tDlg.m_Maxlen ) if ( strRe.GetLength() > tDlg.m_Maxlen ) continue;
				if ( !tDlg.m_Exclude.IsEmpty() ) if ( strRe.FindOneOf(tDlg.m_Exclude) != -1 ) continue;
				if ( !tDlg.m_Include.IsEmpty() ) if ( strRe.FindOneOf(tDlg.m_Include) == -1 ) continue;
				if ( tDlg.m_NonAmbig ) {
					if ( strRe.Find('Y') != -1 ) continue;
					if ( strRe.Find('R') != -1 ) continue;
					if ( strRe.Find('W') != -1 ) continue;
					if ( strRe.Find('S') != -1 ) continue;
					if ( strRe.Find('K') != -1 ) continue;
					if ( strRe.Find('M') != -1 ) continue;
					if ( strRe.Find('B') != -1 ) continue;
					if ( strRe.Find('D') != -1 ) continue;
					if ( strRe.Find('H') != -1 ) continue;
					if ( strRe.Find('V') != -1 ) continue;
					if ( strRe.Find('N') != -1 ) continue;
					if ( strRe.Find('X') != -1 ) continue;
				}
				if ( tDlg.m_Palin  ) {
					int Palin = 1;
					if ( Palin ) {
						int ie = strRe.GetLength() - 1;
						for ( i=0; i < strRe.GetLength()/2; ++i ) {
							if ( strRe[i] != strRe[ie--]  ) {
								Palin = 0;
								break;
							}
						}
					}
					if ( !Palin ) {
						Palin = 1;
						int ie = strRe.GetLength() - 1;
						for ( i=0; i < strRe.GetLength()/2; ++i ) {
							char tc = ' ';
							switch ( strRe[ie--] ) {
							case 'C':
								tc = 'G';
								break;
							case 'G':
								tc = 'C';
								break;
							case 'A':
								tc = 'T';
								break;
							case 'T':
								tc = 'A';
								break;
							case 'U':
								tc = 'A';
								break;
							}
							if ( strRe[i] != tc  ) {
								Palin = 0;
								break;
							}
						}
					}
					if ( tDlg.m_Palin && !Palin ) continue;
				}
			}


			 // Build Search Struct
			stcSearch *sSearch = new stcSearch;

			sSearch->iEnabled = 1;
			sSearch->strSearch = search;
			sSearch->strName = name;
//			sSearch->strDescrip = descrip;
			if ( !back.IsEmpty() ) {
				int red, green, blue;
				if ( sscanf( (const char *)back, "%d,%d,%d", &red, &green, &blue ) == 3 ) {
					sSearch->rgbBack = RGB(red, green, blue);
				} else {
					sSearch->rgbBack = RGB(0,0,0);
				}

				if ( sscanf( (const char *)fore, "%d,%d,%d", &red, &green, &blue ) == 3 ) {
					sSearch->rgbText = RGB(red, green, blue);
				} else {
					sSearch->rgbText = RGB(255,255,255);
				}
			} else {
				sSearch->rgbBack = RGB(0,0,0);
				sSearch->rgbText = RGB(255,255,255);
			}

			int mf = 0;
			for ( i=0; i < pSegCount; ++i ) {
				if ( tDlg.m_Occur ) {
					int f =  SearchRebase( sSearch, pGSArr[i], SeqLength, 0 );
					if ( f > mf ) mf = f;
					if ( mf > tDlg.m_Occur ) {
						mf = 0;
						break;
					}
				} else {
					if ( SearchRebase( sSearch, pGSArr[i], SeqLength, 1 ) ) break;
				}
			}

			if ( i != pSegCount && !tDlg.m_Occur ) {
				listSearch->AddTail( sSearch );
			} else if ( tDlg.m_Occur && mf ) {
				listSearch->AddTail( sSearch );
			} else {
				delete sSearch;
			}

		}
	}

	delete pGSArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
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

	if ( pGSArr != NULL ) delete pGSArr;
	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	if ( pGSArr != NULL ) delete pGSArr;
	return 0;
}
END_CATCH

	return 1;
}


int 
CGenedocDoc::ScanPrositeMotifs(const CString& PathName, CPtrList *listSearch)
{

	GeneStor ** pGSArr = NULL;

TRY {

    int counter = 0, i;

    CString motif;
    CString name;
	CString descrip;


	CString tString;

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


	while ( !listSearch->IsEmpty() ) {
		stcSearch *ps = (stcSearch *)listSearch->RemoveHead();
		delete ps;
	}

	int pSegCount = 0;

	DWORD SeqLength;
	pGSArr = new GeneStor*[pGSFiller->SegDataList.GetCount()];
	if ( pGSArr == 0 ) {
		AfxMessageBox("AutoShadeQuantify:New Fail 1");
		return 0;
	}

		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			SeqLength = tCGSeg->GetTextLength();
			pGSArr[pSegCount] = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			if ( pGSArr[pSegCount] == NULL) {
				AfxMessageBox("AutoShade:GlobalLock:Fail:1");
				delete pGSArr;
				return 0;
			}
			pSegCount++;
		}
	}

	int iMXL = 128;

	// CByteArray
	for ( i=0; i < 26; ++i ) {
		Member[i].SetSize(iMXL);
	}
	Chosen.SetSize(iMXL);
	Max.SetSize(iMXL);
	Min.SetSize(iMXL);

    while( 1 )
    {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			break;
		}
		tString.ReleaseBuffer();

		if( (tString[0]=='P') && (tString[1]=='A') )
		{
			for ( i = 5; i < tString.GetLength(); ++i ) {
				if( !isspace(tString[i]) ) motif += tString[i];
			}
		} else if( (tString[0]=='I') && (tString[1]=='D') )
		{
			for ( i = 5; i < tString.GetLength(); ++i ) {
				if( tString[i] == ';' ) break;
				name += tString[i];
			}

		} else if( (tString[0]=='D') && (tString[1]=='E') )
		{
			descrip = tString.Mid(5);
			// trim right
			char *pc = descrip.GetBuffer(descrip.GetLength());
			pc += descrip.GetLength() - 1;
			while ( *pc == ' ' || *pc == '\n' || *pc == '\r' ) *pc-- = 0;
			descrip.ReleaseBuffer();
		} else if( (tString[0]=='/') && (tString[1]=='/') ) {
			 if( motif.GetLength() != 0  )
			 {
				 // Build Search Struct
				stcSearch *sSearch = new stcSearch;

				sSearch->iEnabled = 1;
				sSearch->strSearch = motif;
				sSearch->strName = name;
				sSearch->strDescrip = descrip;
				sSearch->rgbText = RGB(255,255,255);
				sSearch->rgbBack = RGB(0,0,0);

				int tLen = MotifLength( sSearch->strSearch );		
				if ( tLen > 128 ) {
					for ( i=0; i < 26; ++i ) {
						Member[i].RemoveAll();
					}
					Chosen.RemoveAll();
					Max.RemoveAll();
					Min.RemoveAll();
					iMXL = tLen;
					for ( i=0; i < 26; ++i ) {
						Member[i].SetSize(iMXL);
					}
					Chosen.SetSize(iMXL);
					Max.SetSize(iMXL);
					Min.SetSize(iMXL);
				}

				for ( i=0; i < pSegCount; ++i ) {
					if ( ProcessRecord( sSearch, pGSArr[i], SeqLength ) ) break;
				}

				if ( i != pSegCount ) {
					listSearch->AddTail( sSearch );
				} else {
					delete sSearch;
				}


				motif.Empty();
				name.Empty();
				descrip.Empty();

			 }
		}
	}
	for ( i=0; i < 26; ++i ) {
		Member[i].RemoveAll();
	}
	Chosen.RemoveAll();
	Max.RemoveAll();
	Min.RemoveAll();

	delete pGSArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
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

	if ( pGSArr != NULL ) delete pGSArr;
	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	if ( pGSArr != NULL ) delete pGSArr;
	return 0;
}
END_CATCH

	return 1;
}




void 
CGenedocDoc::ClearSearch(UserVars *dUV)
{
	while ( !dUV->listSearch.IsEmpty() ) {
		stcSearch *ps = (stcSearch *)dUV->listSearch.RemoveHead();
		delete ps;
	}
}

