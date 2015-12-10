#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Resource.hpp"
#include "RadonFramework/IO/Stream.hpp"
#include "RadonFramework/IO/ProtocolServiceLocator.hpp"

namespace RadonFramework { namespace IO {

Resource::~Resource()
{
    if(m_UsedProtocol)
    {
        m_UsedProtocol->FreeInterface(m_Location);
        m_Stream = 0;
    }
}

RF_Type::Bool Resource::Exists() const
{
    return m_UsedProtocol->Exists(m_Location);
}

RF_Type::Bool Resource::IsReadable()const
{
    return m_Stream->CanRead();
}

RF_Type::Bool Resource::IsWriteable()const
{
    return m_Stream->CanWrite();
}

Stream* Resource::GetStream() const
{
    return m_Stream;
}

RF_Type::Size Resource::GetSize()
{
    RF_Type::Size result=0;
    if (IsReadable())
    {
        if (m_Stream->CanSeek())
            result= m_Stream->Length();
    }
    return result;
}

const Uri& Resource::Location()const
{
    return m_Location;
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Resource::Read()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    RF_Type::Size size=GetSize();
    if (size>0)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> data(size);
        m_Stream->Read(data.Get(), 0, size);
        result=data;
    }
    return result;
}

Resource::Resource()
:m_UsedProtocol(0)
,m_Stream(0)
{
}

RF_Mem::AutoPointer<Resource> Resource::FromUri(const RF_IO::Uri& Location)
{
    RF_Mem::AutoPointer<Resource> result;
    auto& protocol = ProtocolServiceLocator::Find(Location.Scheme());
    if(!ProtocolServiceLocator::IsNullService(protocol))
    {
        result = RF_Mem::AutoPointer<Resource>(new Resource);
        result->m_Location = Location;
        result->m_UsedProtocol = &protocol;
        result->m_Stream = protocol.GenerateInterface(result->m_Location);
    }
    return result;
}

} }