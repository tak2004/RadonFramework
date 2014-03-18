#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/Processor.hpp"
#include "RadonFramework/Diagnostics/ProcessorData.hpp"
#include "RadonFramework/Collections/List.hpp"
#include <smmintrin.h>
#include <nmmintrin.h>
//#include <intrin.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::Memory;

//
// On-Demand dispatched functions which are CPU dependent and have always a fallback
//

extern RFTYPE::Int32 Compare_SSE4(const void* P1, const void* P2, RFTYPE::Size Bytes);
extern RFTYPE::Int32 Compare_Std(const void* P1, const void* P2, RFTYPE::Size Bytes);
RFTYPE::Int32 Compare_CPUDispatcher(const void* P1, const void* P2, RFTYPE::Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE4_2))
        RFMEM::Compare = Compare_SSE4;
    else
        RFMEM::Compare = Compare_Std;
    return RFMEM::Compare(P1, P2, Bytes);
}

extern void Set_SSE2(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes);
extern void Set_Std(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes);
void Set_CPUDispatcher(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE2))
        RFMEM::Set = Set_SSE2;
    else
        RFMEM::Set = Set_Std;
    return RFMEM::Set(Pointer, Value, Bytes);
}

extern void Copy_SSE2(void* Destination, const void* Source, Size Bytes);
extern void Copy_Std(void* Destination, const void* Source, Size Bytes);
void Copy_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE2))
        RFMEM::Copy = Copy_SSE2;
    else
        RFMEM::Copy = Copy_Std;
    Copy(Destination, Source, Bytes);
}

extern void Move_Std(void* Destination, const void* Source, Size Bytes);
void Move_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    RFMEM::Move = Move_Std;
    Move(Destination, Source, Bytes);
}

CompareCallback RFMEM::Compare=Compare_CPUDispatcher;
SetCallback RFMEM::Set=Set_CPUDispatcher;
CopyCallback RFMEM::Copy=Copy_CPUDispatcher;
MoveCallback RFMEM::Move=Move_CPUDispatcher;

//
// On-Demand dispatched functions which are OS API dependent and have to be implemented on each platform
//

UInt32 GetPageSize_SystemAPIDispatcher()
{
    Dispatch();
    Assert(GetPageSize != GetPageSize_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetPageSize();
}

void EnableTerminationOnHeapCorruption_SystemAPIDispatcher()
{
    Dispatch();
    Assert(EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    EnableTerminationOnHeapCorruption();
}

void* Allocate_SystemAPIDispatcher(UInt32 Bytes)
{
    Dispatch();
    Assert(Allocate != Allocate_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Allocate(Bytes);
}

void Free_SystemAPIDispatcher(void* FirstPage)
{
    Dispatch();
    Assert(Free != Free_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    Free(FirstPage);
}

GetPageSizeCallback RFMEM::GetPageSize= GetPageSize_SystemAPIDispatcher;
EnableTerminationOnHeapCorruptionCallback RFMEM::EnableTerminationOnHeapCorruption=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
AllocateCallback RFMEM::Allocate=Allocate_SystemAPIDispatcher;
FreeCallback RFMEM::Free=Free_SystemAPIDispatcher;

Bool RFMEM::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && GetPageSize!=GetPageSize_SystemAPIDispatcher;
    result=result && EnableTerminationOnHeapCorruption!=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
    result=result && Allocate!=Allocate_SystemAPIDispatcher;
    result=result && Free!=Free_SystemAPIDispatcher;
    return result;
}

void RFMEM::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (GetPageSize == GetPageSize_SystemAPIDispatcher) 
        Result.AddLast("GetPageSize");
    if (EnableTerminationOnHeapCorruption == EnableTerminationOnHeapCorruption_SystemAPIDispatcher) 
        Result.AddLast("EnableTerminationOnHeapCorruption");
    if (Allocate == Allocate_SystemAPIDispatcher)
        Result.AddLast("Allocate");
    if (Free == Free_SystemAPIDispatcher)
        Result.AddLast("Free");
}