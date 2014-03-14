#ifndef RF_SYSTEM_THREADING_CONDITION_HPP
#define RF_SYSTEM_THREADING_CONDITION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
	namespace Time{
		class TimeSpan;
	}

    namespace System
    {
	    namespace Threading
	    {
	        class Mutex;

	        class Condition
	        {
                public:
                    Condition();
                    ~Condition();
                    void Wait(Mutex& Lock);
                    void TimedWait(Mutex& Lock, const RadonFramework::Time::TimeSpan& Delta);
                    void Notify();
                    void NotifyAll();
                protected:
                    void* m_ImplData;
	        };
	    }
    }
}

#endif // RF_SYSTEM_THREADING_CONDITION_HPP
