// AutoNotepad.cpp : main source file for AutoNotepad.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>


#include "resource.h"

// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f AutoNotepadps.mk in the project directory.
#include "initguid.h"
#include "AutoNotepad.h"
#include "AutoNotepad_i.c"

#include "Application.h"

CAutomationAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Application, CApplication)
END_OBJECT_MAP()

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	//hRes = _Module.Init(ObjectMap, hInstance);
    hRes = _Module.Init(ObjectMap, hInstance, &LIBID_AUTONOTEPADLib);
	ATLASSERT(SUCCEEDED(hRes));


	int nRet = 0;
	TCHAR szTokens[] = _T("-/");
	BOOL bRun = TRUE;
	BOOL bAutomation = FALSE;

	LPCTSTR lpszToken = _Module.FindOneOf(::GetCommandLine(), szTokens);
	while(lpszToken != NULL)
	{
		if(lstrcmpi(lpszToken, _T("UnregServer")) == 0)
		{
			nRet = _Module.UnregisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("RegServer")) == 0)
		{
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		else if ((lstrcmpi(lpszToken, _T("Automation")) == 0) ||
			(lstrcmpi(lpszToken, _T("Embedding")) == 0))
		{
			bAutomation = true;
            _Module.SetAutomated(true);
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if(bRun)
	{
		_Module.StartMonitor();
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
		ATLASSERT(SUCCEEDED(hRes));
		hRes = ::CoResumeClassObjects();
		ATLASSERT(SUCCEEDED(hRes));

		if(bAutomation)
		{
			CMessageLoop theLoop;
            _Module.AddMessageLoop(&theLoop);
			nRet = theLoop.Run();
		}
		else
		{
            CComObjectGlobal<CApplication> app;
            nRet = app.Run(lpstrCmdLine, nCmdShow);
		}

		_Module.RevokeClassObjects();
		::Sleep(_Module.m_dwPause);
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
