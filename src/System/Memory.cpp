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

RFTYPE::Int32 Compare_Std(const void* P1, const void* P2, RFTYPE::Size Bytes)
{
    const RFTYPE::UInt8 *p1 = reinterpret_cast<const RFTYPE::UInt8*>(P1),
                      *p2 = reinterpret_cast<const RFTYPE::UInt8*>(P2);
    while(Bytes--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            *p1++,*p2++;
    return 0;
}

RFTYPE::Int32 Compare_SSE4(const void* P1, const void* P2, RFTYPE::Size Bytes)
{
    const __m128i* mp1 = reinterpret_cast<const __m128i*>(P1);
    const __m128i* mp2 = reinterpret_cast<const __m128i*>(P2);
    const RFTYPE::UInt8 *p1 = reinterpret_cast<const RFTYPE::UInt8*>(P1),
                      *p2 = reinterpret_cast<const RFTYPE::UInt8*>(P2);
    __m128i a, b, cmp;
    const int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY;
    int result = 16;

    // not aligned pointer compare bytewise
    while( Bytes && (reinterpret_cast<RFTYPE::MemoryRange>(p1) & 0xf || reinterpret_cast<RFTYPE::MemoryRange>(p2) & 0xf))
    {
        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        else
        {
            ++p1;
            ++p2;
            --Bytes;
        }
    }

    // compare 16 byte wise
    mp1 = reinterpret_cast<const __m128i*>(p1);
    mp2 = reinterpret_cast<const __m128i*>(p2);
    while ( Bytes >= 16 && result == 16)
    {
        a = _mm_load_si128(mp1);
        b = _mm_load_si128(mp2);
        result = _mm_cmpestri(a, 16, b, 16, mode);
        Bytes -= sizeof(__m128i);
        ++mp1;
        ++mp2;
    }

    if (result < 16 && Bytes >= 16)
    {
        a = _mm_sub_epi8(a, b);
        return *(reinterpret_cast<RFTYPE::UInt8*>(&a) + result) && 0xFF;
    }

    // compare trailing bytes
    p1 = reinterpret_cast<const RFTYPE::UInt8*>(mp1);
    p2 = reinterpret_cast<const RFTYPE::UInt8*>(mp2);
    while(Bytes--)
    {
        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        else
        {
            ++p1;
            ++p2;
        }
    }

    return 0;
}

RFTYPE::Int32 Compare_CPUDispatcher(const void* P1, const void* P2, RFTYPE::Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE4_2))
        RFMEM::Compare = Compare_SSE4;
    else
        RFMEM::Compare = Compare_Std;
    return RFMEM::Compare(P1, P2, Bytes);
}

void Set_Std(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes)
{
    RFTYPE::UInt8* p = reinterpret_cast<RFTYPE::UInt8*>(Pointer);
    RFTYPE::Size* mp;
    RFTYPE::Size size = Value;
    // fill up largest variable
    for(RFTYPE::Size i = 0; i < sizeof(RFTYPE::Size); ++i)
        size = size | (size << 8);

    // not aligned pointer fill bytewise
    while( Bytes && reinterpret_cast<RFTYPE::MemoryRange>(p) & (sizeof(RFTYPE::Size)-1))
    {
        *(p++) = static_cast<RFTYPE::UInt8>(Value);
        --Bytes;
    }

    mp = reinterpret_cast<RFTYPE::Size*>(p);
    // aligned and more bytes then largest variable are left
    while((Bytes / sizeof(RFTYPE::Size)) > 0)
    {
        *(mp++) = size;
        Bytes -= sizeof(RFTYPE::Size);
    }

    p = reinterpret_cast<RFTYPE::UInt8*>(mp);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(p++) = static_cast<RFTYPE::UInt8>(Value);
    }
}

void Set_SSE2(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes)
{
    RFTYPE::UInt8* p = reinterpret_cast<RFTYPE::UInt8*>(Pointer);
    RFTYPE::Size* mp;
    RFTYPE::Size size = Value;
    // not aligned pointer fill bytewise
    while( Bytes && reinterpret_cast<RFTYPE::MemoryRange>(p) & 0xf)
    {
        *(p++) = static_cast<RFTYPE::UInt8>(Value);
        --Bytes;
    }

    // aligned pointer fill 16byte pieces
    __m128i v;
    __m128i* m = reinterpret_cast<__m128i*>(p);
    RFTYPE::UInt32 ui = static_cast<RFTYPE::UInt32>(Value);
    ui = ui << 8 | ui;
    ui = ui << 16 | ui;
    v = _mm_set_epi32(ui,ui,ui,ui);
    while (Bytes >= 16)
    {
        _mm_store_si128(m, v);
        ++m;
        Bytes -= 16;
    }

    p = reinterpret_cast<RFTYPE::UInt8*>(m);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(p++) = static_cast<RFTYPE::UInt8>(Value);
    }
}

void Set_CPUDispatcher(void* Pointer, RFTYPE::Int32 Value, RFTYPE::Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE2))
        RFMEM::Set = Set_SSE2;
    else
        RFMEM::Set = Set_Std;
    return RFMEM::Set(Pointer, Value, Bytes);
}

