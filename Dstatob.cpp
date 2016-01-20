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

#include <search.h>
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CDStatObject, CObject)



void CDStatObject::DoDraw(CDC *pDC )
{
	char buff[256];
	// TODO: add draw code for native data here  
	// strcpy(buff, "XXX");

	CSize docSize = GetDocSize();

	double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
	double xpi = pDC->GetDeviceCaps(LOGPIXELSX);

	int x = (int)((double)docSize.cx/100.0 * xpi);
	int y = (int)((double)docSize.cy/100.0 * ypi);

	int YSpace = (int)(ypi / 24.0);
	int XSpace = (int)(xpi / 24.0);


	// Lets draw graph always ...
	//
	CFont fontTmp;
	CFont* pOldFont = SelectDocFont(pDC, fontTmp, 0);

	CSize fontSize = pDC->GetTextExtent( m_ChartTitle, m_ChartTitle.GetLength() );
	CSize ssize = fontSize;
	// pDC->LPtoDP(&fontSize);

	int charHeight = fontSize.cy;

	int xborder = (int)((double)x * m_xBorderPct);
	int yborder = (int)((double)y * m_yBorderPct);

	yborder += m_LineWidth;

	CPen dPen( PS_DOT, 1, RGB(0,0,0) );

	CPen nPen( PS_SOLID, m_LineWidth, RGB(0,0,0) );
    CPen* oPen = pDC->SelectObject(&nPen);


	pDC->MoveTo(xborder, charHeight + YSpace - m_LineWidth );
	pDC->LineTo(xborder,y - yborder);
	pDC->LineTo(x - XSpace,y - yborder);
	pDC->LineTo(x - XSpace, charHeight + YSpace - m_LineWidth );
	pDC->LineTo(xborder ,charHeight + YSpace - m_LineWidth );


	pDC->TextOut( 
		(int)((double)x * m_xChtTitPct), 
		0, // y - (int)((double)y * m_yChtTitPct), 
		m_ChartTitle 
	);

	int yinc = ((y - yborder) - (charHeight + YSpace ))/4;

	pDC->MoveTo(xborder, charHeight + YSpace );
	pDC->LineTo(xborder - XSpace, charHeight + YSpace );

	CString tStr = "1.0";
	CSize tstrsz;
	tstrsz = pDC->GetTextExtent( tStr, tStr.GetLength() );
	// pDC->LPtoDP( &tstrsz );

	pDC->TextOut( 
		xborder - XSpace - tstrsz.cx, 
		charHeight + YSpace , //-(tstrsz.cy/2), 
		tStr
	);


	pDC->MoveTo(xborder, charHeight + YSpace + yinc );
	pDC->LineTo(xborder - XSpace, charHeight + YSpace + yinc );

    pDC->SelectObject(&dPen);
	pDC->MoveTo(xborder + m_LineWidth, charHeight + YSpace + yinc );
	pDC->LineTo(x - XSpace - m_LineWidth, charHeight + YSpace + yinc );
    pDC->SelectObject(&nPen);

	tStr = ".75";
	tstrsz = pDC->GetTextExtent( tStr, tStr.GetLength() );
	// pDC->LPtoDP( &tstrsz );


	pDC->TextOut( 
		xborder - XSpace - tstrsz.cx, 
		charHeight + YSpace + yinc -(tstrsz.cy/2),  
		tStr 
	);

	pDC->MoveTo(xborder, charHeight + YSpace + (yinc*2) );
	pDC->LineTo(xborder - XSpace, charHeight + YSpace + (yinc*2) );

    pDC->SelectObject(&dPen);
	pDC->MoveTo(xborder + m_LineWidth, charHeight + YSpace + (yinc*2) );
	pDC->LineTo(x - XSpace - m_LineWidth, charHeight + YSpace + (yinc*2) );
    pDC->SelectObject(&nPen);

	tStr = ".50";
	tstrsz = pDC->GetTextExtent( tStr, tStr.GetLength() );
	// pDC->LPtoDP( &tstrsz );

	pDC->TextOut( 
		xborder - XSpace - tstrsz.cx, 
		charHeight + YSpace + (yinc*2) -(tstrsz.cy/2),  
		tStr 
	);

	pDC->MoveTo(xborder, charHeight + YSpace + (yinc*3) );
	pDC->LineTo(xborder - XSpace, charHeight + YSpace + (yinc*3) );

    pDC->SelectObject(&dPen);
	pDC->MoveTo(xborder + m_LineWidth, charHeight + YSpace + (yinc*3) );
	pDC->LineTo(x - XSpace - m_LineWidth, charHeight + YSpace + (yinc*3) );
    pDC->SelectObject(&nPen);

	tStr = ".25";
	tstrsz = pDC->GetTextExtent( tStr, tStr.GetLength() );
	// pDC->LPtoDP( &tstrsz );

	pDC->TextOut( 
		xborder - XSpace - tstrsz.cx, 
		charHeight + YSpace + (yinc*3) -(tstrsz.cy/2),  
		tStr 
	);

	pDC->MoveTo(xborder, y - yborder );
	pDC->LineTo(xborder - XSpace, y - yborder );

	tStr = "0.0";
	tstrsz = pDC->GetTextExtent( tStr, tStr.GetLength() );
	// pDC->LPtoDP( &tstrsz );

	pDC->TextOut( 
		xborder - XSpace - tstrsz.cx, 
		y - yborder -(tstrsz.cy),  
		tStr 
	);

	// Go no further if no data ...
	if ( m_ScoreCount1 == 0 && m_ScoreCount2 == 0  ) return;

	double dblMinScale = -1000000000000.0, dblMaxScale = 1000000000000.0;

	if ( m_ScoreCount1 != 0  ) {
		dblMinScale = m_ScoreArray1[0];
		dblMaxScale = m_ScoreArray1[m_ScoreCount1-1];
	}

	if ( m_ScoreCount2 != 0  ) {

		if ( m_ScoreArray2[0] < dblMinScale ) dblMinScale = m_ScoreArray2[0];

		if ( m_ScoreArray2[m_ScoreCount2 - 1] > dblMaxScale ) dblMaxScale = m_ScoreArray2[m_ScoreCount2 - 1];

	}


	dblMaxScale = (((int)(dblMaxScale / m_RoundingFactor))+1) * m_RoundingFactor;

	dblMinScale = (((int)((dblMinScale-0.5) / m_RoundingFactor))) * m_RoundingFactor;

	double dblRangeScale = dblMaxScale - dblMinScale;

	double dblXMin = dblMinScale;
	double dblXMult = (double)(x - xborder - XSpace) / dblRangeScale;

	int count = (int)((dblMaxScale - dblMinScale) / m_RoundingFactor);
	int everyother = 1;

	while ( count > 30 ) {
		count/= 2;
		everyother*=2;
	}

	int drawn = 0;
	int tother = 0;
	// Do X Axis Scale Ticks
	for ( int Step = (int)dblMinScale; Step <= (int)dblMaxScale; Step+=(int)m_RoundingFactor) {

		if ( tother%everyother == 0 ) {
			double dblXVal = Step;

			dblXVal -= dblXMin;
			dblXVal *= dblXMult;

			pDC->MoveTo((int)dblXVal + xborder,y - yborder);
			pDC->LineTo((int)dblXVal + xborder,y - yborder + YSpace);

			drawn++;
		}

		tother++;
	}


	count = (int)((dblMaxScale - dblMinScale) / m_RoundingFactor);
	everyother = 1;

	while ( count > 10 ) {
		count/= 2;
		everyother*=2;
	}

	drawn = 0;
	tother = 0;
	for (int Step = (int)dblMinScale; Step <= (int)dblMaxScale;Step += (int)m_RoundingFactor) {

		if ( tother%everyother == 0 ) {
			double dblXVal = Step;
			char tBuff[128];

			sprintf ( tBuff, "%d", Step );
			int buflen = strlen(tBuff);
			tstrsz = pDC->GetTextExtent( tBuff, strlen(tBuff) );
			// pDC->LPtoDP(&tstrsz);

			dblXVal -= dblXMin;
			dblXVal *= dblXMult;

			if ( drawn == 0 ) {
				pDC->TextOut( (int)dblXVal + xborder , y - yborder + 5, tBuff, buflen );
			} else if ( drawn == count) {
				pDC->TextOut( (int)dblXVal + xborder - (tstrsz.cx), y - yborder + 5, tBuff, buflen );
			} else {
				pDC->TextOut( (int)dblXVal + xborder - (tstrsz.cx/2), y - yborder + 5, tBuff, buflen );
			}

			if ( ((int)dblXVal != 0) && ((int)dblXVal != (x - XSpace - xborder)) ) {
				pDC->SelectObject(&dPen);
				pDC->MoveTo((int)dblXVal + xborder,y - yborder);
				pDC->LineTo((int)dblXVal + xborder, charHeight + YSpace );
				pDC->SelectObject(&nPen);
			}
			drawn++;
		}

		tother++;
	}


	double dblYMult = (double)y - (yborder + charHeight + YSpace);

	double dblXVal = m_ScoreArray1[0];
	dblXVal -= dblXMin;
	dblXVal *= dblXMult;

	double dblYVal;

	dblYVal = m_FracArray1[0];
	dblYVal *= dblYMult;

	// Create a red pen.
	pDC->SelectObject( oPen );
	nPen.DeleteObject();
	nPen.CreatePen( PS_SOLID, m_LineWidth, RGB(255,0,0) );
    oPen = pDC->SelectObject(&nPen);


	pDC->MoveTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1 );

	for ( int i=0; i < m_ScoreCount1; ++i ) {
		
		// and over
		
		dblXVal = m_ScoreArray1[i];

		dblXVal -= dblXMin;
		dblXVal *= dblXMult;

		pDC->LineTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1);

		// up
		dblYVal = m_FracArray1[i];

		dblYVal *= dblYMult;

		pDC->LineTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1 );

	}


	pDC->SelectObject( oPen );
	nPen.DeleteObject();

	if ( m_ScoreCount1 != 0 && m_ScoreCount2 != 0 ) {

		nPen.CreatePen( PS_SOLID, m_LineWidth, RGB(0,0,255) );
		oPen = pDC->SelectObject(&nPen);

		dblXVal = m_ScoreArray2[0];
		dblXVal -= dblXMin;
		dblXVal *= dblXMult;

		dblYVal = m_FracArray2[0];
		dblYVal *= dblYMult;

		pDC->MoveTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1 );
		int i;
		for ( i=0; i < m_ScoreCount2; ++i ) {
			
			// and over
			
			dblXVal = m_ScoreArray2[i];

			dblXVal -= dblXMin;
			dblXVal *= dblXMult;

			pDC->LineTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1);

			// up 
			dblYVal = m_FracArray2[i];
			dblYVal *= dblYMult;

			pDC->LineTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1);

		}

		pDC->SelectObject( oPen );
		nPen.DeleteObject();


		// Calc and Plot DStat Line
		nPen.CreatePen( PS_SOLID, m_LineWidth, RGB(0,0,0) );
		oPen = pDC->SelectObject(&nPen);

		if ( m_where1 != -1 && m_where2 != -1 ) {

			double Data1 = m_ScoreArray1[m_where1];
			double Data2 = m_ScoreArray2[m_where2];

			if ( Data1 == Data2 ) {

				dblXVal = m_ScoreArray1[m_where1];
				dblYVal = m_FracArray1[m_where1];

			} else if ( Data1 < Data2 ) {

				dblXVal = m_ScoreArray2[m_where2];
				dblYVal = m_FracArray1[m_where1];

			} else if ( Data2 < Data1 ) {

				dblXVal = m_ScoreArray1[m_where1];
				dblYVal = m_FracArray1[m_where1];

			}

			dblXVal -= dblXMin;
			dblXVal *= dblXMult;

			dblYVal *= dblYMult;

			pDC->MoveTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1 );

			if ( Data1 == Data2 ) {

				dblXVal = m_ScoreArray2[m_where2];
				dblYVal = m_FracArray2[m_where2];

			} else if ( Data1 < Data2 ) {

				dblXVal = m_ScoreArray2[m_where2];
				dblYVal = m_FracArray2[m_where2];

			} else if ( Data2 < Data1 ) {

				dblXVal = m_ScoreArray1[m_where1];
				dblYVal = m_FracArray2[m_where2];

			}
			
			dblXVal -= dblXMin;
			dblXVal *= dblXMult;

			dblYVal *= dblYMult;

			pDC->LineTo( (int)dblXVal + xborder, y - yborder - (int)dblYVal - 1);

		}

		// Do not forget to clean up.
		pDC->SelectObject( oPen );
		nPen.DeleteObject();


		sprintf( buff, "DStat = %G", m_DStat );

		pDC->SetTextColor( RGB(255,0,0) );
		pDC->TextOut( 
			(int)((double)x * m_xDStatPct), 
			(int)((double)y * m_yDStatPct),  
			buff, strlen(buff) 
		);

		sprintf( buff, "KSpr = %G", m_KSpr );

		pDC->TextOut( 
			(int)((double)x * m_xKSprPct), 
			(int)((double)y * m_yKSprPct),  
			buff, strlen(buff) 
		);
	}

	pDC->SetTextColor( RGB(0,0,0) );
	pDC->TextOut( 
		(int)((double)x * m_xXAxTPct), 
		y - charHeight, 
		m_XAxisTitle 
	);

	CSize tExt(0,0);
	tExt += pDC->GetTextExtent( m_XAxisTitle, m_XAxisTitle.GetLength()  );

	pDC->TextOut( 
		(int)((double)x * m_xXAxTPct) + tExt.cx, 
		y - charHeight, 
		m_NameSet1 
	);

	pDC->SetTextColor( RGB(255,0,0) );
	pDC->TextOut( 
		(int)((double)x * m_xXAxTPct) + tExt.cx, 
		y - charHeight, 
		m_NameSet1 
	);
	tExt += pDC->GetTextExtent( m_NameSet1, m_NameSet1.GetLength()  );

	if ( m_NameSet2.GetLength() ) {
		pDC->SetTextColor( RGB(0,0,0) );
		pDC->TextOut( 
			(int)((double)x * m_xXAxTPct) + tExt.cx, 
			y - charHeight, 
			" / " 
		);
		tExt += pDC->GetTextExtent( " / ", 3 );

		pDC->SetTextColor( RGB(0,0,255) );
		pDC->TextOut( 
			(int)((double)x * m_xXAxTPct) + tExt.cx, 
			y - charHeight, 
			m_NameSet2 
		);
	}

	pDC->SetTextColor( RGB(0,0,0) );

	pDC->SelectObject( pOldFont );
	fontTmp.DeleteObject();
	pOldFont = SelectDocFont(pDC, fontTmp, 900);

	pDC->TextOut( 2, (int)((double)y * m_yYAxTPct), m_YAxisTitle );

	pDC->SelectObject( pOldFont );

}


