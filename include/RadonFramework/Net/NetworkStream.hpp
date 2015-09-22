#ifndef RF_NET_NETWORKSTREAM_HPP
#define RF_NET_NETWORKSTREAM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Stream.hpp>

namespace RadonFramework { namespace Net {

template<typename CLASS>
class NetworkStream:public CLASS
{
public:
    static_assert(std::is_base_of<RF_IO::Stream, CLASS>::value, "Have to be derived from Stream!");

    template<typename T>
    RF_Type::UInt64 WriteType(const T& ByValue);

    template<typename T>
    RF_Type::UInt64 ReadType(T& ByValue);

    template<typename T>
    static T Convert(const T& Value);
};

template<typename CLASS>
template<typename T>
RF_Type::UInt64 NetworkStream<CLASS>::WriteType(const T& ByValue)
{
    return CLASS::WriteType<T>(Convert(ByValue));
}

template<typename CLASS>
template<typename T>
RF_Type::UInt64 NetworkStream<CLASS>::ReadType(T& ByValue)
{
    RF_Type::UInt64 result = CLASS::ReadType<T>(ByValue);
    ByValue = Convert(ByValue);
    return result;
}

template<typename CLASS>
template<typename T>
T NetworkStream<CLASS>::Convert(const T& Value)
{
    T result = Value;
    static RF_Type::Bool DifferentEndian = RF_Sys::CompilerConfig::Endianness != RF_Sys::Endian::Big;
    static RF_Type::Bool NeedConversion = (sizeof(T) == 2 ||
        sizeof(T) == 4 || sizeof(T) == 8) && DifferentEndian;

    if(NeedConversion)
    {
        T varSwapped;
        for(long i = 0; i < static_cast<long>(sizeof(Value)); i++)
            ((char*)(&varSwapped))[sizeof(Value) - 1 - i] = ((char*)(&Value))[i];
        for(long i = 0; i < static_cast<long>(sizeof(Value)); i++)
            ((char*)(&result))[i] = ((char*)(&varSwapped))[i];
    }
    return result;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_NET_NETWORKSTREAM_HPP