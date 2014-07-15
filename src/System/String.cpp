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
    RFSTR::Format = 0;
    Dispatch();
    Assert(RFSTR::Format != FormatCallback_SystemAPIDispatcher,
           "Function was called and couldn't be dispatched");
    return RFSTR::Format(Buffer, BufferSize, Format, arg);
}

SetLocaleCallback RFSTR::SetLocale = SetLocale_SystemAPIDispatcher;
GetLocaleCallback RFSTR::GetLocale = GetLocaleCallback_SystemAPIDispatcher;
ToUpperCallback RFSTR::ToUpper = ToUpperCallback_SystemAPIDispatcher;
ToLowerCallback RFSTR::ToLower = ToLowerCallback_SystemAPIDispatcher;
SizeCallback RFSTR::CStringSizeOf = SizeCallback_SystemAPIDispatcher;
LengthCallback RFSTR::Length = LengthCallback_SystemAPIDispatcher;
ToInt64Callback RFSTR::ToInt64 = ToInt64Callback_SystemAPIDispatcher;
ToUInt64Callback RFSTR::ToUInt64 = ToUInt64Callback_SystemAPIDispatcher;
ToFloat64Callback RFSTR::ToFloat64 = ToFloat64Callback_SystemAPIDispatcher;
FormatCallback RFSTR::Format = FormatCallback_SystemAPIDispatcher;

Bool RFSTR::IsSuccessfullyDispatched()
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
    return result;
}

void RFSTR::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (SetLocale == SetLocale_SystemAPIDispatcher || SetLocale == 0) 
        Result.AddLast("SetLocale");
    if (GetLocale == GetLocaleCallback_SystemAPIDispatcher || GetLocale == 0) 
        Result.AddLast("GetLocale");
    if (ToUpper == ToUpperCallback_SystemAPIDispatcher || ToUpper == 0)
        Result.AddLast("ToUpper");
    if (ToLower == ToLowerCallback_SystemAPIDispatcher || ToLower == 0)
        Result.AddLast("ToLower");
    if(CStringSizeOf == SizeCallback_SystemAPIDispatcher || CStringSizeOf == 0)
        Result.AddLast("CStringSizeOf");
    if (Length == LengthCallback_SystemAPIDispatcher || Length == 0)
        Result.AddLast("Length");
    if (ToInt64 == ToInt64Callback_SystemAPIDispatcher || ToInt64 == 0)
        Result.AddLast("ToInt64");
    if (ToUInt64 == ToUInt64Callback_SystemAPIDispatcher || ToUInt64 == 0)
        Result.AddLast("ToUInt64");
    if (ToFloat64 == ToFloat64Callback_SystemAPIDispatcher || ToFloat64 == 0)
        Result.AddLast("ToFloat64");
    if (Format == FormatCallback_SystemAPIDispatcher || Format == 0)
        Result.AddLast("Format");
}