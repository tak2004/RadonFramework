#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/String.hpp"
#include "RadonFramework/Math/Math.hpp"
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

using namespace RadonFramework::System::String;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;

String SetLocale(const LocaleCategory::Type Category, const String& Locale)
{
    const int LOCALECATEGORYMAPPER[LocaleCategory::MAX] = {LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME};
    return String(setlocale(LOCALECATEGORYMAPPER[Category], Locale.c_str()),
                  RadonFramework::Core::Common::DataManagment::TransfereOwnership);
}

const String& GetLocale()
{
    static String globalLocale;
    if (globalLocale.Size() == 0)
        globalLocale = String(setlocale(LC_ALL, 0), RadonFramework::Core::Common::DataManagment::TransfereOwnership);
    return globalLocale;
}

Bool ToUpper(String& Instance)
{
    unsigned c;
    unsigned char *p = const_cast<unsigned char *>(reinterpret_cast<const unsigned char*>(Instance.c_str()));
    while (c = *p) *p++ = toupper(c);
}

Bool ToLower(String& Instance)
{
    unsigned c;
    unsigned char *p = const_cast<unsigned char *>(reinterpret_cast<const unsigned char*>(Instance.c_str()));
    while (c = *p) *p++ = tolower(c);
}

Size Length(const UInt8* Buffer, const Size BufferSize)
{
    return strlen(reinterpret_cast<const char*>(Buffer));
}

Bool ToInt64(const String& Instance, Int32 Base, Int64& Out)
{
    Out = strtol(Instance.c_str(), 0, Base);
    return !(errno == ERANGE && (Out == LONG_MIN || Out == LONG_MAX));
}

Bool ToUInt64(const String& Instance, Int32 Base, UInt64& Out)
{
    Out = strtoul(Instance.c_str(), 0, Base);
    return !(errno == ERANGE && Out == ULONG_MAX);
}

Bool ToFloat64(const String& Instance, Float64& Out)
{
    Out = strtod(Instance.c_str(), 0);
    return Out > Math::Math<Float64>::EPSILION &&
           !(errno == ERANGE && (
           Math::Math<Float64>::FAbs(Out + HUGE_VAL) < Math::Math<Float64>::EPSILION ||
           Math::Math<Float64>::FAbs(Out - HUGE_VAL) < Math::Math<Float64>::EPSILION));
}

Int32 Format(RFTYPE::UInt8* Buffer, RFTYPE::Size BufferSize, const String& Format, va_list arg)
{
    return vsnprintf(reinterpret_cast<char*>(Buffer), BufferSize, Format.c_str(), arg);
}

void RFSTR::Dispatch()
{
    SetLocale = ::SetLocale;
    GetLocale = ::GetLocale;
    ToUpper = ::ToUpper;
    ToLower = ::ToLower;
    Length = ::Length;
    ToInt64 = ::ToInt64;
    ToUInt64 = ::ToUInt64;
    ToFloat64 = ::ToFloat64;
    Format = ::Format;

    #ifdef RF_LINUX
    extern void DispatchLinux();
    DispatchLinux();
    #endif
}