#ifndef RF_COLLECTIONS_RINGBUFFER_HPP
#define RF_COLLECTIONS_RINGBUFFER_HPP

#include <RadonFramework/Memory/HeapAllocator.hpp>

namespace RadonFramework::Collections {

enum class ConcurrencyModel
{
    None,
    SPSC,
    MPSC,
    SPMC,
    MPMC
};

template<ConcurrencyModel P>
class RingBufferAccess
{
public:
    explicit RingBufferAccess(RF_Type::Size& UsableBytes, RF_Type::UInt8*& MemoryBlock)
    {}

    RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
    {
        return false;
    }

    RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
    {
        return false;
    }
};

template<ConcurrencyModel P = ConcurrencyModel::SPSC>
class RingBuffer
{
public:
    RingBuffer()
        :m_Access(m_UsableBytes, m_View)
        , m_UsableBytes()
        , m_View(nullptr)
    {

    }

    ~RingBuffer()
    {
        Free();
    }

    void Allocate(const RF_Type::Size Bytes)
    {
        RF_Mem::HeapAllocator alloc;
        m_UsableBytes = Bytes;
        m_Mapping = alloc.Map(Bytes * 2);
        m_View = alloc.MapView(m_Mapping, Bytes);
        alloc.MapView(m_Mapping, Bytes, m_View + Bytes);
    }

    void Free()
    {
        RF_Mem::HeapAllocator alloc;
        alloc.Unmap(m_Mapping);
    }

    RF_Type::Bool Read(RF_Type::UInt8* Data, RF_Type::Size Bytes)
    {
        return m_Access.Read(Data, Bytes);
    }

    RF_Type::Bool Write(RF_Type::UInt8* Data, const RF_Type::Size Bytes)
    {
        return m_Access.Write(Data, Bytes);
    }
private:
    RingBufferAccess<P> m_Access;
    RF_Mem::MemoryMap m_Mapping;
    RF_Type::Size m_UsableBytes;
    RF_Type::UInt8* m_View;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif


#endif // !RF_COLLECTIONS_RINGBUFFER_HPP