#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Math.hpp"
#include "RadonFramework/Collections/ArrayEnumerator.hpp"
#include <string.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;

String::String()
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=0;
}

String::String(const String& Copy)
:m_DataManagment(Common::DataManagment::Copy)
{
    switch (Copy.m_DataManagment)
    {
    case Common::DataManagment::TransfereOwnership:
    case Common::DataManagment::Copy:
        m_Length = Copy.m_Length;
        if (m_Length > 0)
        {
            m_Text = RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length + 1], m_Length + 1);
            RFMEM::Copy(m_Text.Get(), Copy.m_Text.Get(), m_Length + 1);
        }
        break;
    case Common::DataManagment::UnmanagedInstance:
        m_DataManagment = Common::DataManagment::UnmanagedInstance;
        m_Length = Copy.m_Length;
        m_Text = Copy.m_Text.Clone();
        break;
    }
}

String::String(const char* Str, DataManagment::Type Ownership)
:m_DataManagment(Ownership)
{
    if (Str==0)
        m_Length=0;
    else
    {
        m_Length=static_cast<UInt32>(strlen(Str));
        if (m_Length>0)
        {
            switch (m_DataManagment)
            {
                case Common::DataManagment::Copy:
                    m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
                    RFMEM::Copy(m_Text.Get(), Str, m_Length+1);
                    break;
                case Common::DataManagment::UnmanagedInstance:
                case Common::DataManagment::TransfereOwnership:
                    m_Text=RadonFramework::Memory::AutoPointerArray<char>((char*)Str,m_Length+1);
                    break;
            }
        }
    }
}


String::String(const char* cString, UInt32 cStringLength)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=cStringLength;
    if (cString!=0 && m_Length>0)
    {
        m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
        RFMEM::Copy(m_Text.Get(), cString, m_Length);
        m_Text.Get()[m_Length]=0;
    }
}


String::String(const UInt32 StringLength)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=StringLength;
    if (m_Length>0)
    {
        m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
        RFMEM::Set(m_Text.Get(),' ',m_Length+1);
        m_Text.Get()[m_Length]=0;
    }
}

String::String(const char Letter)
:m_DataManagment(Common::DataManagment::Copy)
{
    m_Length=1;
    m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[2],2);
    m_Text.Get()[0]=Letter;
    m_Text.Get()[1]=0;
}

String::~String()
{
    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
        m_Text.Release();
}

UInt32 String::Length()const
{
    return m_Length;
}


Int32 String::Contains(const String &Str)const
{
    if (m_Length<Str.m_Length)
        return -1;

    return IndexOf(Str.c_str(),0,m_Length);
}


Bool String::EndsWith(const String& Value)const
{
    //this test is faster as in the method with char*
    if (Value.m_Length>m_Length)
        return false;

    return EndsWith(Value.c_str());
}


Bool String::EndsWith(const char* Value)const
{
    UInt32 valuelen=static_cast<UInt32>(strlen(Value));
    if (valuelen>m_Length)
        return false;

    Int32 j=valuelen-1;
    for (UInt32 i=m_Length-1;i>=0;--i)
    {
        if(m_Text.Get()[i]==Value[j])
            --j;
        else
            return false;

        if(j==-1)
            return true;
    }
    return false;
}


Int32 String::IndexOf(const String& Value)const
{
    if (m_Length<Value.m_Length)
        return -1;

    return IndexOf(Value.c_str(),0,m_Length);
}


Int32 String::IndexOf(const char* Value)const
{
    return IndexOf(Value,0,m_Length);
}


Int32 String::IndexOf(const String& Value,
                      const UInt32 StartAtIndex)const
{
    if (m_Length-StartAtIndex<Value.m_Length)
        return -1;

    return IndexOf(Value.c_str(),StartAtIndex,m_Length-StartAtIndex);
}


Int32 String::IndexOf(const char* Value,
                      const UInt32 StartAtIndex)const
{
    return IndexOf(Value,StartAtIndex,m_Length-StartAtIndex);
}


