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

class CBSumCaret {

private:
	UINT m_xi;
	DWORD m_yi;
	UINT m_xs;
	UINT m_maxx;
	DWORD m_maxy;
	DWORD m_ys;
	UINT m_minx;
	DWORD m_miny;

	// CPoint m_Position;
	UINT m_XPosition;
	DWORD m_YPosition;
	// CPoint m_ScrollPos;
	UINT m_ScrollXPosition;
	DWORD m_ScrollYPosition;

	int m_ControlOn;
	int m_ShiftOn;
	// CSize m_ViewSize;
	UINT m_ViewXSize;
	DWORD m_ViewYSize;

	DWORD m_CaretHeight;

	// CRect m_ClipRect;
	UINT m_ClipXPosition;
	DWORD m_ClipYPosition;
	UINT m_ClipXSize;
	DWORD m_ClipYSize;

	int m_Clipping;

	char MakeAscii( UINT nChar, UINT nFlags );

public:
	CBSumCaret();

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags, CView* pView);
	void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags, CView* pView);

	void SetIncrements( UINT nxi, DWORD nyi, UINT nxs, DWORD nys);
	void SetMaximums( UINT nmx, DWORD nmy );
	
	void ClipCaret(int Clipping, UINT XPosition = 0, DWORD YPosition = 0, UINT XSize = 0, DWORD YSize = 0);

	void SetPosition( UINT XPosition, DWORD YPosition );
	void SetHeight( DWORD nCaretHeight );
	void GetPosition( UINT *XPosition, DWORD *YPosition );
	void SetViewSize( UINT XSize, DWORD YSize );
	void SetScrollPos( UINT XPosition, DWORD YPosition );
	void CaretPos ();
	void FollowMouse( UINT XPosition, DWORD YPosition );
	virtual void LeftDown( UINT XPosition, DWORD YPosition, CView* pView ) {}
	virtual void Move ( UINT XPosition, DWORD YPosition, CView* pView ) {}
	virtual void LeftUp( UINT XPosition, DWORD YPosition, CView* pView ) {}
	virtual void Select( UINT XPosition, DWORD YPosition, CView* pView ) {}
	virtual int Comment( char nChar, UINT XPosition, DWORD YPosition, CView* pView ) {return 0;}
};
	