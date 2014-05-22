#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/Math/Math.hpp"
#include <string.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;

using RadonFramework::Core::Types::String;

String::String()
:m_DataManagment(Common::DataManagment::Copy)
,m_Length(0)
{
    switch(m_DataManagment)
    {
        case DataManagment::Copy:
            m_FixBuffer[0] = 0;
            break;
        default:
            m_DynBuffer.m_Buffer = 0;
            m_DynBuffer.m_Size = 0;
    }
}

String::String(const String& Copy)
:m_DataManagment(Common::DataManagment::Copy)
,m_Length(Copy.m_Length)
{
    if (m_Length > 0)
    {
        if (m_Length >= BUFFER_SIZE)
        {
            m_DataManagment = DataManagment::AllocateAndCopy;
            m_DynBuffer.m_Buffer = new char[Copy.m_DynBuffer.m_Size + 1];
            m_DynBuffer.m_Size = Copy.m_DynBuffer.m_Size + 1;
            RFMEM::Copy(static_cast<void*>(m_DynBuffer.Raw()), static_cast<const void*>(Copy.m_DynBuffer.Raw()), m_DynBuffer.m_Size);
        }
        else
        {
            RFMEM::Copy(static_cast<void*>(m_FixBuffer.Raw()), static_cast<const void*>(Copy.m_FixBuffer.Raw()), BUFFER_SIZE);
        }
    }
}

String::String(const char* cString, const RFTYPE::Size cStringSize,
    DataManagment::Type Ownership)
:m_DataManagment(Ownership)
{
    if (cString != 0)
    {
        m_Length = static_cast<UInt32>(strlen(cString));

        if (cStringSize > 0)
        {
            switch (m_DataManagment)
            {
            case Common::DataManagment::Copy:
                if (cStringSize < BUFFER_SIZE)
                {
                    RFMEM::Copy(static_cast<void*>(m_FixBuffer.Raw()),
                                static_cast<const void*>(cString), cStringSize);
                }
                else
                {
                    m_DataManagment = DataManagment::AllocateAndCopy;
                    m_DynBuffer.m_Buffer = new char[cStringSize];
                    m_DynBuffer.m_Size = cStringSize;
                    RFMEM::Copy(m_DynBuffer.m_Buffer, cString, m_DynBuffer.m_Size);
                }
                break;
            case Common::DataManagment::UnmanagedInstance:
            case Common::DataManagment::TransfereOwnership:
                m_DynBuffer.m_Buffer = (char*)cString;
                m_DynBuffer.m_Size = cStringSize;
                break;
            }
        }
    }
    else
    {
        m_Length = 0;
        m_FixBuffer[0] = 0;
        m_DataManagment = DataManagment::Copy;
    }
}

String::String(const RFTYPE::Size StringSize)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=StringSize-1;
    if (StringSize <= BUFFER_SIZE)
    {
        RFMEM::Set(static_cast<void*>(m_FixBuffer.Raw()), ' ', m_Length);
        m_FixBuffer[m_Length] = 0;
    }
    else
    {
        m_DataManagment = DataManagment::AllocateAndCopy;
        m_DynBuffer.m_Buffer = new char[m_Length];
        m_DynBuffer.m_Size = m_Length;
        RFMEM::Set(static_cast<void*>(m_DynBuffer.Raw()), ' ', m_Length);
        m_DynBuffer[m_Length] = 0;
    }
}

String::String(const char Letter)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length = 1;
    m_FixBuffer[0] = Letter;
    m_FixBuffer[1] = 0;
}

String::~String()
{
    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
    {
        delete[] m_DynBuffer.m_Buffer;
        m_DynBuffer.m_Size = 0;
    }
}

String String::UnsafeStringCreation(const char* CString)
{
    String result;
    RFTYPE::Size size = 0;
    for (;CString != 0; ++CString, ++size){}
    result = String(CString, size);
    return result;
}

void* String::operator new(size_t bytes)
{
    return RFMEM::Allocate(bytes);
}

void* String::operator new(size_t bytes, void* buffer)
{
    UInt8* p = static_cast<UInt8*>(buffer);
    p += bytes;
    return static_cast<void*>(p);
}

RFTYPE::UInt32 String::Length()const
{
    return m_Length;
}


RFTYPE::Int32 String::Contains(const String &Str)const
{
    if (m_Length < Str.m_Length)
        return -1;

    return IndexOf(Str, 0, m_Length);
}


RFTYPE::Bool String::EndsWith(const String& Value)const
{
    //this test is faster as in the method with char*
    if (Value.m_Length > m_Length)
        return false;

    const char* buffer = GetBuffer();
    Int32 j = m_Length - 1;
    for (UInt32 i = m_Length - 1; i >= 0; --i)
    {
        if(buffer[i] == Value[j])
            --j;
        else
            return false;

        if(j == -1)
            return true;
    }
    return false;
}

RFTYPE::Int32 String::IndexOf(const String& Value)const
{
    if (m_Length<Value.m_Length)
        return -1;

    return IndexOf(Value, 0, m_Length);
}

RFTYPE::Int32 String::IndexOf(const String& Value,
                      const RFTYPE::UInt32 StartAtIndex)const
{
    if (m_Length-StartAtIndex<Value.m_Length)
        return -1;

    return IndexOf(Value, StartAtIndex, m_Length - StartAtIndex);
}

RFTYPE::Int32 String::IndexOf(const RFTYPE::String& Value,
    const RFTYPE::UInt32 StartAtIndex, const RFTYPE::UInt32 Count)const
{
    if (Count < Value.m_Length)
        return -1;

    if (m_Length == 0)
        return -1;

    Int32 j=0;
    for (UInt32 i=StartAtIndex;i<StartAtIndex+Count;++i)
    {
        const char* buffer = GetBuffer();

        if(buffer[i]==Value[j])
            ++j;
        else
            j=0;

        if (j==static_cast<Int32>(m_Length))
            return i-(j-1);
    }
    return -1;
}

RFTYPE::String String::Insert(const RFTYPE::UInt32 AtIndex,
    const RFTYPE::String& Value)
{
    RFTYPE::Size byteSize = m_Length+Value.m_Length;
    String str(byteSize);

    char* buffer = GetBuffer();

    if (AtIndex>0)
        RFMEM::Copy(buffer, c_str(), AtIndex);

    RFMEM::Copy(buffer + AtIndex, Value.c_str(), Value.m_Length);
    if (m_Length > 0)
        RFMEM::Copy(buffer + AtIndex+Value.m_Length, c_str() + AtIndex, m_Length - AtIndex);
    return str;
}

RFTYPE::Int32 String::LastIndexOf(const String& Value)const
{
    if (m_Length<Value.m_Length)
        return -1;

    return LastIndexOf(Value, 0, m_Length);
}

RFTYPE::Int32 String::LastIndexOf(const RFTYPE::String& Value,
    const RFTYPE::UInt32 StartAtIndex)const
{
    if (m_Length-StartAtIndex<Value.m_Length)
        return -1;

    return LastIndexOf(Value, StartAtIndex, m_Length - StartAtIndex);
}

RFTYPE::Int32 String::LastIndexOf(const RFTYPE::String& Value,
    const RFTYPE::UInt32 StartAtIndex, const RFTYPE::UInt32 Count)const
{
    if (Count<Value.m_Length)
        return -1;

    if (m_Length==0)
        return -1;

    const char* buffer = GetBuffer();

    const char* value = GetBuffer();

    const char* v = value;
    const char *p = buffer + (StartAtIndex + Count - m_Length + 1);
    const char *searchp = p;
    const char *vend=value + m_Length;
    const char *pend=buffer + StartAtIndex - 1;

    for(;p!=pend;--p,searchp=p)
    {
        while(v!=vend && *searchp==*v)//compare func
        {
            ++searchp;
            ++v;
        }

        if (v==vend)//finished search
            return static_cast<Int32>(MemoryRange(p-buffer));
        else
            v=value;//reset v for next search
    }
    return -1;
}

