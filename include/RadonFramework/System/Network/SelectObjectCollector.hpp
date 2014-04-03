#ifndef RF_SYSTEM_NETWORK_SELECTOBJECTCOLLECTOR_HPP
#define RF_SYSTEM_NETWORK_SELECTOBJECTCOLLECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Socket.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Net/SelectMode.hpp>
#include <RadonFramework/Net/Error.hpp>

namespace RadonFramework
{
    namespace Time
    {
        class TimeSpan;
    }
    namespace System
    {
        namespace Network
        {
            class SelectObjectCollector
            {
                public:       
                    class PIMPL;

                    static RadonFramework::Memory::AutoPointer<SelectObjectCollector> Create(
                        const Net::Socket& Handler);

                    Net::Error::Type Select(const Net::SelectMode::Type Mode,
                        const Time::TimeSpan* Timeout=0);

                    ~SelectObjectCollector();
                    void Add(const NetService::SocketHandler& Handler);
                    void Remove(const RFTYPE::Size Index);
                    
                    RFTYPE::Size Count()const;
                    RFTYPE::Bool IsSet(const RFTYPE::Size Index)const;
                protected:
                    PIMPL* m_Data;
                private:
                    SelectObjectCollector();
                    SelectObjectCollector(const SelectObjectCollector& Copy);
            };
        }
    }
}

#endif // RF_SYSTEM_NETWORK_SELECTOBJECTCOLLECTOR_HPP