Int32 String::IndexOf(const String& Value,
                      const UInt32 StartAtIndex,
                      const UInt32 Count)const
{
    if (Count<Value.m_Length)
        return -1;

    return IndexOf(Value.c_str(),StartAtIndex,Count);
}


Int32 String::IndexOf(const char* Value,
                      const UInt32 StartAtIndex,
                      const UInt32 Count)const
{
    UInt32 valuelen=static_cast<UInt32>(strlen(Value));
    if (m_Length==0)
        return -1;

    if (valuelen>Count)
        return -1;

    Int32 j=0;
    for (UInt32 i=StartAtIndex;i<StartAtIndex+Count;++i)
    {
        if(m_Text.Get()[i]==Value[j])
            ++j;
        else
            j=0;

        if (j==(Int32)valuelen)
            return i-(j-1);
    }
    return -1;
}


String String::Insert(const UInt32 AtIndex,
                      const String& Value)
{
    Assert(m_Length>0, "Invalid operation.");
    String str(m_Length+Value.m_Length);
    if (AtIndex>0)
        RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),AtIndex);
    RFMEM::Copy(str.m_Text.Get()+AtIndex,Value.c_str(),Value.m_Length);
    if (m_Length>0)
        RFMEM::Copy(str.m_Text.Get()+AtIndex+Value.m_Length,m_Text.Get()+AtIndex,m_Length-AtIndex);
    return str;
}


String String::Insert(const UInt32 AtIndex,
                      const char* Value)
{
    return Insert(AtIndex,String(Value));
}


Int32 String::LastIndexOf(const String& Value)const
{
    if (m_Length<Value.m_Length)
        return -1;

    return LastIndexOf(Value.c_str(),0,m_Length);
}


Int32 String::LastIndexOf(const char* Value)const
{
    return LastIndexOf(Value,0,m_Length);
}


Int32 String::LastIndexOf(const String& Value,
                          const UInt32 StartAtIndex)const
{
    if (m_Length-StartAtIndex<Value.m_Length)
        return -1;

    return LastIndexOf(Value.c_str(),StartAtIndex,m_Length-StartAtIndex);
}


Int32 String::LastIndexOf(const char* Value,
                                 const UInt32 StartAtIndex)const
{
    return LastIndexOf(Value,StartAtIndex,m_Length-StartAtIndex);
}


Int32 String::LastIndexOf(const String& Value,
                          const UInt32 StartAtIndex,
                          const UInt32 Count)const
{
    if (Count<Value.m_Length)
        return -1;

    return LastIndexOf(Value.c_str(),StartAtIndex,Count);
}


Int32 String::LastIndexOf(const char* Value,
                          const UInt32 StartAtIndex,
                          const UInt32 Count)const
{
    UInt32 valuelen=static_cast<UInt32>(strlen(Value));
    if (m_Length==0)
        return -1;

    if (valuelen>Count)
        return -1;

    const char *str=m_Text.Get();
    const char *p=str+(StartAtIndex+Count-valuelen+1);
    const char *searchp=p;
    const char *v=Value;
    const char *vend=Value+valuelen;
    const char *pend=str+StartAtIndex-1;

    for(;p!=pend;--p,searchp=p)
    {
        while(v!=vend && *searchp==*v)//compare func
        {
            ++searchp;
            ++v;
        }

        if (v==vend)//finished search
            return static_cast<Int32>(MemoryRange(p-str));
        else
            v=Value;//reset v for next search
    }
    return -1;
}


String String::PadLeft(const UInt32 TotalWidth,
                       const Char PaddingChar)const
{
    if (TotalWidth<m_Length)
        return *this;
    String str(TotalWidth);
    UInt32 offset=TotalWidth-m_Length;
    if (PaddingChar!=' ' && offset>0)
        RFMEM::Set(str.m_Text.Get(),PaddingChar,offset);
    RFMEM::Copy(str.m_Text.Get()+offset,m_Text.Get(),m_Length);
    return str;
}


