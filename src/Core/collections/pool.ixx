export module rf.core.collections:pool;
import rf.core.types;
import rf.core.memory;
import rf.core.cpu;

export namespace rf {
template <class T> class Pool {
public:
  Pool(AllocatorAdapter Allocator) : allocator(Allocator) {
    this->allocationSize = Allocator.recommendetGranularity();
    this->elementBucketCapacity =
        (this->allocationSize - sizeof(Bucket<T> *)) / sizeof(T);
    this->maskBucketCapacity =
        (this->allocationSize - sizeof(Bucket<u8> *)) * 8;
  }
  T &add() {
    if (this->totalElementCapacity == this->totalElementCount)
      this->grow();
    Bucket<u8> *c = this->usedMaskHead;
    size absoluteIndex = 0;
    while (c != nullptr) {
      bits bitmask;
      bitmask.memory = {c->elements, this->maskBucketCapacity};
      auto index = nextUnset(bitmask, 0, this->maskBucketCapacity);
      if (index == this->maskBucketCapacity) {
        c = c->next;
        absoluteIndex += this->elementBucketCapacity;
      } else {
        absoluteIndex += index;
        bitmask.set(index, true);
        this->totalElementCount++;
        return *this->at(absoluteIndex);
      }
    }
  }
  void remove(T &Object) {}
  void clear() {}
  T *at(size Index) {
    auto *c = this->elementsHead;
    size absoluteIndex = 0;
    T *result = nullptr;
    while (c != nullptr) {
      if (Index < absoluteIndex + this->elementBucketCapacity) {
        result = c->elements + (Index - absoluteIndex);
        break;
      }
      c = c->next;
    }
    return result;
  }
  size capacity() const { return this->totalElementCapacity; }
  size count() const { return this->totalElementCount; }

protected:
  template <class BT> struct Bucket {
    Bucket *next = nullptr;
    BT elements[];
  };

  Bucket<T> *elementsHead = nullptr;
  Bucket<T> *elementsTail = nullptr;
  Bucket<u8> *usedMaskHead = nullptr;
  Bucket<u8> *usedMaskTail = nullptr;
  AllocatorAdapter allocator;
  size totalElementCapacity = 0;
  size totalElementCount = 0;
  size totalMaskCapacity = 0;
  // calculated/obtained during construction
  size allocationSize = 0;
  size elementBucketCapacity = 0;
  size maskBucketCapacity = 0;

  void grow() {
    auto block = this->allocator.allocate(this->allocationSize);
    auto *bucket = reinterpret_cast<Bucket<T> *>(block.address);
    if (this->elementsHead == nullptr)
      this->elementsHead = bucket;
    else
      this->elementsTail->next = bucket;
    this->elementsTail = bucket;
    this->totalElementCapacity += this->elementBucketCapacity;
    if (this->totalElementCapacity > this->totalMaskCapacity) {
      block = this->allocator.allocate(this->allocationSize);
      auto maskBucket = reinterpret_cast<Bucket<u8> *>(block.address);
      this->totalMaskCapacity += this->maskBucketCapacity;
      if (this->usedMaskHead == nullptr)
        this->usedMaskHead = maskBucket;
      else
        this->usedMaskTail->next = maskBucket;
      this->usedMaskTail = maskBucket;
    }
  }
};
} // namespace rf