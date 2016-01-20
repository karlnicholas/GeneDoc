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

IMPLEMENT_DYNCREATE(CDStatMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CDStatMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDStatMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// toolbar buttons - IDs are command buttons
static UINT BASED_CODE dstatbut[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	IDM_DSTATCOPY, 
		ID_SEPARATOR,
	IDM_DSTATGRAPHSETUP, 
		ID_SEPARATOR, 
	IDM_DSTATWRITESCORE, 
	IDM_DSTATWRITEDATA
};

int CDStatMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	lpCreateStruct->style |= WS_MAXIMIZE;
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	// CToolBar
	if (!m_DStatBar.Create(this) ||
		!m_DStatBar.LoadBitmap ( IDB_DSTATBAR ) ||
		!m_DStatBar.SetButtons( dstatbut, sizeof(dstatbut)/sizeof(UINT) )
	) {
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	return 0;
}
 
