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
    m_FixBuffer[0] = 0;
    m_FixBuffer.SetSize(0);
}

String::String(const String& Copy)
:m_DataManagment(Common::DataManagment::Copy)
,m_Length(0)
{
    m_FixBuffer.SetSize(0);
    // if the length of Copy is 0 we don't have to do anything
    if (Copy.m_Length > 0)
    {
        // take the calculated length from Copy
        m_Length = Copy.m_Length;

        if (Copy.m_DataManagment != Common::DataManagment::Copy)
        {
            m_DataManagment = Copy.m_DataManagment;
            if (Copy.m_DataManagment == Common::DataManagment::UnmanagedInstance)
            {// clone it
                m_DynBuffer = Copy.m_DynBuffer;
            }
            else
            {// create a copy
                m_DynBuffer.m_Buffer = new char[Copy.m_DynBuffer.m_Size];
                m_DynBuffer.m_Size = Copy.m_DynBuffer.m_Size;
                RF_SysMem::Copy(static_cast<void*>(m_DynBuffer.Raw()), static_cast<const void*>(Copy.m_DynBuffer.Raw()), m_DynBuffer.m_Size);
            }
        }
        else
        {// locale copy
            RF_SysMem::Copy(static_cast<void*>(m_FixBuffer.Raw()), static_cast<const void*>(Copy.m_FixBuffer.Raw()), BUFFER_SIZE);
            m_FixBuffer.SetSize(Copy.m_FixBuffer.GetSize());
        }
    }
}

String::String(const char* cString, const RF_Type::Size cStringSize,
    DataManagment::Type Ownership)
:m_DataManagment(Ownership)
{
    if (cString != 0 && cStringSize > 0)
    {
        m_Length = RF_SysStr::Length(reinterpret_cast<const UInt8*>(cString), cStringSize);
        RF_Type::Size bytesInUse = RF_SysStr::CStringSizeOf(reinterpret_cast<const UInt8*>(cString), cStringSize);
        switch (m_DataManagment)
        {
        case Common::DataManagment::Copy:
            if(bytesInUse <= BUFFER_SIZE)
            {
                const RF_Type::Size TERMINATION = 1;
                RF_SysMem::Copy(static_cast<void*>(m_FixBuffer.Raw()),
                    static_cast<const void*>(cString), bytesInUse - TERMINATION);
                
                m_FixBuffer[bytesInUse - TERMINATION] = '\0';
                m_FixBuffer.SetSize(bytesInUse);
            }
            else
            {
                m_DataManagment = DataManagment::AllocateAndCopy;
                m_DynBuffer.m_Buffer = new char[bytesInUse];
                m_DynBuffer.m_Size = bytesInUse;
                RF_SysMem::Copy(m_DynBuffer.Raw(), cString, m_DynBuffer.m_Size);
            }
            break;
        case Common::DataManagment::TransfereOwnership:
            m_DataManagment = Common::DataManagment::AllocateAndCopy;
        case Common::DataManagment::UnmanagedInstance:
            m_DynBuffer.m_Buffer = (char*)cString;
            m_DynBuffer.m_Size = bytesInUse;
            break;
        }
    }
    else
    {
        m_Length = 0;
        m_FixBuffer[0] = '\0';
        m_FixBuffer.SetSize(0);
        m_DataManagment = DataManagment::Copy;
    }
}

String::String(const RF_Type::Size StringSize)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=StringSize-1;
    if (StringSize <= BUFFER_SIZE)
    {
        RF_SysMem::Set(static_cast<void*>(m_FixBuffer.Raw()), ' ', m_Length);
        m_FixBuffer[m_Length] = 0;
        m_FixBuffer.SetSize(StringSize);
    }
    else
    {
        m_DataManagment = DataManagment::AllocateAndCopy;
        m_DynBuffer.m_Buffer = new char[StringSize];
        m_DynBuffer.m_Size = StringSize;
        m_Length = StringSize - 1;
        RF_SysMem::Set(static_cast<void*>(m_DynBuffer.Raw()), ' ', m_Length);
        m_DynBuffer[m_Length] = '\0';
    }
}

String::String(const char Letter)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length = 1;
    m_FixBuffer[0] = Letter;
    m_FixBuffer[1] = 0;
    m_FixBuffer.SetSize(2);
}

String::~String()
{
    if (m_DataManagment == Common::DataManagment::AllocateAndCopy)
    {
        delete[] m_DynBuffer.m_Buffer;
        m_DynBuffer.m_Size = 0;
    }
}

