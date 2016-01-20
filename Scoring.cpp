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


struct stcDNAAve {
	char	cRes;
	char	caNA[5];
};

struct stcDNAAve DNAAve[] = {
	{ 'C', "C" }, 
	{ 'G', "G" }, 
	{ 'A', "A" }, 
	{ 'T', "T" }, 
	{ 'Y', "CT" }, 
	{ 'R', "AG" },
	{ 'W', "AT" },
	{ 'S', "CG" }, 
	{ 'K', "TG" }, 
	{ 'M', "CA" }, 
	{ 'B', "CGT" },
	{ 'D', "AGT" }, 
	{ 'H', "ACT" }, 
	{ 'V', "ACG" }, 
	{ 'N', "CGAT" }, 
	{ 'X', "CGAT" }, 

	{ '\0', "" }, 
};



void 
CalcDNAAve(int Sim[26][26])
{
	struct stcDNAAve* pDNA1 = &DNAAve[0];
	struct stcDNAAve* pDNA2;

	while ( pDNA1->cRes != '\0' ) {
		pDNA2 = pDNA1;
		while ( pDNA2->cRes != '\0' ) {
			int c1 = strlen( pDNA1->caNA );
			int c2 = strlen( pDNA2->caNA );
			if ( c1 != 1 || c2 != 1 ) {
				int iTot = 0;
				for ( int i=0; i < c1; ++i ) {
					for ( int j=0; j < c2; ++j ) {
						iTot += Sim[pDNA1->caNA[i]-'A'][pDNA2->caNA[j]-'A'];
					}
				}
				iTot /= ( c1 * c2 );
				Sim[pDNA1->cRes-'A'][pDNA2->cRes-'A'] = iTot;
				Sim[pDNA2->cRes-'A'][pDNA1->cRes-'A'] = iTot;
			}
			pDNA2++;
		}
		pDNA1++;
	}

}

#define Builddp \
	char Res = DNALocArray[0]; \
	Res -= 'A'; \
	Sim[Res][Res] = Match - Match; \
	for ( int i = 1; i < 4; ++i ) { \
		for ( int j = 0; j < i; ++j ) { \
			char Res1 = DNALocArray[i]; \
			char Res2 = DNALocArray[j]; \
			Res1 -= 'A'; \
			Res2 -= 'A'; \
			Sim[Res1][Res2] = Match - MisMch; \
			Sim[Res2][Res1] = Match - MisMch; \
		} \
		char Res1 = DNALocArray[i]; \
		Res1 -= 'A'; \
        Sim[Res1][Res1] = Match - Match; \
	}

void 
dp20( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int Match = 9;
	int MisMch = -1;
	
	*CurrentZeroDistance = Match;
	*NewGap = Match - -15;
	*GapLength = Match - -5;

	Builddp

	CalcDNAAve(Sim);
}


void 
dp30( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int Match = 9;
	int MisMch = -9;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -13;
	*GapLength = Match - -4;

	Builddp

	CalcDNAAve(Sim);
}


void 
dp47( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int Match = 5;
	int MisMch = -4;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -6;
	*GapLength = Match - -2;

	Builddp

	CalcDNAAve(Sim);
}


void 
dp50( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int Match = 9;
	int MisMch = -7;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -15;
	*GapLength = Match - -5;

	Builddp

	CalcDNAAve(Sim);
}


void 
dp65( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Match = 3;
	int MisMch = -2;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -3;
	*GapLength = Match - -1;

	Builddp

	CalcDNAAve(Sim);
}

void 
dp85( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Match = 7;
	int MisMch = -4;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -6;
	*GapLength = Match - -3;

	Builddp

	CalcDNAAve(Sim);
}

void 
dp110( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Match = 2;
	int MisMch = -1;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -2;
	*GapLength = Match - -1;

	Builddp

	CalcDNAAve(Sim);
}

#define Builddpb  \
	char Res = DNALocArray[0]; \
	Res -= 'A'; \
	Sim[Res][Res] = Match - Match; \
	int k = 0; \
	for ( int i = 1; i < 4; ++i ) { \
		for ( int j = 0; j < i; ++j ) { \
			char Res1 = DNALocArray[i]; \
			char Res2 = DNALocArray[j]; \
			Res1 -= 'A'; \
			Res2 -= 'A'; \
			Sim[Res1][Res2] = Match - Mis[k]; \
			Sim[Res2][Res1] = Match - Mis[k]; \
			k = k + 1; \
		} \
		char Res1 = DNALocArray[i]; \
		Res1 -= 'A'; \
		Sim[Res1][Res1] = Match - Match; \
	}
//	int Res1 = 'N' - 'A'; 
//	Sim[Res1][Res1] = Match - XX;


