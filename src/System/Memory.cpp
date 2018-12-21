#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::Memory;

//
// On-Demand dispatched functions which are CPU dependent and have always a fallback
//
#if RF_BUILD_INTRINSIC_SSE41 
extern RF_Type::Int32 Compare_SSE4(const void* P1, const void* P2, RF_Type::Size Bytes);
#endif
extern RF_Type::Int32 Compare_Std(const void* P1, const void* P2, RF_Type::Size Bytes);
RF_Type::Int32 Compare_CPUDispatcher(const void* P1, const void* P2, RF_Type::Size Bytes)
{
    RF_SysHardware::ProcessorFeatureMask features;
    RF_SysHardware::GetLogicalProcessorFeatures(features);
#if RF_BUILD_INTRINSIC_SSE41 
    if(features[RF_SysHardware::ProcessorFeatures::SSE4_2])
        RF_SysMem::Compare = Compare_SSE4;
    else
#endif
        RF_SysMem::Compare = Compare_Std;
    return RF_SysMem::Compare(P1, P2, Bytes);
}

#if RF_BUILD_INTRINSIC_SSE2
extern void Set_SSE2(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes);
#endif
extern void Set_Std(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes);
void Set_CPUDispatcher(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes)
{
    RF_SysHardware::ProcessorFeatureMask features;
    RF_SysHardware::GetLogicalProcessorFeatures(features);
#if RF_BUILD_INTRINSIC_SSE2
    if(features[RF_SysHardware::ProcessorFeatures::SSE2])
        RF_SysMem::Set = Set_SSE2;
    else
#endif
        RF_SysMem::Set = Set_Std;
    return RF_SysMem::Set(Pointer, Value, Bytes);
}

#if RF_BUILD_INTRINSIC_SSE2
extern void Copy_SSE2(void* Destination, const void* Source, Size Bytes);
#endif
extern void Copy_Std(void* Destination, const void* Source, Size Bytes);
void Copy_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    RF_SysHardware::ProcessorFeatureMask features;
    RF_SysHardware::GetLogicalProcessorFeatures(features);
#if RF_BUILD_INTRINSIC_SSE2
    if(features[RF_SysHardware::ProcessorFeatures::SSE2])
        RF_SysMem::Copy = Copy_SSE2;
    else
#endif
        RF_SysMem::Copy = Copy_Std;
    Copy(Destination, Source, Bytes);
}

extern void Move_Std(void* Destination, const void* Source, Size Bytes);
void Move_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    RF_SysMem::Move = Move_Std;
    Move(Destination, Source, Bytes);
}

#if RF_BUILD_INTRINSIC_SSE2
extern void Swap_SSE2(void* P1, void* P2, Size Bytes);
#endif
extern void Swap_Std(void* P1, void* P2, Size Bytes);
void Swap_CPUDispatcher(void* P1, void* P2, Size Bytes)
{
    RF_SysHardware::ProcessorFeatureMask features;
#if RF_BUILD_INTRINSIC_SSE2
    RF_SysHardware::GetLogicalProcessorFeatures(features);
    if(features[RF_SysHardware::ProcessorFeatures::SSE2])
        RF_SysMem::Swap = Swap_SSE2;
    else
#endif
        RF_SysMem::Swap = Swap_Std;
    Swap(P1, P2, Bytes);
}

extern RF_Type::Size Fill_Std(void* Pointer, const void* PatternData,
                              RF_Type::Size PatternSize, RF_Type::Size BufferSize);
// Theres no SIMD implementation yet.
RF_Type::Size Fill_CPUDispatcher(void* Pointer, const void* PatternData,
                                 RF_Type::Size PatternSize, RF_Type::Size BufferSize)
{
    RF_SysMem::Fill = Fill_Std;
    return Fill(Pointer, PatternData, PatternSize, BufferSize);
}

CompareCallback RF_SysMem::Compare = Compare_CPUDispatcher;
/// Set the specified memory block byte-wise.
SetCallback RF_SysMem::Set = Set_CPUDispatcher;
CopyCallback RF_SysMem::Copy = Copy_CPUDispatcher;
MoveCallback RF_SysMem::Move = Move_CPUDispatcher;
SwapCallback RF_SysMem::Swap = Swap_CPUDispatcher;
/// Fill the specified memory block with the given pattern.
FillCallback RF_SysMem::Fill = Fill_CPUDispatcher;

