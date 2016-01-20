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
// geneddoc.cpp : implementation of the CGenedocDoc class
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenedocDoc

IMPLEMENT_DYNCREATE(CGenedocDoc, CDocument)

BEGIN_MESSAGE_MAP(CGenedocDoc, CDocument)
	//{{AFX_MSG_MAP(CGenedocDoc)
	ON_COMMAND(IDM_GENESCOREFILE, OnGenescorefile)
	ON_COMMAND(IDM_GENESTATFILE, OnGenestatfile)
	ON_COMMAND(IDM_CONFIGURE, OnConfigure)
	ON_COMMAND(IDM_GENEEDITSEQ, OnGeneeditseq)
	ON_COMMAND(IDM_GENESAVEINI, SetIniDefaults)
	ON_COMMAND(IDM_GENELOADINI, OnGeneloadini)
	ON_COMMAND(IDM_TITLINGF, OnTitlingf)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(IDM_PHYLODLG, OnPhylodlg)
	ON_COMMAND(IDM_PHYLOVIEW, OnPhyloview)
	ON_COMMAND(IDM_GENEVIEW, OnGeneview)
	ON_COMMAND(IDM_GENESCOREPAIR, OnGenescorepair)
	ON_UPDATE_COMMAND_UI(IDM_GENESCOREPAIR, OnUpdateGenescorepair)
	ON_COMMAND(IDM_GENESCORETREE, OnGenescoretree)
	ON_UPDATE_COMMAND_UI(IDM_GENESCORETREE, OnUpdateGenescoretree)
	ON_COMMAND(IDM_SHOWTABLE, OnShowtable)
	ON_COMMAND(IDM_GENESCORENUMB, OnGenescorenumb)
	ON_UPDATE_COMMAND_UI(IDM_GENESCORENUMB, OnUpdateGenescorenumb)
	ON_COMMAND(IDM_GENESCOREINFO, OnGenescoreinfo)
	ON_UPDATE_COMMAND_UI(IDM_GENESCOREINFO, OnUpdateGenescoreinfo)
	ON_UPDATE_COMMAND_UI(IDM_PHYLOVIEW, OnUpdatePhyloview)
	ON_UPDATE_COMMAND_UI(IDM_GENESTATFILE, OnUpdateGenestatfile)
	ON_UPDATE_COMMAND_UI(IDM_GENESCOREFILE, OnUpdateGenescorefile)
	ON_COMMAND(IDM_EDITGROUPPROP, OnEditgroupprop)
	ON_COMMAND(IDM_GENESHADEGROUPS, OnGeneshadegroups)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADEGROUPS, OnUpdateGeneshadegroups)
	ON_COMMAND(IDM_GENESHADECONTRAST, OnGeneshadecontrast)
	ON_COMMAND(IDM_GENESHADEGROUPCONSERVE, OnGeneshadegroupconserve)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADECONTRAST, OnUpdateGeneshadecontrast)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADEGROUPCONSERVE, OnUpdateGeneshadegroupconserve)
	ON_COMMAND(IDM_GENESHADECONTRASTNOGAP, OnGeneshadecontrastnogap)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADECONTRASTNOGAP, OnUpdateGeneshadecontrastnogap)
	ON_COMMAND(IDM_STCLOADPSDB, OnStcloadpsdb)
	ON_UPDATE_COMMAND_UI(IDM_STCLOADPSDB, OnUpdateStcloadpsdb)
	ON_COMMAND(IDM_STCLOADUSERFILE, OnStcloaduserfile)
	ON_COMMAND(IDM_STCLEARALL, OnStclearall)
	ON_COMMAND(IDM_STCLOADEMBL, OnStcloadembl)
	ON_UPDATE_COMMAND_UI(IDM_STCLOADEMBL, OnUpdateStcloadembl)
	ON_COMMAND(IDM_GENEAUTOSHADE2, OnGeneautoshade2)
	ON_UPDATE_COMMAND_UI(IDM_GENEAUTOSHADE2, OnUpdateGeneautoshade2)
	ON_COMMAND(IDM_GENEAUTOSHADE3, OnGeneautoshade3)
	ON_UPDATE_COMMAND_UI(IDM_GENEAUTOSHADE3, OnUpdateGeneautoshade3)
	ON_COMMAND(IDM_GENEAUTOSHADE4, OnGeneautoshade4)
	ON_UPDATE_COMMAND_UI(IDM_GENEAUTOSHADE4, OnUpdateGeneautoshade4)
	ON_COMMAND(IDM_GENECLEARSHADE, OnGeneclearshade)
	ON_UPDATE_COMMAND_UI(IDM_GENECLEARSHADE, OnUpdateGeneclearshade)
	ON_COMMAND(IDM_GENEGROUPENABLE, OnGenegroupenable)
	ON_UPDATE_COMMAND_UI(IDM_GENEGROUPENABLE, OnUpdateGenegroupenable)
	ON_COMMAND(IDM_GENEMODECONSERVED, OnGenemodeconserved)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODECONSERVED, OnUpdateGenemodeconserved)
	ON_COMMAND(IDM_GENEMODEPROPERTY, OnGenemodeproperty)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODEPROPERTY, OnUpdateGenemodeproperty)
	ON_COMMAND(IDM_GENEMODEQUANTIFY, OnGenemodequantify)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODEQUANTIFY, OnUpdateGenemodequantify)
	ON_COMMAND(IDM_GENEMODESTRUCTURE, OnGenemodestructure)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODESTRUCTURE, OnUpdateGenemodestructure)
	ON_COMMAND(IDM_GENERESIDUEMODEDIFF, OnGeneresiduemodediff)
	ON_UPDATE_COMMAND_UI(IDM_GENERESIDUEMODEDIFF, OnUpdateGeneresiduemodediff)
	ON_COMMAND(IDM_GENEDSTATVIEW, OnGenedstatview)
	ON_UPDATE_COMMAND_UI(IDM_GENEDSTATVIEW, OnUpdateGenedstatview)
	ON_COMMAND(IDM_GROUPSHADEPCR, OnGroupshadepcr)
	ON_UPDATE_COMMAND_UI(IDM_GROUPSHADEPCR, OnUpdateGroupshadepcr)
	ON_COMMAND(IDM_GROUPSHADEPCRSIM, OnGroupshadepcrsim)
	ON_UPDATE_COMMAND_UI(IDM_GROUPSHADEPCRSIM, OnUpdateGroupshadepcrsim)
	ON_COMMAND(IDM_FILEIMPORT, OnFileimport)
	ON_COMMAND(IDM_FILEEXPORT, OnFileexport)
	ON_COMMAND(IDM_CLEARGAPCOLS, OnCleargapcols)
	ON_COMMAND(IDM_PLOTSTATDSTAT, OnPlotstatdstat)
	ON_COMMAND(IDM_PLOTFAVSUBS, OnPlotfavsubs)
	ON_COMMAND(IDM_PLOTGROUP, OnPlotgroup)
	ON_COMMAND(IDM_PLOTGROUPFAV, OnPlotgroupfav)
	ON_COMMAND(IDM_GENEMODEPHYSIOCHEM, OnGenemodephysiochem)
	ON_COMMAND(IDM_GENESHADEGROUPPHYSCHEM, OnGeneshadegroupphyschem)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADEGROUPPHYSCHEM, OnUpdateGeneshadegroupphyschem)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODEPHYSIOCHEM, OnUpdateGenemodephysiochem)
	ON_COMMAND(IDM_GENEGROUPSGCONX, OnGenegroupsgconx)
	ON_UPDATE_COMMAND_UI(IDM_GENEGROUPSGCONX, OnUpdateGenegroupsgconx)
	ON_COMMAND(IDM_GENEMODESEARCH, OnGenemodesearch)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODESEARCH, OnUpdateGenemodesearch)
	ON_COMMAND(IDM_GENESHADEGROUPDNA, OnGeneshadegroupdna)
	ON_UPDATE_COMMAND_UI(IDM_GENESHADEGROUPDNA, OnUpdateGeneshadegroupdna)
	ON_COMMAND(IDM_PLOTFRAG, OnPlotfrag)
	ON_COMMAND(IDM_GENEMODESIMILARITY, OnGenemodesimilarity)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODESIMILARITY, OnUpdateGenemodesimilarity)
	ON_COMMAND(IDM_STCLOADPDB, OnStcloadpdb)
	ON_UPDATE_COMMAND_UI(IDM_STCLOADPDB, OnUpdateStcloadpdb)
	ON_COMMAND(IDM_SUMMARYVIEW, OnSummaryview)
	ON_UPDATE_COMMAND_UI(IDM_SUMMARYVIEW, OnUpdateSummaryview)
	ON_COMMAND(IDM_GENEMODELOGODDS, OnGenemodelogodds)
	ON_UPDATE_COMMAND_UI(IDM_GENEMODELOGODDS, OnUpdateGenemodelogodds)
	ON_COMMAND(IDM_LOGODDSVIEW, OnLogoddsview)
	ON_UPDATE_COMMAND_UI(IDM_LOGODDSVIEW, OnUpdateLogoddsview)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDM_COPYCONS, OnCopycons)
	ON_UPDATE_COMMAND_UI(IDM_COPYCONS, OnUpdateCopycons)
	ON_COMMAND(IDM_SHOWMANSHADE, OnShowmanshade)
	ON_UPDATE_COMMAND_UI(IDM_SHOWMANSHADE, OnUpdateShowman)
	ON_COMMAND(IDM_SHOWCOMMENTS, OnShowcomments)
	ON_UPDATE_COMMAND_UI(IDM_SHOWCOMMENTS, OnUpdateShowcom)
	ON_COMMAND(IDM_CLEARCOMMENTS, OnClearcomments)
	ON_COMMAND(IDM_CLEARMANSHADE, OnClearmanshade)
	ON_COMMAND(IDM_SELECTARRSEQ, OnSelectarrseq)
	ON_COMMAND(IDM_GENESCORELO, OnGenescorelo)
	ON_UPDATE_COMMAND_UI(IDM_GENESCORELO, OnUpdateGenescorelo)
	ON_COMMAND(IDM_RESCOREALL, OnRescoreall)
	ON_COMMAND(IDM_COMPLIMENTSEL, OnComplimentsel)
	ON_COMMAND(IDM_GENEREPORTVIEW, OnGenereportview)
	ON_COMMAND(IDM_REGAPDNA, OnRegapdna)
	ON_COMMAND(IDM_SRCHREPVIEW, OnSrchrepview)
	ON_COMMAND(IDM_GENEGELVIEW, OnGenegelview)
	ON_UPDATE_COMMAND_UI(IDM_GENEGELVIEW, OnUpdateGenegelview)
	ON_COMMAND(IDM_ALIGN, OnAlign)
	ON_COMMAND(IDM_MANSHADEREP, OnManshaderep)
	ON_UPDATE_COMMAND_UI(IDM_MANSHADEREP, OnUpdateManshaderep)
	ON_COMMAND(IDM_SHADING_REP, OnShadingRep)
	ON_COMMAND(IDM_CONFIGREPORT, OnConfigreport)
	ON_COMMAND(IDM_CONSPROSITE, OnConsprosite)
	ON_UPDATE_COMMAND_UI(IDM_CONSPROSITE, OnUpdateConsprosite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenedocDoc construction/destruction
ScoreTableStruct ScoreInit[] = {
	{ "Blosum 35", Blosum35, "DE,NQ,ST,KR,FYW,LIVM,","Blosum 35 in 1/4 bits, Entropy = 0.2111, Expected = -0.1550", 0}, 
	{ "Blosum 45", Blosum45, "DE,NH,ST,QKR,FYW,LIVM,", "Blosum 45 in 1/3 bits, Entropy = 0.3795, Expected = -0.2789", 0}, 
	{ "Blosum 62", Blosum62, "DN,EQ,ST,KR,FYW,LIVM,", "Blosum 62 in 1/3 bits, Entropy = 0.6979, Expected = -0.5209", 0 }, 
	{ "Blosum 80", Blosum80, "DN,EQ,ST,KR,FY,LIVM,", "Blosum 80 in 1/3 bits, Entropy = 0.9868, Expected = -0.7442", 0 }, 
	{ "Blosum 100", Blosum100, "DN,EQ,ST,KR,FY,LM,IV,","Blosum 100 in 1/3 bits, Entropy = 1.4516, Expected = -1.0948", 0 }, 
	{ "Dayhoff PAM 120", Pam120, "DEN,HQ,SAT,KR,FY,LIVM,", "Dayhoff PAM 120 in 1/2 bit units.  Entropy = 0.98", 0 },
	{ "Dayhoff PAM 160", Pam160, "DEN,HQ,SAT,KR,FY,LIVM,","Dayhoff PAM 160 similarity matrix.  Entropy = 0.70", 0 },
	{ "Dayhoff PAM 200", Pam200, "DEQ,HN,SAT,KR,FY,LIVM,","Dayhoff PAM 200 similarity matrix.  Entropy = 0.51", 0 }, 
	{ "Dayhoff PAM 250", Pam250, "DENQH,SAT,KR,FY,LIVM,","Dayhoff PAM 250 in 1/3 bit units.  Entropy = 0.36", 0 }, 

	{ "Nucleic Acid PAM 20", dp20, "", "Nucleic Acid PAM 20 similarity matrix.  Entropy = 1.05", 1 }, 
	{ "Nucleic Acid PAM 30", dp30, "", "Nucleic Acid PAM 30 similarity matrix.  Entropy = 0.80", 1 }, 
	{ "Nucleic Acid PAM 47", dp47, "","Nucleic Acid PAM 47 similarity matrix.  Entropy = 0.50", 1 }, 
	{ "Nucleic Acid PAM 50", dp50, "", "Nucleic Acid PAM 50 similarity matrix.  Entropy = 0.47", 1 }, 
	{ "Nucleic Acid PAM 65", dp65, "", "Nucleic Acid PAM 65 similarity matrix.  Entropy = 0.32", 1 }, 
	{ "Nucleic Acid PAM 85", dp85, "", "Nucleic Acid PAM 85 similarity matrix.  Entropy = 0.19", 1 }, 
	{ "Nucleic Acid PAM 110", dp110, "", "Nucleic Acid PAM 110 similarity matrix.  Entropy = 0.10", 1 }, 
	{ "DNA PAM 20", dp20b, "", "DNA PAM 20, 1 transversion / 3 transitions, Entropy = 1.09", 1 }, 
	{ "DNA PAM 50", dp50b, "", "DNA PAM 50, 1 transversion / 3 transitions, Entropy = 0.54", 1 }, 
	{ "DNA PAM 85", dp85b, "", "DNA PAM 85, 1 transversion / 3 transitions, Entropy = 0.26", 1 }, 
	{ "Identity Matrix", IDMat, "", "Identity Matrix:   Identities = 10,    Mismatches = -5", 1 }, 
};


CGenedocDoc::CGenedocDoc()
{
	int i;
	// TODO: add one-time construction code here
	pGSFiller = NULL;
	m_pTextView = NULL;
	m_pTreeView = NULL;
	m_pSummaryView = NULL;
	m_pDStatView = NULL;
	m_pGelView = NULL;

	m_pPGBase = NULL;

	m_TreeDebugOutput = 0;
	m_SummaryMessaged = 0;

	m_pFS.FindStr = "";
	m_pFS.FindFrom = 0;
	m_pFS.MisMatch = 0;
	m_pFS.InsDel = 0;
	m_pFS.rgbText = RGB(0,0,0);
	m_pFS.rgbBack = RGB(0,255,0);
	m_pFS.PrevSeq = -1;

	// Array init	
	ScoreTableStruct *tSTS;

	int ts = sizeof (ScoreInit) / sizeof(ScoreTableStruct);

	for ( i = 0; i < sizeof (ScoreInit) / sizeof(ScoreTableStruct) ; ++i ) {

		tSTS = new ScoreTableStruct;
		if ( tSTS == 0 ) {
			AfxMessageBox( "Geneddoc:new:fail:1" );
			return;
		}

		tSTS->Name = ScoreInit[i].Name;
		tSTS->TableFunction = ScoreInit[i].TableFunction;
		tSTS->ScoreType = ScoreInit[i].ScoreType;
		

		m_UserVars.m_ScoreTableArray.Add( tSTS );
	}
	
	// Add the Base DisplayVars entry ..
	// CDisplayVars *DisplayVars = new CDisplayVars;
	// m_UserVars.m_DisplayVars.AddTail( DisplayVars );

	// Load User Defaults
	GetIniDefaults();

	((CGenedocApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );


	// Load up score table	// CptrArray
	((ScoreTableStruct *)m_UserVars.m_ScoreTableArray.
		GetAt(m_UserVars.m_CurrentScoreTable))->TableFunction( ScoreArray, &NewGap, &GapLen, &CurrentZeroDistance );

}

CGenedocDoc::~CGenedocDoc()
{
	if ( pGSFiller != NULL ) {
		delete pGSFiller;
	}

	ClearUserVars( &m_UserVars );

	ScoreTableStruct *tSTS;
	int count = m_UserVars.m_ScoreTableArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSTS = (ScoreTableStruct *)m_UserVars.m_ScoreTableArray[i];
		delete tSTS;
	}
//	dUserVars->m_ScoreTableArray.RemoveAll();

	if ( m_pPGBase != NULL ) {
		delete m_pPGBase;
	}

}


void
CGenedocDoc::SetShadeGroupDefault(CPtrArray *ShadePairArray, int NewScoreTable)
{ 
	int i;
	ShadePairStruct *tSPS;
	char DecodeBuff[64];

	int count = ShadePairArray->GetSize();

	for ( i = 0; i < count; ++i ) {
		tSPS = (ShadePairStruct *)(*ShadePairArray)[i];
		delete tSPS;
	}
	ShadePairArray->RemoveAll();

	const char *tStr = ScoreInit[NewScoreTable].DefStrings;

	int RowCount = 0;


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
			AfxMessageBox( "Geneddoc:new:fail:2" );
			return;
		}
		tSPS->RowNum = RowCount + 1;
		strcpy ( tSPS->Group, DecodeBuff );
		ShadePairArray->Add(tSPS);

		RowCount++;
	}

} 

