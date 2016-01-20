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

int 
CGenedocDoc::LogOddsReport(CString& PathName)
{

	char outbuf[256];

	stcLogOdds *pLogOdds = NULL;
	CPtrList m_listHold;
	POSITION tPos = m_UserVars.m_listLogOdds.GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pLO = (stcLogOdds *)m_UserVars.m_listLogOdds.GetNext(tPos);
		m_listHold.AddTail( (void *)pLO->iEnabled );
		pLO->iEnabled = 0;
	}
	CMotSeqDlg sDlg;
	sDlg.pDoc = this;


	int rRet = sDlg.DoModal();

	BeginWaitCursor();

	tPos = m_UserVars.m_listLogOdds.GetHeadPosition();
	POSITION sPos = m_listHold.GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pLO = (stcLogOdds *)m_UserVars.m_listLogOdds.GetNext(tPos);
		int iE = (int)m_listHold.GetNext(sPos);
		if ( pLO->iEnabled ) pLogOdds = pLO;
		pLO->iEnabled = iE;
	}

	if ( rRet != IDOK ) return 0;

	if ( pLogOdds == NULL ) return 0;

	// TODO: Add your command handler code here
//	static char BASED_CODE szFilter[] = "Data Files (*.dat)|*.dat|All Files (*.*)|*.*||";

//	CString possName = ConvertPathname ( ".dat" );

//	CFileDialog tDlg(FALSE, "dat", possName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL );

//	if ( tDlg.DoModal() != IDOK ) return 0;