void
dp20b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Mis[] = { -21, -10, -21, -21, -10, -21, -21, -21, -21, -21 };
	int Match = 13;
	int XX = -21;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -16;
	*GapLength = Match - -8;
	
	Builddpb

	CalcDNAAve(Sim);
}


void
dp50b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int Mis[] = { -13, -3, -13, -13, -3, -13, -13, -13, -13, -13 };
	int Match = 11;
	int XX = -13;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -11;
	*GapLength = Match - -5;
	
	Builddpb

	CalcDNAAve(Sim);
}

void
dp85b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Mis[] = { -1,  0,  -1,  -1,  0,  -1,  -1,  -1,  -1,  -1 };
	int Match = 1;
	int XX = -1;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -2;
	*GapLength = Match - -1;
	
	Builddpb

	CalcDNAAve(Sim);
}

void IDMat( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{
	int Match = 10;
	int MisMch = -5;

	*CurrentZeroDistance = Match;
	*NewGap = Match - -10;
	*GapLength = Match - -5;

	Builddp

	CalcDNAAve(Sim);
}

char ProteinLocArray[] = { 
			'A',  
			'R',  
			'N', 
			'D',  
			'C',
			'Q',  
			'E',  
			'G',  
			'H',  
			'I',  
			'L',  
			'K',  
			'M',  
			'F',  
			'P',  
			'S',  
			'T',  
			'W',  
			'Y',  
			'V',  
			'B',  
			'Z',  
			'X'	
		};

char DNALocArray[] = { 
			'A',  
			'C',  
			'G',  
			'T',
			'Y',
			'R',
			'W',
			'S',
			'K',
			'M',
			'B',
			'D',
			'H',
			'V',
			'N',
			'X',
};

/*
char 
ProtienConvertIndexToChar( int idx ) 
{
//		for ( Loc = 0; Loc < sizeof( LocArr ); ++Loc ) {
//			if ( n == LocArr[Loc] ) break;
//		}
		
//		if ( Loc == sizeof(LocArr) ) {
//			return INT_MIN;	// No Match
//		}

		return ProteinLocArray[idx];
}

		return Loc;
	} else {

		static char LocArr[] = { 
			'A',  
			'C',  
			'G',  
			'T',  
			'N'	
		};

		for ( Loc = 0; Loc < sizeof( LocArr ); ++Loc ) {
			if ( n == LocArr[Loc] ) break;
		}
		
		if ( n == 'U' ) {
			Loc = 3;
		} else if ( 
			n == 'X'
			|| n == 'R' 
			|| n == 'Y' 
			|| n == 'M' 
			|| n == 'K' 
			|| n == 'S' 
			|| n == 'W' 
			|| n == 'H' 
			|| n == 'B' 
			|| n == 'V' 
			|| n == 'D'
		) {
			Loc = 4;
		} else {
			if ( Loc == sizeof(LocArr) ) {
				return INT_MIN;		// no Match
			}
		}
		
		return Loc;
	}
	
	// Will never get here
	return INT_MIN;
}

*/


int ScoreArray[26][26];
int	NewGap, GapLen;
int CurrentZeroDistance;


void
Blosum35( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/4" };

//C
//C
//C ***   The blosum matrix holds the 276 lower triangular elements of
//C       the Blosum35 similarity matrix in one fourth bit units.
//C
//C = A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X
//C
int blosum[] = 
	{
       5,  -1,   8,  -1,  -1,   7,  -1,  -1,   1,   8,  -2,  -3,
      -1,  -3,  15,   0,   2,   1,  -1,  -3,   7,  -1,  -1,  -1,
       2,  -1,   2,   6,   0,  -2,   1,  -2,  -3,  -2,  -2,   7,
      -2,  -1,   1,   0,  -4,  -1,  -1,  -2,  12,  -1,  -3,  -1,
      -3,  -4,  -2,  -3,  -3,  -3,   5,  -2,  -2,  -2,  -2,  -2,
      -2,  -1,  -3,  -2,   2,   5,   0,   2,   0,  -1,  -2,   0,
       1,  -1,  -2,  -2,  -2,   5,   0,   0,  -1,  -3,  -4,  -1,
      -2,  -1,   1,   1,   3,   0,   6,  -2,  -1,  -1,  -3,  -4,
      -4,  -3,  -3,  -3,   1,   2,  -1,   0,   8,  -2,  -2,  -2,
      -1,  -4,   0,   0,  -2,  -1,  -1,  -3,   0,  -3,  -4,  10,
       1,  -1,   0,  -1,  -3,   0,   0,   1,  -1,  -2,  -2,   0,
      -1,  -1,  -2,   4,   0,  -2,   0,  -1,  -1,   0,  -1,  -2,
      -2,  -1,   0,   0,   0,  -1,   0,   2,   5,  -2,   0,  -2,
      -3,  -5,  -1,  -1,  -1,  -4,  -1,   0,   0,   1,   1,  -4,
      -2,  -2,  16,  -1,   0,  -2,  -2,  -5,   0,  -1,  -2,   0,
       0,   0,  -1,   0,   3,  -3,  -1,  -2,   3,   8,   0,  -1,
      -2,  -2,  -2,  -3,  -2,  -3,  -4,   4,   2,  -2,   1,   1,
      -3,  -1,   1,  -2,   0,   5,  -1,  -1,   4,   5,  -2,   0,
       0,   0,   0,  -2,  -2,   0,  -2,  -2,  -1,   0,  -1,  -3,
      -2,  -2,   5,  -1,   0,   0,   1,  -2,   4,   5,  -2,  -1,
      -3,  -2,   1,  -2,  -3,   0,   0,  -1,  -1,  -1,  -2,   0,
       4,   0,  -1,   0,  -1,  -2,  -1,  -1,  -1,  -1,   0,   0,
       0,   0,  -1,  -1,   0,   0,  -1,  -1,   0,  -1,   0,  -1
	};
//
//	strcpy ( MatDef, Def );
//	strcpy ( Bits, IBits );

	int Max = 0;
	for ( i = 0; i < (sizeof(blosum)/sizeof(int)); ++i ) {
		if ( blosum[i] > Max ) Max = blosum[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -8;
	*GapLength = Max - -3;
      
	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - blosum[k];
			Sim[Res2][Res1] = Max - blosum[k];
			k++;
		}
	}
}


void
Blosum45( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/3" };

//C
//C ***   The blosum matrix holds the 276 lower triangular elements of
//C       the Blosum45 similarity matrix in one third bit units.
//C
//C = A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X
//C
	int blosum[] = 
	{
       5,  -2,   7,  -1,   0,   6,  -2,  -1,   2,   7,  -1,  -3,
      -2,  -3,  12,  -1,   1,   0,   0,  -3,   6,  -1,   0,   0,
       2,  -3,   2,   6,   0,  -2,   0,  -1,  -3,  -2,  -2,   7,
      -2,   0,   1,   0,  -3,   1,   0,  -2,  10,  -1,  -3,  -2,
      -4,  -3,  -2,  -3,  -4,  -3,   5,  -1,  -2,  -3,  -3,  -2,
      -2,  -2,  -3,  -2,   2,   5,  -1,   3,   0,   0,  -3,   1,
       1,  -2,  -1,  -3,  -3,   5,  -1,  -1,  -2,  -3,  -2,   0,
      -2,  -2,   0,   2,   2,  -1,   6,  -2,  -2,  -2,  -4,  -2,
      -4,  -3,  -3,  -2,   0,   1,  -3,   0,   8,  -1,  -2,  -2,
      -1,  -4,  -1,   0,  -2,  -2,  -2,  -3,  -1,  -2,  -3,   9,
       1,  -1,   1,   0,  -1,   0,   0,   0,  -1,  -2,  -3,  -1,
      -2,  -2,  -1,   4,   0,  -1,   0,  -1,  -1,  -1,  -1,  -2,
      -2,  -1,  -1,  -1,  -1,  -1,  -1,   2,   5,  -2,  -2,  -4,
      -4,  -5,  -2,  -3,  -2,  -3,  -2,  -2,  -2,  -2,   1,  -3,
      -4,  -3,  15,  -2,  -1,  -2,  -2,  -3,  -1,  -2,  -3,   2,
       0,   0,  -1,   0,   3,  -3,  -2,  -1,   3,   8,   0,  -2,
      -3,  -3,  -1,  -3,  -3,  -3,  -3,   3,   1,  -2,   1,   0,
      -3,  -1,   0,  -3,  -1,   5,  -1,  -1,   4,   5,  -2,   0,
       1,  -1,   0,  -3,  -3,   0,  -2,  -3,  -2,   0,   0,  -4,
      -2,  -3,   4,  -1,   0,   0,   1,  -3,   4,   4,  -2,   0,
      -3,  -2,   1,  -1,  -3,  -1,   0,  -1,  -2,  -2,  -3,   0,
       4,   0,  -1,  -1,  -1,  -2,  -1,  -1,  -1,  -1,  -1,  -1,
      -1,  -1,  -1,  -1,   0,   0,  -2,  -1,  -1,  -1,  -1,  -1 
	};
//
	int Max = 0;
	for ( i = 0; i < (sizeof(blosum)/sizeof(int)); ++i ) {
		if ( blosum[i] > Max ) Max = blosum[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -7;
	*GapLength = Max - -2;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - blosum[k];
			Sim[Res2][Res1] = Max - blosum[k];
			k++;
		}
	}
}

void
Blosum62( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;


	char IBits[] = { " 1/3" };
//C
//C ***   The blosum matrix holds the 276 lower triangular elements of
//C       the Blosum62 similarity matrix in one third bit units.
//C
//C = A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X
//C
	int blosum[] = 
	{
       6,  -2,   8,  -2,  -1,   8,  -3,  -2,   2,   9,  -1,  -5,
      -4,  -5,  13,  -1,   1,   0,   0,  -4,   8,  -1,   0,   0,
       2,  -5,   3,   7,   0,  -3,  -1,  -2,  -4,  -3,  -3,   8,
      -2,   0,   1,  -2,  -4,   1,   0,  -3,  11,  -2,  -4,  -5,
      -5,  -2,  -4,  -5,  -6,  -5,   6,  -2,  -3,  -5,  -5,  -2,
      -3,  -4,  -5,  -4,   2,   6,  -1,   3,   0,  -1,  -5,   2,
       1,  -2,  -1,  -4,  -4,   7,  -1,  -2,  -3,  -5,  -2,  -1,
      -3,  -4,  -2,   2,   3,  -2,   8,  -3,  -4,  -4,  -5,  -4,
      -5,  -5,  -5,  -2,   0,   1,  -5,   0,   9,  -1,  -3,  -3,
      -2,  -4,  -2,  -2,  -3,  -3,  -4,  -4,  -2,  -4,  -5,  11,
       2,  -1,   1,   0,  -1,   0,   0,   0,  -1,  -4,  -4,   0,
      -2,  -4,  -1,   6,   0,  -2,   0,  -2,  -1,  -1,  -1,  -2, 
      -3,  -1,  -2,  -1,  -1,  -3,  -2,   2,   7,  -4,  -4,  -6,
      -6,  -3,  -3,  -4,  -4,  -4,  -4,  -2,  -4,  -2,   1,  -5,
      -4,  -4,  16,  -3,  -3,  -3,  -5,  -4,  -2,  -3,  -5,   3,
      -2,  -2,  -3,  -1,   4,  -4,  -3,  -2,   3,  10,   0,  -4,
      -4,  -5,  -1,  -3,  -4,  -5,  -5,   4,   1,  -3,   1,  -1,
      -4,  -2,   0,  -4,  -2,   6,  -2,  -2,   5,   6,  -5,   0,
       1,  -1,  -1,  -5,  -5,  -1,  -4,  -5,  -3,   0,  -1,  -6,
      -4,  -5,   5,  -1,   0,   0,   1,  -5,   5,   6,  -3,   0,
      -5,  -4,   1,  -2,  -5,  -2,   0,  -1,  -4,  -3,  -4,   0,
       5,  -1,  -2,  -2,  -2,  -3,  -1,  -1,  -2,  -2,  -2,  -2,
      -1,  -1,  -2,  -2,  -1,  -1,  -3,  -2,  -1,  -2,  -1,  -2
	};
//
	int Max = 0;
	for ( i = 0; i < (sizeof(blosum)/sizeof(int)); ++i ) {
		if ( blosum[i] > Max ) Max = blosum[i];
	}


	*CurrentZeroDistance = Max;
	*NewGap = Max - -8;
	*GapLength = Max - -4;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - blosum[k];
			Sim[Res2][Res1] = Max - blosum[k];
			k++;
		}
	}
}

