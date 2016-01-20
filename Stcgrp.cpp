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


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStcGroup

IMPLEMENT_DYNCREATE(CStcGroup, CObject)


CStcGroup::CStcGroup() 
{
	// TODO: add construction code here

	m_pCurrentDataValues = NULL;
	m_Residues = NULL;
	m_ResiduesSize = 0;
}


CStcGroup::~CStcGroup()
{
	ClearAllData();
}


/////////////////////////////////////////////////////////////////////////////
// CStcGroup serialization

void CStcGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStcGroup diagnostics

#ifdef _DEBUG
void CStcGroup::AssertValid() const
{
	CObject::AssertValid();
}

void CStcGroup::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG



void CStcGroup::ClearAllData()
{
	CString key;
	StcDataValues *pDV;
	void *pv;

	// Iterate through the entire map, dumping both name and age.
	for( POSITION pos = m_StcDataValuesMap.GetStartPosition(); pos != NULL; )
	{
		m_StcDataValuesMap.GetNextAssoc( pos, key, pv );
		
		pDV = (StcDataValues *)pv;

		GlobalFree( pDV->Values );
		pDV->ValuesSize = 0L;

		delete pDV;
	}

	m_StcDataValuesMap.RemoveAll();
	
	// m_Residues.Empty();
	if ( m_Residues != NULL ) {
		GlobalFree( m_Residues );
	}

	m_pCurrentDataValues = NULL;
	m_Residues = NULL;
	m_ResiduesSize = 0L;
	
	m_Description.Empty();
	m_Name.Empty();
	// CStringList
	m_FileNames.RemoveAll();
		
}
	
void 
CStcGroup::SetNameDescription( const CString& nName, const CString& nDescription )
{
	m_Name = nName;
	m_Description = nDescription;
}

void 
CStcGroup::GetNameDescription( CString& Name, CString& Description ) const
{
	Name = m_Name;
	Description = m_Description;
}
	
void 
CStcGroup::SetDataTypeValues( const CString& DataType, CMapWordToPtr *pCM, HGLOBAL Values, DWORD ValuesSize )
{
	void *pv;
	StcDataValues *pDV;
	
	if ( m_StcDataValuesMap.Lookup( DataType, pv ) ) {
		// Then Add one
		pDV = (StcDataValues *)pv;

		// pDV->Values.Empty();
		GlobalFree( pDV->Values );
		pDV->ValuesSize = 0L;
		// Copy New values
		pDV->Values = Values;
		pDV->ValuesSize = ValuesSize;
		// 
		pDV->pColorMap = pCM;
	} else {
		// Make a new Structure
		pDV = new StcDataValues;
		// Copy Everything
		pDV->Values = Values;
		pDV->ValuesSize = ValuesSize;
		//
		pDV->pColorMap = pCM;
		// Insert it into map
		m_StcDataValuesMap.SetAt ( DataType, pDV );
	}
}

void 
CStcGroup::SetCurrentDataType ( const CString& DataType, int Force )
{
	void *pv;
	if ( m_StcDataValuesMap.Lookup( DataType, pv ) ) {
		// Then Add one
		m_pCurrentDataValues = (StcDataValues *)pv;

		m_CurrentDataTypeString = DataType;
	} else if ( !Force ) {
		m_pCurrentDataValues = NULL;

		m_CurrentDataTypeString = "";
	} else if ( Force ) {
		m_pCurrentDataValues = NULL;

		m_CurrentDataTypeString = DataType;
	}
}

void 
CStcGroup::GetCurrentData ( DWORD Index, COLORREF *TextColor, COLORREF*BackColor )
{

	if ( m_pCurrentDataValues == NULL ) {
		return;
	}
	
	DWORD Length = m_pCurrentDataValues->ValuesSize;

	if ( Length == 0 ) return;
	if ( Length <= Index ) return;

	char *pVal = (char *)GlobalLock( m_pCurrentDataValues->Values );
	if ( pVal == NULL ) return;

	WORD tChar = pVal[Index];
	// WORD tChar = m_pCurrentDataValues->Values[Index];

	GlobalUnlock( m_pCurrentDataValues->Values );

	CMapWordToPtr *pCM = m_pCurrentDataValues->pColorMap;
	
	
	void *pv;
	if ( !pCM->Lookup ( tChar, pv ) ) return;

	StcColorMapValue* pCMV = (StcColorMapValue *)pv;

	*TextColor = pCMV->TextColor;
	*BackColor = pCMV->BackColor;

}

