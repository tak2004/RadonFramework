#ifndef RF_PACKETWITHHEADER_HPP
#define RF_PACKETWITHHEADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework
{
    namespace Net
    {
        template <typename _Header,typename _Data>
        class PacketWithHeader
        {
            public:
                PacketWithHeader()
                {
                    m_Data=RF_Mem::AutoPointerArray<char>(sizeof(_Header)+sizeof(_Data));
                    Header=(_Header*)(m_Data.Get());
                    Data=(_Data*)(m_Data.Get()+sizeof(_Header));
                }
                /** @brief Copy header and data from pointer to internal structure.
                  *
                  *
                  */
                PacketWithHeader(void *DataPtr)
                {
                    m_Data = RF_Mem::AutoPointerArray<char>(sizeof(_Header) + sizeof(_Data));
                    RF_SysMem::Copy(m_Data.Get(), DataPtr, sizeof(_Header) + sizeof(_Data));
                    Header=(_Header*)(m_Data.Get());
                    Data=(_Data*)(m_Data.Get()+sizeof(_Header));
                }
                _Header *Header;
                _Data *Data;
                unsigned int Size()const
                {
                    return sizeof(_Header)+sizeof(_Data);
                }
                const char* ByteData()const
                {
                    return m_Data.Get();
                }
            protected:
                RF_Mem::AutoPointerArray<char> m_Data;
        };
    }
}

#endif