const char * 
CGenedocDoc::GetScoreTableDescr(int ScoreTable)
{
	ASSERT ( ScoreTable < (sizeof(ScoreInit) / sizeof(ScoreTableStruct)));
	
	return ScoreInit[ScoreTable].TableDefs;
} 
 


void
CGenedocDoc::SetShadePairArray(CPtrArray *nShadePairArray, CPtrArray *oShadePairArray)
{
	ShadePairStruct *tSPS;
	ShadePairStruct *tSPSn;
	int count = nShadePairArray->GetSize();
	int i;
	for ( i = 0; i < count; ++i ) {
		tSPS = (ShadePairStruct *)(*nShadePairArray)[i];
		delete tSPS;
	}
	nShadePairArray->RemoveAll();

	count = oShadePairArray->GetSize();
	for (i = 0; i < count; ++i ) { 
		tSPS = new ShadePairStruct;
		if ( tSPS == 0 ) {
			AfxMessageBox( "Geneddoc:new:fail:3" );
			return;
		}
		tSPSn = (ShadePairStruct *)oShadePairArray->GetAt(i);

		tSPS->RowNum = tSPSn->RowNum;
		strcpy ( tSPS->Group, tSPSn->Group );

		nShadePairArray->Add( tSPS );
	}

}

CString CGenedocDoc::ConvertPathname( const char *nExt )
{
	char *pName;
   	CString PathName = GetPathName();

	int NameLen = PathName.GetLength();

	pName = PathName.GetBuffer(NameLen);

	int tLen = NameLen - 1;
	int i;
	for ( i = 0; i < 4; ++i ) {
		if ( pName[tLen] == '.' ) {
			break;
		}
		tLen--;
	}

	if ( pName[tLen] == '.' ) {
		i = 0;
		while ( (tLen < NameLen) && (i < 4) ) {
			pName[tLen] = nExt[i];
			i++;
			tLen++;
		}
		PathName.ReleaseBuffer();
	} else {
		PathName.ReleaseBuffer();
		PathName += nExt;
	}
	
	return PathName;
}


void
CGenedocDoc::CheckOrientation()
{
	int nLS = ((CGenedocApp *)AfxGetApp())->GetLandscape();
	if ( nLS != m_UserVars.m_Orientation ) {
		m_UserVars.m_Orientation = nLS;
		SetModifiedFlag();
	}
}

void
CGenedocDoc::SetFilePath(const char *pszPathName)
{
   	m_PathName = pszPathName;

	int NameLen = m_PathName.GetLength();

	char *pName = m_PathName.GetBuffer(NameLen);

	while ( NameLen != -1 ) {
		if ( pName[NameLen] == '\\' ) break;
		if ( pName[NameLen] == ':' ) break;
		
		NameLen -= 1;
	}
	
	NameLen++;

	m_PathName.ReleaseBuffer(NameLen);

}
 
void 
CGenedocDoc::GetProjectType()
{
	
	int tType = 0, rc;

	if ( pGSFiller != NULL ) {
		if ( !pGSFiller->SegHeaderList.IsEmpty() ) {

			CString *cStr = (CString *)pGSFiller->SegHeaderList.GetTail();
			// Looking for Master Checksum location ...

			if ( (rc = cStr->Find("Type: ")) != -1 ) {
				const char *rStr = (const char *)*cStr;
				rStr += rc + strlen ( "Type: " );
				if ( *rStr == 'N' ) {
					tType = 1;
				}
			}
		}
	}


	m_UserVars.m_ProjectType = tType + 1;
}


