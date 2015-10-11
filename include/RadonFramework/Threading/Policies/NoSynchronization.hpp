#ifndef RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP
#define RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP

namespace RadonFramework { namespace Threading { namespace Policies {
    
class NoSynchronization:public Threading::ISynchronize
{
public:
    virtual ~NoSynchronization()
    {
    }
    
    void Lock()
    {

    }

    RF_Type::Bool TryLock(RF_Type::UInt64 TimeInMicroSec)
    {
        return false;
    }

    void Unlock()
    {

    }

    void Wait()
    {

    }

    RF_Type::Bool Wait(RF_Type::UInt64 TimeInMicroSec)
    {
        return false;
    }

    void Pulse()
    {

    }

    void PulseAll()
    {

    }
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_THREADPOL
#define RF_SHORTHAND_NAMESPACE_THREADPOL
namespace RF_ThreadPol = RadonFramework::Threading::Policies;
#endif

#endif // RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP