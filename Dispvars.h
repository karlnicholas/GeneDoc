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

#ifndef DISPVARS_H_INCLUDED
#define DISPVARS_H_INCLUDED

typedef struct {
	// Seperate out Display Vars ....
	int		m_GroupEnabled;		// Enable Similarity Groups
		
	double m_PrimaryLevel;
	double m_SecondaryLevel;
	double m_TertiaryLevel;

	int m_ModeConserved;	// 0 = Conserved, 1 = quant, 2 = prop, 3 = structure ..
	int m_LastShadeLevel;	// 0 = clear, 1 = invalid, 2, 3, 4, 5 = autodiff 4 level.

	int m_ResidueMode;		// 0 = Normal, 1 = diff  TODO

	int m_DiffMode;			// 0 old style diff, 1 = Top Seq Diff
	int m_PropStyle;		// 0 = Prop Conserved, 1 = Prop All

	COLORREF	m_TitleTextColor;
	COLORREF	m_TitleBkColor;

	CProperty	m_Property;

	int m_ConsSubStyle;		// 0 = Ident, 1 = Demoted, 2 = Tertiary

	// End Needs initing
	
	CStcGroup	m_StcGroup;		// Group Specific Structure Entries
		
	CString 	m_GroupName;
	CPtrList	m_GroupList;	// CGeneSequence *
	CPtrList	m_IdentList;	// CGeneSequence *
	COLORREF	m_IdentTextColor;	// 255,255,255
	COLORREF	m_IdentBkColor;		// 128,128,128
	int			m_IdentDisplayStyle;

	// End Display Vars ....
} DisplayVars;


class CDisplayVars: public CObject {

private:

	DisplayVars	m_DisplayVars;

public:

	CDisplayVars();

	~CDisplayVars();

	DECLARE_DYNCREATE(CDisplayVars)

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void CopyVars( CDisplayVars *nDisplayVars, CDocument *pDoc );
	void CopyDisplayVars( DisplayVars *pDV, CDisplayVars *nDisplayVars, CDocument *pDC );
	void SetDisplayVars( DisplayVars *pDV, CDocument *pDC );
	void ClearVars( DisplayVars *pDV );
	
	int GetGroupEnabled() const { return m_DisplayVars.m_GroupEnabled; }
	double GetPrimaryLevel() const { return m_DisplayVars.m_PrimaryLevel; }
	double GetSecondaryLevel() const { return m_DisplayVars.m_SecondaryLevel; }
	double GetTertiaryLevel() const { return m_DisplayVars.m_TertiaryLevel; }
	int GetModeConserved() const { return m_DisplayVars.m_ModeConserved; }
	int GetLastShadeLevel() const { return m_DisplayVars.m_LastShadeLevel; }
	int GetDiffMode() const { return m_DisplayVars.m_DiffMode; }
	int GetPropStyle() const {return m_DisplayVars.m_PropStyle; }
	int GetResidueMode() const { return m_DisplayVars.m_ResidueMode; }
	int GetConsSubStyle() const { return m_DisplayVars.m_ConsSubStyle; }

	CProperty& GetProperty() { return m_DisplayVars.m_Property; }
	CStcGroup& GetStcGroup() { return m_DisplayVars.m_StcGroup; }


	void SetGroupEnabled(int GroupEnabled ) { m_DisplayVars.m_GroupEnabled = GroupEnabled; }
	void SetPrimaryLevel( double PrimaryLevel ) { m_DisplayVars.m_PrimaryLevel = PrimaryLevel; }
	void SetSecondaryLevel( double SecondaryLevel ) { m_DisplayVars.m_SecondaryLevel = SecondaryLevel; }
	void SetTertiaryLevel( double TertiaryLevel ) { m_DisplayVars.m_TertiaryLevel = TertiaryLevel; }
	void SetModeConserved( int ModeConserved ) { m_DisplayVars.m_ModeConserved = ModeConserved; }
	void SetLastShadeLevel( int LastShadeLevel ) { m_DisplayVars.m_LastShadeLevel = LastShadeLevel; }
	void SetDiffMode( int DiffMode ) { m_DisplayVars.m_DiffMode = DiffMode; }
	void SetPropStyle( int PropStyle ) { m_DisplayVars.m_PropStyle = PropStyle; }
	void SetResidueMode( int ResidueMode ) { m_DisplayVars.m_ResidueMode = ResidueMode; }
	void SetConsSubStyle( int ConsSubStyle ) { m_DisplayVars.m_ConsSubStyle = ConsSubStyle; }
	
	const CString& GetGroupName() const { return m_DisplayVars.m_GroupName; }
	void SetGroupName( const CString& nGroupName ) { m_DisplayVars.m_GroupName = nGroupName; }
	void SetTitleColors( const COLORREF nTextColor, const COLORREF nBkColor ) 
		{ m_DisplayVars.m_TitleTextColor = nTextColor; m_DisplayVars.m_TitleBkColor = nBkColor; }
	void GetTitleColors( COLORREF *TextColor, COLORREF *BkColor ) const 
		{ *TextColor = m_DisplayVars.m_TitleTextColor; *BkColor = m_DisplayVars.m_TitleBkColor; }
	
	CPtrList *GetGroupList() { return &m_DisplayVars.m_GroupList; }

	CPtrList *GetIdentList() { return &m_DisplayVars.m_IdentList; }
	void SetIdentColors( const COLORREF nTextColor, const COLORREF nBkColor ) 
		{ m_DisplayVars.m_IdentTextColor = nTextColor; m_DisplayVars.m_IdentBkColor = nBkColor; }
	void GetIdentColors( COLORREF *TextColor, COLORREF *BkColor ) const 
		{ *TextColor = m_DisplayVars.m_IdentTextColor; *BkColor = m_DisplayVars.m_IdentBkColor; }

	int GetIdentDisplayStyle() { return m_DisplayVars.m_IdentDisplayStyle; }

	void SetIdentDisplayStyle( int nStyle ) { m_DisplayVars.m_IdentDisplayStyle = nStyle; }


};

#endif
