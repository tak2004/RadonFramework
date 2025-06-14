export module rf.core.memory:diagnostic;
import :allocator;

export namespace rf {
struct MemoryStatistics {
	size totalReserved;
	size totalCommited;
	size totalAllocated;
	size totalMapped;

	size opsReserve;
	size opsCommit;
	size opsRelease;
	size opsAllocate;
	size opsDeallocate;
	size opsOwns;
	size opsClear;
	size opsMap;
	size opsUnmap;
	size opsMapView;
};

class AllocatorDiagnostic : public Allocator {
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
  
  MemoryStatistics statistic = { 0 };
private:
  Allocator *nested;
};

void AllocatorDiagnostic::embed(Allocator* Embed)
{
	this->nested = Embed;
}

mem AllocatorDiagnostic::reserve(size Bytes)
{
	auto result = this->nested->reserve(Bytes);
	this->statistic.totalReserved += result.bytes;
	this->statistic.opsReserve++;
	return result;
}

mem AllocatorDiagnostic::commit(mem Reservation, size ByteOffset, size Bytes)
{
	auto result = this->nested->commit(Reservation, ByteOffset, Bytes);
	this->statistic.totalCommited += result.bytes;
	this->statistic.opsCommit++;
	return result;
}

void AllocatorDiagnostic::release(mem Reservation, const mem& Memory)
{
	this->nested->release(Reservation, Memory);
	this->statistic.totalCommited -= Memory.bytes;
	this->statistic.opsRelease++;
}

mem AllocatorDiagnostic::allocate(size Bytes)
{
	auto result = this->nested->allocate(Bytes);
	this->statistic.totalAllocated += result.bytes;
	this->statistic.opsAllocate++;
	return result;
}

void AllocatorDiagnostic::deallocate(const mem& Memory)
{
	this->nested->deallocate(Memory);
	this->statistic.totalAllocated -= Memory.bytes;
	this->statistic.opsDeallocate++;
}

bool AllocatorDiagnostic::owns(const mem& Block)
{
	this->statistic.opsOwns++;
	return this->nested->owns(Block);
}

void AllocatorDiagnostic::clear()
{
	this->nested->clear();
	this->statistic.totalAllocated = 0;
	this->statistic.totalCommited = 0;
	this->statistic.totalReserved = 0;
	this->statistic.totalMapped = 0;
	this->statistic.opsClear++;
}

memmap AllocatorDiagnostic::map(size Bytes)
{
	auto result = this->nested->map(Bytes);
	this->statistic.totalMapped += result.bytes;
	this->statistic.opsMap++;
	return result;
}

void AllocatorDiagnostic::unmap(const memmap& Mapping)
{
	this->nested->unmap(Mapping);
	this->statistic.totalMapped -= Mapping.bytes;
	this->statistic.opsUnmap++;
}

mem AllocatorDiagnostic::mapView(const memmap& Mapping, size Bytes, ptr View)
{
	auto result = this->nested->mapView(Mapping, Bytes, View);
	this->statistic.opsMapView++;
	return result;
}

} // namespace rf