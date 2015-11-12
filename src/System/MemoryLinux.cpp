#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include <stdlib.h>

void* AllocateLinux(const RF_Type::Size Bytes, const RF_Type::Size Alignment)
{
    return aligned_alloc(Bytes, Alignment);
}

void FreeLinux(void* FirstPage)
{
    free(FirstPage);
}

void RF_SysMem::Dispatch()
{
    Allocate = AllocateLinux;
    Free = FreeLinux;
}