String String::PadLeft(const RFTYPE::UInt32 TotalWidth,
                       const RFTYPE::Char PaddingChar)const
{
    if (TotalWidth<m_Length)
        return *this;

    RFTYPE::Size byteSize = TotalWidth;
    String str(byteSize);
    UInt32 offset = TotalWidth - m_Length;
    const char* buffer = GetBuffer();

    char* strBuffer = str.GetBuffer();

    if (PaddingChar!=' ' && offset>0)
        RFMEM::Set(strBuffer, PaddingChar, offset);

    RFMEM::Copy(strBuffer + offset, buffer, m_Length);
    return str;
}

String String::PadRight(const RFTYPE::UInt32 TotalWidth,
                        const RFTYPE::Char PaddingChar)const
{
    if (TotalWidth<m_Length)
        return *this;
    
    RFTYPE::Size byteSize = TotalWidth;
    String str(byteSize);
    UInt32 offset = TotalWidth - m_Length;
    const char* buffer = GetBuffer();

    char* strBuffer = str.GetBuffer();

    if (PaddingChar!=' ' && offset>0)
        RFMEM::Set(strBuffer + m_Length, PaddingChar, offset);
    RFMEM::Copy(strBuffer, buffer, m_Length);
    return str;
}

String String::Remove(const RFTYPE::UInt32 StartAtIndex)const
{
    if (StartAtIndex==0)
        return String();
    
    const char* buffer = GetBuffer();


    String str(buffer + StartAtIndex, m_Length - StartAtIndex);
    return str;
}

String String::Remove(const RFTYPE::UInt32 StartAtIndex,
                      const RFTYPE::UInt32 Count)const
{
    if (StartAtIndex==0)
        return String();

    if (StartAtIndex > m_Length || Count == 0)
        return *this;

    if (m_Length - StartAtIndex < Count)
        return Remove(StartAtIndex);

    const char* buffer = GetBuffer();

    UInt32 sc = StartAtIndex + Count;
    RFTYPE::Size byteSize = m_Length - Count;
    String str(byteSize);
    char* dstBuffer = str.GetBuffer();

    RFMEM::Copy(dstBuffer, buffer, StartAtIndex);
    RFMEM::Copy(dstBuffer + StartAtIndex,buffer + sc,m_Length-sc);
    return str;
}

String String::Replace(const RFTYPE::Char OldChar,
                       const RFTYPE::Char NewChar)const
{
    String str(*this);
    char* p = str.GetBuffer();

    for (UInt32 i = 0; i < m_Length; ++i)
        if (p[i] == OldChar)
            p[i] = NewChar;
    return str;
}

String String::Replace(const String& OldValue, const String& NewValue)const
{
    if(OldValue.m_Length==0 || OldValue==NewValue || OldValue.m_Length>m_Length)
        return *this;

    String str(*this);
    Int32 ind=0;
    Int32 diff=OldValue.m_Length-NewValue.m_Length;

    while((ind=str.IndexOf(OldValue))>-1)
    {
        if (OldValue.m_Length==NewValue.m_Length)
        {
            RFMEM::Copy(str.GetBuffer() + ind, NewValue.GetBuffer(), NewValue.m_Length);
        }
        else
        {
            RadonFramework::Memory::AutoPointerArray<char> p(new char[str.m_Length-diff+1],str.m_Length-diff+1);
            p.Get()[str.m_Length-diff]=0;

            if (ind!=0)
            {
                RFMEM::Copy(p.Get(),str.GetBuffer(),ind);
            }
            RFMEM::Copy(p.Get()+ind,NewValue.GetBuffer(),NewValue.m_Length);
            if (ind+OldValue.m_Length!=str.m_Length)
            {
                RFMEM::Copy(p.Get()+ind+NewValue.m_Length,str.GetBuffer()+(ind+OldValue.m_Length),str.m_Length-ind-OldValue.m_Length);
            }
            str = String(p.Get(), p.Size());
        }
    }
    return str;
}


