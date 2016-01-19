#ifndef _Module_h_INCLUDE
#define _Module_h_INCLUDE

class CAutomationAppModule : public CServerAppModule
{
public:
    CAutomationAppModule() : m_bAutomation(false) {}

    LONG Lock() 
    {
        ATLTRACE(_T("_Module.Lock() %d -> %d\n"), m_nLockCnt, m_nLockCnt + 1);
        return CServerAppModule::Lock();
    }
    LONG Unlock ()
    {
        ATLTRACE(_T("_Module.Unlock() %d -> %d\n"), m_nLockCnt, m_nLockCnt - 1);
        return CServerAppModule::Unlock();
    }

    void SetAutomated(bool b = true) { m_bAutomation = b; }
    bool IsAutomated() const { return m_bAutomation; }
    bool m_bAutomation;
};

#endif // _Module_h_INCLUDE