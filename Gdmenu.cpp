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


void CGenedocDoc::OnGeneautoshade4() 
{
	// TODO: Add your command handler code here
	AutoShadeMenuFunc( SHADELEVEL4, m_UserVars.m_AutoShade4Structure ); 
}

void CGenedocDoc::OnUpdateGeneautoshade4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		CDisplayVars *DisplayVars = (CDisplayVars*)m_UserVars.m_DisplayVars.GetHead();
		if ( DisplayVars->GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade4Structure.IsEmpty() ) {
				pCmdUI->SetCheck( DisplayVars->GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade4Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( DisplayVars->GetLastShadeLevel() == SHADELEVEL4 );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade4Structure.IsEmpty() ) {
				pCmdUI->SetCheck( m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade4Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( m_UserVars.m_Vars.GetLastShadeLevel() == SHADELEVEL4 );
		}
	}
}

void CGenedocDoc::OnGeneautoshade3() 
{
	// TODO: Add your command handler code here
	AutoShadeMenuFunc( SHADELEVEL3, m_UserVars.m_AutoShade3Structure );

}

void CGenedocDoc::OnUpdateGeneautoshade3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		CDisplayVars *DisplayVars = (CDisplayVars*)m_UserVars.m_DisplayVars.GetHead();
		if ( DisplayVars->GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade3Structure.IsEmpty() ) {
				pCmdUI->SetCheck( DisplayVars->GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade3Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( DisplayVars->GetLastShadeLevel() == SHADELEVEL3 );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade3Structure.IsEmpty() ) {
				pCmdUI->SetCheck( m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade3Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( m_UserVars.m_Vars.GetLastShadeLevel() == SHADELEVEL3 );
		}
	}
}

void CGenedocDoc::OnGeneautoshade2() 
{
	AutoShadeMenuFunc( SHADELEVEL2, m_UserVars.m_AutoShade2Structure );
}

void CGenedocDoc::OnUpdateGeneautoshade2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		CDisplayVars *DisplayVars = (CDisplayVars*)m_UserVars.m_DisplayVars.GetHead();
		if ( DisplayVars->GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade2Structure.IsEmpty() ) {
				pCmdUI->SetCheck( DisplayVars->GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade2Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( DisplayVars->GetLastShadeLevel() == SHADELEVEL2 );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() == SHADESTRUCTURE ) {
			if ( !m_UserVars.m_AutoShade2Structure.IsEmpty() ) {
				pCmdUI->SetCheck( m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType() == m_UserVars.m_AutoShade2Structure );
			} else {
				pCmdUI->SetCheck( FALSE );
			}
		} else {
			pCmdUI->SetCheck( m_UserVars.m_Vars.GetLastShadeLevel() == SHADELEVEL2 );
		}
	}
}


void CGenedocDoc::AutoShadeMenuFunc( int SHADELEVEL, CString& strAutoShadeStructure ) 
{
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		CDisplayVars *DisplayVars = (CDisplayVars*)m_UserVars.m_DisplayVars.GetHead();
		if ( DisplayVars->GetModeConserved() == SHADESTRUCTURE ) {
			if (strAutoShadeStructure.IsEmpty() ) {
				DoGroupConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
				strAutoShadeStructure = DisplayVars->GetStcGroup().GetCurrentDataType();
			} else if ( strAutoShadeStructure == DisplayVars->GetStcGroup().GetCurrentDataType() ) {
				DoGroupConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
				strAutoShadeStructure = DisplayVars->GetStcGroup().GetCurrentDataType();
			}
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->GetStcGroup().SetCurrentDataType(strAutoShadeStructure );
			}
		} else {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetLastShadeLevel( SHADELEVEL );
			}
		}
		/*
		*/
		AutoShade( -1 );
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() == SHADESTRUCTURE ) {
			if ( strAutoShadeStructure.IsEmpty() ) {
				DoConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
				strAutoShadeStructure = m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType();
			} else if ( strAutoShadeStructure == m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType() ) { 
				DoConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
				strAutoShadeStructure = m_UserVars.m_Vars.GetStcGroup().GetCurrentDataType();
			}
			m_UserVars.m_Vars.GetStcGroup().SetCurrentDataType(strAutoShadeStructure );
		}
		AutoShade( SHADELEVEL );
	}
	SetModifiedFlag();

}

void CGenedocDoc::OnGeneclearshade()
{
	// TODO: Add your command handler code here
	SetModifiedFlag();
	// Zero flag is for clearing.
	AutoShade( SHADELEVEL0 );
	
}

void CGenedocDoc::OnUpdateGeneclearshade(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetLastShadeLevel() == SHADELEVEL0 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetLastShadeLevel() == SHADELEVEL0 );
	}
	
}

void CGenedocDoc::OnGenemodeconserved() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADECONSERVED ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADECONSERVED );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADECONSERVED ) {
			m_UserVars.m_Vars.SetModeConserved( SHADECONSERVED);
		} else {
			DoConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateGenemodeconserved(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADECONSERVED 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADECONSERVED );
	}
}


void CGenedocDoc::OnGenemodesearch() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADESEARCH ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADESEARCH );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADESEARCH ) {
			m_UserVars.m_Vars.SetModeConserved( SHADESEARCH);
		} else {
			DoConfigure( CGenedocDoc::ACTPAGESEARCH, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
	
}

void CGenedocDoc::OnUpdateGenemodesearch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADESEARCH 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADESEARCH );
	}
	
}




void CGenedocDoc::OnGenemodelogodds() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADELOGODDS ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADELOGODDS );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADELOGODDS ) {
			m_UserVars.m_Vars.SetModeConserved( SHADELOGODDS);
		} else {
			DoConfigure( CGenedocDoc::ACTPAGELOGODDS, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
	
}

void CGenedocDoc::OnUpdateGenemodelogodds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADELOGODDS  
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADELOGODDS  );
	}
	
}


void CGenedocDoc::OnGenemodequantify() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADEQUANTIFY ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADEQUANTIFY );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADEQUANTIFY ) {
			m_UserVars.m_Vars.SetModeConserved( SHADEQUANTIFY);
		} else {
			DoConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateGenemodequantify(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADEQUANTIFY 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADEQUANTIFY );
	}
}


void CGenedocDoc::OnGenemodeproperty()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADEPROPERTY ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADEPROPERTY );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEPROPERTY, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADEPROPERTY ) {
			m_UserVars.m_Vars.SetModeConserved( SHADEPROPERTY );
		} else {
			DoConfigure( CGenedocDoc::ACTPAGEPROPERTY, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateGenemodeproperty(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADEPROPERTY 
		);
	} else {
		pCmdUI->SetCheck( (m_UserVars.m_Vars.GetModeConserved() == SHADEPROPERTY ) );
	}
}

void CGenedocDoc::OnGenemodestructure()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADESTRUCTURE ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADESTRUCTURE );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADESTRUCTURE ) {
			m_UserVars.m_Vars.SetModeConserved( SHADESTRUCTURE );
//			SetModifiedFlag();
//			AutoShade( -1 );
		} else {
			DoConfigure( CGenedocDoc::ACTPAGESTRUCTURE, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
}


void CGenedocDoc::OnUpdateGenemodestructure(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADESTRUCTURE 
		);
	} else {
		pCmdUI->SetCheck( (m_UserVars.m_Vars.GetModeConserved() == SHADESTRUCTURE ) );
	}

}


void CGenedocDoc::OnGenemodephysiochem() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADEPHYSIOCHEM ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADEPHYSIOCHEM );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEHIGHLIGHTING, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADEPHYSIOCHEM ) {
			m_UserVars.m_Vars.SetModeConserved( SHADEPHYSIOCHEM );
//			SetModifiedFlag();
//			AutoShade( -1 );
		} else {
			DoConfigure( CGenedocDoc::ACTPAGEPHYSIOCHEM, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
	
}


void CGenedocDoc::OnUpdateGenemodephysiochem(CCmdUI* pCmdUI) 
{
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADEPHYSIOCHEM 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADEPHYSIOCHEM );
	}

}

