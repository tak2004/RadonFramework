#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/String.hpp"
#include <math.h>
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

String SetLocaleUnix(const LocaleCategory::Type Category, const String& Locale)
{
    const int LOCALECATEGORYMAPPER[LocaleCategory::MAX] = {LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME};
    return String::UnsafeStringCreation(
        setlocale(LOCALECATEGORYMAPPER[Category], Locale.c_str()),
        RF_Common::DataManagment::TransfereOwnership);
}

const String& GetLocaleUnix()
{
    static String globalLocale;
    if (globalLocale.Size() == 0)
        globalLocale = String::UnsafeStringCreation(
            setlocale(LC_ALL, 0), RF_Common::DataManagment::TransfereOwnership);
    return globalLocale;
}

Bool ToUpperUnix(String& Instance)
{
    unsigned c;
    unsigned char *p = const_cast<unsigned char *>(reinterpret_cast<const unsigned char*>(Instance.c_str()));
    while (c = *p) *p++ = toupper(c);
}

Bool ToLowerUnix(String& Instance)
{
    unsigned c;
    unsigned char *p = const_cast<unsigned char *>(reinterpret_cast<const unsigned char*>(Instance.c_str()));
    while (c = *p) *p++ = tolower(c);
}

Size CStringSizeOfUnix(const UInt8* Buffer, const Size BufferSize)
{
    return strnlen(reinterpret_cast<const char*>(Buffer), BufferSize) + sizeof('\0');
}

Size LengthUnix(const UInt8* Buffer, const Size BufferSize)
{
    char const * pos = reinterpret_cast<const char*>(Buffer);
    char const * end = pos + BufferSize;
    Size length = 0;

    while(*pos != '\0' && pos != end)
    {
        ++length;
        pos += mblen(pos, end-pos);
    }

    return length;
}

Bool ToInt64Unix(const String& Instance, Int32 Base, Int64& Out)
{
    Out = strtol(Instance.c_str(), 0, Base);
    return !(errno == ERANGE && (Out == LONG_MIN || Out == LONG_MAX));
}

Bool ToUInt64Unix(const String& Instance, Int32 Base, UInt64& Out)
{
    Out = strtoul(Instance.c_str(), 0, Base);
    return !(errno == ERANGE && Out == ULONG_MAX);
}

Bool ToFloat64Unix(const String& Instance, Float64& Out)
{
    Out = strtod(Instance.c_str(), 0);
    return Out > Math::Float64::EPSILION &&
           !(errno == ERANGE && (
           Math::Float64::FAbs(Out + HUGE_VAL) < Math::Float64::EPSILION ||
           Math::Float64::FAbs(Out - HUGE_VAL) < Math::Float64::EPSILION));
}

Int32 FormatUnix(RF_Type::UInt8* Buffer, RF_Type::Size BufferSize, const String& Format, va_list arg)
{
    return vsnprintf(reinterpret_cast<char*>(Buffer), BufferSize, Format.c_str(), arg);
}

const UInt8* FindUnix(const RF_Type::UInt8* Buffer, RF_Type::Size BufferSize, 
    const RF_Type::UInt8* LookingFor, RF_Type::Size LookingForSize)
{
    const UInt8* result = reinterpret_cast<const UInt8*>(strstr(reinterpret_cast<const char*>(Buffer), 
        reinterpret_cast<const char*>(LookingFor)));
    return result;
}

void RF_SysStr::Dispatch()
{
    SetLocale = SetLocaleUnix;
    GetLocale = GetLocaleUnix;
    ToUpper = ToUpperUnix;
    ToLower = ToLowerUnix;
    CStringSizeOf = CStringSizeOfUnix;
    Length = LengthUnix;
    ToInt64 = ToInt64Unix;
    ToUInt64 = ToUInt64Unix;
    ToFloat64 = ToFloat64Unix;
    Format = FormatUnix;
    Find = FindUnix;

    #ifdef RF_LINUX
    extern void DispatchLinux();
    DispatchLinux();
    #endif
}