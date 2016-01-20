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
// selarrse.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelArrSeq dialog


CSelArrSeq::CSelArrSeq(CWnd* pParent /*=NULL*/)
	: CDialog(CSelArrSeq::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelArrSeq)
	//}}AFX_DATA_INIT
}

void CSelArrSeq::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelArrSeq)
	DDX_Control(pDX, IDC_LIST1, m_SeqList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelArrSeq, CDialog)
	//{{AFX_MSG_MAP(CSelArrSeq)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_DESEL, OnDesel)
	ON_BN_CLICKED(IDC_COMPLEMENT, OnComplement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSelArrSeq message handlers

void CSelArrSeq::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    char tchBuffer[2048]; 
    RECT rect;
	TEXTMETRIC tm;
    int i;
    int OffSet;
    CGeneSegment *pCGSeg;
	
	if ( (
		lpDrawItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpDrawItemStruct->CtlID == IDC_LIST1)
		&& (lpDrawItemStruct->itemID != -1)
	) {

		GetTextMetrics( lpDrawItemStruct->hDC, &tm);
		OffSet = tm.tmHeight * 7;

		switch ( lpDrawItemStruct->itemAction ) {
		case ODA_DRAWENTIRE:

			pCGSeg = (CGeneSegment *)lpDrawItemStruct->itemData;

			sprintf ( tchBuffer, "%s",  (const char *)pCGSeg->GetTitle() );
			
//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));
			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
			ExtTextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left, 
				lpDrawItemStruct->rcItem.top, 
				ETO_CLIPPED, 
				&rect, 
				tchBuffer, 
				pCGSeg->GetTitle().GetLength(), 
				NULL
			);
			
			// Bingo ..
			strncpy ( tchBuffer, pCGSeg->GetDescr(), pCGSeg->GetDescr().GetLength() );
			tchBuffer[pCGSeg->GetDescr().GetLength()] = 0;
			
			for ( i = strlen ( tchBuffer ); i < 100; ++i ) {
				tchBuffer[i] = ' ';
			}
			tchBuffer[i] = 0;

			SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
			SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

			TextOut(lpDrawItemStruct->hDC, 
				lpDrawItemStruct->rcItem.left + OffSet, 
				lpDrawItemStruct->rcItem.top, 
				tchBuffer, 
				strlen(tchBuffer)
			);
			
			if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
				rect.left = lpDrawItemStruct->rcItem.left; 
				rect.top = lpDrawItemStruct->rcItem.top; 
				rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
				rect.bottom = lpDrawItemStruct->rcItem.bottom; 
 
				InvertRect(lpDrawItemStruct->hDC, &rect);
			} 

			break;
 
		case ODA_SELECT:
 
			rect.left = lpDrawItemStruct->rcItem.left; 
			rect.top = lpDrawItemStruct->rcItem.top; 
			rect.right = lpDrawItemStruct->rcItem.left + OffSet; 
			rect.bottom = lpDrawItemStruct->rcItem.bottom; 
	 
			InvertRect(lpDrawItemStruct->hDC, &rect);
			
			break; 
		}
	
	}
}

void CSelArrSeq::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
 
	/* Set the height of the list box items. */ 
	if ( (
		lpMeasureItemStruct->CtlType == ODT_LISTBOX) 
		&& (lpMeasureItemStruct->itemID != -1)
	) {
 
 		CDC *pDC = GetDC();
 		
		pDC->GetTextMetrics(&tm);
	
		lpMeasureItemStruct->itemHeight = tm.tmHeight - tm.tmInternalLeading; 
		
		ReleaseDC ( pDC );
	
	} else {
		CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	}
	
}

void CSelArrSeq::OnOK() 
{
	// TODO: Add extra validation here
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	POSITION tPos;

	// What about this? Is it OK here, or should it be later?

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tCGSeg->SetArrangeFlag(0);

	}

	int SelCount = m_SeqList.GetSelCount();
	
	if ( SelCount == 0 || SelCount == LB_ERR ) {
		CDialog::OnOK();
		return;
	}
			   
	int *SelArray = new int[SelCount];
	
	m_SeqList.GetSelItems( SelCount, SelArray );

	for ( int i=SelCount-1; i >=0; --i ) {

		int SeqSel = SelArray[i];
		
		CGSFiller *pGSFiller = pDoc->pGSFiller;
		// Put the data rows on the list

		tPos = pGSFiller->SegDataList.FindIndex (SeqSel + 2);

		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetAt (tPos);

		tCGSeg->SetArrangeFlag(1);

	}

	delete SelArray;
	
	CDialog::OnOK();
}

BOOL CSelArrSeq::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CGSFiller *pGSFiller = pDoc->pGSFiller;
	// Put the data rows on the list
	int Count = 0;
	if ( pGSFiller != NULL ) {

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {
	
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
	
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
	
			// CListBox
			int aloc = m_SeqList.AddString ( (const char *)tCGSeg->GetTitle() );
			m_SeqList.SetItemDataPtr(aloc, tCGSeg );
			Count++;
	
		}
	}
	int Sel = 0;
	int idx = 0;
	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			if ( tCGSeg->GetArrangeFlag() ) {
				m_SeqList.SetSel( idx );
				Sel = 1;
			}
			idx++;
		}
	}

	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelArrSeq::OnDesel() 
{
	// TODO: Add your control notification handler code here
	m_SeqList.SetSel(-1, FALSE );
	Invalidate();
	
}

void CSelArrSeq::OnComplement() 
{
	// TODO: Add your control notification handler code here
	// What about this? Is it OK here, or should it be later?


	int SelCount = m_SeqList.GetSelCount();

	int *SelArray = new int[SelCount];

	m_SeqList.GetSelItems( SelCount, SelArray );

	// Select All ..
	m_SeqList.SetSel( -1);

	for ( int i=0; i < SelCount; ++i ) {

		int SeqSel = SelArray[i];
		m_SeqList.SetSel( SeqSel, FALSE );
	}

	delete SelArray;

	Invalidate();

}