BOOL 
CGenedocDoc::OnOpenDocument(const char *pszPathName)
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document\n");


	BeginWaitCursor();

	DeleteContents();

	if ( pGSFiller != NULL ) {
		delete pGSFiller;
		pGSFiller = NULL;
	}
	
	if ( !GetMSFFile( pszPathName ) ) {
		EndWaitCursor();
		return FALSE;
	}
	
	// Save the File Path
	
	SetFilePath(pszPathName);

	// Read the user defaults from the comment list
	GetUserDefaults( );

	// Set printer orientation for this file.
	((CGenedocApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );
	
	// Set Gap Char Correctly
	ChangeGapChar();
	
	// Set correct scoring table.
	((ScoreTableStruct *)m_UserVars.m_ScoreTableArray[m_UserVars.m_CurrentScoreTable])
	->TableFunction(ScoreArray, &NewGap, &GapLen, &CurrentZeroDistance );

	if ( m_UserVars.m_ProjectType == 0 ) {
		GetProjectType();

		if ( m_UserVars.m_ProjectType > 1 && m_UserVars.m_CurrentScoreTable < 9 ) {
			for ( int i = 0; i < 3; ++i ) {
				SetPropertyDefault( 
					m_UserVars.m_Vars.GetProperty().GetArray(i), 
					i, m_UserVars.m_ProjectType 
				);
			}
			m_UserVars.m_CurrentScoreTable = 13;
			// Load up score table	// CptrArray
			((ScoreTableStruct *)m_UserVars.m_ScoreTableArray.
				GetAt(m_UserVars.m_CurrentScoreTable))->TableFunction( ScoreArray, &NewGap, &GapLen, &CurrentZeroDistance );

			SetShadeGroupDefault( &m_UserVars.m_ShadePairArray, m_UserVars.m_CurrentScoreTable );
		}
	}
	
	// Assume 0 = clear, already cleared.
	AutoShade( m_UserVars.m_Vars.GetLastShadeLevel() );
	
	
	SetModifiedFlag(FALSE);     // start off with unmodified

	if ( !ParseTree( m_UserVars.m_ParseString, 0) ) {
		SetModifiedFlag();
		ResetTree();
	}

	EndWaitCursor();


	return TRUE;
}

BOOL 
CGenedocDoc::OnNewDocument()
{

	GetProjectType();
	
/*	if ( ((CGenedocApp*)AfxGetApp())->m_ReallyNewFlag ) {
		
		CProjTypeDialog	tDlg;
		
		tDlg.m_ProjectType = m_UserVars.m_ProjectType - 1;
			
		tDlg.DoModal();
		
		m_UserVars.m_ProjectType = tDlg.m_ProjectType + 1;
	
		AfxMessageBox("Use File or Sequence Edit/Import Function to retrieve Data Files" );
	}	
*/

	return TRUE;
}

void CGenedocDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) {
		AfxMessageBox("Empty Project: Cannot Save!");
		return;
	}
	
	CDocument::OnFileSave();
}

void CGenedocDoc::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) {
		AfxMessageBox("Empty Project: Cannot Save!");
		return;
	}

	OnTitlingf();
	
	CDocument::OnFileSaveAs();
}


BOOL 
CGenedocDoc::OnSaveDocument(const char *pszPathName)
{

	// Get printer orientation for this file.
	m_UserVars.m_Orientation = ((CGenedocApp *)AfxGetApp())->GetLandscape();
	
	if ( 
		(strlen ( m_UserVars.m_TitleProgram ) == 0 )
		|| (strlen ( m_UserVars.m_TitleScoreMatrix ) == 0 )
		|| (strlen ( m_UserVars.m_TitleOpenGap ) == 0 )
		|| (strlen ( m_UserVars.m_TitleExtendGap ) == 0 )
	) {
		OnTitlingf();
	}


	BeginWaitCursor();

	// Write new user defaults to the comment list
	SetUserDefaults();

	WriteMSFFile( pszPathName );
	
	EndWaitCursor();
	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CGenedocDoc serialization

void CGenedocDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGenedocDoc diagnostics

#ifdef _DEBUG
void CGenedocDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGenedocDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenedocDoc commands

// Working Spot

void
CGenedocDoc::CopyGSFiller( CGSFiller *npGSFiller )
{
	pGSFiller = npGSFiller;

	SetModifiedFlag();     // start off with unmodified

	UpdateAllViews(NULL);
}

void 
CGenedocDoc::ClearShade() 
{
	if ( pGSFiller == NULL ) {
		return;
	}

	CGeneSegment *tCGSeg;
	int i = 0;
	HANDLE tSegHandle;

	m_UserVars.m_Vars.SetLastShadeLevel( SHADELEVEL0 );

	int RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment rows
	
	ShadeSegStc* pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row

	if ( pSegArr == 0 ) {
		AfxMessageBox( "Geneddoc:new:fail:" );
		return;
	}

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		pSegArr[i].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
		pSegArr[i].pCGSeg = tCGSeg;
		if ( pSegArr[i].pGeneStor == NULL ) { 
			AfxMessageBox("ClearShade:GlobalLock:Fail");
			delete pSegArr;
			return;
		}

		i++;
	}
	
	DWORD OuterCount = tCGSeg->GetTextLength();

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		// Inner Loop
		for ( i = 0; i < RowCount; ++i ) {
			if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
				(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.m_BackColor0;
				(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.m_ForeColor0;
				(pSegArr[i].pGeneStor)[tCount].CharScore = 0;
				continue;
			}
			// Lets Clear out old shades here.
			(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.m_BackColor0;
			(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.m_ForeColor0;
			// (pSegArr[i].pGeneStor)[tCount].CharScore = 0;
			// Lets Clear out old Displays
			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			if ( m_UserVars.m_ResidueUpper == 1 ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = toupper(tChar);
			} else if ( m_UserVars.m_ResidueUpper == 2 ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = tolower(tChar);
			} else {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = tChar;
			}
			if ( m_UserVars.m_TransTilde ) {
				if ( tChar == '~' ) (pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
			}

		}
	}

	if ( m_UserVars.m_Vars.GetResidueMode() == 1 ) {
		AutoShadeDifference( &pSegArr[2], RowCount - 3, 0, &m_UserVars.m_Vars, NULL );
	}


	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		GlobalUnlock( tSegHandle );
	}

	delete pSegArr;
}


void 
CGenedocDoc::ClearScore() 
{
	if ( pGSFiller == NULL ) {
		return;
	}

	CGeneSegment *tCGSeg;
	GeneStor	*pGeneStor;
	HANDLE tSegHandle;
	
	tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetHead();
	tSegHandle = tCGSeg->GetTextHandle();
	pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
	if ( pGeneStor == NULL ) { 
		AfxMessageBox("ClearScore:GlobalLock:Fail");
		return;
	}
	
	DWORD OuterCount = tCGSeg->GetTextLength();

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		if ( pGeneStor[tCount].CharScore != 0 ) {
			pGeneStor[tCount].CharScore = 0;
			pGeneStor[tCount].CharDisplay = ' ';
			// Reset the colors
			pGeneStor[tCount].BackColor = m_UserVars.m_BackColor0;
			pGeneStor[tCount].TextColor = m_UserVars.m_ForeColor0;
		}
	}

	GlobalUnlock( tSegHandle );

}


void 
CGenedocDoc::ChangeGapChar() 
{
	
	if ( pGSFiller == NULL ) {
		return;
	}
	
	CGeneSegment *tCGSeg;
	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

		tCGSeg->ChangeGapChar(tGapChar );
	}
}


void 
CGenedocDoc::InsertFillerRange(DWORD StartRange, DWORD EndRange) 
{
	
	if ( pGSFiller == NULL ) {
		return;
	}
	
	CGeneSegment *tCGSeg;
	int MaxExpanded = 0;

	BeginWaitCursor();

	POSITION tPos;
	int OnlyExp = 0;
//	if ( InsSelected ) {
		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetArrangeFlag() ) {
				OnlyExp = 1;
				break;
			}

		}
//	}
	//
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( OnlyExp ) if ( !tCGSeg->GetArrangeFlag() ) {
			tCGSeg->m_Expanded = 0;
			continue;
		}
		tCGSeg->InsertFillerRange( StartRange, EndRange );
		if ( tCGSeg->m_Expanded > MaxExpanded ) {
    		MaxExpanded = tCGSeg->m_Expanded;
		}
	}
	//
	if ( MaxExpanded ) {
		// Here we gots increase sizes of strings.
		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->m_Expanded != MaxExpanded ) {
				tCGSeg->AppendFiller( MaxExpanded - tCGSeg->m_Expanded );
			}
		}
	}
	

	EndWaitCursor();

	// Reset the screen
	AutoShade( -1, 1 );

}

void 
CGenedocDoc::DeleteFillerRange(DWORD StartRange, DWORD EndRange, int DelData ) 
{
	
	if ( pGSFiller == NULL ) {
		return;
	}
	
	CGeneSegment *tCGSeg;
	int isok;
	
	BeginWaitCursor();
	POSITION tPos;
	int OnlyExp = 0;
//	if ( DelSelected ) {
		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetArrangeFlag() ) {
				OnlyExp = 1;
				break;
			}

		}
//	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	if ( DelData ) {
		isok = 1;
	} else {
		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( OnlyExp ) if ( !tCGSeg->GetArrangeFlag() ) {
				continue;
			}

			isok = tCGSeg->TestDeleteFillerRange( StartRange, EndRange );
			if ( !isok ) break;
		}

		if ( !isok ) {
    		AfxMessageBox( "Residues detected in Selected Range" );
    		return;
		}
	}
	
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( OnlyExp ) if ( !tCGSeg->GetArrangeFlag() ) {
			continue;
		}
		tCGSeg->DeleteFillerRange( StartRange, EndRange, DelData );
	}

	// Here we gots increase sizes of strings.
	ReSizeRows();
	
	EndWaitCursor();

	// Reset the screen
	AutoShade( -1, 1 );

}


void CGenedocDoc::OnCleargapcols() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) {
		return;
	}
	
	CGeneSegment *tCGSeg;
	int isok;
	
	BeginWaitCursor();

	tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetHead();
	DWORD dwLen = tCGSeg->GetTextLength();

	for ( DWORD dwCount = 0; dwCount < dwLen; ++dwCount ) {

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();

		while (tPos != NULL ) {
			tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			isok = tCGSeg->TestDeleteFillerRange( dwCount, dwCount );
			if ( !isok ) break;
		}

		if ( isok ) {
			tPos = pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
				tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
				tCGSeg->DeleteFillerRange( dwCount, dwCount );
			}

			dwLen--;
			dwCount--;
		}
	}

	//
	
	EndWaitCursor();

	// Reset the screen
	AutoShade( -1, 1 );

	
}

int 
CGenedocDoc::GetNumColors(CDisplayVars *DisplayVars)
{
	if ( DisplayVars->GetModeConserved() == SHADEPROPERTY ) {
		if ( DisplayVars->GetLastShadeLevel() >= SHADELEVEL2 ) {
			return 
				DisplayVars->GetProperty()
					.GetArray(DisplayVars->GetLastShadeLevel() - SHADELEVEL2)
						->GetSize() + 1;
		} else {
			return 1;
		}
	} else { 
		return 4;
	}
}

