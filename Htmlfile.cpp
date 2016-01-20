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
// CHTMLFile
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTMLFile

IMPLEMENT_DYNCREATE(CHTMLFile, CObject)


CHTMLFile::CHTMLFile()
{
	// TODO: add construction code here
}


/////////////////////////////////////////////////////////////////////////////
// CHTMLFile serialization

void CHTMLFile::Serialize(CArchive& ar)
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
// CHTMLFile diagnostics

#ifdef _DEBUG
void CHTMLFile::AssertValid() const
{
	CObject::AssertValid();
}

void CHTMLFile::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// where these?


//
int 
CHTMLFile::HTMLInit ( 
	int pictwidth, 
	int pictheight, 
	int fontpoints, 
	int fontxsize, 
	int fontysize, 
	int fontdescent, 
	int fontbold, 
	char *fontname, 
	const char *outname, 
	COLORREF bgcolor, 
	COLORREF fcolor, 
	int modeflag, 
	int fullweb
) {

TRY {
	m_fontxsize = fontxsize;
	m_fontysize = fontysize;
	m_bold = fontbold;
	m_bgcolor = bgcolor;
	m_fcolor = fcolor;
	m_size = 3;
	m_modeflag = modeflag;
	m_fullweb = fullweb;

	if ( fontpoints < 11 ) m_size = 2;
	if ( fontpoints > 13 ) m_size = 4;
	if ( fontpoints > 17 ) m_size = 5;
	if ( fontpoints > 27 ) m_size = 6;
	if ( fontpoints > 37 ) m_size = 7;


	m_OutFile = new CStdioFile( outname, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	if ( !m_fullweb ) {

		m_OutFile->WriteString( "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">\n" );
		m_OutFile->WriteString( "<HTML>\n" );
		m_OutFile->WriteString( "	<HEAD>\n" );
		m_OutFile->WriteString( "   <TITLE></TITLE>\n" );
		m_OutFile->WriteString( "   <META NAME=\"Author\" CONTENT=\"\">\n" );
		m_OutFile->WriteString( "   <META NAME=\"GENERATOR\" CONTENT=\"GeneDoc\">\n" );
		m_OutFile->WriteString( "</HEAD>\n" );
		char Buff[256];
		sprintf(Buff, "<BODY BGCOLOR=\"#%02X%02X%02X\">", 
			GetRValue( bgcolor ), GetGValue( bgcolor ), GetBValue( bgcolor ) 
		);
		m_OutFile->WriteString( Buff );
	}

	switch ( modeflag ) {
	case 1: // Text only
		{
		if ( fontbold  ) {
			m_OutFile->WriteString( "<B>\n" );
		}
		m_OutFile->WriteString( "<TT>\n<PRE>\n" );
		char Buff[256];
		sprintf(Buff, "<FONT COLOR=\"#%02X%02X%02X\" SIZE=\"%d\">", 
			GetRValue( fcolor ), GetGValue( fcolor ), GetBValue( fcolor ), m_size 
		);
		m_OutFile->WriteString( Buff );
		m_rgbCurrent = fcolor;
		}
		break;
	}

} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
	return 0;
}
END_CATCH

return 1;
}

void
CHTMLFile::StartBlock()
{
TRY {
	switch ( m_modeflag ) {
	case 0:
		{
		char buff[256];
		sprintf ( buff, "<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0  BGCOLOR=\"#%02X%02X%02X\">\n", 
			GetRValue(m_bgcolor), GetGValue(m_bgcolor), GetBValue(m_bgcolor)
		);
		m_OutFile->WriteString( buff );
		}
		break;
	case 1:
		break;
	}
} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void
CHTMLFile::EndBlock()
{
TRY {
	switch ( m_modeflag ) {
	case 0:
		{
		m_OutFile->WriteString( "</TABLE>\n" );
		}
		break;
	case 1:
		break;
	}
} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void
CHTMLFile::StartLine()
{
TRY {
	switch ( m_modeflag ) {
	case 0:
		{
		m_OutFile->WriteString( "<TR>\n" );
		}
		break;
	case 1:
		break;
	}
} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void
CHTMLFile::EndLine()
{
TRY {
	switch ( m_modeflag ) {
	case 0:
		{
		m_OutFile->WriteString( "</TR>\n" );
		}
		break;
	case 1:
		m_OutFile->WriteString( "\n" );
		break;
	}
} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void CHTMLFile::CharOut( char c, COLORREF ForeGround, COLORREF BackGround )
{
TRY {
// <TD BGCOLOR="#FF0000"><FONT COLOR="#FFFFFF" FACE="COURIER NEW" SIZE="4">
//	char s1[256];
//	if ( c == ' ' ) {
//		sprintf ( s1, " WIDTH=\"%d\" HEIGHT=\"%d\"", m_fontxsize, m_fontysize );
//	} else {
//		s1[0] = 0;
//	}

	char s4[16];
	char s5[16];
	if ( m_bold  ) {
		strcpy ( s4, "<B>" );
		strcpy ( s5, "</B>" );
	} else {
		s4[0] = 0;
		s5[0] = 0;
	}

	switch ( m_modeflag ) {
	case 0:
		{
		char s2[128];
		if ( BackGround != m_bgcolor ) {
			sprintf ( s2, " BGCOLOR=\"#%02X%02X%02X\"", 
				GetRValue( BackGround ), GetGValue( BackGround ), GetBValue( BackGround ) 
			);
		} else {
			s2[0] = 0;
		}

		char s3[128];
//		if ( ForeGround != m_fcolor  ) {
			sprintf ( s3, "<FONT COLOR=\"#%02X%02X%02X\" FACE=\"Courier\" SIZE=\"%d\">", 
				GetRValue( ForeGround ), GetGValue( ForeGround ), GetBValue( ForeGround ), m_size 
			);
//		} else {
//			sprintf ( s3, "<FONT FACE=\"Courier\" SIZE=\"%d\">", m_size );
//		}

		char Buff[256];
		sprintf( Buff, "<TD%s>%s%s", s2, s3, s4 );

		m_OutFile->WriteString( Buff );

		if ( c == ' ' ) {
			sprintf( Buff, "&nbsp%s</FONT></TD>\n", s5 );
		} else {
			sprintf( Buff, "%c%s</FONT></TD>\n", c, s5 );
		}

		m_OutFile->WriteString( Buff );
		}
		break;
	case 1:
		{
		char s3[128];
		if ( ForeGround != m_rgbCurrent ) {
			sprintf ( s3, "</FONT><FONT COLOR=\"#%02X%02X%02X\" SIZE=\"%d\">", 
				GetRValue( ForeGround ), GetGValue( ForeGround ), GetBValue( ForeGround ), m_size 
			);
			m_rgbCurrent = ForeGround;
		} else {
			s3[0] = 0;
		}

		char Buff[256];
		if ( c == ' ' ) {
			sprintf( Buff, "%s&nbsp", s3 );
		} else {
			sprintf( Buff, "%s%c", s3, c );
		}

		m_OutFile->WriteString( Buff );

		}
		break;
	}

} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void
CHTMLFile::LineMiddle()
{
}

void
CHTMLFile::LineBottom()
{
}

void
CHTMLFile::LineLeft()
{
}

void
CHTMLFile::LineRight()
{
}


void
CHTMLFile::Exit()
{
	switch ( m_modeflag ) {
	case 1:
		m_OutFile->WriteString( "</PRE>\n</TT>\n" );
		if ( m_bold  ) {
			m_OutFile->WriteString( "</B>\n" );
		}
		break;
	}

	if ( !m_fullweb ) {
		m_OutFile->WriteString( "</BODY>\n" );
		m_OutFile->WriteString( "</HTML>\n" );
	}

	m_OutFile->Close();
	delete m_OutFile;
	
	return;
}
