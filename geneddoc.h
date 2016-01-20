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
// geneddoc.h : interface of the CGenedocDoc class
//
/////////////////////////////////////////////////////////////////////////////

typedef struct {
	CGeneSegment *pCGSeg;
	GeneStor	*pGeneStor;
} ShadeSegStc;

typedef struct {
	CString FindStr;
	int		FindFrom;
	int		MisMatch;
	int		InsDel;
	COLORREF	rgbText;
	COLORREF	rgbBack;
	int		PrevSeq;
} FindStc;


class CGenedocDoc : public CDocument
{
protected: // create from serialization only
	CGenedocDoc();
	DECLARE_DYNCREATE(CGenedocDoc)

	void DoMarkerLine();

	int OnFind(CView *pView );
	BOOL CheckMatch( char cF, char cS);
	FindStc m_pFS;
	// PCR Contrast ..
	void PCRMatchArr( int MatchArr[2][26], ShadePairStruct* rSPS, int *Count );
	void AutoShadePCR(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow
	);
	int m_UsePCRSim;
	void AutoShadeDNASet();

	// DStat Stuff

	CDStatObject DStatObject;
	void DStatScore( DWORD StartRange, DWORD EndRange, int GroupOnly );
	void DStatStat(int Opt);
// Pathname ..