void CGenedocDoc::OnGenemodesimilarity() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() != SHADEIDENTITY ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetModeConserved( SHADEIDENTITY );
			}
		} else {
			DoGroupConfigure( CGenedocDoc::ACTPAGEIDENTITY, FALSE );
		}
	} else {
		if ( m_UserVars.m_Vars.GetModeConserved() != SHADEIDENTITY ) {
			m_UserVars.m_Vars.SetModeConserved( SHADEIDENTITY );
//			SetModifiedFlag();
//			AutoShade( -1 );
		} else {
			DoConfigure( CGenedocDoc::ACTPAGEIDENTITY, FALSE );
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
	
}


void CGenedocDoc::OnUpdateGenemodesimilarity(CCmdUI* pCmdUI) 
{
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetModeConserved() == SHADEIDENTITY 
		);
	} else {
		pCmdUI->SetCheck( m_UserVars.m_Vars.GetModeConserved() == SHADEIDENTITY );
	}

}


void CGenedocDoc::OnGeneresiduemodediff()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetResidueMode() != 1 ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetResidueMode( 1 );
			}
		} else {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetResidueMode( 0 );
			}
		}
	} else {
		if ( m_UserVars.m_Vars.GetResidueMode() != 1 ) {
			m_UserVars.m_Vars.SetResidueMode(1);
		} else {
			m_UserVars.m_Vars.SetResidueMode(0);
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateGeneresiduemodediff(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetResidueMode() == 1 
		);
	} else {
		pCmdUI->SetCheck( (m_UserVars.m_Vars.GetResidueMode() == 1 ) );
	}
}


void CGenedocDoc::OnGenegroupenable() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		if ( ((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetGroupEnabled() ) {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetGroupEnabled(0);
			}
		} else {
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				DisplayVars->SetGroupEnabled(1);
			}
		}
	} else {
		if ( m_UserVars.m_Vars.GetGroupEnabled() ) {
			m_UserVars.m_Vars.SetGroupEnabled(0);
		} else {
			m_UserVars.m_Vars.SetGroupEnabled(1);
		}
	}
	SetModifiedFlag();
	AutoShade( -1 );

}

void CGenedocDoc::OnUpdateGenegroupenable(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
		if ( !m_UserVars.m_DisplayVars.GetCount() ) return;
		pCmdUI->SetCheck( 
			((CDisplayVars*)m_UserVars.m_DisplayVars.GetHead())->GetGroupEnabled() 
		);
	} else {
		pCmdUI->SetCheck(m_UserVars.m_Vars.GetGroupEnabled() );
	}
}



void CGenedocDoc::OnGeneview()
{
	// TODO: Add your command handler code here
	if ( m_pGeneView == NULL ) {
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenGeneView();
	} else {
		m_pGeneView->GetParentFrame()->ActivateFrame();
		m_pGeneView->Invalidate();
	}
	
}

void CGenedocDoc::OnGenescorepair()
{
	// TODO: Add your command handler code here
	m_UserVars.m_ScoringMethod = SCOREPAIR;

	ReScoreAll(1);

	// Flag the doc as dirty	
	SetModifiedFlag();

	UpdateAllViews(NULL);
}

void CGenedocDoc::OnUpdateGenescorepair(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ScoringMethod == SCOREPAIR );
}



void CGenedocDoc::OnGenescorelo() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	m_UserVars.m_ScoringMethod = SCORELOGODD;

	ReScoreAll(1);

	// Flag the doc as dirty	
	SetModifiedFlag();

	UpdateAllViews(NULL);

}

void CGenedocDoc::OnUpdateGenescorelo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ScoringMethod == SCORELOGODD );
}

void CGenedocDoc::OnGenescoretree()
{
	// TODO: Add your command handler code here

//	AfxMessageBox("Tree Scoring Not Yet Implemented." );
//	return;
	
	if ( m_pPGBase != NULL ) {
		if ( !m_pPGBase->CheckCounts(1) ) {
			AfxMessageBox("Tree Not Completed");
			return;
		}
	}

	m_UserVars.m_ScoringMethod = SCORETREE;
	
	ReScoreAll(1);

	// Flag the doc as dirty	
	SetModifiedFlag();

	UpdateAllViews(NULL);
}

void CGenedocDoc::OnUpdateGenescoretree(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ScoringMethod == SCORETREE );
	
}

void CGenedocDoc::OnShowtable()
{
	// TODO: Add your command handler code here
	
	CShowTableDialog tDlg;
	CString tString;
	char tBuff[10];

	if ( m_UserVars.m_ProjectType == 1 ) {
	
		tString.Empty();
		tString += "  ";
		for ( int j=0; j < 23; ++j ) {
			tString += "  ";
			tString += ProteinLocArray[j];
		}
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
		for ( int i = 0; i < 23; ++i ) {
			char Char1 = ProteinLocArray[i];
			tString.Empty();
			tString += Char1;
			tString += ":";
			for (int j=0; j < 23; ++j ) {
				char Char2 = ProteinLocArray[j];
				wsprintf( tBuff, "%3d", ScoreCurrentArray( Char1, Char2 ) );
				tString += tBuff;
			}
			// CEdit
			tString += ":";
			tString += Char1;
			tDlg.m_ShowEditString += tString;
			tDlg.m_ShowEditString += "\r\n";
		}

		tString.Empty();
		tString += "  ";
		for (int j=0; j < 23; ++j ) {
			tString += "  ";
			tString += ProteinLocArray[j];
		}
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
		
		tString.Empty();
		tString += "New Gap = ";
		wsprintf( tBuff, "%d", NewGap );
		tString += tBuff;
		tString += "  Extend Gap = ";
		wsprintf( tBuff, "%d", GapLen );
		tString += tBuff;
		tString += "  Zero Cost Distance = ";
		wsprintf( tBuff, "%d", CurrentZeroDistance );
		tString += tBuff;
		
		
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
	} else {

		tString.Empty();
		tString += "  ";
		for ( int j=0; j < 16; ++j ) {
			tString += "  ";
			tString += DNALocArray[j];
		}
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
		for ( int i = 0; i < 16; ++i ) {
			char Char1 = DNALocArray[i];
			tString.Empty();
			tString += Char1;
			tString += ":";
			for (int j=0; j < 16; ++j ) {
				char Char2 = DNALocArray[j];
				wsprintf( tBuff, "%3d", ScoreCurrentArray( Char1, Char2 ) );
				tString += tBuff;
			}
			// CEdit
			tString += ":";
			tString += Char1;
			tDlg.m_ShowEditString += tString;
			tDlg.m_ShowEditString += "\r\n";
		}

		tString.Empty();
		tString += "  ";
		for (int j=0; j < 16; ++j ) {
			tString += "  ";
			tString += DNALocArray[j];
		}
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
		
		tString.Empty();
		tString += "New Gap = ";
		wsprintf( tBuff, "%d", NewGap );
		tString += tBuff;
		tString += "  Extend Gap = ";
		wsprintf( tBuff, "%d", GapLen );
		tString += tBuff;
		tString += "  Zero Cost Distance = ";
		wsprintf( tBuff, "%d", CurrentZeroDistance );
		tString += tBuff;
		
		tDlg.m_ShowEditString += tString;
		tDlg.m_ShowEditString += "\r\n";
	}

	tDlg.DoModal();
}

void CGenedocDoc::OnGenescorenumb()
{
	// TODO: Add your command handler code here
	
	if ( m_pPGBase != NULL ) {
		if ( !m_pPGBase->CheckCounts(1) ) {
			AfxMessageBox("Tree Not Completed");
			return;
		}
	}

	m_UserVars.m_ScoringMethod = SCORENUMB;
	
	ReScoreAll(1);

	// Flag the doc as dirty	
	SetModifiedFlag();

	UpdateAllViews(NULL);
}

void CGenedocDoc::OnUpdateGenescorenumb(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ScoringMethod == SCORENUMB );
}

void CGenedocDoc::OnGenescoreinfo()
{
	// TODO: Add your command handler code here
	if ( m_TreeDebugOutput ) m_TreeDebugOutput  = 0;
	else {
		m_TreeDebugOutput = 1;
		ReScoreAll(1);
	}
}

void CGenedocDoc::OnUpdateGenescoreinfo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_TreeDebugOutput );
	
}

void CGenedocDoc::OnEditgroupprop()
{
	DoGroupConfigure();
}

void CGenedocDoc::OnGeneshadegroups()
{
	// TODO: Add your command handler code here
	// Paranoia
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
			SetStructureAlignment(&m_UserVars.m_Vars);
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPSETUP;

			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				CDisplayVars * pDV = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				SetStructureAlignment(pDV);
			}
		}
		SetModifiedFlag();

		AutoShade( -1 );	// Redisplay
	}
}

