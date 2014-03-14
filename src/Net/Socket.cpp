#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/Socket.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/System/Network/SelectObjectCollector.hpp"

using namespace RadonFramework::Net;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::Network;

class RadonFramework::Net::PIMPL
{
    public:
        PIMPL()
        {
        }

        NetService::SocketHandler Handler;
        EndPoint LocalEndPoint;
};

AutoPointer<Socket> Socket::Create(NetService::SocketHandler& Handler)
{
    // Create the facade object.
    AutoPointer<Socket> result(new Socket());
    result->m_Data=new PIMPL();
    result->m_Data->Handler=Handler;
    return result;
}

AutoPointer<Socket> Socket::Create(const AddressFamily::Type Family, 
    const SocketType::Type Type, SocketError& Error)
{
    AutoPointer<Socket> result;
    // Create a socket resource.
    NetService::SocketHandler handler;
    Error::Type error=NetService::Create(handler,Family,Type);
    if (error==Error::Ok)
        result=Create(handler);
    Error.Code=error;
    return result;
}

AutoPointer<Socket> Socket::Create(const AddressFamily::Type Family, 
    const SocketType::Type Type)
{
    AutoPointer<Socket> result;
    // Create a socket resource.
    NetService::SocketHandler handler;
    Error::Type error=NetService::Create(handler,Family,Type);
    if (error==Error::Ok)
        result=Create(handler);
    return result;
}

Socket::Socket()
:m_Data(0)
{
}

Socket::~Socket()
{
    //Disconnect();
    if (m_Data)
    {
        delete m_Data;
        m_Data=0;
    }
}

SocketError Socket::Bind( const EndPoint &LocalEP )
{
    SocketError result;
    result.Code=NetService::Bind(m_Data->Handler,LocalEP);
    m_Data->LocalEndPoint=LocalEP;
    return result;
}

SocketError Socket::Accept(AutoPointer<Socket>& Client)
{
    SocketError res;
    NetService::SocketHandler clientHandle;
    EndPoint endPoint;
    res.Code=NetService::Accept(m_Data->Handler,clientHandle,endPoint);
    if (res)
    {
        Client=Create(clientHandle);
        Client->m_Data->LocalEndPoint=endPoint;
    }
    return res;
}

SocketError Socket::Connect( const EndPoint &RemoteEP )
{
    SocketError result;
    result.Code=NetService::Connect(m_Data->Handler,RemoteEP);
    if (result)
        m_Data->LocalEndPoint=RemoteEP;
    return result;
}

SocketError Socket::Connect( const IPAddress &IP, const UInt32 Port )
{
    EndPoint m_EndPoint(IP,Port);
    return Connect(m_EndPoint);
}

SocketError Socket::Listen(const UInt32 MaxWaitingClients)
{
    SocketError res;
    res.Code=NetService::Listen(m_Data->Handler,MaxWaitingClients);
    return res;
}

SocketError Socket::Receive(AutoPointerArray<UInt8>& Data)
{
    SocketError res;
    res.Code=NetService::Receive(m_Data->Handler,Data);
    return res;
}

SocketError Socket::ReceiveFrom(AutoPointerArray<UInt8>& Data, 
                                      const EndPoint &RemoteEP )
{
    SocketError res;
    res.Code=NetService::ReceiveFrom(m_Data->Handler,Data,RemoteEP);
    return res;
}

SocketError Socket::Send(const UInt8* Data, const UInt32 DataSize,
    UInt32& SendDataSize )
{
    SocketError res;
    res.Code=NetService::Send(m_Data->Handler,Data,DataSize,&SendDataSize);
    return res;
}
/*
SocketError RadonFramework::Net::Socket::SendTo( const char *Data, const UInt32 DataSize, const EndPoint &RemoteEP, RadonFramework::Core::Types::UInt32 *SendDataSize )
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->Send(Data,DataSize,RemoteEP,SendDataSize);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError RadonFramework::Net::Socket::Disconnect()
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
    {
        res=m_Backend->Shutdown(SocketShutdown::Both);
        if (res==SocketError::NoError)
        {
            res=m_Backend->Close();
            m_CreateSuccessful=false;
        }
    }
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type RadonFramework::Net::Socket::Shutdown(SocketShutdown::Type How)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->Shutdown(How);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

EndPoint RadonFramework::Net::Socket::RemoteEndPoint()
{
    if (m_Backend)
        return m_Backend->RemoteEndPoint();
    else
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=SocketError::NoBackendAvailable;
        OnError(arg);
    }
    return EndPoint();
}

EndPoint RadonFramework::Net::Socket::LocalEndPoint()
{
    if (m_Backend)
        return m_Backend->LocalEndPoint();
    else
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=SocketError::NoBackendAvailable;
        OnError(arg);
    }
    return EndPoint();
}

SocketError::Type RadonFramework::Net::Socket::GetSocketOption(const SocketOptionLevel::Type OptionLevel, const SocketOptionName::Type OptionName, Core::Types::Bool &Value)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->GetSocketOption(OptionLevel,OptionName,Value);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type RadonFramework::Net::Socket::GetSocketOption(const SocketOptionLevel::Type OptionLevel, const SocketOptionName::Type OptionName, Int32 &Value)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->GetSocketOption(OptionLevel,OptionName,Value);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type RadonFramework::Net::Socket::SetSocketOption(const SocketOptionLevel::Type OptionLevel, const SocketOptionName::Type OptionName, const Core::Types::Bool Value)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->SetSocketOption(OptionLevel,OptionName,Value);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type RadonFramework::Net::Socket::SetSocketOption(const SocketOptionLevel::Type OptionLevel, const SocketOptionName::Type OptionName, const Int32 Value)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->SetSocketOption(OptionLevel,OptionName,Value);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type Socket::SetReceiveTimeout(RadonFramework::Core::Types::UInt32 timeout)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->SetReceiveTimeout(timeout);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

SocketError::Type Socket::SetSendTimeout(RadonFramework::Core::Types::UInt32 timeout)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Backend)
        res=m_Backend->SetSendTimeout(timeout);
    else
        res=SocketError::NoBackendAvailable;

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}

Bool RadonFramework::Net::Socket::Available()
{
    return m_Backend?true:false;
}

Bool RadonFramework::Net::Socket::Working()
{
    return m_Backend && m_CreateSuccessful;
}

Bool RadonFramework::Net::Socket::Blocking()
{
    return m_Blocking;
}

SocketError::Type RadonFramework::Net::Socket::Blocking(const Core::Types::Bool NewValue)
{
    SocketError::Type res=SocketError::NoError;
    if (m_Blocking!=NewValue)
    {
        if (m_Backend)
        {
            res=m_Backend->SetBlockingMode(NewValue);
            if (res==SocketError::NoError)
                m_Blocking=NewValue;
        }
        else
            res=SocketError::NoBackendAvailable;
    }

    if (res!=SocketError::NoError)
    {
        SocketErrorArgument arg;
        arg.Sender=this;
        arg.Error=res;
        OnError(arg);
    }
    return res;
}
*/

void Socket::AssignSelectObjectCollector(SelectObjectCollector& Collector)const
{
    Collector.Add(m_Data->Handler);
}
