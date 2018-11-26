#ifndef RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#define RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>

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
    Str += RF_Type::String(Other, N);
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

struct Murmur
{
    static const RF_Type::UInt64 m = 0xc6a4a7935bd1e995;
    static const int r = 47;

    template<RF_Type::Size N>
    RF_FORCE_INLINE Murmur(const char(&Str)[N])
    {
        const RF_Type::Size LEN = N - 1;
        const RF_Type::Size FIRSTNONLOOPINDEX = (LEN / 8) * 8;
        RF_Type::UInt64 h = 0 ^ (LEN * m);
        typedef const char(&truncated_str)[LEN];
        h = Loop((truncated_str)Str, h);

        switch(LEN & 7)
        {
        case 7: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 6]) << 48;
        case 6: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 5]) << 40;
        case 5: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 4]) << 32;
        case 4: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 3]) << 24;
        case 3: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 2]) << 16;
        case 2: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX + 1]) << 8;
        case 1: h ^= static_cast<RF_Type::UInt64>(Str[FIRSTNONLOOPINDEX]);
                h *= m;
        };
                
        h ^= h >> r;
        h *= m;
        h ^= h >> r;
        m_Result = h;
    }

    operator RF_Type::UInt64()
    {
        return m_Result;
    }
private:
    RF_Type::UInt64 m_Result;

    template<RF_Type::Size N>
    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[N], const RF_Type::UInt64 h)
    {
        static const RF_Type::Size NEXT8BYTEINDEX = N & ~7;
        typedef const char(&truncated_str)[N - 8];
        RF_Type::UInt64 result = Loop((truncated_str)Str, h);
        RF_Type::UInt64 k = *reinterpret_cast<const RF_Type::UInt64*>(&Str[NEXT8BYTEINDEX-8]);
        k *= m;
        k ^= k >> r;
        k *= m;
        result ^= k;
        result *= m;
        return result;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[8], const RF_Type::UInt64 h)
    {
        RF_Type::UInt64 result = h;
        RF_Type::UInt64 k = *reinterpret_cast<const RF_Type::UInt64*>(Str);
        k *= m;
        k ^= k >> r;
        k *= m;
        result ^= k;
        result *= m;
        return result;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[7], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[6], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[5], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[4], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[3], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[2], const RF_Type::UInt64 h)
    {
        return h;
    }

    RF_FORCE_INLINE RF_Type::UInt64 Loop(const char(&Str)[1], const RF_Type::UInt64 h)
    {
        return h;
    }
};

#define RF_HASH(str) Murmur(str)

#endif // RF_CORE_TYPES_UTILS_STRINGOPERATORS_HPP