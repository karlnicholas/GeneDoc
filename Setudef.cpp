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

static char szUDSection[] = "User Defaults";

static char szFONTWEIGHT[] = "Font Weight";
static char szFONTSIZE[] = "Font Size";

static char szFOREPRI[] = "Fore Pri";
static char szFORESEC[] = "Fore Sec";
static char szFORETERT[] = "Fore Tert";
static char szFOREBASE[] = "Fore Base";

static char szBACKPRI[] = "Back Pri";
static char szBACKSEC[] = "Back Sec";
static char szBACKTERT[] = "Back Tert";
static char szBACKBASE[] = "Back Base";

static char szLEFTBORD[] = "Left Bord";
static char szRIGHTBORD[] = "Right Bord";
static char szTOPBORD[] = "Top Bord";
static char szBOTTOMBORD[] = "Bottom Bord";

static char szPRINTSTRING[] = "PString";
static char szPRINTSTRINGFLAG[] = "PStringF";
static char szPRINTPAGENUMBER[] = "PPageNum";
static char szPRINTPAGEOFFSET[] = "PPageOff";
static char szPRINTFONTWEIGHT[] = "PFontW";
static char szPRINTFONTSIZE[] = "PFontS";
static char szPRINTGENEBLOCK[] = "PGeneB";
static char szPRINTFONTNAME[] = "PFontN";


static char szWIDTHMODE[] = "Width Mode";
static char szFIXEDX[] = "Fixed X";
static char szSCORETABLE[] = "Score Table";
static char szSHOWTAIL[] = "Seq Indicator";
static char szORIENTATION[] = "Orient";
static char szGAPIND[] = "Gap Ind";

static char szSHADEGROUPS[] = "Shade Groups";
static char szGROUPENABLED[] = "Groups Enabled";

static char szPRILEVEL[] = "Pri Level";
static char szSECLEVEL[] = "Sec Level";
static char szTERTLEVEL[] = "Tert Level";
static char szDIFFMODE[] = "Diff Mode";
static char szSHADEMODE[] = "Shade Mode";
static char szCONSENSUS[] = "Consensus";
static char szLASTSHADE[] = "Last Shade";
static char szPROPGROUPS[] = "Prop Gp";
static char szPROPSTYLE[] = "Prop Style";
static char szRESIDUEMODE[] = "Residue Mode";
static char szCONSSUBSTYLE[] = "Cons Sub Style";

static char szGROUPDISPMODE[] = "GDMode";
static char szCOLORSEQNAMES[] = "ColSeqN";

static char szGROUPCONSLEVEL[] = "GCLevel";
static char szPCRSIMILARITIES[] = "PCRSIM";
static char szPCRLEVEL[] = "PCRLEV";

static char szDTREEWEIGHT[] = "Disp Tree Weight";
static char szSCOREMETH[] = "Score Meth";

static char szPICTWIDTH[] = "Pict Width";
static char szPICTHEIGHT[] = "Pict Height";
static char szPICTASCENT[] = "Pict Ascent";

static char szMarkerSymb[] = "MarkerSymb";		// *  symbol, 
static char szMarkerSpacing[] = "MarkerSpacing";	// 10  spacing between symbols, 
static char szMarkerReplace[] = "MarkerReplace";	// 2  how often to replace a symbol with a number, 
static char szMarkerStart[] = "MarkerStart";		// -13  the number to be assigned to the first column of the alignment,
static char szMarkerEnable[] = "MarkerEnable";		// is it enabled?

static char szConservedGap[] = "ConservedGap";		// *  symbol, 

static char szResidueUpper[] = "ResidueUpper";		// 

static char szChemPropCysteine[] = "Chem Prop Cysteine";		// 
static char szChemPropShowProp[] = "Chem Prop ShowProp";		// 

static char szFORECHEM0[] = "Fore Chem 0";		// 
static char szBACKCHEM0[] = "Back Chem 0";		// 
static char szCHEMPROPEN0[] = "Prop Chem En 0";	// 
static char szFORECHEM1[] = "Fore Chem 1";		// 
static char szBACKCHEM1[] = "Back Chem 1";		// 
static char szCHEMPROPEN1[] = "Prop Chem En 1";	// 
static char szFORECHEM2[] = "Fore Chem 2";		// 
static char szBACKCHEM2[] = "Back Chem 2";		// 
static char szCHEMPROPEN2[] = "Prop Chem En 2";	// 
static char szFORECHEM3[] = "Fore Chem 3";		// 
static char szBACKCHEM3[] = "Back Chem 3";		// 
static char szCHEMPROPEN3[] = "Prop Chem En 3";	// 
static char szFORECHEM4[] = "Fore Chem 4";		// 
static char szBACKCHEM4[] = "Back Chem 4";		// 
static char szCHEMPROPEN4[] = "Prop Chem En 4";	// 
static char szFORECHEM5[] = "Fore Chem 5";		// 
static char szBACKCHEM5[] = "Back Chem 5";		// 
static char szCHEMPROPEN5[] = "Prop Chem En 5";	// 
static char szFORECHEM6[] = "Fore Chem 6";		// 
static char szBACKCHEM6[] = "Back Chem 6";		// 
static char szCHEMPROPEN6[] = "Prop Chem En 6";	// 
static char szFORECHEM7[] = "Fore Chem 7";		// 
static char szBACKCHEM7[] = "Back Chem 7";		// 
static char szCHEMPROPEN7[] = "Prop Chem En 7";	// 
static char szFORECHEM8[] = "Fore Chem 8";		// 
static char szBACKCHEM8[] = "Back Chem 8";		// 
static char szCHEMPROPEN8[] = "Prop Chem En 8";	// 
static char szFORECHEM9[] = "Fore Chem 9";		// 
static char szBACKCHEM9[] = "Back Chem 9";		// 
static char szCHEMPROPEN9[] = "Prop Chem En 9";	// 
static char szFORECHEM10[] = "Fore Chem 10";		// 
static char szBACKCHEM10[] = "Back Chem 10";		// 
static char szCHEMPROPEN10[] = "Prop Chem En 10";	// 
static char szFORECHEM11[] = "Fore Chem 11";		// 
static char szBACKCHEM11[] = "Back Chem 11";		// 
static char szCHEMPROPEN11[] = "Prop Chem En 11";	// 

