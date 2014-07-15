#ifndef RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP
#define RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP

namespace RadonFramework
{
    namespace Threading
    {
        namespace Policies
        {
            class NoSynchronization:public Threading::ISynchronize
            {
                public:
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
        }        
    }
}

#endif // RF_THREADING_POLICIES_NOSYNCHRONIZATION_HPP