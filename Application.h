// Application.h : Declaration of the CApplication

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "resource.h"       // main symbols
#include "MainFrm.h"
#include "AutoNotepadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CApplication
class ATL_NO_VTABLE CApplication : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CApplication, &CLSID_Application>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CApplication>,
	public IDispatchImpl<IApplication, &IID_IApplication, &LIBID_AUTONOTEPADLib>,
	public CProxy_IApplicationEvents< CApplication >
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_APPLICATION)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

	CApplication();
    HRESULT FinalConstruct();
    void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IApplication
    STDMETHOD(get_Text)(BSTR *pVal);
    STDMETHOD(put_Text)(BSTR newVal);
    STDMETHOD(get_Visible)(VARIANT_BOOL *pVal);
    STDMETHOD(put_Visible)(VARIANT_BOOL newVal);

// Internal methods
    int Run(LPTSTR lpstrCmdLine, int nShow);

private:
    CMainFrame   m_wndMain;
    int          m_nWindowState;
    CComBSTR     m_sText;

public:
    BEGIN_COM_MAP(CApplication)
	    COM_INTERFACE_ENTRY(IApplication)
	    COM_INTERFACE_ENTRY(IDispatch)
	    COM_INTERFACE_ENTRY(ISupportErrorInfo)
	    COM_INTERFACE_ENTRY(IConnectionPointContainer)
	    COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(CApplication)
    CONNECTION_POINT_ENTRY(DIID__IApplicationEvents)
    END_CONNECTION_POINT_MAP()
};

#endif //__APPLICATION_H_
