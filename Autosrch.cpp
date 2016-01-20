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



void 
CGenedocDoc::AutoShadeSearch(
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
			
	if ( !m_UserVars.m_ProSite ) {

		int iMXL = 0;

		POSITION sPOS = m_UserVars.listSearch.GetHeadPosition();
		while ( sPOS != NULL ) {

			stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(sPOS);

			int iL = MotifLength( pSearch->strSearch );
			if ( iL > iMXL ) iMXL = iL;

		}

		// CByteArray
		for ( i=0; i < 26; ++i ) {
			Member[i].SetSize(iMXL);
		}
		Chosen.SetSize(iMXL);
		Max.SetSize(iMXL);
		Min.SetSize(iMXL);
		
		for ( i = 0; i < RowCount; ++i ) {

			if ( ShadeLevel != SHADELEVEL0 ) {
				// Do Search Strings ..
				POSITION sPOS = m_UserVars.listSearch.GetHeadPosition();
				while ( sPOS != NULL ) {
					stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(sPOS);
					if ( pSearch->iEnabled ) {
						ProcessRecord( pSearch, pSegArr[i].pGeneStor, OuterCount );
					}
				}
			}
		}
		for ( i=0; i < 26; ++i ) {
			Member[i].RemoveAll();
		}
		Chosen.RemoveAll();
		Max.RemoveAll();
		Min.RemoveAll();
	} else {

		for ( i = 0; i < RowCount; ++i ) {

			if ( ShadeLevel != SHADELEVEL0 ) {
				// Do Search Strings ..
				POSITION sPOS = m_UserVars.listSearch.GetHeadPosition();
				while ( sPOS != NULL ) {
					stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(sPOS);
					if ( pSearch->iEnabled ) {
						SearchRebase( pSearch, pSegArr[i].pGeneStor, OuterCount );
					}
				}
			}
		}
	}
}


int 
CGenedocDoc::MotifLength( const char *motif )
{
    register int result;
    const char *ptr;
    register char *dst;
    char temp[10];

    result = 1;
    for( ptr=motif; *ptr; ptr++ )
        if( *ptr == '(' )
        {   dst = temp;  ptr++;
            while( *ptr && (*ptr!=',') && (*ptr!=')') )
                *dst++ = *ptr++;
            *dst = '\0';

            result += atoi(temp)-1;
            while( *ptr && (*ptr!=')') )
                 ptr++;
            if( !*ptr) break;

        } else if( *ptr == '-' )
            result++;

    return( result );
}

int 
CGenedocDoc::BuildMatrix( const char *motif )
{
    int index, pos;
    int repeat;
    char *tptr;
    const char *ptr;
    char ch;
    int i;

    char temp[10];
    char tChar;

    ptr = motif;
    pos = 0;
	const char *end = ptr + strlen(motif);

    if( (Nsignal = (*ptr=='<')) ) {
        ptr++;
	}

    do {

        ch = *ptr++;

		if ( ptr >= end ) break;

        if( ch=='[' ) {   
			// CByteArray
            for( i=0; i<26; i++ ) {
                Member[i][pos] = 0;
			}

            while( *ptr != ']' )
            {
				tChar = toupper(*ptr);
				ptr++;
				if ( ptr >= end ) goto ErrorOut;
				if ( tChar >= 'A' && tChar <= 'Z' ) {
	                Member[tChar - 'A'][pos] = 1;
				}
            }
            ptr++;
			if ( ptr >= end ) goto ErrorOut;

        } else if( ch == '{' ) {   /* Exclusive Set! */

            for( i=0; i<26; i++ ) {
                 Member[i][pos] = 1;
			}
                
            while( *ptr != '}' )
            {
				tChar = toupper(*ptr);
				ptr++;
				if ( ptr >= end ) goto ErrorOut;
				if ( tChar >= 'A' && tChar <= 'Z' ) {
	                Member[tChar - 'A'][pos] = 0;
				}
            }
            ptr++;
			if ( ptr >= end ) goto ErrorOut;

        } else { /* Amino Acid Code */
		
			char tChar = toupper( ch );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) goto ErrorOut;
			index =  tChar - 'A';
            if( index != ('X' - 'A') )
            {
				for( i=0; i<26; i++ ) {
					Member[i][pos] = 0;
				}
                Member[index][pos] = 1;
            } else {
                for( i=0; i<26; i++ ) {
                    Member[i][pos] = 1;
				}
			}
        }

        if( *ptr == '(' ) {
			tptr = temp;
            ptr++;
			if ( ptr >= end ) goto ErrorOut;

            /* Scan the first repeat count! */
            while( (*ptr!=',') && (*ptr!=')') ) {
                *tptr++ = *ptr++;
				if ( ptr >= end ) goto ErrorOut;
			}
            *tptr = '\0';

            repeat = atoi(temp);
            Min[pos] = repeat;
            Max[pos] = repeat;

            /* Scan second repeat cont */
           if( *ptr == ',' ) 
           {
				tptr = temp;
				ptr++;
				if ( ptr >= end ) goto ErrorOut;

                while( *ptr != ')' ) {
					*tptr++ = *ptr++;
					if ( ptr >= end ) goto ErrorOut;

				}
                *tptr = '\0';
                Max[pos] = atoi(temp);
            }

            /* Skip till after ')'! */
            while( *ptr!=')' ) {
                ptr++;
				if ( ptr >= end ) goto ErrorOut;
			}
            ptr++;
			if ( ptr >= end ) goto ErrorOut;
        } else {
			Min[pos] = 1;
			Max[pos] = 1;
		}
        pos++;

   } while( *ptr++ == '-' );

   if ( ptr < end ) {
	   if ( *ptr != '.' ) goto ErrorOut;
   }

   Csignal = (ptr[-1]=='>');
   /*printf("Csignal = %d '%c' %s\n", Csignal, *ptr, motif);*/

   /* Otherwise character was a '.' or a '>'! */
   return( pos );

