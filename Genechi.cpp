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

IMPLEMENT_DYNCREATE(CGeneMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CGeneMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGeneMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// toolbar buttons - IDs are command buttons
static UINT BASED_CODE genebut[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	IDM_SELECT,
	IDM_COPYMETACLIP,
	IDM_FIND, 
		ID_SEPARATOR,
	IDM_GENECLEARSHADE,
	IDM_GENEAUTOSHADE2,
	IDM_GENEAUTOSHADE3,
	IDM_GENEAUTOSHADE4,
		ID_SEPARATOR,
	IDM_GENEMODECONSERVED, 
	IDM_GENEMODEQUANTIFY, 
	IDM_GENEMODEPROPERTY, 
	IDM_GENEMODESEARCH, 
	IDM_GENEMODESTRUCTURE, 
	IDM_GENEMODEPHYSIOCHEM, 
	IDM_GENEMODESIMILARITY, 
	IDM_GENEMODELOGODDS, 
		ID_SEPARATOR,
	IDM_GENERESIDUEMODEDIFF, 
	IDM_GENEGROUPENABLE,
		ID_SEPARATOR,
	IDM_GENESHADEGROUPS, 
		ID_SEPARATOR,
	IDM_SELECTCOL,
	IDM_GENESCORE,
	IDM_GENEINSERTFILL, 
	IDM_GENEDELETEFILL, 
		ID_SEPARATOR,
	IDM_GENEARRANGE, 
	IDM_GENEMOVE, 
	IDM_GENEINSERTDASH, 
	IDM_GENEINSERTOTHER, 
	IDM_GENEINSERTONE, 
	IDM_SELECTARRSEQ, 
		ID_SEPARATOR,
	IDM_MANUALSHADE, 
	IDM_GENEEDITMODE, 

};

BOOL 
CGeneMDIChildWnd::PreCreateWindow(CREATESTRUCT& cs )
{

//    cs.style |= WS_MAXIMIZE; 

    // Call the base-class version
    return CMDIChildWnd::PreCreateWindow(cs); 

	
//	cs.style |= WS_MAXIMIZE;	

//	return CMDIChildWnd::PreCreateWindow( cs );
}



int
CGeneMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	// CToolBar
#ifdef _WIN32
	if (!m_GeneBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS ) ||
#else
	if (!m_GeneBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP ) ||
#endif
		!m_GeneBar.LoadBitmap ( IDB_GENEBAR ) ||
		!m_GeneBar.SetButtons( genebut, sizeof(genebut)/sizeof(UINT) )
	) {
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	return 0;
}
 