static char szFORECHEMCONS0[] = "Fore Chem Cons 0";		// 
static char szBACKCHEMCONS0[] = "Back Chem Cons 0";		// 
static char szFORECHEMCONS1[] = "Fore Chem Cons 1";		// 
static char szBACKCHEMCONS1[] = "Back Chem Cons 1";		// 
static char szFORECHEMCONS2[] = "Fore Chem Cons 2";		// 
static char szBACKCHEMCONS2[] = "Back Chem Cons 2";		// 

static char szStrLead[] = "String Lead";		// 
static char szStrTail[] = "String Tail";		// 
static char szMaxNameLength[] = "Max Name Length";		// 


//	CPtrList listSearch;		// stcSearch *Storage ..
//	int m_ProSite;

static char szProSite[] = "ProSite";
static char szLISTSRCH[] = "List Search";
static char szDNAAmbEn[] = "DNAAmbEn";
static char szOVERLAPCOLOR[] = "Overlap Color";
static char szPRINTSHADE[] = "Print Shade";

static char szIDENTDISPSTYLE[] = "Ident Display Style";

static char szSUMCOLINCH[] = "Sum Col Inch";
static char szSUM2WID[] = "Sum2Wid";
static char szSUMDEFDIS[] = "SumDefDis";
static char szSUMTEXTBLACK[] = "SumTextBlack";

static char szLOGODDSMIN[] = "LogOddsMin";
static char szLOGODDSBESTN[] = "LogOddsBestN";
static char szLOGODDSMODE[] = "LogOddsMode";
static char szLOGODDSOVERLAP[] = "LogOddsOver";
static char szLOGODDSNOOV[] = "LogOddsNoOv";
static char szLOGODDSTL1[] = "LogOddsTL1";
static char szLOGODDSTL2[] = "LogOddsTL2";
static char szLOGODDSTL3[] = "LogOddsTL3";
static char szLOGODDSMPC[] = "LogOddsMPC";
static char szLOGODDSOUTTAB[] = "LogOddsOutTab";
static char szLOGODDSBACK[] = "LogOddsBack";
static char szLOGODDSSTA[] = "LogOddsStA";
static char szLOGODDSSTC[] = "LogOddsStC";
static char szLOGODDSSTG[] = "LogOddsStG";
static char szLOGODDSSTT[] = "LogOddsStT";

static char szPRINTFILENAME[] = "PrintFileName";
static char szPRINTDATE[] = "PrintDate";
static char szTRANSTILDE[] = "TransTilde";
static char szSHOWMANSHADE[] = "ShowManShade";
static char szSHOWCOMMENTS[] = "ShowComments";

static char szDNATRANSNAME[] = "DNATransName";
static char szDNATRANS[] = "DNATrans";
static char szDNATRANSSTART[] = "DNATransStart";

static char szRepExactMatch[] = "RepExactMatch";
static char szRepJuxtaposition[] = "RepJuxtaposition";
static char szRepAlignedGaps[] = "RepAlignedGaps";
static char szRepAbsoluteVal[] = "RepAbsoluteVal";
static char szRepPercentVal[] = "RepPercentVal";
static char szRepOutMatrix[] = "RepOutMatrix";
static char szRepLabelTop[] = "RepLabelTop";
static char szRepLabelSingle[] = "RepLabelSingle";
static char szRepIncAA[] = "RepIncAA";
static char szMakeBackups[] = "MakeBackups";
static char szLocAfterName[] = "LocAfterName";
static char szLocAfterSeq[] = "LocAfterSeq";