CFont* CDStatObject::SelectDocFont(CDC* pDC, CFont& font, int Escapement )
{
	// convert points in m_logfont.lfHeight to device
	LOGFONT logfont = m_logFont;
	logfont.lfHeight = -::MulDiv(-logfont.lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);

	// converts device to logical
//	CSize tSize( 10, logfont.lfHeight );
//	pDC->DPtoLP( &tSize );
//	logfont.lfHeight = -tSize.cy;
//	logfont.lfHeight = -tSize.cy;

	logfont.lfEscapement = Escapement;

	// set the text color as appropriate
	/*
	COLORREF cr = m_crText;
	if (cr == COLOR_WINDOW+1)
		cr = GetSysColor(COLOR_WINDOW);
	pDC->SetTextColor(m_crText);
	*/

	// create the font object
	if (!font.CreateFontIndirect(&logfont))
		return NULL;

	// select the font
	return pDC->SelectObject(&font);

	// NotifyChanged();
}



CDStatObject::CDStatObject()
{
	// TODO: add one-time construction code here
	m_ScoreArray1 = NULL;
	m_ScoreArray2 = NULL;

	m_FracArray1 = NULL;
	m_FracArray2 = NULL;

	m_ScoreCount1 = 0;
	m_ScoreCount2 = 0;

	m_TSide = 1;	// max someshit

	m_PageWidth = 500;
	m_PageHeight = 500;
	//

	m_xBorderPct = .10;
	m_yBorderPct = .10;

	m_xDStatPct = .16;
	m_yDStatPct = .10;

	m_xKSprPct = .16;
	m_yKSprPct = .06;

	m_ChartTitle = "Kolmogorov-Smirnov analysis of a pair of distributions";
	m_xChtTitPct = .15;

	m_yYAxTPct = .85;
	m_YAxisTitle = "Fraction of Scores as low or lower than the score being plotted";

	m_XAxisTitle = "Scores";
	m_xXAxTPct = .45;

	m_NameSet1 = "Within";
	m_NameSet2 = "Between";

	m_LineWidth = 2;

	m_RoundingFactor = 100.0;

	// determine default font for document
	memset(&m_logFont, 0, sizeof m_logFont);
	m_logFont.lfHeight = -10;
	lstrcpy(m_logFont.lfFaceName, _T("Arial"));

}

