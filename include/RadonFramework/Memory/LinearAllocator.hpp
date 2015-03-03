#ifndef RF_MEMORY_LINEARALLOCATOR_HPP
#define RF_MEMORY_LINEARALLOCATOR_HPP

// Use this only for large chunks.
// 16Byte alignment is ensured.

namespace RadonFramework { namespace Memory {

struct RF_ALIGN(16) LinearAllocator
{
    static LinearAllocator* CreateInstance(const RF_Type::Size MemorySize);
    static void FreeInstance(LinearAllocator*& Instance);
    void Clear();
    void* Allocate(const RF_Type::Size Bytes);
private:
    RF_Type::Size m_TotalSize;
    RF_Type::Size m_OffsetToFirstFreeByte;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif // RF_MEMORY_LINEARALLOCATOR_HPP