void
CGenedocDoc::GetIniDisplayVars(CDisplayVars *DisplayVars)
{
	// Start Of Display Vars....
	CString strBuffer;
	char DecodeBuff[256];
	int i;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRILEVEL);
	if (strBuffer.IsEmpty())
		DisplayVars->SetPrimaryLevel(100.0 );
	else
		DisplayVars->SetPrimaryLevel( atof(strBuffer) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSECLEVEL);
	if (strBuffer.IsEmpty())
		DisplayVars->SetSecondaryLevel( 80.0);
	else
		DisplayVars->SetSecondaryLevel( atof(strBuffer) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szTERTLEVEL);
	if (strBuffer.IsEmpty())
		DisplayVars->SetTertiaryLevel( 60.0 );
	else
		DisplayVars->SetTertiaryLevel( atof(strBuffer) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHADEMODE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetModeConserved( 0);
	else
		DisplayVars->SetModeConserved( atoi(strBuffer) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLASTSHADE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetLastShadeLevel( SHADELEVEL4 );
	else {
		DisplayVars->SetLastShadeLevel( atoi(strBuffer) );
		if ( DisplayVars->GetLastShadeLevel() > SHADELEVEL4 ) {
			if ( DisplayVars->GetLastShadeLevel() > SHADELEVEL4 + 1) {
				DisplayVars->SetResidueMode(1);
			}
			DisplayVars->SetLastShadeLevel( SHADELEVEL4 );
		}
	}

	
	// Default to Diff/Consensus
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDIFFMODE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetDiffMode( 0 );
	else
		DisplayVars->SetDiffMode( atoi(strBuffer) );


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szGROUPENABLED);
	if (strBuffer.IsEmpty())
		DisplayVars->SetGroupEnabled( 1);
	else
		DisplayVars->SetGroupEnabled( atoi(strBuffer) );


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPROPSTYLE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetPropStyle( 1 );		// Property Shade all, looks cooler ..
	else
		DisplayVars->SetPropStyle( atoi(strBuffer) );

	// Residue Mode
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szRESIDUEMODE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetResidueMode( 0 );
	else
		DisplayVars->SetResidueMode( atoi(strBuffer) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCONSSUBSTYLE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetConsSubStyle( 0 );
	else
		DisplayVars->SetConsSubStyle( atoi(strBuffer) );

	DisplayVars->SetTitleColors ( RGB ( 0,0,0), RGB ( 255,255,255) );

	int PropLevelCount = 0;
	int TopCount = 1;
	PropertyStruct *tPS;
	// CPtrArray

	while ( 1 ) {
	
		sprintf ( DecodeBuff, "%s%d%d", szPROPGROUPS, PropLevelCount + 1, TopCount );

		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );

		if (strBuffer.IsEmpty()) {
			
			if ( TopCount == 1 ) {
				SetPropertyDefault(
					DisplayVars->GetProperty().GetArray(PropLevelCount), // &
					PropLevelCount, 
					m_UserVars.m_ProjectType
				);
			}
			PropLevelCount += 1;
			if ( PropLevelCount >= 3 ) {
				// Were done!!
				break;
			} else {
				TopCount = 1;
				continue;
			}
		}

		// We are getting strings, so lets 
		if ( TopCount == 1 ) {
			// Clear out Old Array
			int count = DisplayVars->GetProperty().GetArray(PropLevelCount)->GetSize();
			for ( i = 0; i < count; ++i ) {
				tPS = DisplayVars->GetProperty().GetPropertyStruct(PropLevelCount, i);
				delete tPS;
			}
			DisplayVars->GetProperty().GetArray(PropLevelCount)->RemoveAll();
		}
		

		const char *tStr = strBuffer;

		int RowCount = 0;
		tPS = new PropertyStruct;
		if ( tPS == 0 ) {
			AfxMessageBox("getinidefaults:new:fail:2");
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
	
	DisplayVars->SetIdentColors ( RGB ( 255,255,255), RGB ( 128,128,128) );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szIDENTDISPSTYLE);
	if (strBuffer.IsEmpty())
		DisplayVars->SetIdentDisplayStyle( 0 );
	else
		DisplayVars->SetIdentDisplayStyle( atoi(strBuffer) );

}


void
DecodeColor( const char *tStr, COLORREF *tRef )
{
	char DecodeBuff[20];
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Red = atoi( DecodeBuff );
	tStr += 3;
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Green = atoi( DecodeBuff );
	tStr += 3;
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Blue = atoi( DecodeBuff );
	*tRef = RGB ( Red, Green, Blue );
}

void
CGenedocDoc::GetIniDefaults()
{

	// Start User Vars default init
	CString strBuffer;
	char DecodeBuff[256];
	int i;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFONTWEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FontWeight = FW_NORMAL;
	else 
		m_UserVars.m_FontWeight = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFONTSIZE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FontSize = 12;
	else 
		m_UserVars.m_FontSize = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKBASE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BackColor0 = RGB ( 255,255,255 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_BackColor0 );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFOREBASE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ForeColor0 = RGB ( 0,0,0 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_ForeColor0 );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKTERT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BackColor60 = RGB ( 192,192,192 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_BackColor60 );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORETERT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ForeColor60 = RGB ( 0,0,0 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_ForeColor60 );
	}
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKSEC);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BackColor80 = RGB( 128, 128, 128);
	else {
		DecodeColor( strBuffer, &m_UserVars.m_BackColor80 );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORESEC);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ForeColor80 = RGB ( 255,255,255 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_ForeColor80 );
	}
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKPRI);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BackColor100 = RGB ( 0,0,0 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_BackColor100 );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFOREPRI);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ForeColor100 = RGB ( 255,255,255 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_ForeColor100 );
	}
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szTOPBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_TopBorder = 1.0;
	else
		m_UserVars.m_TopBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBOTTOMBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BottomBorder = 1.0;
	else
		m_UserVars.m_BottomBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szRIGHTBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_RightBorder = 1.25;
	else
		m_UserVars.m_RightBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLEFTBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_LeftBorder = 1.25;
	else
		m_UserVars.m_LeftBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSTRING);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintString = "";
	else 
		m_UserVars.m_PrintString = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSHADE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintShading = 0;
	else 
		m_UserVars.m_PrintShading = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSTRINGFLAG);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintStringFlag = 0;
	else 
		m_UserVars.m_PrintStringFlag = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTPAGENUMBER);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintPageNumber = 3;
	else 
		m_UserVars.m_PrintPageNumber = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTPAGEOFFSET);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintPageOffset = 0;
	else 
		m_UserVars.m_PrintPageOffset = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTWEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontWeight = FW_NORMAL;
	else 
		m_UserVars.m_PrintFontWeight = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTSIZE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontSize = 12;
	else 
		m_UserVars.m_PrintFontSize = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTGENEBLOCK);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintGeneBlock = 0;
	else 
		m_UserVars.m_PrintGeneBlock = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTNAME);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontName = "Times New Roman";
	else 
		m_UserVars.m_PrintFontName = strBuffer;


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szWIDTHMODE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_WidthMode = 0;
	else
		m_UserVars.m_WidthMode = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFIXEDX);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FixedXSize = 50;
	else
		m_UserVars.m_FixedXSize = atoi(strBuffer);
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCONSENSUS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ConsensusLine = 1;
	else
		m_UserVars.m_ConsensusLine = atoi(strBuffer);
	
	// Set Current Score Array
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSCORETABLE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_CurrentScoreTable = 2;
	else
		m_UserVars.m_CurrentScoreTable = atoi(strBuffer);

	// Default to show tail.
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWTAIL);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowTail = 1;
	else
		m_UserVars.m_ShowTail = atoi(strBuffer);

	// Default to portrait
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szORIENTATION);
	if (strBuffer.IsEmpty())
		m_UserVars.m_Orientation = 0;
	else
		m_UserVars.m_Orientation = atoi(strBuffer);

	// Default to '-'
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szGAPIND);
	if (strBuffer.IsEmpty())
		m_UserVars.m_GapInd = 0;
	else
		m_UserVars.m_GapInd = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDTREEWEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_DispTreeWeight = 1;
	else
		m_UserVars.m_DispTreeWeight = atoi(strBuffer);


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSCOREMETH);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ScoringMethod = SCOREPAIR;
	else
		m_UserVars.m_ScoringMethod = atoi(strBuffer);


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTWIDTH);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictWidth = 0;
	else
		m_UserVars.m_PictWidth = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTHEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictHeight = 0;
	else
		m_UserVars.m_PictHeight = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTASCENT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictAscent = 0;
	else
		m_UserVars.m_PictAscent = atoi(strBuffer);

	// Set default no project type.
	m_UserVars.m_ProjectType = 0;
	
	// Display Groups
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szGROUPDISPMODE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
	else
		m_UserVars.m_GroupDisplayMode = atoi(strBuffer);

	// Display Groups
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCOLORSEQNAMES);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ColorSeqNames = 0;
	else
		m_UserVars.m_ColorSeqNames = atoi(strBuffer);


	// Group Conserved Level
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szGROUPCONSLEVEL);
	if (strBuffer.IsEmpty())
		m_UserVars.m_GroupConsLevel = 100.0;
	else
		m_UserVars.m_GroupConsLevel = atof(strBuffer);

	// Group Conserved Level
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPCRSIMILARITIES);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PCRSimilarities = "";
	else
		m_UserVars.m_PCRSimilarities = strBuffer;

	// Group Conserved Level
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPCRLEVEL);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PCRLevel = 0.0;
	else
		m_UserVars.m_PCRLevel = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerSymb);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerSymb = '*';		// *  symbol, 
	else 
		m_UserVars.m_MarkerSymb = strBuffer[0];

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerSpacing);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerSpacing = 10;	// 10  spacing between symbols, 
	else 
		m_UserVars.m_MarkerSpacing = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerReplace);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerReplace = 2;	// 2  how often to replace a symbol with a number, 
	else 
		m_UserVars.m_MarkerReplace = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerStart);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerStart = 1;		// -13  the number to be assigned to the first column of the alignment,
	else 
		m_UserVars.m_MarkerStart = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerEnable);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerEnable = 1;		// is it enabled?
	else 
		m_UserVars.m_MarkerEnable = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szConservedGap);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ConservedGap = ' ';
	else 
		m_UserVars.m_ConservedGap = strBuffer[0];

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szResidueUpper);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ResidueUpper = 0;
	else 
		m_UserVars.m_ResidueUpper = atoi(strBuffer);

