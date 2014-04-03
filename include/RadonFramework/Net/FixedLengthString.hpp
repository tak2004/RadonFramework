#ifndef RF_FIXEDLENGTHSTRING_HPP
#define RF_FIXEDLENGTHSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework
{
    namespace Net
    {
        template<typename T, unsigned long Len>
        class FixedLengthString
        {
            public:
                FixedLengthString(){
                    m_Len=0;
                    RFMEM::Set(m_Data,0,Len+1);
                }

                T MaxSize()const
                {
                    return Len;
                }

                void operator =(const char* Text)
                {
                    RFTYPE::Size len=0;
                    if (Text)
                    {
                        RFTYPE::String str(Text, Core::Common::DataManagment::UnmanagedInstance);
                        len=str.Length();
                    }
                    Assert(Len>=len, "Index out of bound.");
                    m_Len=static_cast<T>(len);
                    if (m_Len>0)
                        RFMEM::Copy(m_Data, Text, m_Len);
                    m_Data[m_Len]=0;
                }

                void operator =(const RFTYPE::String& Str)
                {
                    Assert(Len>=Str.Length(),"Index out of bound.");
                    m_Len=Str.Length();
                    if (m_Len>0)
                        RFMEM::Copy(m_Data,Str.c_str(),m_Len);
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

                inline RFTYPE::String ToString()const
                {
                    return RFTYPE::String(m_Data,m_Len);
                }
            protected:
                T m_Len;
                char m_Data[Len+1];
        };
    }
}

#endif