TRY {

	CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );


	BeginWaitCursor(); // Let em know


	int RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
	
	ShadeSegStc *pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here


	int SeqCount = 0;
	DWORD SeqLength;
	DWORD OuterCount;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( tCGSeg->GetExportFlag()  ) continue;
	
		SeqLength = tCGSeg->GetTextLength();
		// Lock it down
		pSegArr[SeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
		pSegArr[SeqCount].pCGSeg = tCGSeg;
		SeqCount++;
		OuterCount = tCGSeg->GetTextLength();
	}



	// end for ..
	int sLen = pLogOdds->iLogOddsCount;
	if ( sLen == 0 ) return 0;
	int mCount = 0;

	oFile.WriteString ( " Column" );
	for ( int i=0; i < SeqCount; ++i ) {
		_snprintf ( outbuf, 256, " %10s", (const char *)pSegArr[i].pCGSeg->GetTitle() );
		oFile.WriteString ( outbuf );
	}
	_snprintf ( outbuf, 256, " Total" );
	oFile.WriteString ( outbuf );
	oFile.WriteString ( "\n" );

	double TotSc = 0.0;

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;

		_snprintf ( outbuf, 256, "%7ld", tCount + 1 );
		oFile.WriteString ( outbuf );

		for ( int i=0; i < SeqCount; ++i ) {

			char tChar = toupper(pSegArr[i].pGeneStor[tCount].CharGene);

			if ( !(tChar >= 'A' && tChar <= 'Z' ) ) {
				_snprintf ( outbuf, 256, "          -" );
				oFile.WriteString ( outbuf );
				continue;
			}

			// for report.
			double ThisScore = 0.0;
			DWORD sCount = 0;
			for ( int j = 0; j < sLen; ++j ) {
				char tChar;
				do { 
					if ( tCount + sCount > OuterCount ) break;
					tChar = toupper(pSegArr[i].pGeneStor[tCount + sCount].CharGene);
					sCount++;
				} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

				if ( tCount + sCount > OuterCount ) {
					break;
				}

				ThisScore += pLogOdds->dLogOddsArr[j][tChar - 'A'];
			}

			TotSc += ThisScore;
			_snprintf ( outbuf, 256, " %10.3lf", ThisScore );
			oFile.WriteString ( outbuf );
		}
		_snprintf ( outbuf, 256, " %10.3lf", TotSc );
		oFile.WriteString ( outbuf );
		TotSc = 0.0;
		oFile.WriteString ( "\n" );
	}



	oFile.Close();


	for (int i=0; i < SeqCount; ++i ) {
		GlobalUnlock( pSegArr[i].pCGSeg->GetTextHandle() );
	}

	delete [] pSegArr;


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
CGenedocDoc::ScanMemeMotifs(const CString& PathName, CPtrList *listLogOdds)
{

	GeneStor ** pGSArr = NULL;

TRY {

    int counter = 1, i;

    CString motif;
    CString motift;
    CString name;
	CString descrip;
	CString Alphabet;
	int FoundAlpha = 0;


	CString tString;

	CStdioFile rFile(PathName, CFile::modeRead );

    while( 1 )
    {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			break;
		}
		tString.ReleaseBuffer();

		if( tString.Find( "ALPHABET= " ) != -1 )
		{
			int loc = tString.Find( "ALPHABET= " );
			Alphabet = tString.Mid(loc + 10);
			char *pc = Alphabet.GetBuffer(Alphabet.GetLength());
			pc += Alphabet.GetLength() - 1;
			while ( *pc == ' ' || *pc == '\n' || *pc == '\r' ) *pc-- = 0;
			Alphabet.ReleaseBuffer();
			FoundAlpha = 1;
			break;
		}
	}

	if ( !FoundAlpha ) {
		AfxMessageBox( "Cannot find ALPHABET= in meme file!" );
		return 0;
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

		if( tString.Left(5) == CString("BL   ") ) {
			descrip = tString.Mid(5);
			// trim right
			char *pc = descrip.GetBuffer(descrip.GetLength());
			pc += descrip.GetLength() - 1;
			while ( *pc == ' ' || *pc == '\n' || *pc == '\r' ) *pc-- = 0;
			descrip.ReleaseBuffer();
		} else if ( tString.Left(10) == CString("Multilevel") ) {
			motift = tString.Mid(10);
			motif = "";
			char *pc = motift.GetBuffer(motift.GetLength());
			while ( *pc != 0 ) {
				if ( isalpha(*pc) ) motif += *pc;
				pc++;
			}
//			pc += motif.GetLength() - 1;
//			while ( *pc == ' ' || *pc == '\n' || *pc == '\r' ) *pc-- = 0;
			// Trim left
			motift.ReleaseBuffer();
		} else if ( tString.Left(25) == CString("log-odds matrix: alength=") ) {

			int length, width, any;
			double bayes;
			int ret = sscanf( (const char *)tString, "log-odds matrix: alength= %d w= %d n= %d bayes= %lf", &length, &width, &any, &bayes );
			if ( ret != 4 ) {
				ret = sscanf( (const char *)tString, "log-odds matrix: alength= %d w= %d", &length, &width );
				bayes = 0.0;
				if ( ret != 2 ) continue;
			}

			if ( Alphabet.GetLength() != length ) continue;

			double (*matrix)[26];
			matrix = new double[width][26];
			memset ( matrix, 0, sizeof(double)*width*26 );
			for ( i=0; i < width; ++i ) {
				tString.Empty();
				char *tStr = tString.GetBuffer(1024);
				if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
					// Done .. break out
					break;
				}
				tString.ReleaseBuffer();
				int loc = 0;
				int end = tString.GetLength();
				for ( int l=0; l<length; ++l ) {
					CString val;
					int gotdot = 0;
					int gotnum = 0;
					while (1) {
						char c = tString[loc++];
						val += c;
						if ( isdigit(c) ) gotnum = 1;
						if ( c == '.' ) gotdot = 1;
						if ( c == ' ' && gotnum ) break;
						if ( loc >= end ) break;
					}
					double div;
					if ( gotdot ) div = 1.0;
					else div = 100.0;
					matrix[i][toupper(Alphabet[l]) - 'A'] = atof( (const char *)val ) / div;
					if ( m_UserVars.m_ProjectType > 1 ) {
						char tChar = toupper(Alphabet[l]);
						if ( tChar == 'T' || tChar == 'U' ) {
							matrix[i]['T' - 'A'] = atof( (const char *)val ) / div;
							matrix[i]['U' - 'A'] = atof( (const char *)val ) / div;
						}
					}
					if ( loc >= end ) break;
				}
				if ( loc >= end ) break;
			}
			if ( i != width ) continue;
			char *pc = name.GetBuffer(128);
			sprintf( pc, "Motif %d", counter++ );
			name.ReleaseBuffer();

			 // Build LogOdds Struct
			stcLogOdds *sLogOdds = new stcLogOdds;

			sLogOdds->dLogOddsArr = matrix;
			sLogOdds->iEnabled = 1;
			sLogOdds->iLogOddsCount = width;
			sLogOdds->dLogOddsBayes = bayes;

			sLogOdds->strMotif = motif;
			sLogOdds->strName = name;
			sLogOdds->strDescrip = descrip;
			sLogOdds->rgbText = RGB(255,255,255);
			sLogOdds->rgbBack = RGB(0,0,0);

			listLogOdds->AddTail( sLogOdds );


			motif.Empty();
			name.Empty();
			descrip.Empty();

		}
	}

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



