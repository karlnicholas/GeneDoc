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

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1993 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
//
// Implementation of parmeterized Map
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef AFX_COLL2_SEG
#pragma code_seg(AFX_COLL2_SEG)
#endif


IMPLEMENT_DYNAMIC(CMapDWORDToCPAIR, CObject)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

CMapDWORDToCPAIR::CMapDWORDToCPAIR(int nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_pHashTable = NULL;
	m_nHashTableSize = 17;  // default size
//	m_nHashTableSize = 37;  // default size
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}


inline UINT CMapDWORDToCPAIR::HashKey(DWORD key) const
{
	// default identity hash - works for most primitive values
	return *((UINT*)&((key))) >> 4;
//	return *((UINT*)&((key))) >> 5;
//	return _AFX_FP_OFF(key) >> 5;
}


void CMapDWORDToCPAIR::InitHashTable(UINT nHashSize)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{
	ASSERT_VALID(this);
	ASSERT(m_nCount == 0);
	ASSERT(nHashSize > 0);

	// free hash table
	delete[] m_pHashTable;
	m_pHashTable = NULL;

	m_pHashTable = new CAssoc* [nHashSize];
	memset(m_pHashTable, 0, sizeof(CAssoc*) * nHashSize);
	m_nHashTableSize = nHashSize;
}

void CMapDWORDToCPAIR::RemoveAll()
{
	ASSERT_VALID(this);



	// free hash table
	delete[] m_pHashTable;
	m_pHashTable = NULL;

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

CMapDWORDToCPAIR::~CMapDWORDToCPAIR()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Assoc helpers
// same as CList implementation except we store CAssoc's not CNode's
//    and CAssoc's are singly linked all the time

CMapDWORDToCPAIR::CAssoc* CMapDWORDToCPAIR::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		CMyPlex* newBlock = CMyPlex::Create(m_pBlocks, m_nBlockSize, sizeof(CMapDWORDToCPAIR::CAssoc));
		// chain them into free list
		CMapDWORDToCPAIR::CAssoc* pAssoc = (CMapDWORDToCPAIR::CAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	ASSERT(m_pFreeList != NULL);  // we must have something

	CMapDWORDToCPAIR::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);  // make sure we don't overflow
	memset(&pAssoc->key, 0, sizeof(DWORD));

	memset(&pAssoc->value, 0, sizeof(CPAIR));

	return pAssoc;
}

void CMapDWORDToCPAIR::FreeAssoc(CMapDWORDToCPAIR::CAssoc* pAssoc)
{

	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

CMapDWORDToCPAIR::CAssoc*
CMapDWORDToCPAIR::GetAssocAt(DWORD key, UINT& nHash) const
// find association (or return NULL)
{
	nHash = HashKey(key) % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	CAssoc* pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
			return pAssoc;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CMapDWORDToCPAIR::Lookup(DWORD key, CPAIR& rValue) const
{
	ASSERT_VALID(this);

	UINT nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
		return FALSE;  // not in map

	rValue = pAssoc->value;
	return TRUE;
}

CPAIR& CMapDWORDToCPAIR::operator[](DWORD key)
{
	ASSERT_VALID(this);

	UINT nHash;
	CAssoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		pAssoc->nHashValue = nHash;
		pAssoc->key = key;
		// 'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;  // return new reference
}


BOOL CMapDWORDToCPAIR::RemoveKey(DWORD key)
// remove key - return TRUE if removed
{
	ASSERT_VALID(this);

	if (m_pHashTable == NULL)
		return FALSE;  // nothing in the table

	CAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[HashKey(key) % m_nHashTableSize];

	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;  // not found
}


/////////////////////////////////////////////////////////////////////////////
// Iterating

void CMapDWORDToCPAIR::GetNextAssoc(POSITION& rNextPosition,
	DWORD& rKey, CPAIR& rValue) const
{
	ASSERT_VALID(this);
	ASSERT(m_pHashTable != NULL);  // never call on empty map

	CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	ASSERT(pAssocRet != NULL);

	if (pAssocRet == (CAssoc*) BEFORE_START_POSITION)
	{
		// find the first association
		for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		ASSERT(pAssocRet != NULL);  // must find something
	}

	// find next association
	ASSERT(AfxIsValidAddress(pAssocRet, sizeof(CAssoc)));
	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = pAssocRet->nHashValue + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (POSITION) pAssocNext;

	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization


/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG

void CMapDWORDToCPAIR::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

#define MAKESTRING(x) #x
	AFX_DUMP1(dc, "a " MAKESTRING(CMapDWORDToCPAIR) " with ", m_nCount);
	AFX_DUMP0(dc, " elements");
#undef MAKESTRING
//	if (dc.GetDepth() > 0)
//	{
		// Dump in format "[key] -> value"
//		POSITION pos = GetStartPosition();
//		DWORD key;
//		CPAIR val;

//		AFX_DUMP0(dc, "\n");
//		while (pos != NULL)
//		{
//			GetNextAssoc(pos, key, val);
//			AFX_DUMP1(dc, "\n\t[", key);
//			AFX_DUMP1(dc, "] = ", val);
//		}
//	}
}

void CMapDWORDToCPAIR::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(m_nHashTableSize > 0);
	ASSERT(m_nCount == 0 || m_pHashTable != NULL);
		// non-empty map should have hash table
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