String String::UnsafeStringCreation(const char* CString)
{
    String result;
    RF_Type::Size size = 0;
    const char* stringEnd = CString;
    for (;*stringEnd != '\0'; ++stringEnd, ++size){}
    result = String(CString, size+1);
    return result;
}

void* String::operator new(size_t Bytes)
{
    return RF_SysMem::Allocate(Bytes);
}

void* String::operator new(size_t Bytes, void* Buffer)
{
    UInt8* p = static_cast<UInt8*>(Buffer);
    p += Bytes;
    return static_cast<void*>(p);
}

void String::operator delete(void* Buffer)
{
    RF_SysMem::Free(Buffer);
}

RF_Type::UInt32 String::Length()const
{
    return m_Length;
}

RF_Type::Int32 String::Contains(const String &Str)const
{
    if (Size() < Str.Size())
        return -1;

    return IndexOf(Str, 0, Size());
}

RF_Type::Bool String::EndsWith(const String& Value)const
{
    //this test is faster as in the method with char*
    if (Value.Size() > Size())
        return false;

    const int TERMINATION = 1;
    const char* buffer = GetBuffer();
    Int32 j = Value.Size() - TERMINATION;
    for (UInt32 i = Size() - TERMINATION; i >= 0; --i)
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

RF_Type::Int32 String::IndexOf(const String& Value)const
{
    if (Size() < Value.Size())
        return -1;

    return IndexOf(Value, 0, Size());
}

RF_Type::Int32 String::IndexOf(const String& Value,
                      const RF_Type::UInt32 StartAtIndex)const
{
    if (Size() - StartAtIndex < Value.Size())
        return -1;

    return IndexOf(Value, StartAtIndex, Size() - StartAtIndex);
}

RF_Type::Int32 String::IndexOf(const RF_Type::String& Value,
    const RF_Type::UInt32 StartAtIndex, const RF_Type::UInt32 Count)const
{
    const int TERMINATION = 1;
    if (Count + TERMINATION < Value.Size())
        return -1;

    if (m_Length == 0)
        return -1;

    const char* buffer = GetBuffer();
    RF_Type::Size j=0;
    for (RF_Type::Size i = StartAtIndex; i < StartAtIndex + Count; ++i)
    {
        if(buffer[i] == Value[j])
            ++j;
        else
            j=0;

        if (j == Value.Size() - TERMINATION)
            return i-(j-1);
    }
    return -1;
}

RF_Type::String String::Insert(const RF_Type::UInt32 AtIndex,
    const RF_Type::String& Value)
{
    const int TERMINATION = 1;
    RF_Type::Size byteSize = Size() + Value.Size() - TERMINATION;
    String str(byteSize);

    char* buffer = str.GetBuffer();

    if (AtIndex>0)
        RF_SysMem::Copy(buffer, GetBuffer(), AtIndex);

    RF_SysMem::Copy(buffer + AtIndex, Value.GetBuffer(), Value.Size());
    if (Size() > 0 && AtIndex < Size() - TERMINATION)
        RF_SysMem::Copy(buffer + AtIndex + Value.Size() - TERMINATION, GetBuffer() + AtIndex, Size() - AtIndex);

    return str;
}

RF_Type::Int32 String::LastIndexOf(const String& Value)const
{
    if(Size()<Value.Size())
        return -1;

    return LastIndexOf(Value, 0, Size());
}

RF_Type::Int32 String::LastIndexOf(const RF_Type::String& Value,
    const RF_Type::UInt32 StartAtIndex)const
{
    if (m_Length-StartAtIndex<Value.m_Length)
        return -1;

    return LastIndexOf(Value, StartAtIndex, Size() - StartAtIndex);
}

RF_Type::Int32 String::LastIndexOf(const RF_Type::String& Value,
    const RF_Type::UInt32 StartAtIndex, const RF_Type::UInt32 Count)const
{
    const int TERMINATION = 1;
    if (Count + TERMINATION < Value.Size())
        return -1;

    if (m_Length==0)
        return -1;

    const char* buffer = GetBuffer();

    const char* value = Value.GetBuffer();

    const char* v = value;
    const char *p = buffer + (Size() - Value.Size());
    const char *searchp = p;
    const char *vend = value + Value.Size() - TERMINATION;
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

String String::PadLeft(const RF_Type::UInt32 TotalWidth,
                       const RF_Type::Char PaddingChar)const
{
    if (TotalWidth < m_Length)
        return *this;

    RF_Type::Size byteSize = Size() + (TotalWidth - m_Length);
    String str(byteSize);
    UInt32 offset = TotalWidth - m_Length;
    const char* buffer = GetBuffer();

    char* strBuffer = str.GetBuffer();

    if (PaddingChar!=' ' && offset>0)
        RF_SysMem::Set(strBuffer, PaddingChar, offset);

    RF_SysMem::Copy(strBuffer + offset, buffer, Size());
    return str;
}

String String::PadRight(const RF_Type::UInt32 TotalWidth,
                        const RF_Type::Char PaddingChar)const
{
    const int TERMINATION = 1;
    if (TotalWidth < m_Length)
        return *this;
    
    RF_Type::Size byteSize = Size() + (TotalWidth - m_Length);
    String str(byteSize);
    UInt32 offset = TotalWidth - m_Length;
    const char* buffer = GetBuffer();

    char* strBuffer = str.GetBuffer();

    if (PaddingChar!=' ' && offset>0)
        RF_SysMem::Set(strBuffer + Size() - TERMINATION, PaddingChar, offset);
    RF_SysMem::Copy(strBuffer, buffer, Size() - TERMINATION);
    return str;
}

String String::Remove(const RF_Type::UInt32 StartAtIndex)const
{
    if (StartAtIndex==0)
        return String();
    
    const char* buffer = GetBuffer();

    String str(buffer, StartAtIndex);
    return str;
}

String String::Remove(const RF_Type::UInt32 StartAtIndex,
                      const RF_Type::UInt32 Count)const
{
    const int TERMINATION = 1;
    if (StartAtIndex==0)
        return String();

    if (StartAtIndex >= Size() || Count == 0)
        return *this;

    if (Size() - StartAtIndex - TERMINATION <= Count)
        return Remove(StartAtIndex);

    const char* buffer = GetBuffer();

    UInt32 sc = StartAtIndex + Count;
    RF_Type::Size byteSize = Size() - Count;
    String str(byteSize);
    char* dstBuffer = str.GetBuffer();

    RF_SysMem::Copy(dstBuffer, buffer, StartAtIndex);
    RF_SysMem::Copy(dstBuffer + StartAtIndex, buffer + sc, Size() - sc);
    return str;
}

String String::Replace(const RF_Type::Char OldChar,
                       const RF_Type::Char NewChar)const
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
            RF_SysMem::Copy(str.GetBuffer() + ind, NewValue.GetBuffer(), NewValue.m_Length);
        }
        else
        {
            RF_Mem::AutoPointerArray<char> p(new char[str.m_Length-diff+1],str.m_Length-diff+1);
            p.Get()[str.m_Length-diff]=0;

            if (ind!=0)
            {
                RF_SysMem::Copy(p.Get(),str.GetBuffer(),ind);
            }
            RF_SysMem::Copy(p.Get()+ind,NewValue.GetBuffer(),NewValue.m_Length);
            if (ind+OldValue.m_Length!=str.m_Length)
            {
                RF_SysMem::Copy(p.Get()+ind+NewValue.m_Length,str.GetBuffer()+(ind+OldValue.m_Length),str.m_Length-ind-OldValue.m_Length);
            }
            str = String(p.Get(), p.Size());
        }
    }
    return str;
}


