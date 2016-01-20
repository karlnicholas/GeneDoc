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
// CPictFile
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictFile

IMPLEMENT_DYNCREATE(CPictFile, CObject)


CPictFile::CPictFile()
{
	// TODO: add construction code here
}


/////////////////////////////////////////////////////////////////////////////
// CPictFile serialization

void CPictFile::Serialize(CArchive& ar)
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
// CPictFile diagnostics

#ifdef _DEBUG
void CPictFile::AssertValid() const
{
	CObject::AssertValid();
}

void CPictFile::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// where these?

unsigned char StrHeaderOp[10] = { 
0, 17, 2, 255,			// Version and 2.255 data
12, 0, // Heasder Op  $0C00
255, 255, 255, 255 };	// Followed by version = -1 = fixed point bounding box

unsigned char StrHiLiteClip[6] = { 
0, 30,   // 00, 1E - def hilit opcode
0, 1,    // Cipping Region
0, 10    // Clipping Value Size, 10 bytes. 8 + 2 for size.
};

/*
0, 44, // Font Select
0, 14, // Length
0, 22, // font ID
7, 'C', 'o', 'u', 'r', 'i', 'e', 'r',  // ' ', 'N', 'e', 'w', 
*/

unsigned char StrSetFont[4] = { 
0, 3, // Text Font - Select this font
0, 22, // Text Font Value.
};

/*
0, 4, // Text Face ( Word ) 
0, 0, // Text face value  1 , 0  = BOLD
*/

/*
0, 13, // Text Size .... points.
0 };// pictcell ...
*/

unsigned char LongTextOp[2] = { 0, 40 };
unsigned char RGBfgndOp[2] = {0, 26 };
unsigned char EndPicOp[2] = { 0, 255 };
unsigned char PaintRectOp[2] = { 0, 49 };
unsigned char LineOp[2] = { 0, 32 };
unsigned char PenPattOp[2] = { 0, 9 };
unsigned char PenSizeOp[2] = { 0, 7 };


void 
CPictFile::MakeInt( int val)
{
	putc( val / 256, m_OutFile );
	putc( val % 256, m_OutFile );
}

void 
CPictFile::MakePoint( int xpoint, int ypoint)
{
/* {converts a pair of points into a string containing the values as hex}
{in the order yvalue (hi), yvalue(lo), xvalue(hi), xvalue(lo)}
*/
	putc( ypoint / 256, m_OutFile );
	putc( ypoint % 256, m_OutFile );
	putc( xpoint / 256, m_OutFile );
	putc( xpoint % 256, m_OutFile);
}


void
CPictFile::PutColor( COLORREF BackGround )
{
	putc ( GetRValue ( BackGround), m_OutFile );
	putc ( GetRValue ( BackGround), m_OutFile );

	putc ( GetGValue ( BackGround), m_OutFile );
	putc ( GetGValue ( BackGround), m_OutFile );

	putc ( GetBValue ( BackGround), m_OutFile );
	putc ( GetBValue ( BackGround), m_OutFile );
};


