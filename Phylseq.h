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

class CPhyloSeq: public CPhyloGenBase 
{

	CGeneSegment *m_pSequence;


public:
        
	CPhyloSeq();
	DECLARE_DYNCREATE(CPhyloSeq)

	virtual ~CPhyloSeq();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void WriteString( CString& ParseString );
	int CheckCounts(int ErrMsg);
	void SetDepth( int Depth );
	int DetermineDraw ( CPhyloGenBase * pPNPLast );
	void CallFromSeq( CView *pView );
	void CallDocFromSeq( CDocument* pDoc );
	void CallDocFromDepth( CDocument* pDoc, int Depth );
	void CallSDFromNamedSeq( CDialog *pDlg, const CString& Name );
//
	void SetSequence( CGeneSegment *pSeq ) { m_pSequence = pSeq; }
	const CString& GetName() { return m_pSequence->GetTitle(); }
	GeneStor* GetGeneStor() { return m_pSequence->m_pMyGeneStor; }
//
};

