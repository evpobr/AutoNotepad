// AutoNotepadView.h : interface of the CAutoNotepadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTONOTEPADVIEW_H__BBDF80D1_C111_11D6_AD1F_0020182FF55E__INCLUDED_)
#define AFX_AUTONOTEPADVIEW_H__BBDF80D1_C111_11D6_AD1F_0020182FF55E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAutoNotepadView : public CWindowImpl<CAutoNotepadView, CEdit>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CEdit::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CAutoNotepadView)
	END_MSG_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTONOTEPADVIEW_H__BBDF80D1_C111_11D6_AD1F_0020182FF55E__INCLUDED_)
