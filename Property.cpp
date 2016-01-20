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
//
// Property.cpp : implementation of the CProperty class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProperty

IMPLEMENT_DYNCREATE(CProperty, CObject)

/////////////////////////////////////////////////////////////////////////////
// CProperty serialization

void CProperty::Serialize(CArchive& ar)
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
// CProperty diagnostics

#ifdef _DEBUG
void CProperty::AssertValid() const
{
	CObject::AssertValid();
}

void CProperty::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


CProperty::CProperty()
{
}

void
CProperty::ClearArray()
{
	PropertyStruct *tPS;
	for ( int PropLevel = 0; PropLevel < 3; ++PropLevel ) {
		int count = m_PropertyArray[PropLevel].GetSize();
		for ( int i = 0; i < count; ++i ) {
			tPS = (PropertyStruct *)m_PropertyArray[PropLevel][i];
			delete tPS;
		}
		m_PropertyArray[PropLevel].RemoveAll();
	}
}

CProperty::~CProperty()
{
	ClearArray();
}


void
CProperty::CopyVars( CProperty& nProperty)
{
	SetPropertyArray( nProperty.GetArray(0), &m_PropertyArray[0] );

	SetPropertyArray( nProperty.GetArray(1), &m_PropertyArray[1] );

	SetPropertyArray( nProperty.GetArray(2), &m_PropertyArray[2] );
}



void
SetPropertyArray( CPtrArray *fPropertyArray, CPtrArray *tPropertyArray )
{
	PropertyStruct *tPS;
	PropertyStruct *tPSn;
	int count = tPropertyArray->GetSize();

	for ( int i = 0; i < count; ++i ) {
		tPS = (PropertyStruct *)(*tPropertyArray)[i];
		delete tPS;
	}
	tPropertyArray->RemoveAll();

	count = fPropertyArray->GetSize();
	for (int i = 0; i < count; ++i ) { 
		tPS = new PropertyStruct;
		if ( tPS == 0 ) {
			AfxMessageBox( "Geneddoc:new:fail:9" );
			return;
		}
		tPSn = (PropertyStruct *)fPropertyArray->GetAt(i);

		tPS->RowNum = tPSn->RowNum;
		strcpy ( tPS->Group, tPSn->Group );
		tPS->TextColor = tPSn->TextColor;
		tPS->BkColor = tPSn->BkColor;

		tPropertyArray->Add( tPS );
	}

}	

void
SetPropertyDefault(CPtrArray *PropertyArray, int PropertyLevel, int ProjectType )
{ 
	int i;
	PropertyStruct *tPS;

	int count = PropertyArray->GetSize();
	for ( i = 0; i < count; ++i ) {
		tPS = (PropertyStruct *)(*PropertyArray)[i];
		delete tPS;
	}
	PropertyArray->RemoveAll();

	int RowCount;

	if ( ProjectType < 2 ) {
		// Fill in array with new values.
		switch ( PropertyLevel ) {
		case 0:
			for ( i = 0; i < 2; ++ i ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:4" );
					return;
				}
		
				switch ( i ) {
				case 0:
					strcpy ( tPS->Group, "DEHKRNQST" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "LIVMFYWAGCP" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,255,0);
					break;
				}
		
				tPS->RowNum = i + 1;
		
				PropertyArray->Add( tPS );
			}
			break;
		case 1:
			for ( RowCount = 0; RowCount < 4; ++RowCount ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:5" );
					return;
				}
				tPS->RowNum = RowCount + 1;
				switch ( RowCount ) {
				case 0:
					strcpy ( tPS->Group, "DEHKR" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "NQST" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,128,0);
					break;
				case 2:
					strcpy ( tPS->Group, "LIVMFYW" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,255,0);
					break;
				case 3:
					strcpy ( tPS->Group, "AG" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,128,0);
					break;
				}
					
				PropertyArray->Add( tPS );
			}
			break;
		case 2:
			for ( i = 0; i < 8; ++ i ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:6" );
					return;
				}
	// D,E  H,K,R N,Q  S,T  L,I,V  F,Y,W  A,G  M,C
				switch ( i ) {
				case 0:
					strcpy ( tPS->Group, "DE" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "HKR" );
					tPS->TextColor = RGB ( 255,255,255);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 2:
					strcpy ( tPS->Group, "NQ" );
					tPS->TextColor = RGB ( 0, 255,0);
					tPS->BkColor = RGB ( 255,128,0);
					break;
				case 3:
					strcpy ( tPS->Group, "ST" );
					tPS->TextColor = RGB ( 255,255,255);
					tPS->BkColor = RGB ( 255,128,0);
					break;
				case 4:
					strcpy ( tPS->Group, "LIV" );
					tPS->TextColor = RGB ( 255, 0,0 );
					tPS->BkColor = RGB ( 0,255,0);
					break;
				case 5:
					strcpy ( tPS->Group, "FYW" );
					tPS->TextColor = RGB ( 255, 255,255 );
					tPS->BkColor = RGB ( 0,255,0);
					break;
				case 6:
					strcpy ( tPS->Group, "AG" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,128,0);
					break;
				case 7:
					strcpy ( tPS->Group, "MC" );
					tPS->TextColor = RGB ( 255,255,255 );
					tPS->BkColor = RGB ( 0,128,0);
					break;
				}
				tPS->RowNum = i + 1;
		
				PropertyArray->Add( tPS );
			}
		}
	} else {
		// Fill in array with new values.
		switch ( PropertyLevel ) {
		case 0:
			for ( i = 0; i < 2; ++ i ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:7" );
					return;
				}
		
				switch ( i ) {
				case 0:
					strcpy ( tPS->Group, "AG" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "CTU" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,255,0);
					break;
				}
		
				tPS->RowNum = i + 1;
		
				PropertyArray->Add( tPS );
			}
			break;
		case 1:
			for ( i = 0; i < 2; ++ i ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:8" );
					return;
				}
		
				switch ( i ) {
				case 0:
					strcpy ( tPS->Group, "GC" );
					tPS->TextColor = RGB ( 0,255,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "ATU" );
					tPS->TextColor = RGB ( 255,0,0);
					tPS->BkColor = RGB ( 0,255,0);
					break;
				}
		
				tPS->RowNum = i + 1;
		
				PropertyArray->Add( tPS );
			}
			break;
		case 2:
			for ( i = 0; i < 5; ++ i ) {
				tPS = new PropertyStruct;
				if ( tPS == 0 ) {
					AfxMessageBox( "Geneddoc:new:fail:8" );
					return;
				}
		
				switch ( i ) {
				case 0:
					strcpy ( tPS->Group, "A" );
					tPS->TextColor = RGB ( 0,0,0);
					tPS->BkColor = RGB ( 255,0,0);
					break;
				case 1:
					strcpy ( tPS->Group, "C" );
					tPS->TextColor = RGB ( 0,0,0);
					tPS->BkColor = RGB ( 0,255,0);
					break;
				case 2:
					strcpy ( tPS->Group, "TU" );
					tPS->TextColor = RGB ( 0,0,0);
					tPS->BkColor = RGB ( 0,0,255);
					break;
				case 3:
					strcpy ( tPS->Group, "G" );
					tPS->TextColor = RGB ( 0,0,0);
					tPS->BkColor = RGB ( 255,255,0);
					break;
				case 4:
					strcpy ( tPS->Group, "NX" );
					tPS->TextColor = RGB ( 255,255,255);
					tPS->BkColor = RGB ( 0,0,0);
					break;
				}
		
				tPS->RowNum = i + 1;
		
				PropertyArray->Add( tPS );
			}
			break;

		}
	}
} 