CDStatObject::~CDStatObject()
{
	DeleteContents();
}


void CDStatObject::DeleteContents()
{
	DeleteSet1();
	DeleteSet2();
}

void CDStatObject::DeleteSet1()
{
	if ( m_ScoreArray1 != NULL ) {
		delete m_ScoreArray1;
		m_ScoreArray1 = NULL;
	}

	if ( m_FracArray1 != NULL ) {
		delete m_FracArray1;
		m_FracArray1 = NULL;
	}
	m_ScoreCount1 = 0;
}

void CDStatObject::DeleteSet2()
{
	if ( m_ScoreArray2 != NULL ) {
		delete m_ScoreArray2;
		m_ScoreArray2 = NULL;
	}

	if ( m_FracArray2 != NULL ) {
		delete m_FracArray2;
		m_FracArray2 = NULL;
	}
	m_ScoreCount2 = 0;
}

void CDStatObject::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// CDStatObject diagnostics

#ifdef _DEBUG
void CDStatObject::AssertValid() const
{
	CObject::AssertValid();
}

void CDStatObject::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDStatObject commands

void CDStatObject::MyOpenDocumentFile(CStdioFile& iFile) 
{
#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif

	float Float;
	CPtrArray ScAr1, ScAr2;

	CString Buff;

	int count1 = 0, count2 = 0;

	while ( 1 ) { 
		
		Buff.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( iFile.ReadString( rbuff, 1024 ) == NULL ) break;
		Buff = rbuff;
#else
		if ( !iFile.ReadString( Buff ) ) break;
#endif

		if ( strpbrk( (const char *)Buff, "Xx" ) ) break;		// goto next file array ..
		
		int ret = sscanf( (const char *)Buff, "%G", &Float );

		if ( ret == 1 ) {

			float * pfl = new float;
			*pfl = Float;
			ScAr1.Add( pfl );

			count1++;
		}

	}


	while ( 1 ) { 
		
		Buff.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( iFile.ReadString( rbuff, 1024 ) == NULL ) break;
		Buff = rbuff;
#else
		if ( !iFile.ReadString( Buff ) ) break;
#endif

		if ( strpbrk( (const char *)Buff, "Xx" ) ) break;		// goto next file array ..
		
		int ret = sscanf( (const char *)Buff, "%G", &Float );

		if ( ret == 1 ) {

			float * pfl = new float;
			*pfl = Float;
			ScAr2.Add( pfl );

			count2++;

		}

	}

	if ( count1 == 0 || count2 == 0 ) {
		for ( int i = 0; i < count1; ++i ) {
			float *pfl = (float *)(ScAr1[i]);
			delete pfl;
		}
		
		ScAr1.RemoveAll();
		for (int i = 0; i < count2; ++i ) {
			float *pfl = (float *)(ScAr2[i]);
			delete pfl;
		}
		ScAr2.RemoveAll();
		return;
	}

	DeleteSet1();
	DeleteSet2();
	m_ScoreArray1 = new double[count1];
	m_ScoreArray2 = new double[count2];
	m_ScoreCount1 = count1;
	m_ScoreCount2 = count2;


	for ( int i = 0; i < count1; ++i ) {
		float *pfl = (float *)(ScAr1[i]);
		m_ScoreArray1[i] = (double)*pfl;
		delete pfl;
	}

	ScAr1.RemoveAll();
	
	for (int i = 0; i < count2; ++i ) {
		float *pfl = (float *)(ScAr2[i]);
		m_ScoreArray2[i] = (double)*pfl;
		delete pfl;
	}

	ScAr2.RemoveAll();

	MyDocDStat();

	return;
}


