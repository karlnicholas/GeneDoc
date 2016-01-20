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


class CPictFile: public CObject {
private:

// Work Globals

	int m_fontdescent;
	
	int m_xpos;
	int m_ypos;
	
	FILE* m_OutFile;

	void MakeInt( int val );
	void MakePoint( int xpoint, int ypoint);
	void PutColor( COLORREF BackGround );

//
public:

	// Constructors
	CPictFile();
	DECLARE_DYNCREATE(CPictFile)

	int m_dev_xsize;
	int m_dev_ysize;
	
	int PictInit( 
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
	);

	int SumPictInit( 
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
	);

	void CharOut( char c, COLORREF ForeGround, COLORREF BackGround );

	void SumFillRect( CRect& rect, COLORREF *pColor );
	void SumChar(int SumWidth);

	void NewLine();
	void Exit();

	void LineMiddle();
	void LineBottom();
	void LineLeft();
	void LineRight();


	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	

};

