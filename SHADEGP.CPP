// ShadeGroupp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShadeGroupProperty dialog


CShadeGroupProperty::CShadeGroupProperty() : CPropertyPage(CShadeGroupProperty::IDD)
{
	//{{AFX_DATA_INIT(CShadeGroupProperty)
	//}}AFX_DATA_INIT
}

void CShadeGroupProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShadeGroupProperty)
	//}}AFX_DATA_MAP
}

BOOL CShadeGroupProperty::OnStyleClicked(UINT /*nCmdID*/)
{
	// The CStylePage property page is used for both the
	// CModalShapePropSheet and the CModelessShapePropSheet.
	// Both these versions of the property sheet share a common
	// feature that they immediately update a shape.  In the
	// case of CModalShapePropSheet, the shape is in the preview
	// window.  In the case of CModelessShapePropSheet, the shape
	// is the currently selected shape in the view.

	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();

	if (pPropertySheet->IsKindOf(RUNTIME_CLASS(CModalDisplayPropSheet)))
	{
		UpdateData();
//		((CModalShadeGroupPropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CShadeGroupProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CShadeGroupProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShadeGroupProperty message handlers


// CreateBitmap

BOOL CShadeGroupProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// CListBox	
//	m_ShadePairsChanged = 0;	// Not here. This gets changed both ways elsewhere.
	
	ReBuildListBox();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void
CShadeGroupProperty::ReBuildListBox()
{
	
}


CShadeGroupProperty::~CShadeGroupProperty()
{

	// TODO: Add your message handler code here
}



