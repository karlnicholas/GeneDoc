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
// stcdatad.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStcDataDet dialog


CStcDataDet::CStcDataDet(CWnd* pParent /*=NULL*/)
	: CDialog(CStcDataDet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStcDataDet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CStcDataDet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStcDataDet)
	DDX_Control(pDX, IDC_DATADETLIST, m_DataDetList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStcDataDet, CDialog)
	//{{AFX_MSG_MAP(CStcDataDet)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStcDataDet message handlers

void CStcDataDet::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
    char tchBuffer[256]; 
//	TEXTMETRIC tm;
    int i;
	StcColorMapValue *pCMV;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_DATADETLIST)
		&& (lpDrawItemStruct->itemID != -1)
	) {

//		GetTextMetrics( lpDrawItemStruct->hDC, &tm);

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pCMV = (StcColorMapValue *)lpDrawItemStruct->itemData;

			m_DataDetList.GetText( lpDrawItemStruct->itemID, tchBuffer );
			
			for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, pCMV->BackColor );
			SetTextColor ( lpDrawItemStruct->hDC, pCMV->TextColor );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);

/*			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 
*/
			break;
 
		case ODA_SELECT:
/* 
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);
*/			
			break; 
		}
	
	}

//	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CStcDataDet::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( (
		lpMeasureItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpMeasureItemStruct->CtlID == IDC_DATADETLIST)
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	}

//	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CStcDataDet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// CMapWordToPtr
	
	POSITION pos;
	WORD key;
	void *pv;
	int i = 0;
	for( pos = m_ColorMap->GetStartPosition(); pos != NULL; )
	{
		m_ColorMap->GetNextAssoc( pos, key, pv );
		StcColorMapValue *pCMV = (StcColorMapValue *)pv;

		m_DataDetList.AddString ( *pCMV->Label );
		m_DataDetList.SetItemDataPtr ( i, pCMV );

		++i;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}
