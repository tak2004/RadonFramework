#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/String.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::String;

String SetLocale_SystemAPIDispatcher(const LocaleCategory::Type Category, 
                                     const String& Locale)
{
    Dispatch();
    Assert(SetLocale != SetLocale_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return SetLocale(Category, Locale);
}

const String& GetLocaleCallback_SystemAPIDispatcher()
{
    Dispatch();
    Assert(GetLocale != GetLocaleCallback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetLocale();
}

Bool ToUpperCallback_SystemAPIDispatcher(String& Instance)
{
    Dispatch();
    Assert(ToUpper != ToUpperCallback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ToUpper(Instance);
}

Bool ToLowerCallback_SystemAPIDispatcher(String& Instance)
{
    Dispatch();
    Assert(ToLower != ToLowerCallback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ToLower(Instance);
}

Size LengthCallback_SystemAPIDispatcher(const UInt8* Buffer, const Size BufferSize)
{
    Dispatch();
    Assert(Length != LengthCallback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Length(Buffer, BufferSize);
}

Bool ToInt64Callback_SystemAPIDispatcher(const String& Instance, Int32 Base,
                                         Int64& Out)
{
    Dispatch();
    Assert(ToInt64 != ToInt64Callback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ToInt64(Instance, Base, Out);
}

Bool ToUInt64Callback_SystemAPIDispatcher(const String& Instance, Int32 Base,
                                          UInt64& Out)
{
    Dispatch();
    Assert(ToUInt64 != ToUInt64Callback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ToUInt64(Instance, Base, Out);
}

Bool ToFloat64Callback_SystemAPIDispatcher(const String& Instance, Float64& Out)
{
    Dispatch();
    Assert(ToFloat64 != ToFloat64Callback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ToFloat64(Instance, Out);
}


Int32 FormatCallback_SystemAPIDispatcher(RFTYPE::UInt8* Buffer, RFTYPE::Size BufferSize,
                                         const RFTYPE::String& Format, va_list arg)
{
    Dispatch();
    Assert(RFSTR::Format != FormatCallback_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return RFSTR::Format(Buffer, BufferSize, Format, arg);
}

SetLocaleCallback RFSTR::SetLocale = SetLocale_SystemAPIDispatcher;
GetLocaleCallback RFSTR::GetLocale = GetLocaleCallback_SystemAPIDispatcher;
ToUpperCallback RFSTR::ToUpper = ToUpperCallback_SystemAPIDispatcher;
ToLowerCallback RFSTR::ToLower = ToLowerCallback_SystemAPIDispatcher;
LengthCallback RFSTR::Length = LengthCallback_SystemAPIDispatcher;
ToInt64Callback RFSTR::ToInt64 = ToInt64Callback_SystemAPIDispatcher;
ToUInt64Callback RFSTR::ToUInt64 = ToUInt64Callback_SystemAPIDispatcher;
ToFloat64Callback RFSTR::ToFloat64 = ToFloat64Callback_SystemAPIDispatcher;
FormatCallback RFSTR::Format = FormatCallback_SystemAPIDispatcher;

Bool RFSTR::IsSuccessfullyDispatched()
{
    Bool result=true;
    result = result && SetLocale != SetLocale_SystemAPIDispatcher;
    result = result && GetLocale != GetLocaleCallback_SystemAPIDispatcher;
    result = result && ToUpper != ToUpperCallback_SystemAPIDispatcher;
    result = result && ToLower != ToLowerCallback_SystemAPIDispatcher;
    result = result && Length != LengthCallback_SystemAPIDispatcher;
    result = result && ToInt64 != ToInt64Callback_SystemAPIDispatcher;
    result = result && ToUInt64 != ToUInt64Callback_SystemAPIDispatcher;
    result = result && ToFloat64 != ToFloat64Callback_SystemAPIDispatcher;
    result = result && Format != FormatCallback_SystemAPIDispatcher;
    return result;
}

void RFSTR::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (SetLocale == SetLocale_SystemAPIDispatcher) 
        Result.AddLast("SetLocale");
    if (GetLocale == GetLocaleCallback_SystemAPIDispatcher) 
        Result.AddLast("GetLocale");
    if (ToUpper == ToUpperCallback_SystemAPIDispatcher)
        Result.AddLast("ToUpper");
    if (ToLower == ToLowerCallback_SystemAPIDispatcher)
        Result.AddLast("ToLower");
    if (Length == LengthCallback_SystemAPIDispatcher)
        Result.AddLast("Length");
    if (ToInt64 == ToInt64Callback_SystemAPIDispatcher)
        Result.AddLast("ToInt64");
    if (ToUInt64 == ToUInt64Callback_SystemAPIDispatcher)
        Result.AddLast("ToUInt64");
    if (ToFloat64 == ToFloat64Callback_SystemAPIDispatcher)
        Result.AddLast("ToFloat64");
    if (Format == FormatCallback_SystemAPIDispatcher)
        Result.AddLast("Format");
}