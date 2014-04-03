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

                    RFTYPE::Bool TryLock(RFTYPE::UInt64 TimeInMicroSec)
                    {
                        return false;
                    }

                    void Unlock()
                    {

                    }

                    void Wait()
                    {

                    }

                    RFTYPE::Bool Wait(RFTYPE::UInt64 TimeInMicroSec)
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