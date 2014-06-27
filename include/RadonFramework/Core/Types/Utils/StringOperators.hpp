#ifndef RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#define RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Char &RH);
/// Append "true" or "false" on the string.
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Bool &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Int8 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Int16 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Int32 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::Int64 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::UInt8 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::UInt16 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::UInt32 &RH);
RFTYPE::String operator+(const RFTYPE::String &LH, const RFTYPE::UInt64 &RH);

RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Char& Character);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Bool& Value);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Int8& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Int16& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Int32& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::Int64& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::UInt8& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::UInt16& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::UInt32& Number);
RFTYPE::String& operator+=(RFTYPE::String &LH, const RFTYPE::UInt64& Number);

//OtherType to String
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int8 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int16 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt8 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt16 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Float32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Float64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Char &Self);

template<int N>
RFTYPE::String& operator<<(RFTYPE::String &Str, char const (&Other)[N])
{
    Str += String(Other, N);
    return Str;
}

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::String &Self);

//String to OtherType
RFTYPE::Int8& operator<<(RFTYPE::Int8 &Self, const RFTYPE::String &Str);
RFTYPE::Int16& operator<<(RFTYPE::Int16 &Self, const RFTYPE::String &Str);
RFTYPE::Int32& operator<<(RFTYPE::Int32 &Self, const RFTYPE::String &Str);
RFTYPE::Int64& operator<<(RFTYPE::Int64 &Self, const RFTYPE::String &Str);

RFTYPE::UInt8& operator<<(RFTYPE::UInt8 &Self, const RFTYPE::String &Str);
RFTYPE::UInt16& operator<<(RFTYPE::UInt16 &Self, const RFTYPE::String &Str);
RFTYPE::UInt32& operator<<(RFTYPE::UInt32 &Self, const RFTYPE::String &Str);
RFTYPE::UInt64& operator<<(RFTYPE::UInt64 &Self, const RFTYPE::String &Str);

RFTYPE::Float32& operator<<(RFTYPE::Float32 &Self, const RFTYPE::String &Str);
RFTYPE::Float64& operator<<(RFTYPE::Float64 &Self, const RFTYPE::String &Str);

#endif // RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP