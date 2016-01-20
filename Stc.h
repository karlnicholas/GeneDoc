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

#ifndef STC_H_INCLUDED
#define STC_H_INCLUDED

typedef struct sStcDataType {		// Project Level **
	CString *DataType;
	int DataStart, DataAmount;
	CString *ShortLabel;
	CString *LongLabel;
	CString *ColorMapName;
	//
	CMapWordToPtr *ColorMap;	// Convience pointer
	// 
} StcDataType;
	

typedef struct sStcColorMapValue {			// Project Level
	CString *Label;
	COLORREF TextColor;
	COLORREF BackColor;
} StcColorMapValue;

class CStc : public CObject {
public:


private:

	CMapStringToOb	m_StcNameToColorMap;		// Project Level
	

	CMapStringToPtr m_StcDataTypeMap;			// Project Level
	CPtrList m_StcDataTypeList;					// Project Level

					// Need a filename to save ... not

	void ClearAllData();

	int m_SCMIEMBLLoaded;
	int m_SCMIPSDBLoaded;
	int m_SCMIPDBLoaded;

public:

	CStc();
	DECLARE_DYNCREATE(CStc)
        
	virtual ~CStc();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CopyVars( const CStc& fStc );

	int LoadSCMIEMBL();
	int SCMIEMBLLoaded();
	int LoadSCMIPSDB();
	int SCMIPSDBLoaded();
	int LoadSCMIPDB();
	int SCMIPDBLoaded();
	void ClearAll();
	int StcParseString(const CString& ReadString, int OverRideColor = 1 );
	
	const CMapStringToOb& GetColorMap() const { return m_StcNameToColorMap; }
	
	int GetColorMapCount() const { return m_StcNameToColorMap.GetCount(); }
	
	const CMapStringToPtr& GetDataTypeMap() const { return m_StcDataTypeMap; }
	
	const CPtrList& GetDataTypeList() const { return m_StcDataTypeList; }

	BOOL LookupDataType( const CString& DataType, StcDataType** pDataType ) const 
		{ 
			void *pv;
			BOOL rv =  m_StcDataTypeMap.Lookup( DataType, pv );
			*pDataType = (StcDataType*)pv;
			return rv;
		}
	
};

#endif
