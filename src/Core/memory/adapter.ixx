module;
#include <concepts>
export module rf.core.memory:adapter;
import rf.core.types;

export namespace rf {

template<typename T>
concept IsBasicAllocator = requires(T obj) {
    { obj.allocate(size()) } -> std::same_as<mem>;
    { obj.deallocate(mem{}) } -> std::same_as<void>;
};

template<typename T>
concept IsContinousGrowableAllocator = requires(T obj) {
    { obj.reserve(size()) } -> std::same_as<mem>;
    { obj.commit(mem{}, size(), size()) } -> std::same_as<mem>;
    { obj.deallocate(mem{}) } -> std::same_as<void>;
};

template<typename T>
concept IsAllocator = IsBasicAllocator<T> && IsContinousGrowableAllocator<T>;

struct AllocatorAdapter {
    // Allocate a chunk at an unspecified place and isn't growable.
    mem allocate(size Bytes) { return this->allocateImplementation(Bytes, this->allocator); }
    // Release the specified allocation obtained by the allocate function.
    void deallocate(mem& Memory) { this->deallocateImplementation(Memory, this->allocator); }
    // Allocate a chunk on the specified position of the reserved pool.
    mem commit(mem& Pool, size Offset, size Bytes) { return this->commitImplementation(Pool, Offset, Bytes, this->allocator); }
    // Release the specified allocation in the pool.
    void release(mem& Pool, mem& Memory) { this->releaseImplementation(Pool, Memory, this->allocator); }
    // Release all allocations and reservations.
    void clear() { this->clearImplementation(this->allocator); }
    size recommendetGranularity() { return this->recommendetGranularityImplementation(this->allocator); }
    // Reserve a pool of the specified bytes and return the memory pool on success.
    mem reserve(size Bytes) { return this->reserveImplementation(Bytes, this->allocator); }
    
    mem(*allocateImplementation)(size Bytes, ptr Allocator);
    void (*deallocateImplementation)(mem& Memory, ptr Allocator);
    mem(*commitImplementation)(mem& Pool, size Offset, size Bytes, ptr Allocator);
    void(*releaseImplementation)(mem& Pool, mem& Memory, ptr Allocator);
    void(*clearImplementation)(ptr Allocator);
    size(*recommendetGranularityImplementation)(ptr Allocator);
    mem(*reserveImplementation)(size Bytes, ptr Allocator);
    ptr allocator;
};

struct StackAdapter {
    mem push(size Bytes) { return this->pushImplementation(Bytes, this->allocator); }
    void pop(mem& Memory) { this->popImplementation(Memory, this->allocator); }
    void clear() { this->clearImplementation(this->allocator); }

    mem(*pushImplementation)(size Bytes, ptr Allocator);
    void(*popImplementation)(mem& Memory, ptr Allocator);
    void(*clearImplementation)(ptr Allocator);
    ptr allocator;
};
}