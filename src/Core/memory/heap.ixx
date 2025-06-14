module;
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>
export module rf.core.memory:heap;
import :allocator;

export namespace rf {
class Heap : public Allocator {
public:
  // This will do nothing.
  void embed(Allocator *Embed) override;
  mem reserve(size Bytes) override;
  mem commit(mem Reservation, size ByteOffset, size Bytes) override;
  mem allocate(size Bytes) override;
  void deallocate(const mem &Memory) override;
  void release(mem Reservation, const mem &Memory) override;
  bool owns(const mem &Block) override;
  void clear() override;
  memmap map(size Bytes) override;
  void unmap(const memmap &Mapping) override;
  mem mapView(const memmap &Mapping, size Bytes, ptr View = nullptr) override;
};

mem reserveOS(const size Bytes) {
  mem result;
  result.address = VirtualAlloc(0, Bytes, MEM_RESERVE, PAGE_READWRITE);
  result.bytes = Bytes;
  return result;
}

mem commitOS(const mem &Block) {
  mem result;
  result.address =
      VirtualAlloc(Block.address, Block.bytes, MEM_COMMIT, PAGE_READWRITE);
  result.bytes = result.address ? Block.bytes : 0;
  return result;
}

mem allocateOS(const size Bytes) {
  mem result;
  result.address =
      VirtualAlloc(0, Bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  result.bytes = result.address ? Bytes : 0;
  return result;
}

void deallocateOS(const mem &Block) {
  VirtualFree(Block.address, 0, MEM_RELEASE);
}

memmap mapMemoryOS(size Bytes) {
  memmap result;
  result.handle = CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE,
                                     Bytes >> 32, Bytes & 0xffffffffu, nullptr);
  return result;
}

void unmapMemoryOS(memmap MemoryMapHandle) {
  CloseHandle(MemoryMapHandle.handle);
}

mem mapViewOS(memmap MemoryMapHandle, const size Bytes, ptr View) {
  mem result;
  result.address = MapViewOfFileEx(MemoryMapHandle.handle, FILE_MAP_ALL_ACCESS,
                                   0, 0, Bytes, View);
  result.bytes = result.address ? Bytes : 0;
  return result;
}

void Heap::embed(Allocator *Embed) {}

mem Heap::reserve(const size Bytes) { return reserveOS(Bytes); }

mem Heap::commit(mem Reservation, const size ByteOffset,
                 const size Bytes) {
  mem block;
  block.address = (ptr)((ptrdiff)Reservation.address + ByteOffset);
  block.bytes = Bytes;
  mem result = commitOS(block);
  return result;
}

mem Heap::allocate(const size Bytes) { return allocateOS(Bytes); }

void Heap::deallocate(const mem &Memory) { deallocateOS(Memory); }

void Heap::release(mem Reservation, const mem &Memory) {
  deallocateOS(Memory);
}

bool Heap::owns(const mem &Block) { return false; }

void Heap::clear() {}

memmap Heap::map(const size Bytes) {
  memmap result = mapMemoryOS(Bytes);
  return result;
}

void Heap::unmap(const memmap &Mapping) { unmapMemoryOS(Mapping); }

mem Heap::mapView(const memmap &Mapping, const size Bytes, const ptr View) {
  return mapViewOS(Mapping, Bytes, View);
}

} // namespace rf
