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
// phylnode.cpp : implementation of the CPhyloNode class
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhyloNode

IMPLEMENT_DYNCREATE(CPhyloNode, CObject)

CPhyloNode::CPhyloNode(): CPhyloGenBase()
{
	// TODO: add construction code here
}


CPhyloNode::~CPhyloNode()
{

	while ( !m_PhyloList.IsEmpty() ) {
		delete (CPhyloGenBase *) m_PhyloList.RemoveHead();
	}

}


/////////////////////////////////////////////////////////////////////////////
// CPhyloNode serialization

void CPhyloNode::Serialize(CArchive& ar)
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
// CPhyloNode diagnostics

#ifdef _DEBUG
void CPhyloNode::AssertValid() const
{
	CObject::AssertValid();
}

void CPhyloNode::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CPhyloNode::SetDepth( int Depth )
{
	m_Depth = Depth;
	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		pPGBase->SetDepth( Depth + 1 );
	}
}	

void 
CPhyloNode::WriteString( CString& ParseString )
{
	ParseString += "(";
	
	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		pPGBase->WriteString( ParseString );
	}
	CString strWeight;
	if ( !m_Weight.IsEmpty() ) {
		strWeight += ":" + m_Weight;
		if ( m_pPGParent == NULL ) {
			ParseString += ")" + strWeight + ";\r\n";
		} else if ( ((CPhyloNode*)m_pPGParent)->m_PhyloList.GetTail() != this )  {
			ParseString += ")" + strWeight + ",\r\n";
		} else {
			ParseString += ")" + strWeight + "";
		}
	} else {
		if ( m_pPGParent == NULL ) {
			ParseString += ");\r\n";
		} else if ( ((CPhyloNode*)m_pPGParent)->m_PhyloList.GetTail() != this )  {
			ParseString += "),\r\n";
		} else {
			ParseString += ")";
		}
	}

}

int
CPhyloNode::CheckCounts(int ErrMsg)
{
	if ( m_PhyloList.GetCount() != 2 && ErrMsg == 0 ) return 1;

	if ( m_PhyloList.GetCount() != 2 ) {
		return 0;
	}
	
	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);
		if ( !pPGBase->CheckCounts(ErrMsg) ) {
			return 0;
		}
	}
	
	return 1;

}

int 
CPhyloNode::DetermineDraw ( CPhyloGenBase * pPSBLast )
{
	int ret = DNOTHING;
	CPhyloNode *pPNPLast = (CPhyloNode *)pPSBLast;

	if ( m_pPGParent == NULL ) {
		if ( pPSBLast->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) ) {
			if ( m_FirstBranch == 0 ) {
				if ( m_PhyloList.GetHead() == pPSBLast ) {
					ret = DNODESL;		// This the root node?
					ret = DNODER;
				} else {
					ret = DNODET;
				}
					
			} else {
				if ( m_PhyloList.GetTail() == pPSBLast ) {
					ret = DNODEEU;
				} else {
					ret = DNODET;
				}
			}
		} else if ( m_FirstBranch == 0 && pPNPLast->m_FirstBranch != 0 ) {
			if ( pPNPLast->m_DrawType == DNODEEL ) {
				ret = DNODESL;		// This the root node?
				ret = DNODER;
			} else if ( pPNPLast->m_DrawType == DNOTHING ) {
				ret = DNODEM;
			}
		} else if ( m_PhyloList.GetTail() == pPNPLast ) {
			if ( m_FirstBranch != 0 && pPNPLast->m_FirstBranch == 0 ) {
				if ( pPNPLast->m_DrawType == DNODESU ) {
					ret = DNODEEU;
				} else if ( pPNPLast->m_DrawType == DNOTHING ) {
					ret = DNODEM;
				}
			}
		} else if ( m_PhyloList.GetHead() != pPNPLast ) {
			if ( pPNPLast->m_DrawType == DNODESU ) {
				ret = DNODET;
			} else {
				ret = DNODEM;
			}
		}
	}
	else if ( ((CPhyloNode *)m_pPGParent)->m_FirstBranch == 0 ) {
		if ( pPSBLast->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) ) {
			if ( m_FirstBranch == 0 ) {
				if ( m_FirstCallBack == 1 ) {
					ret = DNODESL;
				} else {
					ret = DNODEM;
				}
			} else {
				ret = DNODEEL;
			}
		} else if ( m_FirstBranch == 0 && pPNPLast->m_FirstBranch != 0 ) {
			if ( pPNPLast->m_DrawType == DNODEEL ) {
				ret = DNODESL;
			} else if ( pPNPLast->m_DrawType == DNOTHING ) {
				ret = DNODEM;
			}
		} else if ( m_FirstBranch != 0 ) {
			if ( pPNPLast->m_DrawType == DNODESU ) {
				ret = DNODEEL;
			} else if ( pPNPLast->m_DrawType == DNOTHING && pPNPLast->m_FirstBranch == 0)  {
				ret = DNODEM;
			}
		}
	} else {
		if ( pPSBLast->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) ) {
			if ( m_FirstBranch != 0 ) {
				if ( m_FirstCallBack == 1 ) {
					ret = DNODEEU;
				} else {
					ret = DNODEM;
				}
			} else {
				ret = DNODESU;
			}
		} else if ( m_FirstBranch != 0 && pPNPLast->m_FirstBranch == 0 ) {
			if ( pPNPLast->m_DrawType == DNODESU ) {
				ret = DNODEEU;
			} else if ( pPNPLast->m_DrawType == DNOTHING ) {
				ret = DNODEM;
			}
		} else if ( m_FirstBranch == 0 ) {
			if ( pPNPLast->m_DrawType == DNODEEL ) {
				ret = DNODESU;
			} else if ( pPNPLast->m_DrawType == DNOTHING && pPNPLast->m_FirstBranch != 0)  {
				ret = DNODEM;
			}
		}
	}
	
	m_FirstCallBack = 0;
	m_DrawType = ret;

	return ret;
	
}

void
CPhyloNode::CallFromSeq( CView* pView )
{
	m_FirstBranch = 0;

	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		m_FirstCallBack = 1;
		pPGBase->CallFromSeq( pView );
		
		m_FirstBranch++;
	}

}

void
CPhyloNode::CallDocFromSeq( CDocument* pDoc )
{
	m_FirstBranch = 0;

	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		m_FirstCallBack = 1;
		pPGBase->CallDocFromSeq( pDoc );

		m_FirstBranch++;
		
	}

}

void
CPhyloNode::CallDocFromDepth( CDocument* pDoc, int Depth )
{
	ASSERT( pDoc->IsKindOf( RUNTIME_CLASS(CGenedocDoc)));
	CGenedocDoc* pGDoc = (CGenedocDoc*)pDoc;

	if ( m_Depth == Depth ) {
		pGDoc->CallDocFromDepth(this);
		return;
	}

	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		pPGBase->CallDocFromDepth( pDoc, Depth );
		
	}

}

void 
CPhyloNode::CallSDFromNamedSeq( CDialog *pDlg, const CString& Name )
{

	POSITION Pos = m_PhyloList.GetHeadPosition();
	while ( Pos != NULL ) {
		CPhyloGenBase *pPGBase = (CPhyloGenBase*)m_PhyloList.GetNext(Pos);

		pPGBase->CallSDFromNamedSeq( pDlg, Name );
		
	}
}

