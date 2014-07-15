#ifndef RF_THREADING_ISYNCHRONIZE_HPP
#define RF_THREADING_ISYNCHRONIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework { namespace Threading {

class ISynchronize
{
public:
    // lock based mechanic
    virtual void Lock()=0;
    virtual RF_Type::Bool TryLock(RF_Type::UInt64 TimeInMicroSec)=0;
    virtual void Unlock()=0;
    // signals
    virtual void Wait()=0;
    virtual RF_Type::Bool Wait(RF_Type::UInt64 TimeInMicroSec)=0;
    virtual void Pulse()=0;
    virtual void PulseAll()=0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif

#endif // RF_THREADING_ISYNCHRONIZE_HPP