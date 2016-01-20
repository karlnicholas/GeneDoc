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

// CPtrList
void 
CGenedocDoc::ResetTree()
{

	if ( pGSFiller == NULL ) return;

	CPhyloGenBase *pPGTemp;
	CGeneSegment *pCGSeg;

	if ( m_pPGBase != NULL ) {
		delete m_pPGBase;
	}
	m_pPGBase = new CPhyloNode();
	m_pPGBase->m_pPGParent = NULL;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		pPGTemp = new CPhyloSeq();
		pPGTemp->m_pPGParent = m_pPGBase;
		((CPhyloSeq *)pPGTemp)->SetSequence(pCGSeg);
		m_pPGBase->m_PhyloList.AddTail( pPGTemp );
		
	}

	SetDepths();
	WriteString();
	
	UpdateAllViews(NULL);
	
	return;
}


int 
CGenedocDoc::ParseTree( const CString& ParseString, int ErrMsgs )
{

	CPhyloGenBase *pPGCurrent;
	CPhyloGenBase *pPGWeight;
	CPhyloGenBase *pPGTemp;
	CPhyloNode *pTempBase;
	CString strWeight;
	
	int StrLength;
	int NameCheck;
	char Name[101];
	int FoundEnd = 0;
	int pos;
	
	if ( (StrLength = ParseString.GetLength()) == 0 ) {
		if ( ErrMsgs ) AfxMessageBox("Empty Parse String");
		return 0;
	}
	
	for ( pos = 0; pos < StrLength; ++pos ) {
		if ( ParseString.GetAt(pos) == '(' ) {
			pos++;
			break;
		}
	}
	if ( pos == StrLength ) {
		if ( ErrMsgs ) AfxMessageBox("Starting '(' not found!" );
		return 0;
	}

	pTempBase = new CPhyloNode();
	pPGCurrent = pTempBase;
	pPGWeight = pTempBase;
	pTempBase->m_pPGParent = NULL;
	

	for ( ; pos < StrLength; ++pos ) {
		switch ( ParseString.GetAt(pos) ) {
		case '(':
			if ( pPGCurrent == NULL ) {
				if ( ErrMsgs ) AfxMessageBox("Last Paren Previously Encountered");
				delete pTempBase;
				return 0;
			}
			pPGTemp = new CPhyloNode();
			pPGTemp->m_pPGParent = pPGCurrent;
			ASSERT( pPGCurrent->IsKindOf( RUNTIME_CLASS( CPhyloNode ) ) );
			((CPhyloNode *)pPGCurrent)->m_PhyloList.AddTail( pPGTemp );
			pPGCurrent = pPGTemp;
			pPGWeight = pPGTemp;

			break;
		case ')':
			if ( pPGCurrent == NULL ) {
				if ( ErrMsgs ) AfxMessageBox("Last Paren Previously Encountered");
				delete pTempBase;
				return 0;
			}

			pPGWeight = pPGCurrent;
			pPGCurrent = pPGCurrent->m_pPGParent;
			break;
		case ',':
			if ( pPGCurrent == NULL ) {
				if ( ErrMsgs ) AfxMessageBox("Last Paren Previously Encountered");
				delete pTempBase;
				return 0;
			}
			break;
		case ';':
			FoundEnd = TRUE;
			pos = StrLength;
			break;
		case ' ':
		case '\r':
		case '\n':
			break;
		case ':':
			while ( ++pos < StrLength ) {
				if ( ParseString.GetAt(pos) == ':' ) break;
				if ( ParseString.GetAt(pos) == ',' ) break;
				if ( ParseString.GetAt(pos) == ')' ) break;
				if ( ParseString.GetAt(pos) == '(' ) break;
				if ( ParseString.GetAt(pos) == ' ' ) break;
				if ( ParseString.GetAt(pos) == ';' ) break;
				if ( ParseString.GetAt(pos) == '\r' ) break;
				if ( ParseString.GetAt(pos) == '\n' ) break;
				strWeight += ParseString.GetAt(pos);
			}
			--pos;
			pPGWeight->m_Weight = strWeight;
			strWeight.Empty();

			break;
		default:
			int c1;
			if ( pPGCurrent == NULL ) {
				if ( ErrMsgs ) AfxMessageBox("Last Paren Previously Encountered");
				delete pTempBase;
				return 0;
			}
			// CString
			
			for ( c1 = pos; c1 < pos + 100; ++c1 ) {
				if ( c1 >= StrLength ) break;
				if ( ParseString.GetAt(c1) == ':' ) break;
				if ( ParseString.GetAt(c1) == ',' ) break;
				if ( ParseString.GetAt(c1) == ')' ) break;
				if ( ParseString.GetAt(c1) == '(' ) break;
				if ( ParseString.GetAt(c1) == ' ' ) break;
				if ( ParseString.GetAt(c1) == ';' ) break;
				if ( ParseString.GetAt(c1) == '\r' ) break;
				if ( ParseString.GetAt(c1) == '\n' ) break;
				Name[c1 - pos] = ParseString.GetAt(c1);

			}
			
			if ( c1 < StrLength ) {
				NameCheck = 0;
				if ( ParseString.GetAt(c1) == ':' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == ',' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == ')' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == '(' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == ' ' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == ';' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == '\r' ) NameCheck = 1;
				if ( ParseString.GetAt(c1) == '\n' ) NameCheck = 1;

				if ( !NameCheck ) {
					if ( ErrMsgs ) AfxMessageBox( "Name is too long: 100 Chars Max" );
					delete pTempBase;
					return 0;
				}			
				Name[c1 - pos] = 0;
			} else {
				if ( ErrMsgs ) AfxMessageBox( "Unexpected end of Statement" );
				delete pTempBase;
				return 0;
			}			

			if ( strlen ( Name ) == 0 ) {
				if ( ErrMsgs ) AfxMessageBox( "Zero Length Name!" );
				delete pTempBase;
				return 0;
			} else {
				pos = c1 - 1;
			}


			pPGTemp = new CPhyloSeq();
			pPGTemp->m_pPGParent = pPGCurrent;
			
			CGeneSegment* pCGSeg;
			if ( (pCGSeg = GetSequenceFromName( Name )) == NULL ) {
				if ( ErrMsgs ) AfxMessageBox("Sequence Name not Found!" );
				delete pPGTemp;
				delete pTempBase;
				return 0;
			}
			
			((CPhyloSeq *)pPGTemp)->SetSequence(pCGSeg);

			
			ASSERT( pPGCurrent->IsKindOf( RUNTIME_CLASS( CPhyloNode ) ) );
			((CPhyloNode *)pPGCurrent)->m_PhyloList.AddTail( pPGTemp );
			pPGWeight = pPGTemp;
			
		}
	}
	
	if ( FoundEnd != TRUE ) {
		if (ErrMsgs ) AfxMessageBox("Ending SemiColon Not Found");
	}


	if ( pTempBase->m_PhyloList.GetCount() == 3 ) {
		CPhyloGenBase *pPGLast;
		pPGLast = (CPhyloGenBase *)pTempBase->m_PhyloList.RemoveTail();
		pPGCurrent = (CPhyloGenBase *)pTempBase->m_PhyloList.RemoveTail();
			
		pPGTemp = new CPhyloNode();
		pPGTemp->m_pPGParent = pTempBase;
		pPGLast->m_pPGParent = pPGTemp;
		pPGCurrent->m_pPGParent = pPGTemp;
	
		((CPhyloNode *)pPGTemp)->m_PhyloList.AddTail(pPGCurrent);
		((CPhyloNode *)pPGTemp)->m_PhyloList.AddTail(pPGLast);
	
		pTempBase->m_PhyloList.AddTail( pPGTemp );
	
	} 
	
	
	if ( !pTempBase->CheckCounts(ErrMsgs) ) {
		if ( ErrMsgs ) AfxMessageBox("Tree Not Structured Properly");
		delete pTempBase;
		return 0;
	}

	if ( m_pPGBase != NULL ) {
		delete m_pPGBase;
	}

	m_pPGBase = pTempBase;
	
	SetDepths();

	WriteString();
	
	UpdateAllViews(NULL);
	
	return 1;
}

