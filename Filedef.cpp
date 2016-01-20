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



UserVars sUserVars;
DisplayVars sDisplayVars;
UserVars iUserVars;


typedef struct {
	void *pData;
	int iType;
} stcEncodeVars;

BOOL UseGSFiller;

extern stcEncodeVars EncodeBaseVars[];
extern stcEncodeVars EncodeDisplayVars[];

CGenedocDoc *gpDoc;

int EncodeVars ( CString& strCode, stcEncodeVars * CodeVars );
int DecodeVars ( CString& strCode, stcEncodeVars * CodeVars, int iSLoc );

void 
CGenedocDoc::GetNewUserDefaults( )
{

	CString strDef;
	CPtrList	*CommentList = &pGSFiller->SegHeaderList;
	CString *tStr;

	#define GDCSTR	"GDC " 

	// Need this to get init vars ..
	CopyUserVars( &sUserVars, &m_UserVars );
	// But clear the lists out 
	ClearUserVars( &sUserVars );
	
	POSITION tPos = CommentList->GetHeadPosition();
	while ( tPos != NULL ) {
		tStr = (CString *)CommentList->GetNext(tPos);
		int FindLoc;
		if ( (FindLoc = tStr->Find(GDCSTR)) != -1 ) {
			if ( tStr->Find("GeneDoc Multiple Sequence Alignment") != -1 ) continue;
			strDef += tStr->Mid( 4, 60 );
		}
	}
	
	gpDoc = this;

	int iSLoc = 0;
	int iSCount = strDef.GetLength();

	while ( iSLoc < iSCount ) {
		int	iRecId;
		iRecId = 10 * (strDef[iSLoc++] - '0');
		iRecId += strDef[iSLoc++] - '0';

		// If iRecId == 1 then its a 4 digit (2 byte ) length record
		// else it is a 8 digit (4 byte) length record
		int iRecLen;
		UINT i;
		char cLen[9];

		switch ( iRecId ) {
		case 1:	// Base Vars
		case 2: // Base Display Vars
		case 3: // User Defined Display Vars
			for ( i=0; i < 4; ++i ) cLen[i] = strDef[iSLoc++];
			cLen[i] = 0;
			iRecLen = (int)strtol( cLen, NULL, 16 );
			break;
		case 4:	// Base Vars
		case 5: // Base Display Vars
		case 6: // User Defined Display Vars
			for ( i=0; i < 8; ++i ) cLen[i] = strDef[iSLoc++];
			cLen[i] = 0;
			iRecLen = (int)strtol( cLen, NULL, 16 );
			break;
		}

		CString strRec = strDef.Mid( iSLoc, iRecLen );

//		strDef = strDef.Right(iSCount - (iRecLen + 6) );

		switch ( iRecId ) {
		case 1:	// Base Vars
		case 4:	// Base Vars
			DecodeVars ( strRec, EncodeBaseVars, 0 );
			iSLoc += strRec.GetLength();
			break;
		case 2: // Base Display Vars
		case 5: // Base Display Vars
			{
				// PreInit DisplayVars
				GetIniDisplayVars(&iUserVars.m_Vars);
				sUserVars.m_Vars.CopyDisplayVars( &sDisplayVars, &iUserVars.m_Vars, this );
				sUserVars.m_Vars.ClearVars(&sDisplayVars);
				ClearUserVars( &iUserVars );

				DecodeVars ( strRec, EncodeDisplayVars, 0 );
				iSLoc += strRec.GetLength();
				const CString& CurType = sDisplayVars.m_StcGroup.GetCurrentDataType();
				sUserVars.m_Vars.SetDisplayVars ( &sDisplayVars, this );
				sUserVars.m_Vars.GetStcGroup().SetCurrentDataType(CurType, 1 );

			}
			break;
		case 3: // User Defined Display Vars
		case 6: // User Defined Display Vars
			{
				// PreInit Display Vars
				GetIniDisplayVars(&iUserVars.m_Vars);
				sUserVars.m_Vars.CopyDisplayVars( &sDisplayVars, &iUserVars.m_Vars, this );
				sUserVars.m_Vars.ClearVars(&sDisplayVars);
				ClearUserVars( &iUserVars );

				DecodeVars ( strRec, EncodeDisplayVars, 0 );
				iSLoc += strRec.GetLength();
				const CString& CurType = sDisplayVars.m_StcGroup.GetCurrentDataType();
				CDisplayVars *pDV = new CDisplayVars;
				GetIniDisplayVars(pDV);
				pDV->SetDisplayVars ( &sDisplayVars, this );
				pDV->GetStcGroup().SetCurrentDataType(CurType, 1);
				sUserVars.m_DisplayVars.AddTail( pDV );
			}
			break;
		}
	}

	// Restore Old Storage..
	sUserVars.m_Vars.CopyDisplayVars( &sDisplayVars, &sUserVars.m_Vars, this );
	// Remove Old Storage ..
	ClearUserVars( &m_UserVars );
	CopyUserVars( &m_UserVars, &sUserVars);
	// Some More Things ..
	tPos = m_UserVars.m_StcDefUser.GetHeadPosition();
	while ( tPos != NULL ) {
		CString& StcFile = m_UserVars.m_StcDefUser.GetNext(tPos);
		LoadUserSduFile( m_PathName + StcFile );
	}

	const CString& CurType = sUserVars.m_Vars.GetStcGroup().GetCurrentDataType();
	CStcGroup& StcGroup = m_UserVars.m_Vars.GetStcGroup();
	const CStringList& StcFileNames = StcGroup.GetFileNames();
	POSITION fPos = StcFileNames.GetHeadPosition();
	while ( fPos != NULL ) {
		const CString& fString = StcFileNames.GetNext(fPos);
		GetDataTypeValuesFile( m_PathName + fString, &m_UserVars.m_Vars.GetStcGroup() );
	}
	m_UserVars.m_Vars.GetStcGroup().SetCurrentDataType(CurType);
	if ( m_UserVars.m_GroupDisplayMode == 0 ) {
		SetStructureAlignment(&m_UserVars.m_Vars);
	}

	int GrpNum = 1;
	tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	POSITION oPos = sUserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars * pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		CDisplayVars * pDVo = (CDisplayVars *)sUserVars.m_DisplayVars.GetNext(oPos);
		const CString& CurType = pDVo->GetStcGroup().GetCurrentDataType();
		CStcGroup& StcGroup = pDV->GetStcGroup();
		const CStringList& StcFileNames = StcGroup.GetFileNames();
		POSITION fPos = StcFileNames.GetHeadPosition();
		while ( fPos != NULL ) {
			const CString& fString = StcFileNames.GetNext(fPos);
			GetDataTypeValuesFile( m_PathName + fString, &pDV->GetStcGroup() );
		}
		pDV->GetStcGroup().SetCurrentDataType(CurType);
		if ( m_UserVars.m_GroupDisplayMode != 0 ) {
			SetStructureAlignment(pDV);
		}

		CPtrList *pGList = pDV->GetGroupList();
		POSITION gPos = pGList->GetHeadPosition();
		while ( gPos != NULL ) {
			CGeneSegment *pCGSeg = (CGeneSegment *)pGList->GetNext( gPos );
			pCGSeg->m_DisplayGroup = GrpNum;
		}
		GrpNum++;
	}

	ClearUserVars( &sUserVars );

//	AutoShade(-1);
}

//		int GrpNum = 1;
//		POSITION tPos2 = sUserVars.m_DisplayVars.GetHeadPosition();
//		while ( tPos2 != NULL ) {
//			sUserVars.m_DisplayVars.GetNext(tPos2);
//			GrpNum++;
//		}
//		tCGSeg->m_DisplayGroup = GrpNum;


/*
//CStdioFile wFile;
//#define WBUG(ostr) wFile.Open( "debug.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText );\
//wFile.SeekToEnd(); \
//wFile.WriteString( ostr );\
//wFile.Close();
*/
#define WBUG(ostr)