ErrorOut:
   return 0;
}


int 
CGenedocDoc::LocateMotif( GeneStor *ptr, int pos, int length, GeneStor *end )
{
    int len,i;

    for( i=0; i<Min[pos]; i++ )
    {
		if ( ptr >= end ) return 0;
		char ct = toupper(ptr->CharGene);
		ptr++;
		while ( !(ct >= 'A' && ct <= 'Z' ) ) {
			if ( ptr >= end ) return 0;
			ct = toupper(ptr->CharGene);
			ptr++;
		}

		if( !Member[ ct - 'A'][pos] )
            return( 0 );
    }

    Chosen[pos] = i;
    if( pos+1 == length )
        return( i );

    while( i<Max[pos] )
    {   len = LocateMotif(ptr,pos+1,length, end);
        if( len ) return( len+i );

		if ( ptr >= end ) return 0;
		char ct = toupper(ptr->CharGene);
		ptr++;
		while ( !(ct >= 'A' && ct <= 'Z' ) ) {
			if ( ptr >= end ) return 0;
			ct = toupper(ptr->CharGene);
			ptr++;
		}

        if( !Member[ct - 'A'][pos] )
            return( 0 );
        Chosen[pos]++;
        i++;
    }

    len = LocateMotif(ptr,pos+1,length, end);
    return( len? len+i : 0 );
}


int 
CGenedocDoc::ProcessRecord( stcSearch *pSearch, GeneStor *pGeneStor, DWORD SeqLength, int Test )
{
    GeneStor *end, *begin;
    GeneStor *ptr;

    DWORD start;
    int found;
    int i;

	int length = BuildMatrix( pSearch->strSearch );

	// Test bad syntax
	if ( length == 0 ) return 0;

	end = pGeneStor + SeqLength;

    /* Signal Processing */
    begin = Csignal? end : pGeneStor;
    if( Nsignal ) end = begin+1;

    found = 0;

    for ( ptr=begin; ptr<end; ptr++ )
    {    
		char tChar = toupper(ptr->CharGene);
		if ( !(tChar >= 'A' && tChar <= 'Z' ) ) continue;
		if( !(i=LocateMotif(ptr,0,length, end)) ) continue;
		if ( Test ) return 1;

         start = ptr - pGeneStor;
//         if( found )
//         {
//			if( start > MotifStop )
//			{
//				MotifStop = start+i;
//				MotifStart = start;
//			} else 
//				 MotifStop = start+i;

//         } else {   

			MotifStop = start+i;
			MotifStart = start;
			found = 1;
//		}

		 // Color Here ..

		int shd = (int)(MotifStop - MotifStart);
		for ( int j=0; j<shd; ++j ) {
//			char tChar = toupper(pGeneStor[start+j].CharGene);
			char tChar = toupper(pGeneStor[MotifStart+j].CharGene);
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				pGeneStor[MotifStart+j].TextColor = pSearch->rgbText;
				pGeneStor[MotifStart+j].BackColor = pSearch->rgbBack;
			} else {
				++shd;
			}
		}
	}

	return found;

}


