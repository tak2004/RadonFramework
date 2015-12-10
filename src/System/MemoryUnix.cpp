#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"
#include <stdlib.h>

void* AllocateLinux(const RF_Type::Size Bytes, const RF_Type::Size Alignment)
{
    void* result = 0;
    if(Bytes > 0)
        ::posix_memalign(&result, Alignment, Bytes);
    return result;
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