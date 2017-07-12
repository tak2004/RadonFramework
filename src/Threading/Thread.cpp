#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/Threading/Scopelock.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"

namespace RadonFramework::Threading {

Thread::Thread()
:m_Priority(ThreadPriority::Normal)
,m_Pid(-1)
,m_ImplData(0)
{
    m_AffinityMask.Resize(RF_SysHardware::GetAvailableLogicalProcessorCount());
    m_AffinityMask.Set();
}

Thread::~Thread()
{
    if (m_ImplData)
        RF_SysThread::Destroy(m_ImplData);
}

void Thread::Run()
{
}

void Thread::Start()
{
    m_ImplData =RF_SysThread::Create(*this, m_Pid);
    RF_SysThread::SetPriority(m_ImplData, m_Priority);
    RF_SysThread::SetAffinityMask(m_ImplData, m_AffinityMask);
    RF_SysThread::PostConfigurationComplete(m_ImplData);
}

void Thread::Exit()
{
    RF_SysThread::Stop(m_ImplData);
    RF_SysThread::Join(m_ImplData);
}

void Thread::Interrupt()
{

}

ThreadPriority::Type Thread::Priority()
{
    return m_Priority;
}

void Thread::Priority(ThreadPriority::Type Value)
{
    if (Value!=m_Priority)
    {
        m_Priority=Value;
        RF_SysThread::SetPriority(m_ImplData, m_Priority);
    }
}

void Thread::Join()
{
    RF_SysThread::Join(m_ImplData);
}

void Thread::Join(const RF_Time::TimeSpan& Delta)
{
    RF_SysThread::Wait(m_ImplData, Delta);
}

void Thread::Sleep(const RF_Time::TimeSpan& Delta)
{
    RF_SysThread::Sleep(Delta);
}

RF_Type::Bool Thread::IsAlive()
{
    return RF_SysThread::IsAlive(m_ImplData);
}

RF_Type::Bool Thread::Working()
{
    return m_ImplData != 0;
}

void Thread::Finished()
{

}

const RF_Type::String& Thread::Name()const
{
    return m_Name;
}

void Thread::Name(const class RF_Type::String& NewName)
{
    m_Name=NewName;
    return RF_SysThread::Rename(m_ImplData, NewName);
}

RF_Type::UInt64 Thread::Pid()const
{
    return m_Pid;
}

void* Thread::MemAlloc(const RF_Type::UInt64 Bytes)
{
    RF_Thread::Scopelock lock(m_ThreadBarrier);
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m(static_cast<RF_Type::UInt32>(Bytes));
    RF_Type::UInt8* p=m.Get();
    m_ThreadAllocatedMemory.PushBack(m);
    return p;
}

void Thread::FreeMem(const void* Ptr)
{
    RF_Thread::Scopelock lock(m_ThreadBarrier);
    Collections::AutoVector<RF_Type::UInt8>::Iterator it=m_ThreadAllocatedMemory.Begin();
    for (;it!=m_ThreadAllocatedMemory.End();++it)
        if ((*it)==Ptr)
        {
            m_ThreadAllocatedMemory.Erase(it);
            break;
        }
}

RF_Type::Bool Thread::MemAccess(const void* Ptr)
{
    RF_Thread::Scopelock lock(m_ThreadBarrier);
    Collections::AutoVector<RF_Type::UInt8>::Iterator it=m_ThreadAllocatedMemory.Begin();
    for (;it!=m_ThreadAllocatedMemory.End();++it)
        if ((*it)==Ptr)
            return true;
    return false;
}

RF_Type::UInt64 Thread::CurrentPid()
{
    return RF_SysThread::GetProcessId();
}

RF_Type::Bool Thread::GetAffinityMask(RF_Collect::BitArray<>& Mask)const
{
    return RF_SysThread::GetAffinityMask(m_ImplData, Mask);
}

RF_Type::Bool Thread::SetAffinityMask(const RF_Collect::BitArray<>& NewValue)
{
    RF_Type::Bool result = true;
    if(NewValue != m_AffinityMask)
    {
        m_AffinityMask = NewValue;
        result = RF_SysThread::SetAffinityMask(m_ImplData, m_AffinityMask);
    }
    return result;
}

RF_Type::Bool Thread::ShouldRunning()
{
    return RF_SysThread::IsRunning(m_ImplData);
}

}