#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Memory;

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