void 
CGenedocDoc::SetUserDefaults( )
{

//wFile.Open( "debug.txt", CFile::modeWrite | CFile::typeText | CFile::modeCreate );
//CString strDebug;
//strDebug.Format(" PhyloSize = %d, PhyloAddr = %x, Phylo = %s\n", 
//		m_UserVars.m_ParseString.GetLength(), 
//		&m_UserVars.m_ParseString, 
//		m_UserVars.m_ParseString 
//);
//wFile.WriteString( strDebug );
//wFile.Close();

	gpDoc = this;


WBUG( "Debug 1\n")
	
	CopyUserVars( &sUserVars, &m_UserVars );
WBUG( "Debug 2\n")

/*
//wFile.Open( "debug.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText );
//strDebug.Format(" PhyloSize = %d, PhyloAddr = %x, Phylo = %s\n", 
//		sUserVars.m_ParseString.GetLength(), 
//		&sUserVars.m_ParseString, 
//		sUserVars.m_ParseString 
//);
//wFile.SeekToEnd(); \
//wFile.WriteString( strDebug );
//wFile.Close();
*/
	CString cCodeVars;

	cCodeVars += "0400000000";		// Add in Record ID and Length placement holder.
	int PlaceHold = 10;

	int Length = EncodeVars( cCodeVars, EncodeBaseVars );

WBUG( "Debug 3\n")
	// Fill out length placement holder
	char conv[10];
	_itoa( Length, conv, 16 );
	conv[8] = 0;
	UINT i;
	
	for ( i = 8; i > strlen(conv); --i ) cCodeVars.SetAt(PlaceHold-i,'0');
	for (UINT j = 0; j < strlen(conv); ++j ) cCodeVars.SetAt(PlaceHold-i+j,conv[j]);

WBUG( "Debug 4\n")
	PlaceHold += Length + 10;
	cCodeVars += "0500000000";		// Add in Record ID for def DisplayVars + length placehold

	// Some silly stuff to get access to private variables ...
	m_UserVars.m_Vars.CopyDisplayVars ( &sDisplayVars, &m_UserVars.m_Vars, this );
WBUG( "Debug 5\n")


/*
//wFile.Open( "debug.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText );
//strDebug.Format(" PhyloSize = %d, PhyloAddr = %x, Phylo = %s\n", 
//		sUserVars.m_ParseString.GetLength(), 
//		&sUserVars.m_ParseString, 
//		sUserVars.m_ParseString 
//);
//wFile.SeekToEnd(); \
//wFile.WriteString( strDebug );
//wFile.Close();                
*/

	Length = EncodeVars( cCodeVars, EncodeDisplayVars );

WBUG( "Debug 6\n")
	// Fill out length placement holder
	_itoa( Length, conv, 16 );
	conv[8] = 0;
	UINT j;
	for ( i = 8; i > strlen(conv); --i ) cCodeVars.SetAt(PlaceHold-i,'0');
	for ( j = 0; j < strlen(conv); ++j ) cCodeVars.SetAt(PlaceHold-i+j,conv[j]);

WBUG( "Debug 7\n")

	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	
	while ( tPos != NULL ) {

WBUG( "Debug 8\n")
		CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
WBUG( "Debug 9\n")
		DisplayVars->CopyDisplayVars ( &sDisplayVars, DisplayVars, this );
WBUG( "Debug 10\n")
	
		PlaceHold += Length + 10;
		cCodeVars += "0600000000";		// Add in Record ID for def DisplayVars + length placehold

		Length = EncodeVars( cCodeVars, EncodeDisplayVars );

WBUG( "Debug 11\n")
		// Fill out length placement holder
		_itoa( Length, conv, 16 );
		conv[8] = 0;
		for ( i = 8; i > strlen(conv); --i ) cCodeVars.SetAt(PlaceHold-i,'0');
		for ( j = 0; j < strlen(conv); ++j ) cCodeVars.SetAt(PlaceHold-i+j,conv[j]);

WBUG( "Debug 12\n")
	}


WBUG( "Debug 13\n")
	// Remove Storage ..
	ClearUserVars( &sUserVars );

//	GetNewUserDefaults( cCodeVars );


	CPtrList	OrigComments;
	CPtrList	*CommentList;
	CString *tStr;

WBUG( "Debug 14\n")
	#define GENEDOCIDSTR	"GENEDOC:" 
	#define GDCSTR	"GDC " 
	char BuildBuff[256];

	
WBUG( "Debug 15\n")

	if ( pGSFiller != NULL ) {
		CommentList = &pGSFiller->SegHeaderList;

		while ( !CommentList->IsEmpty() ) {
			tStr = (CString *)CommentList->RemoveHead();
			if ( tStr->Find(GENEDOCIDSTR) != -1 ) {
				delete tStr;
			} else if ( tStr->Find(GDCSTR) != -1 ) {
				delete tStr;
			} else {
				OrigComments.AddTail(tStr);
			}
		}
	WBUG( "Debug 16\n")
		
		// Now put back all commentst but the last one.	
		int tCount = OrigComments.GetCount();
		while ( !OrigComments.IsEmpty() ) {
			if ( (--tCount) <= 0 ) {
				break;
			}
			CommentList->AddTail ( OrigComments.RemoveHead() );
		}

		CommentList->AddTail ( new CString( "GDC ******** GeneDoc Multiple Sequence Alignment Editor ********") );

	WBUG( "Debug 17\n")
		UINT Count = cCodeVars.GetLength();
		for (int i = 0; i < Count; i += 60 ) {
			int Amount = 60;
			if ( i + Amount > Count ) {
				Amount = Count - i;
			}
			// Another various flags string
			_snprintf ( BuildBuff, sizeof(BuildBuff), "%s%s", GDCSTR, (const char *)cCodeVars.Mid(i, Amount) );
			tStr = new CString(BuildBuff);
			CommentList->AddTail( tStr );

		}

	WBUG( "Debug 18\n")
		// Put the last comment back on	
		while ( !OrigComments.IsEmpty() ) {
			CommentList->AddTail ( OrigComments.RemoveHead() );
		}
	WBUG( "Debug 19\n")
	}

}




enum {
	STOREINT, 
	STORECOLOR, 
	STOREDOUBLE, 
	STORESTRING, 
	STOREFLAG, 
	STORECHAR, 
	STORESHADEPAIR, 
	STORECHEMPROP12, 
	STORECHEMPROP3, 
	STOREFILELIST,
	STOREPROPERTY, 
	STORESTRUCTURE, 
	STORESEQNAMES, 
	STORESEARCH, 
	STORESEQSTART, 
	STORESEENAB, 
	STORELOGODDS, 
	STORESEQDESCR, 
	STORECPAIR, 
	STORECOMMENT, 
	STOREDWORD, 
	STORECPAIR2, 
	STORECOMMENT2,  
	STORESEQDESCR2  
};

