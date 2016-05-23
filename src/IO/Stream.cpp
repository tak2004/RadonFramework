#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Stream.hpp"

namespace RadonFramework { namespace IO {

Stream::~Stream()
{

}

RF_Type::UInt64 Stream::WriteText(const RF_Type::String& ByValue)
{
    return Write(reinterpret_cast<const RF_Type::UInt8*>(ByValue.c_str()), 0, ByValue.Size()-1);
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Stream::ReadBytes(RF_Type::Size Bytes)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result(Bytes);
    RF_Type::UInt64 bytesRead = Read(result.Get(), 0, Bytes);
    if(bytesRead != Bytes)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newBuffer(bytesRead);
        RF_SysMem::Copy(newBuffer.Get(), result.Get(), bytesRead);
        result.Swap(newBuffer);
    }
    return result;
}

RF_Type::UInt64 Stream::WriteData(const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    return Write(Data.Get(), 0, Data.Count());
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Stream::PeekBytes(RF_Type::Size Bytes)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result(Bytes);
    RF_Type::UInt64 bytesRead = Peek(result.Get(), 0, Bytes);
    if(bytesRead != Bytes)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> newBuffer(bytesRead);
        RF_SysMem::Copy(newBuffer.Get(), result.Get(), bytesRead);
        result.Swap(newBuffer);
    }
    return result;
}

} }