AutoPointerArray<String> String::Split(const String &Delimiters)const
{
    AutoPointerArray<String> list;
    UInt32 lasthit=0;
    const Char* p = GetBuffer();
    UInt32 hits=1;
    for (UInt32 i=0;i<m_Length-1;i++)
    {
        for (UInt32 j=0;j<Delimiters.m_Length;j++)
        {
            if (p[i]==Delimiters[j])
            {
                ++hits;
                break;
            }
        }
    }

    list=AutoPointerArray<String>(new String[hits],hits);
    hits=0;
    for (UInt32 i=0;i<m_Length;i++)
    {
        for (UInt32 j=0;j<Delimiters.m_Length;j++)
        {
            if (p[i]==Delimiters[j])
            {
                String& str=list[hits];
                RFTYPE::Size bytes=i-lasthit;
                str = String(bytes);
                RFMEM::Copy(str.GetBuffer(), p + lasthit, i - lasthit);
                lasthit=i+1;
                ++hits;
                break;
            }
        }
    }

    if (lasthit<m_Length)
    {
        String& str=list[hits];
        RFTYPE::Size bytes = m_Length - lasthit;
        str = String(bytes);
        RFMEM::Copy(str.GetBuffer(), p + lasthit, m_Length - lasthit + 1);//copy the 0 termination too
    }
    return list;
}

RFTYPE::Bool String::StartsWith(const String& AString)const
{
    if (AString.m_Length>m_Length || AString.m_Length==0)
        return false;
    return RFMEM::Compare(GetBuffer(), AString.GetBuffer(), AString.m_Length) == 0 ? true : false;
}


String String::SubString(const RFTYPE::UInt32 StartIndex,
                        const RFTYPE::UInt32 Count)const
{
    if (StartIndex+Count>m_Length || Count==0)
        return String();
    String str(GetBuffer() + StartIndex, Count);
    return str;
}


String String::Trim(const String& TrimChars)const
{
    return TrimStart(TrimChars).TrimEnd(TrimChars);
}


String String::TrimStart(const String& TrimChars)const
{
    Bool foundone;
    UInt32 i=0;
    for (;i<m_Length;++i)
    {
        foundone=false;
        for (UInt32 j=0;j<TrimChars.m_Length;++j)
        {
            if (GetBuffer()[i]==TrimChars[j])
            {
                foundone=true;
            }
        }

        if (!foundone)
            break;
    }
    String str(GetBuffer() + i, m_Length - i);
    return str;
}


String String::TrimEnd(const String& TrimChars)const
{
    Bool foundone;
    UInt32 i=m_Length-1;
    for (;i>=0;--i)
    {
        foundone=false;
        for (UInt32 j=0;j<TrimChars.m_Length;++j)
        {
            if (GetBuffer()[i]==TrimChars[j])
            {
                foundone=true;
            }
        }

        if (!foundone)
            break;
    }
    String str(GetBuffer(),i+1);
    return str;
}


RFTYPE::Int32 String::Compare(const String& With)const
{
    if (m_Length==With.m_Length)
    {
        for (UInt32 i=0;i<m_Length;++i)
        {
            if ((*this)[i]==With[i])
            {
            }
            else
            {
                return i+1;
            }
        }
    }
    else
        return -1;
    return 0;
}

char String::operator[](const RFTYPE::Size Index)const
{
    Assert(static_cast<UInt32>(Index)<m_Length+1&&Index>=0, "Out of bound.");
    return *(GetBuffer() + Index);
}

char& String::operator[](const RFTYPE::Size Index)
{
    Assert(static_cast<UInt32>(Index)<m_Length+1&&Index>=0, "Out of bound");
    return *(GetBuffer()+Index);
}