void 
CGenedocDoc::ClearLogOdds(UserVars *dUV)
{
	while ( !dUV->m_listLogOdds.IsEmpty() ) {
		stcLogOdds *ps = (stcLogOdds *)dUV->m_listLogOdds.RemoveHead();
		delete [] ps->dLogOddsArr;
		delete ps;
	}

}


void 
CGenedocDoc::AutoShadeLogOdds(
	ShadeSegStc *pSegArr, 
	int RowCount, 
	int ShadeLevel, 
	CDisplayVars *DisplayVars, 
	ShadeSegStc *pConsensusRow
) 
{

	int i;

	DWORD OuterCount = pSegArr[0].pCGSeg->GetTextLength();
	
	// init locations
	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
	
		for ( i = 0; i < RowCount; ++i ) {

			// Lets Clear out old shades while here.
			GetLevelColors( DisplayVars, 0, 
				&(pSegArr[i].pGeneStor)[tCount].TextColor, 
				&(pSegArr[i].pGeneStor)[tCount].BackColor
			);

			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			// Reset Display Char while here.
			if ( DisplayVars->GetResidueMode() == 0 ) {
				if ( m_UserVars.m_ResidueUpper == 1 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
				} else if ( m_UserVars.m_ResidueUpper == 2 ) {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
				} else {
					(pSegArr[i].pGeneStor)[tCount].CharDisplay = tChar;
				}
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
			}
		}
	}
			

	for ( i = 0; i < RowCount; ++i ) {

		if ( ShadeLevel != SHADELEVEL0 ) {
			// Do LogOdds 
			POSITION sPOS = m_UserVars.m_listLogOdds.GetHeadPosition();
			while ( sPOS != NULL ) {
				stcLogOdds *pLogOdds = (stcLogOdds *)m_UserVars.m_listLogOdds.GetNext(sPOS);
				if ( !pLogOdds->iEnabled ) continue;

				switch ( m_UserVars.m_iLogOddsMode ) {
				case 0:
					LogOddsShade( pLogOdds, pSegArr[i].pGeneStor, OuterCount );
					break;
				case 1:
					LogOddsShadeBestN( pLogOdds, pSegArr[i].pGeneStor, OuterCount );
					break;
				case 2:
					LogOddsShadeBetter( pLogOdds, pSegArr[i].pGeneStor, OuterCount );
					break;
				case 3:
					LogOddsShadeThree( pLogOdds, pSegArr[i].pGeneStor, OuterCount );
					break;
				}
			}
		}
	}
}


void 
CGenedocDoc::LogOddsShadeBetter( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount )
{
	typedef struct {
		double Score;
		DWORD Start;
		DWORD End;
	} stcLOSc;

	CPtrArray LOScArr;

	// end for ..
	int sLen = pLogOdds->iLogOddsCount;
	if ( sLen == 0 ) return;
	int mCount = 0;

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;

		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;

		// for report.
		double ThisScore = 0.0;
		DWORD sCount = 0;
		int match = 1;
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

			ThisScore += pLogOdds->dLogOddsArr[j][tChar - 'A'];
		}
		if ( match && ThisScore >= m_UserVars.m_dLogOddsMin ) {
			stcLOSc *pLOSc = new stcLOSc;
			pLOSc->Score = ThisScore;
			pLOSc->Start = tCount;
			pLOSc->End = tCount + sCount;
			LOScArr.Add( pLOSc );
			int c = LOScArr.GetSize();
			int deld = 0;

			if ( c && m_UserVars.m_iLogOddsNoOv ) {
				for ( int i=0; i < c; ++i ) {
					for ( int j=i+1; j < c; ++j ) {
						stcLOSc *pLOSc1 = (stcLOSc *)LOScArr.GetAt(i);
						stcLOSc *pLOSc2 = (stcLOSc *)LOScArr.GetAt(j);
						if ( 
							(pLOSc1->Start >= pLOSc2->Start && pLOSc1->Start <= pLOSc2->End)
							|| (pLOSc1->End >= pLOSc2->Start && pLOSc1->End <= pLOSc2->End) 
						) {
							// OverLap Detected
							// Remove Lower Score
							// CPtrArr
							if ( pLOSc1->Score > pLOSc1->Score ) {
								LOScArr.RemoveAt(j);
							} else {
								LOScArr.RemoveAt(i);
							}
							deld = 1;
							break;
						}
					}
					if ( deld == 1 ) break;
				}
			}
		}
	}



	int c = LOScArr.GetSize();
	for ( int i=0; i < c; ++i ) {
		stcLOSc *pLOSc1 = (stcLOSc *)LOScArr.GetAt(i);

		DWORD sCount = 0;
		for ( int j = 0; j < sLen; ++j ) {
			char tChar;
			do { 
				if ( pLOSc1->Start + sCount > OuterCount ) break;
				tChar = toupper(pGeneStor[pLOSc1->Start + sCount].CharGene);
				sCount++;
			} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

			if ( pGeneStor[pLOSc1->Start + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
				pGeneStor[pLOSc1->Start + sCount - 1].TextColor = RGB(0,0,0);
				pGeneStor[pLOSc1->Start + sCount - 1].BackColor = m_UserVars.m_rgbLogOddsOverlap;
			} else {
				pGeneStor[pLOSc1->Start + sCount - 1].TextColor = pLogOdds->rgbText;
				pGeneStor[pLOSc1->Start + sCount - 1].BackColor = pLogOdds->rgbBack;
			}
		}
	}
	for (int i=0; i < c; ++i ) {
		delete (stcLOSc *)LOScArr.GetAt(i);
	}
}