int EncodeShadePair(CString& strCode, stcEncodeVars * CodeVars );
int EncodeChemProp(CString& strCode, stcEncodeVars * CodeVars, UINT count );
int EncodeFileList(CString& strCode, stcEncodeVars * CodeVars );
int EncodeProperty(CString& strCode, stcEncodeVars * CodeVars );
int EncodeStructure(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSeqNames(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSearch(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSeqStart(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSeEnab(CString& strCode, stcEncodeVars * CodeVars );
int EncodeLogOdds(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSeqDescr(CString& strCode, stcEncodeVars * CodeVars );
int EncodeCPAIR(CString& strCode, stcEncodeVars * CodeVars );
int EncodeComment(CString& strCode, stcEncodeVars * CodeVars );
int EncodeCPAIR2(CString& strCode, stcEncodeVars * CodeVars );
int EncodeComment2(CString& strCode, stcEncodeVars * CodeVars );
int EncodeSeqDescr2(CString& strCode, stcEncodeVars * CodeVars );

int DecodeShadePair(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeChemProp(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeFileList(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeProperty(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeStructure(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSeqNames(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSearch(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSeqStart(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSeEnab(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeLogOdds(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSeqDescr(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeCPAIR(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeComment(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeCPAIR2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeComment2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );
int DecodeSeqDescr2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc );

stcEncodeVars EncodeDisplayVars[] = {
	{ &sDisplayVars.m_GroupEnabled,		STOREFLAG },
	{ &sDisplayVars.m_PrimaryLevel,		STOREDOUBLE },
	{ &sDisplayVars.m_SecondaryLevel,	STOREDOUBLE }, 
	{ &sDisplayVars.m_TertiaryLevel,	STOREDOUBLE }, 
	{ &sDisplayVars.m_ModeConserved,	STORECHAR }, 
	{ &sDisplayVars.m_LastShadeLevel,	STOREFLAG }, 
	{ &sDisplayVars.m_ResidueMode,		STOREFLAG }, 
	{ &sDisplayVars.m_DiffMode,			STOREFLAG }, 
	{ &sDisplayVars.m_PropStyle,		STOREFLAG }, 
	{ &sDisplayVars.m_TitleTextColor,	STORECOLOR }, 
	{ &sDisplayVars.m_TitleBkColor,		STORECOLOR }, 
	{ &sDisplayVars.m_Property,			STOREPROPERTY }, 
	{ &sDisplayVars.m_StcGroup,			STORESTRUCTURE }, 
	{ &sDisplayVars.m_GroupName,		STORESTRING }, 
	{ &sDisplayVars.m_GroupList,		STORESEQNAMES }, 
	{ &sDisplayVars.m_ConsSubStyle,		STOREFLAG }, 
	{ &sDisplayVars.m_IdentTextColor,	STORECOLOR }, 
	{ &sDisplayVars.m_IdentBkColor,		STORECOLOR }, 
	{ &sDisplayVars.m_IdentList,		STORESEQNAMES }, 
	{ &sDisplayVars.m_IdentDisplayStyle,STOREFLAG }, 
	{ NULL, 0 } 
};

stcEncodeVars EncodeBaseVars[] = {
	{&sUserVars.m_FontWeight,				STOREINT },
	{&sUserVars.m_FontSize,					STOREINT },
	{&sUserVars.m_ForeColor100,				STORECOLOR },
	{&sUserVars.m_ForeColor80,				STORECOLOR },
	{&sUserVars.m_ForeColor60,				STORECOLOR },
	{&sUserVars.m_ForeColor0,				STORECOLOR },
	{&sUserVars.m_BackColor100,				STORECOLOR },
	{&sUserVars.m_BackColor80,				STORECOLOR },
	{&sUserVars.m_BackColor60,				STORECOLOR },
	{&sUserVars.m_BackColor0,				STORECOLOR },
	{&sUserVars.m_LeftBorder,				STOREDOUBLE },
	{&sUserVars.m_RightBorder,				STOREDOUBLE },
	{&sUserVars.m_TopBorder,				STOREDOUBLE },
	{&sUserVars.m_BottomBorder,				STOREDOUBLE },
	{&sUserVars.m_PrintString,				STORESTRING },
	{&sUserVars.m_PrintStringFlag,			STOREFLAG },
	{&sUserVars.m_PrintPageNumber,			STOREINT },
	{&sUserVars.m_PrintPageOffset,			STOREINT },
	{&sUserVars.m_PrintFontWeight,			STOREINT },
	{&sUserVars.m_PrintFontSize,			STOREINT },
	{&sUserVars.m_PrintGeneBlock,			STOREFLAG },
	{&sUserVars.m_PrintFontName,			STORESTRING },
	{&sUserVars.m_WidthMode,				STOREFLAG },
	{&sUserVars.m_FixedXSize,				STOREINT },
	{&sUserVars.m_CurrentScoreTable,		STOREINT },
	{&sUserVars.m_PictWidth,				STOREINT },
	{&sUserVars.m_PictHeight,				STOREINT },
	{&sUserVars.m_PictAscent,				STOREINT },
	{&sUserVars.m_TitleProgram,				STORESTRING },
	{&sUserVars.m_TitleScoreMatrix,			STORESTRING },
	{&sUserVars.m_TitleOpenGap,				STORESTRING },
	{&sUserVars.m_TitleExtendGap,			STORESTRING },
	{&sUserVars.m_ShadePairArray,			STORESHADEPAIR },
	{&sUserVars.m_ParseString,				STORESTRING },
	{&sUserVars.m_ConsensusLine,			STOREFLAG },
	{&sUserVars.m_ShowTail,					STOREFLAG },
	{&sUserVars.m_Orientation,				STOREFLAG },
	{&sUserVars.m_GapInd,					STOREFLAG },
	{&sUserVars.m_ProjectType,				STOREFLAG },
	{&sUserVars.m_ScoringMethod,			STOREFLAG },
	{&sUserVars.m_GroupDisplayMode,			STOREFLAG },
	{&sUserVars.m_ColorSeqNames,			STOREFLAG },
	{&sUserVars.m_AutoShade4Structure,		STORESTRING },
	{&sUserVars.m_AutoShade3Structure,		STORESTRING },
	{&sUserVars.m_AutoShade2Structure,		STORESTRING },
	{&sUserVars.m_MarkerSymb,				STORECHAR },
	{&sUserVars.m_MarkerSpacing,			STOREINT },
	{&sUserVars.m_MarkerReplace,			STOREINT },
	{&sUserVars.m_MarkerStart,				STOREINT },
	{&sUserVars.m_MarkerEnable,				STOREFLAG },
	{&sUserVars.m_ConservedGap,				STORECHAR },
	{&sUserVars.m_ResidueUpper,				STOREFLAG },
	{&sUserVars.m_ChemPropCysteine,			STOREFLAG },
	{&sUserVars.m_ChemPropShowProp,			STOREFLAG },
	{&sUserVars.m_MaxNameLength,			STOREINT },
	{&sUserVars.m_strLead,					STORESTRING },
	{&sUserVars.m_strTail,					STORESTRING },
	{&sUserVars.m_GroupConsLevel,			STOREDOUBLE },
	{&sUserVars.m_PCRSimilarities,			STORESTRING },
	{&sUserVars.m_PCRLevel,					STOREDOUBLE },
	{&sUserVars.ChemGroupOxi,				STORECHEMPROP12 },
	{&sUserVars.ChemGroupRed,				STORECHEMPROP12 },
	{&sUserVars.ChemCons,					STORECHEMPROP3 },
	{&sUserVars.m_StcDefUser,				STOREFILELIST },
	{&sUserVars.listSearch,					STORESEARCH },
	{&sUserVars.m_ProSite,					STOREFLAG },
	{&sUserVars.m_DispTreeWeight,			STOREFLAG },
	{&sUserVars.m_DNAAmbEn,					STOREFLAG },
	{&sUserVars.ChemPropEnabled[0],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[1],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[2],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[3],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[4],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[5],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[6],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[7],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[8],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[9],			STOREFLAG },
	{&sUserVars.ChemPropEnabled[10],		STOREFLAG },
	{&sUserVars.ChemPropEnabled[11],		STOREFLAG },
	{&sUserVars.m_OverlapColor,				STORECOLOR },
	{&sUserVars.m_PrintShading,				STOREFLAG },
	{&UseGSFiller,							STORESEQSTART }, 
	{&sUserVars.m_SumDefDis,				STOREFLAG }, 
	{&sUserVars.m_SumColInch,				STOREINT }, 
	{&sUserVars.m_Sum2Wid,					STOREFLAG }, 
	{&sUserVars.m_SumTextBlack,				STOREFLAG }, 
	{&sUserVars.listSearch,					STORESEENAB },
	{&sUserVars.m_strLogOddsFile,			STORESTRING }, 
	{&sUserVars.m_dLogOddsMin,				STOREDOUBLE }, 
	{&sUserVars.m_iLogOddsBestN,			STOREINT }, 
	{&sUserVars.m_iLogOddsMode,				STOREFLAG }, 
	{&sUserVars.m_rgbLogOddsOverlap,		STORECOLOR }, 
	{&sUserVars.m_iLogOddsNoOv,				STOREFLAG }, 
	{&sUserVars.m_dLogOddsTL1,				STOREDOUBLE }, 
	{&sUserVars.m_dLogOddsTL2,				STOREDOUBLE }, 
	{&sUserVars.m_dLogOddsTL3,				STOREDOUBLE },
	{&sUserVars.m_listLogOdds,				STORELOGODDS },
	{&sUserVars.m_iLogOddsOutTab,			STOREINT }, 
	{&sUserVars.m_dLogOddsMPC,				STOREDOUBLE }, 
	{&sUserVars.m_iLogOddsBack,				STOREFLAG }, 
	{&sUserVars.m_dLogOddsStA,				STOREDOUBLE }, 
	{&sUserVars.m_dLogOddsStC,				STOREDOUBLE }, 
	{&sUserVars.m_dLogOddsStG,				STOREDOUBLE }, 
	{&sUserVars.m_dLogOddsStT,				STOREDOUBLE }, 
	{&UseGSFiller,							STORESEQDESCR }, 
	{&sUserVars.m_PrintFileName,			STOREFLAG }, 
	{&sUserVars.m_PrintDate,				STOREFLAG }, 
	{&sUserVars.m_TransTilde,				STOREFLAG }, 
	{&sUserVars.m_ShowManShade,				STOREFLAG }, 
	{&sUserVars.m_ShowComments,				STOREFLAG }, 
	{&UseGSFiller,							STORECPAIR }, 
	{&UseGSFiller,							STORECOMMENT }, 
	{&sUserVars.m_DNATransName,				STORESTRING }, 
	{&sUserVars.m_DNATrans,					STORESTRING }, 
	{&sUserVars.m_DNATransStart,			STORESTRING }, 
	{&sUserVars.m_RepExactMatch,			STOREFLAG }, 
	{&sUserVars.m_RepJuxtaposition,			STOREFLAG }, 
	{&sUserVars.m_RepAlignedGaps,			STOREFLAG }, 
	{&sUserVars.m_RepAbsoluteVal,			STOREFLAG }, 
	{&sUserVars.m_RepPercentVal,			STOREFLAG }, 
	{&sUserVars.m_RepOutMatrix,				STOREINT }, 
	{&sUserVars.m_RepLabelTop,				STOREINT }, 
	{&sUserVars.m_RepLabelSingle,			STOREINT }, 
	{&UseGSFiller,							STORECPAIR2 }, 
	{&UseGSFiller,							STORECOMMENT2 }, 
	{&sUserVars.m_RepIncAA,					STOREFLAG }, 
	{&sUserVars.m_MakeBackups,					STOREFLAG }, 
	{&sUserVars.m_LocAfterName,					STOREFLAG }, 
	{&sUserVars.m_LocAfterSeq,					STOREFLAG }, 
	{&UseGSFiller,							STORESEQDESCR2 }, 

	{ NULL, 0 } 
};


//	CString m_strLogOddsFile;
//	double m_dLogOddsMin;
//	int m_iLogOddsBestN;
//	int	m_iLogOddsMode;
//	COLORREF m_rgbLogOddsOverlap;
//	int m_iLogOddsNoOv;
//	double m_dLogOddsTL1;
//	double m_dLogOddsTL2;
//	double m_dLogOddsTL3;


int 
DecodeVars ( CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int strLength = strCode.GetLength();
	int Length = 0, ic;
	UINT i;
	while ( CodeVars->pData != NULL && Length < strLength ) {
		switch ( CodeVars->iType ) {
		case STOREINT:
			{
				char cLen[5];
				for ( i=0; i < 4; ++i ) cLen[i] = strCode[iSLoc++];
				cLen[i] = 0;
				*(int *)CodeVars->pData = (int)strtol(cLen, NULL, 16);
				Length += 4;
			}
			break;
		case STORECOLOR:
			{
				int Red, Green, Blue;
				char conv[3];
				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = 0;
				Red = (int)strtol( conv, NULL, 16 );

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				Green = (int)strtol( conv, NULL, 16 );

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				Blue = (int)strtol( conv, NULL, 16 );

				*(COLORREF *)CodeVars->pData = RGB( Red, Green, Blue );

				Length += 6;
			}
			break;
		case STOREDOUBLE:
			{
				BYTE * pB = (BYTE *)CodeVars->pData;
				char conv[3];
				for ( int i=0; i < sizeof(double); ++i ) {
					conv[0] = strCode[iSLoc++];
					conv[1] = strCode[iSLoc++];
					conv[2] = 0;
					pB[i] = (BYTE)strtol( conv, NULL, 16 );
					Length += 2;
				}
			}
			break;
		case STORESTRING:
			{
				CString *pstr = (CString *)CodeVars->pData;
				pstr->Empty();
				char ct;
				char conv[3];
				while ( 1 ) {
					conv[0] = strCode[iSLoc++];
					conv[1] = strCode[iSLoc++];
					conv[2] = 0;
					ct = (char)strtol( conv, NULL, 16 );
					Length += 2;
					if ( ct == 0 ) break;
					*pstr += ct;
				}
			}
			break;
		case STOREFLAG:
			{
				*(int *)CodeVars->pData = strCode[iSLoc++] - 'A';
				Length += 1;
			}
			break;
		case STORECHAR:
			{
				char conv[3];
				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = 0;
				*(BYTE *)CodeVars->pData = (BYTE)strtol( conv, NULL, 16 );
				Length += 2;
			}
			break;
		case STORESHADEPAIR:
			ic = DecodeShadePair(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORECHEMPROP12:
			ic = DecodeChemProp(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORECHEMPROP3:
			ic = DecodeChemProp(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STOREFILELIST:
			ic = DecodeFileList(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STOREPROPERTY:
			ic = DecodeProperty(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESTRUCTURE:
			ic = DecodeStructure(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break; 
		case STORESEQNAMES:
			ic = DecodeSeqNames(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESEARCH:
			ic = DecodeSearch(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESEQSTART:
			ic = DecodeSeqStart(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESEENAB:
			ic = DecodeSeEnab(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORELOGODDS:
			ic = DecodeLogOdds(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESEQDESCR:
			ic = DecodeSeqDescr(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORECPAIR:
			ic = DecodeCPAIR(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORECOMMENT:
			ic = DecodeComment(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STOREDWORD:
			{
				char cLen[9];
				for ( UINT i=0; i < 8; ++i ) cLen[i] = strCode[iSLoc++];
				cLen[i] = 0;
				*(DWORD *)CodeVars->pData = (DWORD)strtoul(cLen, NULL, 16);
				Length += 8;
			}
			break;

		case STORECPAIR2:
			ic = DecodeCPAIR2(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORECOMMENT2:
			ic = DecodeComment2(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		case STORESEQDESCR2:
			ic = DecodeSeqDescr2(strCode, CodeVars, iSLoc );
			Length += ic;
			iSLoc += ic;
			break;
		}
		// Point next element ..
		CodeVars++;

	}

	return Length;
}



int  
EncodeVars ( CString& strCode, stcEncodeVars * CodeVars )
{
	int Length = 0;

WBUG( "Encode 1\n")
	while (CodeVars->pData != NULL ) {
		switch ( CodeVars->iType ) {
		case STOREINT:
WBUG( "Encode 2\n")
			{
				char conv[10];
				_itoa( *(int *)CodeVars->pData, conv, 16 );
				conv[4] = 0;
				for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				Length += 4;
			}
WBUG( "Encode 3\n")
			break;
		case STORECOLOR:
WBUG( "Encode 4\n")
			{
				char conv[10];
				_itoa( GetRValue( *(COLORREF *)CodeVars->pData), conv, 16 );
				conv[2] = 0;
				for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				_itoa( GetGValue( *(COLORREF *)CodeVars->pData), conv, 16 );
				conv[2] = 0;
				for (UINT i = 2; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				_itoa( GetBValue( *(COLORREF *)CodeVars->pData), conv, 16 );
				conv[2] = 0;
				for (UINT i = 2; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				Length += 6;
			}
WBUG( "Encode 5\n")
			break;
		case STOREDOUBLE:
WBUG( "Encode 6\n")
			{
				BYTE * pB = (BYTE *)CodeVars->pData;
				for ( int i=0; i < sizeof(double); ++i ) {
					char conv[3];
					_itoa( pB[i], conv, 16 );
					conv[2] = 0;
					for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
					strCode += conv;
					Length += 2;
				}
			}
WBUG( "Encode 7\n")
			break;
		case STORESTRING:
WBUG( "Encode 8\n")
			{
				char conv[3];
				CString *pStr = (CString *)CodeVars->pData;
//wFile.Open( "debug.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText );
//CString strDebug;
//strDebug.Format(" StrSize = %d, StrAddr = %x, Str = %s\n", 
//		pStr->GetLength(), 
//		pStr, 
//		(const char *)*pStr 
//);
//wFile.SeekToEnd();
//wFile.WriteString( strDebug );
//wFile.Close();
				if ( !pStr->IsEmpty() ) {
					const char *pstr = *pStr;
					while ( *pstr != 0 ) {
						_itoa( *pstr++, conv, 16 );
							conv[2] = 0;
						for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
						strCode += conv;
						Length += 2;
					}
				}
				conv[0] = '0';
				conv[1] = '0';
				conv[2] = 0;
				strCode += conv;
				Length += 2;
			}
WBUG( "Encode 9\n")
			break;
		case STOREFLAG:
WBUG( "Encode 10\n")
			{
				char conv[2];
				conv[0] = *(int *)CodeVars->pData + 'A';
				if ( conv[0] > 'Z' ) conv[0] = 'Z';
				conv[1] = 0;
				strCode += conv;
				Length += 1;
			}
WBUG( "Encode 11\n")
			break;
		case STORECHAR:
WBUG( "Encode 12\n")
			{
				char conv[3];
				_itoa( *(BYTE *)CodeVars->pData, conv, 16 );
				conv[2] = 0;
				for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				Length += 2;
			}
WBUG( "Encode 13\n")
			break;
		case STORESHADEPAIR:
WBUG( "Encode 14\n")
			Length += EncodeShadePair(strCode, CodeVars );
WBUG( "Encode 15\n")
			break;
		case STORECHEMPROP12:
WBUG( "Encode 16\n")
			Length += EncodeChemProp(strCode, CodeVars, 12 );
WBUG( "Encode 17\n")
			break;
		case STORECHEMPROP3:
WBUG( "Encode 18\n")
			Length += EncodeChemProp(strCode, CodeVars, 3 );
WBUG( "Encode 19\n")
			break;
		case STOREFILELIST:
WBUG( "Encode 20\n")
			Length += EncodeFileList(strCode, CodeVars );
WBUG( "Encode 21\n")
			break;
		case STOREPROPERTY:
WBUG( "Encode 22\n")
			Length += EncodeProperty(strCode, CodeVars );
WBUG( "Encode 23\n")
			break;
		case STORESTRUCTURE:
WBUG( "Encode 24\n")
			Length += EncodeStructure(strCode, CodeVars );
WBUG( "Encode 25\n")
			break;
		case STORESEQNAMES:
WBUG( "Encode 26\n")
			Length += EncodeSeqNames(strCode, CodeVars );
WBUG( "Encode 27\n")
			break;
		case STORESEARCH:
WBUG( "Encode 28\n")
			Length += EncodeSearch(strCode, CodeVars );
WBUG( "Encode 29\n")
			break;
		case STORESEQSTART:
			Length += EncodeSeqStart(strCode, CodeVars );
			break;
		case STORESEENAB:
			Length += EncodeSeEnab(strCode, CodeVars );
			break;
		case STORELOGODDS:
			Length += EncodeLogOdds(strCode, CodeVars );
			break;
		case STORESEQDESCR:
			Length += EncodeSeqDescr(strCode, CodeVars );
			break;
		case STORECPAIR:
			Length += EncodeCPAIR(strCode, CodeVars );
			break;
		case STORECOMMENT:
			Length += EncodeComment(strCode, CodeVars );
			break;
		case STOREDWORD:
			{
				char conv[10];
				_ultoa( *(DWORD *)CodeVars->pData, conv, 16 );
				conv[9] = 0;
				for ( UINT i = 8; i > strlen(conv); --i ) strCode += '0';
				strCode += conv;
				Length += 8;
			}
			break;
		case STORECPAIR2:
			Length += EncodeCPAIR2(strCode, CodeVars );
			break;
		case STORECOMMENT2:
			Length += EncodeComment2(strCode, CodeVars );
			break;
		case STORESEQDESCR2:
			Length += EncodeSeqDescr2(strCode, CodeVars );
			break;
		}
		// Point next element ..
		CodeVars++;

	}

WBUG( "Encode 30\n")
	return Length;
}


struct sSN {
	CStringList SeqNames;
} SN;

stcEncodeVars EncodeSNVars[] = {
	{ &SN.SeqNames, STOREFILELIST }, 
	{ NULL, 0 }
};

int 
DecodeSeqNames(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	CPtrList *pCGS = (CPtrList *)CodeVars->pData;


	int Length = 0;

	// CHAR
	SN.SeqNames.RemoveAll();

	int ic = DecodeVars( strCode, EncodeSNVars, iSLoc );
	Length += ic;
	iSLoc += ic;

	POSITION tPos = SN.SeqNames.GetHeadPosition();
	while ( tPos != NULL ) {
		CString& SeqName = SN.SeqNames.GetNext(tPos);

		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetTitle() == SeqName ) {

				// Check to see if its the same as it was, if so, reset to nogroup.
				pCGS->AddTail ( tCGSeg );
					
				break;
			}

		}
	}
	
	return Length;

}

int 
EncodeSeqNames(CString& strCode, stcEncodeVars * CodeVars )
{
	CPtrList *pCGS = (CPtrList *)CodeVars->pData;


	int Length = 0;

WBUG( "Seq 1\n")
	SN.SeqNames.RemoveAll();

WBUG( "Seq 2\n")
	POSITION tPos = pCGS->GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeq = (CGeneSegment *)pCGS->GetNext(tPos);

		SN.SeqNames.AddTail( tCGSeq->GetTitle() );
	}

WBUG( "Seq 3\n")
	Length += EncodeVars( strCode, EncodeSNVars );
WBUG( "Seq 4\n")

	return Length;

}




struct sFL {
	CString File;
} FL;

stcEncodeVars EncodeFLVars[] = {
	{ &FL.File, STORESTRING },
	{ NULL, 0 }
};

int 
DecodeFileList(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	CStringList *pFL = (CStringList *)CodeVars->pData;

	int Length = 0;

	// CHAR
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count = (int)strtol( conv, NULL, 16 );
	Length += 2;


	for ( int i = 0; i < count; ++i ) { 
		FL.File.Empty();

		int ic = DecodeVars( strCode, EncodeFLVars, iSLoc );
		Length += ic;
		iSLoc += ic;

		pFL->AddTail( FL.File );

	}

	return Length;

}

int 
EncodeFileList(CString& strCode, stcEncodeVars * CodeVars )
{
	CStringList *pFL = (CStringList *)CodeVars->pData;

	int Length = 0;

WBUG( "File 1\n")
	// CHAR
	char conv[10];
	UINT count = pFL->GetCount();
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

WBUG( "File 2\n")
	Length += 2;

	POSITION tPos = pFL->GetHeadPosition();
	while ( tPos != NULL ) {
		FL.File = pFL->GetNext(tPos);

WBUG( "File 3\n")
		Length += EncodeVars( strCode, EncodeFLVars );
WBUG( "File 4\n")
	}

WBUG( "File 5\n")
	return Length;

}

struct sSPS {
	int RowNum;
	CString Group;
} SPS;

stcEncodeVars EncodeSPSVars[] = {
	{ &SPS.RowNum, STORECHAR }, 
	{ &SPS.Group, STORESTRING },
	{ NULL, 0 }
};

int 
DecodeShadePair(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
// 	CPtrArray	m_ShadePairArray;		// Holding a list of ShadePairStruct's
	CPtrArray *pSPSArr = (CPtrArray *)CodeVars->pData;

	int Length = 0;


	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count = (int)strtol( conv, NULL, 16 );
	Length += 2;

	// CHAR
		
	for ( int i = 0; i < count; ++i ) { 

		int ic = DecodeVars( strCode, EncodeSPSVars, iSLoc );
		Length += ic;
		iSLoc += ic;

		ShadePairStruct *tSPS = new ShadePairStruct;

		tSPS->RowNum = SPS.RowNum;
		strcpy ( tSPS->Group, (const char *)SPS.Group );

		pSPSArr->Add(tSPS);

	}

	return Length;
}


int 
EncodeShadePair(CString& strCode, stcEncodeVars * CodeVars )
{
// 	CPtrArray	m_ShadePairArray;		// Holding a list of ShadePairStruct's
	CPtrArray *pSPSArr = (CPtrArray *)CodeVars->pData;


	int Length = 0;

WBUG( "Shade 1\n")
	// CHAR
	char conv[10];
	UINT count = pSPSArr->GetSize();
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

WBUG( "Shade 2\n")
	Length += 2;
		
	for (int i = 0; i < count; ++i ) { 

		ShadePairStruct *tSPS = (ShadePairStruct *)pSPSArr->GetAt(i);

		SPS.RowNum = tSPS->RowNum;
		SPS.Group = tSPS->Group;

WBUG( "Shade 3\n")
		Length += EncodeVars( strCode, EncodeSPSVars );
WBUG( "Shade 4\n")
	}

WBUG( "Shade 5\n")
	return Length;

}

stcChemProp CP;

stcEncodeVars EncodeCPVars[] = {
	{ &CP.Chem, STORESTRING }, 
	{ &CP.TextColor, STORECOLOR }, 
	{ &CP.BackColor, STORECOLOR },
	{ NULL, 0 }
};

int 
DecodeChemProp(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	stcChemProp *pCPArr = (stcChemProp *)CodeVars->pData;


	int Length = 0;

	// CHAR
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int props = (int)strtol( conv, NULL, 16 );
	Length += 2;
		
	for ( int i = 0; i < props; ++i ) { 
		int ic = DecodeVars( strCode, EncodeCPVars, iSLoc );
		Length += ic;
		iSLoc += ic;

		pCPArr[i].Chem = CP.Chem;
		pCPArr[i].TextColor = CP.TextColor;
		pCPArr[i].BackColor = CP.BackColor;

	}

	return Length;

}

int 
EncodeChemProp(CString& strCode, stcEncodeVars * CodeVars, UINT count )
{
	stcChemProp *pCPArr = (stcChemProp *)CodeVars->pData;


	int Length = 0;

WBUG( "Chem 1\n")
	// CHAR
	char conv[10];
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

WBUG( "Chem 2\n")
	Length += 2;
		
	for (int i = 0; i < count; ++i ) { 
		stcChemProp *tCP = &pCPArr[i];

		CP.Chem = tCP->Chem;
		CP.TextColor = tCP->TextColor;
		CP.BackColor = tCP->BackColor;

WBUG( "Chem 3\n")
		Length += EncodeVars( strCode, EncodeCPVars );
WBUG( "Chem 4\n")
	}

WBUG( "Chem 5\n")
	return Length;

}

struct sPS {
	int RowNum;
	CString Group;
	COLORREF TextColor;
	COLORREF BkColor;
} PS;

stcEncodeVars EncodePVars[] = {
	{ &PS.RowNum, STORECHAR }, 
	{ &PS.Group, STORESTRING }, 
	{ &PS.TextColor, STORECOLOR }, 
	{ &PS.BkColor, STORECOLOR },
	{ NULL, 0 }
};

int 
DecodeProperty(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	CProperty *pProp = (CProperty *)CodeVars->pData;

	int Length = 0;

	// Char of 3 sets ..
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count1 = (int)strtol( conv, NULL, 16 );
	Length += 2;

	for ( int ipc = 0; ipc < count1; ++ ipc ) {

		CPtrArray *pPArr = (CPtrArray *)pProp->GetArray(ipc);
		// CHAR
		conv[0] = strCode[iSLoc++];
		conv[1] = strCode[iSLoc++];
		conv[2] = 0;
		int count2 = (int)strtol( conv, NULL, 16 );
		Length += 2;

		for ( int i = 0; i < count2; ++i ) { 

			int ic = DecodeVars( strCode, EncodePVars, iSLoc );
			Length += ic;
			iSLoc += ic;

			PropertyStruct *pPS = new PropertyStruct;

			pPS->RowNum = PS.RowNum;
			strcpy ( pPS->Group, (const char *)PS.Group );
			pPS->TextColor = PS.TextColor;
			pPS->BkColor = PS.BkColor;

			pPArr->Add(pPS);
		}
	}

	return Length;

}

int 
EncodeProperty(CString& strCode, stcEncodeVars * CodeVars )
{
	CProperty *pProp = (CProperty *)CodeVars->pData;


	int Length = 0;

	// Char of 3 sets ..
	strCode += "03";
	Length += 2;

WBUG( "Prop 1\n")
	

	for ( int ipc = 0; ipc < 3; ++ ipc ) {

		CPtrArray *pPArr = (CPtrArray *)pProp->GetArray(ipc);
		// CHAR
		UINT count = pPArr->GetSize();

WBUG( "Prop 2\n")
		char conv[10];
		_itoa( count , conv, 16 );
		conv[2] = 0;
		for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
		strCode += conv;
		Length += 2;

WBUG( "Prop 3\n")
		for (int i = 0; i < count; ++i ) { 
			PropertyStruct *pPS = (PropertyStruct *)pPArr->GetAt(i);

			PS.RowNum = pPS->RowNum;
			PS.Group = pPS->Group;
			PS.TextColor = pPS->TextColor;
			PS.BkColor = pPS->BkColor;
WBUG( "Prop 4\n")
			Length += EncodeVars( strCode, EncodePVars );
WBUG( "Prop 5\n")
		}
WBUG( "Prop 6\n")
	}

WBUG( "Prop 7\n")
	return Length;

}

struct sSS {
	CString MasterSeq;
	CString DataType;
	CStringList FileNames;
} SS;

stcEncodeVars EncodeSVars[] = {
	{ &SS.MasterSeq, STORESTRING }, 
	{ &SS.DataType, STORESTRING }, 
	{ &SS.FileNames, STOREFILELIST }, 
	{ NULL, 0 }
};

int 
DecodeStructure(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	CStcGroup *pSGrp = (CStcGroup *)CodeVars->pData;


	int Length = 0;
	SS.FileNames.RemoveAll();
	int ic = DecodeVars( strCode, EncodeSVars, iSLoc );
	Length += ic;
	iSLoc += ic;

	// Another various flags string
	pSGrp->SetMasterSeq(SS.MasterSeq);
	pSGrp->SetCurrentDataType(SS.DataType, 1);	// Force it

	// STOREFILELIST
	POSITION tPos = SS.FileNames.GetHeadPosition();
	while ( tPos != NULL ) {
		pSGrp->AddFileName( SS.FileNames.GetNext(tPos) );
	}

	return Length;

}

int 
EncodeStructure(CString& strCode, stcEncodeVars * CodeVars )
{
	CStcGroup *pSGrp = (CStcGroup *)CodeVars->pData;


	int Length = 0;

WBUG( "Stc 1\n")
	SS.FileNames.RemoveAll();

	// Another various flags string
	SS.MasterSeq = pSGrp->GetMasterSeq();
WBUG( "Stc 2\n")
	SS.DataType = pSGrp->GetCurrentDataType();
WBUG( "Stc 3\n")

	// STOREFILELIST
	const CStringList& listS = pSGrp->GetFileNames();
	POSITION tPos = listS.GetHeadPosition();
	while ( tPos != NULL ) {
		SS.FileNames.AddTail( listS.GetNext(tPos) );
	}
WBUG( "Stc 4\n")

	Length += EncodeVars( strCode, EncodeSVars );

WBUG( "Stc 5\n")
	return Length;

}


stcSearch SE;

stcEncodeVars EncodeSEVars[] = {
	{ &SE.strSearch, STORESTRING }, 
	{ &SE.strName, STORESTRING }, 
	{ &SE.strDescrip, STORESTRING }, 
	{ &SE.rgbText, STORECOLOR }, 
	{ &SE.rgbBack, STORECOLOR },
	{ NULL, 0 }
};

int 
DecodeSearch(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	// CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList *pSCH = (CPtrList *)CodeVars->pData;

	int Length = 0;

	// CHAR

	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count = (int)strtol( conv, NULL, 16 );
	Length += 2;

	for ( int i = 0; i < count; ++i ) {
			int ic = DecodeVars( strCode, EncodeSEVars, iSLoc );
			Length += ic;
			iSLoc += ic;

			stcSearch *pSE = new stcSearch;

			pSE->iEnabled = 1;

			pSE->strSearch = SE.strSearch;
			pSE->strName = SE.strName;
			pSE->strDescrip = SE.strDescrip;
			pSE->rgbText = SE.rgbText;
			pSE->rgbBack = SE.rgbBack;

			pSCH->AddTail(pSE);
	}
	
	return Length;

}

int 
EncodeSearch(CString& strCode, stcEncodeVars * CodeVars )
{
	// CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList *pSCH = (CPtrList *)CodeVars->pData;

	int Length = 0;

WBUG( "Sch 1\n")
	UINT count = pSCH->GetCount();

	char conv[10];
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;
	Length += 2;

WBUG( "Sch 2\n")
	POSITION tPos = pSCH->GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSE = (stcSearch *)pSCH->GetNext(tPos);

WBUG( "Sch 3\n")
		SE.strSearch = pSE->strSearch;
		SE.strName = pSE->strName;
		SE.strDescrip = pSE->strDescrip;
		SE.rgbText = pSE->rgbText;
		SE.rgbBack = pSE->rgbBack;
WBUG( "Sch 4\n")

		Length += EncodeVars( strCode, EncodeSEVars );
WBUG( "Sch 5\n")
	}

WBUG( "Sch 6\n")
	return Length;

}


struct sSQS {
	DWORD Start;
} SQS;

stcEncodeVars EncodeSQSVars[] = {
	{ &SQS.Start, STOREINT },
	{ NULL, 0 }
};

int 
DecodeSeqStart(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{

	int Length = 0;

	// CHAR
	char conv[5];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = strCode[iSLoc++];
	conv[3] = strCode[iSLoc++];
	conv[4] = 0;
	DWORD count = strtol( conv, NULL, 16 );
	Length += 4;

	DWORD cUsed = 1;

	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				if ( cUsed > count ) break;
				int ic = DecodeVars( strCode, EncodeSQSVars, iSLoc );
				Length += ic;
				iSLoc += ic;
				// CDWordArray
				tCGSeg->SetTextStart( SQS.Start );
				cUsed++;
			}
		}
	}

	return Length;
}

int 
EncodeSeqStart(CString& strCode, stcEncodeVars * CodeVars )
{
	int Length = 0;

	// CHAR
	char conv[10];
//	UINT count = pFL->GetCount();
	UINT count = 0;

	POSITION sPos;

	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) count++;
		}
	}

	_itoa( count , conv, 16 );
	conv[4] = 0;
	for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

	Length += 4;

	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
			SQS.Start = tCGSeg->GetTextStart();
			Length += EncodeVars( strCode, EncodeSQSVars );
		}
	}

	return Length;

}


void
CopyPhysioChemVars( 
	int *nCy, int *oCy,
	int*nShow, int* oShow, 
	stcChemProp* nOxi, stcChemProp* oOxi, 
	stcChemProp* nRed, stcChemProp* oRed, 
	stcChemProp* nCons, stcChemProp* oCons, 
	int *nEnab, int *oEnab 
)
{
	// TODO: Add your command handler code here
	*nCy = *oCy;
	*nShow = *oShow;
	for ( int i=0; i < 12; ++i ) {
		nOxi[i].Chem = oOxi[i].Chem;
		nOxi[i].TextColor = oOxi[i].TextColor;
		nOxi[i].BackColor = oOxi[i].BackColor;
		//
		nRed[i].Chem = oRed[i].Chem;
		nRed[i].TextColor = oRed[i].TextColor;
		nRed[i].BackColor = oRed[i].BackColor;
		//
		nEnab[i] = oEnab[i];
	}
	for (int i=0; i < 3; ++i ) {
		nCons[i].Chem = oCons[i].Chem;
		nCons[i].TextColor = oCons[i].TextColor;
		nCons[i].BackColor = oCons[i].BackColor;
	}

}


int g_iEnabled;

stcEncodeVars EncodeSEEVars[] = {
	{ &g_iEnabled, STOREFLAG }, 
	{ NULL, 0 }
};

int 
DecodeSeEnab(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	// CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList *pSCH = (CPtrList *)CodeVars->pData;

	int Length = 0;

	// CHAR

	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count = (int)strtol( conv, NULL, 16 );
	Length += 2;

	int lcount = pSCH->GetCount();

	for ( int i = 0; i < count; ++i ) {
			int ic = DecodeVars( strCode, EncodeSEEVars, iSLoc );
			Length += ic;
			iSLoc += ic;

			// Paranoia
			if ( i >= lcount ) continue;

			stcSearch *pSE = (stcSearch *)pSCH->GetAt( pSCH->FindIndex( i ) );
			pSE->iEnabled = g_iEnabled;
	}
	
	return Length;

}


// fuck

int 
EncodeSeEnab(CString& strCode, stcEncodeVars * CodeVars )
{
	// CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList *pSCH = (CPtrList *)CodeVars->pData;

	int Length = 0;

	UINT count = pSCH->GetCount();

	char conv[10];
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;
	Length += 2;

	POSITION tPos = pSCH->GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSE = (stcSearch *)pSCH->GetNext(tPos);

		g_iEnabled = pSE->iEnabled;

		Length += EncodeVars( strCode, EncodeSEEVars );
	}

	return Length;

}


stcLogOdds LO;

stcEncodeVars EncodeLOVars[] = {
	{ &LO.strMotif, STORESTRING }, 
	{ &LO.strName, STORESTRING }, 
	{ &LO.strDescrip, STORESTRING }, 
	{ &LO.rgbText, STORECOLOR }, 
	{ &LO.rgbBack, STORECOLOR },
	{ &LO.iEnabled, STOREFLAG },
	{ NULL, 0 }
};

int 
DecodeLogOdds(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	// CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList *pLO = (CPtrList *)CodeVars->pData;

	int Length = 0;
	stcLogOdds *pstcLO;

	int fscan = 0;
	// CHAR
	if ( sUserVars.m_strLogOddsFile.GetLength() ) {
		fscan = gpDoc->ScanMemeMotifs(gpDoc->m_PathName + sUserVars.m_strLogOddsFile, pLO);
	}

	POSITION tPos = pLO->GetHeadPosition();
	while ( tPos != NULL ) {
		pstcLO = (stcLogOdds *)pLO->GetNext(tPos);
		pstcLO->iEnabled = -1;
	}


	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;
	int count = (int)strtol( conv, NULL, 16 );
	Length += 2;

	for ( int i = 0; i < count; ++i ) {
		int ic = DecodeVars( strCode, EncodeLOVars, iSLoc );
		Length += ic;
		iSLoc += ic;

		int found = 0;
		tPos = pLO->GetHeadPosition();
		while ( tPos != NULL ) {
			pstcLO = (stcLogOdds *)pLO->GetNext(tPos);
			if ( pstcLO->strName == LO.strName ) {
				found = 1;
				break;
			}
		}

		if ( found && fscan ) {
			pstcLO->iEnabled = LO.iEnabled;
			pstcLO->strMotif = LO.strMotif;
			pstcLO->strDescrip = LO.strDescrip;
			pstcLO->rgbText = LO.rgbText;
			pstcLO->rgbBack = LO.rgbBack;
		}
	}
	
	tPos = pLO->GetHeadPosition();
	while ( tPos != NULL ) {
		POSITION sPos = tPos;
		pstcLO = (stcLogOdds *)pLO->GetNext(tPos);
		if ( pstcLO->iEnabled == -1 ) {
			pLO->RemoveAt(sPos);
			delete [] pstcLO->dLogOddsArr;
			delete pstcLO;
		}
	}

	return Length;

}

int 
EncodeLogOdds(CString& strCode, stcEncodeVars * CodeVars )
{
	// CPtrList	m_GroupList;	// CGeneLOquence *
	CPtrList *pLO = (CPtrList *)CodeVars->pData;

	int Length = 0;

	UINT count = pLO->GetCount();

	char conv[10];
	_itoa( count , conv, 16 );
	conv[2] = 0;
	for ( UINT i = 2; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;
	Length += 2;

	POSITION tPos = pLO->GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pstcLO = (stcLogOdds *)pLO->GetNext(tPos);

		LO.strMotif = pstcLO->strMotif;
		LO.strName = pstcLO->strName;
		LO.strDescrip = pstcLO->strDescrip;
		LO.rgbText = pstcLO->rgbText;
		LO.rgbBack = pstcLO->rgbBack;
		LO.iEnabled = pstcLO->iEnabled;

		Length += EncodeVars( strCode, EncodeLOVars );
	}

	return Length;

}

struct sSQD {
	CString Descr;
} SQD;

stcEncodeVars EncodeSQDVars[] = {
	{ &SQD.Descr, STORESTRING },
	{ NULL, 0 }
};

int 
DecodeSeqDescr(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 2;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				if ( cUsed > count ) break;
				int ic = DecodeVars( strCode, EncodeSQDVars, iSLoc );
				Length += ic;
				iSLoc += ic;
				// CDWordArray
				tCGSeg->SetDescr( SQD.Descr );
				cUsed++;
			}
		}
	}

	return Length;
}

// Zero'ed out due to a bug
int 
EncodeSeqDescr(CString& strCode, stcEncodeVars * CodeVars )
{
	strCode += "00";
	return 2;
}



struct sSQCP {
	DWORD		Position;
	COLORREF	rgbText;
	COLORREF	rgbBack;
} SQCP;

stcEncodeVars EncodeSQCPVars[] = {
	{ &SQCP.Position, STOREDWORD },
	{ &SQCP.rgbText, STORECOLOR },
	{ &SQCP.rgbBack, STORECOLOR },
	{ NULL, 0 }
};

int 
DecodeCPAIR(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 2;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				if ( cUsed > count ) break;

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = 0;

				DWORD mcount = strtol( conv, NULL, 16 );
				Length += 2;

				for ( DWORD mc = 0; mc < mcount; ++mc ) {
					int ic = DecodeVars( strCode, EncodeSQCPVars, iSLoc );
					Length += ic;
					iSLoc += ic;
					// CDWordArray
					tCGSeg->SetShade( SQCP.Position, SQCP.rgbText, SQCP.rgbBack, TRUE );
				}

				cUsed++;
			}
		}
	}

	return Length;
}

int 
EncodeCPAIR(CString& strCode, stcEncodeVars * CodeVars )
{
	// Zeroed out due to a bug
	strCode += "00";
	return 2;

}


struct sSQCOM {
	DWORD		Position;
	char		Comment;
} SQCOM;

stcEncodeVars EncodeSQCOMVars[] = {
	{ &SQCOM.Position, STOREDWORD },
	{ &SQCOM.Comment, STORECHAR },
	{ NULL, 0 }
};

int 
DecodeComment(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[3];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 2;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				if ( cUsed > count ) break;

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = 0;

				DWORD mcount = strtol( conv, NULL, 16 );
				Length += 2;

				for ( DWORD mc = 0; mc < mcount; ++mc ) {
					int ic = DecodeVars( strCode, EncodeSQCOMVars, iSLoc );
					Length += ic;
					iSLoc += ic;
					// CDWordArray
					tCGSeg->SetComment( SQCOM.Position, SQCOM.Comment );
				}

				cUsed++;
			}
		}
	}

	return Length;
}

int 
EncodeComment(CString& strCode, stcEncodeVars * CodeVars )
{
	// Zeroed out due to a bug
	strCode += "00";
	return 2;

}


int 
DecodeCPAIR2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[10];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = strCode[iSLoc++];
	conv[3] = strCode[iSLoc++];
	conv[4] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 4;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				if ( cUsed > count ) break;

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = strCode[iSLoc++];
				conv[3] = strCode[iSLoc++];
				conv[4] = 0;

				DWORD mcount = strtol( conv, NULL, 16 );
				Length += 4;

				for ( DWORD mc = 0; mc < mcount; ++mc ) {
					int ic = DecodeVars( strCode, EncodeSQCPVars, iSLoc );
					Length += ic;
					iSLoc += ic;
					// CDWordArray
					tCGSeg->SetShade( SQCP.Position, SQCP.rgbText, SQCP.rgbBack, TRUE );
				}

				cUsed++;
			}
		}
	}

	return Length;
}

int 
EncodeCPAIR2(CString& strCode, stcEncodeVars * CodeVars )
{
	int Length = 0;

	// CHAR
	char conv[10];
//	UINT count = pFL->GetCount();
	UINT count = 0;
	POSITION sPos;
	CPAIR tPair;
	DWORD dwPos;
	
	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) count++;
		}
	}

	_itoa( count , conv, 16 );
	conv[4] = 0;
	for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

	Length += 4;

	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
		
			const CMapDWORDToCPAIR& map = tCGSeg->GetMapCPAIR();
			count = map.GetCount();
			_itoa( count , conv, 16 );
			conv[4] = 0;
			for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
			strCode += conv;

			Length += 4;

			POSITION tPos = map.GetStartPosition();
			while ( tPos != NULL ) {
				map.GetNextAssoc( tPos, dwPos, tPair );
				SQCP.Position = dwPos;
				SQCP.rgbText = tPair.rgbText;
				SQCP.rgbBack = tPair.rgbBack;

				Length += EncodeVars( strCode, EncodeSQCPVars );
			}
		}
	}

	return Length;

}

int 
DecodeComment2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[10];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = strCode[iSLoc++];
	conv[3] = strCode[iSLoc++];
	conv[4] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 4;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				if ( cUsed > count ) break;

				conv[0] = strCode[iSLoc++];
				conv[1] = strCode[iSLoc++];
				conv[2] = strCode[iSLoc++];
				conv[3] = strCode[iSLoc++];
				conv[4] = 0;

				DWORD mcount = strtol( conv, NULL, 16 );
				Length += 4;

				for ( DWORD mc = 0; mc < mcount; ++mc ) {
					int ic = DecodeVars( strCode, EncodeSQCOMVars, iSLoc );
					Length += ic;
					iSLoc += ic;
					// CDWordArray
					tCGSeg->SetComment( SQCOM.Position, SQCOM.Comment );
				}

				cUsed++;
			}
		}
	}

	return Length;
}

