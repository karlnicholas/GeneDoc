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

class CGeneString: public CObject {

private:
	int	m_Selected;
	int m_enum;

	GeneStor *m_GString;
	CGeneSegment *pGeneSegment;
	DWORD m_SegStartPos;
	int m_SegSize;

	COLORREF *m_TextColor; 
	COLORREF *m_BackColor;

public:

	// Constructors
	CGeneString();
	DECLARE_DYNCREATE(CGeneString)

	virtual ~CGeneString();

	int SetString( 
		GeneStor  *pnString, 
		int nSize, 
		DWORD nStartPos, 
		CGeneSegment *pParent, 
		unsigned int eval
	);
	int SetNewString( GeneStor *pnString, int nSize );
	void SetShade( int Position, COLORREF TextColor, COLORREF BackColor );
	void SetComment( int Position, char nChar );
	void SetResidue( int Position, char nChar );
	void GetShade(int Position, COLORREF *TextColor, COLORREF *BackColor);
	void Select();
	void DeSelect();
	int IsSelected();
	
	int GetLength() { return m_SegSize; }
	int GetEnum() { return m_enum; }
	DWORD GetStartPos() { return m_SegStartPos; }
	CGeneSegment *GetGeneSegment() { return pGeneSegment; }
	operator const GeneStor *  () const { return m_GString; }
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	

};