void CDStatObject::MyOpenDocumentFileSet1(CStdioFile& iFile) 
{
#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif
	float Float;
	CPtrArray ScAr1;

	CString Buff;

	int count1 = 0;

	while ( 1 ) { 
		
		Buff.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( iFile.ReadString( rbuff, 1024 ) == NULL ) break;
		Buff = rbuff;
#else
		if ( !iFile.ReadString( Buff ) ) break;
#endif

		int ret = sscanf( (const char *)Buff, "%G", &Float );

		if ( ret == 1 ) {

			float * pfl = new float;
			*pfl = Float;
			ScAr1.Add( pfl );

			count1++;
		}

	}


	if ( count1 == 0  ) {
		for ( int i = 0; i < count1; ++i ) {
			float *pfl = (float *)(ScAr1[i]);
			delete pfl;
		}
		
		ScAr1.RemoveAll();
		return;
	}
	
	DeleteSet1();
	m_ScoreArray1 = new double[count1];
	m_ScoreCount1 = count1;


	for ( int i = 0; i < count1; ++i ) {
		float *pfl = (float *)(ScAr1[i]);
		m_ScoreArray1[i] = (double)*pfl;
		delete pfl;
	}

	ScAr1.RemoveAll();
	
	MyDocDStat();

	return;
}