// NEW

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szChemPropCysteine);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ChemPropCysteine = 0;
	else 
		m_UserVars.m_ChemPropCysteine = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szChemPropShowProp);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ChemPropShowProp = 0;
	else 
		m_UserVars.m_ChemPropShowProp = atoi(strBuffer);


	for ( i=0; i < NUMCHEMPROP; ++i ) {
		switch (i) {
		case 0:
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "PX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM0);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM0);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(255,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN0);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 1:
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "GX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM1);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM1);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(255,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN1);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 2: // Tiny
			m_UserVars.ChemGroupRed[i].Chem = "ACGSX";
			m_UserVars.ChemGroupOxi[i].Chem = "AGSX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM2);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM2);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(255,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN2);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 3: // Small
			m_UserVars.ChemGroupRed[i].Chem = "VAGDNSTPX";
			m_UserVars.ChemGroupOxi[i].Chem = "VCAGDNSTPX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM3);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM3);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(255,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN3);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 4: // Positive
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "HKRX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM4);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(255,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM4);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN4);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}

			break;
		case 5: // Aromatic
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "FYWHX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM5);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM5);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(128,128,128) ;
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN5);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 6:  // Negative
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "EDX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM6);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM6);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN6);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 7:  // Charged
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "HKREDX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM7);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(255,255,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM7);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,0,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN7);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 8:	// Amphoteric
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "HREQDNBZX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM8);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(255,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM8);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,255,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN8);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 9:  // Polar
			m_UserVars.ChemGroupRed[i].Chem = "CYWHKREQDNSTBZX";
			m_UserVars.ChemGroupOxi[i].Chem = "YWHKREQDNSTBZX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM9);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(0,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM9);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,255,0) ;
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN9);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 10:  // Aliphatic
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "ILVAX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM10);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(255,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM10);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(128,128,128);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN10);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		case 11: // Hydrophobic
			m_UserVars.ChemGroupRed[i].Chem = m_UserVars.ChemGroupOxi[i].Chem = "ILVCAGMFYWHTPX";
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEM11);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].TextColor = RGB(255,255,255);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].TextColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEM11);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemGroupOxi[i].BackColor = RGB(0,0,0);
			else {
				DecodeColor( strBuffer, &m_UserVars.ChemGroupOxi[i].BackColor );
			}
			strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCHEMPROPEN11);
			if (strBuffer.IsEmpty())
				m_UserVars.ChemPropEnabled[i] = 1;
			else {
				m_UserVars.ChemPropEnabled[i] = atoi(strBuffer);
			}
			break;
		}
	}


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEMCONS0);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[0].TextColor = RGB(255,255,255);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[0].TextColor );
	}
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEMCONS0);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[0].BackColor = RGB(0,0,0);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[0].BackColor );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEMCONS1);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[1].TextColor = RGB(255,255,255);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[1].TextColor );
	}
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEMCONS1);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[1].BackColor = RGB(128,128,128);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[1].BackColor );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFORECHEMCONS2);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[2].TextColor = RGB(0,0,0);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[2].TextColor );
	}
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKCHEMCONS2);
	if (strBuffer.IsEmpty())
		m_UserVars.ChemCons[2].BackColor = RGB(192,192,192);
	else {
		DecodeColor( strBuffer, &m_UserVars.ChemCons[2].BackColor );
	}


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szStrLead);
	if (strBuffer.IsEmpty())
		m_UserVars.m_strLead = " : ";
	else
		m_UserVars.m_strLead = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szStrTail);
	if (strBuffer.IsEmpty())
		m_UserVars.m_strTail = " : ";
	else
		m_UserVars.m_strTail = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMaxNameLength);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MaxNameLength = 10;
	else 
		m_UserVars.m_MaxNameLength = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDNAAmbEn);
	if (strBuffer.IsEmpty())
		m_UserVars.m_DNAAmbEn = 1;
	else 
		m_UserVars.m_DNAAmbEn = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMCOLINCH);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumColInch = 24;
	else
		m_UserVars.m_SumColInch = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUM2WID);
	if (strBuffer.IsEmpty())
		m_UserVars.m_Sum2Wid = 0;
	else
		m_UserVars.m_Sum2Wid = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMDEFDIS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumDefDis = 0;
	else
		m_UserVars.m_SumDefDis = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMTEXTBLACK);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumTextBlack = 0;
	else
		m_UserVars.m_SumTextBlack = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFILENAME);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFileName = 0;
	else
		m_UserVars.m_PrintFileName = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTDATE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintDate = 0;
	else
		m_UserVars.m_PrintDate = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szTRANSTILDE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_TransTilde = 0;
	else
		m_UserVars.m_TransTilde = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWMANSHADE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowManShade = 1;
	else
		m_UserVars.m_ShowManShade = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWCOMMENTS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowComments = 1;
	else
		m_UserVars.m_ShowComments = atoi(strBuffer);
	// Search ..

