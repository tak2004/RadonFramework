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

namespace RadonFramework { namespace Time {
class TimeSpan;
} }

namespace RadonFramework { namespace System { namespace Network {

class SelectObjectCollector
{
public:       
    class PIMPL;

    static RF_Mem::AutoPointer<SelectObjectCollector> Create(
        const Net::Socket& Handler);

    Net::Error Select(const Net::SelectMode::Type Mode,
        RadonFramework::Time::TimeSpan* const Timeout=0);

    ~SelectObjectCollector();
    void Add(const NetService::SocketHandler& Handler);
    void Remove(const RF_Type::Size Index);
                    
    RF_Type::Size Count()const;
    RF_Type::Bool IsSet(const RF_Type::Size Index)const;
protected:
    PIMPL* m_Data;
private:
    SelectObjectCollector();
    SelectObjectCollector(const SelectObjectCollector& Copy);
    SelectObjectCollector& operator=(const SelectObjectCollector& Other);
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYS_NET
#define RF_SHORTHAND_NAMESPACE_SYS_NET
namespace RF_SysNet = RadonFramework::System::Network;
#endif

#endif // RF_SYSTEM_NETWORK_SELECTOBJECTCOLLECTOR_HPP