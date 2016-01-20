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

#define GENEDOCIDSTR	"GENEDOC:" 

#define GDFONTWEIGHT	"Font Weight:"
#define GDFONTSIZE		"Font Size:"

#define GDFOREPRI		"Fore Pri:"
#define GDFORESEC		"Fore Sec:"
#define GDFORETERT		"Fore Tert:"
#define GDFOREBASE		"Fore Base:"

#define GDBACKPRI		"Back Pri:"
#define GDBACKSEC		"Back Sec:"
#define GDBACKTERT		"Back Tert:"
#define GDBACKBASE		"Back Base:"

#define GDLEFTBORD		"Left Bord:"
#define GDRIGHTBORD		"Right Bord:"
#define GDTOPBORD		"Top Bord:"
#define GDBOTTOMBORD	"Bottom Bord:"

#define GDPRINTSTRING "PString:"
#define GDPRINTSTRINGFLAG "PStringF:"
#define GDPRINTPAGENUMBER "PPageNum:"
#define GDPRINTPAGEOFFSET "PPageOff:"
#define GDPRINTFONTWEIGHT "PFontW:"
#define GDPRINTFONTSIZE "PFontS:"
#define GDPRINTFONTNAME "PFontN:"
#define GDPRINTGENEBLOCK "PGeneB:"

#define GDWIDTHMODE		"Width Mode:"
#define GDFIXEDX		"Fixed X:"
#define GDSCORETABLE	"Score Table:"

#define GDSHOWTAIL		"Seq Indicator:"
#define GDORIENTATION	"Orient:"
#define GDGAPIND		"Gap Ind:"
#define GDPROJTYPE		"Proj Type:"
#define GDGROUPDISPMODE	"GDMode:"
#define GDCOLORSEQNAMES	"ColSeqN:"

#define GDTTLPROG		"Ttl Prog:"
#define GDTTLSM			"Ttl SM:"
#define GDTTLOG			"Ttl OG:"
#define GDTTLEG			"Ttl EG:"


#define GDCONSENSUS		"Consensus:"		// m_ConsensusLine;

#define GDSHADEGROUPS	"Shade Groups:"
#define GDPHYLOTREE		"PhTree"

#define GDSCOREMETH		"Scor Meth:"

#define GDPICTWIDTH		"Pct Wdth:"
#define GDPICTHEIGHT	"Pct Hght:"
#define GDPICTASCENT	"Pct Asct:"

#define GDAUTOSSTC		"ASSTC:"
#define GDPCRSET		"PCRSet:"


// DisplayVars Start
#define GDPRILEVEL		"Pri Level"
#define GDSECLEVEL		"Sec Level"
#define GDTERTLEVEL		"Tert Level"

#define GDSHADEMODE		"Shade Mode"		// m_ModeConserved
#define GDGROUPENABLED	"Groups Enabled"
#define GDLASTSHADE		"Last Shade"

#define GDDIFFMODE		"Diff Mode"
#define GDPROPSTYLE		"Prop Style"
#define GDRESIDUEMODE	"Residue Mode"


#define GDPROPGROUPS	"Prop Gp"

#define GDSTRUCTURE		"StcInf"
#define GDSTCFNAMES		"StcFNS"
#define GDSTCDEFUSER	"StcDU"

#define GDGROUPNAME		"GroupName"
#define GDGROUPINF		"GroupInf"
#define GDGROUPSEQ		"GroupSeq"
// DisplayVars End
#define GDMARKER		"Marker:"
#define GDCHEMPROP		"ChemProp"
#define GDNAMESIND		"NmnInd:"


const char *
CGenedocDoc::GDUFindString ( const CString& FindString )
{
	int FindLoc;
	const char * rStr;
	
	POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while ( tPos != NULL ) {
		CString *tStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
		if ( tStr->Find ( GENEDOCIDSTR ) == -1 ) continue;
		if ( (FindLoc = tStr->Find(FindString)) != -1 ) {
			rStr = (const char *)*tStr;
			rStr += FindLoc + FindString.GetLength();
			return rStr;
		}
	}
	
	return NULL;
}