void Copy_Std(void* Destination, const void* Source, Size Bytes)
{
    RFTYPE::UInt8* dst = reinterpret_cast<RFTYPE::UInt8*>(Destination);
    const RFTYPE::UInt8* src = reinterpret_cast<const RFTYPE::UInt8*>(Source);
    RFTYPE::Size* sDst;
    const RFTYPE::Size* sSrc;

    // not aligned pointer fill bytewise
    while( Bytes && (reinterpret_cast<RFTYPE::MemoryRange>(dst) & (sizeof(RFTYPE::Size)-1) ||
                     reinterpret_cast<RFTYPE::MemoryRange>(src) & (sizeof(RFTYPE::Size)-1)))
    {
        *(dst++) = *(src++);
        --Bytes;
    }

    sDst = reinterpret_cast<RFTYPE::Size*>(dst);
    sSrc = reinterpret_cast<const RFTYPE::Size*>(src);
    // aligned and more bytes then largest variable are left
    while((Bytes / sizeof(RFTYPE::Size)) > 0)
    {
        *(sDst++) = *(sSrc++);
        Bytes -= sizeof(RFTYPE::Size);
    }

    dst = reinterpret_cast<RFTYPE::UInt8*>(sDst);
    src = reinterpret_cast<const RFTYPE::UInt8*>(sSrc);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(dst++) = *(src++);
    }
}

void Copy_SSE2(void* Destination, const void* Source, Size Bytes)
{
    RFTYPE::UInt8* dst = reinterpret_cast<RFTYPE::UInt8*>(Destination);
    const RFTYPE::UInt8* src = reinterpret_cast<const RFTYPE::UInt8*>(Source);

    // not aligned pointer fill bytewise
    while( Bytes && (reinterpret_cast<RFTYPE::MemoryRange>(dst) & 0xf ||
                     reinterpret_cast<RFTYPE::MemoryRange>(src) & 0xf ))
    {
        *(dst++) = *(src++);
        --Bytes;
    }

    // aligned pointer fill 16byte pieces
    __m128i a;
    const __m128i* mSrc = reinterpret_cast<const __m128i*>(src);
    __m128i* mDst = reinterpret_cast<__m128i*>(dst);
    while (Bytes >= 16)
    {
        a = _mm_load_si128(mSrc++);
        _mm_store_si128(mDst++, a);
        Bytes -= 16;
    }

    dst = reinterpret_cast<RFTYPE::UInt8*>(mDst);
    src = reinterpret_cast<const RFTYPE::UInt8*>(mSrc);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(dst++) = *(src++);
    }
}

void Copy_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    if (info.Extensions.Test(RadonFramework::Diagnostics::ProcessorExtension::SSE2))
        RFMEM::Copy = Copy_SSE2;
    else
        RFMEM::Copy = Copy_Std;
    Copy(Destination, Source, Bytes);
}

void Move_Std(void* Destination, const void* Source, Size Bytes)
{
    UInt8 *pd = reinterpret_cast<UInt8*>(Destination);
    const UInt8 *ps = reinterpret_cast<const UInt8*>(Source);

    if (pd <= ps || pd >= (ps + Bytes))
    {
        // Non-Overlapping Buffers
        // copy from lower addresses to higher addresses
        while (Bytes--)
        {
            *(pd++) = *(ps++);
        }
    }
    else
    {
        // Overlapping Buffers
        // copy from higher addresses to lower addresses
        for (pd += Bytes, ps += Bytes; Bytes--;)
        {
            *--pd = *--ps;
        }
    }
}

void Move_CPUDispatcher(void* Destination, const void* Source, Size Bytes)
{
    const RadonFramework::Diagnostics::ProcessorSharedData& info = RadonFramework::System::LoadSharedProcessorInfo();
    RFMEM::Move = Move_Std;
    Move(Destination, Source, Bytes);
}

CompareCallback RadonFramework::System::Memory::Compare=Compare_CPUDispatcher;
SetCallback RadonFramework::System::Memory::Set=Set_CPUDispatcher;
CopyCallback RadonFramework::System::Memory::Copy=Copy_CPUDispatcher;
MoveCallback RadonFramework::System::Memory::Move=Move_CPUDispatcher;

//
// On-Demand dispatched functions which are OS API dependent and have to be implemented on each platform
//

UInt32 GetPageSize_SystemAPIDispatcher()
{
    Dispatch();
    return GetPageSize();
}

void EnableTerminationOnHeapCorruption_SystemAPIDispatcher()
{
    Dispatch();
    EnableTerminationOnHeapCorruption();
}

void* Allocate_SystemAPIDispatcher(UInt32 Bytes)
{
    Dispatch();
    return Allocate(Bytes);
}

void Free_SystemAPIDispatcher(void* FirstPage)
{
    Dispatch();
    Free(FirstPage);
}

GetPageSizeCallback RadonFramework::System::Memory::GetPageSize= GetPageSize_SystemAPIDispatcher;
EnableTerminationOnHeapCorruptionCallback RadonFramework::System::Memory::EnableTerminationOnHeapCorruption=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
AllocateCallback RadonFramework::System::Memory::Allocate=Allocate_SystemAPIDispatcher;
FreeCallback RadonFramework::System::Memory::Free=Free_SystemAPIDispatcher;

Bool RadonFramework::System::Memory::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && GetPageSize!=GetPageSize_SystemAPIDispatcher;
    result=result && EnableTerminationOnHeapCorruption!=EnableTerminationOnHeapCorruption_SystemAPIDispatcher;
    result=result && Allocate!=Allocate_SystemAPIDispatcher;
    result=result && Free!=Free_SystemAPIDispatcher;
    return result;
}

void RadonFramework::System::Memory::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
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