void
Blosum80( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/3" };
//C
//C ***   The blosum matrix holds the 276 lower triangular elements of
//C       the Blosum80 similarity matrix in one third bit units.
//C
//C = A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X
//C
	int blosum[] = 
	{
       7,  -3,   9,  -3,  -1,   9,  -3,  -3,   2,  10,  -1,  -6,
      -5,  -7,  13,  -2,   1,   0,  -1,  -5,   9,  -2,  -1,  -1,
       2,  -7,   3,   8,   0,  -4,  -1,  -3,  -6,  -4,  -4,   9,
      -3,   0,   1,  -2,  -7,   1,   0,  -4,  12,  -3,  -5,  -6,
      -7,  -2,  -5,  -6,  -7,  -6,   7,  -3,  -4,  -6,  -7,  -3,
      -4,  -6,  -7,  -5,   2,   6,  -1,   3,   0,  -2,  -6,   2,
       1,  -3,  -1,  -5,  -4,   8,  -2,  -3,  -4,  -6,  -3,  -1,
      -4,  -5,  -4,   2,   3,  -3,   9,  -4,  -5,  -6,  -6,  -4,
      -5,  -6,  -6,  -2,  -1,   0,  -5,   0,  10,  -1,  -3,  -4,
      -3,  -6,  -3,  -2,  -5,  -4,  -5,  -5,  -2,  -4,  -6,  12,
       2,  -2,   1,  -1,  -2,  -1,  -1,  -1,  -2,  -4,  -4,  -1,
      -3,  -4,  -2,   7,   0,  -2,   0,  -2,  -2,  -1,  -2,  -3,
      -3,  -2,  -3,  -1,  -1,  -4,  -3,   2,   8,  -5,  -5,  -7,
      -8,  -5,  -4,  -6,  -6,  -4,  -5,  -4,  -6,  -3,   0,  -7,
      -6,  -5,  16,  -4,  -4,  -4,  -6,  -5,  -3,  -5,  -6,   3,
      -3,  -2,  -4,  -3,   4,  -6,  -3,  -3,   3,  11,  -1,  -4,
      -5,  -6,  -2,  -4,  -4,  -6,  -5,   4,   1,  -4,   1,  -2,
      -4,  -3,   0,  -5,  -3,   7,  -3,  -2,   5,   6,  -6,  -1,
       1,  -2,  -1,  -6,  -7,  -1,  -5,  -6,  -4,   0,  -1,  -8,
      -5,  -6,   6,  -2,   0,  -1,   1,  -7,   5,   6,  -4,   0,
      -6,  -5,   1,  -3,  -6,  -2,  -1,  -2,  -5,  -4,  -4,   0,
       6,  -1,  -2,  -2,  -3,  -4,  -2,  -2,  -3,  -2,  -2,  -2,
      -2,  -2,  -3,  -3,  -1,  -1,  -5,  -3,  -2,  -3,  -1,  -2
	};

//
	int Max = 0;
	for ( i = 0; i < (sizeof(blosum)/sizeof(int)); ++i ) {
		if ( blosum[i] > Max ) Max = blosum[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -12;
	*GapLength = Max - -6;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - blosum[k];
			Sim[Res2][Res1] = Max - blosum[k];
			k++;
		}
	}
}