void
CGenedocDoc::GetLevelColors( CDisplayVars *DisplayVars, int Level, COLORREF * TextColor, COLORREF *BkColor )
{
	// Check for special case properties shading
	int LastShadeLevel = DisplayVars->GetLastShadeLevel();

	// &&  LastShadeLevel != 5 
	if ( DisplayVars->GetModeConserved() == SHADEPROPERTY ) {
		if ( Level > 0 ) {

			CPtrArray *pPArray = (CPtrArray *)DisplayVars->GetProperty().GetArray(LastShadeLevel - SHADELEVEL2);
			if ( pPArray->GetSize() < Level ) {
				*BkColor = RGB(0,0,0);
				*TextColor = RGB(0,0,0);
				return;
			}
			*BkColor = 	((PropertyStruct *)pPArray->GetAt(Level - 1))->BkColor;
			*TextColor = ((PropertyStruct *)pPArray->GetAt(Level - 1))->TextColor;
		} else {
			*BkColor = m_UserVars.m_BackColor0;
			*TextColor = m_UserVars.m_ForeColor0;
		}
	} else {
		// Check for converse, quantify, and difference shade levels.
		if ( Level == 1 ) {
			*BkColor = m_UserVars.m_BackColor60;
			*TextColor = m_UserVars.m_ForeColor60;
		} else if ( Level == 2 ) {
			*BkColor = m_UserVars.m_BackColor80;
			*TextColor = m_UserVars.m_ForeColor80;
		} else if ( Level == 3 ) {
			*BkColor = m_UserVars.m_BackColor100;
			*TextColor = m_UserVars.m_ForeColor100;
		} else {
			*BkColor = m_UserVars.m_BackColor0;
			*TextColor = m_UserVars.m_ForeColor0;
		}
	}
}


CGeneSegment* 
CGenedocDoc::GetSequenceFromName( const CString& Name )
{
	if ( pGSFiller == NULL ) return NULL;

	CGeneSegment *pCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		// CString
		if ( !pCGSeg->GetTitle().CompareNoCase( Name ) ) {
			return pCGSeg;
		}
	}
	
	return NULL;
}



void
CopyPhysioChemVars( 
int *nCy, int *oCy,
int*nShow, int* oShow, 
stcChemProp* nOxi, stcChemProp* oOxi, 
stcChemProp* nRed, stcChemProp* oRed, 
stcChemProp* nCons, stcChemProp* oCons, 
int *nEnab, int *oEnab 
);

void 
CGenedocDoc::CopyUserVars( UserVars * nUserVars, UserVars * oUserVars  )
{

	// Start User Variables ....

	nUserVars->m_FontWeight = oUserVars->m_FontWeight;
	nUserVars->m_FontSize = oUserVars->m_FontSize;
	nUserVars->m_ForeColor100 = oUserVars->m_ForeColor100;
	nUserVars->m_ForeColor80 = oUserVars->m_ForeColor80;
	nUserVars->m_ForeColor60 = oUserVars->m_ForeColor60;
	nUserVars->m_ForeColor0 = oUserVars->m_ForeColor0;

	nUserVars->m_BackColor100 = oUserVars->m_BackColor100;
	nUserVars->m_BackColor80 = oUserVars->m_BackColor80;
	nUserVars->m_BackColor60 = oUserVars->m_BackColor60;
	nUserVars->m_BackColor0 = oUserVars->m_BackColor0;
	nUserVars->m_WidthMode = oUserVars->m_WidthMode;
	nUserVars->m_FixedXSize = oUserVars->m_FixedXSize;

	nUserVars->m_CurrentScoreTable = oUserVars->m_CurrentScoreTable;

	nUserVars->m_LeftBorder = oUserVars->m_LeftBorder;
	nUserVars->m_RightBorder = oUserVars->m_RightBorder;
	nUserVars->m_TopBorder = oUserVars->m_TopBorder;
	nUserVars->m_BottomBorder = oUserVars->m_BottomBorder;

	// Copy DisplayVars

	nUserVars->m_Vars.CopyVars( &oUserVars->m_Vars, this );
	// Will Need to copy all of em ...
	POSITION tPos = oUserVars->m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars *pVars = (CDisplayVars *)oUserVars->m_DisplayVars.GetNext( tPos );
		CDisplayVars *pnVars = new CDisplayVars;

		pnVars->CopyVars( pVars, this );

		nUserVars->m_DisplayVars.AddTail( pnVars );
	}
	
	nUserVars->m_ConsensusLine = oUserVars->m_ConsensusLine;
	
	// Copy this	
	nUserVars->m_ShowTail = oUserVars->m_ShowTail;

	nUserVars->m_Orientation = oUserVars->m_Orientation;
	((CGenedocApp *)AfxGetApp())->SetLandscape( nUserVars->m_Orientation );

	nUserVars->m_GapInd = oUserVars->m_GapInd;
	
	nUserVars->m_ProjectType = oUserVars->m_ProjectType;


	nUserVars->m_TitleProgram = oUserVars->m_TitleProgram;
	nUserVars->m_TitleScoreMatrix = oUserVars->m_TitleScoreMatrix;
	nUserVars->m_TitleOpenGap = oUserVars->m_TitleOpenGap;
	nUserVars->m_TitleExtendGap = oUserVars->m_TitleExtendGap;

	
	SetShadePairArray( &nUserVars->m_ShadePairArray, &oUserVars->m_ShadePairArray );

//	This is basically static for now. When user tables are supported, 
//	Then we will copy it/
//	CPtrArray	nUserVars->m_ScoreTableArray;


// Do the PhylogenTree
	nUserVars->m_ParseString = oUserVars->m_ParseString;

	nUserVars->m_ScoringMethod = oUserVars->m_ScoringMethod;

//	nUserVars->m_DisplayMethod = oUserVars->m_DisplayMethod;

	nUserVars->m_PrintShading = oUserVars->m_PrintShading;
	nUserVars->m_PrintString = oUserVars->m_PrintString;
	nUserVars->m_PrintStringFlag = oUserVars->m_PrintStringFlag;
	nUserVars->m_PrintPageNumber = oUserVars->m_PrintPageNumber;
	nUserVars->m_PrintPageOffset = oUserVars->m_PrintPageOffset;
	nUserVars->m_PrintFontWeight = oUserVars->m_PrintFontWeight;
	nUserVars->m_PrintFontSize = oUserVars->m_PrintFontSize;
	nUserVars->m_PrintFontName = oUserVars->m_PrintFontName;
	nUserVars->m_PrintGeneBlock = oUserVars->m_PrintGeneBlock;


	nUserVars->m_PictWidth = oUserVars->m_PictWidth;
	nUserVars->m_PictHeight = oUserVars->m_PictHeight;
	nUserVars->m_PictAscent = oUserVars->m_PictAscent;

	nUserVars->m_GroupDisplayMode = oUserVars->m_GroupDisplayMode;
	nUserVars->m_ColorSeqNames = oUserVars->m_ColorSeqNames;

	nUserVars->m_AutoShade4Structure = oUserVars->m_AutoShade4Structure;
	nUserVars->m_AutoShade3Structure = oUserVars->m_AutoShade3Structure;
	nUserVars->m_AutoShade2Structure = oUserVars->m_AutoShade2Structure;


	nUserVars->m_MarkerSymb = oUserVars->m_MarkerSymb;
	nUserVars->m_MarkerSpacing = oUserVars->m_MarkerSpacing;
	nUserVars->m_MarkerReplace = oUserVars->m_MarkerReplace;
	nUserVars->m_MarkerStart = oUserVars->m_MarkerStart;
	nUserVars->m_MarkerEnable = oUserVars->m_MarkerEnable;

	nUserVars->m_ResidueUpper = oUserVars->m_ResidueUpper;
	nUserVars->m_ConservedGap = oUserVars->m_ConservedGap;

	CopyPhysioChemVars( 
	&nUserVars->m_ChemPropCysteine, &oUserVars->m_ChemPropCysteine, 
	&nUserVars->m_ChemPropShowProp, &oUserVars->m_ChemPropShowProp, 
	nUserVars->ChemGroupOxi, oUserVars->ChemGroupOxi, 
	nUserVars->ChemGroupRed, oUserVars->ChemGroupRed, 
	nUserVars->ChemCons, oUserVars->ChemCons, 
	nUserVars->ChemPropEnabled, oUserVars->ChemPropEnabled  
	);

	nUserVars->m_strLead = oUserVars->m_strLead;
	nUserVars->m_strTail = oUserVars->m_strTail;
	nUserVars->m_MaxNameLength = oUserVars->m_MaxNameLength;

	const CStringList& cList = oUserVars->m_StcDefUser;
	for( POSITION pos = cList.GetHeadPosition(); pos != NULL; )
	{
		nUserVars->m_StcDefUser.AddTail( cList.GetNext(pos) );
	}

	nUserVars->m_GroupConsLevel = oUserVars->m_GroupConsLevel;
	nUserVars->m_PCRSimilarities = oUserVars->m_PCRSimilarities;
	nUserVars->m_PCRLevel = oUserVars->m_PCRLevel;


	tPos = oUserVars->listSearch.GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(tPos);
		stcSearch *pnS = new stcSearch;

		pnS->iEnabled = pSearch->iEnabled;

		pnS->strSearch = pSearch->strSearch;
		pnS->strName = pSearch->strName;
		pnS->strDescrip = pSearch->strDescrip;
		pnS->rgbText = pSearch->rgbText;
		pnS->rgbBack = pSearch->rgbBack;
		nUserVars->listSearch.AddTail( pnS );
	}
	nUserVars->m_ProSite = oUserVars->m_ProSite;
	nUserVars->m_DispTreeWeight = oUserVars->m_DispTreeWeight;

	nUserVars->m_DNAAmbEn = oUserVars->m_DNAAmbEn;

	nUserVars->m_OverlapColor = oUserVars->m_OverlapColor;

	nUserVars->m_SumColInch = oUserVars->m_SumColInch;
	nUserVars->m_Sum2Wid = oUserVars->m_Sum2Wid;
	nUserVars->m_SumDefDis = oUserVars->m_SumDefDis;
	nUserVars->m_SumTextBlack = oUserVars->m_SumTextBlack;

	tPos = oUserVars->m_listLogOdds.GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pLogOdds = (stcLogOdds *)m_UserVars.m_listLogOdds.GetNext(tPos);
		stcLogOdds *pnLO = new stcLogOdds;

		pnLO->iEnabled = pLogOdds->iEnabled;

		pnLO->strMotif = pLogOdds->strMotif;
		pnLO->strName = pLogOdds->strName;
		pnLO->strDescrip = pLogOdds->strDescrip;
		pnLO->rgbText = pLogOdds->rgbText;
		pnLO->rgbBack = pLogOdds->rgbBack;
		pnLO->dLogOddsArr = new double[pLogOdds->iLogOddsCount][26];
		memcpy ( pnLO->dLogOddsArr, pLogOdds->dLogOddsArr, sizeof(double)*pLogOdds->iLogOddsCount*26 );
		pnLO->iLogOddsCount = pLogOdds->iLogOddsCount;
		pnLO->dLogOddsBayes = pLogOdds->dLogOddsBayes;

		nUserVars->m_listLogOdds.AddTail( pnLO );
	}
	nUserVars->m_dLogOddsMin = oUserVars->m_dLogOddsMin;
	nUserVars->m_iLogOddsBestN = oUserVars->m_iLogOddsBestN;
	nUserVars->m_iLogOddsMode = oUserVars->m_iLogOddsMode;
	nUserVars->m_strLogOddsFile = oUserVars->m_strLogOddsFile;
	nUserVars->m_rgbLogOddsOverlap = oUserVars->m_rgbLogOddsOverlap;
	nUserVars->m_iLogOddsNoOv = oUserVars->m_iLogOddsNoOv;
	nUserVars->m_dLogOddsTL1 = oUserVars->m_dLogOddsTL1;
	nUserVars->m_dLogOddsTL2 = oUserVars->m_dLogOddsTL2;
	nUserVars->m_dLogOddsTL3 = oUserVars->m_dLogOddsTL3;
	nUserVars->m_iLogOddsOutTab = oUserVars->m_iLogOddsOutTab;
	nUserVars->m_dLogOddsMPC = oUserVars->m_dLogOddsMPC;
	nUserVars->m_iLogOddsBack = oUserVars->m_iLogOddsBack;
	nUserVars->m_dLogOddsStA = oUserVars->m_dLogOddsStA;
	nUserVars->m_dLogOddsStC = oUserVars->m_dLogOddsStC;
	nUserVars->m_dLogOddsStG = oUserVars->m_dLogOddsStG;
	nUserVars->m_dLogOddsStT = oUserVars->m_dLogOddsStT;

	nUserVars->m_PrintFileName = oUserVars->m_PrintFileName;
	nUserVars->m_PrintDate = oUserVars->m_PrintDate;

	nUserVars->m_TransTilde = oUserVars->m_TransTilde;
	nUserVars->m_ShowManShade = oUserVars->m_ShowManShade;
	nUserVars->m_ShowComments = oUserVars->m_ShowComments;

	nUserVars->m_DNATransName = oUserVars->m_DNATransName;
	nUserVars->m_DNATrans = oUserVars->m_DNATrans;
	nUserVars->m_DNATransStart = oUserVars->m_DNATransStart;

	nUserVars->m_RepExactMatch = oUserVars->m_RepExactMatch;
	nUserVars->m_RepJuxtaposition = oUserVars->m_RepJuxtaposition;
	nUserVars->m_RepAlignedGaps = oUserVars->m_RepAlignedGaps;
	nUserVars->m_RepAbsoluteVal = oUserVars->m_RepAbsoluteVal;
	nUserVars->m_RepPercentVal = oUserVars->m_RepPercentVal;
	nUserVars->m_RepOutMatrix = oUserVars->m_RepOutMatrix;
	nUserVars->m_RepLabelSingle = oUserVars->m_RepLabelSingle;
	nUserVars->m_RepLabelTop = oUserVars->m_RepLabelTop;

	nUserVars->m_RepIncAA = oUserVars->m_RepIncAA;

	nUserVars->m_MakeBackups = oUserVars->m_MakeBackups;
	nUserVars->m_LocAfterName = oUserVars->m_LocAfterName;
	nUserVars->m_LocAfterSeq = oUserVars->m_LocAfterSeq;

}