//
// On-Demand dispatched functions which are OS API dependent and have to be implemented on each platform
//

UInt32 GetPageSize_SystemAPIDispatcher()
{
    GetPageSize = nullptr;
    Dispatch();
    RF_ASSERT(GetPageSize != GetPageSize_SystemAPIDispatcher &&
           GetPageSize != 0,
           "Funtion was called and couldn't be dispatched");
    return GetPageSize();
}

UInt32 GetBlockSize_SystemAPIDispatcher()
{
    GetBlockSize = nullptr;
    Dispatch();
    RF_ASSERT(GetBlockSize != GetBlockSize_SystemAPIDispatcher &&
           GetBlockSize != 0,
           "Funtion was called and couldn't be dispatched");
    return GetBlockSize();
}

void EnableTerminationOnHeapCorruption_SystemAPIDispatcher()
{
    EnableTerminationOnHeapCorruption = nullptr;
    Dispatch();
    RF_ASSERT(EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher &&
           EnableTerminationOnHeapCorruption != 0,
           "Funtion was called and couldn't be dispatched");
    EnableTerminationOnHeapCorruption();
}

Size PageAllocationSize_SystemAPIDispatcher(const void* FirstPage)
{
    PageAllocationSize = nullptr;
    Dispatch();
    RF_ASSERT(PageAllocationSize != PageAllocationSize_SystemAPIDispatcher &&
           PageAllocationSize != 0,
           "Funtion was called and couldn't be dispatched");
    return PageAllocationSize(FirstPage);
}

void* PageAllocate_SystemAPIDispatcher(Size& Bytes)
{
    PageAllocate = nullptr;
    Dispatch();
    RF_ASSERT(PageAllocate != PageAllocate_SystemAPIDispatcher &&
           PageAllocate != 0,
           "Funtion was called and couldn't be dispatched");
    return PageAllocate(Bytes);
}

void PageFree_SystemAPIDispatcher(void* FirstPage)
{
    PageFree = nullptr;
    Dispatch();
    RF_ASSERT(PageFree != PageFree_SystemAPIDispatcher&&
           PageFree != 0,
           "Funtion was called and couldn't be dispatched");
    PageFree(FirstPage);
}

void* Allocate_SystemAPIDispatcher(const Size Bytes, const Size Alignment)
{
    Allocate = nullptr;
    Dispatch();
    RF_ASSERT(Allocate != Allocate_SystemAPIDispatcher &&
           Allocate != 0,
           "Funtion was called and couldn't be dispatched");
    return Allocate(Bytes, Alignment);
}

void Free_SystemAPIDispatcher(void* FirstPage)
{
    Free = nullptr;
    Dispatch();
    RF_ASSERT(Free != Free_SystemAPIDispatcher &&
           Free != 0,
           "Funtion was called and couldn't be dispatched");
    Free(FirstPage);
}

void* MapMemory_SystemAPIDispatcher(void* Memory, RF_Type::Size Bytes)
{
    MapMemory = nullptr;
    Dispatch();
    RF_ASSERT(MapMemory != MapMemory_SystemAPIDispatcher &&
           MapMemory != 0,
           "Funtion was called and couldn't be dispatched");
    return MapMemory(Memory, Bytes);
}

void UnmapMemory_SystemAPIDispatcher(void* MemoryMapHandle)
{
    UnmapMemory = nullptr;
    Dispatch();
    RF_ASSERT(UnmapMemory != UnmapMemory_SystemAPIDispatcher &&
           UnmapMemory != 0,
           "Funtion was called and couldn't be dispatched");
    UnmapMemory(MemoryMapHandle);
}

void* MapView_SystemAPIDispatcher(void* MemoryMapHandle, const RF_Type::Size Bytes, void* View)
{
    MapView = nullptr;
    Dispatch();
    RF_ASSERT(MapView != MapView_SystemAPIDispatcher &&
           MapView != 0,
           "Funtion was called and couldn't be dispatched");
    return MapView(MemoryMapHandle, Bytes, View);
}