void
Blosum100( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/3" };

//C
//C ***   The blosum matrix holds the 276 lower triangular elements of
//C       the Blosum100 similarity matrix in one third bit units.
//C
//C = A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  Z  X

	int blosum[] = { 
       8,  -3,  10,  -4,  -2,  11,  -5,  -5,   1,  10,  -2,  -8,
      -5,  -8,  14,  -2,   0,  -1,  -2,  -7,  11,  -3,  -2,  -2,
       2,  -9,   2,  10,  -1,  -6,  -2,  -4,  -7,  -5,  -6,   9,
      -4,  -1,   0,  -3,  -8,   1,  -2,  -6,  13,  -4,  -7,  -7,
      -8,  -3,  -6,  -7,  -9,  -7,   8,  -4,  -6,  -7,  -8,  -5,
      -5,  -7,  -8,  -6,   2,   8,  -2,   3,  -1,  -3,  -8,   2,
       0,  -5,  -3,  -6,  -6,  10,  -3,  -4,  -5,  -8,  -4,  -2,
      -5,  -7,  -5,   1,   3,  -4,  12,  -5,  -6,  -7,  -8,  -4,
      -6,  -8,  -8,  -4,  -2,   0,  -6,  -1,  11,  -2,  -5,  -5,
      -5,  -8,  -4,  -4,  -6,  -5,  -7,  -7,  -3,  -5,  -7,  12,
       1,  -3,   0,  -2,  -3,  -2,  -2,  -2,  -3,  -5,  -6,  -2,
      -4,  -5,  -3,   9,  -1,  -3,  -1,  -4,  -3,  -3,  -3,  -5, 
      -4,  -3,  -4,  -3,  -2,  -5,  -4,   2,   9,  -6,  -7,  -8,
     -10,  -7,  -5,  -8,  -7,  -5,  -6,  -5,  -8,  -4,   0,  -8,
      -7,  -7,  17,  -5,  -5,  -5,  -7,  -6,  -4,  -7,  -8,   1,
      -4,  -4,  -5,  -5,   4,  -7,  -5,  -5,   2,  12,  -2,  -6,
      -7,  -8,  -3,  -5,  -5,  -8,  -7,   4,   0,  -5,   0,  -3,
      -6,  -4,  -1,  -5,  -5,   8,  -4,  -4,   5,   6,  -7,  -2,
       0,  -3,  -2,  -8,  -8,  -2,  -7,  -7,  -5,  -1,  -2,  -9,
      -6,  -7,   6,  -2,  -1,  -2,   0,  -8,   5,   7,  -5,  -1,
      -7,  -6,   0,  -4,  -7,  -4,  -2,  -3,  -7,  -6,  -5,   0,
       6,  -2,  -3,  -3,  -4,  -5,  -2,  -3,  -4,  -4,  -3,  -3,
      -3,  -3,  -4,  -4,  -2,  -2,  -6,  -4,  -3,  -4,  -2,  -3  
	};
//
	int Max = 0;
	for ( i = 0; i < (sizeof(blosum)/sizeof(int)); ++i ) {
		if ( blosum[i] > Max ) Max = blosum[i];
	}

	*CurrentZeroDistance = Max;
   	*NewGap = Max - -15;
	*GapLength = Max - -5;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - blosum[k];
			Sim[Res2][Res1] = Max - blosum[k];
			k++;
		}
	}
}


