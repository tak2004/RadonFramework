#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Network/SelectObjectCollector.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/System/Network/OSSocketError.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"
#include <errno.h>

using namespace RadonFramework::Time;
using namespace RadonFramework::Net;
using namespace RadonFramework::Memory;
using namespace RadonFramework::System::Network;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

#if defined(RF_WINDOWS)
    /** Define WINVER and NT Version to WIN_VERSION_XP.
      * GetAdaptersInfo is available since windows xp(NT Kernel 501).
      * To be sure that all the cool features of windows API are available it's
      * necessary to define windows xp as minimum API.
      **/
    static const int WIN_VERSION_XP=0x501;
    #define WINVER 0x501
    #define _WIN32_WINNT 0x501
    #define WIN32_LEAN_AND_MEAN

    #include <windows.h>
    #include <winsock2.h>
#endif

#if defined(RF_UNIX)
    #include <sys/select.h>
    #include <sys/errno.h>

#endif

class SelectObjectCollector::PIMPL
{
public:
    fd_set FileDescriptors;
    fd_set Lookup;
    Size FDCount;
    Array<NetService::SocketHandler> Sockets;
};

SelectObjectCollector::SelectObjectCollector()
:m_Data(0)
{

}

SelectObjectCollector::~SelectObjectCollector()
{
    if (m_Data)
    {
        delete m_Data;
        m_Data=0;
    }
}

SelectObjectCollector::SelectObjectCollector(const SelectObjectCollector& Copy)
{

}

Size SelectObjectCollector::Count()const
{
    return m_Data->Sockets.Count();
}

Bool SelectObjectCollector::IsSet(const Size Index)const
{
    Assert(Index<m_Data->Sockets.Count(),"Index out of bound.");
    return FD_ISSET(m_Data->Sockets(Index),&m_Data->Lookup)!=0;
}

Error::Type SelectObjectCollector::Select(
    const SelectMode::Type Mode, const TimeSpan* Timeout)
{
    Error::Type result=Error::Ok;
    int ret=-1;
    AutoPointer<timeval> timeout;
    if (Timeout)
    {
        timeout=AutoPointer<timeval>(new timeval);
        timeout->tv_sec=Timeout->Seconds();
        timeout->tv_usec=Timeout->Microseconds();
    }    

    Bool done;
    m_Data->Lookup=m_Data->FileDescriptors;
    do
    {
        done=true;

        switch (Mode)
        {
            case SelectMode::Error:
                ret=select(static_cast<int>(m_Data->FDCount), 0, 0, &m_Data->Lookup, timeout.Get());
                break;
            case SelectMode::Read:
                ret=select(static_cast<int>(m_Data->FDCount), &m_Data->Lookup, 0, 0, timeout.Get());
                break;
            case SelectMode::Write:
                ret=select(static_cast<int>(m_Data->FDCount), 0, &m_Data->Lookup, 0, timeout.Get());
                break;
            case SelectMode::ReadWrite:
                ret=select(static_cast<int>(m_Data->FDCount), &m_Data->Lookup,
                        &m_Data->Lookup, 0, timeout.Get());
                break;
            case SelectMode::ReadError:
                ret=select(static_cast<int>(m_Data->FDCount), &m_Data->Lookup, 0,
                        &m_Data->Lookup, timeout.Get());
                break;
            case SelectMode::WriteError:
                ret=select(static_cast<int>(m_Data->FDCount), 0, &m_Data->Lookup,
                        &m_Data->Lookup, timeout.Get());
                break;
            case SelectMode::ReadWriteError:
                ret=select(static_cast<int>(m_Data->FDCount), &m_Data->Lookup,
                        &m_Data->Lookup, &m_Data->Lookup, timeout.Get());
                break;
        }
    
        if (ret==0)
            result=Error::IsTimedOut;

        if (ret==-1)
        {
            if (errno==EINTR)
                done=false;
            else
                result=OSSocketError::ConvertOSError();
        }
    }while(!done);

    return result;
}

AutoPointer<SelectObjectCollector> SelectObjectCollector::Create(
    const Socket& Handler)
{
    AutoPointer<SelectObjectCollector> result(new SelectObjectCollector());
    if (result)
    {
        result->m_Data=new PIMPL();
        FD_ZERO(&result->m_Data->FileDescriptors);
        result->m_Data->FDCount=0;
        Handler.AssignSelectObjectCollector(*result);
    }
    return result;
}

void SelectObjectCollector::Add(const NetService::SocketHandler& Handler)
{
    m_Data->Sockets.Resize(m_Data->Sockets.Count()+1);
    m_Data->Sockets(m_Data->FDCount)=Handler;
    FD_SET(Handler,&m_Data->FileDescriptors);
    ++m_Data->FDCount;
}

void SelectObjectCollector::Remove(const Size Index)
{
    FD_CLR(m_Data->Sockets(Index),&m_Data->FileDescriptors);
    --m_Data->FDCount;    

    if (Index==m_Data->FDCount)
        m_Data->Sockets.Resize(m_Data->FDCount);
    else
    {
        Array<NetService::SocketHandler> tmp(m_Data->FDCount);
        if (Index>0)
            m_Data->Sockets.Copy(tmp,Index-1);
        m_Data->Sockets.Copy(Index+1,tmp,Index,m_Data->FDCount-Index);
        m_Data->Sockets=tmp;
    }    
}