String String::PadRight(const UInt32 TotalWidth,
                        const Char PaddingChar)const
{
    if (TotalWidth<m_Length)
        return *this;
    String str(TotalWidth);
    UInt32 offset=TotalWidth-m_Length;
    if (PaddingChar!=' ' && offset>0)
        RFMEM::Set(str.m_Text.Get()+m_Length,PaddingChar,offset);
    RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),m_Length);
    return str;
}


String String::Remove(const UInt32 StartAtIndex)const
{
    if (StartAtIndex==0)
        return String();
    String str(m_Text.Get(),StartAtIndex);
    return str;
}


String String::Remove(const UInt32 StartAtIndex,
                      const UInt32 Count)const
{
    if (StartAtIndex==0)
        return String();
    if (StartAtIndex>m_Length || Count==0)
        return *this;
    if (m_Length-StartAtIndex<Count)
        return String(m_Text.Get(),StartAtIndex);

    UInt32 sc=StartAtIndex+Count;
    String str(m_Length-Count);
    RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),StartAtIndex);
    RFMEM::Copy(str.m_Text.Get()+StartAtIndex,m_Text.Get()+sc,m_Length-sc);
    return str;
}


String String::Replace(const Char OldChar,
                       const Char NewChar)const
{
    String str(*this);
    char *p=str.m_Text.Get();
    for (UInt32 i=0;i<m_Length;++i)
        if (p[i]==OldChar)
            p[i]=NewChar;
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
            RFMEM::Copy(str.m_Text.Get()+ind,NewValue.m_Text.Get(),NewValue.m_Length);
        }
        else
        {
            RadonFramework::Memory::AutoPointerArray<char> p(new char[str.m_Length-diff+1],str.m_Length-diff+1);
            p.Get()[str.m_Length-diff]=0;

            if (ind!=0)
            {
                RFMEM::Copy(p.Get(),str.m_Text.Get(),ind);
            }
            RFMEM::Copy(p.Get()+ind,NewValue.m_Text.Get(),NewValue.m_Length);
            if (ind+OldValue.m_Length!=str.m_Length)
            {
                RFMEM::Copy(p.Get()+ind+NewValue.m_Length,str.m_Text.Get()+(ind+OldValue.m_Length),str.m_Length-ind-OldValue.m_Length);
            }
            str.m_Text=p;
            str.m_Length-=diff;
        }
    }
    return str;
}


AutoPointerArray<String> String::Split(const String &Delimiters)const
{
    AutoPointerArray<String> list;
    UInt32 lasthit=0;
    Char* p=m_Text.Get();
    UInt32 hits=1;
    for (UInt32 i=0;i<m_Length-1;i++)
        for (UInt32 j=0;j<Delimiters.m_Length;j++)
            if (p[i]==Delimiters[j])
            {
                ++hits;
                break;
            }

    list=AutoPointerArray<String>(new String[hits],hits);
    hits=0;
    for (UInt32 i=0;i<m_Length;i++)
        for (UInt32 j=0;j<Delimiters.m_Length;j++)
            if (p[i]==Delimiters[j])
            {
                String& str=list[hits];
                str.m_Length=i-lasthit;
                str.m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[str.m_Length+1],str.m_Length+1);
                RFMEM::Copy(str.m_Text.Get(),p+lasthit,i-lasthit);
                str.m_Text.Get()[i-lasthit]=0x00;
                lasthit=i+1;
                ++hits;
                break;
            }

    if (lasthit<m_Length)
    {
        String& str=list[hits];
        str.m_Length=m_Length-lasthit;
        str.m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[str.m_Length+1],str.m_Length+1);
        RFMEM::Copy(str.m_Text.Get(),p+lasthit,m_Length-lasthit+1);//copy the 0 termination too
    }
    return list;
}


AutoPointerArray<String> String::Split(const Char* Delimiters)const
{
    return Split(String(Delimiters));
}