void
CGenedocDoc::ClearUserVars( UserVars * dUserVars )
{
	ShadePairStruct *tSPS;
	int count = dUserVars->m_ShadePairArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ShadePairStruct *)dUserVars->m_ShadePairArray[i];
		delete tSPS;
	}
	dUserVars->m_ShadePairArray.RemoveAll();

	// DisplayVars
	POSITION tPos = dUserVars->m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars *pVars = (CDisplayVars *)dUserVars->m_DisplayVars.GetNext( tPos );
		delete pVars;
	}
	dUserVars->m_DisplayVars.RemoveAll();

	dUserVars->m_StcDefUser.RemoveAll();

	ClearSearch(dUserVars);
	ClearLogOdds(dUserVars);

}




void CGenedocDoc::OnConfigure() 
{
	DoConfigure();
}	


void CGenedocDoc::DoConfigure(int ActivePage, int ReDraw ) 
{
	// TODO: Add your command handler code here

	char tBuff[100];
	int DisplayChanged = 0;
	int ScoreChanged = 0;

	CModalDisplayPropSheet tDlg;
	// Get Base Display Vars

#if defined(_WIN32) && _MSC_VER > 999
	switch ( ActivePage ) {
	case ACTPAGEHIGHLIGHTING:
		tDlg.m_SetActivePage = &tDlg.m_ShadeModePage;
		break;
	case ACTPAGEREPORTS:
		tDlg.m_SetActivePage = &tDlg.m_ReportPage;
		break;
	case ACTPAGESEARCH:
		tDlg.m_SetActivePage = &tDlg.m_SearchPropPage;
		break;
	case ACTPAGEPROPERTY:
		tDlg.m_SetActivePage = &tDlg.m_PropertyGroupPage;
		break;
	case ACTPAGESTRUCTURE:
		tDlg.m_SetActivePage = &tDlg.m_StructurePage;
		break;
	case ACTPAGEPHYSIOCHEM:
		tDlg.m_SetActivePage = &tDlg.m_PhysioChemPage;
		break;
	case ACTPAGEIDENTITY:
		tDlg.m_SetActivePage = &tDlg.m_IdentityPage;
		break;
	case ACTPAGELOGODDS:
		tDlg.m_SetActivePage = &tDlg.m_LogOddsPropPage;
		break;
	}
#else
	switch ( ActivePage ) {
	case ACTPAGEHIGHLIGHTING:
		tDlg.m_SetActivePage = 2;
		break;
	case ACTPAGEREPORTS:
		tDlg.m_SetActivePage = 3;
		break;
	case ACTPAGEPROPERTY:
		tDlg.m_SetActivePage = 4;
		break;
	case ACTPAGESEARCH:
		tDlg.m_SetActivePage = 5;
		break;
	case ACTPAGESTRUCTURE:
		tDlg.m_SetActivePage = 6;
		break;
	case ACTPAGEPHYSIOCHEM:
		tDlg.m_SetActivePage = 7;
		break;
	case ACTPAGEIDENTITY:
		tDlg.m_SetActivePage = 8;
		break;
	case ACTPAGELOGODDS:
		tDlg.m_SetActivePage = 9;
		break;
	}        
#endif

	// Display Page	
	tDlg.m_DisplayPage.pDoc = this;
	if ( m_UserVars.m_FontWeight == FW_NORMAL ) {
		tDlg.m_DisplayPage.m_FontWeight = "Normal";
	} else {
		tDlg.m_DisplayPage.m_FontWeight = "Bold";
	}

	tDlg.m_DisplayPage.m_FontSize = m_UserVars.m_FontSize;
	
	tDlg.m_DisplayPage.m_AutoWidth = m_UserVars.m_WidthMode;
	tDlg.m_DisplayPage.m_FixedWidth = m_UserVars.m_FixedXSize;
	tDlg.m_DisplayPage.m_ShowTail = m_UserVars.m_ShowTail;
	tDlg.m_DisplayPage.m_GapInd = m_UserVars.m_GapInd;
	tDlg.m_DisplayPage.m_ProjectType = m_UserVars.m_ProjectType - 1;
	tDlg.m_DisplayPage.m_DNAAmbEn = m_UserVars.m_DNAAmbEn;
	tDlg.m_DisplayPage.m_ScoringMethod = m_UserVars.m_ScoringMethod;
	tDlg.m_DisplayPage.m_ConsensusLine = m_UserVars.m_ConsensusLine;

	tDlg.m_DisplayPage.m_PictWidth = m_UserVars.m_PictWidth;
	tDlg.m_DisplayPage.m_PictHeight = m_UserVars.m_PictHeight;
	tDlg.m_DisplayPage.m_PictAscent = m_UserVars.m_PictAscent;

	tDlg.m_DisplayPage.m_MarkerSymb = m_UserVars.m_MarkerSymb;
	tDlg.m_DisplayPage.m_MarkerSpacing = m_UserVars.m_MarkerSpacing;
	tDlg.m_DisplayPage.m_MarkerReplace = m_UserVars.m_MarkerReplace;
	tDlg.m_DisplayPage.m_MarkerStart = m_UserVars.m_MarkerStart;
	tDlg.m_DisplayPage.m_MarkerEnable = m_UserVars.m_MarkerEnable;

	tDlg.m_DisplayPage.m_ConservedGap = m_UserVars.m_ConservedGap;

	tDlg.m_DisplayPage.m_ResidueUpper = m_UserVars.m_ResidueUpper;

	tDlg.m_DisplayPage.m_MaxNameLength = m_UserVars.m_MaxNameLength;
	tDlg.m_DisplayPage.m_strLead = m_UserVars.m_strLead;
	tDlg.m_DisplayPage.m_strTail = m_UserVars.m_strTail;

	tDlg.m_DisplayPage.m_SumColInch = m_UserVars.m_SumColInch;
	tDlg.m_DisplayPage.m_Sum2Wid = m_UserVars.m_Sum2Wid;
	tDlg.m_DisplayPage.m_SumDefDis = m_UserVars.m_SumDefDis;
	tDlg.m_DisplayPage.m_SumTextBlack = m_UserVars.m_SumTextBlack;
	tDlg.m_DisplayPage.m_TransTilde = m_UserVars.m_TransTilde;
	tDlg.m_DisplayPage.m_ShowManShade = m_UserVars.m_ShowManShade;
	tDlg.m_DisplayPage.m_ShowComments = m_UserVars.m_ShowComments;
	tDlg.m_DisplayPage.m_MakeBackups = m_UserVars.m_MakeBackups;
	tDlg.m_DisplayPage.m_LocAfterName = m_UserVars.m_LocAfterName;
	tDlg.m_DisplayPage.m_LocAfterSeq = m_UserVars.m_LocAfterSeq;
	

	// Print Page	
	tDlg.m_PrintPage.m_TopBorder = m_UserVars.m_TopBorder;
	tDlg.m_PrintPage.m_BottomBorder = m_UserVars.m_BottomBorder;
	tDlg.m_PrintPage.m_LeftBorder = m_UserVars.m_LeftBorder;
	tDlg.m_PrintPage.m_RightBorder = m_UserVars.m_RightBorder;

	tDlg.m_PrintPage.m_Orientation = m_UserVars.m_Orientation;
	
	tDlg.m_PrintPage.m_PrintFontName = m_UserVars.m_PrintFontName;

	if ( m_UserVars.m_PrintFontWeight == FW_NORMAL ) {
		tDlg.m_PrintPage.m_PrintFontWeight = "Normal";
	} else {
		tDlg.m_PrintPage.m_PrintFontWeight = "Bold";
	}

	itoa( m_UserVars.m_PrintFontSize, tBuff, 10 );
	tDlg.m_PrintPage.m_PrintFontPoints = tBuff;

	tDlg.m_PrintPage.m_PrintPage = m_UserVars.m_PrintPageNumber;
	tDlg.m_PrintPage.m_PrintPageOffset = m_UserVars.m_PrintPageOffset;
	tDlg.m_PrintPage.m_PrintString = m_UserVars.m_PrintString;
	tDlg.m_PrintPage.m_GeneBlockPos = m_UserVars.m_PrintGeneBlock;
	tDlg.m_PrintPage.m_PrintStringFlag = m_UserVars.m_PrintStringFlag;
	tDlg.m_PrintPage.m_PrintShading = m_UserVars.m_PrintShading;
	tDlg.m_PrintPage.m_PrintFileName = m_UserVars.m_PrintFileName;
	tDlg.m_PrintPage.m_PrintDate = m_UserVars.m_PrintDate;

	// Report Page
	tDlg.m_ReportPage.m_RepExactMatch = m_UserVars.m_RepExactMatch;
	tDlg.m_ReportPage.m_RepJuxtaposition = m_UserVars.m_RepJuxtaposition;
	tDlg.m_ReportPage.m_RepAlignedGaps = m_UserVars.m_RepAlignedGaps;
	tDlg.m_ReportPage.m_RepAbsoluteVal = m_UserVars.m_RepAbsoluteVal;
	tDlg.m_ReportPage.m_RepPercentVal = m_UserVars.m_RepPercentVal;
	tDlg.m_ReportPage.m_RepOutMatrix = m_UserVars.m_RepOutMatrix;
	tDlg.m_ReportPage.m_RepLabelSingle = m_UserVars.m_RepLabelSingle;
	tDlg.m_ReportPage.m_RepLabelTop = m_UserVars.m_RepLabelTop;
	tDlg.m_ReportPage.m_RepIncAA = m_UserVars.m_RepIncAA;


	// Property Group Page

	// Start Display Vars ...
	SetPropertyArray ( 
		m_UserVars.m_Vars.GetProperty().GetArray(0), 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[0] 
	);
	SetPropertyArray ( 
		m_UserVars.m_Vars.GetProperty().GetArray(1), 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[1] 
	);
	SetPropertyArray ( 
		m_UserVars.m_Vars.GetProperty().GetArray(2), 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[2] 
	);

	tDlg.m_PropertyGroupPage.m_PropStyle = m_UserVars.m_Vars.GetPropStyle();
	// tDlg.m_PropertyGroupPage.m_ListBox = NULL;	// This for SetDefault to test ...
	tDlg.m_PropertyGroupPage.pDoc = this;
	if ( m_UserVars.m_Vars.GetLastShadeLevel() != SHADELEVEL0 ) {
		tDlg.m_PropertyGroupPage.m_CurrentPropLevel	= m_UserVars.m_Vars.GetLastShadeLevel() - SHADELEVEL2;
	} else {
		tDlg.m_PropertyGroupPage.m_CurrentPropLevel	= 0;
	}

	// Search page
	POSITION tPos = m_UserVars.listSearch.GetHeadPosition();
	while ( tPos != NULL ) {
		stcSearch *pSearch = (stcSearch *)m_UserVars.listSearch.GetNext(tPos);
		stcSearch *pnS = new stcSearch;

		pnS->iEnabled = pSearch->iEnabled;

		pnS->strSearch = pSearch->strSearch;
		pnS->strName = pSearch->strName;
		pnS->strDescrip = pSearch->strDescrip;
		pnS->rgbText = pSearch->rgbText;
		pnS->rgbBack = pSearch->rgbBack;
		tDlg.m_SearchPropPage.m_listCopy.AddTail( pnS );
	}
	tDlg.m_SearchPropPage.m_OverlapColor = m_UserVars.m_OverlapColor;
	tDlg.m_SearchPropPage.m_ProSite = m_UserVars.m_ProSite;
	tDlg.m_SearchPropPage.pDoc = this;

	// Structure Page.
	tDlg.m_StructurePage.pDoc = this;
	tDlg.m_StructurePage.m_DisplayVars = &m_UserVars.m_Vars;
	

	// TODO: Add your command handler code here
	CopyPhysioChemVars( 
	&tDlg.m_PhysioChemPage.m_Cysteine, &m_UserVars.m_ChemPropCysteine, 
	&tDlg.m_PhysioChemPage.m_ShowProperty, &m_UserVars.m_ChemPropShowProp, 
	tDlg.m_PhysioChemPage.ChemGroup, m_UserVars.ChemGroupOxi, 
	tDlg.m_PhysioChemPage.ChemGroupRed, m_UserVars.ChemGroupRed, 
	tDlg.m_PhysioChemPage.ChemCons, m_UserVars.ChemCons, 
	tDlg.m_PhysioChemPage.ChemPropEnabled, m_UserVars.ChemPropEnabled 
	);

	// Identity Page
	if ( pGSFiller != NULL ) {
		tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
			CGeneSegment *pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
			if ( pCGSeg->GetStyle() == LINESEQUENCE ) {
				tDlg.m_IdentityPage.m_SegList.AddTail(pCGSeg);
			}
		}
	}
	CPtrList *pList = m_UserVars.m_Vars.GetIdentList();
	tPos = pList->GetHeadPosition();
	while ( tPos != NULL ) {
		tDlg.m_IdentityPage.m_IdentList.AddTail( pList->GetNext(tPos));
	}
	m_UserVars.m_Vars.GetIdentColors( &tDlg.m_IdentityPage.m_rgbText, &tDlg.m_IdentityPage.m_rgbBack );
	tDlg.m_IdentityPage.m_IdentDisplayStyle = m_UserVars.m_Vars.GetIdentDisplayStyle();


	// LogOdds page
	tPos = m_UserVars.m_listLogOdds.GetHeadPosition();
	while ( tPos != NULL ) {
		stcLogOdds *pLogOdds = (stcLogOdds *)m_UserVars.m_listLogOdds.GetNext(tPos);
		stcLogOdds *pnLO = new stcLogOdds;

		pnLO->iEnabled = pLogOdds->iEnabled;

		pnLO->strMotif = pLogOdds->strMotif;
		pnLO->strName = pLogOdds->strName;
		pnLO->strDescrip = pLogOdds->strDescrip;
		pnLO->rgbText = pLogOdds->rgbText;
		pnLO->rgbBack = pLogOdds->rgbBack;
		pnLO->iLogOddsCount = pLogOdds->iLogOddsCount;
		pnLO->dLogOddsBayes = pLogOdds->dLogOddsBayes;

		pnLO->dLogOddsArr = new double[pLogOdds->iLogOddsCount][26];
		memcpy ( pnLO->dLogOddsArr, pLogOdds->dLogOddsArr, sizeof(double)*pLogOdds->iLogOddsCount*26 );

		tDlg.m_LogOddsPropPage.m_listCopy.AddTail( pnLO );
	}
	tDlg.m_LogOddsPropPage.m_OverlapColor = m_UserVars.m_rgbLogOddsOverlap;
	tDlg.m_LogOddsPropPage.m_iLogOddsNoOv = m_UserVars.m_iLogOddsNoOv;
	tDlg.m_LogOddsPropPage.m_dLogOddsMin = m_UserVars.m_dLogOddsMin;
	tDlg.m_LogOddsPropPage.m_iLogOddsBestN = m_UserVars.m_iLogOddsBestN;
	tDlg.m_LogOddsPropPage.m_iLogOddsMode = m_UserVars.m_iLogOddsMode;
	tDlg.m_LogOddsPropPage.m_strLogOddsFile = m_UserVars.m_strLogOddsFile;
	tDlg.m_LogOddsPropPage.m_dLogOddsTL1 = m_UserVars.m_dLogOddsTL1;
	tDlg.m_LogOddsPropPage.m_dLogOddsTL2 = m_UserVars.m_dLogOddsTL2;
	tDlg.m_LogOddsPropPage.m_dLogOddsTL3 = m_UserVars.m_dLogOddsTL3;
	tDlg.m_LogOddsPropPage.m_iLogOddsOutTab = m_UserVars.m_iLogOddsOutTab;
	tDlg.m_LogOddsPropPage.m_dLogOddsMPC = m_UserVars.m_dLogOddsMPC;
	tDlg.m_LogOddsPropPage.m_iLogOddsBack = m_UserVars.m_iLogOddsBack;
	tDlg.m_LogOddsPropPage.m_dLogOddsStA = m_UserVars.m_dLogOddsStA;
	tDlg.m_LogOddsPropPage.m_dLogOddsStC = m_UserVars.m_dLogOddsStC;
	tDlg.m_LogOddsPropPage.m_dLogOddsStG = m_UserVars.m_dLogOddsStG;
	tDlg.m_LogOddsPropPage.m_dLogOddsStT = m_UserVars.m_dLogOddsStT;
	tDlg.m_LogOddsPropPage.pDoc = this;

	// Mode/Style Page
	tDlg.m_ShadeModePage.m_PrimaryLevel = m_UserVars.m_Vars.GetPrimaryLevel();
	tDlg.m_ShadeModePage.m_SecondaryLevel = m_UserVars.m_Vars.GetSecondaryLevel();
	tDlg.m_ShadeModePage.m_TertiaryLevel = m_UserVars.m_Vars.GetTertiaryLevel();
	tDlg.m_ShadeModePage.m_ModeConserved = m_UserVars.m_Vars.GetModeConserved();
	tDlg.m_ShadeModePage.m_DiffMode = m_UserVars.m_Vars.GetDiffMode();
	tDlg.m_ShadeModePage.m_ResidueMode = m_UserVars.m_Vars.GetResidueMode();
	tDlg.m_ShadeModePage.m_ShadeLevel = m_UserVars.m_Vars.GetLastShadeLevel();
	tDlg.m_ShadeModePage.m_GroupEnabled = m_UserVars.m_Vars.GetGroupEnabled();
	tDlg.m_ShadeModePage.m_ConsSubStyle = m_UserVars.m_Vars.GetConsSubStyle();

	tDlg.m_ShadeModePage.m_BackColor0 = m_UserVars.m_BackColor0;
	tDlg.m_ShadeModePage.m_ForeColor0 = m_UserVars.m_ForeColor0;

	tDlg.m_ShadeModePage.m_BackColor60 = m_UserVars.m_BackColor60;
	tDlg.m_ShadeModePage.m_ForeColor60 = m_UserVars.m_ForeColor60;
	
	tDlg.m_ShadeModePage.m_BackColor80 = m_UserVars.m_BackColor80;
	tDlg.m_ShadeModePage.m_ForeColor80 = m_UserVars.m_ForeColor80;
	
	tDlg.m_ShadeModePage.m_BackColor100 = m_UserVars.m_BackColor100;
	tDlg.m_ShadeModePage.m_ForeColor100 = m_UserVars.m_ForeColor100;

	tDlg.m_ShadeModePage.m_FontWeight = m_UserVars.m_FontWeight;
	tDlg.m_ShadeModePage.m_FontSize = m_UserVars.m_FontSize;

	// Score Table Page
	// Group Page
	tDlg.m_ScoreTablePage.pDoc = this;
	tDlg.m_ScoreTablePage.m_ProjectType = m_UserVars.m_ProjectType;
	tDlg.m_ScoreTablePage.SetScoreTableArray ( 
		&m_UserVars.m_ScoreTableArray, m_UserVars.m_ProjectType 
	);
	tDlg.m_ScoreTablePage.m_CurrentScoreTable = m_UserVars.m_CurrentScoreTable;
	// Substitution Group Page
	tDlg.m_ScoreTablePage.SetShadePairArray ( &m_UserVars.m_ShadePairArray );
	tDlg.m_ScoreTablePage.m_listGroup = NULL;	// This for SetDefault to test ...
	

	// For Project Type;
