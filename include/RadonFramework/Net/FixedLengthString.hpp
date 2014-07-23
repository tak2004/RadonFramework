#ifndef RF_FIXEDLENGTHSTRING_HPP
#define RF_FIXEDLENGTHSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework { namespace Net {

template<typename T, unsigned long Len>
class FixedLengthString
{
public:
    FixedLengthString(){
        m_Len=0;
        RF_SysMem::Set(m_Data,0,Len+1);
    }

    T MaxSize()const
    {
        return Len;
    }

    void operator =(const char* Text)
    {
        RF_Type::Size len=0;
        if (Text)
        {
            RF_Type::String str = RF_Type::String::UnsafeStringCreation(Text, Core::Common::DataManagment::UnmanagedInstance);
            len=str.Length();
        }
        Assert(Len>=len, "Index out of bound.");
        m_Len=static_cast<T>(len);
        if (m_Len>0)
            RF_SysMem::Copy(m_Data, Text, m_Len);
        m_Data[m_Len]=0;
    }

    void operator =(const RF_Type::String& Str)
    {
        Assert(Len>=Str.Length(),"Index out of bound.");
        m_Len=Str.Length();
        if (m_Len>0)
            RF_SysMem::Copy(m_Data,Str.c_str(),m_Len);
        m_Data[m_Len]=0;
    }

    const bool operator ==(const FixedLengthString<T,Len> &Other)const
    {
        for (int i=0;i<=m_Len;i++)
            if (m_Data[i]!=Other.m_Data[i])
                return false;
        return true;
    }
                
    char const* c_str()const
    {
        return m_Data;
    }

    inline char& operator[](const T Index)
    {
        Assert(Index<Len,"Index out of bound.");
        return m_Data[Index];
    }

    inline RF_Type::String ToString()const
    {
        return RF_Type::String(m_Data,m_Len);
    }
protected:
    T m_Len;
    char m_Data[Len+1];
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
