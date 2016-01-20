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

IMPLEMENT_DYNCREATE(CPhyloMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CPhyloMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPhyloMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// toolbar buttons - IDs are command buttons
static UINT BASED_CODE phylobut[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	IDM_PHYLOCOPY, 
		ID_SEPARATOR,
	IDM_PHYLOCREATE, 
	IDM_PHYLODELETE, 
	IDM_PHYLOMVUP, 
	IDM_PHYLOMVDN, 
	IDM_PHYLOCLEAR, 
		ID_SEPARATOR,
	IDM_DISPTREEWEIGHT, 
		ID_SEPARATOR,
	IDM_PHYLODLG, 
};

int CPhyloMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	lpCreateStruct->style |= WS_MAXIMIZE;
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	// CToolBar
#ifdef _WIN32
	if (!m_PhyloBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS) ||
#else
	if (!m_PhyloBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP) ||
#endif
		!m_PhyloBar.LoadBitmap ( IDB_PHYLOBAR ) ||
		!m_PhyloBar.SetButtons( phylobut, sizeof(phylobut)/sizeof(UINT) )
	) {
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	return 0;
}
 
