#include "stdafx.h"
#include "AutoNotepad.h"
#include "Application.h"
#include "MainFrm.h"

LRESULT CMainFrame::
OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    ATLTRACE(_T("CMainFrame::OnClose()\n"));
    if (_Module.IsAutomated())
    {
        // Protect against the client releasing their pointer while handling the event.
        m_pApplication->AddRef();

        m_pApplication->Fire_OnAppClose();
        ShowWindow(SW_HIDE);
        bHandled = TRUE; // Prevent the DefWindowProc doing DeleteWindow.

        m_pApplication->Release();
    }
    else
    {
        m_pApplication->Fire_OnAppClose();
        DestroyWindow();
    }
    return 0L;
}

LRESULT CMainFrame::
OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    ATLTRACE(_T("CMainFrame::OnDestroy()\n"));
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
    if (! _Module.IsAutomated())
    {
        if(_Module.GetLockCount() == 1)
	    {
		    _Module.m_dwTimeOut = 0L;
		    _Module.m_dwPause = 0L;
	    }
	    _Module.Unlock();
    }
    return 0;
}

