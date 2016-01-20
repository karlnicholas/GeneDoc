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
// GraphSetup.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup dialog


CGraphSetup::CGraphSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphSetup)
	m_PageHeight = 0.0f;
	m_PageWidth = 0.0f;
	m_Set1Count = 0;
	m_Set2Count = 0;
	m_TSide = -1;
	m_ChartTitle = _T("");
	m_xChtTitPct = 0;
	m_yDStatPct = 0;
	m_xKSprPct = 0;
	m_yKSprPct = 0;
	m_LineWidth = 0;
	m_RoundingFactor = 0.0;
	m_xXAxTPct = 0;
	m_xBorderPct = 0;
	m_yBorderPct = 0;
	m_yYAxTPct = 0;
	m_xDStatPct = 0;
	m_XAxisTitle = _T("");
	m_YAxisTitle = _T("");
	//}}AFX_DATA_INIT
}


void CGraphSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphSetup)
	DDX_Text(pDX, IDC_PAGEHEIGHT, m_PageHeight);
	DDX_Text(pDX, IDC_PAGEWIDTH, m_PageWidth);
	DDX_Text(pDX, IDC_SET1COUNT, m_Set1Count);
	DDX_Text(pDX, IDC_SET2COUNT, m_Set2Count);
	DDX_Radio(pDX, IDC_TSIDE1, m_TSide);
	DDX_Text(pDX, IDC_CHARTTITLE, m_ChartTitle);
	DDX_Text(pDX, IDC_CHARTTITLEPCT, m_xChtTitPct);
	DDX_Text(pDX, IDC_DSTATYPCT, m_yDStatPct);
	DDX_Text(pDX, IDC_KSPRXPCT, m_xKSprPct);
	DDX_Text(pDX, IDC_KSPRYPCT, m_yKSprPct);
	DDX_Text(pDX, IDC_LINEWIDTH, m_LineWidth);
	DDX_Text(pDX, IDC_XAXISROUNDING, m_RoundingFactor);
	DDX_Text(pDX, IDC_XAXISTITLEPCT, m_xXAxTPct);
	DDX_Text(pDX, IDC_XBORDERPCT, m_xBorderPct);
	DDX_Text(pDX, IDC_YBORDERPCT, m_yBorderPct);
	DDX_Text(pDX, IDC_YAXISTITLEPCT, m_yYAxTPct);
	DDX_Text(pDX, IDC_DSTATXPCT, m_xDStatPct);
	DDX_Text(pDX, IDC_XAXISTITLE, m_XAxisTitle);
	DDX_Text(pDX, IDC_YAXISTITLE, m_YAxisTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphSetup, CDialog)
	//{{AFX_MSG_MAP(CGraphSetup)
	ON_BN_CLICKED(IDC_CHGFONT, OnChgfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup message handlers

void CGraphSetup::OnChgfont() 
{
	// TODO: Add your control notification handler code here
	CClientDC dc(NULL);
	LOGFONT lf = m_logFont;
	lf.lfHeight = -::MulDiv(-lf.lfHeight, dc.GetDeviceCaps(LOGPIXELSY), 72);
	CFontDialog dlg(&lf);
	// dlg.m_cf.rgbColors = m_crText;
	if (dlg.DoModal() == IDOK)
	{
		lf.lfHeight = -::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY));
		// m_crText = dlg.GetColor();
		m_logFont = lf;
	}
}
