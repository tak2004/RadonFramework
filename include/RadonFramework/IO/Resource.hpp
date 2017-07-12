#ifndef RF_IO_RESOURCE_HPP
#define RF_IO_RESOURCE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::IO {

class Stream;
class ProtocolService;

class Resource
{
public:
    static RF_Mem::AutoPointer<Resource> FromUri(const RF_IO::Uri& Location);
    ~Resource();
    RF_Type::Bool Exists()const;
    RF_Type::Bool IsReadable()const;
    RF_Type::Bool IsWriteable()const;
    Stream* GetStream()const;
    RF_Type::Size GetSize();
    const Uri& Location()const;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> Read();
protected:
    Resource();
    Uri m_Location;
    ProtocolService* m_UsedProtocol;
    Stream* m_Stream;
};

}

#endif // RF_IO_RESOURCE_HPP