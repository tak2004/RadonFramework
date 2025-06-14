export module rf.core.memory:allocatorevents;
import :allocator;

export namespace rf {
// Allows to set functions which will be called on following chases:
// - after commit
// - after allocate
// - after map
// - before deallocate
// - before unmap
// This is usefull to zero memory to avoid leaking data, zero memory
// to optimize logic code or fill it with a debug pattern to find find
// uninitialized memory like Visual Studio does.
class AllocatorEvents : public Allocator {
public:
  void embed(Allocator *Embed) override;
  mem reserve(size Bytes) override;
  mem commit(mem Reservation, size ByteOffset, size Bytes) override;
  void release(mem Reservation, const mem &Memory) override;
  mem allocate(size Bytes) override;
  void deallocate(const mem &Memory) override;
  bool owns(const mem &Block) override;
  void clear() override;
  memmap map(size Bytes) override;
  void unmap(const memmap &Mapping) override;
  mem mapView(const memmap &Mapping, size Bytes, ptr View = nullptr) override;

  void (*onPostCommit)(mem &Memory);
  void (*onPreRelease)(const mem &Memory);
  void (*onPostAllocate)(mem &Memory);
  void (*onPostMap)(memmap &Memory);
  void (*onPreDeallocate)(const mem &Memory);
  void (*onPreUnmap)(const memmap &Memory);

private:
  Allocator *nested;
};

void AllocatorEvents::embed(Allocator *Embed) { this->nested = Embed; }

mem AllocatorEvents::reserve(size Bytes) {
  auto result = this->nested->reserve(Bytes);
  return result;
}

mem AllocatorEvents::commit(mem Reservation, size ByteOffset, size Bytes) {
  auto result = this->nested->commit(Reservation, ByteOffset, Bytes);
  if (this->onPostCommit != nullptr)
    this->onPostCommit(result);
  return result;
}

void AllocatorEvents::release(mem Reservation, const mem &Memory) {
    if (this->onPreRelease != nullptr)
        this->onPreRelease(Memory);
    this->nested->release(Reservation, Memory);
}

mem AllocatorEvents::allocate(size Bytes) {
  auto result = this->nested->allocate(Bytes);
  if (this->onPostAllocate != nullptr)
    this->onPostAllocate(result);
  return result;
}

void AllocatorEvents::deallocate(const mem &Memory) {
  if (this->onPreDeallocate != nullptr)
    this->onPreDeallocate(Memory);
  this->nested->deallocate(Memory);
}

bool AllocatorEvents::owns(const mem &Block) {
  return this->nested->owns(Block);
}

void AllocatorEvents::clear() { this->nested->clear(); }

memmap AllocatorEvents::map(size Bytes) {
  auto result = this->nested->map(Bytes);
  if (this->onPostMap != nullptr)
    this->onPostMap(result);
  return result;
}

void AllocatorEvents::unmap(const memmap &Mapping) {
  if (this->onPreUnmap != nullptr)
    this->onPreUnmap(Mapping);
  this->nested->unmap(Mapping);
}

mem AllocatorEvents::mapView(const memmap &Mapping, size Bytes, ptr View) {
  auto result = this->nested->mapView(Mapping, Bytes, View);
  return result;
}
} // namespace rf