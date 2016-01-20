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
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)

#ifdef WIN32
#include <afxrich.h>
#define VIEWBASE CRichEditView
#else 
#define VIEWBASE CEditView
#endif

#include <limits.h>



// typedef ...

extern int ScoreArray[26][26];
extern int	NewGap, GapLen;
extern int CurrentZeroDistance;

#define ScoreCurrentArray( n1, n2 ) (ScoreArray[n1 - 'A'][n2 - 'A'])
extern char ProteinLocArray[23];
extern char DNALocArray[23];
extern void GetTempFileName (CString& PathName );
extern void DeleteTempFile (CString& PathName );

typedef struct {
	CString Chem;
	COLORREF	TextColor;
	COLORREF BackColor;
} stcChemProp;


typedef struct {
	CString strSearch;
	CString strName;
	CString strDescrip;
	COLORREF rgbText;
	COLORREF rgbBack;
	int iEnabled;
} stcSearch;

typedef struct {
	CString strName;
	CString strDescrip;
	CString strMotif;
	COLORREF rgbText;
	COLORREF rgbBack;
	double (*dLogOddsArr)[26];
	int iLogOddsCount;
	double dLogOddsBayes;
	int iEnabled;
} stcLogOdds;


	extern void Blosum35( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Blosum45( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Blosum62( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Blosum80( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Blosum100( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Pam120( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Pam160( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Pam200( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void Pam250( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );

	// Dna  Start at 9 .. 
	extern void dp20( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp30( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp47( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp50( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp65( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp85( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp110( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp20b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp50b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void dp85b( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	extern void IDMat( int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	

enum {
	SHADECONSERVED, 
	SHADEQUANTIFY, 
	SHADEPROPERTY, 
	SHADESEARCH, 
	SHADESTRUCTURE, 
	SHADEPHYSIOCHEM,  
	SHADEIDENTITY, 
	SHADELOGODDS 
};

enum {
	SHADELEVEL0, 
	SHADELEVEL2, 
	SHADELEVEL3, 
	SHADELEVEL4
};

enum {
	GROUPDISPNONE, 
	GROUPDISPSETUP,
	GROUPDISPCONT,
	GROUPDISPCONTNG,
	GROUPDISPCONS,
	GROUPDISPCONSX,
	GROUPDISPPCR,
	GROUPDISPPCRSIM,
	GROUPDISPPHYSIOCHEM,
	GROUPDISPDNASET, 

	GROUPDISPMAX
};

enum {
	LINESEQUENCE, 
	LINECOMMENT 
};


#include "plex.h"
#include "charmap.h"
#include "dwordmap.h"
// typedef
#include "genestor.h"
#include "segnames.h"
#include "shadeps.h"
// #include "props.h"
#include "scorets.h"

// Structure Definition
#include "stc.h"
#include "stcgrp.h"
#include "property.h"
// Main doc
#include "dispvars.h"
#include "uservars.h"

// typedef
#include "usermess.h"
#include "drawstc.h"

#include "dstatchi.h"
#include "phylochi.h"
#include "genechi.h"

// Main prog
#include "genedoc.h"

// PictFile
#include "pictfile.h"
#include "htmlfile.h"
#include "rtffile.h"

// Segements
#include "gsbase.h"
#include "gsegment.h"
#include "gsfiller.h"

// PhyloGenetic Tree
#include "phylbase.h"
#include "phylnode.h"
#include "phylseq.h"

// Views
#include "textview.h"
//#include "scoedit.h"
//#include "scinfed.h"
//#include "srchrepv.h"

// DStat View
#include "GraphStp.h"
#include "DStatOb.h"

// Main doc
#include "geneddoc.h"

#include "DStatVw.h"
#include "GelView.h"

// Alignment Object
#include "pwalign.h"

// Utility
#include "gstring.h"
// caret
#include "mycaret.h"
#include "sumcaret.h"

#include "sviewret.h"

//
#include "mainfrm.h"

#include "gvbase.h"

#include "gprowvw.h"
#include "gpsumvw.h"

// View
#include "gvedit.h"
#include "gvsum.h"
#include "gvelead.h"
#include "gvetail.h"
#include "gvefill.h"

// Modal dialog
#include "colorbar.h"
// Phylogen Dialog
#include "phylodlg.h"

// Phylogen View
#include "phylovw.h"

// View
#include "genedvw.h"
#include "sumview.h"

//dialog
#include "scorecan.h"
#include "showtabl.h"
#include "shadeedi.h"
#include "proped.h"
#include "displayp.h"
#include "prints.h"
#include "searchdl.h"
#include "logodds.h"
#include "propgp.h"
#include "shademp.h"
#include "cscored.h"
#include "stcdatad.h"
#include "cstcpdlg.h"
#include "chemprop.h"
#include "grpprop.h"
#include "confiden.h"
#include "repdlg.h"
#include "propsht.h"
#include "grppsht.h"
#include "titlingf.h"
#include "dispgnm.h"
#include "seqinp.h"
#include "groupsel.h"
#include "findrepl.h"
#include "importty.h"
#include "exportdl.h"
#include "srchdlg.h"
#include "logdlg.h"
#include "pdbdialo.h"
#include "htmlpicd.h"
#include "refiltdl.h"
#include "srchrepd.h"
#include "seqseldl.h"
#include "motseqdl.h"
#include "finddlg.h"
#include "selarrse.h"
#include "selproje.h"
#include "dnatrans.h"
#include "aligndlg.h"
#include "genbank.h"

//
#include "seqdetdi.h"
#include "seqdialo.h"

#ifdef WIN32

#define GMEM_FLAG GMEM_FIXED

#else 

#define GMEM_FLAG GMEM_MOVEABLE

#endif

enum {
	pict_init, 
	pict_charout, 
	pict_newline, 
	pict_exit
};

void PictFile ( int action, double *xpos, double *ypos,  char c = 0,  COLORREF ForeGround = 0, COLORREF BackGround = 0 );