AutoPointerArray<String> String::Split(const String &Delimiters)const
{
    const int TERMINATION = 1;
    AutoPointerArray<String> list;
    const Char* p = GetBuffer();
    RF_Type::Size hits=1;

    for (RF_Type::Size i = 0; i < Size() - TERMINATION; ++i)
    {
        for (RF_Type::Size j = 0; j < Delimiters.Size() - TERMINATION; ++j)
        {
            if (p[i] == Delimiters[j])
            {
                ++hits;
                break;
            }
        }
    }

    list = AutoPointerArray<String>(new String[hits], hits);
    hits=0;
    RF_Type::Size lasthit=0;

    for (RF_Type::Size i = 0; i < Size() - TERMINATION; ++i)
    {
        for (RF_Type::Size j = 0; j < Delimiters.Size() - TERMINATION; ++j)
        {
            if (p[i] == Delimiters[j])
            {
                String& str=list[hits];
                str = SubString(lasthit, i - lasthit);
                lasthit = i + 1;
                ++hits;
                break;
            }
        }
    }

    if (lasthit < Size() - TERMINATION)
    {
        String& str = list[hits];
        str = SubString(lasthit, Size() - lasthit - TERMINATION);
    }
    return list;
}

RF_Type::Bool String::StartsWith(const String& AString)const
{
    if (AString.m_Length>m_Length || AString.m_Length==0)
        return false;
    return RF_SysMem::Compare(GetBuffer(), AString.GetBuffer(), AString.m_Length) == 0 ? true : false;
}

