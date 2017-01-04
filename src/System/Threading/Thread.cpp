#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/Collections/List.hpp"

namespace RadonFramework { namespace System { namespace Threading {

RF_Type::Bool IsAlive_SystemAPIDispatcher(void* Data)
{
    IsAlive = 0;
    Dispatch();
    Assert(IsAlive != IsAlive_SystemAPIDispatcher &&
        IsAlive != 0, "Funtion was called and couldn't be dispatched");
    return IsAlive(Data);
}

RF_Type::Bool IsRunning_SystemAPIDispatcher(void* Data)
{
    IsRunning = 0;
    Dispatch();
    Assert(IsRunning != IsRunning_SystemAPIDispatcher &&
        IsRunning != 0, "Funtion was called and couldn't be dispatched");
    return IsRunning(Data);
}

void* Create_SystemAPIDispatcher(RF_Thread::Thread& Instance, RF_Type::UInt64& PID)
{
    Create = 0;
    Dispatch();
    Assert(Create != Create_SystemAPIDispatcher &&
        Create != 0, "Funtion was called and couldn't be dispatched");
    return Create(Instance, PID);
}

void Destroy_SystemAPIDispatcher(void* Data)
{
    Destroy = 0;
    Dispatch();
    Assert(Destroy != Destroy_SystemAPIDispatcher &&
        Destroy != 0, "Funtion was called and couldn't be dispatched");
    Destroy(Data);
}

void Rename_SystemAPIDispatcher(void* Data, const RF_Type::String& Name)
{
    Rename = 0;
    Dispatch();
    Assert(Rename != Rename_SystemAPIDispatcher &&
        Rename != 0, "Funtion was called and couldn't be dispatched");
    Rename(Data, Name);
}

void Sleep_SystemAPIDispatcher(const RF_Time::TimeSpan& Delta)
{
    Sleep = 0;
    Dispatch();
    Assert(Sleep != Sleep_SystemAPIDispatcher &&
        Sleep != 0, "Funtion was called and couldn't be dispatched");
    Sleep(Delta);
}

RF_Type::UInt64 GetProcessId_SystemAPIDispatcher()
{
    GetProcessId = 0;
    Dispatch();
    Assert(GetProcessId != GetProcessId_SystemAPIDispatcher &&
        GetProcessId != 0, "Funtion was called and couldn't be dispatched");
    return GetProcessId();
}

void Wait_SystemAPIDispatcher(void* Data, const RF_Time::TimeSpan& Delta)
{
    Wait = 0;
    Dispatch();
    Assert(Wait != Wait_SystemAPIDispatcher &&
        Wait != 0, "Funtion was called and couldn't be dispatched");
    Wait(Data, Delta);
}

void Join_SystemAPIDispatcher(void* Data)
{
    Join = 0;
    Dispatch();
    Assert(Join != Join_SystemAPIDispatcher &&
        Join != 0, "Funtion was called and couldn't be dispatched");
    Join(Data);
}

void SetPriority_SystemAPIDispatcher(void* Data, RF_Thread::ThreadPriority::Type Value)
{
    SetPriority = 0;
    Dispatch();
    Assert(SetPriority != SetPriority_SystemAPIDispatcher &&
        SetPriority != 0, "Funtion was called and couldn't be dispatched");
    SetPriority(Data, Value);
}

RF_Thread::ThreadPriority::Type GetPriority_SystemAPIDispatcher(void* Data)
{
    GetPriority = 0;
    Dispatch();
    Assert(GetPriority != GetPriority_SystemAPIDispatcher &&
        GetPriority != 0, "Funtion was called and couldn't be dispatched");
    return GetPriority(Data);
}

RF_Type::Bool SetAffinityMask_SystemAPIDispatcher(void* Data,
    const RF_Collect::BitArray<>& NewMask)
{
    SetAffinityMask = 0;
    Dispatch();
    Assert(SetAffinityMask != SetAffinityMask_SystemAPIDispatcher &&
        SetAffinityMask != 0, "Funtion was called and couldn't be dispatched");
    return SetAffinityMask(Data, NewMask);
}

RF_Type::Bool GetAffinityMask_SystemAPIDispatcher(void* Data,
    RF_Collect::BitArray<>& Mask)
{
    GetAffinityMask = 0;
    Dispatch();
    Assert(GetAffinityMask != GetAffinityMask_SystemAPIDispatcher &&
        GetAffinityMask != 0, "Funtion was called and couldn't be dispatched");
    return GetAffinityMask(Data, Mask);
}

void PostConfigurationComplete_SystemAPIDispatcher(void* Data)
{
    PostConfigurationComplete = 0;
    Dispatch();
    Assert(PostConfigurationComplete != PostConfigurationComplete_SystemAPIDispatcher &&
        PostConfigurationComplete != 0, "Funtion was called and couldn't be dispatched");
    PostConfigurationComplete(Data);
}

void ShortestPause_SystemAPIDispatcher()
{
    ShortestPause = nullptr;
    Dispatch();
    Assert(ShortestPause != ShortestPause_SystemAPIDispatcher &&
           ShortestPause != 0, "Funtion was called and couldn't be dispatched");
    ShortestPause();
}

IsAliveCallback IsAlive = IsAlive_SystemAPIDispatcher;
IsRunningCallback IsRunning = IsRunning_SystemAPIDispatcher;
CreateCallback Create = Create_SystemAPIDispatcher;
DestroyCallback Destroy = Destroy_SystemAPIDispatcher;
RenameCallback Rename = Rename_SystemAPIDispatcher;
SleepCallback Sleep = Sleep_SystemAPIDispatcher;
GetProcessIdCallback GetProcessId = GetProcessId_SystemAPIDispatcher;
WaitCallback Wait = Wait_SystemAPIDispatcher;
JoinCallback Join = Join_SystemAPIDispatcher;
SetPriorityCallback SetPriority = SetPriority_SystemAPIDispatcher;
GetPriorityCallback GetPriority = GetPriority_SystemAPIDispatcher;
SetAffinityMaskCallback SetAffinityMask = SetAffinityMask_SystemAPIDispatcher;
GetAffinityMaskCallback GetAffinityMask = GetAffinityMask_SystemAPIDispatcher;
PostConfigurationCompleteCallback PostConfigurationComplete = PostConfigurationComplete_SystemAPIDispatcher;
ShortestPauseCallback ShortestPause = ShortestPause_SystemAPIDispatcher;

RF_Type::Bool IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && IsAlive != IsAlive_SystemAPIDispatcher && IsAlive != 0;
    result = result && IsRunning != IsRunning_SystemAPIDispatcher && IsRunning != 0;
    result = result && Create != Create_SystemAPIDispatcher && Create != 0;
    result = result && Rename != Rename_SystemAPIDispatcher && Rename != 0;
    result = result && Sleep != Sleep_SystemAPIDispatcher && Sleep != 0;
    result = result && GetProcessId != GetProcessId_SystemAPIDispatcher && GetProcessId != 0;
    result = result && Wait != Wait_SystemAPIDispatcher && Wait != 0;
    result = result && Join != Join_SystemAPIDispatcher && Join != 0;
    result = result && SetPriority != SetPriority_SystemAPIDispatcher && SetPriority != 0;
    result = result && GetPriority != GetPriority_SystemAPIDispatcher && GetPriority != 0;
    result = result && SetAffinityMask != SetAffinityMask_SystemAPIDispatcher && SetAffinityMask != 0;
    result = result && GetAffinityMask != GetAffinityMask_SystemAPIDispatcher && GetAffinityMask != 0;
    result = result && PostConfigurationComplete != PostConfigurationComplete_SystemAPIDispatcher && PostConfigurationComplete != 0;
    result = result && ShortestPause != ShortestPause_SystemAPIDispatcher && ShortestPause != nullptr;
    return result;
}

void GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result)
{
    if(IsAlive == IsAlive_SystemAPIDispatcher || IsAlive == 0)
        Result.AddLast("IsAlive"_rfs);
    if(IsRunning == IsRunning_SystemAPIDispatcher || IsRunning == 0)
        Result.AddLast("IsRunning"_rfs);
    if(Create == Create_SystemAPIDispatcher || Create == 0)
        Result.AddLast("Create"_rfs);
    if(Rename == Rename_SystemAPIDispatcher || Rename == 0)
        Result.AddLast("Rename"_rfs);
    if(Sleep == Sleep_SystemAPIDispatcher || Sleep == 0)
        Result.AddLast("Sleep"_rfs);
    if(GetProcessId == GetProcessId_SystemAPIDispatcher || GetProcessId == 0)
        Result.AddLast("GetProcessId"_rfs);
    if(Wait == Wait_SystemAPIDispatcher || Wait == 0)
        Result.AddLast("Wait"_rfs);
    if(Join == Join_SystemAPIDispatcher || Join == 0)
        Result.AddLast("Join"_rfs);
    if(SetPriority == SetPriority_SystemAPIDispatcher || SetPriority == 0)
        Result.AddLast("SetPriority"_rfs);
    if(GetPriority == GetPriority_SystemAPIDispatcher || GetPriority == 0)
        Result.AddLast("GetPriority"_rfs);
    if(SetAffinityMask == SetAffinityMask_SystemAPIDispatcher || SetAffinityMask == 0)
        Result.AddLast("SetAffinityMask"_rfs);
    if(GetAffinityMask == GetAffinityMask_SystemAPIDispatcher || GetAffinityMask == 0)
        Result.AddLast("GetAffinityMask"_rfs);
    if(PostConfigurationComplete == PostConfigurationComplete_SystemAPIDispatcher || PostConfigurationComplete == 0)
        Result.AddLast("PostConfigurationComplete"_rfs);
    if(ShortestPause == ShortestPause_SystemAPIDispatcher || ShortestPause == nullptr)
        Result.AddLast("ShortestPause"_rfs);
}

} } }