#ifndef RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#define RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Char &RH);
/// Append "true" or "false" on the string.
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Bool &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Int8 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Int16 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Int32 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::Int64 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::UInt8 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::UInt16 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::UInt32 &RH);
RF_Type::String operator+(const RF_Type::String &LH, const RF_Type::UInt64 &RH);

RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Char& Character);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Bool& Value);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Int8& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Int16& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Int32& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::Int64& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::UInt8& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::UInt16& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::UInt32& Number);
RF_Type::String& operator+=(RF_Type::String &LH, const RF_Type::UInt64& Number);

//OtherType to String
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Int8 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Int16 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Int32 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Int64 &Self);

RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::UInt8 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::UInt16 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::UInt32 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::UInt64 &Self);

RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Float32 &Self);
RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Float64 &Self);

RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::Char &Self);

template<int N>
RF_Type::String& operator<<(RF_Type::String &Str, char const (&Other)[N])
{
    Str += String(Other, N);
    return Str;
}

RF_Type::String& operator<<(RF_Type::String &Str, const RF_Type::String &Self);

//String to OtherType
RF_Type::Int8& operator<<(RF_Type::Int8 &Self, const RF_Type::String &Str);
RF_Type::Int16& operator<<(RF_Type::Int16 &Self, const RF_Type::String &Str);
RF_Type::Int32& operator<<(RF_Type::Int32 &Self, const RF_Type::String &Str);
RF_Type::Int64& operator<<(RF_Type::Int64 &Self, const RF_Type::String &Str);

RF_Type::UInt8& operator<<(RF_Type::UInt8 &Self, const RF_Type::String &Str);
RF_Type::UInt16& operator<<(RF_Type::UInt16 &Self, const RF_Type::String &Str);
RF_Type::UInt32& operator<<(RF_Type::UInt32 &Self, const RF_Type::String &Str);
RF_Type::UInt64& operator<<(RF_Type::UInt64 &Self, const RF_Type::String &Str);

RF_Type::Float32& operator<<(RF_Type::Float32 &Self, const RF_Type::String &Str);
RF_Type::Float64& operator<<(RF_Type::Float64 &Self, const RF_Type::String &Str);

#endif // RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP