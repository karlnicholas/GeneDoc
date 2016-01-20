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
#include <math.h>


int 
CGenedocDoc::LogOddsScore( 
	DWORD *nStartRange, 
	DWORD *nEndRange, 
	unsigned long *Score, 
	int RowCount, 
	ShadeSegStc *pSegArr )
{

	if ( m_UserVars.m_ProjectType > 1 ) {
		ScoreDNALO( nStartRange, nEndRange, Score, RowCount, pSegArr );
	} else {
		ScoreProtLO( nStartRange, nEndRange, Score, RowCount, pSegArr );
	}
	return 1;
}


extern int qijBlosum30[];
extern int qijBlosum50[];
extern int qijBlosum62[];
extern int qijBlosum75[];
extern void HCount( double MPC, double *Frac, 
	double (*q)[26][26], double *QSum, 
	double DiffRes, double TotalRes  );

	
void CGenedocDoc::ScoreProtLO(	
	DWORD *nStartRange, 
	DWORD *nEndRange, 
	unsigned long *Score, 
	int RowCount, 
	ShadeSegStc *pSegArr )
{
	// TODO: Add your command handler code here
	
	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;

	double qij[26][26];

	double dArr[26];
//	double dBackFrac[26];
	double dForeFrac[26];
	int i;
	double MPC = m_UserVars.m_dLogOddsMPC;
	int di;

	double QSum[26];
	int *pqij;
	memset ( QSum, 0, sizeof(QSum) );
	// Do this sum thing .. wasted CPU time
	switch ( m_UserVars.m_iLogOddsOutTab ) {
	case 0:
		pqij = qijBlosum30;
		break;
	case 1:
		pqij = qijBlosum50;
		break;
	case 2:
		pqij = qijBlosum62;
		break;
	case 3:
		pqij = qijBlosum75;
		break;
	default:
		pqij = qijBlosum62;
		break;
	}

	memset ( qij, 0, sizeof(qij) );
	int k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( int j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
			qij[Res1][Res2] = (double)pqij[k] / 10000.0;
			qij[Res2][Res1] = (double)pqij[k] / 10000.0;
			k++;
		}
	}

	for ( int aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'V':
		case 'W':
		case 'Y':
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					QSum[aa] = QSum[aa] + qij[aa][i];
				}
			}
		}
	}
	

	*Score = 0;

		
	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		for ( di=2; di < RowCount; ++di ) {
			char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
			}
		}

		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dForeFrac[i] = dArr[i];
		}

		HCount( MPC, dForeFrac, &qij, QSum, Diff, Total );

		for ( i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'V':
			case 'W':
			case 'Y':
				{
					if ( dForeFrac[i] == 0.0 ) {
//						oFile.WriteString( " -6.000 " );
					} else {
//						double res = dForeFrac[i] / dBackFrac[i];
						double res = dForeFrac[i];
						res = ( (1.0/log(2.0)) * log(res) );
						res *= -(dForeFrac[i]);
						*Score += unsigned long(res * 1000.0);
					}
					break;
				}
			}
		}
	}
}


extern int i11PAM30[];
extern int i11PAM60[];
extern int i11PAM90[];
extern int i31PAM30[];
extern int i31PAM60[];
extern int i31PAM90[];
extern int iPAM30pseudo[];
extern int iPAM60pseudo[];
extern int iPAM90pseudo[];
extern void HCountDNA( double MPC, double *Frac, 
	double (*q)[26][26], double *QSum, 
	double DiffRes, double TotalRes  );


void CGenedocDoc::ScoreDNALO(
	DWORD *nStartRange, 
	DWORD *nEndRange, 
	unsigned long *Score, 
	int RowCount, 
	ShadeSegStc *pSegArr 
) 
{
	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;


	// TODO: Add your command handler code here
	
	double qij[26][26];

	double dArr[26];
	double dForeFrac[26];
	int i;
	double MPC = m_UserVars.m_dLogOddsMPC;
	int di;


	double QSum[26];
	int *pqij;
	memset ( QSum, 0, sizeof(QSum) );
	// Do this sum thing .. wasted CPU time
	switch ( m_UserVars.m_iLogOddsOutTab ) {
	case 0:
		pqij = i11PAM30;
		break;
	case 1:
		pqij = i11PAM60;
		break;
	case 2:
		pqij = i11PAM90;
		break;
	case 3:
		pqij = i31PAM30;
		break;
	case 4:
		pqij = i31PAM60;
		break;
	case 5:
		pqij = i31PAM90;
		break;
	case 6:
		pqij = iPAM30pseudo;
		break;
	case 7:
		pqij = iPAM60pseudo;
		break;
	case 8:
		pqij = iPAM90pseudo;
		break;
	default:
		pqij = i11PAM60;
		break;
	}

	memset ( qij, 0, sizeof(qij) );
	int k = 0;
	for ( i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 4; ++ j ) {
			char Res1 = DNALocArray[i];
			char Res2 = DNALocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
			qij[Res1][Res2] = (double)pqij[k] / 10000.0;
//			qij[Res2][Res1] = (double)pqij[k] / 10000.0;
			k++;
		}
	}

	for ( int aa = 0; aa < 26; ++aa ) {
		switch (aa + 'A') {
		case 'A':
		case 'C':
		case 'G':
		case 'T':
			for ( i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					QSum[aa] = QSum[aa] + qij[aa][i];
				}
			}
		}
	}
	

	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		for ( di=2; di < RowCount; ++di ) {
			char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				switch ( tChar ) {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					dArr[tChar - 'A'] += pSegArr[di].pCGSeg->GetWeight();
					break;
				case 'U':
					dArr['T' - 'A'] += pSegArr[di].pCGSeg->GetWeight();
					break;
				}
			}
		}

//		double Total = 0.0;
//		for ( i=0; i < 26; ++i ) {
//			Total += dArr[i];
//		}

		double Total = 0.0;
		double Diff = 0.0;
		for ( i=0; i < 26; ++i ) {
			if ( dArr[i] != 0.0 ) Diff += 1.0;
			Total += dArr[i];
			dForeFrac[i] = dArr[i];
		}

		HCountDNA( MPC, dForeFrac, &qij, QSum, Diff, Total );
//		for ( i=0; i < 26; ++i ) {
//			dForeFrac[i] = dArr[i] / Total;
//		}

		for ( i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'G':
			case 'T':
				{
					if ( dForeFrac[i] == 0.0 ) {
//						oFile.WriteString( " -6.000 " );
					} else {
//						double res = dForeFrac[i] / dBackFrac[i];
						double res = dForeFrac[i];
						res = ( (1.0/log(2.0)) * log(res) );
						res *= -(dForeFrac[i]);
						*Score += unsigned long(res * 1000.0);
//						_snprintf ( outbuf, sizeof(outbuf), " % 5.3lf ", res );
//						oFile.WriteString( outbuf );
					}
					break;
				}
			}
		}
	}


}

