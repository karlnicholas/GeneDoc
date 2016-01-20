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


class CHTMLFile: public CObject {
private:

// Work Globals

	
	CStdioFile* m_OutFile;
	int m_fontxsize;
	int m_fontysize;
	int m_bold;
	int m_size;
	int m_modeflag;
	int m_fullweb;

	COLORREF m_bgcolor;
	COLORREF m_fcolor;

	COLORREF m_rgbCurrent;


//
public:

	// Constructors
	CHTMLFile();
	DECLARE_DYNCREATE(CHTMLFile)

	int HTMLInit( int pictwidth, 
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
	);
	void CharOut( char c, COLORREF ForeGround, COLORREF BackGround );
	void StartBlock();
	void EndBlock();
	void StartLine();
	void EndLine();
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

