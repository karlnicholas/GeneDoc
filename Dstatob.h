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

void HeapSort( double *m_ScoreArray1, int m_ScoreCount1 );


class CDStatObject: public CObject {

private:

	// Graphing Vars

	double m_xBorderPct;
	double m_yBorderPct;

	double m_xDStatPct;
	double m_yDStatPct;

	double m_xKSprPct;
	double m_yKSprPct;

	CString m_ChartTitle;
	double m_xChtTitPct;

	double m_yYAxTPct;
	CString m_YAxisTitle;

	int m_LineWidth;

	LOGFONT m_logFont;

	int m_PageWidth;
	int m_PageHeight;

	// Data/Calc Vars
	double *m_FracArray1;
	double *m_FracArray2;
	int m_where1, m_where2;


	double m_DStat, m_KSpr;
	BOOL m_DWhich;

public:

	CDStatObject();

	DECLARE_DYNCREATE(CDStatObject)

	virtual ~CDStatObject();
	
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	double *m_ScoreArray1;
	double *m_ScoreArray2;
	int m_ScoreCount1;
	int m_ScoreCount2;

	double m_RoundingFactor;
	CString m_XAxisTitle;
	double m_xXAxTPct;
	int m_TSide;

	CString m_NameSet1;
	CString m_NameSet2;


	// GUI Subroutines
	CSize GetDocSize() { return CSize( m_PageWidth, m_PageHeight ); }
	void DoDraw(CDC *pDC );

	void OnDatafile( const CString& PathName );
	void OnSet1( const CString& PathName );
	void OnSet2( const CString& PathName );
	void OnGraphsetup();
	void OnWriteoutput( const CString& PathName );

	void DeleteContents();
	void DeleteSet1();
	void DeleteSet2();

	void SetTSide( int nTSide ) { m_TSide = nTSide; }
	int GetTSide() { return m_TSide; }

	BOOL MyDocDStat();

	void WriteData(const CString& PathName );

protected:

	void MyOpenDocumentFile(CStdioFile& iFile);
	void MyOpenDocumentFileSet1(CStdioFile& iFile);
	void MyOpenDocumentFileSet2(CStdioFile& iFile);

	CFont* SelectDocFont(CDC* pDC, CFont& font, int Escapement);

	// Data/Calc Subroutines

	void MyDocKS2( double *DStat, double *KSpr, int *where1, int *where2, BOOL* DWhich );

	void MyAveVar( double *pDbl, int count, double* pAve, double *pVar );
	double KSProb( int Count1, int Count2, double dstat );
	int PakDat( int Points, double *ScoreArray, double *FracArray );
	void ReCalcDStat();
};