bool String::operator==(const String& Other)const
{
    if (m_Length!=Other.m_Length)
    {
        return false;
    }

    for (UInt32 i=0;i<m_Length;i++)
    {
        if (GetBuffer()[i] != Other.GetBuffer()[i])
        {
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String& Other)const
{
    if (Other.m_Length!=m_Length)
    {
        return true;
    }

    for (UInt32 i=0;i<m_Length;++i)
    {
        if (GetBuffer()[i] != Other.GetBuffer()[i])
        {
            return true;
        }
    }
    return false;
}

String String::operator+(const String &Str)const
{
    if (m_Length + Str.m_Length)
    {
        RFTYPE::Size bytes = m_Length + Str.m_Length + 1;
        String str(bytes);

        if (m_Length>0)
            RFMEM::Copy(str.GetBuffer(), GetBuffer(), m_Length);

        if (Str.m_Length>0)
            RFMEM::Copy(str.GetBuffer() + m_Length, Str.GetBuffer(), Str.m_Length);

        str[str.m_Length]='\0';

        return str;
    }
    return String();
}

String String::operator+(const RFTYPE::Char Character)const
{
    RFTYPE::Size bytes = m_Length + 2;
    String str(bytes);
    if (m_Length>0)
        RFMEM::Copy(str.GetBuffer(), GetBuffer(), m_Length);

    str[str.m_Length-1]=Character;
    str[str.m_Length]='\0';
    return str;
}

String String::operator+(const RFTYPE::Bool& Value)const
{
    String res(*this);
    res+=(Value==true?"true":"false");
    return res;
}

String String::operator+(const RFTYPE::Int8 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::Int16 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::Int32 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::Int64 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::UInt8 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::UInt16 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::UInt32 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String String::operator+(const RFTYPE::UInt64 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}

String& String::operator+=(const RFTYPE::Char Character)
{
    RFTYPE::Size bytes = m_Length + 2;
    String newStr(bytes);
    if (m_Length>0)
        RFMEM::Copy(newStr.GetBuffer(), GetBuffer(), m_Length);

    newStr[m_Length]=Character;
    newStr[m_Length+1]='\0';

    Swap(newStr);
    return *this;
}

String& String::operator+=(const String& Str)
{
    if (Str.m_Length > 0)
    {
        RFTYPE::Size bytes = m_Length + Str.m_Length + 1;
        String newStr(bytes);

        if (m_Length>0)
            RFMEM::Copy(newStr.GetBuffer(), GetBuffer(), m_Length);
        RFMEM::Copy(newStr.GetBuffer() + m_Length, Str.GetBuffer(), Str.m_Length + 1);
        Swap(newStr);
    }
    return *this;
}

String& String::operator+=(const RFTYPE::Bool& Value)
{
    *this+=Convert::ToString(Value);
    return *this;
}

String& String::operator+=(const RFTYPE::Int8 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::Int16 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::Int32 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::Int64 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::UInt8 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::UInt16 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::UInt32 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator+=(const RFTYPE::UInt64 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::Char Character)
{
    m_Length=1;

    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
        m_DynBuffer.Free();

    m_DataManagment = DataManagment::Copy;
    m_FixBuffer[m_Length-1]=Character;
    m_FixBuffer[m_Length]='\0';
    return *this;
}

String& String::operator=(const String &Other)
{
    String newStr(Other);
    Swap(newStr);
    return *this;
}

String& String::operator=(const RFTYPE::Bool& Value)
{
    *this=Convert::ToString(Value);
    return *this;
}

String& String::operator=(const RFTYPE::Int8 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::Int16 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::Int32 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::Int64 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::UInt8 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::UInt16 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::UInt32 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

String& String::operator=(const RFTYPE::UInt64 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}

char const* String::c_str()const
{
    return GetBuffer();
}

RFTYPE::Int32 String::HexToDec()const
{
    Int64 val;
    RFSTR::ToInt64(*this, 16, val);
    return val;
}

String String::Format(const String& Str,...)
{
    va_list argp;
    va_start(argp, Str);

    RadonFramework::Memory::AutoPointerArray<char> out;
    RadonFramework::Memory::AutoPointerArray<char> dynBuf;
    Int32 len=0;
    Int32 buflen=0;
    while(len==buflen || len==-1)
    {
        buflen+=256;
        dynBuf=RadonFramework::Memory::AutoPointerArray<char>(new char[buflen],buflen);
        len = RFSTR::Format(reinterpret_cast<UInt8*>(dynBuf.Get()), buflen-1, String(Str.GetBuffer(), Str.Size(), RadonFramework::Core::Common::DataManagment::UnmanagedInstance), argp);
    }
    out=RadonFramework::Memory::AutoPointerArray<char>(new char[len+1],len+1);
    RFMEM::Copy(out.Get(),dynBuf.Get(),len);
    out.Get()[len]=0;

    va_end(argp);
    return String(out.Release().Ptr, DataManagment::TransfereOwnership);
}

void String::ToUpper()
{
    *this = RFSTR::ToUpper(*this);
}

void String::ToLower()
{
    *this = RFSTR::ToLower(*this);
}

RFTYPE::Bool String::IsNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if (GetBuffer()[i]>=48 && GetBuffer()[i]<=57)
        {
        }
        else
            return false;
    return true;
}

RFTYPE::Bool String::IsFloatingpointNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if ((GetBuffer()[i]>=48 && GetBuffer()[i]<=57) || GetBuffer()[i]=='.')
        {
        }
        else
            return false;
    return true;
}

RFTYPE::Bool String::IsBoolean()const 
{    
    static const String TRUE("true", sizeof("true"));
    static const String FALSE("false", sizeof("false"));
    String lowerCase=*this;
    lowerCase.ToLower();
    return lowerCase == TRUE || lowerCase == FALSE;
}

void String::Swap(String& Other)
{
    String tmp(Other);
    Other = *this;
    *this = tmp;
}

String& operator<<(String &Str, const RFTYPE::Int8 &Self)
{
    return Str += RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Int16 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Int32 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Int64 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::UInt8 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::UInt16 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::UInt32 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::UInt64 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Float32 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Float64 &Self)
{
    return Str+=RFTYPE::Convert::ToString(Self);
}

String& operator<<(String &Str, const RFTYPE::Char &Self)
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

RFTYPE::Int8& operator<<(RFTYPE::Int8 &Self, const String &Str)
{
    RFTYPE::Convert::ToInt8(Str,Self);
    return Self;
}

RFTYPE::Int16& operator<<(RFTYPE::Int16 &Self, const String &Str)
{
    RFTYPE::Convert::ToInt16(Str,Self);
    return Self;
}

RFTYPE::Int32& operator<<(RFTYPE::Int32 &Self, const String &Str)
{
    RFTYPE::Convert::ToInt32(Str,Self);
    return Self;
}

RFTYPE::Int64& operator<<(RFTYPE::Int64 &Self, const String &Str)
{
    RFTYPE::Convert::ToInt64(Str,Self);
    return Self;
}

RFTYPE::UInt8& operator<<(RFTYPE::UInt8 &Self, const String &Str)
{
    RFTYPE::Convert::ToUInt8(Str,Self);
    return Self;
}

RFTYPE::UInt16& operator<<(RFTYPE::UInt16 &Self, const String &Str)
{
    RFTYPE::Convert::ToUInt16(Str,Self);
    return Self;
}

RFTYPE::UInt32& operator<<(RFTYPE::UInt32 &Self, const String &Str)
{
    RFTYPE::Convert::ToUInt32(Str,Self);
    return Self;
}

RFTYPE::UInt64& operator<<(RFTYPE::UInt64 &Self, const String &Str)
{
    RFTYPE::Convert::ToUInt64(Str,Self);
    return Self;
}

RFTYPE::Float32& operator<<(RFTYPE::Float32 &Self, const String &Str)
{
    RFTYPE::Convert::ToFloat32(Str,Self);
    return Self;
}

RFTYPE::Float64& operator<<(RFTYPE::Float64 &Self, const String &Str)
{
    RFTYPE::Convert::ToFloat64(Str,Self);
    return Self;
}

inline char* String::GetBuffer()
{
    if (m_DataManagment == DataManagment::Copy)
        return m_FixBuffer.Raw();
    else
        return m_DynBuffer.Raw();
}

inline const char* String::GetBuffer()const
{
    if (m_DataManagment == DataManagment::Copy)
        return m_FixBuffer.Raw();
    else
        return m_DynBuffer.Raw();
}

RFTYPE::Bool String::IsEmpty() const
{
    return m_Length == 0;
}

RFTYPE::Size String::Size()const
{
    if (m_DataManagment == DataManagment::Copy)
        return m_Length;
    else
        return m_DynBuffer.m_Size;
}