void CGenedocDoc::OnUpdateGeneshadegroups(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPSETUP );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
}

void CGenedocDoc::OnGeneshadecontrast()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONT ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPCONT;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
}

void CGenedocDoc::OnGeneshadegroupconserve()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONS ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPCONS;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
	
}

void CGenedocDoc::OnUpdateGeneshadecontrast(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPCONT );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
	
}

void CGenedocDoc::OnUpdateGeneshadegroupconserve(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPCONS );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
}



void CGenedocDoc::OnGenegroupsgconx() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONSX ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPCONSX;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
	
}

void CGenedocDoc::OnUpdateGenegroupsgconx(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPCONSX );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
	
}

void CGenedocDoc::OnGeneshadecontrastnogap()
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPCONTNG ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPCONTNG;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
}

void CGenedocDoc::OnUpdateGeneshadecontrastnogap(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPCONTNG );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
}


void CGenedocDoc::OnGroupshadepcr() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPCR ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPPCR;
		}
		m_UsePCRSim = 0;
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}

}

void CGenedocDoc::OnUpdateGroupshadepcr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPPCR );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
	
}

void CGenedocDoc::OnGroupshadepcrsim() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPCRSIM ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPPCRSIM;
		}
		m_UsePCRSim = 1;
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
}

void CGenedocDoc::OnUpdateGroupshadepcrsim(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPPCRSIM );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}

}

void CGenedocDoc::OnGeneshadegroupphyschem() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPPHYSIOCHEM;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}

}

void CGenedocDoc::OnUpdateGeneshadegroupphyschem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPPHYSIOCHEM );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}
	
}

void CGenedocDoc::OnGeneshadegroupdna() 
{
	// TODO: Add your command handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		if ( m_UserVars.m_GroupDisplayMode == GROUPDISPDNASET ) {
			m_UserVars.m_GroupDisplayMode = GROUPDISPNONE;
		} else {
			m_UserVars.m_GroupDisplayMode = GROUPDISPDNASET;
		}
		SetModifiedFlag();
		AutoShade( -1 );	// Redisplay
	}
	
}

void CGenedocDoc::OnUpdateGeneshadegroupdna(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( m_UserVars.m_DisplayVars.GetCount() ) {
		pCmdUI->SetCheck( m_UserVars.m_GroupDisplayMode == GROUPDISPDNASET );
		pCmdUI->Enable( TRUE );

	} else {
		pCmdUI->SetCheck( FALSE );
		pCmdUI->Enable( FALSE );
	}

}

void CGenedocDoc::OnStcloadembl() 
{
	// TODO: Add your command handler code here
	
	BeginWaitCursor();
	
	m_UserVars.m_Stc.LoadSCMIEMBL();
	
	EndWaitCursor();

}

void CGenedocDoc::OnUpdateStcloadembl(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( pGSFiller != NULL ) {

		pCmdUI->SetCheck( m_UserVars.m_Stc.SCMIEMBLLoaded() != 0 );
		
	}
}

void CGenedocDoc::OnStcloadpsdb() 
{
	// TODO: Add your command handler code here
	
	BeginWaitCursor();
	
	m_UserVars.m_Stc.LoadSCMIPSDB();
	
	EndWaitCursor();

}

void CGenedocDoc::OnUpdateStcloadpsdb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( pGSFiller != NULL ) {

		pCmdUI->SetCheck( m_UserVars.m_Stc.SCMIPSDBLoaded() != 0 );
		
	}

}


void CGenedocDoc::OnStcloadpdb() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor();
	
	m_UserVars.m_Stc.LoadSCMIPDB();
	
	EndWaitCursor();

	
}

void CGenedocDoc::OnUpdateStcloadpdb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( pGSFiller != NULL ) {

		pCmdUI->SetCheck( m_UserVars.m_Stc.SCMIPDBLoaded() != 0 );
		
	}
	
}

void CGenedocDoc::OnStclearall() 
{
	// TODO: Add your command handler code here
	m_UserVars.m_Stc.ClearAll();
	    
	m_UserVars.m_Vars.GetStcGroup().ClearAllData();

	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		DisplayVars->GetStcGroup().ClearAllData();
	}

	m_UserVars.m_StcDefUser.RemoveAll();

	m_UserVars.m_AutoShade4Structure.Empty();
	m_UserVars.m_AutoShade3Structure.Empty();
	m_UserVars.m_AutoShade2Structure.Empty();

}


void CGenedocDoc::OnGenedstatview()
{
	// TODO: Add your command handler code here
	if ( m_pPGBase != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pDStatView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenDStatView();
		} else {
			m_pDStatView->GetParentFrame()->ActivateFrame();
			m_pDStatView->Invalidate();
		}
	}
}

void CGenedocDoc::OnUpdateGenedstatview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL && m_pDStatView != NULL );
}


void CGenedocDoc::OnGenegelview() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pGelView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenGelView();
		} else {
			m_pGelView->GetParentFrame()->ActivateFrame();
			m_pGelView->Invalidate();
		}
	}
}

void CGenedocDoc::OnUpdateGenegelview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}

void CGenedocDoc::OnSummaryview()
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pSummaryView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenSummaryView();
		} else {
			m_pSummaryView->GetParentFrame()->ActivateFrame();
			m_pSummaryView->Invalidate();
		}
	}
}

void CGenedocDoc::OnUpdateSummaryview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}

void CGenedocDoc::OnFileimport() 
{
	// TODO: Add your command handler code here
	SequenceImport();

	AutoShade(-1);
}

void CGenedocDoc::OnFileexport() 
{
	// TODO: Add your command handler code here
	SequenceExport();
}


void CGenedocDoc::OnPlotstatdstat() 
{
	// TODO: Add your command handler code here
	DStatStat(0);
	
}

void CGenedocDoc::OnPlotfavsubs() 
{
	// TODO: Add your command handler code here
	DStatStat(1);
	
}

void CGenedocDoc::OnPlotgroup() 
{
	// TODO: Add your command handler code here
	DStatStat(2);

}

void CGenedocDoc::OnPlotgroupfav() 
{
	// TODO: Add your command handler code here
	DStatStat(3);
	
}

void CGenedocDoc::OnGeneeditseq() 
{
	// TODO: Add your command handler code here
	CSeqDialog tDlg;

	tDlg.pDoc = this;

	tDlg.DoModal();

//	if ( tDlg.m_Modify ) {
//		ResetTree();
//	}

	AutoShade( -1, 1 );	// Rescore and redispay.

}

void CGenedocDoc::OnGeneloadini()
{

	int sType = m_UserVars.m_ProjectType;

	GetIniDefaults();
	
	m_UserVars.m_ProjectType = sType;
	
	AutoShade( -1, 1 );	// Rescore and Redisplay
	
	SetModifiedFlag();
}

