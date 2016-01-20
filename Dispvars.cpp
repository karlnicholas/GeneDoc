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
// DisplayVars.cpp : implementation of the CDisplayVars class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayVars

IMPLEMENT_DYNCREATE(CDisplayVars, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDisplayVars serialization

void CDisplayVars::Serialize(CArchive& ar)
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
// CDisplayVars diagnostics

#ifdef _DEBUG
void CDisplayVars::AssertValid() const
{
	CObject::AssertValid();
}

void CDisplayVars::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


CDisplayVars::CDisplayVars()
{
}

CDisplayVars::~CDisplayVars()
{
}

void 
CDisplayVars::ClearVars( DisplayVars *nDisplayVars )
{
	nDisplayVars->m_Property.ClearArray();
	nDisplayVars->m_StcGroup.ClearAllData();		// Group Specific Structure Entries
	nDisplayVars->m_GroupName.Empty();
	nDisplayVars->m_GroupList.RemoveAll();	// CGeneSequence *
	nDisplayVars->m_IdentList.RemoveAll();	// CGeneSequence *
	
}

void
CDisplayVars::CopyVars( CDisplayVars *nDisplayVars, CDocument *pDC )
{

	CopyDisplayVars ( &m_DisplayVars, nDisplayVars, pDC );
}

void
CDisplayVars::CopyDisplayVars( DisplayVars *pDV, CDisplayVars *nDisplayVars, CDocument *pDC )
{

	pDV->m_GroupEnabled = nDisplayVars->GetGroupEnabled();

	pDV->m_PrimaryLevel = nDisplayVars->GetPrimaryLevel();
	pDV->m_SecondaryLevel = nDisplayVars->GetSecondaryLevel();
	pDV->m_TertiaryLevel = nDisplayVars->GetTertiaryLevel();
	
	pDV->m_ModeConserved = nDisplayVars->GetModeConserved();

	// Where do we make the call for this?
	pDV->m_LastShadeLevel = nDisplayVars->GetLastShadeLevel();

	pDV->m_ResidueMode = nDisplayVars->GetResidueMode();

	// Copy Those to these ...
	pDV->m_DiffMode = nDisplayVars->GetDiffMode();

	pDV->m_PropStyle = nDisplayVars->GetPropStyle();

	nDisplayVars->GetTitleColors ( &pDV->m_TitleTextColor, &pDV->m_TitleBkColor);

	pDV->m_ConsSubStyle = nDisplayVars->GetConsSubStyle();

	// Copy property ...
	pDV->m_Property.CopyVars( nDisplayVars->GetProperty() );

	pDV->m_StcGroup.CopyVars( nDisplayVars->GetStcGroup() );

	//
	pDV->m_GroupName = nDisplayVars->GetGroupName();

	// Clear current contents of list.
	pDV->m_GroupList.RemoveAll();

	CPtrList *listGN = nDisplayVars->GetGroupList();

	CGenedocDoc *pDoc = (CGenedocDoc *)pDC;

	POSITION tPos = listGN->GetHeadPosition();

	while ( tPos != NULL ) {
		CGeneSegment * pCGSeg = (CGeneSegment *)listGN->GetNext(tPos);

		POSITION sPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(sPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetTitle() == pCGSeg->GetTitle() ) {
				pDV->m_GroupList.AddTail ( tCGSeg );
				break;
			}

		}
	}


	// Clear current contents of list.
	pDV->m_IdentList.RemoveAll();

	listGN = nDisplayVars->GetIdentList();

	tPos = listGN->GetHeadPosition();

	while ( tPos != NULL ) {
		CGeneSegment * pCGSeg = (CGeneSegment *)listGN->GetNext(tPos);

		POSITION sPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(sPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetTitle() == pCGSeg->GetTitle() ) {
				pDV->m_IdentList.AddTail ( tCGSeg );
				break;
			}

		}
	}
	nDisplayVars->GetIdentColors ( &pDV->m_IdentTextColor, &pDV->m_IdentBkColor);
	pDV->m_IdentDisplayStyle = nDisplayVars->GetIdentDisplayStyle();


}

void
CDisplayVars::SetDisplayVars( DisplayVars *pDV, CDocument *pDC )
{

	SetGroupEnabled( pDV->m_GroupEnabled );

	SetPrimaryLevel( pDV->m_PrimaryLevel );
	SetSecondaryLevel( pDV->m_SecondaryLevel );
	SetTertiaryLevel( pDV->m_TertiaryLevel );
	
	SetModeConserved( pDV->m_ModeConserved );

	// Where do we make the call for this?
	SetLastShadeLevel( pDV->m_LastShadeLevel );

	SetResidueMode( pDV->m_ResidueMode );

	// Copy Those to these ...
	SetDiffMode( pDV->m_DiffMode );

	SetPropStyle( pDV->m_PropStyle );

	SetConsSubStyle ( pDV->m_ConsSubStyle );

	SetTitleColors ( pDV->m_TitleTextColor, pDV->m_TitleBkColor);

	// Copy property ...
	m_DisplayVars.m_Property.CopyVars( pDV->m_Property );

	m_DisplayVars.m_StcGroup.CopyVars( pDV->m_StcGroup );

	//
	SetGroupName( pDV->m_GroupName );

	CPtrList& listGN = pDV->m_GroupList;

	CGenedocDoc *pDoc = (CGenedocDoc *)pDC;

	POSITION tPos = listGN.GetHeadPosition();

	while ( tPos != NULL ) {
		CGeneSegment * pCGSeg = (CGeneSegment *)listGN.GetNext(tPos);

		POSITION sPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(sPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetTitle() == pCGSeg->GetTitle() ) {
				m_DisplayVars.m_GroupList.AddTail ( tCGSeg );
				break;
			}

		}
	}


	// IdentList
	CPtrList& listID = pDV->m_IdentList;

	tPos = listID.GetHeadPosition();

	while ( tPos != NULL ) {
		CGeneSegment * pCGSeg = (CGeneSegment *)listID.GetNext(tPos);

		POSITION sPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (sPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(sPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetTitle() == pCGSeg->GetTitle() ) {
				m_DisplayVars.m_IdentList.AddTail ( tCGSeg );
				break;
			}

		}
	}
	SetIdentColors ( pDV->m_IdentTextColor, pDV->m_IdentBkColor);
	SetIdentDisplayStyle( pDV->m_IdentDisplayStyle );


}