void 
CGenedocDoc::LogOddsShadeThree( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount )
{
	// end for ..
	int sLen = pLogOdds->iLogOddsCount;
	if ( sLen == 0 ) return;
	int mCount = 0;
	double HighScore;
	for ( int i=0; i < pLogOdds->iLogOddsCount; ++i ) {
		double RowHigh = 0.0;
		for ( int a=0; a<26; ++a ) {
			if ( pLogOdds->dLogOddsArr[i][a] > RowHigh ) RowHigh = pLogOdds->dLogOddsArr[i][a];
		}
		HighScore += RowHigh;
	}
	double TL1, TL2, TL3;
	TL1 = HighScore * (m_UserVars.m_dLogOddsTL1 / 100.0);
	TL2 = HighScore * (m_UserVars.m_dLogOddsTL2 / 100.0);
	TL3 = HighScore * (m_UserVars.m_dLogOddsTL3 / 100.0);


	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;

		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;

		// for report.
		double ThisScore = 0.0;
		DWORD sCount = 0;
		int match = 1;
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

			ThisScore += pLogOdds->dLogOddsArr[j][tChar - 'A'];
		}

		// Test if Should do Colors.
		if ( match && ThisScore >= TL3 ) {
			COLORREF rgbText, rgbBack;
			rgbText = m_UserVars.m_ForeColor60;
			rgbBack = m_UserVars.m_BackColor60;
			if ( ThisScore >= TL2 ) {
				rgbText = m_UserVars.m_ForeColor80;
				rgbBack = m_UserVars.m_BackColor80;
			}
			if ( ThisScore >= TL1 ) {
				rgbText = m_UserVars.m_ForeColor100;
				rgbBack = m_UserVars.m_BackColor100;
			}

			if ( m_UserVars.m_iLogOddsNoOv ) {
				int Back = 0;
				sCount = 0;
				for (int j = 0; j < sLen; ++j ) {
					char tChar;
					do { 
						tChar = toupper(pGeneStor[tCount + sCount].CharGene);
						sCount++;
					} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

					if ( pGeneStor[tCount + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
						Back = 1;
						break;
					}
				}
				if ( Back ) continue;
			}
			sCount = 0;
			for (int j = 0; j < sLen; ++j ) {
				char tChar;
				do { 
					tChar = toupper(pGeneStor[tCount + sCount].CharGene);
					sCount++;
				} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

				if ( pGeneStor[tCount + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
					pGeneStor[tCount + sCount - 1].TextColor = RGB(0,0,0);
					pGeneStor[tCount + sCount - 1].BackColor = m_UserVars.m_rgbLogOddsOverlap;
				} else {
					pGeneStor[tCount + sCount - 1].TextColor = rgbText;
					pGeneStor[tCount + sCount - 1].BackColor = rgbBack;
				}
			}
		}
	}
}

