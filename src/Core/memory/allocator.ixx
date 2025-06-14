export module rf.core.memory:allocator;
import rf.core.types;

export namespace rf {
class Allocator {
public:
  virtual void embed(Allocator *Embed) = 0;
  // Reserve a memory block which can be used later on due a commitment.
  virtual mem reserve(size Bytes) = 0;
  // Commit the usage of a memory block in a reservation.
  virtual mem commit(mem Reservation, size ByteOffset, size Bytes) = 0;
  /// <summary>
  /// Allocate the requested amount of bytes on the heap.
  /// This should be used if the size of the block is never changing during
  /// runtime.
  /// </summary>
  /// <param name="Bytes">Amount of bytes to allocate</param>
  /// <returns>A memor block which is at least as large as the requested size or
  /// empty.</returns>
  virtual mem allocate(size Bytes) = 0;
  /// <summary>
  /// Deallocate a previously allocated memory block.
  /// </summary>
  /// <param name="Memory">Specifies the memory block returned by the allocate
  /// function.</param>
  virtual void deallocate(const mem &Memory) = 0;
  // Deallocate a memory block which was allocated by the commit method.
  virtual void release(mem Reservation, const mem& Memory) = 0;
  /// <summary>
  /// Check if the specified memory block is owned by the allocator.
  /// </summary>
  /// <param name="Block">A block which is part of an allocation.</param>
  /// <returns>True if the specified block is part of an allocation else
  /// false.</returns>
  virtual bool owns(const mem &Block) = 0;
  /// <summary>
  /// Deallocate all memory owned by this allocator.
  /// </summary>
  virtual void clear() = 0;
  // Create a map to map data to memory.
  virtual memmap map(size Bytes) = 0;
  // Free the mapping.
  virtual void unmap(const memmap &Mapping) = 0;
  // Maps the specified amount of Bytes of the specified map to the View.
  // This can be used to simplify and optimize ring buffer by mapping the memory
  // block right after the memory block. Writing beyond the memory block will
  // write into the mapping which points to the beginning of the memory block.
  virtual mem mapView(const memmap &Mapping, size Bytes,
                      ptr View = nullptr) = 0;
};
} // namespace rf