void
Pam120( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/2" };
//C
//C   Pam 120 Amino Acid Similarity matrix
//C
//C ***   Order of amino acdids in PAM matrices
//C      Character*1  AA(23)
//C      DATA  AA  / 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I',
//C     *            'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V',
//C     1            'B', 'Z', 'X' /
//C
	int dayhof[] = 
	{
	  3, -3,  6,  0, -1,  4,  0, -3,  2,  5, -3, -4,
     -5, -7,  9, -1,  1,  0,  1, -7,  6,  0, -3,  1,  3, -7,  2,
      5,  1, -4,  0,  0, -5, -3, -1,  5, -3,  1,  2,  0, -4,  3,
     -1, -4,  7, -1, -2, -2, -3, -3, -3, -3, -4, -4,  6, -3, -4,
     -4, -5, -7, -2, -4, -5, -3,  1,  5, -2,  2,  1, -1, -7,  0,
     -1, -3, -2, -2, -4,  5, -2, -1, -3, -4, -6, -1, -4, -4, -4,
      1,  3,  0,  8, -4, -4, -4, -7, -6, -6, -6, -5, -2,  0,  0,
     -6, -1,  8,  1, -1, -2, -2, -3,  0, -1, -2, -1, -3, -3, -2,
     -3, -5,  6,  1, -1,  1,  0, -1, -2, -1,  1, -2, -2, -4, -1,
     -2, -3,  1,  3,  1, -2,  0, -1, -3, -2, -2, -1, -3,  0, -3,
     -1, -1, -4, -1,  2,  4, -7,  1, -5, -8, -8, -6, -8, -8, -5,
     -7, -5, -5, -7, -1, -7, -2, -6, 12, -4, -6, -2, -5, -1, -5,
     -4, -6, -1, -2, -3, -6, -4,  4, -6, -3, -3, -1,  8,  0, -3,
     -3, -3, -2, -3, -3, -2, -3,  3,  1, -4,  1, -3, -2, -2,  0,
     -8, -3,  5,  0, -2,  3,  3, -6,  0,  2,  0,  1, -2, -4,  0,
     -3, -5, -2,  0,  0, -6, -3, -3,  3,  0, -1,  0,  2, -7,  4,
      3, -2,  1, -3, -3,  0, -2, -6,  0, -1, -2, -7, -4, -3,  1,
      3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1 
	};
//
	int Max = 0;
	for ( i = 0; i < (sizeof(dayhof)/sizeof(int)); ++i ) {
		if ( dayhof[i] > Max ) Max = dayhof[i];
	}


	*CurrentZeroDistance = Max;
	*NewGap = Max - -12;
	*GapLength = Max - -6;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - dayhof[k];
			Sim[Res2][Res1] = Max - dayhof[k];
			k++;
		}
	}
}