String String::SubString(const RF_Type::UInt32 StartIndex,
                        const RF_Type::UInt32 Count)const
{
    if (StartIndex+Count>m_Length || Count==0)
        return String();
    String str(GetBuffer() + StartIndex, Count);
    str.GetBuffer()[Count - 1] = '\0';
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
    for (; i < Size(); ++i)
    {
        foundone = false;
        for (UInt32 j = 0; j < TrimChars.m_Length; ++j)
        {
            if (GetBuffer()[i] == TrimChars[j])
            {
                foundone=true;
            }
        }

        if (!foundone)
            break;
    }
    String str(GetBuffer() + i, Size() - i);
    return str;
}

String String::TrimEnd(const String& TrimChars)const
{
    Bool foundone;
    UInt32 i = Size() - 2;
    for (; i >= 0; --i)
    {
        foundone = false;
        for (UInt32 j = 0; j < TrimChars.m_Length; ++j)
        {
            if (GetBuffer()[i] == TrimChars[j])
            {
                foundone = true;
            }
        }

        if (!foundone)
            break;
    }
    String str(GetBuffer(), i + 1);
    return str;
}

RF_Type::Int32 String::Compare(const String& With)const
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

char String::operator[](const RF_Type::Size Index)const
{
    Assert(static_cast<UInt32>(Index) <= Size() && Index >= 0, "Out of bound.");
    return *(GetBuffer() + Index);
}

char& String::operator[](const RF_Type::Size Index)
{
    Assert(static_cast<UInt32>(Index) <= Size() && Index >= 0, "Out of bound");
    return *(GetBuffer() + Index);
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

String String::operator+(const String& Str)const
{
    if (Length() + Str.Length())
    {
        RF_Type::Size bytes = Size() + Str.Size() - 1;
        String str(bytes);

        if (Length() > 0)
            RF_SysMem::Copy(const_cast<char*>(str.c_str()), c_str(), Size());

        if (Str.Length() > 0)
            RF_SysMem::Copy(const_cast<char*>(str.c_str() + Size() - 1), Str.c_str(), Str.Size());

        return str;
    }
    return String();
}

String& String::operator+=(const String& Str)
{
    if (Str.m_Length > 0)
    {
        RF_Type::Size bytes = m_Length + Str.m_Length + 1;
        String newStr(bytes);

        if (m_Length>0)
            RF_SysMem::Copy(newStr.GetBuffer(), GetBuffer(), m_Length);
        RF_SysMem::Copy(newStr.GetBuffer() + m_Length, Str.GetBuffer(), Str.m_Length + 1);
        Swap(newStr);
    }
    return *this;
}

String& String::operator=(const String &Other)
{
    m_DataManagment = Other.m_DataManagment;
    m_Length = Other.m_Length;
    if (Other.m_DataManagment == Common::DataManagment::Copy)
    {// Other is a locale buffer
        RF_SysMem::Copy(m_FixBuffer.Raw(), Other.m_FixBuffer.Raw(), BUFFER_SIZE);
        m_FixBuffer.SetSize(Other.m_FixBuffer.GetSize());
    }
    else
    {
        m_DynBuffer.m_Size = Other.m_DynBuffer.m_Size;
        m_DynBuffer.m_Buffer = new Char[m_DynBuffer.m_Size];
        RF_SysMem::Copy(m_DynBuffer.Raw(), Other.m_DynBuffer.Raw(), m_DynBuffer.m_Size);
    }
    return *this;
}

char const* String::c_str()const
{
    return GetBuffer();
}

RF_Type::Int32 String::HexToDec()const
{
    Int64 val;
    RF_SysStr::ToInt64(*this, 16, val);
    return val;
}

String String::Format(const String& Str,...)
{
    va_list argp;
    va_start(argp, Str);

    String result;
    result = String::FormatStrict(Str, argp);

    va_end(argp);
    return result;
}

String String::FormatStrict(const String& Str, va_list ArgumentList)
{
    RF_Mem::AutoPointerArray<char> out;
    RF_Mem::AutoPointerArray<char> dynBuf;
    Int32 byteLen=0;
    Int32 buflen=0;
    while(byteLen==buflen || byteLen==-1)
    {
        buflen+=256;
        dynBuf=RF_Mem::AutoPointerArray<char>(new char[buflen],buflen);
        byteLen = RF_SysStr::Format(reinterpret_cast<UInt8*>(dynBuf.Get()), buflen-1, Str, ArgumentList);
    }
    out=RF_Mem::AutoPointerArray<char>(new char[byteLen+1],byteLen+1);
    RF_SysMem::Copy(out.Get(),dynBuf.Get(),byteLen);
    out.Get()[byteLen]=0;

    return String(out.Release().Ptr, byteLen, DataManagment::TransfereOwnership);
}

void String::ToUpper()
{
    RF_SysStr::ToUpper(*this);
}

void String::ToLower()
{
    RF_SysStr::ToLower(*this);
}

RF_Type::Bool String::IsNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if (GetBuffer()[i]>=48 && GetBuffer()[i]<=57)
        {
        }
        else
            return false;
    return true;
}

