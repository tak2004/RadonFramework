#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ModuleInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ThreadInformation.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Profiling::Process;

ProcessInformation::ProcessInformation()
{

}

ProcessInformation::ProcessInformation(const ProcessInformation& Copy)
{
    m_Data=AutoPointer<ProcessData>(new ProcessData);
    *m_Data=*Copy.m_Data;
    //m_Modules=Copy.m_Modules;
    //m_Threads=Copy.m_Threads;
}

ProcessInformation::ProcessInformation( AutoPointer<ProcessData> Data,
                                        AutoVector<ModuleInformation>& Modules,
                                        AutoVector<ThreadInformation>& Threads )
:m_Data(Data)
,m_Modules(Modules)
,m_Threads(Threads)
{
}

const ProcessData& ProcessInformation::Data()const
{
    return *m_Data.Get();
}

UInt32 ProcessInformation::ModuleCount()const
{
    return m_Modules.Size();
}

const ModuleInformation& ProcessInformation::Module(const UInt32 Index)const
{
    return *m_Modules[Index];
}

UInt32 ProcessInformation::ThreadCount()const
{
    return m_Threads.Size();
}

const ThreadInformation& ProcessInformation::Thread(const UInt32 Index)const
{
    return *m_Threads[Index];
}

void ProcessInformation::Swap(ProcessInformation& Other)
{
    AutoPointer<ProcessData> tmp(m_Data.Release());
    m_Data=Other.m_Data;
    Other.m_Data=tmp;
    m_Modules.Swap(Other.m_Modules);
    m_Threads.Swap(Other.m_Threads);
}