int 
EncodeComment2(CString& strCode, stcEncodeVars * CodeVars )
{
	int Length = 0;

	// CHAR
	char conv[10];
//	UINT count = pFL->GetCount();
	UINT count = 0;
	POSITION sPos;
	char tChar;
	DWORD dwPos;
	
	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) count++;
		}
	}

	_itoa( count , conv, 16 );
	conv[4] = 0;
	for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

	Length += 4;

	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) continue;
		
			const CMapDWORDToChar& map = tCGSeg->GetMapChar();
			count = map.GetCount();
			_itoa( count , conv, 16 );
			conv[4] = 0;
			for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
			strCode += conv;

			Length += 4;

			POSITION tPos = map.GetStartPosition();
			while ( tPos != NULL ) {
				map.GetNextAssoc( tPos, dwPos, tChar );
				SQCOM.Position = dwPos;
				SQCOM.Comment = tChar;

				Length += EncodeVars( strCode, EncodeSQCOMVars );
			}
		}
	}

	return Length;

}

int 
DecodeSeqDescr2(CString& strCode, stcEncodeVars * CodeVars, int iSLoc )
{
	int Length = 0;

	// CHAR
	char conv[10];
	conv[0] = strCode[iSLoc++];
	conv[1] = strCode[iSLoc++];
	conv[2] = strCode[iSLoc++];
	conv[3] = strCode[iSLoc++];
	conv[4] = 0;

	DWORD count = strtol( conv, NULL, 16 );
	Length += 4;

	DWORD cUsed = 1;
	if ( gpDoc->pGSFiller != NULL ) {
		POSITION sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
				if ( cUsed > count ) break;
				int ic = DecodeVars( strCode, EncodeSQDVars, iSLoc );
				Length += ic;
				iSLoc += ic;
				// CDWordArray
				tCGSeg->SetDescr( SQD.Descr );
				cUsed++;
			}
		}
	}

	return Length;
}

// FUCK!!
int 
EncodeSeqDescr2(CString& strCode, stcEncodeVars * CodeVars )
{
	int Length = 0;

	// CHAR
	char conv[10];
//	UINT count = pFL->GetCount();
	UINT count = 0;
	POSITION sPos;
	
	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() == LINESEQUENCE ) count++;
		}
	}

	_itoa( count , conv, 16 );
	conv[4] = 0;
	for ( UINT i = 4; i > strlen(conv); --i ) strCode += '0';
	strCode += conv;

	Length += 4;

	if ( gpDoc->pGSFiller != NULL ) {
		sPos = gpDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)gpDoc->pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
			SQD.Descr = tCGSeg->GetDescr();
			Length += EncodeVars( strCode, EncodeSQDVars );
		}
	}

	return Length;

}