///new 	
	
	int SrchLevelCount = 0;
	stcSearch *tSE;
	// CPtrArray
	// Clear out Old Search Stuff
	ClearSearch(&m_UserVars);
	ClearLogOdds(&m_UserVars);

	while ( 1 ) {
	
		sprintf ( DecodeBuff, "%sS%d", szLISTSRCH, SrchLevelCount + 1 );

		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );

		if (strBuffer.IsEmpty()) {
				break;
		}


		int RowCount = 0;
		tSE = new stcSearch;
		if ( tSE == 0 ) {
			AfxMessageBox("getinidefaults:new:fail:stcSearch");
			return;
		}

		// Fill in array with new values.
		tSE->strSearch = strBuffer;

		sprintf ( DecodeBuff, "%sN%d", szLISTSRCH, SrchLevelCount + 1 );

		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );

		tSE->strName = strBuffer;

		sprintf ( DecodeBuff, "%sD%d", szLISTSRCH, SrchLevelCount + 1 );
		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );
		tSE->strDescrip = strBuffer;

		sprintf ( DecodeBuff, "%sE%d", szLISTSRCH, SrchLevelCount + 1 );
		tSE->iEnabled = AfxGetApp()->GetProfileInt(szUDSection, DecodeBuff, 1 );

		sprintf ( DecodeBuff, "%sT%d", szLISTSRCH, SrchLevelCount + 1 );
		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );

		if (strBuffer.IsEmpty()) {
			m_UserVars.listSearch.AddTail(tSE);
			continue;
		}

		DecodeColor( strBuffer, &tSE->rgbText );

		sprintf ( DecodeBuff, "%sB%d", szLISTSRCH, SrchLevelCount + 1 );

		strBuffer = AfxGetApp()->GetProfileString(szUDSection, DecodeBuff );

		if (strBuffer.IsEmpty()) {
			m_UserVars.listSearch.AddTail(tSE);
			continue;
		}

		DecodeColor( strBuffer, &tSE->rgbBack );

		m_UserVars.listSearch.AddTail(tSE);

		SrchLevelCount++;
	}
	
//	LoadSearch();
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szProSite);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ProSite = 0;
	else 
		m_UserVars.m_ProSite = atoi(strBuffer);


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szOVERLAPCOLOR);
	if (strBuffer.IsEmpty())
		m_UserVars.m_OverlapColor = RGB(0,255,0);
	else {
		DecodeColor( strBuffer, &m_UserVars.m_OverlapColor );
	}
	
// End Search
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSMIN);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsMin = 0.0;
	else 
		m_UserVars.m_dLogOddsMin = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSBESTN);
	if (strBuffer.IsEmpty())
		m_UserVars.m_iLogOddsBestN = 3;
	else 
		m_UserVars.m_iLogOddsBestN = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSMODE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_iLogOddsMode = 0;
	else 
		m_UserVars.m_iLogOddsMode = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSOVERLAP);
	if (strBuffer.IsEmpty())
		m_UserVars.m_rgbLogOddsOverlap = RGB(0,255,0);
	else {
		DecodeColor( strBuffer, &m_UserVars.m_rgbLogOddsOverlap );
	}

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSNOOV);
	if (strBuffer.IsEmpty())
		m_UserVars.m_iLogOddsNoOv = 0;
	else 
		m_UserVars.m_iLogOddsNoOv = atoi(strBuffer);
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSTL1);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsTL1 = 90.0;
	else 
		m_UserVars.m_dLogOddsTL1 = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSTL2);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsTL2 = 70.0;
	else 
		m_UserVars.m_dLogOddsTL2 = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSTL3);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsTL3 = 50.0;
	else 
		m_UserVars.m_dLogOddsTL3 = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSMPC);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsMPC = 5.0;
	else 
		m_UserVars.m_dLogOddsMPC = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSOUTTAB);
	if (strBuffer.IsEmpty())
		m_UserVars.m_iLogOddsOutTab = 2;
	else 
		m_UserVars.m_iLogOddsOutTab = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSBACK);
	if (strBuffer.IsEmpty())
		m_UserVars.m_iLogOddsBack = 0;
	else 
		m_UserVars.m_iLogOddsBack = atoi(strBuffer);


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSSTA);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsStA = 235091.0;
	else 
		m_UserVars.m_dLogOddsStA = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSSTC);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsStC = 181410.0;
	else 
		m_UserVars.m_dLogOddsStC = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSSTG);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsStG = 185091.0;
	else 
		m_UserVars.m_dLogOddsStG = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLOGODDSSTT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_dLogOddsStT = 226863.0;
	else 
		m_UserVars.m_dLogOddsStT = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDNATRANSNAME);
	if (strBuffer.IsEmpty())
		m_UserVars.m_DNATransName = "Standard";
	else
		m_UserVars.m_DNATransName = strBuffer;
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDNATRANS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_DNATrans = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";
	else
		m_UserVars.m_DNATrans = strBuffer;
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szDNATRANSSTART);
	if (strBuffer.IsEmpty())
		m_UserVars.m_DNATransStart = "-----------------------------------M----------------------------";
	else
		m_UserVars.m_DNATransStart = strBuffer;

	
	m_UserVars.m_RepExactMatch = AfxGetApp()->GetProfileInt(szUDSection, szRepExactMatch, (int)TRUE );
	m_UserVars.m_RepJuxtaposition = AfxGetApp()->GetProfileInt(szUDSection, szRepJuxtaposition, (int)TRUE );
	m_UserVars.m_RepAlignedGaps = AfxGetApp()->GetProfileInt(szUDSection, szRepAlignedGaps, (int)TRUE );
	m_UserVars.m_RepAbsoluteVal = AfxGetApp()->GetProfileInt(szUDSection, szRepAbsoluteVal, (int)TRUE );
	m_UserVars.m_RepPercentVal = AfxGetApp()->GetProfileInt(szUDSection, szRepPercentVal, (int)TRUE );
	m_UserVars.m_RepOutMatrix = AfxGetApp()->GetProfileInt(szUDSection, szRepOutMatrix, 0 );
	m_UserVars.m_RepLabelTop = AfxGetApp()->GetProfileInt(szUDSection, szRepLabelTop, 0 );
	m_UserVars.m_RepLabelSingle = AfxGetApp()->GetProfileInt(szUDSection, szRepLabelSingle, 0 );
	m_UserVars.m_RepIncAA = AfxGetApp()->GetProfileInt(szUDSection, szRepIncAA, (int)TRUE );
	
	m_UserVars.m_MakeBackups = AfxGetApp()->GetProfileInt(szUDSection, szMakeBackups, (int)TRUE );
	m_UserVars.m_LocAfterName = AfxGetApp()->GetProfileInt(szUDSection, szLocAfterName, (int)FALSE );
	m_UserVars.m_LocAfterSeq = AfxGetApp()->GetProfileInt(szUDSection, szLocAfterSeq, (int)TRUE );


	// Group Conserved Level
	// Init these empty.
