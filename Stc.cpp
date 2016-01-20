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

#include "stccmapi.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStc

IMPLEMENT_DYNCREATE(CStc, CObject)


CStc::CStc() 
{
	// TODO: add construction code here
	m_SCMIEMBLLoaded = 0;
	m_SCMIPSDBLoaded = 0;
	m_SCMIPDBLoaded = 0;
}


CStc::~CStc()
{
	ClearAllData();
}


/////////////////////////////////////////////////////////////////////////////
// CStc serialization

void CStc::Serialize(CArchive& ar)
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
// CStc diagnostics

#ifdef _DEBUG
void CStc::AssertValid() const
{
	CObject::AssertValid();
}

void CStc::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG



void CStc::ClearAllData()
{
	// CMapStringToOb
	CString key;
	CObject *pOCM;
	CMapWordToPtr *pCM;
	POSITION pos, pos2;	
	void *pv;
	WORD key2;
	
	// Iterate through the entire map, dumping both name and age.
	for( pos = m_StcNameToColorMap.GetStartPosition(); pos != NULL; )
	{
		m_StcNameToColorMap.GetNextAssoc( pos, key, pOCM );
		ASSERT(pOCM->IsKindOf(RUNTIME_CLASS(CMapWordToPtr)));
		pCM = (CMapWordToPtr*)pOCM;
		for( pos2 = pCM->GetStartPosition(); pos2 != NULL; )
		{
			pCM->GetNextAssoc( pos2, key2, pv );
			StcColorMapValue *pCMV = (StcColorMapValue *)pv;
			delete pCMV->Label;
			delete pCMV;
		}
		pCM->RemoveAll();
		//
		delete pCM;
	}
	m_StcNameToColorMap.RemoveAll();


	StcDataType *pDT;
	// Iterate through the entire map, dumping both name and age.
	for( pos = m_StcDataTypeMap.GetStartPosition(); pos != NULL; )
	{
		m_StcDataTypeMap.GetNextAssoc( pos, key, pv );
		
		pDT = (StcDataType *)pv;
		delete pDT->DataType;
		delete pDT->ShortLabel;
		delete pDT->LongLabel;
		delete pDT->ColorMapName;

		delete pDT;
	}
	m_StcDataTypeMap.RemoveAll();
	m_StcDataTypeList.RemoveAll();
	
	m_SCMIEMBLLoaded = 0;
	m_SCMIPSDBLoaded = 0;
	
}


int CStc::LoadSCMIEMBL()
{
	CString ReadString;

	for ( int MapLoc = 0; MapLoc < (sizeof(SCMIEMBL) / sizeof( char *)); ++ MapLoc ) {
		ReadString.Empty();
		ReadString = SCMIEMBL[MapLoc];
		if ( !StcParseString(ReadString, 0) ) return 0;
	}
	m_SCMIEMBLLoaded = 1;

	return 1;
}
int CStc::SCMIEMBLLoaded()
{
	return m_SCMIEMBLLoaded;
}
int CStc::LoadSCMIPSDB()
{
#ifdef _WIN32

	CString ReadString;

	for ( int MapLoc = 0; MapLoc < (sizeof(SCMIPSDB) / sizeof( char *)); ++ MapLoc ) {
		ReadString.Empty();
		ReadString = SCMIPSDB[MapLoc];
		if ( !StcParseString(ReadString, 0) ) return 0;
	}
	m_SCMIPSDBLoaded = 1;

	return 1;
#else
	m_SCMIPSDBLoaded = 0;      
	return 0;
#endif
}
int CStc::SCMIPSDBLoaded()
{
	return m_SCMIPSDBLoaded;
}
	
int CStc::LoadSCMIPDB()
{
	CString ReadString;

	for ( int MapLoc = 0; MapLoc < (sizeof(SCMIPDB) / sizeof( char *)); ++ MapLoc ) {
		ReadString.Empty();
		ReadString = SCMIPDB[MapLoc];
		if ( !StcParseString(ReadString, 0) ) return 0;
	}
	m_SCMIPDBLoaded = 1;

	return 1;
}
int CStc::SCMIPDBLoaded()
{
	return m_SCMIPDBLoaded;
}

void  
CStc::ClearAll()
{
	ClearAllData();
}


