#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"
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

extern RF_Type::Int32 Compare_SSE4(const void* P1, const void* P2, RF_Type::Size Bytes);
extern RF_Type::Int32 Compare_Std(const void* P1, const void* P2, RF_Type::Size Bytes);
RF_Type::Int32 Compare_CPUDispatcher(const void* P1, const void* P2, RF_Type::Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE4_2])
        RF_SysMem::Compare = Compare_SSE4;
    else
        RF_SysMem::Compare = Compare_Std;
    return RF_SysMem::Compare(P1, P2, Bytes);
}

extern void Set_SSE2(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes);
extern void Set_Std(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes);
void Set_CPUDispatcher(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE2])
        RF_SysMem::Set = Set_SSE2;
    else
        RF_SysMem::Set = Set_Std;
    return RF_SysMem::Set(Pointer, Value, Bytes);
}

extern void Copy_SSE2(void* Destination, const void* Source, Size Bytes);
extern void Copy_Std(void* Destination, const void* Source, Size Bytes);
void Copy_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE2])
        RF_SysMem::Copy = Copy_SSE2;
    else
        RF_SysMem::Copy = Copy_Std;
    Copy(Destination, Source, Bytes);
}

extern void Move_Std(void* Destination, const void* Source, Size Bytes);
void Move_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    RF_SysMem::Move = Move_Std;
    Move(Destination, Source, Bytes);
}

extern void Swap_SSE2(void* P1, void* P2, Size Bytes);
extern void Swap_Std(void* P1, void* P2, Size Bytes);
void Swap_CPUDispatcher(void* P1, void* P2, Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if(features[RFHDW::ProcessorFeatures::SSE2])
        RF_SysMem::Swap = Swap_SSE2;
    else
        RF_SysMem::Swap = Swap_Std;
    Swap(P1, P2, Bytes);
}

CompareCallback RF_SysMem::Compare=Compare_CPUDispatcher;
SetCallback RF_SysMem::Set=Set_CPUDispatcher;
CopyCallback RF_SysMem::Copy=Copy_CPUDispatcher;
MoveCallback RF_SysMem::Move=Move_CPUDispatcher;
SwapCallback RF_SysMem::Swap=Swap_CPUDispatcher;

//
// On-Demand dispatched functions which are OS API dependent and have to be implemented on each platform
//

UInt32 GetPageSize_SystemAPIDispatcher()
{
    GetPageSize = 0;
    Dispatch();
    Assert(GetPageSize != GetPageSize_SystemAPIDispatcher &&
           GetPageSize != 0,
           "Funtion was called and couldn't be dispatched");
    return GetPageSize();
}

void EnableTerminationOnHeapCorruption_SystemAPIDispatcher()
{
    EnableTerminationOnHeapCorruption = 0;
    Dispatch();
    Assert(EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher &&
           EnableTerminationOnHeapCorruption != 0,
           "Funtion was called and couldn't be dispatched");
    EnableTerminationOnHeapCorruption();
}

void* Allocate_SystemAPIDispatcher(UInt32 Bytes)
{
    Allocate = 0;
    Dispatch();
    Assert(Allocate != Allocate_SystemAPIDispatcher &&
           Allocate != 0,
           "Funtion was called and couldn't be dispatched");
    return Allocate(Bytes);
}

void Free_SystemAPIDispatcher(void* FirstPage)
{
    Free = 0;
    Dispatch();
    Assert(Free != Free_SystemAPIDispatcher &&
           Free != 0,
           "Funtion was called and couldn't be dispatched");
    Free(FirstPage);
}

GetPageSizeCallback RF_SysMem::GetPageSize= GetPageSize_SystemAPIDispatcher;
EnableTerminationOnHeapCorruptionCallback RF_SysMem::EnableTerminationOnHeapCorruption=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
AllocateCallback RF_SysMem::Allocate=Allocate_SystemAPIDispatcher;
FreeCallback RF_SysMem::Free=Free_SystemAPIDispatcher;

Bool RF_SysMem::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && GetPageSize != GetPageSize_SystemAPIDispatcher && GetPageSize != 0;
    result=result && EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher 
           && EnableTerminationOnHeapCorruption != 0;
    result=result && Allocate != Allocate_SystemAPIDispatcher && Allocate != 0;
    result=result && Free != Free_SystemAPIDispatcher && Free != 0;
    return result;
}

void RF_SysMem::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (GetPageSize == GetPageSize_SystemAPIDispatcher || GetPageSize == 0) 
        Result.AddLast(RF_Type::String("GetPageSize", sizeof("GetPageSize")));
    if (EnableTerminationOnHeapCorruption == EnableTerminationOnHeapCorruption_SystemAPIDispatcher
        || EnableTerminationOnHeapCorruption == 0) 
        Result.AddLast(RF_Type::String("EnableTerminationOnHeapCorruption", sizeof("EnableTerminationOnHeapCorruption")));
    if (Allocate == Allocate_SystemAPIDispatcher || Allocate == 0)
        Result.AddLast(RF_Type::String("Allocate", sizeof("Allocate")));
    if (Free == Free_SystemAPIDispatcher || Free == 0)
        Result.AddLast(RF_Type::String("Free", sizeof("Free")));
}