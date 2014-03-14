#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

namespace std
{
    struct nothrow_t{};
    extern const nothrow_t nothrow;
}

const std::nothrow_t std::nothrow;

// no throw
void* operator new[](size_t bytes, const std::nothrow_t& nothrow) throw()
{
    return HeapAlloc(GetProcessHeap(), 0, bytes);
}

void* operator new(size_t bytes)
{
    return HeapAlloc(GetProcessHeap(), 0, bytes);
}

void* operator new(size_t bytes, const std::nothrow_t& nothrow) throw()
{
    return HeapAlloc(GetProcessHeap(), 0, bytes);
}

void operator delete(void *p)
{
    HeapFree(GetProcessHeap(), 0, p);
}

void operator delete[](void *p)
{
    HeapFree(GetProcessHeap(), 0, p);
}

void *operator new[](size_t s)
{
    return HeapAlloc(GetProcessHeap(), 0, s);
}