//	m_UserVars.m_TitleProgram[0] = 0;
//	m_UserVars.m_TitleScoreMatrix[0] = 0;
//	m_UserVars.m_TitleOpenGap[0] = 0;
//	m_UserVars.m_TitleExtendGap[0] = 0;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHADEGROUPS);
	if (strBuffer.IsEmpty()) {

		SetShadeGroupDefault(&m_UserVars.m_ShadePairArray, m_UserVars.m_CurrentScoreTable);

	} else {

		int RowCount = 0;
		ShadePairStruct *tSPS;
	
		// CPtrArray
		// Clear out Old Array
		int count = m_UserVars.m_ShadePairArray.GetSize();
		for ( i = 0; i < count; ++i ) {
			tSPS = (ShadePairStruct *)m_UserVars.m_ShadePairArray[i];
			delete tSPS;
		}
		m_UserVars.m_ShadePairArray.RemoveAll();
	
		// Fill in array with new values.
		const char *pc = strBuffer;
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
				AfxMessageBox("getinidefaults:new:fail:1");
				return;
			}
			tSPS->RowNum = RowCount + 1;
			strcpy ( tSPS->Group, DecodeBuff );
			m_UserVars.m_ShadePairArray.Add(tSPS);

			RowCount++;
		}
	}
	
	// INit structure with PSDB info.
	
//	m_UserVars.m_Stc.LoadSCMIPROTPRED( );
//	m_UserVars.m_Stc.LoadSCMIDSSP( );

	// Init Base DisplayVars	
	GetIniDisplayVars( &m_UserVars.m_Vars );

}

