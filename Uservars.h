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

typedef struct {


	int	m_ShowComments;	// T/F
	int	m_ShowManShade;	// T/F
	int m_TransTilde;
	int m_PrintFileName;	//T/F
	int m_PrintDate;	//T/F

	CPtrList m_listLogOdds;		// stcSearch *Storage ..

	CString m_strLogOddsFile;
	double m_dLogOddsMin;
	int m_iLogOddsBestN;
	int	m_iLogOddsMode;
	COLORREF m_rgbLogOddsOverlap;
	int m_iLogOddsNoOv;
	double m_dLogOddsTL1;
	double m_dLogOddsTL2;
	double m_dLogOddsTL3;
	int m_iLogOddsOutTab;
	double m_dLogOddsMPC;
	int m_iLogOddsBack;
	double m_dLogOddsStA;
	double m_dLogOddsStC;
	double m_dLogOddsStG;
	double m_dLogOddsStT;
	
	int m_SumDefDis;
	int m_SumColInch;
	int m_Sum2Wid;
	int m_SumTextBlack;

	// Start User Variables ....
	int m_PrintShading;

	CPtrList listSearch;		// stcSearch *Storage ..
	int m_ProSite;
	int m_DNAAmbEn;
	COLORREF m_OverlapColor;

	CString m_strLead;
	CString m_strTail;
	int m_MaxNameLength;

	#define	NUMCHEMPROP 12
	int ChemPropEnabled[12];
	stcChemProp ChemGroupOxi[12];
	stcChemProp ChemGroupRed[12];
	stcChemProp ChemCons[3];
	int m_ChemPropCysteine;
	int m_ChemPropShowProp;

	char m_ConservedGap;	// ' ' or '-' for conserve sequences ...

	char m_MarkerSymb;		// *  symbol, 
	int m_MarkerSpacing;	// 10  spacing between symbols, 
	int m_MarkerReplace;	// 2  how often to replace a symbol with a number, 
	int m_MarkerStart;		// -13  the number to be assigned to the first column of the alignment,
	int m_MarkerEnable;		// is it enabled?

	int m_ResidueUpper;		// 0 = normal, 1 = upper, 2 = lower

	// New vars ..
	CDisplayVars	m_Vars;		// Only Display Variables for non groups...
	
	CPtrList	m_DisplayVars;		// This holds CDisplayVars for groups 
	
	int m_GroupDisplayMode;			// 0 = not enabled, 

	int m_ColorSeqNames;

	CString m_AutoShade4Structure;
	CString m_AutoShade3Structure;
	CString m_AutoShade2Structure;

	CStc	m_Stc;				// Project Structure Definitions
	CStringList m_StcDefUser;		// User definition files
	// 
	double m_GroupConsLevel;
	CString m_PCRSimilarities;
	double m_PCRLevel;
	// 
	COLORREF	m_ForeColor100;
	COLORREF	m_ForeColor80;
	COLORREF	m_ForeColor60;
	COLORREF	m_ForeColor0;

	COLORREF	m_BackColor100;
	COLORREF	m_BackColor80;
	COLORREF	m_BackColor60;
	COLORREF	m_BackColor0;


	int m_FontWeight;
	int m_FontSize;

	int			m_WidthMode;
	int			m_FixedXSize;


	CPtrArray	m_ShadePairArray;		// Holding a list of ShadePairStruct's
	CPtrArray	m_ScoreTableArray;
	int			m_CurrentScoreTable;
	
	double m_LeftBorder;
	double m_RightBorder;
	double m_TopBorder;
	double m_BottomBorder;

	CString m_PrintString;  // A header or footer string for printouts
	int m_PrintStringFlag;	//  = no, 1 = upper center, 2 = lower center.
	int m_PrintPageNumber;	// 0 = no, 1 = Upper Center, 2 = Upper Right, 3 = Lower Center, 4 = Lower Right.
	int m_PrintPageOffset;	// Offset to Page numbers while printing.
	int m_PrintFontWeight;
	int m_PrintFontSize;
	CString m_PrintFontName;
	int m_PrintGeneBlock;

	int m_ConsensusLine;			// 0 = upper
	
	int m_ShowTail;			// 1 = Show Gap Location Indicator

	int	m_Orientation;		// 0 = Portrait

	int m_GapInd;			// 0 = '-', 1 = '.' 
	
	int m_ProjectType;		// 0 = protein, 1 = mixed, 2 = dna, 3 = rna
	
	CString m_TitleProgram;
	CString m_TitleExtendGap;
	CString m_TitleOpenGap;
	CString m_TitleScoreMatrix;

	CString m_ParseString;
	int m_DispTreeWeight;
	
	int m_ScoringMethod;

	int m_PictWidth;
	int m_PictHeight;
	int m_PictAscent;

	CString m_DNATransName;
	CString m_DNATrans;
	CString m_DNATransStart;

	BOOL	m_RepExactMatch;
	BOOL	m_RepJuxtaposition;
	BOOL	m_RepAlignedGaps;
	BOOL	m_RepAbsoluteVal;
	BOOL	m_RepPercentVal;
	int		m_RepOutMatrix;
	int		m_RepLabelTop;
	int		m_RepLabelSingle;

	BOOL	m_RepIncAA;
	BOOL	m_MakeBackups;
	BOOL	m_LocAfterName;
	BOOL	m_LocAfterSeq;

} UserVars;
