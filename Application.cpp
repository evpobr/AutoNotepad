// Application.cpp : Implementation of CApplication
#include "stdafx.h"
#include "AutoNotepad.h"
#include "Application.h"

CApplication::CApplication()
{
}

HRESULT CApplication::
FinalConstruct()
{
    if (_Module.IsAutomated())
    {
        int nShow = SW_HIDE;
	    if (m_wndMain.CreateEx(NULL, NULL, 0, 0, (void*)&nShow) == NULL)
	    {
		    ATLTRACE(_T("Main window creation failed!\n"));
		    return 0;
	    }
        m_wndMain.ShowWindow(SW_HIDE);
        _Module.Lock();
    }

    m_wndMain.m_pApplication = this;

    return S_OK;
}   

void CApplication::
FinalRelease()
{
    ATLTRACE(_T("CApplication::FinalRelease()\n"));
    if (_Module.IsAutomated())
    {
        // Clean up the main window if it is still present
        if (m_wndMain.IsWindow())
        {
            m_wndMain.SendMessage(WM_CLOSE, 0, 0L);
            m_wndMain.DestroyWindow();
        }

        // Try and speed up process destruction if no one else is using us.
        if (_Module.GetLockCount() == 2)
	    {
		    _Module.m_dwTimeOut = 0L;
		    _Module.m_dwPause = 0L;
	    }
	    _Module.Unlock();
    }
}

int CApplication::
Run(LPTSTR lpstrCmdLine, int nShow)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	if (m_wndMain.CreateEx(NULL, NULL, 0, 0, (void*)&nShow) == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

    // Permit loading a filename passed in through the commandline.
    //if (lpstrCmdLine && _tcslen(lpstrCmdLine) > 0)
    //    m_wndMain.LoadFrom(lpstrCmdLine);

	_Module.Lock();
	m_wndMain.ShowWindow(nShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

STDMETHODIMP CApplication::
get_Text(BSTR *pVal)
{
    HRESULT hr = E_POINTER;
    if (pVal)
    {
        int cbsz  = m_wndMain.m_view.GetWindowTextLength();
        LPTSTR sz = new TCHAR[cbsz+1];
        m_wndMain.m_view.GetWindowText(sz, cbsz);
        sz[cbsz+1] = 0;
        CComBSTR s(sz);
        hr = s.CopyTo(pVal);
    }
    return hr;
}

STDMETHODIMP CApplication::
put_Text(BSTR newVal)
{
    USES_CONVERSION;
    m_wndMain.m_view.SetWindowText(OLE2CT(newVal));
    return S_OK;
}

STDMETHODIMP CApplication::
get_Visible(VARIANT_BOOL *pVal)
{
    HRESULT hr = E_POINTER;
    if (pVal)
    {
        *pVal = ((m_wndMain.IsWindow() && m_wndMain.IsWindowVisible()) ? VARIANT_TRUE : VARIANT_FALSE);
        hr = S_OK;
    }
    return hr;
}

STDMETHODIMP CApplication::
put_Visible(VARIANT_BOOL newVal)
{
    if (newVal == VARIANT_TRUE)
    {
        //m_wndMain.RestoreWindowPlacement();
        m_wndMain.ShowWindow(SW_SHOW);
        m_wndMain.SetActiveWindow();
    }
    else
    {
        //m_wndMain.StoreUserPreferences();
        m_wndMain.ShowWindow(SW_HIDE);
        m_wndMain.SetActiveWindow();
    }
    
    return S_OK;
}

STDMETHODIMP CApplication::
InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IApplication
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
