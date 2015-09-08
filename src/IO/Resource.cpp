#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Resource.hpp"
#include "RadonFramework/IO/Stream.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

Resource::~Resource()
{
}

Bool Resource::IsReadable()const
{
    Stream* stream=Reader();
    return stream->CanRead();
}

Bool Resource::IsWriteable()const
{
    Stream* stream=Writer();
    return stream->CanWrite();
}

Size Resource::GetSize()
{
    Size result=0;
    if (IsReadable())
    {
        Stream* stream=Reader();
        if (stream->CanSeek())
            result=stream->Length();
    }
    return result;
}

const Uri& Resource::Location()const
{
    return m_Location;
}

void Resource::Location(const Uri& NewLocation)
{
    m_Location=NewLocation;
}

AutoPointerArray<UInt8> Resource::Read()
{
    AutoPointerArray<UInt8> result;
    Size size=GetSize();
    if (size>0)
    {
        Stream* stream=Reader();
        AutoPointerArray<UInt8> data(size);
        stream->Read(data.Get(), 0, size);
        result=data;
    }
    return result;
}