//
int 
CPictFile::PictInit ( 
	int pictwidth, 
	int pictheight, 
	int fontpoints, 
	int fontxsize, 
	int fontysize, 
	int fontdescent, 
	int fontbold, 
	char *fontname, 
	const char *outname, 
	int addwidth, 
	int addheight, 
	int addascent
) {

	int	i;
	int tlX, tlY, brX, brY;
	char StrFormat[8];
	char StrFormat2[16];

	
	m_dev_xsize = (int)((double)fontpoints*(double)fontxsize/(double)(fontysize)) + 2 + addwidth;
	m_dev_ysize = fontpoints + addheight;
		
	m_fontdescent = (int)(m_dev_ysize * (double)fontdescent / (double)fontysize + 0.5) + addascent;

	m_xpos = m_dev_xsize / 2;
	m_ypos = m_dev_ysize + (m_dev_ysize / 2);

		// { 0,0 is top left corner, and we increase *ypos to go down the page}
/*			{as the size of the unit cell gets larger, the shift of the
			character to place it nicely in the "box" changes; I haven't worked
			out a nice formula that gives integer values that work for any
			number of points}
*/

	if ( ( m_OutFile = fopen( outname, "w+b" ) ) == NULL ) return 0;

/*
{Calculate here the TopLeft and BottomRight corners of the PICT, based on the size of the
 image and the page dimensions entered above: changing these to reflect, e.g. US Letter
 paper will result in a changed 'window' in which the program will draw the PICT. Note that
 BOXSHADE allows both PICT and EPSF to be *wider* than the defined page (i.e. it doesn't 
check for user errors over what will fit), but it does split the output into separate files of one 
'page-full' (or less)}
*/

	tlX = 0;
	tlY = 0;

	brY = tlY + (pictheight / fontysize) * m_dev_ysize;
	brX = tlX + (pictwidth / fontxsize) * m_dev_xsize + m_dev_xsize;
	
	StrFormat[0] = tlY / 256;
	StrFormat[1] = tlY % 256;
	StrFormat[2] = tlX / 256;
	StrFormat[3] = tlX % 256;
	StrFormat[4] = brY / 256;
	StrFormat[5] = brY % 256;
	StrFormat[6] = brX / 256;
	StrFormat[7] = brX % 256;
   
	for ( i = 0; i < 16; ++i ) StrFormat2[i] = 0;
	/* {yes, I know I'm being lazy!} */
	// hres
	StrFormat2[0] = tlX / 256;
	StrFormat2[1] = tlX % 256;

	// vres
	StrFormat2[4] = tlY / 256;
	StrFormat2[5] = tlY % 256;
                                  
	// srcrect top
	StrFormat2[8] = brX / 256;
	StrFormat2[9] = brX % 256;
	// srcrect left

	// srcrect bottom
	StrFormat2[12] = brY / 256;
	StrFormat2[13] = brY % 256;
	// srcrect right
		
	// version int 2
	// res int 2    
		
	// hres, fixed 4
	// vres  .. fixed 4
	// srcrect  .. top, left, bottom, right ints .. 8
		
	// reserved long  4
        
		// Represent a version 2 picture fixed point bounding box   

/*
{I have to write a header of 512 bytes plus 2 bytes for the PICT size field, 
which fortunately is never read.}
*/

	for ( i = 0; i < 514; ++i )  putc(0, m_OutFile );
			
/*	{now we write the various header opcodes and size for the file} */
			
	for ( i = 0; i < 8; ++i ) putc( StrFormat[i], m_OutFile );
	for ( i = 0; i < 10; ++i ) putc( StrHeaderOp[i], m_OutFile );
	for ( i = 0; i < 16; ++i ) putc( StrFormat2[i], m_OutFile );
	for ( i = 0; i < 4; ++i ) putc( 0, m_OutFile );

	// Now ..

	for ( i = 0; i < 6; ++i ) putc( StrHiLiteClip[i], m_OutFile );
	for ( i = 0; i < 8; ++i ) putc( StrFormat[i], m_OutFile );
		
	// Do Op 44, SetFontName?
	MakeInt ( 44 );
	int length = strlen(fontname) + 3;
	MakeInt ( length );
	MakeInt ( 22 );		// FontID
	putc ( length = strlen(fontname), m_OutFile );
	for ( i = 0; i < length; ++i ) putc( fontname[i], m_OutFile );
		
	// SetFontId op
	for ( i = 0; i < 4; ++i ) putc( StrSetFont[i], m_OutFile );
		
	MakeInt( 4 ); // Text Face ( Word ) 
		
	if ( fontbold ) {
		MakeInt(256);
	} else {
		MakeInt(0);
	}
		
	MakeInt(13); // Text Size points
	MakeInt(fontpoints); // Text Size points
		
	return 1;
}

