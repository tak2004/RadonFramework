#ifndef RF_MEMORY_POOLALLOCATOR_HPP
#define RF_MEMORY_POOLALLOCATOR_HPP

namespace RadonFramework::Memory
{
/// Use this class only for allocation of the same size and alignment.
/// It reserves a large chunk from the specified arena and split it up.
template <class ALLOCATOR,
          RF_Type::Size BLOCK_SIZE,
          RF_Type::Size BLOCK_ALIGN_SIZE>
class PoolAllocator : private ALLOCATOR
{
public:
protected:
private:
};

}  // namespace RadonFramework::Memory

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif  // RF_MEMORY_POOLALLOCATOR_HPP