void 
CGenedocDoc::LogOddsShadeBestN( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount )
{
	typedef struct {
		double Score;
		DWORD Start;
		DWORD End;
	} stcLOSc;

	CPtrArray LOScArr;

	// end for ..
	int sLen = pLogOdds->iLogOddsCount;
	if ( sLen == 0 ) return;
	int mCount = 0;

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;

		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;

		// for report.
		double ThisScore = 0.0;
		DWORD sCount = 0;
		int match = 1;
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

			ThisScore += pLogOdds->dLogOddsArr[j][tChar - 'A'];
		}
		if ( match ) {
			stcLOSc *pLOSc = new stcLOSc;
			pLOSc->Score = ThisScore;
			pLOSc->Start = tCount;
			pLOSc->End = tCount + sCount;
			LOScArr.Add( pLOSc );
			int c = LOScArr.GetSize();
			int deld = 0;

			if ( c && m_UserVars.m_iLogOddsNoOv ) {
				for ( int i=0; i < c; ++i ) {
					for ( int j=i+1; j < c; ++j ) {
						stcLOSc *pLOSc1 = (stcLOSc *)LOScArr.GetAt(i);
						stcLOSc *pLOSc2 = (stcLOSc *)LOScArr.GetAt(j);
						if ( 
							(pLOSc1->Start >= pLOSc2->Start && pLOSc1->Start <= pLOSc2->End)
							|| (pLOSc1->End >= pLOSc2->Start && pLOSc1->End <= pLOSc2->End) 
						) {
							// OverLap Detected
							// Remove Lower Score
							// CPtrArr
							if ( pLOSc1->Score > pLOSc1->Score ) {
								LOScArr.RemoveAt(j);
							} else {
								LOScArr.RemoveAt(i);
							}
							deld = 1;
							break;
						}
					}
					if ( deld == 1 ) break;
				}
			}

			// Sort for Best Score
			for ( int i=0; i < c-1; ++i ) {
				for ( int j=i+1; j < c; ++j ) {
					stcLOSc *pLOSc1 = (stcLOSc *)LOScArr.GetAt(i);
					stcLOSc *pLOSc2 = (stcLOSc *)LOScArr.GetAt(j);
					if ( pLOSc1->Score < pLOSc2->Score ) {
						LOScArr.SetAt(i, pLOSc2);
						LOScArr.SetAt(j, pLOSc1);
					}
				}
			}
			// Check Max Size ...
			if ( c > m_UserVars.m_iLogOddsBestN ) {
				delete (stcLOSc *)LOScArr.GetAt(c-1);
				LOScArr.RemoveAt(c-1);
			}
		}
	}



	int c = LOScArr.GetSize();
	for ( int i=0; i < c; ++i ) {
		stcLOSc *pLOSc1 = (stcLOSc *)LOScArr.GetAt(i);

		DWORD sCount = 0;
		for ( int j = 0; j < sLen; ++j ) {
			char tChar;
			do { 
				if ( pLOSc1->Start + sCount > OuterCount ) break;
				tChar = toupper(pGeneStor[pLOSc1->Start + sCount].CharGene);
				sCount++;
			} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

			if ( pGeneStor[pLOSc1->Start + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
				pGeneStor[pLOSc1->Start + sCount - 1].TextColor = RGB(0,0,0);
				pGeneStor[pLOSc1->Start + sCount - 1].BackColor = m_UserVars.m_rgbLogOddsOverlap;
			} else {
				pGeneStor[pLOSc1->Start + sCount - 1].TextColor = pLogOdds->rgbText;
				pGeneStor[pLOSc1->Start + sCount - 1].BackColor = pLogOdds->rgbBack;
			}
		}
	}
	for (int i=0; i < c; ++i ) {
		delete (stcLOSc *)LOScArr.GetAt(i);
	}
}


void 
CGenedocDoc::LogOddsShade( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount )
{
	// end for ..
	int sLen = pLogOdds->iLogOddsCount;
	if ( sLen == 0 ) return;
	int mCount = 0;

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( sLen + tCount > OuterCount ) break;

		char tChar = toupper(pGeneStor[tCount].CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;

		// for report.
		double ThisScore = 0.0;
		DWORD sCount = 0;
		int match = 1;
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

			ThisScore += pLogOdds->dLogOddsArr[j][tChar - 'A'];
		}

		// Test if Should do Colors.
		if ( match && ThisScore >= pLogOdds->dLogOddsBayes ) {

			sCount = 0;
			for (int j = 0; j < sLen; ++j ) {
				char tChar;
				do { 
					if ( tCount + sCount > OuterCount ) break;
					tChar = toupper(pGeneStor[tCount + sCount].CharGene);
					sCount++;
				} while ( !(tChar >= 'A' && tChar <= 'Z' ) );

				if ( pGeneStor[tCount + sCount - 1].BackColor != m_UserVars.m_BackColor0 ) {
					pGeneStor[tCount + sCount - 1].TextColor = RGB(0,0,0);
					pGeneStor[tCount + sCount - 1].BackColor = m_UserVars.m_rgbLogOddsOverlap;
				} else {
					pGeneStor[tCount + sCount - 1].TextColor = pLogOdds->rgbText;
					pGeneStor[tCount + sCount - 1].BackColor = pLogOdds->rgbBack;
				}
			}
		}
	}
}
