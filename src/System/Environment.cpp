#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"

using namespace RadonFramework::Collections;
using namespace RadonFramework::System::Environment;

MemoryArchitectureOfOSCallback RadonFramework::System::Environment::MemoryArchitectureOfOS=0;
Is32BitEmulationCallback RadonFramework::System::Environment::Is32BitEmulation=0;
OSVersionCallback RadonFramework::System::Environment::OSVersion=0;
GetVariableCallback RadonFramework::System::Environment::GetVariable=0;
PlatformCallback RadonFramework::System::Environment::Platform=0;
OSFamilyCallback RadonFramework::System::Environment::OSFamily=0;

RFTYPE::Bool RadonFramework::System::Environment::IsSuccessfullyDispatched()
{
    RFTYPE::Bool result=true;
    result=result && MemoryArchitectureOfOS!=0;
    result=result && Is32BitEmulation!=0;
    result=result && OSVersion!=0;
    result=result && GetVariable!=0;
    result=result && Platform!=0;
    result=result && OSFamily!=0;
    return result;
}

void RadonFramework::System::Environment::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (MemoryArchitectureOfOS==0) 
        Result.AddLast("MemoryArchitectureOfOS");
    if (Is32BitEmulation==0) 
        Result.AddLast("Is32BitEmulation");
    if (OSVersion==0) 
        Result.AddLast("OSVersion");
    if (GetVariable==0) 
        Result.AddLast("GetVariable");
    if (Platform==0) 
        Result.AddLast("Platform");
    if (OSFamily==0) 
        Result.AddLast("OSFamily");
}