void
Pam160( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " ?? " };
//C
//C ***   Order of amino acdids in PAM matrices
//C      Character*1  AA(23)
//C      DATA  AA  / 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I',
//C     *            'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V',
//C     1            'B', 'Z', 'X' /
//C
	int dayhof[] = 
	{
		2, -2,  6,  0, -1,  3,  0, -2,  2,  4, -2, -3,
	   -4, -5,  9, -1,  1,  0,  1, -5,  5,  0, -2,  1,  3, -5,  2,
		4,  1, -3,  0,  0, -4, -2,  0,  4, -2,  1,  1,  0, -3,  2,
		0, -3,  6, -1, -2, -2, -3, -2, -2, -2, -3, -3,  5, -2, -3,
       -3, -4, -6, -2, -3, -4, -2,  1,  5, -2,  3,  1,  0, -5,  0,
       -1, -2, -1, -2, -3,  4, -1, -1, -2, -3, -5, -1, -3, -3, -3,
        2,  3,  1,  7, -3, -4, -3, -5, -4, -4, -5, -4, -2,  0,  1,
       -5, -1,  7,  1, -1, -1, -1, -3,  0, -1, -1, -1, -3, -2, -2,
       -3, -4,  5,  1, -1,  1,  0,  0, -1,  0,  1, -1, -2, -3,  0,
       -2, -3,  1,  2,  1, -1,  0, -1, -2, -1, -1, -1, -2,  0, -2,
        0, -1, -3,  0,  1,  3, -5,  1, -4, -7, -7, -5, -7, -6, -4,
       -6, -4, -4, -5,  0, -5, -2, -5, 12, -3, -5, -2, -4,  0, -4,
       -4, -5,  0, -2, -2, -5, -3,  5, -5, -3, -3,  0,  8,  0, -3,
       -2, -3, -2, -2, -2, -2, -3,  3,  1, -3,  1, -2, -2, -1,  0,
       -7, -3,  4,  1,  0,  4,  4, -3,  2,  3,  1,  2, -1, -3,  1,
       -2, -3,  0,  1,  1, -4, -2, -1,  5,  1,  1,  2,  3, -4,  5,
        4,  0,  2, -1, -1,  1, -1, -4,  1,  0,  0, -5, -3, -1,  4,
        5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1  
    };
