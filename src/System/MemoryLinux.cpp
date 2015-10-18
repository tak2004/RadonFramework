#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"

void* AllocateLinux(RF_Type::UInt32 Bytes)
{
    return malloc(Bytes);
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