RF_Type::Bool String::IsFloatingpointNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if ((GetBuffer()[i]>=48 && GetBuffer()[i]<=57) || GetBuffer()[i]=='.')
        {
        }
        else
            return false;
    return true;
}

RF_Type::Bool String::IsBoolean()const 
{    
    static const String TRUE("true", sizeof("true"));
    static const String FALSE("false", sizeof("false"));
    String lowerCase=*this;
    lowerCase.ToLower();
    return lowerCase == TRUE || lowerCase == FALSE;
}

void String::Swap(String& Other)
{
    Assert(&Other != this, "It's not allowed to use Swap with itself!");
    // make a copy of this to tmp;
    String tmp;
    if (m_Length > 0)
    {
        tmp.m_DataManagment = m_DataManagment;
        tmp.m_Length = m_Length;
        if (m_DataManagment == Common::DataManagment::Copy)
        {
            RF_SysMem::Copy(tmp.m_FixBuffer.Raw(), m_FixBuffer.Raw(), BUFFER_SIZE);
            tmp.m_FixBuffer.SetSize(m_FixBuffer.GetSize());
        }
        else
        {
            tmp.m_DynBuffer.m_Buffer = m_DynBuffer.m_Buffer;
            tmp.m_DynBuffer.m_Size = m_DynBuffer.m_Size;
            // ensure to not leak memory
            m_DynBuffer.m_Size = 0;
            m_DynBuffer.m_Buffer = 0;
        }
    }

    // copy Other to this
    m_DataManagment = Other.m_DataManagment;
    m_Length = Other.m_Length;
    if (Other.m_DataManagment == Common::DataManagment::Copy)
    {// Other use a locale buffer
        RF_SysMem::Copy(m_FixBuffer.Raw(), Other.m_FixBuffer.Raw(), BUFFER_SIZE);
        m_FixBuffer.SetSize(Other.m_FixBuffer.GetSize());
    }
    else
    {
        m_DynBuffer.m_Buffer = Other.m_DynBuffer.m_Buffer;
        m_DynBuffer.m_Size = Other.m_DynBuffer.m_Size;
        // ensure to not leak memory
        Other.m_DynBuffer.m_Buffer = 0;
        Other.m_DynBuffer.m_Size = 0;
    }

    // move tmp to Other
    Other.m_DataManagment = tmp.m_DataManagment;
    Other.m_Length = tmp.m_Length;
    if (tmp.m_DataManagment == Common::DataManagment::Copy)
    {// tmp use a locale buffer
        if (tmp.m_Length > 0)
        {
            RF_SysMem::Copy(Other.m_FixBuffer.Raw(), tmp.m_FixBuffer.Raw(), BUFFER_SIZE);
        }
        else
        {
            Other.m_FixBuffer[0] = '\0';
        }
        Other.m_FixBuffer.SetSize(tmp.m_FixBuffer.GetSize());
    }
    else
    {
        Other.m_DynBuffer.m_Buffer = tmp.m_DynBuffer.m_Buffer;
        Other.m_DynBuffer.m_Size = tmp.m_DynBuffer.m_Size;
        // ensure to not leak memory
        tmp.m_DynBuffer.m_Buffer = 0;
        tmp.m_DynBuffer.m_Size = 0;
    }
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

RF_Type::Bool String::IsEmpty() const
{
    return Size() == 0;
}

RF_Type::Size String::Size()const
{
    if (m_DataManagment == DataManagment::Copy)
        return m_FixBuffer.GetSize();
    else
        return m_DynBuffer.GetSize();
}