void 
CStcGroup::CopyResidues( HGLOBAL nResidues, DWORD nResiduesSize )
{
	if ( nResidues != NULL ) {
		char * pnRes = (char *)GlobalLock(nResidues);
		if ( pnRes == NULL ) {
			AfxMessageBox("GlobalLock Fails: CStcGroup::CopyVars 1" );
			AfxAbort();
		}
		
		m_Residues = GlobalAlloc( GMEM_FLAG, nResiduesSize );
		m_ResiduesSize = nResiduesSize;
		
		if ( m_Residues == NULL ) {
			AfxMessageBox("GlobalAlloc Fails: CStcGroup::CopyVars 2" );
			AfxAbort();
		}
		
		char *pRes = (char *)GlobalLock(m_Residues);
		if ( pRes == NULL ) {
			AfxMessageBox("GlobalLock Fails: CStcGroup::CopyVars 3" );
			AfxAbort();
		}
		
		while ( nResiduesSize-- ) {
			*pRes++ = *pnRes++;
		}
		
		GlobalUnlock(nResidues);
		GlobalUnlock(m_Residues);
	} else {
		m_Residues = NULL;
		m_ResiduesSize = 0;
	}

}
	
void 
CStcGroup::CopyDataValues( StcDataValues *pDV, HGLOBAL nValues, DWORD nValuesSize )
{

	char * pnVal = (char *)GlobalLock(nValues);
	if ( pnVal == NULL ) {
		AfxMessageBox("GlobalLock Fails: CStcGroup::CopyVars 1" );
		AfxAbort();
	}
	
	pDV->Values = GlobalAlloc( GMEM_FLAG, nValuesSize );
	pDV->ValuesSize = nValuesSize;
	
	if ( pDV->Values == NULL ) {
		AfxMessageBox("GlobalAlloc Fails: CStcGroup::CopyVars 2" );
		AfxAbort();
	}
	
	char *pVal = (char *)GlobalLock(pDV->Values);
	if ( pVal == NULL ) {
		AfxMessageBox("GlobalLock Fails: CStcGroup::CopyVars 3" );
		AfxAbort();
	}
	
	while ( nValuesSize-- ) {
		*pVal++ = *pnVal++;
	}
	
	GlobalUnlock(nValues);
	GlobalUnlock(pDV->Values);

}
	
void 
CStcGroup::AddFileName( const CString& strFName )
{
	POSITION tPos = m_FileNames.GetHeadPosition();
	while ( tPos != NULL ) {
		POSITION sPos = tPos;
		if ( m_FileNames.GetNext(tPos) == strFName ) {
			m_FileNames.RemoveAt(sPos);
		}
	}
	m_FileNames.AddTail( strFName );
}
 
void 
CStcGroup::CopyVars( const CStcGroup& fStcGroup )
{

	ClearAllData();

	// CMapStringToOb
	CString key;
	POSITION pos;	
	void *pfv;
	

	const CMapStringToPtr& DataValuesMap = fStcGroup.GetDataValuesMap();


	StcDataValues *pfDV;
	// Iterate through the entire map, dumping both name and age.
	for( pos = DataValuesMap.GetStartPosition(); pos != NULL; )
	{
		DataValuesMap.GetNextAssoc( pos, key, pfv );
		
		pfDV = (StcDataValues *)pfv;

		StcDataValues *pDV = new StcDataValues;

		// Fix this .. done 
		CopyDataValues( pDV, pfDV->Values, pfDV->ValuesSize );
		
		pDV->pColorMap = pfDV->pColorMap;

		m_StcDataValuesMap.SetAt( key, pDV );
		//

	}

	// CStringList
	const CStringList& cList = fStcGroup.GetFileNames();
	for( pos = cList.GetHeadPosition(); pos != NULL; )
	{
		m_FileNames.AddTail( cList.GetNext(pos) );
	}

	fStcGroup.GetNameDescription( m_Name, m_Description );

	// m_Residues = fStcGroup.GetResidues();
	CopyResidues( fStcGroup.GetResidues(), fStcGroup.GetResiduesSize() );

	m_MasterSeq = fStcGroup.GetMasterSeq();

	SetCurrentDataType( fStcGroup.GetCurrentDataType() );
	
}