Bool String::StartsWith(const String& AString)const
{
    if (AString.m_Length>m_Length || AString.m_Length==0)
        return false;
    return RFMEM::Compare(m_Text.Get(),AString.m_Text.Get(),AString.m_Length)==0?true:false;
}


String String::SubString(const UInt32 StartIndex,
                        const UInt32 Count)const
{
    if (StartIndex+Count>m_Length || Count==0)
        return String();
    String str(m_Text.Get()+StartIndex,Count);
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
            if (m_Text.Get()[i]==TrimChars[j])
                foundone=true;
        if (!foundone)
            break;
    }
    String str(m_Text.Get()+i,m_Length-i);
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
            if (m_Text.Get()[i]==TrimChars[j])
                foundone=true;
        if (!foundone)
            break;
    }
    String str(m_Text.Get(),i+1);
    return str;
}


Int32 String::Compare(const String& With)const
{
    if (m_Length==With.m_Length)
    {
        for (UInt32 i=0;i<m_Length;++i)
            if ((*this)[i]==With[i])
            {
            }
            else
                return i+1;
    }
    else
        return -1;
    return 0;
}


char String::operator[](const MemoryRange Index)const
{
    Assert(static_cast<UInt32>(Index)<m_Length+1&&Index>=0, "Out of bound.");
    return *(m_Text.Get()+Index);
}


char& String::operator[](const MemoryRange Index)
{
    Assert(static_cast<UInt32>(Index)<m_Length+1&&Index>=0, "Out of bound");
    return *(m_Text.Get()+Index);
}


bool String::operator==(const String& Other)const
{
    if (m_Length!=Other.m_Length)
        return false;
    for (UInt32 i=0;i<m_Length;i++)
        if (m_Text.Get()[i]!=Other.m_Text.Get()[i])
            return false;
    return true;
}


bool String::operator==(const char* Other)const
{
    UInt32 len=static_cast<UInt32>(strlen(Other));
    if (len!=m_Length)
        return false;
    for  (UInt32 i=0;i<len;++i)
        if (m_Text.Get()[i]!=Other[i])
            return false;
    return true;
}


bool String::operator!=(const String& Other)const
{
    if (Other.m_Length!=m_Length)
        return true;
    for (UInt32 i=0;i<m_Length;++i)
        if (m_Text.Get()[i]!=Other.m_Text.Get()[i])
            return true;
    return false;
}


bool String::operator!=(const char* Other)const
{
    UInt32 len=static_cast<UInt32>(strlen(Other));
    if (len!=m_Length)
        return true;
    for (UInt32 i=0;i<len;++i)
        if (m_Text.Get()[i]!=Other[i])
            return true;
    return false;
}


String String::operator+(const String &Str)const
{
    String str;
    str.m_Length=m_Length+Str.m_Length;
    if (str.m_Length>0)
    {
        str.m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[str.m_Length+1],str.m_Length+1);
        if (m_Length>0)
            RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),m_Length);
        if (Str.m_Length>0)
            RFMEM::Copy(str.m_Text.Get()+m_Length,Str.m_Text.Get(),Str.m_Length);
        str[str.m_Length]='\0';
    }
    return str;
}


String String::operator+(const char* Str)const
{
    String str;
    str.m_Length=static_cast<UInt32>(strlen(Str)+m_Length);
    if (str.m_Length>0)
    {
        str.m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[str.m_Length+1],str.m_Length+1);
        if (m_Length>0)
            RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),m_Length);
        if (Str[0]!='\0')
            RFMEM::Copy(str.m_Text.Get()+m_Length, Str,strlen(Str));
        str[str.m_Length]='\0';
    }
    return str;
}


String String::operator+(const Char Character)const
{
    String str;
    str.m_Length=m_Length+1;
    str.m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[str.m_Length+1],str.m_Length+1);
    if (m_Length>0)
        RFMEM::Copy(str.m_Text.Get(),m_Text.Get(),m_Length);
    str[str.m_Length-1]=Character;
    str[str.m_Length]='\0';
    return str;
}