//	tDlg.m_ScoreTablePage.m_DialogInited = 0;
//	tDlg.m_PropertyGroupPage.m_DialogInited = 0;

	if ( tDlg.DoModal() != IDOK ) {
		while ( !tDlg.m_SearchPropPage.m_listCopy.IsEmpty() ) 
			delete (stcSearch *)tDlg.m_SearchPropPage.m_listCopy.RemoveHead();
		while ( !tDlg.m_LogOddsPropPage.m_listCopy.IsEmpty() ) {
			stcLogOdds *pLO = (stcLogOdds *)tDlg.m_LogOddsPropPage.m_listCopy.RemoveHead();
			delete [] pLO->dLogOddsArr;
			delete pLO;
		}
		return;
	}

	if ( tDlg.m_DisplayPage.m_FontWeight == "Normal" ) {
		m_UserVars.m_FontWeight = FW_NORMAL;
	} else {
		m_UserVars.m_FontWeight = FW_BOLD;
	}
    m_UserVars.m_FontSize = tDlg.m_DisplayPage.m_FontSize;

	m_UserVars.m_WidthMode = tDlg.m_DisplayPage.m_AutoWidth;
	m_UserVars.m_FixedXSize = tDlg.m_DisplayPage.m_FixedWidth;
	m_UserVars.m_ShowTail = tDlg.m_DisplayPage.m_ShowTail;

	if ( m_UserVars.m_GapInd != tDlg.m_DisplayPage.m_GapInd ) {
		m_UserVars.m_GapInd = tDlg.m_DisplayPage.m_GapInd;
		ChangeGapChar();
	}
	m_UserVars.m_ProjectType = tDlg.m_DisplayPage.m_ProjectType + 1;
	m_UserVars.m_DNAAmbEn = tDlg.m_DisplayPage.m_DNAAmbEn;
	m_UserVars.m_ScoringMethod = tDlg.m_DisplayPage.m_ScoringMethod;
	if ( m_UserVars.m_ConsensusLine != tDlg.m_DisplayPage.m_ConsensusLine ) {
		int tShadeLevel = m_UserVars.m_Vars.GetLastShadeLevel();
		ClearShade();
		m_UserVars.m_Vars.SetLastShadeLevel(tShadeLevel);
	}
	m_UserVars.m_ConsensusLine = tDlg.m_DisplayPage.m_ConsensusLine;
	m_UserVars.m_PictWidth = tDlg.m_DisplayPage.m_PictWidth;
	m_UserVars.m_PictHeight = tDlg.m_DisplayPage.m_PictHeight;
	m_UserVars.m_PictAscent = tDlg.m_DisplayPage.m_PictAscent;
	
	if ( !tDlg.m_DisplayPage.m_MarkerSymb.IsEmpty() ) 
		m_UserVars.m_MarkerSymb = tDlg.m_DisplayPage.m_MarkerSymb[0];
	m_UserVars.m_MarkerSpacing = tDlg.m_DisplayPage.m_MarkerSpacing;
	m_UserVars.m_MarkerReplace = tDlg.m_DisplayPage.m_MarkerReplace;
	m_UserVars.m_MarkerStart = tDlg.m_DisplayPage.m_MarkerStart;
	m_UserVars.m_MarkerEnable = tDlg.m_DisplayPage.m_MarkerEnable;

	if ( !tDlg.m_DisplayPage.m_ConservedGap.IsEmpty() ) 
		m_UserVars.m_ConservedGap = tDlg.m_DisplayPage.m_ConservedGap[0];

	m_UserVars.m_ResidueUpper = tDlg.m_DisplayPage.m_ResidueUpper;

	m_UserVars.m_MaxNameLength = tDlg.m_DisplayPage.m_MaxNameLength;
	m_UserVars.m_strLead = tDlg.m_DisplayPage.m_strLead;
	m_UserVars.m_strTail = tDlg.m_DisplayPage.m_strTail;
	m_UserVars.m_SumColInch = tDlg.m_DisplayPage.m_SumColInch;
	m_UserVars.m_Sum2Wid = tDlg.m_DisplayPage.m_Sum2Wid;
	m_UserVars.m_SumDefDis = tDlg.m_DisplayPage.m_SumDefDis;
	m_UserVars.m_SumTextBlack = tDlg.m_DisplayPage.m_SumTextBlack;
	m_UserVars.m_TransTilde = tDlg.m_DisplayPage.m_TransTilde;
	m_UserVars.m_ShowManShade = tDlg.m_DisplayPage.m_ShowManShade;

	m_UserVars.m_MakeBackups = tDlg.m_DisplayPage.m_MakeBackups;
	m_UserVars.m_LocAfterName = tDlg.m_DisplayPage.m_LocAfterName;
	m_UserVars.m_LocAfterSeq = tDlg.m_DisplayPage.m_LocAfterSeq;
		

	// PrintPage
	m_UserVars.m_TopBorder = tDlg.m_PrintPage.m_TopBorder;
	m_UserVars.m_BottomBorder = tDlg.m_PrintPage.m_BottomBorder;
	m_UserVars.m_LeftBorder = tDlg.m_PrintPage.m_LeftBorder;
	m_UserVars.m_RightBorder = tDlg.m_PrintPage.m_RightBorder;

	m_UserVars.m_Orientation = tDlg.m_PrintPage.m_Orientation;

	m_UserVars.m_PrintFontName = tDlg.m_PrintPage.m_PrintFontName;

	if ( tDlg.m_PrintPage.m_PrintFontWeight == "Normal" ) {
		m_UserVars.m_PrintFontWeight = FW_NORMAL;
	} else {
		m_UserVars.m_PrintFontWeight = FW_BOLD;
	}
	m_UserVars.m_PrintFontSize = atoi ( tDlg.m_PrintPage.m_PrintFontPoints );

	m_UserVars.m_PrintPageNumber= tDlg.m_PrintPage.m_PrintPage;
	m_UserVars.m_PrintPageOffset = tDlg.m_PrintPage.m_PrintPageOffset;
	m_UserVars.m_PrintString = tDlg.m_PrintPage.m_PrintString;
	m_UserVars.m_PrintGeneBlock = tDlg.m_PrintPage.m_GeneBlockPos;
	m_UserVars.m_PrintStringFlag = tDlg.m_PrintPage.m_PrintStringFlag;
	m_UserVars.m_PrintShading = tDlg.m_PrintPage.m_PrintShading;
	m_UserVars.m_PrintFileName = tDlg.m_PrintPage.m_PrintFileName;
	m_UserVars.m_PrintDate = tDlg.m_PrintPage.m_PrintDate;

	// Set printer orientation for this file.
	((CGenedocApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );

//
//	if ( tDlg.m_PrintPage.m_DisplayMethodChanged ) {
//
//		m_UserVars.m_DisplayMethod = tDlg.m_PrintPage.m_DisplayMethod;
//		
//		DisplayChanged = 1;
//	}
//

	// Shade Mode Page
	m_UserVars.m_Vars.SetPrimaryLevel( tDlg.m_ShadeModePage.m_PrimaryLevel );
	m_UserVars.m_Vars.SetSecondaryLevel( tDlg.m_ShadeModePage.m_SecondaryLevel );
	m_UserVars.m_Vars.SetTertiaryLevel( tDlg.m_ShadeModePage.m_TertiaryLevel );
	
	m_UserVars.m_Vars.SetModeConserved( tDlg.m_ShadeModePage.m_ModeConserved );
	m_UserVars.m_Vars.SetDiffMode( tDlg.m_ShadeModePage.m_DiffMode );
	m_UserVars.m_Vars.SetResidueMode( tDlg.m_ShadeModePage.m_ResidueMode );

	m_UserVars.m_Vars.SetLastShadeLevel( tDlg.m_ShadeModePage.m_ShadeLevel );
	m_UserVars.m_Vars.SetGroupEnabled( tDlg.m_ShadeModePage.m_GroupEnabled );

	m_UserVars.m_Vars.SetConsSubStyle( tDlg.m_ShadeModePage.m_ConsSubStyle );

	m_UserVars.m_BackColor0 = tDlg.m_ShadeModePage.m_BackColor0;
	m_UserVars.m_ForeColor0 = tDlg.m_ShadeModePage.m_ForeColor0;

	m_UserVars.m_BackColor60 = tDlg.m_ShadeModePage.m_BackColor60;
	m_UserVars.m_ForeColor60 = tDlg.m_ShadeModePage.m_ForeColor60;
	
	m_UserVars.m_BackColor80 = tDlg.m_ShadeModePage.m_BackColor80;
	m_UserVars.m_ForeColor80 = tDlg.m_ShadeModePage.m_ForeColor80;
	
	m_UserVars.m_BackColor100 = tDlg.m_ShadeModePage.m_BackColor100;
	m_UserVars.m_ForeColor100 = tDlg.m_ShadeModePage.m_ForeColor100;


	// Report Page
	m_UserVars.m_RepExactMatch = tDlg.m_ReportPage.m_RepExactMatch;
	m_UserVars.m_RepJuxtaposition = tDlg.m_ReportPage.m_RepJuxtaposition;
	m_UserVars.m_RepAlignedGaps = tDlg.m_ReportPage.m_RepAlignedGaps;
	m_UserVars.m_RepAbsoluteVal = tDlg.m_ReportPage.m_RepAbsoluteVal;
	m_UserVars.m_RepPercentVal = tDlg.m_ReportPage.m_RepPercentVal;
	m_UserVars.m_RepOutMatrix = tDlg.m_ReportPage.m_RepOutMatrix;
	m_UserVars.m_RepLabelTop = tDlg.m_ReportPage.m_RepLabelTop;
	m_UserVars.m_RepLabelSingle = tDlg.m_ReportPage.m_RepLabelSingle;
	m_UserVars.m_RepIncAA = tDlg.m_ReportPage.m_RepIncAA;

	// Properties Page
	SetPropertyArray ( 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[0], 
		m_UserVars.m_Vars.GetProperty().GetArray(0) 
	);

	SetPropertyArray ( 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[1], 
		m_UserVars.m_Vars.GetProperty().GetArray(1) 
	);

	SetPropertyArray ( 
		&tDlg.m_PropertyGroupPage.m_PropertyArray[2], 
		m_UserVars.m_Vars.GetProperty().GetArray(2) 
	);
	
	m_UserVars.m_Vars.SetPropStyle( tDlg.m_PropertyGroupPage.m_PropStyle );

	if ( m_UserVars.m_Vars.GetModeConserved() == SHADEPROPERTY ) {
		m_UserVars.m_Vars.SetLastShadeLevel( tDlg.m_PropertyGroupPage.m_CurrentPropLevel + SHADELEVEL2);
	}

	// Search Page
	ClearSearch(&m_UserVars);

	while ( !tDlg.m_SearchPropPage.m_listCopy.IsEmpty() ) {
		m_UserVars.listSearch.AddTail( tDlg.m_SearchPropPage.m_listCopy.RemoveHead() );
	}
	m_UserVars.m_ProSite = tDlg.m_SearchPropPage.m_ProSite;
	m_UserVars.m_OverlapColor = tDlg.m_SearchPropPage.m_OverlapColor;

	// LogOdds Page
	ClearLogOdds(&m_UserVars);

	while ( !tDlg.m_LogOddsPropPage.m_listCopy.IsEmpty() ) {
		m_UserVars.m_listLogOdds.AddTail( tDlg.m_LogOddsPropPage.m_listCopy.RemoveHead() );
	}
	m_UserVars.m_iLogOddsNoOv = tDlg.m_LogOddsPropPage.m_iLogOddsNoOv;
	m_UserVars.m_rgbLogOddsOverlap = tDlg.m_LogOddsPropPage.m_OverlapColor;
	m_UserVars.m_dLogOddsMin = tDlg.m_LogOddsPropPage.m_dLogOddsMin;
	m_UserVars.m_iLogOddsBestN = tDlg.m_LogOddsPropPage.m_iLogOddsBestN;
	m_UserVars.m_iLogOddsMode = tDlg.m_LogOddsPropPage.m_iLogOddsMode;
	m_UserVars.m_strLogOddsFile = tDlg.m_LogOddsPropPage.m_strLogOddsFile;
	m_UserVars.m_dLogOddsTL1 = tDlg.m_LogOddsPropPage.m_dLogOddsTL1;
	m_UserVars.m_dLogOddsTL2 = tDlg.m_LogOddsPropPage.m_dLogOddsTL2;
	m_UserVars.m_dLogOddsTL3 = tDlg.m_LogOddsPropPage.m_dLogOddsTL3;
	m_UserVars.m_iLogOddsOutTab = tDlg.m_LogOddsPropPage.m_iLogOddsOutTab;
	m_UserVars.m_dLogOddsMPC = tDlg.m_LogOddsPropPage.m_dLogOddsMPC ;
	m_UserVars.m_iLogOddsBack = tDlg.m_LogOddsPropPage.m_iLogOddsBack;
	m_UserVars.m_dLogOddsStA = tDlg.m_LogOddsPropPage.m_dLogOddsStA;
	m_UserVars.m_dLogOddsStC = tDlg.m_LogOddsPropPage.m_dLogOddsStC;
	m_UserVars.m_dLogOddsStG = tDlg.m_LogOddsPropPage.m_dLogOddsStG;
	m_UserVars.m_dLogOddsStT = tDlg.m_LogOddsPropPage.m_dLogOddsStT;


	// m_UserVars.m_Vars.GetStcGroup().SetCurrentDataType( tDlg.m_StructurePage.m_StcGroup->GetDataType() );
		

	// PhysioChem page
	CopyPhysioChemVars( 
		&m_UserVars.m_ChemPropCysteine, &tDlg.m_PhysioChemPage.m_Cysteine, 
		&m_UserVars.m_ChemPropShowProp, &tDlg.m_PhysioChemPage.m_ShowProperty, 
		m_UserVars.ChemGroupOxi, tDlg.m_PhysioChemPage.ChemGroup, 
		m_UserVars.ChemGroupRed, tDlg.m_PhysioChemPage.ChemGroupRed, 
		m_UserVars.ChemCons, tDlg.m_PhysioChemPage.ChemCons, 
		m_UserVars.ChemPropEnabled, tDlg.m_PhysioChemPage.ChemPropEnabled 
	);


	// Identity Page
	pList = m_UserVars.m_Vars.GetIdentList();
	pList->RemoveAll();
	tPos = tDlg.m_IdentityPage.m_IdentList.GetHeadPosition();
	while ( tPos != NULL ) {
		pList->AddTail( tDlg.m_IdentityPage.m_IdentList.GetNext(tPos));
	}
	m_UserVars.m_Vars.SetIdentColors( tDlg.m_IdentityPage.m_rgbText, tDlg.m_IdentityPage.m_rgbBack );
	m_UserVars.m_Vars.SetIdentDisplayStyle( tDlg.m_IdentityPage.m_IdentDisplayStyle );

	// 
	// Score Table Page

	m_UserVars.m_CurrentScoreTable = tDlg.m_ScoreTablePage.m_CurrentScoreTable;
	((ScoreTableStruct *)m_UserVars.m_ScoreTableArray[m_UserVars.m_CurrentScoreTable])
	->TableFunction(ScoreArray, &NewGap, &GapLen, &CurrentZeroDistance );
		
	SetShadePairArray ( &m_UserVars.m_ShadePairArray, &tDlg.m_ScoreTablePage.m_ShadePairArray );


	AutoShade( -1, 1 );		// Second -1 is ignored
	// Dirty the document
	SetModifiedFlag();

}

