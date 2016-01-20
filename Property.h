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

#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED


#define MAXPROPERTYGROUP 20


typedef struct {
	int RowNum;
	char Group[MAXPROPERTYGROUP + 1];
	COLORREF TextColor;
	COLORREF BkColor;
} PropertyStruct;

void SetPropertyArray(CPtrArray *fPropertyArray, CPtrArray *tPropertyArray );
void SetPropertyDefault(CPtrArray *PropertyArray, int PropertyLevel, int ProjectType );


class CProperty: public CObject {

private:


	CPtrArray	m_PropertyArray[3];		// Holding the Level 1, 2, and 3 PropertyStructs

public:

	CProperty();

	~CProperty();
	void ClearArray();

	DECLARE_DYNCREATE(CProperty)

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void CopyVars( CProperty& nProperty );
	CPtrArray* GetArray(int p) { ASSERT(p<4);return &m_PropertyArray[p]; }
	
	PropertyStruct *GetPropertyStruct(int p, int i)
	{
		ASSERT(p<4);
		return (PropertyStruct *)m_PropertyArray[p][i]; 
	}


};

#endif