String String::operator+(const Bool& Value)const
{
    String res(*this);
    res+=(Value==true?"true":"false");
    return res;
}


String String::operator+(const Int8 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const Int16 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const Int32 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const Int64 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const UInt8 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const UInt16 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const UInt32 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String String::operator+(const UInt64 Number)const
{
    String res(*this);
    res+=Convert::ToString(Number);
    return res;
}


String& String::operator+=(const char *Str)
{
    UInt32 len=static_cast<UInt32>(m_Length+strlen(Str));
    if (len>0)
    {
        if (len>m_Length)
        {
            RadonFramework::Memory::AutoPointerArray<char> str=RadonFramework::Memory::AutoPointerArray<char>(new char[len+1],len+1);
            if (m_Length>0)
                RFMEM::Copy(str.Get(),m_Text.Get(),m_Length);
            RFMEM::Copy(str.Get()+m_Length,Str,strlen(Str)+1);
            m_Text=str;
            m_Length+=static_cast<UInt32>(strlen(Str));
        }
    }
    return *this;
}


String& String::operator+=(const Char Character)
{
    UInt32 len=m_Length+1;
    RadonFramework::Memory::AutoPointerArray<char> str=RadonFramework::Memory::AutoPointerArray<char>(new char[len+1],len+1);
    if (m_Length>0)
        RFMEM::Copy(str.Get(),m_Text.Get(),m_Length);
    ++m_Length;
    str[m_Length-1]=Character;
    str[m_Length]='\0';
    m_Text=str;
    return *this;
}


String& String::operator+=(const String& Str)
{
    UInt32 len=m_Length+Str.m_Length;
    if (len>0)
    {
        if (len>m_Length)
        {
            RadonFramework::Memory::AutoPointerArray<char> str=RadonFramework::Memory::AutoPointerArray<char>(new char[len+1],len+1);
            if (m_Length>0)
                RFMEM::Copy(str.Get(),m_Text.Get(),m_Length);
            RFMEM::Copy(str.Get()+m_Length,Str.m_Text.Get(),Str.m_Length+1);
            m_Text=str;
            m_Length+=Str.m_Length;
        }
    }
    return *this;
}


String& String::operator+=(const Bool& Value)
{
    *this+=(Value==true?"true":"false");
    return *this;
}


String& String::operator+=(const Int8 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const Int16 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const Int32 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const Int64 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const UInt8 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const UInt16 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const UInt32 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator+=(const UInt64 Number)
{
    *this+=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const char *Str)
{
    m_Length=static_cast<UInt32>(strlen(Str));

    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
        m_Text.Reset();

    if (m_Length>0)
    {
        m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
        RFMEM::Copy(m_Text.Get(),Str,m_Length+1);
    }
    return *this;
}


String& String::operator=(const Char Character)
{
    m_Length=1;

    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
        m_Text.Reset();

    m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
    m_Text[m_Length-1]=Character;
    m_Text[m_Length]='\0';
    return *this;
}


String& String::operator=(const String &Other)
{
    m_Length=Other.m_Length;

    if (m_DataManagment==Common::DataManagment::UnmanagedInstance)
        m_Text.Reset();

    if (m_Length>0)
    {
        m_Text=RadonFramework::Memory::AutoPointerArray<char>(new char[m_Length+1],m_Length+1);
        RFMEM::Copy(m_Text.Get(),Other.m_Text.Get(),m_Length+1);
    }
    return *this;
}


String& String::operator=(const Bool& Value)
{
    *this=(Value==true?"true":"false");
    return *this;
}


String& String::operator=(const Int8 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const Int16 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const Int32 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const Int64 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const UInt8 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const UInt16 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const UInt32 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


String& String::operator=(const UInt64 Number)
{
    *this=Convert::ToString(Number);
    return *this;
}


char const* String::c_str()const
{
    return m_Text.Get();
}


Int32 String::HexToDec()const
{
    Int64 val;
    RFSTR::ToInt64(*this, 16, val);
    return val;
}


String String::Format(const char* Str,...)
{
    va_list argp;
    va_start(argp,Str);
    String result = Format(Str, argp);
    va_end(argp);
    return result;
}


String String::Format(const String& Str,...)
{
    va_list argp;
    va_start(argp,Str);
    String result = Format(Str.c_str(), argp);
    va_end(argp);
    return result;
}

UInt32 String::Format(AutoPointerArray<UInt8>& Buffer, const UInt32 BufferBoundaryStart,
    const UInt32 BufferBoundaryEnd, const char* Str,...)
{
    va_list argp;
    va_start(argp,Str);
    Int32 result = RFSTR::Format(Buffer.Get()+BufferBoundaryStart,
        BufferBoundaryEnd-BufferBoundaryStart, String(Str, RadonFramework::Core::Common::DataManagment::UnmanagedInstance), argp);
    va_end(argp);
    if (result>=0 && static_cast<UInt32>(result)<BufferBoundaryEnd-BufferBoundaryStart)
        return result;
    else
        return 0;
}

UInt32 String::Format(AutoPointerArray<UInt8>& Buffer, const UInt32 BufferBoundaryStart,
    const UInt32 BufferBoundaryEnd, const String& Str,...)
{
    va_list argp;
    va_start(argp,Str);
    Int32 result = RFSTR::Format(Buffer.Get()+BufferBoundaryStart,
        BufferBoundaryEnd-BufferBoundaryStart, Str, argp);
    va_end(argp);
    if (result>=0 && static_cast<UInt32>(result)<BufferBoundaryEnd-BufferBoundaryStart)
        return result;
    else
        return 0;
}

String String::Format(const char* Str, va_list argptr)
{
    RadonFramework::Memory::AutoPointerArray<char> out;
    RadonFramework::Memory::AutoPointerArray<char> dynBuf;
    Int32 len=0;
    Int32 buflen=0;
    while(len==buflen || len==-1)
    {
        buflen+=256;
        dynBuf=RadonFramework::Memory::AutoPointerArray<char>(new char[buflen],buflen);
        len = RFSTR::Format(reinterpret_cast<UInt8*>(dynBuf.Get()), buflen-1, String(Str, RadonFramework::Core::Common::DataManagment::UnmanagedInstance), argptr);
    }
    out=RadonFramework::Memory::AutoPointerArray<char>(new char[len+1],len+1);
    RFMEM::Copy(out.Get(),dynBuf.Get(),len);
    out.Get()[len]=0;
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

Bool String::IsNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if (m_Text.Get()[i]>=48 && m_Text.Get()[i]<=57)
        {
        }
        else
            return false;
    return true;
}

Bool String::IsFloatingpointNumber()const 
{
    for (UInt32 i=0;i<m_Length;++i)
        if ((m_Text.Get()[i]>=48 && m_Text.Get()[i]<=57) || m_Text.Get()[i]=='.')
        {
        }
        else
            return false;
    return true;
}

Bool String::IsBoolean()const 
{    
    String lowerCase=*this;
    lowerCase.ToLower();
    return lowerCase=="true" || lowerCase=="false";
}

void String::Swap(String& Other)
{
    UInt32 l=m_Length;
    m_Length=Other.m_Length;
    Other.m_Length=l;

    Common::DataManagment::Type t=m_DataManagment;
    m_DataManagment=Other.m_DataManagment;
    Other.m_DataManagment=t;

    m_Text.Swap(Other.m_Text);
}

String& operator<<(String &Str, const Int8 &Self)
{
    return Str+=Convert::ToString(Self);
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

String& operator<<(String &Str, const char *c_str)
{
    Str+=c_str;
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

AutoPointer<ArrayEnumerator<char> > String::GetEnumerator()
{
    return AutoPointer<ArrayEnumerator<char> >(new ArrayEnumerator<char>(m_Text.Get(), m_Text.Get()+m_Length));
}

Bool String::IsEmpty() const
{
    return m_Length == 0;
}

Size String::Size()const
{
    return m_Text.Size();
}