GetPageSizeCallback RF_SysMem::GetPageSize = GetPageSize_SystemAPIDispatcher;
GetBlockSizeCallback RF_SysMem::GetBlockSize = GetBlockSize_SystemAPIDispatcher;
EnableTerminationOnHeapCorruptionCallback RF_SysMem::EnableTerminationOnHeapCorruption = EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
PageAllocationSizeCallback RF_SysMem::PageAllocationSize = PageAllocationSize_SystemAPIDispatcher;
PageAllocateCallback RF_SysMem::PageAllocate = PageAllocate_SystemAPIDispatcher;
PageFreeCallback RF_SysMem::PageFree = PageFree_SystemAPIDispatcher;
AllocateCallback RF_SysMem::Allocate = Allocate_SystemAPIDispatcher;
FreeCallback RF_SysMem::Free = Free_SystemAPIDispatcher;
MapMemoryCallback RF_SysMem::MapMemory = MapMemory_SystemAPIDispatcher;
UnmapMemoryCallback RF_SysMem::UnmapMemory = UnmapMemory_SystemAPIDispatcher;
MapViewCallback RF_SysMem::MapView = MapView_SystemAPIDispatcher;

Bool RF_SysMem::IsSuccessfullyDispatched()
{
    Bool result = true;
    result = result && GetPageSize != GetPageSize_SystemAPIDispatcher && GetPageSize != 0;
    result = result && GetBlockSize != GetBlockSize_SystemAPIDispatcher && GetBlockSize != 0;
    result = result && EnableTerminationOnHeapCorruption != EnableTerminationOnHeapCorruption_SystemAPIDispatcher
        && EnableTerminationOnHeapCorruption != 0;
    result = result && PageAllocationSize != PageAllocationSize_SystemAPIDispatcher && PageAllocationSize != 0;
    result = result && PageAllocate != PageAllocate_SystemAPIDispatcher && PageAllocate != 0;
    result = result && PageFree != PageFree_SystemAPIDispatcher && PageFree != 0;
    result = result && Allocate != Allocate_SystemAPIDispatcher && Allocate != 0;
    result = result && Free != Free_SystemAPIDispatcher && Free != 0;
    result = result && MapMemory != MapMemory_SystemAPIDispatcher && MapMemory != 0;
    result = result && UnmapMemory != UnmapMemory_SystemAPIDispatcher && UnmapMemory != 0;
    result = result && MapView != MapView_SystemAPIDispatcher && MapView != 0;
    return result;
}

void RF_SysMem::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if(GetPageSize == GetPageSize_SystemAPIDispatcher || GetPageSize == 0)
        Result.AddLast("GetPageSize"_rfs);
    if(GetBlockSize == GetBlockSize_SystemAPIDispatcher || GetBlockSize == 0)
        Result.AddLast("GetBlockSize"_rfs);
    if(EnableTerminationOnHeapCorruption == EnableTerminationOnHeapCorruption_SystemAPIDispatcher
       || EnableTerminationOnHeapCorruption == 0)
       Result.AddLast("EnableTerminationOnHeapCorruption"_rfs);
    if(PageAllocationSize == PageAllocationSize_SystemAPIDispatcher || PageAllocationSize == 0)
        Result.AddLast("PageAllocationSize"_rfs);
    if(PageAllocate == PageAllocate_SystemAPIDispatcher || PageAllocate == 0)
        Result.AddLast("PageAllocate"_rfs);
    if(PageFree == PageFree_SystemAPIDispatcher || PageFree == 0)
        Result.AddLast("PageFree"_rfs);
    if(Allocate == Allocate_SystemAPIDispatcher || Allocate == 0)
        Result.AddLast("Allocate"_rfs);
    if(Free == Free_SystemAPIDispatcher || Free == 0)
        Result.AddLast("Free"_rfs);
    if (MapMemory == MapMemory_SystemAPIDispatcher || MapMemory == 0)
        Result.AddLast("MapMemory"_rfs);
    if (UnmapMemory == UnmapMemory_SystemAPIDispatcher || UnmapMemory == 0)
        Result.AddLast("UnmapMemory"_rfs);
    if(MapView == MapView_SystemAPIDispatcher || MapView == 0)
        Result.AddLast("MapView"_rfs);
}