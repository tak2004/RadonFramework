#ifndef RF_MEMORY_LINEARALLOCATOR_HPP
#define RF_MEMORY_LINEARALLOCATOR_HPP

// Use this only for large chunks.
// 16Byte alignment is ensured.

namespace RadonFramework
{
    namespace Memory
    {
        struct ALIGN(16) LinearAllocator
        {
            static LinearAllocator* CreateInstance(const RFTYPE::Size MemorySize);
            static void FreeInstance(LinearAllocator*& instance);
            void ClearInstance();
            void* Allocate(const RFTYPE::Size Bytes);
        private:
            RFTYPE::Size m_TotalSize;
            RFTYPE::Size m_OffsetToFirstFreeByte;
        };
    }
}

#endif // RF_MEMORY_LINEARALLOCATOR_HPP