#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/String.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::String;

String SetLocale_SystemAPIDispatcher(const LocaleCategory::Type Category, 
                                     const String& Locale)
{
    SetLocale = 0;
    Dispatch();
    Assert(SetLocale != SetLocale_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return SetLocale(Category, Locale);
}

const String& GetLocaleCallback_SystemAPIDispatcher()
{
    GetLocale = 0;
    Dispatch();
    Assert(GetLocale != GetLocaleCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return GetLocale();
}

Bool ToUpperCallback_SystemAPIDispatcher(String& Instance)
{
    ToUpper = 0;
    Dispatch();
    Assert(ToUpper != ToUpperCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return ToUpper(Instance);
}

Bool ToLowerCallback_SystemAPIDispatcher(String& Instance)
{
    ToLower = 0;
    Dispatch();
    Assert(ToLower != ToLowerCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return ToLower(Instance);
}

Size SizeCallback_SystemAPIDispatcher(const UInt8* Buffer, const Size BufferSize)
{
    CStringSizeOf = 0;
    Dispatch();
    Assert(CStringSizeOf != SizeCallback_SystemAPIDispatcher,
        "Function was called and couldn't be dispatched");
    return CStringSizeOf(Buffer, BufferSize);
}

Size LengthCallback_SystemAPIDispatcher(const UInt8* Buffer, const Size BufferSize)
{
    Length = 0;
    Dispatch();
    Assert(Length != LengthCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return Length(Buffer, BufferSize);
}

Bool ToInt64Callback_SystemAPIDispatcher(const String& Instance, Int32 Base,
                                         Int64& Out)
{
    ToInt64 = 0;
    Dispatch();
    Assert(ToInt64 != ToInt64Callback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return ToInt64(Instance, Base, Out);
}

Bool ToUInt64Callback_SystemAPIDispatcher(const String& Instance, Int32 Base,
                                          UInt64& Out)
{
    ToUInt64 = 0;
    Dispatch();
    Assert(ToUInt64 != ToUInt64Callback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return ToUInt64(Instance, Base, Out);
}

Bool ToFloat64Callback_SystemAPIDispatcher(const String& Instance, Float64& Out)
{
    ToFloat64 = 0;
    Dispatch();
    Assert(ToFloat64 != ToFloat64Callback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return ToFloat64(Instance, Out);
}


Int32 FormatCallback_SystemAPIDispatcher(RF_Type::UInt8* Buffer, RF_Type::Size BufferSize,
                                         const RF_Type::String& Format, va_list arg)
{
    RF_SysStr::Format = 0;
    Dispatch();
    Assert(RF_SysStr::Format != FormatCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return RF_SysStr::Format(Buffer, BufferSize, Format, arg);
}

const UInt8* FindCallback_SystemAPIDispatcher(const RF_Type::UInt8* Buffer, 
    RF_Type::Size BufferSize, const RF_Type::UInt8* LookingFor, 
    RF_Type::Size LookingForSize)
{
    RF_SysStr::Find = 0;
    Dispatch();
    Assert(RF_SysStr::Find != FindCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return RF_SysStr::Find(Buffer, BufferSize, LookingFor, LookingForSize);
}

SetLocaleCallback RF_SysStr::SetLocale = SetLocale_SystemAPIDispatcher;
GetLocaleCallback RF_SysStr::GetLocale = GetLocaleCallback_SystemAPIDispatcher;
ToUpperCallback RF_SysStr::ToUpper = ToUpperCallback_SystemAPIDispatcher;
ToLowerCallback RF_SysStr::ToLower = ToLowerCallback_SystemAPIDispatcher;
SizeCallback RF_SysStr::CStringSizeOf = SizeCallback_SystemAPIDispatcher;
LengthCallback RF_SysStr::Length = LengthCallback_SystemAPIDispatcher;
ToInt64Callback RF_SysStr::ToInt64 = ToInt64Callback_SystemAPIDispatcher;
ToUInt64Callback RF_SysStr::ToUInt64 = ToUInt64Callback_SystemAPIDispatcher;
ToFloat64Callback RF_SysStr::ToFloat64 = ToFloat64Callback_SystemAPIDispatcher;
FormatCallback RF_SysStr::Format = FormatCallback_SystemAPIDispatcher;
FindCallback RF_SysStr::Find = FindCallback_SystemAPIDispatcher;

Bool RF_SysStr::IsSuccessfullyDispatched()
{
    Bool result=true;
    result = result && SetLocale != SetLocale_SystemAPIDispatcher && SetLocale != 0;
    result = result && GetLocale != GetLocaleCallback_SystemAPIDispatcher && GetLocale != 0;
    result = result && ToUpper != ToUpperCallback_SystemAPIDispatcher && ToUpper != 0;
    result = result && ToLower != ToLowerCallback_SystemAPIDispatcher && ToLower != 0;
    result = result && CStringSizeOf != SizeCallback_SystemAPIDispatcher && CStringSizeOf != 0;
    result = result && Length != LengthCallback_SystemAPIDispatcher && Length != 0;
    result = result && ToInt64 != ToInt64Callback_SystemAPIDispatcher && ToInt64 != 0;
    result = result && ToUInt64 != ToUInt64Callback_SystemAPIDispatcher && ToUInt64 != 0;
    result = result && ToFloat64 != ToFloat64Callback_SystemAPIDispatcher && ToFloat64 != 0;
    result = result && Format != FormatCallback_SystemAPIDispatcher && Format != 0;
    result = result && Find != FindCallback_SystemAPIDispatcher && Find != 0;
    return result;
}

void RF_SysStr::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (SetLocale == SetLocale_SystemAPIDispatcher || SetLocale == 0) 
        Result.AddLast(RF_Type::String("SetLocale"));
    if (GetLocale == GetLocaleCallback_SystemAPIDispatcher || GetLocale == 0) 
        Result.AddLast(RF_Type::String("GetLocale"));
    if (ToUpper == ToUpperCallback_SystemAPIDispatcher || ToUpper == 0)
        Result.AddLast(RF_Type::String("ToUpper"));
    if (ToLower == ToLowerCallback_SystemAPIDispatcher || ToLower == 0)
        Result.AddLast(RF_Type::String("ToLower"));
    if(CStringSizeOf == SizeCallback_SystemAPIDispatcher || CStringSizeOf == 0)
        Result.AddLast(RF_Type::String("CStringSizeOf"));
    if (Length == LengthCallback_SystemAPIDispatcher || Length == 0)
        Result.AddLast(RF_Type::String("Length"));
    if (ToInt64 == ToInt64Callback_SystemAPIDispatcher || ToInt64 == 0)
        Result.AddLast(RF_Type::String("ToInt64"));
    if (ToUInt64 == ToUInt64Callback_SystemAPIDispatcher || ToUInt64 == 0)
        Result.AddLast(RF_Type::String("ToUInt64"));
    if (ToFloat64 == ToFloat64Callback_SystemAPIDispatcher || ToFloat64 == 0)
        Result.AddLast(RF_Type::String("ToFloat64"));
    if (Format == FormatCallback_SystemAPIDispatcher || Format == 0)
        Result.AddLast(RF_Type::String("Format"));
    if (Find == FindCallback_SystemAPIDispatcher || Find == 0)
        Result.AddLast(RF_Type::String("Find"));
}