//
int 
CPictFile::SumPictInit ( 
	int pictwidth, 
	int pictheight, 
	int numchars, 
	int numcols, 
	int colsinch, 
	int fontpoints, 
	int fontxsize, 
	int fontysize, 
	int fontdescent, 
	int fontbold, 
	char *fontname, 
	const char *outname, 
	int addwidth, 
	int addheight, 
	int addascent
) {

	int	i;
	int tlX, tlY, brX, brY;
	char StrFormat[8];
	char StrFormat2[16];

	
	m_dev_xsize = (int)((double)fontpoints*(double)fontxsize/(double)(fontysize)) + 2 + addwidth;
	m_dev_ysize = fontpoints + addheight;
		
	m_fontdescent = (int)(m_dev_ysize * (double)fontdescent / (double)fontysize + 0.5) + addascent;

	m_xpos = m_dev_xsize / 2;
	m_ypos = m_dev_ysize + (m_dev_ysize / 2);

		// { 0,0 is top left corner, and we increase *ypos to go down the page}
/*			{as the size of the unit cell gets larger, the shift of the
			character to place it nicely in the "box" changes; I haven't worked
			out a nice formula that gives integer values that work for any
			number of points}
*/

	if ( ( m_OutFile = fopen( outname, "w+b" ) ) == NULL ) return 0;

/*
{Calculate here the TopLeft and BottomRight corners of the PICT, based on the size of the
 image and the page dimensions entered above: changing these to reflect, e.g. US Letter
 paper will result in a changed 'window' in which the program will draw the PICT. Note that
 BOXSHADE allows both PICT and EPSF to be *wider* than the defined page (i.e. it doesn't 
check for user errors over what will fit), but it does split the output into separate files of one 
'page-full' (or less)}
*/

	tlX = 0;
	tlY = 0;

	int sumpix = 72 / colsinch;
	if ( sumpix == 0 ) sumpix = 1;

	brY = tlY + (pictheight / fontysize) * m_dev_ysize;
	brX = tlX + numchars * m_dev_xsize + numcols * sumpix + m_dev_xsize;
	
	StrFormat[0] = tlY / 256;
	StrFormat[1] = tlY % 256;
	StrFormat[2] = tlX / 256;
	StrFormat[3] = tlX % 256;
	StrFormat[4] = brY / 256;
	StrFormat[5] = brY % 256;
	StrFormat[6] = brX / 256;
	StrFormat[7] = brX % 256;
   
	for ( i = 0; i < 16; ++i ) StrFormat2[i] = 0;
	/* {yes, I know I'm being lazy!} */
	// hres
	StrFormat2[0] = tlX / 256;
	StrFormat2[1] = tlX % 256;

	// vres
	StrFormat2[4] = tlY / 256;
	StrFormat2[5] = tlY % 256;
                                  
	// srcrect top
	StrFormat2[8] = brX / 256;
	StrFormat2[9] = brX % 256;
	// srcrect left

	// srcrect bottom
	StrFormat2[12] = brY / 256;
	StrFormat2[13] = brY % 256;
	// srcrect right
		
	// version int 2
	// res int 2    
		
	// hres, fixed 4
	// vres  .. fixed 4
	// srcrect  .. top, left, bottom, right ints .. 8
		
	// reserved long  4
        
		// Represent a version 2 picture fixed point bounding box   

/*
{I have to write a header of 512 bytes plus 2 bytes for the PICT size field, 
which fortunately is never read.}
*/

	for ( i = 0; i < 514; ++i )  putc(0, m_OutFile );
			
/*	{now we write the various header opcodes and size for the file} */
			
	for ( i = 0; i < 8; ++i ) putc( StrFormat[i], m_OutFile );
	for ( i = 0; i < 10; ++i ) putc( StrHeaderOp[i], m_OutFile );
	for ( i = 0; i < 16; ++i ) putc( StrFormat2[i], m_OutFile );
	for ( i = 0; i < 4; ++i ) putc( 0, m_OutFile );

	// Now ..

	for ( i = 0; i < 6; ++i ) putc( StrHiLiteClip[i], m_OutFile );
	for ( i = 0; i < 8; ++i ) putc( StrFormat[i], m_OutFile );
		
	// Do Op 44, SetFontName?
	MakeInt ( 44 );
	int length = strlen(fontname) + 3;
	MakeInt ( length );
	MakeInt ( 22 );		// FontID
	putc ( length = strlen(fontname), m_OutFile );
	for ( i = 0; i < length; ++i ) putc( fontname[i], m_OutFile );
		
	// SetFontId op
	for ( i = 0; i < 4; ++i ) putc( StrSetFont[i], m_OutFile );
		
	MakeInt( 4 ); // Text Face ( Word ) 
		
	if ( fontbold ) {
		MakeInt(256);
	} else {
		MakeInt(0);
	}
		
	MakeInt(13); // Text Size points
	MakeInt(fontpoints); // Text Size points
		
	return 1;
}

