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
/////////////////////////////////////////////////////////////////////////////


class CMapDWORDToChar : public CObject
{

	DECLARE_DYNAMIC(CMapDWORDToChar)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		char value;
	};
public:

// Construction
	CMapDWORDToChar(int nBlockSize=10);

// Attributes
	// number of elements
//	int GetCount() const;
//	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(DWORD key, char& rValue) const;

// Operations
	// Lookup and add if not there
	char& operator[](DWORD key);

	// add a new (key, value) pair
//	void SetAt(DWORD key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
//	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, char& rValue) const;

	// advanced features for derived classes
//	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;



inline int GetCount() const 
	{ return m_nCount; }

inline BOOL IsEmpty() const 

	{ return m_nCount == 0; }

inline void SetAt(DWORD key, char newValue) 
	{ (*this)[key] = newValue; }

inline POSITION GetStartPosition() const 
	{ return (m_nCount == 0) ? NULL : (POSITION)-1L; }

inline UINT GetHashTableSize() const
	{ return m_nHashTableSize; }


// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CMyPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	~CMapDWORDToChar();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