void
CGenedocDoc::SetIniDefaults()
{

	TCHAR szBuffer[256];
	int i;

	sprintf( szBuffer, "%d", m_UserVars.m_FontWeight );
	AfxGetApp()->WriteProfileString(szUDSection, szFONTWEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_FontSize );
	AfxGetApp()->WriteProfileString(szUDSection, szFONTSIZE, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_BackColor0), 
		GetGValue(m_UserVars.m_BackColor0), 
		GetBValue(m_UserVars.m_BackColor0) 
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKBASE, szBuffer);


	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_ForeColor0),
		GetGValue(m_UserVars.m_ForeColor0),
		GetBValue(m_UserVars.m_ForeColor0)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFOREBASE, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_BackColor60),
		GetGValue(m_UserVars.m_BackColor60),
		GetBValue(m_UserVars.m_BackColor60)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKTERT, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_ForeColor60),
		GetGValue(m_UserVars.m_ForeColor60),
		GetBValue(m_UserVars.m_ForeColor60)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORETERT, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_BackColor80),
		GetGValue(m_UserVars.m_BackColor80),
		GetBValue(m_UserVars.m_BackColor80)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKSEC, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_ForeColor80),
		GetGValue(m_UserVars.m_ForeColor80),
		GetBValue(m_UserVars.m_ForeColor80)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORESEC, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_BackColor100),
		GetGValue(m_UserVars.m_BackColor100),
		GetBValue(m_UserVars.m_BackColor100)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKPRI, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_ForeColor100),
		GetGValue(m_UserVars.m_ForeColor100),
		GetBValue(m_UserVars.m_ForeColor100)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFOREPRI, szBuffer);


	sprintf( szBuffer, "%f", m_UserVars.m_TopBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szTOPBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_BottomBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szBOTTOMBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_RightBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szRIGHTBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_LeftBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szLEFTBORD, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintString );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSTRING, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintShading );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSHADE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintStringFlag );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSTRINGFLAG, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintPageNumber );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTPAGENUMBER, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintPageOffset );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTPAGEOFFSET, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFontWeight );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTWEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFontSize );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTSIZE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintGeneBlock );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTGENEBLOCK, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintFontName );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTNAME, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_Vars.GetPrimaryLevel() );
	AfxGetApp()->WriteProfileString(szUDSection, szPRILEVEL, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_Vars.GetSecondaryLevel() );
	AfxGetApp()->WriteProfileString(szUDSection, szSECLEVEL, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_Vars.GetTertiaryLevel() );
	AfxGetApp()->WriteProfileString(szUDSection, szTERTLEVEL, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_WidthMode );
	AfxGetApp()->WriteProfileString(szUDSection, szWIDTHMODE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_FixedXSize );
	AfxGetApp()->WriteProfileString(szUDSection, szFIXEDX, szBuffer);
	
	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetModeConserved() );
	AfxGetApp()->WriteProfileString(szUDSection, szSHADEMODE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ConsensusLine);
	AfxGetApp()->WriteProfileString(szUDSection, szCONSENSUS, szBuffer);
	
	sprintf( szBuffer, "%d", m_UserVars.m_CurrentScoreTable);
	AfxGetApp()->WriteProfileString(szUDSection, szSCORETABLE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetLastShadeLevel() );
	AfxGetApp()->WriteProfileString(szUDSection, szLASTSHADE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ShowTail);
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWTAIL, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Orientation);
	AfxGetApp()->WriteProfileString(szUDSection, szORIENTATION, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_GapInd);
	AfxGetApp()->WriteProfileString(szUDSection, szGAPIND, szBuffer);

	// Default to Diff/Consensus
	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetDiffMode() );
	AfxGetApp()->WriteProfileString(szUDSection, szDIFFMODE, szBuffer);


	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetGroupEnabled() );
	AfxGetApp()->WriteProfileString(szUDSection, szGROUPENABLED, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetPropStyle() );
	AfxGetApp()->WriteProfileString(szUDSection, szPROPSTYLE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetResidueMode() );
	AfxGetApp()->WriteProfileString(szUDSection, szRESIDUEMODE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetConsSubStyle() );
	AfxGetApp()->WriteProfileString(szUDSection, szCONSSUBSTYLE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_DispTreeWeight );
	AfxGetApp()->WriteProfileString(szUDSection, szDTREEWEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ScoringMethod );
	AfxGetApp()->WriteProfileString(szUDSection, szSCOREMETH, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictWidth );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTWIDTH, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictHeight );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTHEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictAscent );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTASCENT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_GroupDisplayMode );
	AfxGetApp()->WriteProfileString(szUDSection, szGROUPDISPMODE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ColorSeqNames );
	AfxGetApp()->WriteProfileString(szUDSection, szCOLORSEQNAMES, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_GroupConsLevel );
	AfxGetApp()->WriteProfileString(szUDSection, szGROUPCONSLEVEL, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PCRSimilarities );
	AfxGetApp()->WriteProfileString(szUDSection, szPCRSIMILARITIES, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_PCRLevel );
	AfxGetApp()->WriteProfileString(szUDSection, szPCRLEVEL, szBuffer);

	sprintf( szBuffer, "%c", m_UserVars.m_MarkerSymb );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerSymb, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerSpacing );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerSpacing, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerReplace );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerReplace, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerStart );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerStart, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerEnable );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerEnable, szBuffer);

	sprintf( szBuffer, "%c", m_UserVars.m_ConservedGap );
	AfxGetApp()->WriteProfileString(szUDSection, szConservedGap, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ResidueUpper );
	AfxGetApp()->WriteProfileString(szUDSection, szResidueUpper, szBuffer);


	sprintf( szBuffer, "%d", m_UserVars.m_ChemPropCysteine );
	AfxGetApp()->WriteProfileString(szUDSection, szChemPropCysteine, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ChemPropShowProp );
	AfxGetApp()->WriteProfileString(szUDSection, szChemPropShowProp, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[0].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[0].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[0].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM0, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[0].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[0].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[0].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM0, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[0] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN0, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[1].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[1].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[1].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM1, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[1].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[1].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[1].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM1, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[1] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN1, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[2].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[2].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[2].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM2, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[2].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[2].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[2].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM2, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[2] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN2, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[3].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[3].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[3].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM3, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[3].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[3].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[3].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM3, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[3] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN3, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[4].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[4].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[4].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM4, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[4].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[4].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[4].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM4, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[4] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN4, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[5].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[5].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[5].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM5, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[5].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[5].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[5].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM5, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[5] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN5, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[6].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[6].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[6].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM6, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[6].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[6].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[6].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM6, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[6] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN6, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[7].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[7].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[7].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM7, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[7].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[7].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[7].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM7, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[7] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN7, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[8].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[8].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[8].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM8, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[8].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[8].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[8].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM8, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[8] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN8, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[9].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[9].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[9].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM9, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[9].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[9].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[9].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM9, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[9] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN9, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[10].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[10].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[10].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM10, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[10].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[10].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[10].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM10, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[10] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN10, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[11].TextColor), 
		GetGValue(m_UserVars.ChemGroupOxi[11].TextColor), 
		GetBValue(m_UserVars.ChemGroupOxi[11].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEM11, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemGroupOxi[11].BackColor), 
		GetGValue(m_UserVars.ChemGroupOxi[11].BackColor), 
		GetBValue(m_UserVars.ChemGroupOxi[11].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEM11, szBuffer);
	sprintf( szBuffer, "%d", m_UserVars.ChemPropEnabled[11] );
	AfxGetApp()->WriteProfileString(szUDSection, szCHEMPROPEN11, szBuffer);


	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[0].TextColor), 
		GetGValue(m_UserVars.ChemCons[0].TextColor), 
		GetBValue(m_UserVars.ChemCons[0].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEMCONS0, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[0].BackColor), 
		GetGValue(m_UserVars.ChemCons[0].BackColor), 
		GetBValue(m_UserVars.ChemCons[0].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEMCONS0, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[1].TextColor), 
		GetGValue(m_UserVars.ChemCons[1].TextColor), 
		GetBValue(m_UserVars.ChemCons[1].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEMCONS1, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[1].BackColor), 
		GetGValue(m_UserVars.ChemCons[1].BackColor), 
		GetBValue(m_UserVars.ChemCons[1].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEMCONS1, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[2].TextColor), 
		GetGValue(m_UserVars.ChemCons[2].TextColor), 
		GetBValue(m_UserVars.ChemCons[2].TextColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFORECHEMCONS2, szBuffer);
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.ChemCons[2].BackColor), 
		GetGValue(m_UserVars.ChemCons[2].BackColor), 
		GetBValue(m_UserVars.ChemCons[2].BackColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKCHEMCONS2, szBuffer);


	sprintf( szBuffer, "%d", m_UserVars.m_MaxNameLength );
	AfxGetApp()->WriteProfileString(szUDSection, szMaxNameLength, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_strLead );
	AfxGetApp()->WriteProfileString(szUDSection, szStrLead, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_strTail );
	AfxGetApp()->WriteProfileString(szUDSection, szStrTail, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_DNAAmbEn );
	AfxGetApp()->WriteProfileString(szUDSection, szDNAAmbEn, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_SumColInch );
	AfxGetApp()->WriteProfileString(szUDSection, szSUMCOLINCH, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Sum2Wid );
	AfxGetApp()->WriteProfileString(szUDSection, szSUM2WID, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_SumDefDis );
	AfxGetApp()->WriteProfileString(szUDSection, szSUMDEFDIS, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_SumTextBlack );
	AfxGetApp()->WriteProfileString(szUDSection, szSUMTEXTBLACK, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFileName );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFILENAME, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintDate );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTDATE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_TransTilde );
	AfxGetApp()->WriteProfileString(szUDSection, szTRANSTILDE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ShowManShade );
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWMANSHADE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ShowComments );
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWCOMMENTS, szBuffer);

	szBuffer[0] = '\0';
	int Count = m_UserVars.m_ShadePairArray.GetSize();
	for ( i =0; i < Count; ++i ) {
		strcat ( szBuffer, (char *)((ShadePairStruct *)m_UserVars.m_ShadePairArray[i])->Group );
		strcat ( szBuffer, "," );
	}
	AfxGetApp()->WriteProfileString(szUDSection, szSHADEGROUPS, szBuffer);


	szBuffer[0] = '\0';


//	CPtrArray	m_PropertyArray;		// Hoding a list of PropertyStruct's
	// Another various flags string
