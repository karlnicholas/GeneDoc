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

class CPhyloGenBase: public CObject
{
protected:
	
public:

	CPhyloGenBase*	m_pPGParent;
	int m_Depth;
	int m_DrawType;	// What was this node last draw as?
	CRect m_ClientRect;
	int m_Selected;
	int m_FirstSelection;
	int m_Number;

	char m_cAncestry;
	char m_pPrevResidue;
	unsigned m_AverageCost;

	CString m_Weight;


	void *m_pTSW;

//
	CPhyloGenBase() { 
		m_pPGParent = NULL;
	}

	virtual ~CPhyloGenBase() {}
//

	virtual void WriteString( CString& ParseString ) = 0;
	virtual int CheckCounts(int ErrMsg) = 0;
	virtual void SetDepth(int Depth) = 0;
	virtual int DetermineDraw( CPhyloGenBase * pPSBLast ) = 0;
	
	enum {
		DLABEL, 
		DNODESU, 
		DNODESL, 
		DNODEM, 
		DNODEEU, 
		DNODEEL, 
		DNOTHING, 
		DNODET, 
		DEXTEND,
		DNODER
	};

	virtual void CallFromSeq( CView* pView ) = 0;
	virtual void CallDocFromSeq( CDocument *pDoc ) = 0;
	virtual void CallDocFromDepth( CDocument *pDoc, int Depth ) = 0;
	virtual void CallSDFromNamedSeq( CDialog *pDlg, const CString& Name ) = 0;
	
};