void
CPictFile::CharOut( char c, COLORREF ForeGround, COLORREF BackGround )
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( BackGround );
              	
	putc ( PaintRectOp[0], m_OutFile );
	putc ( PaintRectOp[1], m_OutFile );
	xpoint = m_xpos;
	ypoint = m_ypos - m_dev_ysize;
	MakePoint( xpoint, ypoint );
	xpoint = m_xpos + m_dev_xsize;
	ypoint = m_ypos;
	MakePoint( xpoint, ypoint );
             
	putc( RGBfgndOp[0], m_OutFile );
	putc( RGBfgndOp[1], m_OutFile );

	PutColor( ForeGround );

	putc ( LongTextOp[0], m_OutFile );
	putc ( LongTextOp[1], m_OutFile );

	xpoint = m_xpos;
	ypoint = m_ypos - m_fontdescent;

	MakePoint( xpoint, ypoint );

	putc ( 1, m_OutFile );
	putc ( c, m_OutFile );


	m_xpos = m_xpos + m_dev_xsize; // {need to move anyway}

	return;
}


void 
CPictFile::SumFillRect( CRect& rect, COLORREF *pColor )
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( *pColor );

	putc ( PaintRectOp[0], m_OutFile );
	putc ( PaintRectOp[1], m_OutFile );

	CPoint tl = rect.TopLeft();
	xpoint = m_xpos + tl.x;
	ypoint = m_ypos - m_dev_ysize + tl.y;
	MakePoint( xpoint, ypoint );

	tl = rect.BottomRight();
	xpoint = m_xpos + tl.x;
	ypoint = m_ypos - m_dev_ysize + tl.y;
	MakePoint( xpoint, ypoint );

}

void 
CPictFile::SumChar(int SumWidth)
{
	m_xpos = m_xpos + SumWidth; // {need to move anyway}
}

void
CPictFile::LineMiddle()
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( RGB(0,0,0) );

	putc ( PenPattOp[0], m_OutFile );
	putc ( PenPattOp[1], m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );


	putc ( LineOp[0], m_OutFile );
	putc ( LineOp[1], m_OutFile );

	xpoint = m_xpos - m_dev_xsize;
	ypoint = m_ypos - (m_dev_ysize/2) - 1;
	MakePoint( xpoint, ypoint );

	xpoint = m_xpos + m_dev_xsize - m_dev_xsize;
	ypoint = m_ypos - (m_dev_ysize/2) - 1;
	MakePoint( xpoint, ypoint );
             
	return;
}

void
CPictFile::LineBottom()
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( RGB(0,0,0) );

	putc ( PenPattOp[0], m_OutFile );
	putc ( PenPattOp[1], m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
		
              	
	putc ( LineOp[0], m_OutFile );
	putc ( LineOp[1], m_OutFile );

	xpoint = m_xpos - m_dev_xsize;
	ypoint = m_ypos - 1;
	MakePoint( xpoint, ypoint );

	xpoint = m_xpos + m_dev_xsize - m_dev_xsize;
	ypoint = m_ypos - 1;
	MakePoint( xpoint, ypoint );
             
	return;
}

void
CPictFile::LineLeft()
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( RGB(0,0,0) );

	putc ( PenPattOp[0], m_OutFile );
	putc ( PenPattOp[1], m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );

              	
	putc ( LineOp[0], m_OutFile );
	putc ( LineOp[1], m_OutFile );

	xpoint = m_xpos - m_dev_xsize;
	ypoint = m_ypos - m_dev_ysize;
	MakePoint( xpoint, ypoint );

	xpoint = m_xpos - m_dev_xsize;
	ypoint = m_ypos - 1;
	MakePoint( xpoint, ypoint );
             
	return;
}

void
CPictFile::LineRight()
{
	int	xpoint, ypoint;

	putc ( RGBfgndOp[0], m_OutFile );
	putc ( RGBfgndOp[1], m_OutFile );

	PutColor( RGB(0,0,0) );

	putc ( PenPattOp[0], m_OutFile );
	putc ( PenPattOp[1], m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );
	putc ( -1, m_OutFile );

              	
	putc ( LineOp[0], m_OutFile );
	putc ( LineOp[1], m_OutFile );

	xpoint = m_xpos + m_dev_xsize - m_dev_xsize - 1;
	ypoint = m_ypos - m_dev_ysize;
	MakePoint( xpoint, ypoint );
	xpoint = m_xpos + m_dev_xsize - m_dev_xsize - 1;
	ypoint = m_ypos - 1;
	MakePoint( xpoint, ypoint );
             
	return;
}

void
CPictFile::NewLine()
{
	m_xpos = m_dev_xsize / 2;
	m_ypos = m_ypos + m_dev_ysize;

	return;
}

void
CPictFile::Exit()
{

	putc ( EndPicOp[0], m_OutFile );
	putc ( EndPicOp[1], m_OutFile );

	fclose( m_OutFile);
	
	return;
}
