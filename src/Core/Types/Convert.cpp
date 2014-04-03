#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/Convert.hpp"
#include "RadonFramework/Math/Math.hpp"

using namespace RadonFramework::Core::Types;

Bool Convert::ToBool(const bool Value)
{
    Bool result={Value};
    return result;
}

Bool Convert::ToBool(const String& In, Bool& Out)
{
    Bool result=false;
    String tmp(In);
    tmp.ToLower();
    if (tmp=="true")
    {
        Out=true;
        result=true;
    }
    if (tmp=="false")
    {
        Out=false;
        result=true;
    }
    return result;
}

Bool Convert::ToInt8(const String& In, Int8& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Int64 n;
        if (RFSTR::ToInt64(In, 10, n) && n >= Int8Min && n <= Int8Max)
        {
            Out = static_cast<UInt8>(n);
            result = true;
        }
    }
    return result;
}

Bool Convert::ToInt16(const String& In, Int16& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Int64 n;
        if (RFSTR::ToInt64(In, 10, n) && n >= Int16Min && n <= Int16Max)
        {
            Out = static_cast<UInt16>(n);
            result = true;
        }
    }
    return result;
}

Bool Convert::ToInt32(const String& In, Int32& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Int64 n;;
        if (RFSTR::ToInt64(In, 10, n) && n >= Int32Min && n <= Int32Max)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

Bool Convert::ToInt64(const String& In, Int64& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Int64 n;
        if (RFSTR::ToInt64(In, 10, n) && n >= Int64Min && n <= Int64Max)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

Bool Convert::ToUInt8(const String& In, UInt8& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        UInt64 n;
        if (RFSTR::ToUInt64(In, 10, n) && n >= UInt8Min && n <= UInt8Max)
        {
            Out = static_cast<UInt8>(n);
            result = true;
        }
    }
    return result;
}

Bool Convert::ToUInt16(const String& In, UInt16& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        UInt64 n;
        if (RFSTR::ToUInt64(In, 10, n) && n >= UInt16Min && n <= UInt16Max)
        {
            Out = static_cast<UInt16>(n);
            result = true;
        }
    }
    return result;
}

Bool Convert::ToUInt32(const String& In, UInt32& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        UInt64 n;
        if (RFSTR::ToUInt64(In, 10, n) && n >= UInt32Min && n <= UInt32Max)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

Bool Convert::ToUInt64(const String& In, UInt64& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        UInt64 n;
        if (RFSTR::ToUInt64(In, 10, n) && n >= UInt64Min && n <= UInt64Max)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

Bool Convert::ToFloat32(const String& In, Float32& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Float64 n;
        if (RFSTR::ToFloat64(In, n) && n >= Float32Min && n <= Float32Max)
        {
            Out = static_cast<Float32>(n);
            result = true;
        }
    }
    return result;
}

Bool Convert::ToFloat64(const String& In, Float64& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        Float64 n;
        if (RFSTR::ToFloat64(In, n) && n >= Float64Min && n <= Float64Max)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

Bool Convert::ToSize(const String& In, Size& Out)
{
    Bool result=false;
    if (In.Length() > 0)
    {
        UInt64 n;
        if (RFSTR::ToUInt64(In, 10, n) && n >= SizeMin && n <= SizeMax)
        {
            Out = n;
            result = true;
        }
    }
    return result;
}

String Convert::ToString(const Bool Value)
{
    String result(Value?"true":"false");
    return result;
}

String Convert::ToString(const Int8 Value)
{
    return String::Format("%i", Value);
}

String Convert::ToString(const Int16 Value)
{
    return String::Format("%i",Value);
}

String Convert::ToString(const Int32 Value)
{
    return String::Format("%i",Value);
}

String Convert::ToString(const Int64 Value)
{
    return String::Format("%lld",Value);
}

String Convert::ToString(const UInt8 Value)
{
    return String::Format("%u", Value);
}

String Convert::ToString(const UInt16 Value)
{
    return String::Format("%u", Value);
}

String Convert::ToString(const UInt32 Value)
{
    return String::Format("%u", Value);
}

String Convert::ToString(const UInt64 Value)
{
    return String::Format("%llu", Value);
}

String Convert::ToString(const Float32 Value)
{
    return String::Format("%f", Value);
}

String Convert::ToString(const Float64 Value)
{
    return String::Format("%f", Value);
}


#define STRING_TO(T, COMPARE_OPERATOR, CONVERT_FUNCTION) template<>\
Bool Convert::StringTo<T>(const String& In, T& Out)\
{\
    Bool result = false; \
    if (In.COMPARE_OPERATOR())\
        result = CONVERT_FUNCTION(In, Out); \
    return result;\
}

STRING_TO(Bool, IsBoolean, ToBool)
STRING_TO(Int8, IsNumber, ToInt8)
STRING_TO(Int16, IsNumber, ToInt16)
STRING_TO(Int32, IsNumber, ToInt32)
STRING_TO(Int64, IsNumber, ToInt64)
STRING_TO(UInt8, IsNumber, ToUInt8)
STRING_TO(UInt16, IsNumber, ToUInt16)
STRING_TO(UInt32, IsNumber, ToUInt32)
STRING_TO(UInt64, IsNumber, ToUInt64)
STRING_TO(Float32, IsFloatingpointNumber, ToFloat32)
STRING_TO(Float64, IsFloatingpointNumber, ToFloat64)
#undef STRING_TO