void
CGenedocDoc::SetDepths()
{
	m_pPGBase->SetDepth( 0 );
	m_MaxDepth = 0;
	m_CallSwitch = CALLSETMAX;
	m_pPGBase->CallDocFromSeq(this);
	m_NodeNumber = 0;
	m_CallSwitch = CALLSETNUMBER;
	m_pPGBase->CallDocFromSeq(this);
	while ( m_MaxDepth >= 0 ) {
		m_pPGBase->CallDocFromDepth(this, m_MaxDepth);
		m_MaxDepth--;
	}
}

void 
CGenedocDoc::CallDocFromDepth( CObject *p )
{
	switch ( m_CallSwitch ) {
	case CALLSETOBJ:
		CallSetObj(p);
		break;
	case CALLSETNUMBER:
		CallSetNumber(p);
		break;
	}
}

void 
CGenedocDoc::CallSetNumber( CObject *p )
{
	CPhyloGenBase *pPGB = (CPhyloGenBase *)p;
	pPGB->m_Number = ++m_NodeNumber;
}

void 
CGenedocDoc::CallDocFromSeq( CObject *p )
{
	switch ( m_CallSwitch ) {
	case CALLSETMAX:
		CallSetMax(p);
		break;
	case CALLSETNUMBER:
		CallSetNumber(p);
		break;
	case CALLDRAWDEBUG:
		CallDrawDebug(p);
		break;
	}
}

void 
CGenedocDoc::CallSetMax( CObject *p )
{
	ASSERT( p->IsKindOf(RUNTIME_CLASS(CPhyloSeq)) );
	CPhyloSeq *pPS = (CPhyloSeq *)p;

	if ( pPS->m_Depth > m_MaxDepth ) {
		m_MaxDepth = pPS->m_Depth;
	}
	
}

void 
CGenedocDoc::WriteString()
{
	m_UserVars.m_ParseString.Empty();

	m_pPGBase->WriteString( m_UserVars.m_ParseString );

}


void CGenedocDoc::OnPhylodlg()
{
	
	CPhyloGenDialog tDlg;
	
	tDlg.m_ParseString = m_UserVars.m_ParseString;

	do {

		if ( tDlg.DoModal() != IDOK ) {
			return;
		}
	
	}
	while ( !ParseTree( tDlg.m_ParseString, 1 ) );

	SetModifiedFlag();

}

void CGenedocDoc::OnPhyloview()
{
	if ( m_pPGBase != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pTreeView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTreeView();
		} else {
			m_pTreeView->GetParentFrame()->ActivateFrame();
			m_pTreeView->Invalidate();
		}
	}
}

void CGenedocDoc::OnUpdatePhyloview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_pPGBase != NULL );
}