void CDStatObject::MyOpenDocumentFileSet2(CStdioFile& iFile) 
{
#if !defined(_WIN32) || _MSC_VER < 999
	char rbuff[1024];
#endif
	float Float;
	CPtrArray ScAr2;

	CString Buff;

	int count2 = 0;

	while ( 1 ) { 
		
		Buff.Empty();

#if !defined(_WIN32) || _MSC_VER < 999
		if ( iFile.ReadString( rbuff, 1024 ) == NULL ) break;
		Buff = rbuff;
#else
		if ( !iFile.ReadString( Buff ) ) break;
#endif

		int ret = sscanf( (const char *)Buff, "%G", &Float );

		if ( ret == 1 ) {

			float * pfl = new float;
			*pfl = Float;
			ScAr2.Add( pfl );

			count2++;

		}

	}

	if ( count2 == 0 ) {
		for ( int i = 0; i < count2; ++i ) {
			float *pfl = (float *)(ScAr2[i]);
			delete pfl;
		}
		ScAr2.RemoveAll();
		return;
	}
	
	DeleteSet2();
	m_ScoreArray2 = new double[count2];
	m_ScoreCount2 = count2;

	for ( int i = 0; i < count2; ++i ) {
		float *pfl = (float *)(ScAr2[i]);
		m_ScoreArray2[i] = (double)*pfl;
		delete pfl;
	}

	ScAr2.RemoveAll();

	MyDocDStat();

	return;
}

void CDStatObject::OnGraphsetup()
{
	// TODO: Add your command handler code here

	CGraphSetup tDlg;

	tDlg.m_PageWidth = (float)m_PageWidth / (float)100.0;
	tDlg.m_PageHeight = (float)m_PageHeight / (float)100.0;

	tDlg.m_logFont = m_logFont;

	tDlg.m_Set1Count = m_ScoreCount1;
	tDlg.m_Set2Count = m_ScoreCount2;

	tDlg.m_TSide = m_TSide;

	tDlg.m_xBorderPct = (int)(m_xBorderPct*100.0);
	tDlg.m_yBorderPct = (int)(m_yBorderPct*100.0);
	tDlg.m_xDStatPct = (int)(m_xDStatPct*100.0);
	tDlg.m_yDStatPct = (int)(m_yDStatPct*100.0);
	tDlg.m_xKSprPct = (int)(m_xKSprPct*100.0);
	tDlg.m_yKSprPct = (int)(m_yKSprPct*100.0);
	tDlg.m_ChartTitle = m_ChartTitle;
	tDlg.m_xChtTitPct = (int)(m_xChtTitPct*100.0);
	tDlg.m_yYAxTPct = (int)(m_yYAxTPct*100.0);
	tDlg.m_YAxisTitle = m_YAxisTitle;
	tDlg.m_XAxisTitle = m_XAxisTitle;
	tDlg.m_xXAxTPct = (int)(m_xXAxTPct*100.0);
	tDlg.m_LineWidth = m_LineWidth;
	tDlg.m_RoundingFactor = m_RoundingFactor;

	if ( tDlg.DoModal() != IDOK ) return;

	m_TSide = tDlg.m_TSide;
	m_PageWidth = (int)(tDlg.m_PageWidth*100);
	m_PageHeight = (int)(tDlg.m_PageHeight*100);

	m_logFont = tDlg.m_logFont;

	m_xBorderPct = (double)tDlg.m_xBorderPct/100.0;
	m_yBorderPct = (double)tDlg.m_yBorderPct/100.0;
	m_xDStatPct = (double)tDlg.m_xDStatPct/100.0;
	m_yDStatPct = (double)tDlg.m_yDStatPct/100.0;
	m_xKSprPct = (double)tDlg.m_xKSprPct/100.0;
	m_yKSprPct = (double)tDlg.m_yKSprPct/100.0;
	m_ChartTitle = tDlg.m_ChartTitle;
	m_xChtTitPct = (double)tDlg.m_xChtTitPct/100.0;
	m_yYAxTPct = (double)tDlg.m_yYAxTPct/100.0;
	m_YAxisTitle = tDlg.m_YAxisTitle;
	m_XAxisTitle = tDlg.m_XAxisTitle;
	m_xXAxTPct = (double)tDlg.m_xXAxTPct/100.0;
	m_LineWidth = tDlg.m_LineWidth;
	m_RoundingFactor = tDlg.m_RoundingFactor;

	ReCalcDStat();

}