void 
CGenedocDoc::GetUserDefaults( )
{

	const char * tStr;
	char DecodeBuff[256];

	int NewHeader = 0;
	POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while ( tPos != NULL ) {
		CString *tStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
		if ( tStr->Find ( GENEDOCIDSTR ) != -1 ) break;
		if ( tStr->Find ( "GDC " ) != -1 ) {
			NewHeader = 1;
			break;
		}
	}

	if ( NewHeader ) {
		GetNewUserDefaults();
		return;
	}

	SetModifiedFlag();

	tStr = GDUFindString ( GDFONTWEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FontWeight = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDFONTSIZE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FontSize = atoi( DecodeBuff );
	}


	tStr = GDUFindString ( GDFOREPRI );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_ForeColor100 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDFORESEC );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_ForeColor80 = RGB ( Red, Green, Blue );
	}
		
	tStr = GDUFindString ( GDFORETERT );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_ForeColor60 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDFOREBASE );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_ForeColor0 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDBACKPRI );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_BackColor100 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDBACKSEC );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_BackColor80 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDBACKTERT );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_BackColor60 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDBACKBASE );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_BackColor0 = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDLEFTBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_LeftBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDRIGHTBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_RightBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDTOPBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_TopBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDBOTTOMBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_BottomBorder = atof( DecodeBuff );
	}


	tStr = GDUFindString ( GDPRINTSTRING );
	if ( tStr != NULL ) {
		tStr++;
		m_UserVars.m_PrintString = tStr;
	}

	tStr = GDUFindString ( GDPRINTSTRINGFLAG );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintStringFlag = atoi( DecodeBuff );
		if ( m_UserVars.m_PrintStringFlag > 2 ) m_UserVars.m_PrintStringFlag = 0;
	}

	tStr = GDUFindString ( GDPRINTPAGENUMBER );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintPageNumber = atoi( DecodeBuff );
		if ( m_UserVars.m_PrintPageNumber > 4 ) m_UserVars.m_PrintPageNumber = 0;
	}

	tStr = GDUFindString ( GDPRINTPAGEOFFSET );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 5 );
		DecodeBuff[5] = 0;
		m_UserVars.m_PrintPageOffset = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTWEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_PrintFontWeight = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTSIZE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_PrintFontSize = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTGENEBLOCK );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintGeneBlock = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTNAME );
	if ( tStr != NULL ) {
		tStr++;
		m_UserVars.m_PrintFontName = tStr;
	}


	tStr = GDUFindString ( GDWIDTHMODE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_WidthMode = atoi( DecodeBuff );
		if ( m_UserVars.m_WidthMode != 0 ) m_UserVars.m_WidthMode = 1;
	}

	tStr = GDUFindString ( GDFIXEDX );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FixedXSize = atoi( DecodeBuff );
		if ( m_UserVars.m_FixedXSize > 999 ) m_UserVars.m_FixedXSize = 999;
	}

	tStr = GDUFindString ( GDSCORETABLE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_CurrentScoreTable = atoi( DecodeBuff );
		if ( m_UserVars.m_CurrentScoreTable > 19 ) m_UserVars.m_CurrentScoreTable = 2;
	}

	tStr = GDUFindString ( GDCONSENSUS );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ConsensusLine = atoi( DecodeBuff );
		if ( m_UserVars.m_ConsensusLine > 2 ) m_UserVars.m_ConsensusLine = 2;
	}

	tStr = GDUFindString ( GDSHOWTAIL );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ShowTail = atoi( DecodeBuff );
		if ( m_UserVars.m_ShowTail != 0 ) m_UserVars.m_ShowTail = 1;
	}

	tStr = GDUFindString ( GDORIENTATION );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_Orientation = atoi( DecodeBuff );
		if ( m_UserVars.m_Orientation != 0 ) m_UserVars.m_Orientation = 1;
	}

	tStr = GDUFindString ( GDGAPIND );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_GapInd = atoi( DecodeBuff );
		if ( m_UserVars.m_GapInd != 0 ) m_UserVars.m_GapInd = 1;
	}

	tStr = GDUFindString ( GDPROJTYPE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ProjectType = atoi( DecodeBuff );
		if ( m_UserVars.m_ProjectType > 4 ) m_UserVars.m_ProjectType = 0;
	}

	tStr = GDUFindString ( GDGROUPDISPMODE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_GroupDisplayMode = atoi( DecodeBuff );
		if ( m_UserVars.m_GroupDisplayMode >= GROUPDISPMAX ) 
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
	}

	tStr = GDUFindString ( GDCOLORSEQNAMES );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ColorSeqNames = atoi( DecodeBuff );
		if ( m_UserVars.m_ColorSeqNames != 0 ) 
			m_UserVars.m_ColorSeqNames = 1;
	}


	tStr = GDUFindString ( GDAUTOSSTC );
	if ( tStr != NULL ) {
		CString strASS(tStr+1);
		for ( int i =0; i < 3; ++i ) {
			int FLoc;
		
			if ( (FLoc = strASS.Find(',')) == -1 ) {
				break;
			}
			
			CString Name = strASS.Left( FLoc );
			
			strASS = strASS.Mid( FLoc + 1 );

			switch(i){
			case 0:
				m_UserVars.m_AutoShade4Structure = Name;
				break;
			case 1:
				m_UserVars.m_AutoShade3Structure = Name;
				break;
			case 2:
				m_UserVars.m_AutoShade2Structure = Name;
				break;
			}
		}
	}


	tStr = GDUFindString ( GDPCRSET );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_GroupConsLevel = atof( DecodeBuff );
		//
		m_UserVars.m_PCRSimilarities = tStr;
		m_UserVars.m_PCRSimilarities = m_UserVars.m_PCRSimilarities.Mid(6,20);
		int i;
		for ( int i=0; i < m_UserVars.m_PCRSimilarities.GetLength(); ++i ) {
			if ( m_UserVars.m_PCRSimilarities[i] != ' ' ) break;
		}
		m_UserVars.m_PCRSimilarities = m_UserVars.m_PCRSimilarities.Right(m_UserVars.m_PCRSimilarities.GetLength() - i);

		//
		memcpy ( DecodeBuff, tStr + 6 + 20, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_PCRLevel = atof( DecodeBuff );
	}


	tStr = GDUFindString ( GDMARKER );
	if ( tStr != NULL ) {
		m_UserVars.m_MarkerSymb = tStr[1];

		memcpy ( DecodeBuff, tStr + 2, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_MarkerSpacing = atoi( DecodeBuff );

		memcpy ( DecodeBuff, tStr + 2 + 6, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_MarkerReplace = atoi( DecodeBuff );
		
		memcpy ( DecodeBuff, tStr + 2 + 6 + 6, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_MarkerStart = atoi( DecodeBuff );

		memcpy ( DecodeBuff, tStr + 2 + 6 + 6 + 6, 1 );
		DecodeBuff[1] = 0;
		m_UserVars.m_MarkerEnable = atoi( DecodeBuff );
		
		m_UserVars.m_ConservedGap = tStr[2 + 6 + 6 + 6 + 1];

		memcpy ( DecodeBuff, tStr + 2 + 6 + 6 + 6 + 1 + 1, 1 );
		DecodeBuff[1] = 0;
		m_UserVars.m_ResidueUpper = atoi( DecodeBuff );

		memcpy ( DecodeBuff, tStr + 2 + 6 + 6 + 6 + 1 + 1 + 1, 1 );
		DecodeBuff[1] = 0;
		m_UserVars.m_ChemPropCysteine = atoi( DecodeBuff );

		memcpy ( DecodeBuff, tStr + 2 + 6 + 6 + 6 + 1 + 1 + 1 + 1, 1 );
		DecodeBuff[1] = 0;
		m_UserVars.m_ChemPropShowProp = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDNAMESIND );
	if ( tStr != NULL ) {
		// marker flags
		m_UserVars.m_MaxNameLength = ((tStr[1] - '0') * 10) + (tStr[2] - '0');

		int i = 3;
		m_UserVars.m_strLead.Empty();
		while(1) {
			char tChar = ((*(tStr+i)) - 'A') * 16;
			i++;
			tChar += (*(tStr+i)) - 'A';
			i++;
			if ( tChar == 0 ) break;
			m_UserVars.m_strLead += tChar;
		}

		m_UserVars.m_strTail.Empty();
		while(1) {
			char tChar = ((*(tStr+i)) - 'A') * 16;
			i++;
			tChar += (*(tStr+i)) - 'A';
			i++;
			if ( tChar == 0 ) break;
			m_UserVars.m_strTail += tChar;
		}
	}

	
	int TopCount = 1;
	// CPtrArray
	CString strChemProp;
	while ( 1 ) {
	
		sprintf ( DecodeBuff, "%s%d:", GDCHEMPROP, TopCount );

		tStr = GDUFindString ( DecodeBuff );
		if ( tStr == NULL ) {
			// Were done!!
			break;
		}

		tStr++;

		strChemProp += tStr;

		TopCount++;
	}

	// CString
	if ( strChemProp.GetLength() == 15*3*3*2 ) {
		const char *pc = strChemProp;
		// Now Get the Colors ..
		int Rd0, Grn0, Bl0, Rd1, Grn1, Bl1;
		TopCount = 0;
		for ( int i = 0; i < 12*3*3*2; i += 3*3*2 ) {
			memcpy(DecodeBuff, pc + i, 3*3*2 );
			DecodeBuff[3*3*2] = 0;
			sscanf( DecodeBuff, "%03d%03d%03d%03d%03d%03d", &Rd0, &Grn0, &Bl0, &Rd1, &Grn1, &Bl1 );
			m_UserVars.ChemGroupOxi[TopCount].TextColor = RGB( Rd0, Grn0, Bl0 );
			m_UserVars.ChemGroupOxi[TopCount++].BackColor = RGB( Rd1, Grn1, Bl1 );
		}
		TopCount = 0;
		for (int i = 12*3*3*2; i < 15*3*3*2; i += 3*3*2 ) {
			memcpy(DecodeBuff, pc + i, 3*3*2 );
			DecodeBuff[3*3*2] = 0;
			sscanf( DecodeBuff, "%03d%03d%03d%03d%03d%03d", &Rd0, &Grn0, &Bl0, &Rd1, &Grn1, &Bl1 );
			m_UserVars.ChemCons[TopCount].TextColor = RGB( Rd0, Grn0, Bl0 );
			m_UserVars.ChemCons[TopCount++].BackColor = RGB( Rd1, Grn1, Bl1 );
		}
	}
	//
	
	int lPos = 0;
	char convbuff[10];

	do {
		CString strLook = CString(GDSTCDEFUSER) + CString(_itoa( lPos, convbuff, 10 )) + ":";
			
		if ( (tStr = GDUFindString( strLook )) == NULL ) break;

		CString rStr = tStr + 1;
			
		CString fString;
		int fLoc;

		while ( (fLoc = rStr.Find( ',' )) != -1 ) {
			fString = rStr.Left( fLoc );
			rStr = rStr.Right( rStr.GetLength() - fLoc - 1 );

			char * pc = fString.GetBuffer( fString.GetLength() );
			while ( *pc != 0 ) {
				if ( *pc == '|' ) *pc = '.';
				pc++;
			}
			fString.ReleaseBuffer();
		
			if ( LoadUserSduFile( m_PathName + fString ) )
				m_UserVars.m_StcDefUser.AddTail( fString );
		}
			
		lPos++;

	} while (1);


	tStr = GDUFindString ( GDTTLPROG );
	if ( tStr != NULL ) {
		char *tStr2 = m_UserVars.m_TitleProgram.GetBuffer(128);
		int ff = 1;
		for ( int i = 0; i < 21; ++i ) {
			if ( (*tStr == ' ') && ff ) {
				tStr++;
				continue;
			}
			ff = 0;
			*tStr2++ = *tStr++;
		}
		*tStr2 = 0;
		m_UserVars.m_TitleProgram.ReleaseBuffer();
	}

	tStr = GDUFindString ( GDTTLSM );
	if ( tStr != NULL ) {
		char *tStr2 = m_UserVars.m_TitleScoreMatrix.GetBuffer(128);
		int ff = 1;
		for ( int i = 0; i < 21; ++i ) {
			if ( (*tStr == ' ') && ff ) {
				tStr++;
				continue;
			}
			ff = 0;
			*tStr2++ = *tStr++;
		}
		*tStr2 = 0;
		m_UserVars.m_TitleScoreMatrix.ReleaseBuffer();
	}

	tStr = GDUFindString ( GDTTLOG );
	if ( tStr != NULL ) {
		char *tStr2 = m_UserVars.m_TitleOpenGap.GetBuffer(128);
		int ff = 1;
		for ( int i = 0; i < 21; ++i ) {
			if ( (*tStr == ' ') && ff ) {
				tStr++;
				continue;
			}
			ff = 0;
			*tStr2++ = *tStr++;
		}
		*tStr2 = 0;
		m_UserVars.m_TitleOpenGap.ReleaseBuffer();
	}

	tStr = GDUFindString ( GDTTLEG );
	if ( tStr != NULL ) {
		char *tStr2 = m_UserVars.m_TitleExtendGap.GetBuffer(128);
		int ff = 1;
		for ( int i = 0; i < 21; ++i ) {
			if ( (*tStr == ' ') && ff ) {
				tStr++;
				continue;
			}
			ff = 0;
			*tStr2++ = *tStr++;
		}
		*tStr2 = 0;
		m_UserVars.m_TitleExtendGap.ReleaseBuffer();
	}

	tStr = GDUFindString ( GDSCOREMETH );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ScoringMethod = atoi( DecodeBuff );
		if ( m_UserVars.m_ScoringMethod >= SCORETYPEMAX ) m_UserVars.m_ScoringMethod = SCOREPAIR;
//		m_UserVars.m_ScoringMethod = SCOREPAIR;
	}

	tStr = GDUFindString ( GDPICTWIDTH );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictWidth = atoi( DecodeBuff );
		if ( m_UserVars.m_PictWidth < -9 || m_UserVars.m_PictWidth > 9 ) m_UserVars.m_PictWidth = 0;
	}

	tStr = GDUFindString ( GDPICTHEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictHeight = atoi( DecodeBuff );
		if ( m_UserVars.m_PictHeight < -9 || m_UserVars.m_PictHeight > 9 ) m_UserVars.m_PictHeight = 0;
	}

	tStr = GDUFindString ( GDPICTASCENT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictAscent = atoi( DecodeBuff );
		if ( m_UserVars.m_PictAscent < -9 || m_UserVars.m_PictAscent > 9 ) m_UserVars.m_PictAscent = 0;
	}


	tStr = GDUFindString ( GDSHADEGROUPS );
	if ( tStr != NULL ) {
		tStr++;		// Point to real data.
		int RowCount = 0;
		ShadePairStruct *tSPS;

		// CPtrArray
		// Clear out Old Array
		int count = m_UserVars.m_ShadePairArray.GetSize();
		for ( int i = 0; i < count; ++i ) {
			tSPS = (ShadePairStruct *)m_UserVars.m_ShadePairArray[i];
			delete tSPS;
		}
		m_UserVars.m_ShadePairArray.RemoveAll();

		// Fill in array with new values.
		const char *pc = tStr;
		while ( 1 ) {
			if ((*pc == ' ') || (*pc == 0)) {
				break;
			}
			char *pc2 = DecodeBuff;
			while ( *pc != ',' && (*pc != 0) ) {
				*pc2++ = *pc++;
			}
			// little paranoia code here
			if ( *pc == 0 ) break;
			// Point to next group
			pc++;
			// Copy This Group
			*pc2 = 0;

			tSPS = new ShadePairStruct;
			if ( tSPS == 0 ) {
				AfxMessageBox("getuserdef:new:fail:1");
				return;
			}
			tSPS->RowNum = RowCount + 1;
			strcpy ( tSPS->Group, DecodeBuff );
			m_UserVars.m_ShadePairArray.Add(tSPS);

			RowCount++;
		}
	}

	TopCount = 1;
	// CPtrArray

	while ( 1 ) {
	
		sprintf ( DecodeBuff, "%s%d:", GDPHYLOTREE, TopCount );

		tStr = GDUFindString ( DecodeBuff );
		if ( tStr == NULL ) {
			// Were done!!
			break;
		}
		if ( TopCount == 1 ) {
			// Clear out Old Array
			m_UserVars.m_ParseString.Empty();
		}
		
		tStr++;

		m_UserVars.m_ParseString += tStr;

		TopCount++;
	}


	
	// Do base display vars ...
	GetUserDefaultsDVars(":", &m_UserVars.m_Vars );
	
	// Do Groups ...
	
	int GroupCount = 1;
	CString GroupString;
	
	while ( 1 ) {
	
		_snprintf ( DecodeBuff, sizeof(DecodeBuff), "%c%d:", 'G', GroupCount );
		GroupString = DecodeBuff;

		_snprintf ( DecodeBuff, sizeof(DecodeBuff), "%s%s", 
			GDGROUPNAME, (const char *)GroupString  
		);

		tStr = GDUFindString ( DecodeBuff );
		if ( tStr == NULL ) {
			// All Done Here ..
			break;
		}

		
		tStr++;					// Point to real data.
		// Create a group ...
	
		CDisplayVars *DisplayVars = new CDisplayVars;
		m_UserVars.m_DisplayVars.AddTail( DisplayVars );
	
		// Load User Defaults
		GetIniDisplayVars(DisplayVars);
	
		// Set Group Name
		DisplayVars->SetGroupName( tStr );

		// Get Group Colors

		_snprintf ( DecodeBuff, sizeof(DecodeBuff), "%s%s", GDGROUPINF, (const char *)GroupString );
		tStr = GDUFindString ( DecodeBuff );

		if ( tStr != NULL ) {

			COLORREF TextColor, BkColor;
			int Red, Green, Blue;
	
			tStr++;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Red = atoi( DecodeBuff );
			tStr += 3;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Green = atoi( DecodeBuff );
			tStr += 3;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Blue = atoi( DecodeBuff );
	
			TextColor = RGB ( Red, Green, Blue );
	
			tStr += 3;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Red = atoi( DecodeBuff );
			tStr += 3;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Green = atoi( DecodeBuff );
			tStr += 3;
			memcpy ( DecodeBuff, tStr, 3 );
			DecodeBuff[3] = 0;
			Blue = atoi( DecodeBuff );
			BkColor = RGB ( Red, Green, Blue );
	
			DisplayVars->SetTitleColors( TextColor, BkColor );
		}
		
		// Set Group Sequences ...
		CString GroupSeqs;

		TopCount = 1;

		while ( 1 ) {
		
			_snprintf ( DecodeBuff, sizeof(DecodeBuff), "%s%d%s", GDGROUPSEQ, TopCount, (const char *)GroupString );
	
			tStr = GDUFindString ( DecodeBuff );
			if ( tStr == NULL ) {
				// Were done!!
				break;
			}
			tStr++;
	
			GroupSeqs += tStr;
			
			TopCount++;
	
		}

		CString SeqName;
		
		while ( 1 ) {
			int FLoc;
		
			if ( (FLoc = GroupSeqs.Find(',')) == -1 ) {
				break;
			}
			
			SeqName = GroupSeqs.Left( FLoc );
			
			GroupSeqs = GroupSeqs.Mid( FLoc + 1 );
			
			// Add Sequence .. SeqName

			POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
		
				CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
				if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
					continue;
				}
	
				if ( SeqName == tCGSeg->GetTitle() ) {
	
					// Manage DisplayVars GroupList
					
					// Is it in a group already?
					if ( tCGSeg->m_DisplayGroup != 0 ) {
						int GrpNum = 0;
						CDisplayVars *DisplayVars2;
						POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
						while ( tPos != NULL ) {
							DisplayVars2 = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
							GrpNum++;
							if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
						}
					
						CPtrList *pDVGL = DisplayVars2->GetGroupList();
						
						POSITION oPos = pDVGL->Find( tCGSeg );
						
						if ( oPos != NULL ) pDVGL->RemoveAt( oPos );
						
					}
	
					int GrpNum = 0;
					CDisplayVars *DisplayVars3;
					POSITION tPos2 = m_UserVars.m_DisplayVars.GetHeadPosition();
					while ( tPos2 != NULL ) {
						DisplayVars3 = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos2);
						GrpNum++;
						if ( DisplayVars == DisplayVars3 ) break;
					}
					
					// Check to see if its the same as it was, if so, reset to nogroup.
	
					CPtrList *pDVGL = DisplayVars->GetGroupList();
						
					pDVGL->AddTail( tCGSeg );
						
					tCGSeg->m_DisplayGroup = GrpNum;
	
					break;
				}
				
			}

			// Donme Add Sequence
			
		}
		
		GetUserDefaultsDVars( GroupString, DisplayVars );
		
		GroupCount++;

	}

}




