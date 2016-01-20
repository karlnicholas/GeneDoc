// ScoreInfoEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoreInfoEditView view

class CScoreInfoEditView : public CEditView
{
	DECLARE_DYNCREATE(CScoreInfoEditView)
protected:
	CScoreInfoEditView();			// protected constructor used by dynamic creation
	CFont *m_pFont;

// Attributes
public:
	void LoadFile();

// Operations
public:

// Implementation
protected:
	virtual ~CScoreInfoEditView();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view

	// Generated message map functions
protected:
	//{{AFX_MSG(CScoreInfoEditView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
