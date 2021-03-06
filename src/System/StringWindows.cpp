#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/String.hpp"
#include <math.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <mbstring.h>
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/Math/Float64.hpp"

using namespace RadonFramework::System::String;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework;

String SetLocale(const LocaleCategory::Type Category, const String& Locale)
{
    const int LOCALECATEGORYMAPPER[LocaleCategory::MAX] = {LC_ALL, LC_COLLATE, LC_CTYPE, LC_MONETARY, LC_NUMERIC, LC_TIME};
    return String::UnsafeStringCreation(
            setlocale(LOCALECATEGORYMAPPER[Category], Locale.c_str()));
}

const String& GetLocale()
{
    static String globalLocale;
    if (globalLocale.Size() == 0)
        globalLocale = String::UnsafeStringCreation(setlocale(LC_ALL, 0));
    return globalLocale;
}

Bool ToUpper(String& Instance)
{
	Bool result = false;
	if (!Instance.IsEmpty())
	{
		result = _strupr_s(const_cast<char*>(Instance.c_str()), Instance.Size()) == 0;
	}
	return result;
}

Bool ToLower(String& Instance)
{
	Bool result = false;
	if (!Instance.IsEmpty())
	{
		result = _strlwr_s(const_cast<char*>(Instance.c_str()), Instance.Size()) == 0;
	}
    return result;
}

Size StrSize(const UInt8* Buffer, const Size BufferSize)
{
    return strnlen(reinterpret_cast<const char*>(Buffer), BufferSize) + sizeof('\0');
}

Size Length(const UInt8* Buffer, const Size BufferSize)
{
    return _mbsnlen(Buffer, BufferSize);
}

Bool ToInt64(const String& Instance, Int32 Base, Int64& Out)
{
    errno = 0;
    Out = strtol(Instance.c_str(), 0, Base);

    Bool noNumber = Out == 0 && Instance.c_str() != 0 && Instance != "0";
    Bool outOfRange = errno == ERANGE && (Out == LONG_MIN || Out == LONG_MAX);

    return noNumber == false && outOfRange == false;
}

Bool ToUInt64(const String& Instance, Int32 Base, UInt64& Out)
{
    errno = 0;
    Out = strtoul(Instance.c_str(), 0, Base);

    Bool noNumber = Out == 0 && Instance.c_str() != 0 && Instance != "0";
    Bool outOfRange = errno == ERANGE && Out == ULONG_MAX;
    
    return noNumber == false && outOfRange == false;
}

Bool ToFloat64(const String& Instance, Float64& Out)
{
    Out = strtod(Instance.c_str(), 0);
    return Out > Math::Float64::EPSILION &&
           !(errno == ERANGE && (
           Math::Float64::FAbs(Out + HUGE_VAL) < Math::Float64::EPSILION ||
           Math::Float64::FAbs(Out - HUGE_VAL) < Math::Float64::EPSILION));
}

Int32 Format(RF_Type::UInt8* Buffer, RF_Type::Size BufferSize, const String& Format, va_list arg)
{
    return vsnprintf(reinterpret_cast<char*>(Buffer), BufferSize, Format.c_str(), arg);
}

const UInt8* Find(const RF_Type::UInt8* Buffer, RF_Type::Size BufferSize, 
    const RF_Type::UInt8* LookingFor, RF_Type::Size LookingForSize)
{
    const UInt8* result = reinterpret_cast<const UInt8*>(strstr(reinterpret_cast<const char*>(Buffer), reinterpret_cast<const char*>(LookingFor)));
    if ((Buffer + BufferSize - result) < LookingForSize)
        result = 0;
    return result;
}

void RF_SysStr::Dispatch()
{
    SetLocale = ::SetLocale;
    GetLocale = ::GetLocale;
    ToUpper = ::ToUpper;
    ToLower = ::ToLower;
    CStringSizeOf = ::StrSize;
    Length = ::Length;
    ToInt64 = ::ToInt64;
    ToUInt64 = ::ToUInt64;
    ToFloat64 = ::ToFloat64;
    Format = ::Format;
    Find = ::Find;
}