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

extern RFTYPE::Int32 Compare_SSE4(const void* P1, const void* P2, RFTYPE::Size Bytes);
extern RFTYPE::Int32 Compare_Std(const void* P1, const void* P2, RFTYPE::Size Bytes);
RFTYPE::Int32 Compare_CPUDispatcher(const void* P1, const void* P2, RFTYPE::Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE4_2])
        RFMEM::Compare = Compare_SSE4;
    else
        RFMEM::Compare = Compare_Std;
    return RFMEM::Compare(P1, P2, Bytes);
}

extern void Set_SSE2(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes);
extern void Set_Std(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes);
void Set_CPUDispatcher(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE2])
        RFMEM::Set = Set_SSE2;
    else
        RFMEM::Set = Set_Std;
    return RFMEM::Set(Pointer, Value, Bytes);
}

extern void Copy_SSE2(void* Destination, const void* Source, Size Bytes);
extern void Copy_Std(void* Destination, const void* Source, Size Bytes);
void Copy_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    RFHDW::ProcessorFeatureMask features;
    RFHDW::GetLogicalProcessorFeatures(features);
    if (features[RFHDW::ProcessorFeatures::SSE2])
        RFMEM::Copy = Copy_SSE2;
    else
        RFMEM::Copy = Copy_Std;
    Copy(Destination, Source, Bytes);
}

extern void Move_Std(void* Destination, const void* Source, Size Bytes);
void Move_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
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

GetPageSizeCallback RFMEM::GetPageSize= GetPageSize_SystemAPIDispatcher;
EnableTerminationOnHeapCorruptionCallback RFMEM::EnableTerminationOnHeapCorruption=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
AllocateCallback RFMEM::Allocate=Allocate_SystemAPIDispatcher;
FreeCallback RFMEM::Free=Free_SystemAPIDispatcher;

Bool RFMEM::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && GetPageSize != GetPageSize_SystemAPIDispatcher && GetPageSize != 0;
    result=result && EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher 
           && EnableTerminationOnHeapCorruption != 0;
    result=result && Allocate != Allocate_SystemAPIDispatcher && Allocate != 0;
    result=result && Free != Free_SystemAPIDispatcher && Free != 0;
    return result;
}

void RFMEM::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (GetPageSize == GetPageSize_SystemAPIDispatcher || GetPageSize == 0) 
        Result.AddLast("GetPageSize");
    if (EnableTerminationOnHeapCorruption == EnableTerminationOnHeapCorruption_SystemAPIDispatcher
        || EnableTerminationOnHeapCorruption == 0) 
        Result.AddLast("EnableTerminationOnHeapCorruption");
    if (Allocate == Allocate_SystemAPIDispatcher || Allocate == 0)
        Result.AddLast("Allocate");
    if (Free == Free_SystemAPIDispatcher || Free == 0)
        Result.AddLast("Free");
}