// ShadeColorp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShadeColorProperty dialog


CShadeColorProperty::CShadeColorProperty() : CPropertyPage(CShadeColorProperty::IDD)
{
        //{{AFX_DATA_INIT(CShadeColorProperty)
	//}}AFX_DATA_INIT
}

void CShadeColorProperty::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CShadeColorProperty)
	//}}AFX_DATA_MAP
}

BOOL CShadeColorProperty::OnStyleClicked(UINT /*nCmdID*/)
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
//              ((CModalShadeColorPropSheet*)pPropertySheet)->UpdateShapePreview();
                SetModified(); // enable Apply Now button
        }
        return TRUE;
}

BEGIN_MESSAGE_MAP(CShadeColorProperty, CPropertyPage)
        //{{AFX_MSG_MAP(CShadeColorProperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShadeColorProperty message handlers


BOOL CShadeColorProperty::OnInitDialog() 
{
        CDialog::OnInitDialog();
        
        // TODO: Add extra initialization here

        
        return TRUE;  // return TRUE unless you set the focus to a control
                      // EXCEPTION: OCX Property Pages should return FALSE
}
