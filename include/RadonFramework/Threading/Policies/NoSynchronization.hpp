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

                    Core::Types::Bool TryLock(Core::Types::UInt64 TimeInMicroSec)
                    {
                        return false;
                    }

                    void Unlock()
                    {

                    }

                    void Wait()
                    {

                    }

                    Core::Types::Bool Wait(Core::Types::UInt64 TimeInMicroSec)
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