void CGenedocDoc::OnTitlingf()
{
	CTitlingFDialog tDlg;
//	int fFirst = 1;
	CPtrList	tHeaderList;
	
	
	if ( pGSFiller != NULL ) {
		if ( !pGSFiller->SegHeaderList.IsEmpty() ) {

			POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
			while ( tPos != NULL ) {

				CString *cStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
				// Looking for Master Checksum location ...

				if ( cStr->Find("GENEDOC:") != -1 ) {
					break;
				}
				if ( cStr->Find("GDC ") != -1 ) {
					break;
				}
				if ( cStr->Find("..") != -1 && cStr->Find("MSF:") != -1) {
					break;
				}
				int Len = cStr->GetLength();
				char *pc = cStr->GetBuffer(Len );
				pc += Len - 1;
				while ( *pc == '\r' || *pc == '\n' ) *pc-- = 0;
				cStr->ReleaseBuffer();
//				if ( fFirst ) {
//					tDlg.m_FirstLine = *cStr;
//					fFirst = 0;
//				} else {
					// Got a CEdit object here
					tDlg.m_CommentText += *cStr;
					tDlg.m_CommentText += "\r\n";
//				}
			}
		}
		
		tDlg.m_Program = m_UserVars.m_TitleProgram;
		tDlg.m_ExtendGap = m_UserVars.m_TitleExtendGap;
		tDlg.m_OpenGap = m_UserVars.m_TitleOpenGap;
		tDlg.m_ScoreMatrix = m_UserVars.m_TitleScoreMatrix;

		tDlg.m_CTChanged = 0;
		tDlg.m_ICChanged = 0;

		if ( tDlg.DoModal() != IDOK ) {
			return;
		}
		
		if ( tDlg.m_CTChanged ) {
			//Remove old comments
			CString *cStr;
//			fFirst = 1;
			while ( !pGSFiller->SegHeaderList.IsEmpty() ) {
				cStr = (CString *)pGSFiller->SegHeaderList.RemoveHead();

				if ( cStr->Find("GDC ") != -1 ) {
					pGSFiller->SegHeaderList.AddHead(cStr);
					break;
				}
				if ( cStr->Find("GENEDOC:") != -1 ) {
					pGSFiller->SegHeaderList.AddHead(cStr);
					break;
				}
				if ( cStr->Find("..") != -1 && cStr->Find("MSF:") != -1) {
					pGSFiller->SegHeaderList.AddHead(cStr);
					break;
				}
//				if ( fFirst ) {
//					tHeaderList.AddTail ( new CString ( *cStr ) );
//					fFirst = 0;
//				} else {
//					// Got a CString object here
					delete cStr;
//				}
			}
			
			int LineLoc;
			while ( (LineLoc = tDlg.m_CommentText.Find("\r\n")) != -1 ) {
				
				tHeaderList.AddTail( new CString ( tDlg.m_CommentText.Left( LineLoc )) );

				tDlg.m_CommentText = tDlg.m_CommentText.Right ( tDlg.m_CommentText.GetLength() - LineLoc - 2 );
			}
			if ( !tDlg.m_CommentText.IsEmpty() ) {

				tHeaderList.AddTail( new CString ( tDlg.m_CommentText ) );
			}

			// Copy tHeaderList to SegHeaderList
			while ( !tHeaderList.IsEmpty() ) {
				pGSFiller->SegHeaderList.AddHead( tHeaderList.RemoveTail() );
			}
			
			SetModifiedFlag();
			
		}

		if ( tDlg.m_ICChanged ) {
			m_UserVars.m_TitleProgram = tDlg.m_Program;
			m_UserVars.m_TitleExtendGap = tDlg.m_ExtendGap;
			m_UserVars.m_TitleOpenGap = tDlg.m_OpenGap;
			m_UserVars.m_TitleScoreMatrix = tDlg.m_ScoreMatrix;
			
			SetModifiedFlag();
		}
	}
}


void CGenedocDoc::OnPlotfrag() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {

		PlotUniqueFrags();
		
		if ( m_pDStatView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenDStatView();
		} else {
			m_pDStatView->GetParentFrame()->ActivateFrame();
			m_pDStatView->Invalidate();
		}
	}	
}

BOOL CGenedocDoc::CheckMatch( char cF, char cS)
{
	BOOL match = FALSE;

	if ( m_UserVars.m_ProjectType > 1 ) {
		switch( cF ) {
		case 'A': match = (cS == 'A'); break;
		case 'G': match = (cS == 'G'); break;
		case 'C': match = (cS == 'C'); break;
		case 'T': match = (cS == 'T'); break;
		case 'U': match = (cS == 'U'); break;
		case 'Y': match = (cS == 'C' || cS == 'T' || cS == 'U' ); break;
		case 'R': match = (cS == 'A' || cS == 'G' ); break;
		case 'W': match = (cS == 'A' || cS == 'T' || cS == 'U' ); break;
		case 'S': match = (cS == 'C' || cS == 'G' ); break;
		case 'K': match = (cS == 'T' || cS == 'U' || cS == 'G' ); break;
		case 'M': match = (cS == 'C' || cS == 'A' ); break;
		case 'B': match = (cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'D': match = (cS == 'A' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'H': match = (cS == 'A' || cS == 'C' || cS == 'T' || cS == 'U' ); break;
		case 'V': match = (cS == 'A' || cS == 'C' || cS == 'G' ); break;
		case 'N': match = (cS == 'A' || cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'X': match = (cS == 'A' || cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		}
	} else {
		if ( cF == 'X' && ( cS >= 'A' && cS <= 'Z') ) match = TRUE;
		else if ( cF == cS ) match = TRUE;
	}
	return match;
}

int CGenedocDoc::OnFind(CView *pView ) 
{
	if ( pGSFiller == NULL ) return 0;
	if ( m_pFS.FindStr.GetLength() == 0 ) return 0;

	ShadeSegStc *pSSArr = NULL;
	int i;
	BOOL Matched = 0;
	BOOL Found = 0;


TRY {

	int iSegCount = 0;
	pSSArr = new ShadeSegStc[pGSFiller->SegDataList.GetCount()];

		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( !tCGSeg->GetExportFlag() ) {
			continue;
		}
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			pSSArr[iSegCount].pCGSeg = tCGSeg;
			pSSArr[iSegCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			if ( pSSArr[iSegCount].pGeneStor == NULL) AfxThrowMemoryException();
			iSegCount++;
		}
	}

	CGenedocView* pGEView = (CGenedocView*)pView;

	UINT XPosition;
	DWORD YPosition;

	pGEView->m_MyCaret.GetPosition(&XPosition, &YPosition);

	DWORD dwAlignLength = ((CGeneSegment *)pGSFiller->SegDataList.GetHead())->GetTextLength();
	DWORD dwAlignComp;
	DWORD dwCaretColPos;
	int iDir;

	switch ( m_pFS.FindFrom ) {
	case 0:	// Find Foward 
		dwAlignComp = ((CGeneSegment *)pGSFiller->SegDataList.GetHead())->GetTextLength();
		dwCaretColPos = pGEView->ColPosFromCaret( XPosition, YPosition );
		iDir = 1;
		break;
	case 1:	// Find Reverse
		dwAlignComp = 0;
		dwCaretColPos = pGEView->ColPosFromCaret( XPosition, YPosition );
		iDir = -1;
		break;
	case 2: // Find From Begin
		dwAlignComp = ((CGeneSegment *)pGSFiller->SegDataList.GetHead())->GetTextLength();
		dwCaretColPos = 0;
		iDir = 1;
		break;
	case 3: // Shade All .. 
		dwAlignComp = ((CGeneSegment *)pGSFiller->SegDataList.GetHead())->GetTextLength();
		dwCaretColPos = 0;
		iDir = 1;
		break;
	}

	DWORD tCount;
	for ( tCount = dwCaretColPos; tCount != dwAlignComp; tCount += iDir ) {
		for ( i= m_pFS.PrevSeq + 1; i < iSegCount; ++i ) {
			char tChar = toupper ( pSSArr[i].pGeneStor[tCount].CharGene );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) continue;
// Start of Find Routine ...

			DWORD dwSPos = tCount;
			DWORD dwSMax = m_pFS.FindStr.GetLength() + m_pFS.InsDel;
			CString SeqString;
			CString FindString;
//			if ( dwSMax > dwAlignLength ) dwSMax = dwAlignLength;
			for ( ; dwSPos < dwAlignLength; ++dwSPos ) {
				tChar = toupper ( pSSArr[i].pGeneStor[dwSPos].CharGene );
				if ( !(tChar >= 'A' && tChar <= 'Z') ) continue;
				SeqString += tChar;
				if ( --dwSMax == 0 ) break;
			}
			// Convert Find String to Upper case.
			for ( int j = 0; j < m_pFS.FindStr.GetLength(); ++j ) {
				FindString += "" + toupper(m_pFS.FindStr[j]);
			}
// Insert Find Code ..

			CDWordArray	arrFind;
			// Fill out our find array.
			for ( int fc = 0; fc < FindString.GetLength(); ++fc ) {
				for ( int sc = 0; sc < SeqString.GetLength(); ++sc ) {
					if ( CheckMatch( FindString[fc], SeqString[sc]) ) {
						DWORD tadd = (fc << 16) + sc;
						arrFind.Add(tadd);
					}
				}
			}

			CWordArray	arrFRes;
			CWordArray	arrSRes;

			arrFRes.SetSize(FindString.GetLength());
			arrSRes.SetSize(SeqString.GetLength());

			for (int fc = 0; fc < FindString.GetLength(); ++fc ) {
				arrFRes[fc] = -1;
			}

			for ( int sc = 0; sc < SeqString.GetLength(); ++sc ) {
				arrSRes[sc] = -1;
			}

			for ( int nins = 0; nins <= m_pFS.InsDel; ++nins ) {
				for ( int ma = 0; ma < arrFind.GetSize(); ++ma ) {
					int fl = HIWORD(arrFind[ma]);
					int sl = LOWORD(arrFind[ma]);
					int diff;
					if ( fl > sl ) {
						diff = fl - sl;
					} else {
						diff = sl - fl;
					}
					if ( diff > nins ) continue;
					if ( arrFRes[fl] != (WORD)-1 ) continue;
					if ( arrSRes[sl] != (WORD)-1 ) continue;
					// Check Order ..
					int nogo = 0;
					for ( int tml = 0; tml < arrSRes.GetSize(); ++tml ) {
						if ( arrSRes[tml] >= sl && (arrSRes[tml] != (WORD)-1) ) nogo = 1;
					}
					if ( nogo ) continue;
					arrFRes[fl] = sl;
					arrSRes[sl] = fl;
				}
			}

			// Determine number of mistaches and ins/dels
			int CurrDiff = 0;

			int mismatch = 0;
			int ins = 0;
			int del = 0;

			for (int fc = 0; fc < arrFRes.GetSize(); ++fc ) {
				if ( arrFRes[fc] == (WORD)-1 ) {
					mismatch++;
					continue;
				}
				int fl = fc;
				int sl = arrFRes[fc];
				int diff = sl - fl;
				if ( diff != CurrDiff ) {
					if ( diff > 0 ) {
						ins += diff;
					} else {
						del += 0 - diff;
					}
					CurrDiff = diff;
				}
			}
			if ( del > mismatch ) {
				mismatch = 0;
			} else {
				mismatch -= del;
			}
			int insdel = ins + del;

			if ( m_pFS.MisMatch >= mismatch && m_pFS.InsDel >= insdel ) {
				// See if Shading instead ..
				Found = 1;
				if ( m_pFS.FindFrom == 3 ) {
					dwSPos = tCount;
					dwSMax = arrSRes.GetSize();
//					if ( dwSMax > dwAlignLength ) dwSMax = dwAlignLength;
					int sridx = 0;
					for ( ; dwSPos < dwAlignLength; ++dwSPos ) {
						tChar = toupper ( pSSArr[i].pGeneStor[dwSPos].CharGene );
						if ( !(tChar >= 'A' && tChar <= 'Z') ) continue;
						if ( arrSRes[sridx] != (WORD)-1 ) {
							pSSArr[i].pGeneStor[dwSPos].TextColor = m_pFS.rgbText;
							pSSArr[i].pGeneStor[dwSPos].BackColor = m_pFS.rgbBack;
						}
						sridx++;
						if ( --dwSMax == 0 ) break;
					}
					
				} else {
					Matched = 1;
				}
			}


// End of Find routine
// Be sure 'i' is set if matched ..
			if ( Matched == 1 ) break;
		}
		m_pFS.PrevSeq = -1;
		if ( Matched == 1 ) break;
	}

	if ( Matched ) {
		pGEView->CaretPosFromColSeq( tCount, pSSArr[i].pCGSeg );
		m_pFS.PrevSeq = i;
	}

	delete pSSArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
		}
	}
} 
CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	if ( pSSArr != NULL ) delete pSSArr;
	return 0;
}
END_CATCH
	return Found;
}