void 
CGenedocDoc::GetUserDefaultsDVars( const CString& AppStr, CDisplayVars* DisplayVars )
{
TRY {
	const char * tStr;
	char DecodeBuff[256];

	// Start of Display Vars ...
	tStr = GDUFindString ( GDPRILEVEL + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 9 );
		DecodeBuff[9] = 0;
		DisplayVars->SetPrimaryLevel( atof( DecodeBuff ) );
	}

	tStr = GDUFindString ( GDSECLEVEL + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 9 );
		DecodeBuff[9] = 0;
		DisplayVars->SetSecondaryLevel( atof( DecodeBuff ) );
	}

	tStr = GDUFindString ( GDTERTLEVEL  + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 9 );
		DecodeBuff[9] = 0;
		DisplayVars->SetTertiaryLevel( atof( DecodeBuff ) );
	}

	tStr = GDUFindString ( GDSHADEMODE  + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetModeConserved( atoi( DecodeBuff ) );
		if ( DisplayVars->GetModeConserved() > SHADEIDENTITY ) 
			DisplayVars->SetModeConserved( SHADECONSERVED );
//		if ( DisplayVars->GetModeConserved() >= SHADESEARCH ) 
//			DisplayVars->SetModeConserved( DisplayVars->GetModeConserved() + 1 );
	}

	tStr = GDUFindString ( GDLASTSHADE  + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetLastShadeLevel( atoi( DecodeBuff ) );
		if ( DisplayVars->GetLastShadeLevel() > SHADELEVEL4 ) {
			if ( DisplayVars->GetLastShadeLevel() > SHADELEVEL4 + 1) {
				DisplayVars->SetResidueMode(1);
			}
			DisplayVars->SetLastShadeLevel( SHADELEVEL4 );
		}
	}

	tStr = GDUFindString ( GDGROUPENABLED + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetGroupEnabled( atoi( DecodeBuff ) );
		if ( DisplayVars->GetGroupEnabled() != 0 ) 
			DisplayVars->SetGroupEnabled( 1 );
	}

	tStr = GDUFindString ( GDDIFFMODE + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetDiffMode( atoi( DecodeBuff ) );
		if ( DisplayVars->GetDiffMode() != 0 ) 
			DisplayVars->SetDiffMode( 1 );
	}

	tStr = GDUFindString ( GDPROPSTYLE + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetPropStyle( atoi( DecodeBuff ) );
		if ( DisplayVars->GetPropStyle() != 0 ) 
			DisplayVars->SetPropStyle( 1);
	}

	tStr = GDUFindString ( GDRESIDUEMODE + AppStr );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		DisplayVars->SetResidueMode( atoi( DecodeBuff ) );
		if ( DisplayVars->GetResidueMode() != 0 ) 
			DisplayVars->SetResidueMode( 1);
	}

	int PropLevelCount = 0;
	int TopCount = 1;
	PropertyStruct *tPS;
	// CPtrArray

	while ( 1 ) {
	
		_snprintf ( DecodeBuff, sizeof(DecodeBuff), "%s%d%d%s", 
			GDPROPGROUPS, PropLevelCount + 1, TopCount, (const char *)AppStr 
		);

		tStr = GDUFindString ( DecodeBuff );
		if ( tStr == NULL ) {
			if ( PropLevelCount >= 3 ) {
				// Were done!!
				break;
			} else {
				PropLevelCount += 1;
				TopCount = 1;
				continue;
			}
		}
		if ( TopCount == 1 ) {
			// Clear out Old Array
			int count = DisplayVars->GetProperty().GetArray(PropLevelCount)->GetSize();
			for ( int i = 0; i < count; ++i ) {
				tPS = (PropertyStruct *)DisplayVars->GetProperty().GetPropertyStruct(PropLevelCount,i);
				delete tPS;
			}
			DisplayVars->GetProperty().GetArray(PropLevelCount)->RemoveAll();
		}
		
		tStr++;					// Point to real data.
		int RowCount = 0;
		tPS = new PropertyStruct;
		if ( tPS == 0 ) {
			AfxMessageBox("getuserdef:new:fail:2");
			return;
		}
		tPS->RowNum = TopCount;
		tPS->TextColor = RGB( 255,255,255);
		tPS->BkColor = RGB(0,0,0);
		// Fill in array with new values.
		char *pc2 = tPS->Group;
		int Limit = MAXPROPERTYGROUP - 1;
		while ( Limit-- ) {
			if ((*tStr == ' ') || (*tStr == 0) || (*tStr == ',' )) {
				break;
			}
			*pc2++ = *tStr++;
		}
		*pc2 = 0;

		// Paranoia check
		if ( *tStr != ',' ) continue;

		int Red, Green, Blue;

		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		tPS->TextColor = RGB ( Red, Green, Blue );

		tStr += 3;
		// Paranoia check
		if ( *tStr != ',' ) continue;

		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		tPS->BkColor = RGB ( Red, Green, Blue );

		DisplayVars->GetProperty().GetArray(PropLevelCount)->Add(tPS);
	
		TopCount++;
	}

	// Do Structure info ...
	tStr = GDUFindString ( GDSTRUCTURE + AppStr );
	if ( tStr != NULL ) {
		// DisplayVars->GetStcGroup().GetMasterSeq(), 
		// DisplayVars->GetStcGroup().GetFileName(), 
		// DisplayVars->GetStcGroup().GetCurrentDataType()
		
		CString rStr(tStr);
		CString dString;
		dString = rStr.Mid( 1, 10 );
		int i;
		for ( i=0; i < dString.GetLength(); ++i ) {
			if ( dString[i] != ' ' ) break;
		}
		dString = dString.Right(dString.GetLength() - i);
		
		if ( !dString.IsEmpty() ) {
			DisplayVars->GetStcGroup().SetMasterSeq( dString );
	
			dString = rStr.Mid( 12, 15 );
			for ( int i=0; i < dString.GetLength(); ++i ) {
				if ( dString[i] != ' ' ) break;
			}
			dString = dString.Right(dString.GetLength() - i);
		}
		
		int lPos = 0;
		char convbuff[10];

		do {		
			CString strLook = CString(GDSTCFNAMES) + CString(_itoa( lPos, convbuff, 10 )) + AppStr;
			
			if ( (tStr = GDUFindString( strLook )) == NULL ) break;

			rStr = tStr + 1;
			
			CString fString;
			int fLoc;

			while ( (fLoc = rStr.Find( ',' )) != -1 ) {
				fString = rStr.Left( fLoc );
				rStr = rStr.Right( rStr.GetLength() - fLoc - 1 );

				char * pc = fString.GetBuffer( fString.GetLength() );
				while ( *pc != 0 ) {
					if ( *pc == '|' ) *pc = '.';
					pc++;
				}
				fString.ReleaseBuffer();
		
				if ( GetDataTypeValuesFile( m_PathName + fString, &DisplayVars->GetStcGroup() ) ) {
					DisplayVars->GetStcGroup().AddFileName( fString );
				}
			}
			
			lPos++;

		} while (1);


		if ( !dString.IsEmpty() ) {
			DisplayVars->GetStcGroup().SetCurrentDataType( dString );

			SetStructureAlignment(DisplayVars);

		}


	}
	// End of Display Vars ...
}
CATCH ( CMemoryException, e )
{
	AfxMessageBox("Memory Exception: GetUserDefaultsDVars");
}
END_CATCH
}