//
	int Max = 0;
	for ( i = 0; i < (sizeof(dayhof)/sizeof(int)); ++i ) {
		if ( dayhof[i] > Max ) Max = dayhof[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -10;
	*GapLength = Max - -4;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - blosum[k];
//			if ( j < i ) Sim[j][i] = Max - blosum[k];
			Sim[Res1][Res2] = Max - dayhof[k];
			Sim[Res2][Res1] = Max - dayhof[k];
			k++;
		}
	}
}


void
Pam200( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = {" ?? " };
//C
//C ***   Order of amino acids in PAM matrices
//C
//C      DATA  AA  / 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I',
//C     *            'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V',
//C     1            'B', 'Z', 'X' /
//C
//C      *****     PAM200 Scoring Matrix - Similarity     *****
//C
	int dayhof[] = 
	{
		 2, -2,  0,  0, -2, -1,  0,  1, -1, -1,
		-2, -1, -1, -3,  1,  1,  1, -5, -3,  0,
		 1,  1, -1, -2,  5,  0, -1, -3,  1, -1,
		-3,  1, -2, -2,  2,  0, -3,  0,  0, -1,
		 1, -4, -2,  0,  1, -1,  0,  0,  2,  2,
		-3,  0,  1,  0,  1, -1, -2,  1, -2, -2,
		 0,  1,  0, -4, -1, -2,  3,  2, -1,  0,
		-1,  2,  3, -4,  1,  3,  0,  0, -2, -3,
		 0, -2, -4, -1,  0,  0, -6, -3, -2,  4,
		 3, -1, -2, -3, -3, -4,  8, -4, -4, -3,
		-3, -2, -5, -4, -4, -4, -2,  0, -2, -6,
		 0, -2, -3, -3, -1, -1,  1,  0,  1, -4,
		 4,  2, -1,  2, -2, -1,  0, -1, -4,  0,
		-1, -1, -4, -3, -2,  2,  4, -1,  0, -1,
		 1,  3, -4,  2,  3,  0,  0, -2, -3,  0,
		-2, -4,  0,  0,  0, -6, -3, -2,  3,  4,
		-1,  1, -3,  0,  0, -3, -1,  0,  4, -2,
		-2, -3, -2, -3, -3, -1,  1,  0, -5, -4,
		-1,  1,  0, -1, -1,  1,  1,  0, -3,  2,
		 0, -2,  5, -2, -2,  0, -2, -1,  0, -1,
		-1, -3,  0, -2,  2,  2, -1, -1, -2, -1,
		-2, -2, -2, -2, -2, -2,  4,  2, -1,  2,
		 1, -2, -1,  0, -5, -1,  3, -1, -1, -1,
		-2, -2, -2, -3, -5, -1, -3, -3, -2,  2,
		 4, -2,  3,  1, -2, -2, -1, -4, -1,  1,
		-2, -1, -1, -1,  2,  1,  0, -4,  0,  0,
		-2,  0, -1, -2,  4,  1, -4, -1,  0,  0,
		-3, -4, -2,  1,  1, -1, -1,  0, -2, -2,
		-4, -1, -2, -3, -2,  2,  3,  1,  5,  0,
		-2, -1,  0, -4, -2,  1, -1,  0, -1, -3,
		-3, -2, -4, -4, -4, -4, -3, -1,  1,  1,
		-4,  0,  7, -4, -2, -2,  0,  5, -1, -2,
		-3, -1,  1,  0,  0, -1, -2,  0,  0, -1,
		 0, -2, -2, -1, -2, -4,  5,  1,  0, -5,
		-4, -1,  0,  1, -1,  1,  0,  1,  0,  0,
		-1,  0,  1, -1, -1, -2,  0, -1, -2,  1,
		 2,  1, -2, -2, -1,  1,  1, -1,  1, -1,
		 0,  0, -2, -1,  0,  0, -1,  0, -1,  0,
		 0, -2,  0,  1,  3, -4, -2,  0,  1,  0,
		-1, -5,  1, -4, -6, -6, -4, -6, -5, -3,
		-5, -4, -3, -4,  0, -5, -2, -4, 12,  0,
		-6, -3, -4, -1, -3, -4, -1, -3,  0, -3,
		-3, -4,  0, -1, -1, -4, -2,  5, -4, -2, 
		-2,  0,  7, -2, -1, -2, -1,  0, -2, -2,
		-2, -2, -2, -2, -1, -2,  3,  1, -2,  1,
		-1, -1, -1,  0, -6, -2,  4, -1, -1, -1,
		 1,  0,  3,  4, -3,  2,  3,  1,  2, -1,
		-2,  1, -1, -2,  0,  1,  1, -3, -1, -1,
		 4,  4, -1,  1,  1,  2,  3, -3,  4,  4,
		 0,  2, -1, -1,  1,  0, -3,  1,  1,  0,
		-4, -2, -1,  4,  5, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1
	};
//C
//C ***   Code to put PAM200 values into square scoring matrix, Sim.
//
	int Max = 0;
	for ( i = 0; i < (sizeof(dayhof)/sizeof(int)); ++i ) {
		if ( dayhof[i] > Max ) Max = dayhof[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -8;
	*GapLength = Max - -3;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j < 23; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
			Sim[Res1][Res2] = Max - dayhof[k++];
//			Sim[i][j] = Max - dayhof[k++];

		}
	}
}