/*
// Set Weight, ident = 1, non-ident = -1, gap = -2
// Set ExtndG to large negative for no Ins/Del, ie -3 or -10 * length of Find
// Look for score Length of Find - ( 2* MisMatches )
//			long ExtndG = -10 * FindString.GetLength();
			long ExtndG = -2;

			long *FitSim = new long[SeqString.GetLength()+1];
			memset ( FitSim, 0, sizeof(long) * SeqString.GetLength() );

			for ( int F = 1; F <= FindString.GetLength(); ++F ) {
				int Fimjm = FitSim[0];
				FitSim[0] = F * ExtndG;
				for ( int S = 1; S <= SeqString.GetLength(); ++S ) {
					int SM = S - 1;
					int GapF = FitSim[S] + ExtndG;
					int GapS = FitSim[SM] + ExtndG;
					if ( F >= FindString.GetLength() ) GapS = LONG_MIN;
		//			NextFS = Fimjm + Weight( FindString[i-1], SeqString[j-1] );
					int NextFS = Fimjm + ( FindString[F-1] == SeqString[S-1] ? 1 : -1);
					Fimjm = FitSim[S];
					FitSim[S] = max( NextFS, max( GapF, GapS ) );
				}
			}

			delete [] FitSim;

*/


void CGenedocDoc::OnCopycons() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;

	// CWnd
	if ( !OpenClipboard(AfxGetMainWnd()->m_hWnd) ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	BeginWaitCursor(); // Let em know
	

	int ConsensusCount = -1;
	int tRC = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
	CGeneSegment *pConsSeg = NULL;

	if ( m_UserVars.m_ConsensusLine == 0 ) {
		// Use Top Consensus Row
		ConsensusCount = 1;
	} else if ( m_UserVars.m_ConsensusLine == 1 ) {
		// Use Bottom Consensus Row
		ConsensusCount = tRC - 1;
	}

	if ( ConsensusCount == -1 ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "No Consensus Line!" );
		return;
	}

	int i = 0;
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( i == ConsensusCount ) {
			pConsSeg = tCGSeg;
			break;
		}
		i++;
	}

	if ( pConsSeg == NULL ) {
		EndWaitCursor(); // Let em know
		return;
	}

	DWORD Size = pConsSeg->GetTextLength();

	CString BuildString;

	GeneStor *pc = (GeneStor *)GlobalLock(pConsSeg->GetTextHandle());
	if ( pc == NULL ) {
		AfxMessageBox("GetConsensus:GlobalLock:Fail:2");
		return;
	}

	BuildString = ">" + GetTitle().SpanExcluding(".") + "\r\n";

	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = pConsSeg->GetTextLength();

	while ( (CurPos + 60L) < Len ) {

		// Build data blocks
		GeneStor *tgs = pc + CurPos;
		for ( int j = 0; j < 60; ++j ) {
			char tChar = toupper( tgs->CharDisplay );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				DataBlock[j] = tgs->CharDisplay;
			} else {
				DataBlock[j] = '-';
			}

			tgs++;
		}
		DataBlock[60] = 0;

		BuildString += CString(DataBlock) + "\r\n";

		CurPos += 60L;

	};
	
	// Do Last set of lines 

	Len = pConsSeg->GetTextLength() - CurPos;
	

	// Build data blocks
	GeneStor *tgs = pc + CurPos;
	for ( unsigned int j = 0; j < Len; ++j ) {
		char tChar = toupper( tgs->CharDisplay );
		if ( tChar >= 'A' && tChar <= 'Z' ) {
			DataBlock[j] = tgs->CharDisplay;
		} else {
			DataBlock[j] = '-';
		}
		tgs++;
	}
	DataBlock[Len] = 0;

	BuildString += CString(DataBlock) + "\r\n";
	

	GlobalUnlock(pConsSeg->GetTextHandle());
		
	HANDLE hnSeg = GlobalAlloc(GMEM_DDESHARE, BuildString.GetLength() + 1 );
	if ( hnSeg == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalAlloc:Fail:1");
		return;
	}

	char *pn = (char *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalLock:Fail:1");
		return;
	}

	memcpy ( pn, (const char *)BuildString, BuildString.GetLength() );
	pn[BuildString.GetLength()] = 0;

	GlobalUnlock(hnSeg);
	
	if ( SetClipboardData ( CF_TEXT, hnSeg ) == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "SetClipboardData Fails" );
	}
	
	if ( !CloseClipboard() ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}
	
	EndWaitCursor(); // Let em know
	
}

void CGenedocDoc::OnUpdateCopycons(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
	
}


void CGenedocDoc::OnConsprosite() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;

	// CWnd
	if ( !OpenClipboard(AfxGetMainWnd()->m_hWnd) ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	BeginWaitCursor(); // Let em know
	

	CString PathName;

	if ( pGSFiller == NULL ) {
		return;
	}
	

	unsigned long Score = 0;


//	DWORD SegLength = ((CGeneSegment*)pGSFiller->SegDataList.GetHead())->GetTextLength();

	DWORD StartRange = 0L;
	DWORD EndRange = ((CGeneSegment*)pGSFiller->SegDataList.GetHead())->GetTextLength() - 1;
	
	DWORD iSeqCount = 0;
	ShadeSegStc *pSSArr = new ShadeSegStc[pGSFiller->SegDataList.GetCount()];
	
	CGeneSegment *tCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			pSSArr[iSeqCount].pCGSeg = tCGSeg;
			pSSArr[iSeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			if ( pSSArr[iSeqCount].pGeneStor == NULL) AfxThrowMemoryException();
			iSeqCount++;
		}
	}
	


	CString BuildString;
