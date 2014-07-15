#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/Utils/StringOperators.hpp"
#include "RadonFramework/Core/Types/Convert.hpp"

using namespace RadonFramework::Core::Types;

String operator+(const String& LH, const String &RH)
{
    if (LH.Length() + RH.Length())
    {
        Size bytes = LH.Size() + RH.Size() - 1;
        String str(bytes);

        if (LH.Length() > 0)
            RF_SysMem::Copy(const_cast<char*>(str.c_str()), LH.c_str(), LH.Size());

        if (RH.Length() > 0)
            RF_SysMem::Copy(const_cast<char*>(str.c_str() + LH.Size() - 1), RH.c_str(), RH.Size());

        return str;
    }
    return String();
}

String operator+(const String& LH, const Char &RH)
{
    Size bytes = LH.Size() + 1;
    String str(bytes);
    if (LH.Length() > 0)
        RF_SysMem::Copy(const_cast<char*>(str.c_str()), LH.c_str(), bytes - 2);

    str[str.Length()-1] = RH;
    str[str.Length()]='\0';
    return str;
}

String operator+(const String& LH, const Bool& RH)
{
    String res(LH);
    res += (RH == true ? "true" : "false");
    return res;
}

String operator+(const String& LH, const Int8 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const Int16 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const Int32 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const Int64 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const UInt8 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const UInt16 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const UInt32 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}

String operator+(const String& LH, const UInt64 &RH)
{
    String res(LH);
    res+=Convert::ToString(RH);
    return res;
}


String& operator+=(String &LH, const Bool& Value)
{
    LH += Convert::ToString(Value);
    return LH;
}

String& operator+=(String &LH, const Int8& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const Int16& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const Int32& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const Int64& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const Char& Character)
{
    const int TERMINATION = 1;
    Size bytes = LH.Size();
    if (bytes == 0)
        bytes = 2;
    else
        bytes += TERMINATION;

    String newStr(bytes);
    if (LH.Length() > 0)
        RF_SysMem::Copy(const_cast<char*>(newStr.c_str()), LH.c_str(), bytes);

    newStr[bytes-2] = Character;
    newStr[bytes-1] = '\0';

    LH.Swap(newStr);
    return LH;
}

String& operator+=(String &LH, const UInt8& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const UInt16& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const UInt32& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator+=(String &LH, const UInt64& Number)
{
    LH += Convert::ToString(Number);
    return LH;
}

String& operator<<(String &Str, const Int8 &Self)
{
    return Str += Convert::ToString(Self);
}

String& operator<<(String &Str, const Int16 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const Int32 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const Int64 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const UInt8 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const UInt16 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const UInt32 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const UInt64 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const Float32 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const Float64 &Self)
{
    return Str+=Convert::ToString(Self);
}

String& operator<<(String &Str, const Char &Self)
{
    char str[2]={};
    str[0]=Self;
    Str+=str;
    return Str;
}

String& operator<<(String &Str, const String &Self)
{
    Str+=Self;
    return Str;
}

Int8& operator<<(Int8 &Self, const String &Str)
{
    Convert::ToInt8(Str,Self);
    return Self;
}

Int16& operator<<(Int16 &Self, const String &Str)
{
    Convert::ToInt16(Str,Self);
    return Self;
}

Int32& operator<<(Int32 &Self, const String &Str)
{
    Convert::ToInt32(Str,Self);
    return Self;
}

Int64& operator<<(Int64 &Self, const String &Str)
{
    Convert::ToInt64(Str,Self);
    return Self;
}

UInt8& operator<<(UInt8 &Self, const String &Str)
{
    Convert::ToUInt8(Str,Self);
    return Self;
}

UInt16& operator<<(UInt16 &Self, const String &Str)
{
    Convert::ToUInt16(Str,Self);
    return Self;
}

UInt32& operator<<(UInt32 &Self, const String &Str)
{
    Convert::ToUInt32(Str,Self);
    return Self;
}

UInt64& operator<<(UInt64 &Self, const String &Str)
{
    Convert::ToUInt64(Str,Self);
    return Self;
}

Float32& operator<<(Float32 &Self, const String &Str)
{
    Convert::ToFloat32(Str,Self);
    return Self;
}

Float64& operator<<(Float64 &Self, const String &Str)
{
    Convert::ToFloat64(Str,Self);
    return Self;
}