int 
CStc::StcParseString(const CString& ReadString, int OverRideColor )
{
TRY {

	if ( ReadString.Left( 8 ) == "COLORMAP" ) {
		// Vars
		CString Name;
		CString Label;
		WORD Symbol;
		BYTE Red, Green, Blue;
		COLORREF ColorRef;
		CString Values;

		int Count = 8;
		int Length = ReadString.GetLength();
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get COLORMAP Name
		while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',') {
			Name += ReadString[Count];
			if ( ++Count >= Length ) goto skipCOLORMAP;
		}

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Quote
		while( ReadString[Count] == '"' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get SymbolMap Label
		while( ReadString[Count] != '"' ) {
			if ( ReadString[Count] == '\\' ) {
				if ( ++Count >= Length ) goto skipCOLORMAP;
				if ( ReadString[Count] == '"' ) {
					Label += ReadString[Count];
				} else {
					--Count;
					Label += ReadString[Count];
				}
			} else {
				Label += ReadString[Count];
			}
			if ( ++Count >= Length ) goto skipCOLORMAP;
		}
		// Skip over End Quote
		if ( ++Count >= Length ) goto skipCOLORMAP;

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get Symbolmap symbol
		Symbol = ReadString[Count];
		if ( ++Count >= Length ) goto skipCOLORMAP;

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get Red Value
		while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
			Values += ReadString[Count];
			if ( ++Count >= Length ) goto skipCOLORMAP;
		}
		Red = atoi( (const char *)Values );
		Values.Empty();
		
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get Green Value
		while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
			Values += ReadString[Count];
			if ( ++Count >= Length ) goto skipCOLORMAP;
		}
		Green = atoi( (const char *)Values );
		Values.Empty();

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipCOLORMAP;
		// Get Blue Value
		while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
			Values += ReadString[Count];
			if ( ++Count >= Length ) break;
		}
		Blue = atoi( (const char *)Values );
		Values.Empty();
		
		ColorRef = RGB( Red, Green, Blue );
		
		COLORREF TextColor;

		if ( Count < Length ) {
			// Get White Space
			while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
				if ( ++Count >= Length ) goto skipTextColor;
			// Get a Comma
			while( ReadString[Count] == ',' )
				if ( ++Count >= Length ) goto skipTextColor;
			// Get White Space
			while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
				if ( ++Count >= Length ) goto skipTextColor;
			// Get Red Value
			while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
				Values += ReadString[Count];
				if ( ++Count >= Length ) break;
			}
			Red = atoi( (const char *)Values );
			Values.Empty();
			

			if ( Count < Length ) {
				// Get White Space
				while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get a Comma
				while( ReadString[Count] == ',' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get White Space
				while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get Green Value
				while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
					Values += ReadString[Count];
					if ( ++Count >= Length ) goto skipTextColor;
				}
				Green = atoi( (const char *)Values );
				Values.Empty();

				// Get White Space
				while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get a Comma
				while( ReadString[Count] == ',' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get White Space
				while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
					if ( ++Count >= Length ) goto skipTextColor;
				// Get Blue Value
				while( ReadString[Count] != ' ' && ReadString[Count] != '\t' && ReadString[Count] != ',' ) {
					Values += ReadString[Count];
					if ( ++Count >= Length ) break;
				}
				Blue = atoi( (const char *)Values );
				Values.Empty();

				TextColor = RGB( Red, Green, Blue );
				goto TextColorcont;
			}
				
			Values.Empty();
			if ( Red ) {
				TextColor = RGB(255,255,255);
			} else {
				TextColor = RGB(0,0,0);
			}
			goto TextColorcont;
		}

skipTextColor:
		if ( (GetGValue(ColorRef) > 127) ) {
			TextColor = RGB(0,0,0);
		} else {
			TextColor = RGB(255,255,255);
		}

