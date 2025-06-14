export module rf.core.memory:ownership;
import :allocator;

export namespace rf {
// Keep track of allocations and stops the owns function to be passed any further.
class AllocatorOwnership : public Allocator {
public:
  void embed(Allocator *Embed) override;
  mem reserve(size Bytes) override;
  mem commit(mem Reservation, size ByteOffset, size Bytes) override;
  void release(mem Reservation, const mem& Memory) override;
  mem allocate(size Bytes) override;
  void deallocate(const mem &Memory) override;
  bool owns(const mem &Block) override;
  void clear() override;
  memmap map(size Bytes) override;
  void unmap(const memmap &Mapping) override;
  mem mapView(const memmap &Mapping, size Bytes, ptr View = nullptr) override;
private:
  Allocator *nested;
};

void AllocatorOwnership::embed(Allocator* Embed)
{
	this->nested = Embed;
}

mem AllocatorOwnership::reserve(size Bytes)
{
	auto result = this->nested->reserve(Bytes);
	return result;
}

mem AllocatorOwnership::commit(mem Reservation, size ByteOffset, size Bytes)
{
	auto result = this->nested->commit(Reservation, ByteOffset, Bytes);
	return result;
}

void AllocatorOwnership::release(mem Reservation, const mem& Memory)
{
	this->nested->release(Reservation, Memory);
}

mem AllocatorOwnership::allocate(size Bytes)
{
	auto result = this->nested->allocate(Bytes);
	return result;
}

void AllocatorOwnership::deallocate(const mem& Memory)
{
	this->nested->deallocate(Memory);
}

bool AllocatorOwnership::owns(const mem& Block)
{
    // TODO: Implement memory tracking.
	return false;
}

void AllocatorOwnership::clear()
{
	this->nested->clear();
}

memmap AllocatorOwnership::map(size Bytes)
{
	auto result = this->nested->map(Bytes);
	return result;
}

void AllocatorOwnership::unmap(const memmap& Mapping)
{
	this->nested->unmap(Mapping);
}

mem AllocatorOwnership::mapView(const memmap& Mapping, size Bytes, ptr View)
{
	auto result = this->nested->mapView(Mapping, Bytes, View);
	return result;
}
} // namespace rf