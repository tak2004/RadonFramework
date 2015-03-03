#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Memory;

RF_Type::Int32 Compare_Std(const void* P1, const void* P2, RF_Type::Size Bytes)
{
    const RF_Type::UInt8 *p1 = reinterpret_cast<const RF_Type::UInt8*>(P1),
                      *p2 = reinterpret_cast<const RF_Type::UInt8*>(P2);
    while(Bytes--)
    {
        if(*p1 != *p2)
        {
            return *p1 - *p2;
        }
        else
        {
            p1++;
            p2++;
        }
    }
    return 0;
}

void Set_Std(void* Pointer, RF_Type::Int32 Value, RF_Type::Size Bytes)
{
    RF_Type::UInt8* p = reinterpret_cast<RF_Type::UInt8*>(Pointer);
    RF_Type::Size* mp;
    RF_Type::Size size = Value;
    // fill up largest variable
    for(RF_Type::Size i = 0; i < sizeof(RF_Type::Size); ++i)
        size = size | (size << 8);

    // not aligned pointer fill bytewise
    while( Bytes && reinterpret_cast<RF_Type::MemoryRange>(p) & (sizeof(RF_Type::Size)-1))
    {
        *(p++) = static_cast<RF_Type::UInt8>(Value);
        --Bytes;
    }

    mp = reinterpret_cast<RF_Type::Size*>(p);
    // aligned and more bytes then largest variable are left
    while((Bytes / sizeof(RF_Type::Size)) > 0)
    {
        *(mp++) = size;
        Bytes -= sizeof(RF_Type::Size);
    }

    p = reinterpret_cast<RF_Type::UInt8*>(mp);
    // fill up last unaligned bytes
    while(Bytes--)
    {
        *(p++) = static_cast<RF_Type::UInt8>(Value);
    }
}

void Copy_Std(void* Destination, const void* Source, Size Bytes)
{
    RF_Type::UInt8* dst = reinterpret_cast<RF_Type::UInt8*>(Destination);
    const RF_Type::UInt8* src = reinterpret_cast<const RF_Type::UInt8*>(Source);
    RF_Type::Size* sDst;
    const RF_Type::Size* sSrc;

    // not aligned pointer fill bytewise
    while( Bytes && (reinterpret_cast<RF_Type::MemoryRange>(dst) & (sizeof(RF_Type::Size)-1) ||
                     reinterpret_cast<RF_Type::MemoryRange>(src) & (sizeof(RF_Type::Size)-1)))
    {
        *(dst++) = *(src++);
        --Bytes;
    }

    sDst = reinterpret_cast<RF_Type::Size*>(dst);
    sSrc = reinterpret_cast<const RF_Type::Size*>(src);
    // aligned and more bytes then largest variable are left
    while((Bytes / sizeof(RF_Type::Size)) > 0)
    {
        *(sDst++) = *(sSrc++);
        Bytes -= sizeof(RF_Type::Size);
    }

    dst = reinterpret_cast<RF_Type::UInt8*>(sDst);
    src = reinterpret_cast<const RF_Type::UInt8*>(sSrc);
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

void Swap_Std(void* P1, void* P2, Size Bytes)
{
    UInt8 tmp;
    Size stmp;
    UInt8 *p1 = reinterpret_cast<UInt8*>(P1);
    UInt8 *p2 = reinterpret_cast<UInt8*>(P2);
    if(p1 <= p2 || p1 >= (p2 + Bytes))
    {
        while(Bytes && (reinterpret_cast<MemoryRange>(P1)& (sizeof(Size) - 1) ||
            reinterpret_cast<MemoryRange>(P2)& (sizeof(Size) - 1)))
        {
            tmp = *p1;
            *(p1++) = *p2;
            *(p2++) = tmp;
            --Bytes;
        }

        Size* s1 = reinterpret_cast<Size*>(p1);
        Size* s2 = reinterpret_cast<Size*>(p2);
        // aligned and more bytes then largest variable are left
        while((Bytes / sizeof(Size)) > 0)
        {
            stmp = *s1;
            *(s1++) = *s2;
            *(s2++) = stmp;
            Bytes -= sizeof(Size);
        }

        p1 = reinterpret_cast<UInt8*>(s1);
        p2 = reinterpret_cast<UInt8*>(s2);
        // swap last unaligned bytes
        while(Bytes--)
        {
            tmp = *p1;
            *(p1++) = *p2;
            *(p2++) = tmp;
        }
    }
}