void 
CGenedocDoc::DoGroupConfigure(int ActivePage, int ReDraw )
{
	
	// TODO: Add your command handler code here
	CGroupPropertySheet tDlg;

	if ( tDlg.m_NumGroups = m_UserVars.m_DisplayVars.GetCount() ) {

#if defined(_WIN32) && _MSC_VER > 999
		switch ( ActivePage ) {
		case ACTPAGEHIGHLIGHTING:
			tDlg.m_SetActivePage = &tDlg.m_ShadeModePage;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGEPROPERTY:
			tDlg.m_SetActivePage = &tDlg.m_PropertyGroupPage;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGESTRUCTURE:
			tDlg.m_SetActivePage = &tDlg.m_StructurePage;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGEIDENTITY:
			tDlg.m_SetActivePage = &tDlg.m_IdentityPage;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		}
#else
		switch ( ActivePage ) {
		case ACTPAGEHIGHLIGHTING:
			tDlg.m_SetActivePage = 1;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGEPROPERTY:
			tDlg.m_SetActivePage = 2;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGESTRUCTURE:
			tDlg.m_SetActivePage = 3;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		case ACTPAGEIDENTITY:
			tDlg.m_SetActivePage = 4;
			tDlg.m_GroupPropPage.m_ModifyAll = TRUE;
			break;
		}
#endif

		CDisplayVars * DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetHead();
			
		// init the PropertyPages with current values.
		// TODO: Need more work
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(0), &tDlg.m_PropertyGroupPage.m_PropertyArray[0] );
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(1), &tDlg.m_PropertyGroupPage.m_PropertyArray[1] );
		SetPropertyArray ( DisplayVars->GetProperty().GetArray(2), &tDlg.m_PropertyGroupPage.m_PropertyArray[2] );
		
		tDlg.m_PropertyGroupPage.m_PropStyle = DisplayVars->GetPropStyle();
		tDlg.m_PropertyGroupPage.pDoc = this;
		if ( DisplayVars->GetLastShadeLevel() != SHADELEVEL0 ) {
			tDlg.m_PropertyGroupPage.m_CurrentPropLevel	= DisplayVars->GetLastShadeLevel() - SHADELEVEL2;
		} else {
			tDlg.m_PropertyGroupPage.m_CurrentPropLevel	= 0;
		}
		
		// Structure Page.
		tDlg.m_StructurePage.pDoc = this;
		tDlg.m_StructurePage.m_DisplayVars = DisplayVars;
		tDlg.m_StructurePage.m_ModifyAll = TRUE;
				
		// Mode/Style Page
		tDlg.m_ShadeModePage.m_PrimaryLevel = DisplayVars->GetPrimaryLevel();
		tDlg.m_ShadeModePage.m_SecondaryLevel = DisplayVars->GetSecondaryLevel();
		tDlg.m_ShadeModePage.m_TertiaryLevel = DisplayVars->GetTertiaryLevel();
		tDlg.m_ShadeModePage.m_ModeConserved = DisplayVars->GetModeConserved();
		tDlg.m_ShadeModePage.m_DiffMode = DisplayVars->GetDiffMode();
		tDlg.m_ShadeModePage.m_ResidueMode = DisplayVars->GetResidueMode();
		tDlg.m_ShadeModePage.m_ShadeLevel  = DisplayVars->GetLastShadeLevel();
		tDlg.m_ShadeModePage.m_GroupEnabled = DisplayVars->GetGroupEnabled();
		tDlg.m_ShadeModePage.m_ConsSubStyle = DisplayVars->GetConsSubStyle();
		tDlg.m_ShadeModePage.m_BackColor0 = m_UserVars.m_BackColor0;
		tDlg.m_ShadeModePage.m_ForeColor0 = m_UserVars.m_ForeColor0;
		tDlg.m_ShadeModePage.m_BackColor60 = m_UserVars.m_BackColor60;
		tDlg.m_ShadeModePage.m_ForeColor60 = m_UserVars.m_ForeColor60;
		tDlg.m_ShadeModePage.m_BackColor80 = m_UserVars.m_BackColor80;
		tDlg.m_ShadeModePage.m_ForeColor80 = m_UserVars.m_ForeColor80;
		tDlg.m_ShadeModePage.m_BackColor100 = m_UserVars.m_BackColor100;
		tDlg.m_ShadeModePage.m_ForeColor100 = m_UserVars.m_ForeColor100;

		tDlg.m_ShadeModePage.m_FontWeight = m_UserVars.m_FontWeight;
		tDlg.m_ShadeModePage.m_FontSize = m_UserVars.m_FontSize;

		// Identity Page
		CPtrList *pList = DisplayVars->GetGroupList();
		POSITION tPos = pList->GetHeadPosition();
		while (tPos != NULL ) {
			CGeneSegment *pCGSeg = (CGeneSegment *)pList->GetNext(tPos);
			if ( pCGSeg->GetStyle() == LINESEQUENCE ) {
				tDlg.m_IdentityPage.m_SegList.AddTail(pCGSeg);
			}
		}
		pList = DisplayVars->GetIdentList();
		tPos = pList->GetHeadPosition();
		while ( tPos != NULL ) {
			tDlg.m_IdentityPage.m_IdentList.AddTail( pList->GetNext(tPos));
		}
		DisplayVars->GetIdentColors( &tDlg.m_IdentityPage.m_rgbText, &tDlg.m_IdentityPage.m_rgbBack );

		if ( ActivePage != ACTPAGENONE ) {
			tDlg.m_GroupPropPage.m_CurrentGroupName = DisplayVars->GetGroupName();
		}
	}

	tDlg.m_GroupPropPage.pDoc = this;

	tDlg.m_GroupPropPage.m_ColorSeqNames = m_UserVars.m_ColorSeqNames;
	tDlg.m_GroupPropPage.m_GroupConsLevel = m_UserVars.m_GroupConsLevel;
	tDlg.m_GroupPropPage.m_InitSimilarities = m_UserVars.m_PCRSimilarities;
	tDlg.m_GroupPropPage.m_PCRLevel = m_UserVars.m_PCRLevel;
	// Property Group Page
	// CCombo1Box