// delete old ones first
	
	char PropBuff[20];
	PropertyStruct *tPS;
	
	for ( int PropLevelCount = 0; PropLevelCount < 3; ++PropLevelCount ) {
		i = 1;
		while ( 1 ) {
			sprintf ( PropBuff, "%s%d%d", szPROPGROUPS, PropLevelCount + 1, i++ );
			if ( AfxGetApp()->GetProfileString(szUDSection, PropBuff, szBuffer).IsEmpty() ) break;
			szBuffer[0] = 0;
			AfxGetApp()->WriteProfileString(szUDSection, PropBuff, szBuffer);
		}
	}

	for (int PropLevelCount = 0; PropLevelCount < 3; ++PropLevelCount ) {

		Count = m_UserVars.m_Vars.GetProperty().GetArray(PropLevelCount)->GetSize();
	
		for ( i =0; i < Count; ++i ) {
			tPS = m_UserVars.m_Vars.GetProperty().GetPropertyStruct(PropLevelCount,i);
			sprintf ( PropBuff, "%s%d%d", szPROPGROUPS, PropLevelCount + 1, i + 1 );
			sprintf ( szBuffer, "%s,%3d%3d%3d,%3d%3d%3d", 
				tPS->Group, 
				GetRValue ( tPS->TextColor ), 
				GetGValue ( tPS->TextColor ), 
				GetBValue ( tPS->TextColor ), 
				GetRValue ( tPS->BkColor ), 
				GetGValue ( tPS->BkColor ), 
				GetBValue ( tPS->BkColor )
			);
	
			AfxGetApp()->WriteProfileString(szUDSection, PropBuff, szBuffer);
		}
	}

	char SrchBuff[256];
	stcSearch *tSE;
	
	i = 1;
	while ( 1 ) {
		sprintf ( SrchBuff, "%sS%d", szLISTSRCH, i );
		if ( AfxGetApp()->GetProfileString(szUDSection, SrchBuff, szBuffer).IsEmpty() ) break;
		szBuffer[0] = 0;
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sN%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sD%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sT%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sE%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sB%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		i++;
	}


	Count = m_UserVars.listSearch.GetCount();

	POSITION tPOS = m_UserVars.listSearch.GetHeadPosition();
	i = 1;
	while (tPOS != NULL ) {
		tSE = (stcSearch*)m_UserVars.listSearch.GetNext(tPOS);
		sprintf ( SrchBuff, "%sS%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, (const char *)tSE->strSearch );

		sprintf ( SrchBuff, "%sN%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, (const char *)tSE->strName );

		sprintf ( SrchBuff, "%sD%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, (const char *)tSE->strDescrip );

		sprintf ( SrchBuff, "%sE%d", szLISTSRCH, i );
		AfxGetApp()->WriteProfileInt(szUDSection, SrchBuff, tSE->iEnabled );

		sprintf ( SrchBuff, "%sT%d", szLISTSRCH, i );
		sprintf ( szBuffer, "%3d%3d%3d", 
			GetRValue ( tSE->rgbText ), 
			GetGValue ( tSE->rgbText ), 
			GetBValue ( tSE->rgbText ) 
		);

		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		sprintf ( SrchBuff, "%sB%d", szLISTSRCH, i );
		sprintf ( szBuffer, "%3d%3d%3d", 
			GetRValue ( tSE->rgbBack ), 
			GetGValue ( tSE->rgbBack ), 
			GetBValue ( tSE->rgbBack ) 
		);

		AfxGetApp()->WriteProfileString(szUDSection, SrchBuff, szBuffer);

		i++;
	}
	
	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_OverlapColor), 
		GetGValue(m_UserVars.m_OverlapColor), 
		GetBValue(m_UserVars.m_OverlapColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szOVERLAPCOLOR, szBuffer);
	

	sprintf( szBuffer, "%d", m_UserVars.m_Vars.GetIdentDisplayStyle() );
	AfxGetApp()->WriteProfileString(szUDSection, szIDENTDISPSTYLE, szBuffer);


	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsMin );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSMIN, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_iLogOddsBestN );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSBESTN, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_iLogOddsMode );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSMODE, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_rgbLogOddsOverlap), 
		GetGValue(m_UserVars.m_rgbLogOddsOverlap), 
		GetBValue(m_UserVars.m_rgbLogOddsOverlap)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSOVERLAP, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_iLogOddsNoOv );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSNOOV, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsTL1 );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSTL1, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsTL2 );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSTL2, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsTL3 );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSTL3, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsMPC );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSMPC, szBuffer);

	sprintf( szBuffer, "%i", m_UserVars.m_iLogOddsOutTab );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSOUTTAB, szBuffer);

	sprintf( szBuffer, "%i", m_UserVars.m_iLogOddsBack );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSBACK, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsStA );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSSTA, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsStC );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSSTC, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsStG );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSSTG, szBuffer);

	sprintf( szBuffer, "%lf", m_UserVars.m_dLogOddsStT );
	AfxGetApp()->WriteProfileString(szUDSection, szLOGODDSSTT, szBuffer);
	
	sprintf( szBuffer, "%s", m_UserVars.m_DNATransName );
	AfxGetApp()->WriteProfileString(szUDSection, szDNATRANSNAME, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_DNATrans );
	AfxGetApp()->WriteProfileString(szUDSection, szDNATRANS, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_DNATransStart );
	AfxGetApp()->WriteProfileString(szUDSection, szDNATRANSSTART, szBuffer);

	AfxGetApp()->WriteProfileInt(szUDSection, szRepExactMatch, m_UserVars.m_RepExactMatch );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepJuxtaposition, m_UserVars.m_RepJuxtaposition );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepAlignedGaps, m_UserVars.m_RepAlignedGaps );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepAbsoluteVal, m_UserVars.m_RepAbsoluteVal );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepPercentVal, m_UserVars.m_RepPercentVal );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepOutMatrix, m_UserVars.m_RepOutMatrix );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepLabelTop, m_UserVars.m_RepLabelTop );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepLabelSingle, m_UserVars.m_RepLabelSingle );
	AfxGetApp()->WriteProfileInt(szUDSection, szRepIncAA, m_UserVars.m_RepIncAA );

	AfxGetApp()->WriteProfileInt(szUDSection, szMakeBackups, m_UserVars.m_MakeBackups );
	AfxGetApp()->WriteProfileInt(szUDSection, szLocAfterName, m_UserVars.m_LocAfterName );
	AfxGetApp()->WriteProfileInt(szUDSection, szLocAfterSeq, m_UserVars.m_LocAfterSeq );
//	
	
	// End User Vars default init
}

