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
class CGeneSegBase: public CObject
{
protected:
//	int m_Selected;
public:

	CGeneSegBase*	pGeneSegParent;
	CPtrList		SegHeaderList;
	CPtrList		SegDataList;
//
	CGeneSegBase() { /* m_Selected = 0;*/  pGeneSegParent = NULL; }
	virtual ~CGeneSegBase() {}
//
//	virtual int	IsSelected() { return m_Selected; }
//	virtual void DeSelect() { m_Selected = 0; }
//	virtual void Select() { m_Selected = 1; }
//
};