// Start Display Vars ...
	
	tDlg.DoModal();

	// See if any groups left ...
	if ( !m_UserVars.m_DisplayVars.GetCount() ) {
		m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
	} else {
		if ( m_UserVars.m_GroupDisplayMode == 0 ) {
			SetStructureAlignment(&m_UserVars.m_Vars);
		} else {
			// Lets insure that all the groups/structure info is setup properly
			POSITION dPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			// Skip first
			// m_UserVars.m_DisplayVars.GetNext(dPos);

			while ( dPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(dPos);

				if ( DisplayVars->GetStcGroup().GetMasterSeq().GetLength() != 0 ) {

					SetStructureAlignment( DisplayVars );

				}
			}
		}
	}

	if ( ReDraw ) {
	
		AutoShade(-1);
	}
}



void CGenedocDoc::OnAlign() 
{
	// TODO: Add your command handler code here
	CMultAl *MultAl = new CMultAl();
	if ( MultAl->PWAlign( this ) ) {
		ReSizeRows();
		AutoShade( -1, 1 );		// Second -1 is ignored
		// Dirty the document
		SetModifiedFlag();
	}
	delete MultAl;
}

void CGenedocDoc::OnConfigreport() 
{
	// TODO: Add your command handler code here
	DoConfigure( CGenedocDoc::ACTPAGEREPORTS, FALSE );
	
}

