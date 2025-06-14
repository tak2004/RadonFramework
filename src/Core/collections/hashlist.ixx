export module rf.core.collections:hashlist;
import rf.core.types;
import rf.core.memory;
import rf.core.cpu;

export namespace rf {
// The Hashlist use a bucket list with a fixed amount of keys per bucket.
// The elements per bucket are determined by the CPU L1 Cache-layout.
template <class KEYTYPE=u32, IsContinousGrowableAllocator ALLOCATOR=Allocator>
class Hashlist {
public:
  Hashlist() = delete;
  Hashlist(ALLOCATOR &LongLiving, StackAdapter Stack,
           size MemoryLimit = 12_kib);
  ~Hashlist();
  // forbid copies, use clone() method
  Hashlist(const Hashlist &) = delete;
  Hashlist &operator=(const Hashlist &) = delete;
  Hashlist &operator=(Hashlist) = delete;
  void clone(Hashlist &To) const;

  void set(KEYTYPE Key, ptr Value);
  bool containsKey(KEYTYPE Key) const;
  void remove(KEYTYPE Key);
  ptr get(KEYTYPE Key) const;

protected:
  ALLOCATOR *allocator=nullptr;
  StackAdapter stack = {};
  mem pool = {nullptr, 0};
  size hashesSize = 0;
  size valuesSize = 0;
  ptr values = nullptr;
  size hashesGrowSize = 0;
  size valuesGrowSize = 0;
  size bucketElements = 0;
  size buckets = 0;