	CString m_PathName;
	void SetFilePath(const char *pszPathName);

// Structure Vars
	BOOL GetDataTypeValuesFile( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFileSeq( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFileDss( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFilePhd( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFileSsp( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFilePrd( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFileStu( const CString& szFilename, CStcGroup* StcGroup );
	BOOL GetDataTypeValuesFilePDB( const CString& szFilename, CStcGroup* StcGroup );
	BOOL SetStructureAlignment(CDisplayVars *DisplayVars);

//
	
	void SortMatchArr( CDisplayVars *DisplayVars, int MatchArr[2][26], ShadePairStruct* rSPS, int *Count, int Depth );
	void AutoShade( 
		int ShadeLevel = -1,		// If -1, Just Reshade at old level
		int ScoreAll = 0 
	);


	void AutoShadeSearch( 
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeLogOdds( 
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void ClearSearch(UserVars *dUV);
	int ScanPrositeMotifs(const CString& PathName, CPtrList * listSearch );
	int ScanRebaseFile(const CString& PathName, CPtrList *listSearch);

	int ScanMemeMotifs(const CString& PathName, CPtrList * listSearch );
	void ClearLogOdds(UserVars *dUV);
	void LogOddsShade( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD SeqLength );
	void LogOddsShadeBestN( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount );
	void LogOddsShadeThree( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount );
	void LogOddsShadeBetter( stcLogOdds *pLogOdds, GeneStor *pGeneStor, DWORD OuterCount );

	DWORD MotifStop;
	DWORD MotifStart;
	int Csignal;
	int Nsignal;


	CByteArray Member[26];
	CByteArray Chosen;
	CByteArray Max;
	CByteArray Min;	 

	int BuildMatrix( const char *motif );
	int LocateMotif( GeneStor *ptr, int pos, int length, GeneStor *end );
	int ProcessRecord( stcSearch *pSearch, GeneStor *pGeneStor, DWORD SeqLength, int Test = 0 );
	int MotifLength( const char *motif );
	int SearchRebase( stcSearch *pSearch, GeneStor *pGeneStor, DWORD SeqLength, int Test = 0 );
	void SearchRebaseReport( stcSearch *pSearch, ShadeSegStc *pSegArr, CPtrArray& RepArr, DWORD OuterCount );
	BOOL RebaseReport(CString& PathName);
	void PlotUniqueFrags();
	int LogOddsReport(CString& PathName);
	void DNAFreqRep(DWORD StartRange, DWORD EndRange);
	void ColFreqRep(DWORD StartRange, DWORD EndRange, int UseWeights );
	
	void GetDNAAmbiguous( ShadePairStruct *pSPS, ShadeSegStc *pSegArr, int RowCount, int *MaxMatchCount, DWORD tCount, int Depth );
	
	void AutoShadeQuantify( 
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeConserve(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeGroupConserve(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeContrast(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);
	int PairwiseCheck( ShadeSegStc *pSegArr, int pSegCount, DWORD tCount, int *PWScr );
	int PairwiseCheckOther( 
		ShadeSegStc *pSegArr, 
		int RowCount, 
		ShadeSegStc *pOSegArr, 
		int gSegCount, 
		DWORD tCount, 
		int *PWScr 
	);
	void AutoShadeDifference(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeIdentity(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeProperty(
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);
	void AutoShadeStructure( 
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow = NULL
	);

	void AutoShadeGroupChem(
		ShadeSegStc* pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc* pConsensusRow 
	);

	void AutoShadeGroupChemCons(
		ShadeSegStc* pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc* pConsensusRow 
	);

	void AutoGroupConsCross (
		ShadeSegStc *pSegArr, 
		int RowCount, 
		int ShadeLevel, 
		CDisplayVars *DisplayVars, 
		ShadeSegStc *pConsensusRow );


	enum {
		ACTPAGENONE, 
		ACTPAGEHIGHLIGHTING, 
		ACTPAGESEARCH, 
		ACTPAGEREPORTS, 
		ACTPAGEPROPERTY, 
		ACTPAGESTRUCTURE, 
		ACTPAGEPHYSIOCHEM, 
		ACTPAGEIDENTITY, 
		ACTPAGELOGODDS
	};

	void AutoShadeMenuFunc( int SHADELEVEL, CString& strAutoShadeStructure );


	void ClearShade();

	void ClearScore();
	void Score( DWORD *nStartRange, DWORD *nEndRange );
	int FindScore ( DWORD Location, DWORD *nStartRange, DWORD *nEndRange );
	void ReScoreAll( int ScoreAll = 0 );
	int PairWiseScore( 
		DWORD *nStartRange, 
		DWORD *nEndRange, 
		unsigned long *Score, 
		int RowCount,  
		ShadeSegStc *pSegArr 
	);

	int TreeScore( 
		DWORD *nStartRange, 
		DWORD *nEndRange, 
		unsigned long *Score, 
		int RowCount, 
		ShadeSegStc *pSegArr, 
		CString& PathName);
	int LogOddsScore( 
		DWORD *nStartRange, 
		DWORD *nEndRange, 
		unsigned long *Score, 
		int RowCount, 
		ShadeSegStc *pSegArr );
	void ScoreProtLO(	
		DWORD *nStartRange, 
		DWORD *nEndRange, 
		unsigned long *Score, 
		int RowCount, 
		ShadeSegStc *pSegArr );
	void ScoreDNALO(
		DWORD *nStartRange, 
		DWORD *nEndRange, 
		unsigned long *Score, 
		int RowCount, 
		ShadeSegStc *pSegArr );


	void InsertFillerRange(DWORD StartRange, DWORD EndRange );
	void DeleteFillerRange(DWORD StartRange, DWORD EndRange, int DelData );
	const char *GDUFindString ( const CString& FindString );
	void SetShadeGroupDefault(CPtrArray *ShadePairArray, int NewScoreTable);
	const char * GetScoreTableDescr(int ScoreTable);

	int SequenceImport();
	int SequenceExport(int Selected = 0);
	int GetMSFFile( CString PathName, int Append = 0 );
	int GetFastaFile( CString PathName, int Append = 0 );
	int GetFasNTFile( CString PathName, int Append = 0 );
	int GetALNFile( CString PathName, int Append = 0);
	int GetPIRFile( CString PathName, int Append );
	int GetPhylipFile( CString PathName, int Append );
	int GetTextFile( CString PathName, int Append, 
		const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC );
	int GetGenbankFile( CString PathName, int Append = 0 );

	int WriteStatFile( const char *FileName );
	int WriteScoreFile( const char *FileName );
	int WriteManRepFile( const char *FileName );

	CTextView *m_pTextView;
	CView *m_pTreeView;
	CView *m_pGeneView;
	CView *m_pSummaryView;
	CView *m_pDStatView;
	CView *m_pGelView;

	CString ConvertPathname( const char *nExt );

	// Fasta read work vars ...
	BOOL bCR, bEOF;

	#define  BSIZE  64
	
	#define S_NULL      0
	#define S_PRENAME   1
	#define S_NAME      2
	#define S_PRETITLE  3
	#define S_TITLE     4
	#define S_NOTEORSEQ 5
	#define S_NOTES     6
	#define S_SEQ       7

	// The order here is tied to CConfDisplay.	
	enum {
		SCOREPAIR,
		SCORETREE, 
		SCORENUMB, 
		SCORELOGODD, 
		
		SCORETYPEMAX
		
	};

	typedef int (*GetCharProc) (void);
	//typedef short ClassId;
	unsigned I, B;
	char     pLocal[BSIZE];
	HANDLE   hGlobal;
	int nErrno;
	#define ERR_FIL_OPEN 1
	DWORD	gMaxStrSize;

	BOOL ReadTextFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName, 
		const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC );
	int WriteTextFile( const CString& PathName, int Selected = 0 );
	int WriteTNoGapFile( const CString& PathName, int Selected = 0 );

	BOOL ReadFasNTFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WriteFasNTFile( const CString& PathName, int Selected = 0 );
	BOOL ReadFastaFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WriteFastaFile( const CString& PathName, int Selected = 0 );
	BOOL ReadGenbankFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
//	void NEAR  Fastahopen();
//	BOOL NEAR  Fastahputc (char c);
//	HANDLE NEAR  Fastahclose();
//	int Fastagetchar1 (CFile& rFile);
//	int ParseFASTA ( CPtrList *SequenceList, CFile& rFile);
//	int Seq_New(HANDLE hTitle,HANDLE hDesc,HANDLE hText,CPtrList *SequenceList);
	//
	int ReadPIRFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WritePIRFile( const CString& PathName, int Selected = 0 );

	// End of Fasta stuff

	int ReadMSFFile( CPtrList *CommentList, CPtrList *SequenceList, const char *FileName );
	int WriteMSFFile( const char *FileName );
	int ReadALNFile( CPtrList* CommentList, CPtrList* SequenceList, CString& PathName );
	int WriteALNFile( const CString& PathName, int Selected = 0 );
	
	int WritePhylipFile( const CString& PathName, int Selected = 0 );
	int ReadPhylipIFile( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );


	int ProcessRows( CPtrList& CommentList, CPtrList& SequenceList, int Append );
	int ReSizeRows();
	int AppendDataRows(CPtrList& SequenceList, int Append );
	int CreateBottomRows();
	int CreateTopRows();
	
	void SetUserDefaults();
//	void SetUserDefaultsDVars( const CString& AppStr, CDisplayVars* DisplayVars );
	void GetUserDefaultsDVars( const CString& AppStr, CDisplayVars* DisplayVars );
	void GetNewUserDefaults( );

	void GetUserDefaults();
	void SetShadeGroupDefault();
	void ChangeGapChar();
	void GetIniDefaults();

	void CheckOrientation();
	
	void GetProjectType();

	CPhyloNode *m_pPGBase;
	int m_MaxDepth;
	int m_NodeNumber;

	CGeneSegment* GetSequenceFromName( const CString& Name );

	int m_CallSwitch;
	enum { 
		CALLSETMAX, 
		CALLSETNUMBER,
		CALLSETOBJ, 
		CALLDRAWDEBUG
	};
	void CallSetNumber( CObject *p );
	void CallSetMax( CObject *p );
	void CallSetObj( CObject *p );
//	int m_CRDetected;
	
	typedef struct sTreeScoreWork {
	
		int UnionString[28];
		int UnionStringLength;
		int UnionParentAppended;
	//
		int DescendentTypeL;
		int DescendentTypeR;
		sTreeScoreWork *DescendentTSWL;
		sTreeScoreWork *DescendentTSWR;
		int DescendentCharL;
		int DescendentCharR;
	//
		CPhyloNode *m_pPN;
	//
	//
		int m_cAncestry;
		int m_AssignedDescent;
		int m_ScoreIndex;
		int m_ScoreCarry;
		
		int m_SaveBestResidue;
		int m_PrevBestResidue;
	
	} TreeScoreWork;

	typedef struct TreeSaveBests {
		int m_cAncestry;
		int m_PrevBestResidue;
	} TreeSaveBest;

	CPtrList m_TreeScoreList;
	CPtrList m_SaveBestList;

	// option flags
	int m_NumbTreeFlag;
	int m_TreeDebugOutput;

	void CallDrawDebug(CObject *p);
	void DrawDebugNodeBox(CString &ResString, int StartX, CPhyloGenBase *pPGB );
	void DoDrawDebugCmd ( CString& ResString, int DrawCmd, int Depth2, CPhyloGenBase* pPGB );
	void OnDrawDebugTree();
	int TreeTestGood( TreeScoreWork *TSArray, int TSWLEngth );

	FILE * m_DebugFile;
	unsigned long m_DebugScore;
	char m_GapChar;
	unsigned m_CostDiv;
	int m_ScAve;
	BOOL DocPeekMessage(HWND hCanDlg );
	int m_CancelFlag;
	int m_ScoreWaitCursor;


// Attributes
public:

	CGSFiller* pGSFiller;

	void CopyGSFiller( CGSFiller *npGSFiller );
	void SetShadePairArray(CPtrArray *nShadePairArray, CPtrArray *oShadePairArray);
	void CopyUserVars( UserVars *nUserVars, UserVars *oUserVars );
	void ClearUserVars( UserVars * dUserVars );

	int GetNumColors(CDisplayVars *DisplayVars);
	void GetLevelColors(CDisplayVars *DisplayVars, int Level, COLORREF * TextColor, COLORREF *BkColor );

	void GetIniDisplayVars(CDisplayVars *DisplayVars);

	UserVars	m_UserVars;
	int m_SummaryMessaged;

	int ParseTree( const CString & ParseString, int ErrMsgs );
	void SetDepths();
	void WriteString ();
	void ResetTree();
	void CallDocFromDepth( CObject *p );
	void CallDocFromSeq( CObject *p );
	void DoConfigure(int ActivePage = ACTPAGENONE, int ReDraw = TRUE ); 
	void DoGroupConfigure(int ActivePage = ACTPAGENONE, int ReDraw = TRUE ); 

	BOOL LoadUserSduFile(const CString& PathName);
	void ReplaceFromProj(DWORD StartPos, DWORD EndPos);
//	int IndexChar( char n );
	
	// End User Variables ....

// Operations
public:

// Implementation
public:
	virtual ~CGenedocDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnOpenDocument(const char* pszPathName );
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(const char *pszPathName );

// Generated message map functions
protected:
	//{{AFX_MSG(CGenedocDoc)
	afx_msg void OnGenescorefile();
	afx_msg void OnGenestatfile();
	afx_msg void OnConfigure();
	afx_msg void OnGeneeditseq();
	afx_msg void SetIniDefaults();
	afx_msg void OnGeneloadini();
	afx_msg void OnTitlingf();
	afx_msg void OnFileSaveAs();
	afx_msg void OnPhylodlg();
	afx_msg void OnPhyloview();
	afx_msg void OnGeneview();
	afx_msg void OnGenescorepair();
	afx_msg void OnUpdateGenescorepair(CCmdUI* pCmdUI);
	afx_msg void OnGenescoretree();
	afx_msg void OnUpdateGenescoretree(CCmdUI* pCmdUI);
	afx_msg void OnShowtable();
	afx_msg void OnGenescorenumb();
	afx_msg void OnUpdateGenescorenumb(CCmdUI* pCmdUI);
	afx_msg void OnGenescoreinfo();
	afx_msg void OnUpdateGenescoreinfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePhyloview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenestatfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenescorefile(CCmdUI* pCmdUI);
	afx_msg void OnEditstructure();
	afx_msg void OnUpdateEditstructure(CCmdUI* pCmdUI);
	afx_msg void OnEditgroupprop();
	afx_msg void OnGeneshadegroups();
	afx_msg void OnUpdateGeneshadegroups(CCmdUI* pCmdUI);
	afx_msg void OnGeneshadecontrast();
	afx_msg void OnGeneshadegroupconserve();
	afx_msg void OnUpdateGeneshadecontrast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGeneshadegroupconserve(CCmdUI* pCmdUI);
	afx_msg void OnGeneshadecontrastnogap();
	afx_msg void OnUpdateGeneshadecontrastnogap(CCmdUI* pCmdUI);
	afx_msg void OnStcloadpsdb();
	afx_msg void OnUpdateStcloadpsdb(CCmdUI* pCmdUI);
	afx_msg void OnStcloaduserfile();
	afx_msg void OnStclearall();
	afx_msg void OnStcloadembl();
	afx_msg void OnUpdateStcloadembl(CCmdUI* pCmdUI);
	afx_msg void OnGeneautoshade2();
	afx_msg void OnUpdateGeneautoshade2(CCmdUI* pCmdUI);
	afx_msg void OnGeneautoshade3();
	afx_msg void OnUpdateGeneautoshade3(CCmdUI* pCmdUI);
	afx_msg void OnGeneautoshade4();
	afx_msg void OnUpdateGeneautoshade4(CCmdUI* pCmdUI);
	afx_msg void OnGeneclearshade();
	afx_msg void OnUpdateGeneclearshade(CCmdUI* pCmdUI);
	afx_msg void OnGenegroupenable();
	afx_msg void OnUpdateGenegroupenable(CCmdUI* pCmdUI);
	afx_msg void OnGenemodeconserved();
	afx_msg void OnUpdateGenemodeconserved(CCmdUI* pCmdUI);
	afx_msg void OnGenemodeproperty();
	afx_msg void OnUpdateGenemodeproperty(CCmdUI* pCmdUI);
	afx_msg void OnGenemodequantify();
	afx_msg void OnUpdateGenemodequantify(CCmdUI* pCmdUI);
	afx_msg void OnGenemodestructure();
	afx_msg void OnUpdateGenemodestructure(CCmdUI* pCmdUI);
	afx_msg void OnGeneresiduemodediff();
	afx_msg void OnUpdateGeneresiduemodediff(CCmdUI* pCmdUI);
	afx_msg void OnGenedstatview();
	afx_msg void OnUpdateGenedstatview(CCmdUI* pCmdUI);
	afx_msg void OnGroupshadepcr();
	afx_msg void OnUpdateGroupshadepcr(CCmdUI* pCmdUI);
	afx_msg void OnGroupshadepcrsim();
	afx_msg void OnUpdateGroupshadepcrsim(CCmdUI* pCmdUI);
	afx_msg void OnFileimport();
	afx_msg void OnFileexport();
	afx_msg void OnCleargapcols();
	afx_msg void OnPlotstatdstat();
	afx_msg void OnPlotfavsubs();
	afx_msg void OnPlotgroup();
	afx_msg void OnPlotgroupfav();
	afx_msg void OnGenemodephysiochem();
	afx_msg void OnGeneshadegroupphyschem();
	afx_msg void OnUpdateGeneshadegroupphyschem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenemodephysiochem(CCmdUI* pCmdUI);
	afx_msg void OnGenegroupsgconx();
	afx_msg void OnUpdateGenegroupsgconx(CCmdUI* pCmdUI);
	afx_msg void OnGenemodesearch();
	afx_msg void OnUpdateGenemodesearch(CCmdUI* pCmdUI);
	afx_msg void OnGeneshadegroupdna();
	afx_msg void OnUpdateGeneshadegroupdna(CCmdUI* pCmdUI);
	afx_msg void OnPlotfrag();
	afx_msg void OnGenemodesimilarity();
	afx_msg void OnUpdateGenemodesimilarity(CCmdUI* pCmdUI);
	afx_msg void OnStcloadpdb();
	afx_msg void OnUpdateStcloadpdb(CCmdUI* pCmdUI);
	afx_msg void OnSummaryview();
	afx_msg void OnUpdateSummaryview(CCmdUI* pCmdUI);
	afx_msg void OnGenemodelogodds();
	afx_msg void OnUpdateGenemodelogodds(CCmdUI* pCmdUI);
	afx_msg void OnLogoddsview();
	afx_msg void OnUpdateLogoddsview(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnCopycons();
	afx_msg void OnUpdateCopycons(CCmdUI* pCmdUI);
	afx_msg void OnShowmanshade();
	afx_msg void OnUpdateShowman(CCmdUI* pCmdUI);
	afx_msg void OnShowcomments();
	afx_msg void OnUpdateShowcom(CCmdUI* pCmdUI);
	afx_msg void OnClearcomments();
	afx_msg void OnClearmanshade();
	afx_msg void OnSelectarrseq();
	afx_msg void OnGenescorelo();
	afx_msg void OnUpdateGenescorelo(CCmdUI* pCmdUI);
	afx_msg void OnRescoreall();
	afx_msg void OnComplimentsel();
	afx_msg void OnGenereportview();
	afx_msg void OnRegapdna();
	afx_msg void OnSrchrepview();
	afx_msg void OnGenegelview();
	afx_msg void OnUpdateGenegelview(CCmdUI* pCmdUI);
	afx_msg void OnAlign();
	afx_msg void OnManshaderep();
	afx_msg void OnUpdateManshaderep(CCmdUI* pCmdUI);
	afx_msg void OnShadingRep();
	afx_msg void OnConfigreport();
	afx_msg void OnConsprosite();
	afx_msg void OnUpdateConsprosite(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
