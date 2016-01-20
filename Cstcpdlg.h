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
// cstcpdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStructurePropDialog dialog

class CStructurePropDialog : public CPropertyPage
{
// Construction
public:
	CStructurePropDialog();	// standard constructor
	~CStructurePropDialog();	// standard destructor

	CGenedocDoc *pDoc;
	CPtrList	m_DataLabelList;
	// CString m_ResultDataType;
	CDisplayVars *m_DisplayVars;
	int m_ModifyAll;

	void ResetData();

// Dialog Data
	//{{AFX_DATA(CStructurePropDialog)
	enum { IDD = IDD_STRUCTUREPROP };
	CButton	m_StcLoadData;
	CComboBox	m_ComboMaster;
	CListBox	m_DataTypeList;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void InitDataTypeList();
	int m_DialogInited;

	// Generated message map functions
	//{{AFX_MSG(CStructurePropDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnStcloaddata();
	afx_msg void OnSelchangeDataTypeList();
	afx_msg void OnDatasetdet();
	afx_msg void OnDblclkDataTypeList();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
