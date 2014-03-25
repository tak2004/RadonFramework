#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Threading/Scopelock.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Time/DateTime.hpp>
#include "RadonFramework/Threading/ThreadPool.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Time;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics;

Bool Log::IsInfoEnabled=true;
Bool Log::IsErrorEnabled=true;
Bool Log::IsFatalErrorEnabled=true;
Bool Log::IsDebugEnabled=true;
Array<AutoPointer<Appender> > Log::m_Appender;

void Log::WriteInfo(AutoPointer<String> Text)
{                    
    if (m_Appender.Count())
    {
        RadonFramework::Singleton<ThreadPool>::GetInstance().QueueUserWorkItem(PoolLogInfoTask,Text.Release(),TaskStrategy::SerialPerThread);
    }
}

void Log::WriteError(AutoPointer<String> Text)
{                    
    if (m_Appender.Count())
    {
        RadonFramework::Singleton<ThreadPool>::GetInstance().QueueUserWorkItem(PoolLogErrorTask,Text.Release(),TaskStrategy::SerialPerThread);
    }
}

void Log::WriteFatalError(AutoPointer<String> Text)
{                    
    if (m_Appender.Count())
    {
        RadonFramework::Singleton<ThreadPool>::GetInstance().QueueUserWorkItem(PoolLogFatalErrorTask,Text.Release(),TaskStrategy::SerialPerThread);
    }
}

void Log::WriteDebug(AutoPointer<String> Text)
{                    
    if (m_Appender.Count())
    {
        RadonFramework::Singleton<ThreadPool>::GetInstance().QueueUserWorkItem(PoolLogDebugTask,Text.Release(),TaskStrategy::SerialPerThread);
    }
}

void Log::AddAppender(AutoPointer<Appender> Value)
{
    m_Appender.Resize(m_Appender.Count()+1);
    m_Appender(m_Appender.Count()-1)=Value;
}

void Log::AddAppenders(AutoPointer<Array<AutoPointer<Appender> > > Values)
{
    Size i=m_Appender.Count();
    m_Appender.Resize(m_Appender.Count()+Values->Count());
    Size len=m_Appender.Count();
    for (Size j=0; i<len; ++i, ++j)    
        m_Appender(i)=(*Values)(j);
}

void Log::ReplaceAppenders(AutoPointer<Array<AutoPointer<Appender> > > Values)
{
    m_Appender.Swap(*Values);
}

void Log::RemoveAppender(const Appender& Value)
{
    Int32 index=0;
    ArrayEnumerator<AutoPointer<Appender> > it=m_Appender.GetEnumerator();
    while(it.MoveNext())
    {
        if (it.Current()->Get()==&Value)
            break;
        ++index;
    }

    if (index>=0)
    {
        Array<AutoPointer<Appender> > tmp(m_Appender.Count()-1);
        if (index==0)
            m_Appender.Copy(1,tmp,0,tmp.Count()-1);
        else
            if (index==tmp.Count()-1)
                m_Appender.Copy(0,tmp,0,tmp.Count()-1);
            else
            {
                m_Appender.Copy(0,tmp,0,index);
                m_Appender.Copy(index,tmp,index+1,m_Appender.Count()-index);
            }
        m_Appender.Swap(tmp);
    }
}

void Log::PoolLogInfoTask(void* Data)
{
    Size len=m_Appender.Count();
    String* str=reinterpret_cast<String*>(Data);
    for (Size i=0; i<len; ++i)
        m_Appender(i)->WriteInfo(*str);
}

void Log::PoolLogErrorTask(void* Data)
{
    Size len=m_Appender.Count();
    String* str=reinterpret_cast<String*>(Data);
    for (Size i=0; i<len; ++i)
        m_Appender(i)->WriteError(*str);
}

void Log::PoolLogFatalErrorTask(void* Data)
{
    Size len=m_Appender.Count();
    String* str=reinterpret_cast<String*>(Data);
    for (Size i=0; i<len; ++i)
        m_Appender(i)->WriteFatalError(*str);
}

void Log::PoolLogDebugTask(void* Data)
{
    Size len=m_Appender.Count();
    String* str=reinterpret_cast<String*>(Data);
    for (Size i=0; i<len; ++i)
        m_Appender(i)->WriteDebug(*str);
}