void CDStatObject::OnWriteoutput(const CString& PathName ) 
{
	// TODO: Add your command handler code here
	// CDocument

TRY {

	CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	double Score1 = 0.0;
	double Frac1 = 0.0;
	double Score2 = 0.0;
	double Frac2 = 0.0;
	double *ScoreArray1 = NULL;
	double *FracArray1 = NULL;
	double *ScoreArray2 = NULL;
	double *FracArray2 = NULL;

	int ScoreCount1 = m_ScoreCount1;

	if ( m_ScoreCount1 ) {

		ScoreArray1 = new double[m_ScoreCount1];
		memcpy ( ScoreArray1, m_ScoreArray1, sizeof(double)*m_ScoreCount1 );

		FracArray1 = new double[m_ScoreCount1];
		memcpy ( FracArray1, m_FracArray1, sizeof(double)*m_ScoreCount1 );

		ScoreCount1 = PakDat( m_ScoreCount1, ScoreArray1, FracArray1 );
	
		Score1 = ScoreArray1[0];

	}

	int ScoreCount2 = m_ScoreCount2;
	
	if ( m_ScoreCount2 ) {

		ScoreArray2 = new double[m_ScoreCount2];
		memcpy ( ScoreArray2, m_ScoreArray2, sizeof(double)*m_ScoreCount2 );

		FracArray2 = new double[m_ScoreCount2];
		memcpy ( FracArray2, m_FracArray2, sizeof(double)*m_ScoreCount2 );

		ScoreCount2 = PakDat( m_ScoreCount2, ScoreArray2, FracArray2 );

		Score2 = ScoreArray2[0];
	}


	int count;

	if ( ScoreCount1 > ScoreCount2 ) count = ScoreCount1;
	else count = ScoreCount2;

	char outBuff[256];


	for ( int i=0; i < count; ++i ) {
		outBuff[0] = 0;
		if ( i < ScoreCount1 && i < ScoreCount2 ) {
			sprintf(outBuff, "%12f,%12f,%12f,%12f\n", 
				Score1, 
				Frac1, 
				Score2, 
				Frac2
			);
			oFile.WriteString( outBuff );
			Frac1 = FracArray1[i];
			Frac2 = FracArray2[i];
			sprintf(outBuff, "%12f,%12f,%12f,%12f\n", 
				Score1, 
				Frac1, 
				Score2, 
				Frac2
			);
		} else if ( i < ScoreCount1 && i >= ScoreCount2 ) {
			sprintf(outBuff, "%12f,%12f,            ,            \n", 
				Score1, 
				Frac1
			);
			oFile.WriteString( outBuff );
			Frac1 = FracArray1[i];
//			Frac2 = FracArray2[i];
			sprintf(outBuff, "%12f,%12f,            ,            \n", 
				Score1, 
				Frac1
			);
		} else if ( i >= ScoreCount1 && i < ScoreCount2 ) {
			sprintf(outBuff, "            ,            ,%12f,%12f\n", 
				Score2, 
				Frac2
			);
			oFile.WriteString(outBuff );
//			Frac1 = FracArray1[i];
			Frac2 = FracArray2[i];
			sprintf(outBuff, "            ,            ,%12f,%12f\n", 
				Score2, 
				Frac2
			);
		}
		oFile.WriteString(outBuff );
		if ( i+1 < ScoreCount1 ) Score1 = ScoreArray1[i+1];
		if ( i+1 < ScoreCount2 ) Score2 = ScoreArray2[i+1];

	}

	oFile.Close();
	
	if ( ScoreArray1 != NULL ) delete ScoreArray1;
	if ( FracArray1 != NULL ) delete FracArray1;
	if ( ScoreArray2 != NULL ) delete ScoreArray2;
	if ( FracArray2 != NULL ) delete FracArray2;

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}


void CDStatObject::WriteData(const CString& PathName ) 
{
TRY {

	CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	
	char outBuff[1024];

	sprintf(outBuff, "%s Scores\n", (const char *)m_NameSet1 );
	oFile.WriteString(outBuff);

	for ( int i=0; i < m_ScoreCount1; ++i ) {
		sprintf(outBuff, "%12f\n", m_ScoreArray1[i] );
		oFile.WriteString(outBuff);
	}

	sprintf(outBuff, "XXX\n %s Scores\n", (const char *)m_NameSet2 );
	oFile.WriteString(outBuff);

	for (int i=0; i < m_ScoreCount2; ++i ) {
		sprintf(outBuff, "%12f\n", m_ScoreArray2[i] );
		oFile.WriteString(outBuff);
	}

	sprintf(outBuff, "\n" );
	oFile.WriteString(outBuff);

	oFile.Close();

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}

void CDStatObject::OnDatafile(const CString& PathName ) 
{
TRY {

	CStdioFile iFile( PathName, CFile::modeRead | CFile::typeText );

	MyOpenDocumentFile(iFile);

	iFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}

void CDStatObject::OnSet1(const CString& PathName ) 
{
TRY {

	CStdioFile iFile( PathName, CFile::modeRead | CFile::typeText );

	MyOpenDocumentFileSet1(iFile);

	iFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}

void CDStatObject::OnSet2(const CString& PathName ) 
{
TRY {

	CStdioFile iFile( PathName, CFile::modeRead | CFile::typeText );

	MyOpenDocumentFileSet2(iFile);

	iFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}


void
CDStatObject::MyAveVar( double *pDbl, int count, double* pAve, double *pVar )
{
	double ave = 0.0;

	if ( count > 0 ) {
		int ctr = count;
		while (ctr--) {
			ave += pDbl[ctr];
		}
		ave = ave / count;
	}

	double var = 0.0;

	if ( count > 1 ) {
		int ctr = count;
		while (ctr--) {
			double tvar = (pDbl[ctr] - ave);
			var += (tvar * tvar);
		}
		var /= count - 1;
	}

	*pAve = ave;

	*pVar = var;
}


BOOL
CDStatObject::MyDocDStat()
{
	
	if ( m_ScoreCount1 != 0 && m_ScoreCount2 == 0  ) {

		HeapSort( m_ScoreArray1, m_ScoreCount1 );

		m_ScoreCount1++;
		double *tarr = new double[m_ScoreCount1];
		tarr[0] = m_ScoreArray1[0];
		for ( int i=1; i < m_ScoreCount1; ++i ) {
			tarr[i] = m_ScoreArray1[i-1];
		}
		delete m_ScoreArray1;
		m_ScoreArray1 = tarr;

		if ( m_FracArray1 == NULL )
			m_FracArray1 = new double[m_ScoreCount1];

		for (int i=0; i < m_ScoreCount1; ++i ) {
			if ( i == 0 ) 
				m_FracArray1[i] = 0.0;
			else 
				m_FracArray1[i] = (double)(i+1) / (double)m_ScoreCount1;
		}

		return TRUE;
	}

	if ( m_ScoreCount1 ==0 || m_ScoreCount2 == 0 ) {
		return FALSE;
	}

	HeapSort( m_ScoreArray1, m_ScoreCount1 );

	HeapSort( m_ScoreArray2, m_ScoreCount2 );

	m_ScoreCount1++;
	m_ScoreCount2++;
	double *tarr = new double[m_ScoreCount1];
	tarr[0] = m_ScoreArray1[0];
//	tarr[0] = 0.0;
	for ( int i=1; i < m_ScoreCount1; ++i ) {
		tarr[i] = m_ScoreArray1[i-1];
	}
	delete m_ScoreArray1;
	m_ScoreArray1 = tarr;
	m_ScoreArray1[0] = m_ScoreArray1[1];

	tarr = new double[m_ScoreCount2];
	tarr[0] = m_ScoreArray2[0];
//	tarr[0] = 0.0;
	for (int i=1; i < m_ScoreCount2; ++i ) {
		tarr[i] = m_ScoreArray2[i-1];
	}
	delete m_ScoreArray2;
	m_ScoreArray2 = tarr;

	if ( m_FracArray1 != NULL )
		delete m_FracArray1;
	m_FracArray1 = new double[m_ScoreCount1];

	if ( m_FracArray2 != NULL )
		delete m_FracArray2;
	m_FracArray2 = new double[m_ScoreCount2];

	m_FracArray1[0] = 0.0;
	for (int i=0; i < m_ScoreCount1 - 1; ++i ) {
		m_FracArray1[i+1] = (double)(i+1) / (double)(m_ScoreCount1-1);
	}

	m_FracArray2[0] = 0.0;
	for (int i=0; i < m_ScoreCount2 - 1; ++i ) {
		m_FracArray2[i+1] = (double)(i+1) / (double)(m_ScoreCount2-1);
	}

	ReCalcDStat();

	return TRUE;
}

void
CDStatObject::ReCalcDStat()
{
	double Ave1, Var1, Ave2, Var2;

//	m_ScoreCount1 = PakDat( m_ScoreCount1, m_ScoreArray1, m_FracArray1 );
//	m_ScoreCount2 = PakDat( m_ScoreCount2, m_ScoreArray2, m_FracArray2 );

	MyAveVar( m_ScoreArray1, m_ScoreCount1, &Ave1, &Var1 );

	MyAveVar( m_ScoreArray2, m_ScoreCount2, &Ave2, &Var2 );

	MyDocKS2( &m_DStat, &m_KSpr, &m_where1, &m_where2, &m_DWhich );
}

int
CDStatObject::PakDat( int Points, double *ScoreArray, double *FracArray )
{
	int next, prev, knt;

	next = 0;
	prev = 0;

	for ( knt = 1; knt < Points; knt++ ) {
		if ( ScoreArray[knt] - ScoreArray[prev] < 0.000005 ) {
		} else {
			next++;
			if ( next < knt) {
               ScoreArray[next] = ScoreArray[knt];
               FracArray[next] = FracArray[knt];
			}
            prev = knt;
		}
	}
	return next;
}

double
CDStatObject::KSProb( int Count1, int Count2, double dstat )
{
//
// ***  Significance Probabliity for Kolmogorov-Smirnov D statistic
//
//
	double Fn, alam;
//
	int j;
	double a2, fac, term, termbf, KSProb;
	double eps1 = 0.001, eps2 = 1.0E-8;
//
	Fn = sqrt( (double)Count1 * (double)Count2 / (double)(Count1 + Count2) );
	alam = dstat * ( Fn + 0.12 + 0.11 / Fn );
	a2 = -2.0 * (alam * alam);
//
	fac = 2.0;
	KSProb = 0.0;
	termbf = 0.0;
//
	for ( j = 0; j < 100; ++j ) {
		term = fac * exp( a2 * ((j + 1)*(j + 1)) );
		KSProb = KSProb + term;
		if ( (fabs(term) <= eps1*termbf) || (fabs(term) <= eps2*KSProb) ) return KSProb;
		fac = -fac;
		termbf = fabs( term );
	}

	KSProb = 1.0;
	return KSProb;
}

void
CDStatObject::MyDocKS2( double *DStat, double *KSpr, int *where1, int *where2, BOOL *DWhich )
{
	int j1, j2;
	double tdstat, tkspr;
	int pwhere1 = -1, pwhere2 = -1;
	int mwhere1 = -1, mwhere2 = -1;
	int twhere1, twhere2;
	BOOL tDWhich;

	double dplus, dminus, dstatp, dstatm;


	j1 = 0;
	j2 = 0;
	tdstat= 0.0;
	dstatp = 0.0;
	dstatm = 0.0;

	while ( j1 < m_ScoreCount1 && j2 < m_ScoreCount2 ) {
		if ( m_ScoreArray1[j1] == m_ScoreArray2[j2] ) {
			dplus = m_FracArray2[j2] - m_FracArray1[j1];
			dminus = -dplus;
			if ( dplus > dstatp ) {
				pwhere1 = j1;
				pwhere2 = j2;
				dstatp = dplus;
				tDWhich = TRUE;
				// Type *, ' tdstat Plus =', dstatp, j1, j2
			}
			if ( dminus > dstatm ) {
				mwhere1 = j1;
				mwhere2 = j2;
				dstatm = dminus;
				tDWhich = FALSE;
				//Type *, ' tdstat Minus =', dstatm, j1, j2
			}

			if ( j2 + 1 < m_ScoreCount2 && j1 + 1 < m_ScoreCount1) {
				if ( m_ScoreArray1[j1 + 1] < m_ScoreArray2[j2 + 1] ) {
		            j1 = j1 + 1;
				}
				else if ( m_ScoreArray2[j2 + 1] < m_ScoreArray1[j1 + 1] ) {
		            j2 = j2 + 1;
				}
				else {
					j1 = j1 + 1;
					j2 = j2 + 1;
				}
			}
			else {
				j1 = j1 + 1;
				j2 = j2 + 1;
			}
		}
		else if ( m_ScoreArray1[j1] < m_ScoreArray2[j2] ) {
			dplus = m_FracArray2[j2] - m_FracArray1[j1];
			dminus = -dplus;
			if ( dplus > dstatp ) {
				pwhere1 = j1;
				pwhere2 = j2;
				dstatp = dplus;
				tDWhich = TRUE;
				// Type *, ' tdstat Plus =', dstatp, j1, j2
			}
			if ( dminus > dstatm ) {
				mwhere1 = j1;
				mwhere2 = j2;
				dstatm = dminus;
				tDWhich = FALSE;
				// Type *, ' tdstat Minus =', dstatm, j1, j2
			}
			if ( j2 + 1 < m_ScoreCount2 && j1 + 1 < m_ScoreCount1) {
				if ( m_ScoreArray2[j2 + 1] < m_ScoreArray1[j1 + 1] ) {
					j2 = j2 + 1;
				}
				else 
					j1 = j1 + 1;
			}
			else
				j1 = j1 + 1;
		}
		else if ( m_ScoreArray2[j2] < m_ScoreArray1[j1] ) {
			dplus = m_FracArray2[j2] - m_FracArray1[j1];
			dminus = -dplus;
			if ( dplus > dstatp ) {
				pwhere1 = j1;
				pwhere2 = j2;
				dstatp = dplus;
				tDWhich = TRUE;
				// Type *, ' tdstat Plus =', dstatp, j1, j2
			}
            if ( dminus > dstatm ) {
				mwhere1 = j1;
				mwhere2 = j2;
				dstatm = dminus;
				tDWhich = FALSE;
				// Type *, ' tdstat Minus =', dstatm, j1, j2
			}
			if ( j2 + 1 < m_ScoreCount2 && j1 + 1 < m_ScoreCount1) {
				if ( m_ScoreArray1[j1 + 1] < m_ScoreArray2[j2 + 1] ) {
					j1 = j1 + 1;
				}
				else 
					j2 = j2 + 1;
			}
			else
				j2 = j2 + 1;
		}
		// goto label100;
	}

	if ( m_TSide == 0 ) {
		tdstat = dstatp;
		twhere1 = pwhere1;
		twhere2 = pwhere2;
		tkspr = KSProb( m_ScoreCount1, m_ScoreCount2, tdstat ) * 0.5;
		// Type *, ' Final dstat+=', dstat, twhere1, twhere2
	}
	else if ( m_TSide == 1 ) {
		tdstat = dstatm;
		twhere1 = mwhere1;
		twhere2 = mwhere2;
		tkspr = KSProb( m_ScoreCount1, m_ScoreCount2, tdstat ) * 0.5;
		// Type *, ' Final dstat-=', dstat, twhere1, twhere2
	}
	else if ( m_TSide == 2 ) {
		if ( dstatp > dstatm ) {
			tdstat = dstatp;
			twhere1 = pwhere1;
			twhere2 = pwhere2;
		} else {
			tdstat = dstatm;
			twhere1 = mwhere1;
			twhere2 = mwhere2;
		}
		tkspr = KSProb( m_ScoreCount1, m_ScoreCount2, tdstat );
		// Type *, ' Final tdstat =', dstat, twhere1, twhere2
	}

	*DStat = tdstat;
	*KSpr = tkspr;
	*where1 = twhere1;
	*where2 = twhere2;
	*DWhich = tDWhich;

}