//	BuildString = ">" + GetTitle().SpanExcluding(".") + "\r\n";

	
	DWORD CurPos = 0;
	int first = 1;
	int dArr[26];
	int found = 0;
		
	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		if ( !first && found) BuildString += "-";
		first = 0;

		found = 0;

		for ( DWORD di=0; di < iSeqCount; ++di ) {
			char tChar = toupper ( pSSArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				dArr[tChar - 'A'] = 1;
			}
		}
		for ( int i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'V':
			case 'W':
			case 'Y':
				if ( dArr[i] ) found++;
				break;
			}
		}
		if ( found == 1 ) {
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] ) BuildString += "" + i + 'A';
					break;
				}
			}
		} else if ( found == 20 ) {
			BuildString += "X";
		} else if ( found > 10 ) {
			BuildString += "{";
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] == 0 ) BuildString += "" + i + 'A';
					break;
				}
			}
			BuildString += "}";
		} else if ( found <= 10 && found > 0 ) {
			BuildString += "[";
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] ) BuildString += "" +  i + 'A';
					break;
				}
			}
			BuildString += "]";
		}
	}
	BuildString += ".";

	delete pSSArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
		}
	}
	
	HANDLE hnSeg = GlobalAlloc(GMEM_DDESHARE, BuildString.GetLength() + 1 );
	if ( hnSeg == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalAlloc:Fail:1");
		return;
	}

	char *pn = (char *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalLock:Fail:1");
		return;
	}

	memcpy ( pn, (const char *)BuildString, BuildString.GetLength() );
	pn[BuildString.GetLength()] = 0;

	GlobalUnlock(hnSeg);
	
	if ( SetClipboardData ( CF_TEXT, hnSeg ) == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "SetClipboardData Fails" );
	}
	
	if ( !CloseClipboard() ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}
	
	EndWaitCursor(); // Let em know
	
}


void CGenedocDoc::OnUpdateConsprosite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );

}

void CGenedocDoc::OnShowmanshade()
{
	m_UserVars.m_ShowManShade = !m_UserVars.m_ShowManShade;
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateShowman(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowManShade );

}

void CGenedocDoc::OnShowcomments()
{
	m_UserVars.m_ShowComments = !m_UserVars.m_ShowComments;
	AutoShade( -1 );
}

void CGenedocDoc::OnUpdateShowcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowComments );

}

void CGenedocDoc::OnClearcomments() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			tCGSeg->ClearComments();
		}
	}

	SetModifiedFlag();
	AutoShade( -1 );
	
}

void CGenedocDoc::OnClearmanshade() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			tCGSeg->ClearShades();
		}
	}

	SetModifiedFlag();
	AutoShade( -1 );
	
}


void CGenedocDoc::OnSelectarrseq() 
{
	// TODO: Add your command handler code here
	CSelArrSeq tDlg;
	tDlg.pDoc = this;
	tDlg.DoModal();
	UpdateAllViews(NULL);
}

void CGenedocDoc::OnRescoreall() 
{
	// TODO: Add your command handler code here
	ReScoreAll(1);	
	UpdateAllViews(NULL);
}


void CGenedocDoc::OnComplimentsel() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			if ( tCGSeg->GetArrangeFlag() ) {
				tCGSeg->SetArrangeFlag(0);
			} else {
				tCGSeg->SetArrangeFlag(1);
			}
		}
	}

	UpdateAllViews(NULL);
	
}

void CGenedocDoc::OnGenereportview() 
{
	
	if ( m_pTextView == NULL ) {
	
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
	} else {

		m_pTextView->GetParentFrame()->ActivateFrame();
		m_pTextView->Invalidate();
	}
	
}

void CGenedocDoc::OnGenescorefile() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
	
		WriteScoreFile( PathName );
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {

			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();

		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	
		EndWaitCursor();
	}
}


void CGenedocDoc::OnUpdateGenescorefile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}


void CGenedocDoc::OnGenestatfile() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {

		BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
	
		WriteStatFile( PathName );
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();
		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	
		EndWaitCursor();
	}
}

void CGenedocDoc::OnUpdateGenestatfile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}


void CGenedocDoc::OnSrchrepview() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {

		// BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
	
		if ( !RebaseReport(PathName) ) return;
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();
		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	
		EndWaitCursor();
	}
}

void CGenedocDoc::OnLogoddsview() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {

		// BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
	
		if ( !LogOddsReport(PathName) ) return;
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();
		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	
		EndWaitCursor();
	}
	
}

void CGenedocDoc::OnUpdateLogoddsview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
	
}