  void detectHardwareOptimizationSettings(StackAdapter Stack);
  void grow();
  size find(KEYTYPE Key) const;
  size findEmptySlot(const KEYTYPE Key) const;
  size findBucket(const KEYTYPE Key) const;
  size invalidIndex() const;
};

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::detectHardwareOptimizationSettings(
    StackAdapter Stack) {
  // The idea is to use as many buckets as possible and keep the bucket size at
  // a fix size. The bucket size should utilize the L1 cache. Commonly the cache
  // is a N-Way-Set-Associative. 32kb l1, 64b linesize, 8-way, 8 lines = 512b
  // per set, 32kb/512b = 64 sets, 64sets*64b lines=4096b sequential cache
  static size memorizedGrowSize;
  static size memorizedBucketElements;
  if (memorizedGrowSize == 0 || memorizedBucketElements == 0) {
    size simdWidth = detectMaxSIMDWidth<KEYTYPE>();
    size simdElements = simdWidth / sizeof(KEYTYPE);
    size optimalBlockSize = 64; // fallback l1 cache line 64byte
    CacheLayout cache;
    cache.detect(Stack);
    auto l1Data = cache.get(getCurrentProcessorNumber(), 1, CacheUseCase::Data);
    if (l1Data) {
      constexpr size associativeMultiplier[] = {
          1, 2, 4, 6, 8, 12, 16, 24, 1, 1}; // CacheAssociativity
      auto setSize =
          l1Data->lineBytes *
          associativeMultiplier[static_cast<u8>(l1Data->associativity)];
      auto sets = l1Data->bytes / setSize;
      optimalBlockSize = sets * l1Data->lineBytes;
    }
    Stack.clear();
    auto instructionsPerBlock = (optimalBlockSize + simdWidth - 1) / simdWidth;
    memorizedBucketElements = instructionsPerBlock * simdElements;
    memorizedGrowSize = optimalBlockSize;
  }
  this->bucketElements = memorizedBucketElements;
  this->hashesGrowSize = memorizedGrowSize;
  this->valuesGrowSize = memorizedBucketElements * sizeof(ptr);
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
Hashlist<KEYTYPE, ALLOCATOR>::Hashlist(ALLOCATOR &LongLiving,
                                       StackAdapter Stack, size MemoryLimit)
    : allocator(&LongLiving), stack(Stack) {
  this->detectHardwareOptimizationSettings(this->stack);
  this->pool = this->allocator->reserve(MemoryLimit);
  auto offset = (MemoryLimit / (this->hashesGrowSize + this->valuesGrowSize)) *
                this->hashesGrowSize;
  this->values = rf::offset(this->pool, offset);
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
Hashlist<KEYTYPE, ALLOCATOR>::~Hashlist() {
  this->allocator->clear();
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::clone(Hashlist &To) const {
  // Clean up old memory and assign the new memory allocators.
  To.allocator->clear();
  To.allocator = this->allocator;
  To.stack = this->stack;
  // Clone the metadata.
  To.hashesGrowSize = this->hashesGrowSize;
  To.valuesGrowSize = this->valuesGrowSize;
  To.bucketElements = this->bucketElements;
  To.buckets = this->buckets;
  To.hashesSize = this->hashesSize;
  To.valuesSize = this->valuesSize;
  // Reserve, commit and copy memory.
  To.pool = To.allocator->reserve(this->pool.bytes);
  auto offset = reinterpret_cast<ptrdiff>(this->values) -
                reinterpret_cast<ptrdiff>(this->pool.address);
  To.values = rf::offset(To.pool, offset);
  auto hashes = To.allocator->commit(To.pool, 0, To.hashesSize);
  auto values = To.allocator->commit(To.pool, offset, To.valuesSize);
  mem srcHashes = {To.pool.address, To.hashesSize};
  mem srcValues = {To.values, To.valuesSize};
  rf::copy(srcHashes, hashes);
  rf::copy(srcValues, values);
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::set(KEYTYPE Key, ptr Value) {
  auto keyIndex = this->find(Key);
  if (keyIndex == invalidIndex()) {
    keyIndex = this->findEmptySlot(Key);
    if (keyIndex == invalidIndex()) {
      this->grow();
      keyIndex = this->findEmptySlot(Key);
    }
  }
  reinterpret_cast<KEYTYPE *>(this->pool.address)[keyIndex] = Key;
  reinterpret_cast<ptr *>(this->values)[keyIndex] = Value;
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
bool Hashlist<KEYTYPE, ALLOCATOR>::containsKey(KEYTYPE Key) const {
  auto keyIndex = this->find(Key);
  return keyIndex != invalidIndex();
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::remove(KEYTYPE Key) {
  auto keyIndex = this->find(Key);
  if (keyIndex != invalidIndex()) {
    reinterpret_cast<KEYTYPE *>(this->pool.address)[keyIndex] = 0;
    reinterpret_cast<ptr *>(this->values)[keyIndex] = nullptr;
  }
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
ptr Hashlist<KEYTYPE, ALLOCATOR>::get(KEYTYPE Key) const {
  auto keyIndex = this->find(Key);
  if (keyIndex != invalidIndex())
    return reinterpret_cast<ptr *>(this->values)[keyIndex];
  else
    return nullptr;
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::grow() {
  auto block = this->allocator->commit(this->pool, this->hashesSize,
                                       this->hashesGrowSize);
  this->hashesSize += block.bytes;
  auto byteOffset = reinterpret_cast<ptrdiff>(this->values) -
                    reinterpret_cast<ptrdiff>(this->pool.address);
  block = this->allocator->commit(this->pool, byteOffset + this->valuesSize,
                                  this->valuesGrowSize);
  this->valuesSize += block.bytes;
  this->buckets++;
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::find(KEYTYPE Key) const {
  SIMDView<KEYTYPE> keys;
  if (this->buckets) {
    auto offset = findBucket(Key);
    keys.memory =
        slice(this->pool, offset * this->hashesGrowSize, this->hashesGrowSize);
    auto index = rf::find(keys, Key);
    if (index != keys.memory.bytes)
      return offset + index;
  }
  return invalidIndex();
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
inline size
Hashlist<KEYTYPE, ALLOCATOR>::findEmptySlot(const KEYTYPE Key) const {
  if (this->buckets) {
    auto offset = findBucket(Key);
    SIMDView<KEYTYPE> keys;
    keys.memory.address = rf::offset(this->pool, offset * this->hashesGrowSize);
    keys.memory.bytes = this->hashesGrowSize;
    auto index = rf::find(keys, 0);
    if (index != keys.memory.bytes)
      return offset + index;
  }
  return invalidIndex();
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::findBucket(const KEYTYPE Key) const {
  return (Key & (this->buckets - 1)) * this->bucketElements;
}

template <class KEYTYPE, IsContinousGrowableAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::invalidIndex() const {
  return this->buckets * this->bucketElements;
}
} // namespace rf