void
Pam250( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance )
{

	int i, j, k;

	char IBits[] = { " 1/3" };

	int dayhof[] = {
	2, -2, 6, 0,  0,  2,  0, -1,  2,  4, -2, -4, -4, -5,
	12,  0,  1,  1,  2, -5,  4,  0, -1,  1,  3, -5,  2,  4,
	1, -3,  0,  1, -3, -1,  0,  5, -1,  2,  2,  1, -3,  3,
	1, -2,  6, -1, -2, -2, -2, -2, -2, -2, -3, -2,  5, -2, -3, -3, -4, -6,
	-2, -3, -4, -2,  2,  6, -1,  3,  1,  0, -5,  1,  0, -2,
	0, -2, -3,  5, -1,  0, -2, -3, -5, -1, -2, -3, -2,  2,
	4,  0,  6, -4, -4, -4, -6, -4, -5, -5,  -5, -2,  1,  2, -5,  0,
	9,  1,  0, -1, -1, -3,  0, -1, -1,  0, -2, -3, -1, -2,
	-5,  6,  1,  0,  1,  0,  0, -1,  0,  1, -1, -1, -3,  0,
	-2, -3,  1,  2,  1, -1,  0,  0, -2, -1,  0,  0, -1,  0,
	-2,  0, -1, -3,  0,  1,  3, -6,  2, -4, -7, -8, -5, -7,
	-7, -3, -5, -2, -3, -4,  0, -6, -2, -5, 17, -3, -4, -2,
	-4,  0, -4, -4, -5,  0, -1, -1, -4, -2,  7, -5, -3, -3,
	0, 10,  0, -2, -2, -2, -2, -2, -2, -1, -2,  4,  2, -2,  2, -1, -1, -1,  0,
	-6, -2,  4,  0, -1,  2,  3, -4,  1,  2,  0,  1, -2, -3,
	1, -2, -5, -1,  0,  0, -5, -3, -2,  2,  0,  0,  1,  3,
	-5,  3,  3, -1,  2, -2, -3,  0, -2, -5,  0,  0, -1, -6,
	-4, -2,  2,  3,  0, -1,  0, -1, -3, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1,
	0,  0, -4, -2, -1,  0, -1, -1 
	};
//
	int Max = 0;
	for ( i = 0; i < (sizeof(dayhof)/sizeof(int)); ++i ) {
		if ( dayhof[i] > Max ) Max = dayhof[i];
	}

	*CurrentZeroDistance = Max;
	*NewGap = Max - -12;
	*GapLength = Max - -4;

	k = 0;
	for ( i = 0; i < 23; ++i ) {
		for ( j = 0; j <= i; ++ j ) {
			char Res1 = ProteinLocArray[i];
			char Res2 = ProteinLocArray[j];
			Res1 -= 'A';
			Res2 -= 'A';
//			Sim[i][j] = Max - dayhof[k];
//			if ( j < i ) Sim[j][i] = Max - dayhof[k];
			Sim[Res1][Res2] = Max - dayhof[k];
			Sim[Res2][Res1] = Max - dayhof[k];
			k++;
		}
	}
}