TextColorcont:


		CObject *pOCM;
		// All data found, lets add it if needed.
		if ( !m_StcNameToColorMap.Lookup( Name, pOCM ) ) {
			// Then Add one
			CMapWordToPtr * pCM = new CMapWordToPtr;
			StcColorMapValue *pCMV = new StcColorMapValue;
			pCMV->Label = new CString(Label);
			pCMV->TextColor = TextColor;
			pCMV->BackColor = ColorRef;
			pCM->SetAt( Symbol, pCMV );

			m_StcNameToColorMap.SetAt( Name, pCM );
		} else {
			CMapWordToPtr *pCM = (CMapWordToPtr *)pOCM;
			void *pv;
			if ( !pCM->Lookup( Symbol, pv ) ) {
				StcColorMapValue *pCMV = new StcColorMapValue;
				pCMV->Label = new CString(Label);
				pCMV->TextColor = TextColor;
				pCMV->BackColor = ColorRef;
				pCM->SetAt( Symbol, pCMV );
			} else if ( OverRideColor ) {
				// Then lets override whats already there.
				StcColorMapValue *pCMV = (StcColorMapValue *)pv;
				*pCMV->Label = Label;
				pCMV->TextColor = TextColor;
				pCMV->BackColor = ColorRef;
			}
		}