/*

void 
CGenedocDoc::SetUserDefaults( )
{

TRY {

	CPtrList	OrigComments;
	CPtrList	*CommentList = &pGSFiller->SegHeaderList;
	CString *tStr;
	char BuildBuff[256];

	
	while ( !CommentList->IsEmpty() ) {
		tStr = (CString *)CommentList->RemoveHead();
		if ( tStr->Find(GENEDOCIDSTR) != -1 ) {
			delete tStr;
		} else {
			OrigComments.AddTail(tStr);
		}
	}
	
	// Now put back all commentst but the last one.	
	int tCount = OrigComments.GetCount();
	while ( !OrigComments.IsEmpty() ) {
		if ( (--tCount) <= 0 ) {
			break;
		}
		CommentList->AddTail ( OrigComments.RemoveHead() );
	}

	
	// Start with Title String
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s CopyRight 1996, 1997 - Karl Nicholas", GENEDOCIDSTR );
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	// A font string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %5d %s %5d", 
		GENEDOCIDSTR, 
		GDFONTWEIGHT, m_UserVars.m_FontWeight, 
		GDFONTSIZE, m_UserVars.m_FontSize
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	// A foreground colors string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %3d%3d%3d %s %3d%3d%3d", 
		GENEDOCIDSTR, 
		GDFOREPRI, 
			GetRValue(m_UserVars.m_ForeColor100), 
			GetGValue(m_UserVars.m_ForeColor100), 
			GetBValue(m_UserVars.m_ForeColor100), 
		GDFORESEC, 
			GetRValue(m_UserVars.m_ForeColor80), 
			GetGValue(m_UserVars.m_ForeColor80), 
			GetBValue(m_UserVars.m_ForeColor80)
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	// A foreground colors string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %3d%3d%3d %s %3d%3d%3d", 
		GENEDOCIDSTR, 
		GDFORETERT, 
			GetRValue(m_UserVars.m_ForeColor60), 
			GetGValue(m_UserVars.m_ForeColor60), 
			GetBValue(m_UserVars.m_ForeColor60), 
		GDFOREBASE, 
			GetRValue(m_UserVars.m_ForeColor0), 
			GetGValue(m_UserVars.m_ForeColor0), 
			GetBValue(m_UserVars.m_ForeColor0) 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// A background colors string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %3d%3d%3d %s %3d%3d%3d", 
		GENEDOCIDSTR, 
		GDBACKPRI, 
			GetRValue(m_UserVars.m_BackColor100), 
			GetGValue(m_UserVars.m_BackColor100), 
			GetBValue(m_UserVars.m_BackColor100), 
		GDBACKSEC, 
			GetRValue(m_UserVars.m_BackColor80), 
			GetGValue(m_UserVars.m_BackColor80), 
			GetBValue(m_UserVars.m_BackColor80)
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// A background colors string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %3d%3d%3d %s %3d%3d%3d", 
		GENEDOCIDSTR, 
		GDBACKTERT, 
			GetRValue(m_UserVars.m_BackColor60), 
			GetGValue(m_UserVars.m_BackColor60), 
			GetBValue(m_UserVars.m_BackColor60), 
		GDBACKBASE, 
			GetRValue(m_UserVars.m_BackColor0), 
			GetGValue(m_UserVars.m_BackColor0), 
			GetBValue(m_UserVars.m_BackColor0) 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// A Borders string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %6.3f %s %6.3f", 
		GENEDOCIDSTR, 
		GDLEFTBORD, m_UserVars.m_LeftBorder,
		GDRIGHTBORD, m_UserVars.m_RightBorder
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// A Borders string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %6.3f %s %6.3f", 
		GENEDOCIDSTR, 
		GDTOPBORD, m_UserVars.m_TopBorder,
		GDBOTTOMBORD, m_UserVars.m_BottomBorder
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// A Print string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %s", 
		GENEDOCIDSTR, 
		GDPRINTSTRING, m_UserVars.m_PrintString 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// Another various Print flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %1d %s %1d %s %4d", 
		GENEDOCIDSTR, 
		GDPRINTSTRINGFLAG, m_UserVars.m_PrintStringFlag, 
		GDPRINTPAGENUMBER, m_UserVars.m_PrintPageNumber, 
		GDPRINTPAGEOFFSET, m_UserVars.m_PrintPageOffset 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// A Print font string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %5d %s %5d %s %1d", 
		GENEDOCIDSTR, 
		GDPRINTFONTWEIGHT, m_UserVars.m_PrintFontWeight, 
		GDPRINTFONTSIZE, m_UserVars.m_PrintFontSize, 
		GDPRINTGENEBLOCK, m_UserVars.m_PrintGeneBlock 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	// A Print font string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %s", 
		GENEDOCIDSTR, 
		GDPRINTFONTNAME, m_UserVars.m_PrintFontName 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// A various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %1d %s %5d %s %1d", 
		GENEDOCIDSTR, 
		GDWIDTHMODE, m_UserVars.m_WidthMode, 
		GDFIXEDX, m_UserVars.m_FixedXSize, 
		GDSCORETABLE, m_UserVars.m_CurrentScoreTable
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %2d %s %2d %s %2d", 
		GENEDOCIDSTR, 
		GDPICTWIDTH, m_UserVars.m_PictWidth, 
		GDPICTHEIGHT, m_UserVars.m_PictHeight, 
		GDPICTASCENT, m_UserVars.m_PictAscent
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %20s %s %20s", 
		GENEDOCIDSTR, 
		GDTTLPROG, m_UserVars.m_TitleProgram, 
		GDTTLSM, m_UserVars.m_TitleScoreMatrix 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %20s %s %20s", 
		GENEDOCIDSTR, 
		GDTTLOG, m_UserVars.m_TitleOpenGap, 
		GDTTLEG, m_UserVars.m_TitleExtendGap 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


//	CPtrArray	m_ShadePairArray;		// Hoding a list of ShadePairStruct's
	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s ", 
		GENEDOCIDSTR, GDSHADEGROUPS );
	
	int Count = m_UserVars.m_ShadePairArray.GetSize();
	for ( int i =0; i < Count; ++i ) {
		strcat ( BuildBuff, (char *)((ShadePairStruct *)m_UserVars.m_ShadePairArray[i])->Group );
		strcat ( BuildBuff, "," );
	}
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	Count = m_UserVars.m_ParseString.GetLength();
	for ( i = 0; i < Count; i += 50 ) {
		int Amount = 50;
		if ( i + Amount > Count ) {
			Amount = Count - i;
		}
		// Another various flags string
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d: %s", 
			GENEDOCIDSTR, 
			GDPHYLOTREE, (i/50)+1, 
			(const char *)m_UserVars.m_ParseString.Mid(i, Amount)
		);
		tStr = new CString(BuildBuff);
		CommentList->AddTail( tStr );

	}

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %1d %s %1d %s %1d", 
		GENEDOCIDSTR, 
		GDCONSENSUS, m_UserVars.m_ConsensusLine, 
		GDSHOWTAIL, m_UserVars.m_ShowTail, 
		GDORIENTATION, m_UserVars.m_Orientation
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %1d %s %1d %s %1d", 
		GENEDOCIDSTR, 
		GDGAPIND, m_UserVars.m_GapInd, 
		GDPROJTYPE, m_UserVars.m_ProjectType, 
		GDSCOREMETH, m_UserVars.m_ScoringMethod 

	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %1d %s %1d", 
		GENEDOCIDSTR, 
		GDGROUPDISPMODE, m_UserVars.m_GroupDisplayMode, 
		GDCOLORSEQNAMES, m_UserVars.m_ColorSeqNames 
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %s,%s,%s,", 
		GENEDOCIDSTR, GDAUTOSSTC, 
		(const char *)m_UserVars.m_AutoShade4Structure, 
		(const char *)m_UserVars.m_AutoShade3Structure, 
		(const char *)m_UserVars.m_AutoShade2Structure
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );
	
	// marker flags
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %c%6d%6d%6d%1d%c%d%d%d", 
		GENEDOCIDSTR, GDMARKER, 
		m_UserVars.m_MarkerSymb, m_UserVars.m_MarkerSpacing, 
		m_UserVars.m_MarkerReplace, 
		m_UserVars.m_MarkerStart, m_UserVars.m_MarkerEnable, 
		m_UserVars.m_ConservedGap, 
		m_UserVars.m_ResidueUpper, 
		m_UserVars.m_ChemPropCysteine, 
		m_UserVars.m_ChemPropShowProp  
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// marker flags
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s %02d", 
		GENEDOCIDSTR, GDNAMESIND, 
		m_UserVars.m_MaxNameLength  
	);

	char pszConv[32];

	for ( i = 0; i < (int)strlen(m_UserVars.m_strLead); ++i ) {
		_snprintf ( pszConv, 32, "%c%c", (m_UserVars.m_strLead[i] / 16) + 'A', (m_UserVars.m_strLead[i] % 16) + 'A' );
		strcat( BuildBuff, pszConv );
	}

	strcat( BuildBuff, "AA" );

	for ( i = 0; i < (int)strlen(m_UserVars.m_strTail); ++i ) {
		_snprintf ( pszConv, 32, "%c%c", (m_UserVars.m_strTail[i] / 16) + 'A', (m_UserVars.m_strTail[i] % 16) + 'A' );
		strcat( BuildBuff, pszConv );
	}

	strcat( BuildBuff, "AA" );

	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );

	// PCR Settings
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%6.2f%20s%6.2f", 
		GENEDOCIDSTR, GDPCRSET, 
		m_UserVars.m_GroupConsLevel, 
		(const char *)m_UserVars.m_PCRSimilarities, 
		m_UserVars.m_PCRLevel
	);
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	CString strChemProp;
	char *tpc = strChemProp.GetBuffer(3*3*2*15+10);
	tpc[0] = 0;
	char tpc2[20];
	// RGB
	for ( i=0; i <12; ++i ) {
		sprintf(tpc2, "%03d%03d%03d%03d%03d%03d", 
			GetRValue(m_UserVars.ChemGroupOxi[i].TextColor), 
			GetGValue(m_UserVars.ChemGroupOxi[i].TextColor), 
			GetBValue(m_UserVars.ChemGroupOxi[i].TextColor), 
			GetRValue(m_UserVars.ChemGroupOxi[i].BackColor), 
			GetGValue(m_UserVars.ChemGroupOxi[i].BackColor), 
			GetBValue(m_UserVars.ChemGroupOxi[i].BackColor)
		);
		strcat(tpc, tpc2);
	}
	for ( i=0; i <3; ++i ) {
		sprintf(tpc2, "%03d%03d%03d%03d%03d%03d", 
			GetRValue(m_UserVars.ChemCons[i].TextColor), 
			GetGValue(m_UserVars.ChemCons[i].TextColor), 
			GetBValue(m_UserVars.ChemCons[i].TextColor), 
			GetRValue(m_UserVars.ChemCons[i].BackColor), 
			GetGValue(m_UserVars.ChemCons[i].BackColor), 
			GetBValue(m_UserVars.ChemCons[i].BackColor)
		);
		strcat(tpc, tpc2);
	}
	strChemProp.ReleaseBuffer();
	Count = strChemProp.GetLength();
	for ( i = 0; i < Count; i += 50 ) {
		int Amount = 50;
		if ( i + Amount > Count ) {
			Amount = Count - i;
		}
		// Another various flags string
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d: %s", 
			GENEDOCIDSTR, 
			GDCHEMPROP, (i/50)+1, 
			(const char *)strChemProp.Mid(i, Amount)
		);
		tStr = new CString(BuildBuff);
		CommentList->AddTail( tStr );

	}


	int RPos = 0;
	const CStringList& strList = m_UserVars.m_StcDefUser;
	Count = strList.GetCount();
	POSITION tPos = strList.GetHeadPosition();
	do {
		int Round = Count > 3 ? 3 : Count;
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d: ", 
			GENEDOCIDSTR, GDSTCDEFUSER, RPos
		);
		tStr = new CString(BuildBuff);
		for (int j=0; j < Round; ++j ) {
			*tStr += strList.GetNext(tPos) + ",";
		}
		char * pc = tStr->GetBuffer( tStr->GetLength() );
		while ( *pc != 0 ) {
			if ( *pc == '.' ) *pc = '|';
			pc++;
		}
		tStr->ReleaseBuffer();
		CommentList->AddTail( tStr );
		Count -= Round;
		RPos++;

	} while (Count);

	
	
	// m_Stc has already been loaded ..
	SetUserDefaultsDVars( ":", &m_UserVars.m_Vars );

	// Now Do Groups..
	// CPtrList
	int GroupCount = 1;
	
	CString CurrentGroup;
	CString GroupString;

	tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	
	while ( tPos != NULL ) {

		CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);

		CurrentGroup = DisplayVars->GetGroupName();
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%c%d:", 'G', GroupCount );
		GroupString = BuildBuff;

		// Add GroupName String
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %s", 
			GENEDOCIDSTR, GDGROUPNAME, 
			(const char *)GroupString, 
			(const char *)CurrentGroup 
		);
		tStr = new CString(BuildBuff);
		if ( tStr == 0 ) {
			AfxMessageBox("SetUserDefaults:new:fail:14");
			return;
		}
		CommentList->AddTail( tStr );

		COLORREF TextColor, BkColor;
		DisplayVars->GetTitleColors( &TextColor, &BkColor );

		// A foreground colors string
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %3d%3d%3d%3d%3d%3d", 
			GENEDOCIDSTR, GDGROUPINF, (const char *)GroupString, 
			GetRValue(TextColor), 
			GetGValue(TextColor), 
			GetBValue(TextColor), 
			GetRValue(BkColor), 
			GetGValue(BkColor), 
			GetBValue(BkColor)
		);
		tStr = new CString(BuildBuff);
		CommentList->AddTail( tStr );

		
		// Put Sequences ...
		CPtrList* SeqGroupList = (CPtrList*) DisplayVars->GetGroupList();
		
		// Lets reuse currentgroup string
		CurrentGroup.Empty();

		POSITION tPos = SeqGroupList->GetHeadPosition();
		while (tPos != NULL ) {
		
			CGeneSegment *tCGSeg = (CGeneSegment *)SeqGroupList->GetNext(tPos);
		
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
		
			// CComboBox
			CurrentGroup += tCGSeg->GetTitle() + ',';

		}

		Count = CurrentGroup.GetLength();
		for ( i = 0; i < Count; i += 50 ) {
			int Amount = 50;
			if ( i + Amount > Count ) {
				Amount = Count - i;
			}
			// Another various flags string
			_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d%s %s", 
				GENEDOCIDSTR, 
				GDGROUPSEQ, (i/50)+1, (const char *)GroupString, 
				(const char *)CurrentGroup.Mid(i, Amount)
			);
			tStr = new CString(BuildBuff);
			CommentList->AddTail( tStr );
	
		}

		
		// Do all the rest of the group vars ...
		
		SetUserDefaultsDVars( GroupString, DisplayVars );
		
		GroupCount++;
	}
	

	// Put an empty string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s", GENEDOCIDSTR );
	tStr = new CString(BuildBuff);
	CommentList->AddTail( tStr );


	// Put the last comment back on	
	while ( !OrigComments.IsEmpty() ) {
		CommentList->AddTail ( OrigComments.RemoveHead() );
	}
	
//	Static for Now ...
//	CPtrArray	m_ScoreTableArray;
}
CATCH ( CMemoryException, e )
{
	AfxMessageBox("Memory Exception: SetUserDefaults");
}
END_CATCH
}

void 
CGenedocDoc::SetUserDefaultsDVars( const CString& AppStr, CDisplayVars* DisplayVars )
{

TRY {

	CString *tStr;
	char BuildBuff[256];
	CPtrList	*CommentList = &pGSFiller->SegHeaderList;
	int Count, i;

	// A Shade Levels String
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %6.2f %s%s %6.2f %s%s %6.2f", 
		GENEDOCIDSTR, 
		GDPRILEVEL, (const char *)AppStr, DisplayVars->GetPrimaryLevel(), 
		GDSECLEVEL, (const char *)AppStr, DisplayVars->GetSecondaryLevel(), 
		GDTERTLEVEL, (const char *)AppStr, DisplayVars->GetTertiaryLevel() 
	);
	tStr = new CString(BuildBuff);
	if ( tStr == 0 ) {
		AfxMessageBox("SetUserDefaults:new:fail:8");
		return;
	}
	CommentList->AddTail( tStr );

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %1d %s%s %1d %s%s %1d", 
		GENEDOCIDSTR, 
		GDSHADEMODE, (const char *)AppStr, DisplayVars->GetModeConserved(), 
		GDGROUPENABLED, (const char *)AppStr, DisplayVars->GetGroupEnabled(),
		GDLASTSHADE, (const char *)AppStr, DisplayVars->GetLastShadeLevel() 
	);
	tStr = new CString(BuildBuff);
	if ( tStr == 0 ) {
		AfxMessageBox("SetUserDefaults:new:fail:12");
		return;
	}
	CommentList->AddTail( tStr );

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %1d %s%s %1d %s%s %1d", 
		GENEDOCIDSTR, 
		GDDIFFMODE, (const char *)AppStr, DisplayVars->GetDiffMode(), 
		GDPROPSTYLE, (const char *)AppStr, DisplayVars->GetPropStyle(), 
		GDRESIDUEMODE, (const char *)AppStr, DisplayVars->GetResidueMode() 
	);
	tStr = new CString(BuildBuff);
	if ( tStr == 0 ) {
		AfxMessageBox("SetUserDefaults:new:fail:14");
		return;
	}
	CommentList->AddTail( tStr );


	//	CPtrArray	m_PropertyArray
	// Hoding a list of PropertyStruct's
	// Another various flags string
	
	PropertyStruct *tPS;
	
	for ( int PropLevelCount = 0; PropLevelCount < 3; ++PropLevelCount ) {
	
		Count = DisplayVars->GetProperty().GetArray(PropLevelCount)->GetSize();
		for ( i =0; i < Count; ++i ) {
			tPS = DisplayVars->GetProperty().GetPropertyStruct(PropLevelCount,i);
			_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d%d%s %s,%3d%3d%3d,%3d%3d%3d", 
				GENEDOCIDSTR, GDPROPGROUPS, PropLevelCount + 1, i + 1, (const char *)AppStr, tPS->Group, 
				GetRValue ( tPS->TextColor ), 
				GetGValue ( tPS->TextColor ), 
				GetBValue ( tPS->TextColor ), 
				GetRValue ( tPS->BkColor ), 
				GetGValue ( tPS->BkColor ), 
				GetBValue ( tPS->BkColor )
			);
	
			tStr = new CString(BuildBuff);
			if ( tStr == 0 ) {
				AfxMessageBox("SetUserDefaults:new:fail:15");
				return;
			}
			CommentList->AddTail( tStr );
		}
	}	

	// Save Structure Info ...

	// Another various flags string
	_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%s %10s %15s", 
		GENEDOCIDSTR, GDSTRUCTURE, (const char *)AppStr, 
		(const char *)DisplayVars->GetStcGroup().GetMasterSeq(), 
		(const char *)DisplayVars->GetStcGroup().GetCurrentDataType() 
	);
	tStr = new CString(BuildBuff);
	if ( tStr == 0 ) {
		AfxMessageBox("SetUserDefaults:new:fail:21");
		return;
	}
	CommentList->AddTail( tStr );


	int RPos = 0;
	const CStringList& strList = DisplayVars->GetStcGroup().GetFileNames();
	Count = strList.GetCount();
	POSITION tPos = strList.GetHeadPosition();
	do {
		int Round = Count > 3 ? 3 : Count;
		_snprintf ( BuildBuff, sizeof(BuildBuff), "%s %s%d%s ", 
			GENEDOCIDSTR, GDSTCFNAMES, RPos, (const char *)AppStr 
		);
		tStr = new CString(BuildBuff);
		for (int j=0; j < Round; ++j ) {
			*tStr += strList.GetNext(tPos) + ",";
		}
		char * pc = tStr->GetBuffer( tStr->GetLength() );
		while ( *pc != 0 ) {
			if ( *pc == '.' ) *pc = '|';
			pc++;
		}
		tStr->ReleaseBuffer();
		CommentList->AddTail( tStr );
		Count -= Round;
		RPos++;

	} while (Count);

	// End Display Vars
	
}
CATCH ( CMemoryException, e )
{
	AfxMessageBox("Memory Exception: SetUserDefaultsDVars");
}
END_CATCH
}

*/