void CGenedocDoc::DNAFreqRep(DWORD StartRange, DWORD EndRange) 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL && m_UserVars.m_ProjectType ) {

		// BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
		double dArr[26];
		char outbuf[256];

		BeginWaitCursor();


	TRY {

		CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );


		BeginWaitCursor(); // Let em know


		int RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
		
		ShadeSegStc *pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here


		int SeqCount = 0;

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
			// Lock it down
			pSegArr[SeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			pSegArr[SeqCount].pCGSeg = tCGSeg;
			SeqCount++;
		}


		if (m_UserVars.m_ProjectType == 1 ) {

				
			for ( int di=0; di < SeqCount; ++di ) {
	
				memset ( dArr, 0, sizeof(dArr) );

				for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {
					char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						dArr[tChar - 'A'] += 1.0;
					}
				}

				double Total = 0.0;
				for ( int i=0; i < 26; ++i ) {
					Total += dArr[i];
				}

				_snprintf ( outbuf, sizeof(outbuf), "%-10s ", pSegArr[di].pCGSeg->GetTitle() );
				oFile.WriteString( outbuf );

				if ( Total == 0.0 ) {
					_snprintf ( outbuf, sizeof(outbuf), "\n");
					oFile.WriteString( outbuf );
					continue;
				}
				int crc = 0;
				for (int i=0; i < 26; ++i ) {
					switch (i + 'A') {
					case 'A':
					case 'C':
					case 'D':
					case 'E':
					case 'F':
					case 'G':
					case 'H':
					case 'I':
					case 'K':
					case 'L':
					case 'M':
					case 'N':
					case 'P':
					case 'Q':
					case 'R':
					case 'S':
					case 'T':
					case 'V':
					case 'W':
					case 'Y':
						{
							
							if ( (crc % 5) == 0 && crc != 0) {
								_snprintf ( outbuf, sizeof(outbuf), "\n%-10s ", pSegArr[di].pCGSeg->GetTitle() );
								oFile.WriteString( outbuf );
							}
							crc++;
							double Score = dArr[i] / Total;
							_snprintf ( outbuf, sizeof(outbuf), " %c = %5.4lf", i + 'A', Score );
							oFile.WriteString( outbuf );
							break;
						}
					}
				}
				_snprintf ( outbuf, sizeof(outbuf), "\n\n");
				oFile.WriteString( outbuf );
			}

		} else {

//

			for ( int di=0; di < SeqCount; ++di ) {
				memset ( dArr, 0, sizeof(dArr) );

				for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

					char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						switch ( tChar ) {
						case 'A':
						case 'C':
						case 'G':
						case 'T':
							dArr[tChar - 'A'] += 1.0;
							break;
						case 'U':
							dArr['T' - 'A'] += 1.0;
							break;
						case 'Y':
							dArr['C' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'R':
							dArr['A' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'W':
							dArr['A' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'S':
							dArr['C' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'K':
							dArr['T' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'M':
							dArr['C' - 'A'] += 1.0;
							dArr['A' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'B':
							dArr['C' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'D':
							dArr['A' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'H':
							dArr['A' - 'A'] += 1.0;
							dArr['C' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'V':
							dArr['A' - 'A'] += 1.0;
							dArr['C' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'N':
							dArr['A' - 'A'] += 1.0;
							dArr['C' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						case 'X':
							dArr['A' - 'A'] += 1.0;
							dArr['C' - 'A'] += 1.0;
							dArr['G' - 'A'] += 1.0;
							dArr['T' - 'A'] += 1.0;
//							dArr['N' - 'A'] += 1.0;
							break;
						}
					}
				}


				double Total = 0.0;
				for ( int i=0; i < 26; ++i ) {
					Total += dArr[i];
				}

				_snprintf ( outbuf, sizeof(outbuf), "%-10s ", pSegArr[di].pCGSeg->GetTitle() );
				oFile.WriteString( outbuf );

				if ( Total == 0.0 ) {
					_snprintf ( outbuf, sizeof(outbuf), "\n");
					oFile.WriteString( outbuf );
					continue;
				}

				for (int i=0; i < 26; ++i ) {
					switch (i + 'A') {
					case 'A':
					case 'C':
					case 'G':
					case 'T':
						{
							double Score = dArr[i] / Total;
							_snprintf ( outbuf, sizeof(outbuf), " %c = %5.4lf", i + 'A', Score );
							oFile.WriteString( outbuf );
							break;
						}
					}
				}
				double Score = dArr['N' - 'A'] / Total;
				double ttot = dArr['G' - 'A'] + dArr['C' - 'A'] + dArr['T' - 'A'] + dArr['A' - 'A'];
				double ScoreGC = (dArr['G' - 'A'] + dArr['C' - 'A']) / ttot;
				_snprintf ( outbuf, sizeof(outbuf), " (N = %5.4lf GC = %5.4lf)\n", Score, ScoreGC );
				oFile.WriteString( outbuf );
			}
		}

//		

		oFile.Close();


		for ( int i=0; i < SeqCount; ++i ) {
			GlobalUnlock( pSegArr[i].pCGSeg->GetTextHandle() );
		}

		delete [] pSegArr;


	} 
	CATCH (CFileException, e ) {
		if( e->m_cause == CFileException::fileNotFound )
			AfxMessageBox( "File Not Found Error" );
		else
			AfxMessageBox( "File Error" );

		return;
	}
	AND_CATCH (CMemoryException, e ) {
		AfxMessageBox( "Memory Exception" );
		return;
	}
	END_CATCH

		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	}


}


void CGenedocDoc::OnManshaderep() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
	
		WriteManRepFile( PathName );
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {

			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();

		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	
		EndWaitCursor();
	}
}


void CGenedocDoc::OnUpdateManshaderep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
	
}


void CGenedocDoc::ReplaceFromProj(DWORD StartPos, DWORD EndPos) 
{
	// TODO: Add your command handler code here

	int count = 0;
	CGenedocDoc *poDoc;
	CMultiDocTemplate* pMDTmpl = ((CGenedocApp *)AfxGetApp())->m_pGenedocTemplate;

	POSITION dPos = pMDTmpl->GetFirstDocPosition( );
	while ( dPos != NULL ) {
		poDoc = (CGenedocDoc*)pMDTmpl->GetNextDoc(dPos);
		if ( poDoc == this ) continue;
		count++;
		break;
	}

	if ( !count ) {
		AfxMessageBox("No Other Project To Select From!");
		return;
	}
	
	CSelProject pDlg;
	pDlg.pDoc = this;
	if ( pDlg.DoModal() != IDOK ) return;

	poDoc = pDlg.poDoc;

	if ( poDoc == NULL ) {
		AfxMessageBox("No Other Project Selected!");
		return;
	}

	CGSFiller *poFiller = poDoc->pGSFiller;
	if ( poFiller == NULL ) return;

	if ( pGSFiller == NULL ) return;

	CGeneSegment *pCGSeg;
	CGeneSegment *poCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		POSITION pPos = poFiller->SegDataList.GetHeadPosition();
		while (pPos != NULL ) {
			poCGSeg = (CGeneSegment *)poFiller->SegDataList.GetNext(pPos);
			if ( poCGSeg->GetStyle() != LINESEQUENCE ) continue;
			if ( pCGSeg->GetTitle() == poCGSeg->GetTitle() ) {
				pCGSeg->ReplaceWith( StartPos, EndPos, poCGSeg->GetTextHandle(), poCGSeg->GetTextLength() );
				break;
			}
		}
	}

	ReSizeRows();

	AutoShade(-1);
	SetModifiedFlag();
}

void CGenedocDoc::OnRegapdna() 
{
	// TODO: Add your command handler code here

	int count = 0;
	BOOL ret;
	CGenedocDoc *poDoc;
	CString ErrStr;
	CMultiDocTemplate* pMDTmpl = ((CGenedocApp *)AfxGetApp())->m_pGenedocTemplate;

	POSITION dPos = pMDTmpl->GetFirstDocPosition( );
	while ( dPos != NULL ) {
		poDoc = (CGenedocDoc*)pMDTmpl->GetNextDoc(dPos);
		if ( poDoc == this ) continue;
		count++;
		break;
	}

	if ( !count ) {
		AfxMessageBox("No Other Project To Select From!");
		return;
	}
	
	CSelProject pDlg;
	pDlg.pDoc = this;
	if ( pDlg.DoModal() != IDOK ) return;

	poDoc = pDlg.poDoc;

	if ( poDoc == NULL ) {
		AfxMessageBox("No Other Project Selected!");
		return;
	}

	CGSFiller *poFiller = poDoc->pGSFiller;
	if ( poFiller == NULL ) return;

	if ( pGSFiller == NULL ) return;

	CGeneSegment *pCGSeg;
	CGeneSegment *poCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		POSITION pPos = poFiller->SegDataList.GetHeadPosition();
		while (pPos != NULL ) {
			poCGSeg = (CGeneSegment *)poFiller->SegDataList.GetNext(pPos);
			if ( poCGSeg->GetStyle() != LINESEQUENCE ) continue;
			if ( pCGSeg->GetTitle() == poCGSeg->GetTitle() ) {
				ret = poCGSeg->ReGapDNAWith( 
					pCGSeg->GetTextHandle(), 
					pCGSeg->GetTextLength(), 
					poDoc->m_UserVars.m_DNATrans, 
					ErrStr 
				);
				
				break;
			}
		}
		if ( ret == FALSE ) {
			if ( AfxMessageBox( "Error: " + ErrStr, MB_OKCANCEL ) == IDCANCEL ) break;
		}
	}

	// Make all sequences the same length.
	poDoc->ReSizeRows();

	poDoc->AutoShade(-1);
	poDoc->SetModifiedFlag();

	poDoc->OnGeneview();
}

void CGenedocDoc::ColFreqRep(DWORD StartRange, DWORD EndRange, int UseWeights) 
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL && m_UserVars.m_ProjectType ) {

		// BeginWaitCursor();
		CString PathName;
		GetTempFileName( PathName );
		double dArr[26];
		char outbuf[256];

		BeginWaitCursor();


	TRY {

		CStdioFile oFile( PathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );


		BeginWaitCursor(); // Let em know


		int RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
		
		ShadeSegStc *pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row here


		int SeqCount = 0;

		POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
			// Lock it down
			pSegArr[SeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			pSegArr[SeqCount].pCGSeg = tCGSeg;
			SeqCount++;
		}


		if (m_UserVars.m_ProjectType == 1 ) {

				
	
			for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {
				memset ( dArr, 0, sizeof(dArr) );

				for ( int di=0; di < SeqCount; ++di ) {
					char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						double dInc;
						if ( UseWeights ) {
							dInc = pSegArr[di].pCGSeg->GetWeight();
						} else {
							dInc = 1.0;
						}
						dArr[tChar - 'A'] += dInc;
					}
				}

				double Total = 0.0;
				for ( int i=0; i < 26; ++i ) {
					Total += dArr[i];
				}

				_snprintf ( outbuf, sizeof(outbuf), "%-10ld ", dwl + 1);
				oFile.WriteString( outbuf );

				if ( Total == 0.0 ) {
					_snprintf ( outbuf, sizeof(outbuf), "\n");
					oFile.WriteString( outbuf );
					continue;
				}
				int crc = 0;
				for (int i=0; i < 26; ++i ) {
					switch (i + 'A') {
					case 'A':
					case 'C':
					case 'D':
					case 'E':
					case 'F':
					case 'G':
					case 'H':
					case 'I':
					case 'K':
					case 'L':
					case 'M':
					case 'N':
					case 'P':
					case 'Q':
					case 'R':
					case 'S':
					case 'T':
					case 'V':
					case 'W':
					case 'Y':
						{
							
							if ( (crc % 5) == 0 && crc != 0) {
								_snprintf ( outbuf, sizeof(outbuf), "\n%-10ld ", dwl + 1 );
								oFile.WriteString( outbuf );
							}
							crc++;
							double Score = dArr[i] / Total;
							_snprintf ( outbuf, sizeof(outbuf), " %c = %5.4lf", i + 'A', Score );
							oFile.WriteString( outbuf );
							break;
						}
					}
				}
				_snprintf ( outbuf, sizeof(outbuf), "\n\n");
				oFile.WriteString( outbuf );
			}

		} else {

//
			for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

				memset ( dArr, 0, sizeof(dArr) );

				for ( int di=0; di < SeqCount; ++di ) {

					char tChar = toupper ( pSegArr[di].pGeneStor[dwl].CharGene );
					if ( tChar >= 'A' && tChar <= 'Z' ) {
						double dInc;
						if ( UseWeights ) {
							dInc = pSegArr[di].pCGSeg->GetWeight();
						} else {
							dInc = 1.0;
						}
						switch ( tChar ) {
						case 'A':
						case 'C':
						case 'G':
						case 'T':
							dArr[tChar - 'A'] += dInc;
							break;
						case 'U':
							dArr['T' - 'A'] += dInc;
							break;
						case 'Y':
							dArr['C' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'R':
							dArr['A' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'W':
							dArr['A' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'S':
							dArr['C' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'K':
							dArr['T' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'M':
							dArr['C' - 'A'] += dInc;
							dArr['A' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'B':
							dArr['C' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'D':
							dArr['A' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'H':
							dArr['A' - 'A'] += dInc;
							dArr['C' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'V':
							dArr['A' - 'A'] += dInc;
							dArr['C' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'N':
							dArr['A' - 'A'] += dInc;
							dArr['C' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						case 'X':
							dArr['A' - 'A'] += dInc;
							dArr['C' - 'A'] += dInc;
							dArr['G' - 'A'] += dInc;
							dArr['T' - 'A'] += dInc;
//							dArr['N' - 'A'] += dInc;
							break;
						}
					}
				}


				double Total = 0.0;
				for ( int i=0; i < 26; ++i ) {
					Total += dArr[i];
				}

				_snprintf ( outbuf, sizeof(outbuf), "%-10ld ", dwl + 1 );
				oFile.WriteString( outbuf );

				if ( Total == 0.0 ) {
					_snprintf ( outbuf, sizeof(outbuf), "\n");
					oFile.WriteString( outbuf );
					continue;
				}

				for (int i=0; i < 26; ++i ) {
					switch (i + 'A') {
					case 'A':
					case 'C':
					case 'G':
					case 'T':
						{
							double Score = dArr[i] / Total;
							_snprintf ( outbuf, sizeof(outbuf), " %c = %5.4lf", i + 'A', Score );
							oFile.WriteString( outbuf );
							break;
						}
					}
				}
				double Score = dArr['N' - 'A'] / Total;
//				double ttot = dArr['G' - 'A'] + dArr['C' - 'A'] + dArr['T' - 'A'] + dArr['A' - 'A'];
//				double ScoreGC = (dArr['G' - 'A'] + dArr['C' - 'A']) / ttot;
				_snprintf ( outbuf, sizeof(outbuf), " (N = %5.4lf)\n", Score);
				oFile.WriteString( outbuf );
			}
		}

//		

		oFile.Close();


		for ( int i=0; i < SeqCount; ++i ) {
			GlobalUnlock( pSegArr[i].pCGSeg->GetTextHandle() );
		}

		delete [] pSegArr;


	} 
	CATCH (CFileException, e ) {
		if( e->m_cause == CFileException::fileNotFound )
			AfxMessageBox( "File Not Found Error" );
		else
			AfxMessageBox( "File Error" );

		return;
	}
	AND_CATCH (CMemoryException, e ) {
		AfxMessageBox( "Memory Exception" );
		return;
	}
	END_CATCH

		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {
			m_pTextView->GetParentFrame()->ActivateFrame();
		}

		m_pTextView->LoadFile(PathName);

		DeleteTempFile( PathName );
	}


}

void CGenedocDoc::OnShadingRep() 
{
	static char *aatrans[] = {
		"Ala", "", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile", "", "Lys",
		"Leu", "Met", "Asn", "", "Pro", "Gln", "Arg", "Ser", "Thr", "", "Val",
		"Trp", "Xxx", "Tyr", "Glx" 
	};
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		BeginWaitCursor();
		CString FileName;
		GetTempFileName( FileName );
	
		COLORREF TextC, BkC;
		GetLevelColors( &m_UserVars.m_Vars, 0, &TextC, &BkC );

		int rc = 1;
	TRY {
		char LeadBuff[512];
		char OutBuf[256];

		
		POSITION tPos;
		
		CStdioFile oFile ( FileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );


		char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
		
		// Allocate memory for subsequent sequence data
		POSITION sPos = pGSFiller->SegDataList.GetHeadPosition();
		
		while ( sPos != NULL ) {
			CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(sPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
				continue;
			}
			CString GroupName = "";
			// tCGSeg;
			if ( tCGSeg->m_DisplayGroup != 0 ) {
				CDisplayVars *DisplayVars = NULL;
				int GrpNum = 0;
				POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
				while ( tPos != NULL ) {
					DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
					GrpNum++;
					if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
				}
				if ( DisplayVars != NULL ) {
					GroupName = DisplayVars->GetGroupName();
				}
			}

			GeneStor *pGS = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

			sprintf( LeadBuff, "%s %s\n", tCGSeg->GetTitle(), GroupName );
			oFile.WriteString( LeadBuff );

			DWORD tCount = tCGSeg->GetTextLength();

			CPtrList m_ColorList;

			// Fill out color list.
			for ( DWORD i = 0; i < tCount; ++i ) {
				if ( pGS[i].TextColor == TextC && pGS[i].BackColor == BkC ) continue;
				POSITION tPos = m_ColorList.GetHeadPosition();
				int found = 0;
				while ( tPos != NULL ) {
					stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)m_ColorList.GetNext(tPos);
					if ( pPDBC->rgbText == pGS[i].TextColor 
						&& pPDBC->rgbBack == pGS[i].BackColor 
					) {
						found = 1;
						break;
					}
				}
				if ( !found  ) {
					stcPDBCOLOR *pPDBC2 = new stcPDBCOLOR;
					pPDBC2->rgbText = pGS[i].TextColor;
					pPDBC2->rgbBack = pGS[i].BackColor;
					m_ColorList.AddTail( pPDBC2 );
				}
			}

			tPos = m_ColorList.GetHeadPosition();
			while ( tPos != NULL ) {
				stcPDBCOLOR *pPDBC = (stcPDBCOLOR *)m_ColorList.GetNext(tPos);
				sprintf( OutBuf, "color [%d,%d,%d]\n", 
					GetRValue( pPDBC->rgbBack ), 
					GetGValue( pPDBC->rgbBack ), 
					GetBValue( pPDBC->rgbBack ) 
				);
				oFile.WriteString( OutBuf );
				for (int i = 0; i < tCount; ++i ) {
					char tChar = toupper(pGS[i].CharGene );
					if ( tChar >= 'A' && tChar <= 'Z' ) {

						if ( pPDBC->rgbText == pGS[i].TextColor
							&& pPDBC->rgbBack == pGS[i].BackColor
						) {
							if ( m_UserVars.m_RepIncAA ) {
								sprintf( OutBuf, "%s%ld, ", aatrans[tChar-'A'], pGS[i].GeneSeqNumber );
							} else {
								sprintf( OutBuf, "%ld, ", pGS[i].GeneSeqNumber );
							}
							oFile.WriteString( OutBuf );
						}
					}
				}
				oFile.WriteString( "\n" );
			}


			GlobalUnlock( tCGSeg->GetTextHandle() );

			while ( !m_ColorList.IsEmpty() ) delete (stcPDBCOLOR *)m_ColorList.RemoveHead();
		
		}
		
		// only sequences now ..
		
		

		oFile.Close();

		// Return success
	} 
	CATCH (CFileException, e ) {
		if( e->m_cause == CFileException::fileNotFound )
			AfxMessageBox( "File Not Found Error" );
		else
			AfxMessageBox( "File Error" );

//		return 0;
	}
	AND_CATCH (CMemoryException, e ) {
		AfxMessageBox( "Memory Exception" );
//		return 0;
	}
	END_CATCH

//		return rc;
	
		if ( m_pTextView == NULL ) {
		
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
		} else {

			m_pTextView->GetParentFrame()->ActivateFrame();
//			m_pTextView->Invalidate();

		}

		m_pTextView->LoadFile(FileName);

		DeleteTempFile( FileName );
	
		EndWaitCursor();
	}

}
