#ifndef RF_SYSTEM_THREADING_SEMAPHORE_HPP
#define RF_SYSTEM_THREADING_SEMAPHORE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework
{
    namespace Time
    {
        class TimeSpan;
    }

    namespace System
    {
	    namespace Threading
	    {
		    class Semaphore
		    {
		        public:
			        Semaphore(Core::Types::UInt32 value=0);
			        ~Semaphore();
			        void Release();
			        void Wait();
			        Core::Types::Bool TimedWait(const Time::TimeSpan& timeout);
                protected:
                    void* m_ImplData;
		    };
	    }
    }
}

#endif // RF_SYSTEM_THREADING_SEMAPHORE_HPP