#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/Process/ThreadInformation.hpp"

using namespace RadonFramework::Diagnostics::Profiling::Process;
using namespace RadonFramework;
using namespace RadonFramework::Memory;

ThreadInformation::ThreadInformation()
{

}

ThreadInformation::ThreadInformation(const ThreadInformation& Copy)
{
    m_Data=AutoPointer<ThreadData>(new ThreadData);
    RFMEM::Copy(m_Data.Get(),Copy.m_Data.Get(),sizeof(ThreadData));
}

ThreadInformation::ThreadInformation( Memory::AutoPointer<ThreadData> Data )
:m_Data(Data)
{
}

const ThreadData& ThreadInformation::Data()const
{
    return *m_Data.Get();
}

RadonFramework::Core::Types::String ThreadData::PriorityAsString()const
{
    Core::Types::String str;
    switch (Priority)
    {
        case Threading::ThreadPriority::Maximal:str="Maximal";break;
        case Threading::ThreadPriority::Minimal:str="Minimal";break;
        case Threading::ThreadPriority::Normal:str="Normal";break;
    }
    return str;
}

void ThreadInformation::Swap(ThreadInformation& Other)
{
    AutoPointer<ThreadData> tmp=AutoPointer<ThreadData>(m_Data.Release());
    m_Data=Other.m_Data;
    Other.m_Data=tmp;
}