skipCOLORMAP:;

	} else if ( ReadString.Left( 8 ) == "DATATYPE" ) {
		// Vars
		CString DataType;
		CString ShortLabel;
		CString LongLabel;
		CString Name;
		CString strDataStart;
		int DataStart = 0;
		CString strDataAmount;
		int DataAmount = 0;

		int Count = 8;
		int Length = ReadString.GetLength();
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Quote
		while( ReadString[Count] == '"' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get SymbolMap Label
		while( ReadString[Count] != '"' ) {
			if ( ReadString[Count] == '\\' ) {
				if ( ++Count >= Length ) goto skipDATATYPE;
				if ( ReadString[Count] == '"' ) {
					DataType += ReadString[Count];
				} else {
					--Count;
					DataType += ReadString[Count];
				}
			} else {
				DataType += ReadString[Count];
			}
			if ( ++Count >= Length ) goto skipDATATYPE;
		}
		// Skip over End Quote
		if ( ++Count >= Length ) goto skipDATATYPE;


		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get SymbolMap Label
		while( ReadString[Count] != ',' ) {
			strDataStart += ReadString[Count];
			if ( ++Count >= Length ) goto skipDATATYPE;
		}
		// Skip over End Quote
		DataStart = atoi(strDataStart);

		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get SymbolMap Label
		while( ReadString[Count] != ',' ) {
			strDataAmount += ReadString[Count];
			if ( ++Count >= Length ) goto skipDATATYPE;
		}
		// Skip over End Quote
		DataAmount = atoi(strDataAmount);
		
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Quote
		while( ReadString[Count] == '"' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get SymbolMap Label
		while( ReadString[Count] != '"' ) {
			if ( ReadString[Count] == '\\' ) {
				if ( ++Count >= Length ) goto skipDATATYPE;
				if ( ReadString[Count] == '"' ) {
					ShortLabel += ReadString[Count];
				} else {
					--Count;
					ShortLabel += ReadString[Count];
				}
			} else {
				ShortLabel += ReadString[Count];
			}
			if ( ++Count >= Length ) goto skipDATATYPE;
		}
		// Skip over End Quote
		if ( ++Count >= Length ) goto skipDATATYPE;

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Quote
		while( ReadString[Count] == '"' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get SymbolMap Label
		while( ReadString[Count] != '"' ) {
			if ( ReadString[Count] == '\\' ) {
				if ( ++Count >= Length ) goto skipDATATYPE;
				if ( ReadString[Count] == '"' ) {
					LongLabel += ReadString[Count];
				} else {
					--Count;
					LongLabel += ReadString[Count];
				}
			} else {
				LongLabel += ReadString[Count];
			}
			if ( ++Count >= Length ) goto skipDATATYPE;
		}
		// Skip over End Quote
		if ( ++Count >= Length ) goto skipDATATYPE;

		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Comma
		while( ReadString[Count] == ',' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get a Quote
		while( ReadString[Count] == '"' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get White Space
		while( ReadString[Count] == ' ' || ReadString[Count] == '\t' )
			if ( ++Count >= Length ) goto skipDATATYPE;
		// Get COLORMAP Name
		while( 
			ReadString[Count] != ' ' 
			&& ReadString[Count] != '\t' 
			&& ReadString[Count] != ',' 
			&& ReadString[Count] != '\n'
		) {
			Name += ReadString[Count];
			if ( ++Count >= Length ) break;
		}

		// All data found, lets add it if needed.
		void *pv;

		if ( !m_StcDataTypeMap.Lookup( DataType, pv ) ) {
			// Then Add one
			StcDataType *pDT = new StcDataType;
			pDT->DataType = new CString(DataType);
			pDT->DataStart = DataStart;
			pDT->DataAmount = DataAmount;
			pDT->ShortLabel = new CString(ShortLabel);
			pDT->LongLabel = new CString(LongLabel);
			pDT->ColorMapName = new CString(Name);
			
			CObject *pOCM;
			if ( m_StcNameToColorMap.Lookup( Name, pOCM ) ) {
				pDT->ColorMap = (CMapWordToPtr *)pOCM;
			} else {
				AfxMessageBox("Setting Color Map NULL!");
				pDT->ColorMap = NULL;
			}

			m_StcDataTypeMap.SetAt( DataType, pDT );
			m_StcDataTypeList.AddTail( pDT );

		} else  if ( OverRideColor ) {
			// Lets override whats already there..
			StcDataType *pDT = (StcDataType *)pv;
			*pDT->DataType = DataType;
			pDT->DataStart = DataStart;
			pDT->DataAmount = DataAmount;
			*pDT->ShortLabel = ShortLabel;
			*pDT->LongLabel = LongLabel;
			*pDT->ColorMapName = Name;
			
			CObject *pOCM;
			if ( m_StcNameToColorMap.Lookup( Name, pOCM ) ) {
				pDT->ColorMap = (CMapWordToPtr *)pOCM;
			} else {
				AfxMessageBox("Setting Color Map NULL!");
				pDT->ColorMap = NULL;
			}
		}

skipDATATYPE:;

	}

}
CATCH ( CMemoryException, e ) {

	ClearAllData();

	AfxMessageBox("Memory Exception: Function Fails" );

return 0;

}
END_CATCH

return 1;
}
	
void CStc::CopyVars( const CStc& fStc )
{

	ClearAllData();
	m_StcDataTypeList.RemoveAll();

	// CMapStringToOb
	CString key;
	CObject *pfOCM;
	CMapWordToPtr *pfCM;
	POSITION pos, pos2;	
	void *pfv;
	WORD key2;
	
	const CMapStringToOb& NameToColorMap = fStc.GetColorMap();
	// Iterate through the entire map, dumping both name and age.
	for( pos = NameToColorMap.GetStartPosition(); pos != NULL; )
	{
		NameToColorMap.GetNextAssoc( pos, key, pfOCM );
		ASSERT(pfOCM->IsKindOf(RUNTIME_CLASS(CMapWordToPtr)));
		pfCM = (CMapWordToPtr*)pfOCM;

		// Then Add one
		CMapWordToPtr * pCM = new CMapWordToPtr;
		
		for( pos2 = pfCM->GetStartPosition(); pos2 != NULL; )
		{
			pCM->GetNextAssoc( pos2, key2, pfv );
			StcColorMapValue *pfCMV = (StcColorMapValue *)pfv;
	   
			StcColorMapValue *pCMV = new StcColorMapValue;
			pCMV->Label = new CString(*pfCMV->Label);
			pCMV->TextColor = pfCMV->TextColor;
			pCMV->BackColor = pfCMV->BackColor;
			pCM->SetAt( key2, pCMV );

		}
		m_StcNameToColorMap.SetAt( key, pCM );

	}


	const CMapStringToPtr& DataTypeMap = fStc.GetDataTypeMap();


	StcDataType *pfDT;
	// Iterate through the entire map, dumping both name and age.
	for( pos = DataTypeMap.GetStartPosition(); pos != NULL; )
	{
		DataTypeMap.GetNextAssoc( pos, key, pfv );
		
		pfDT = (StcDataType *)pfv;

		StcDataType *pDT = new StcDataType;

		pDT->DataType = new CString( *pfDT->DataType );
		pDT->ShortLabel = new CString( *pfDT->ShortLabel );
		pDT->LongLabel = new CString( *pfDT->LongLabel );
		pDT->ColorMapName = new CString( *pfDT->ColorMapName );

		m_StcDataTypeMap.SetAt( key, pDT );
		m_StcDataTypeList.AddTail( pDT );
		//
		// delete pDT;

	}
	// m_StcDataTypeMap.RemoveAll();
	//

}
