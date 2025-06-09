export module rf.core.collections:hashlist;
import rf.core.types;
import rf.core.memory;
import rf.core.cpu;

export namespace rf {
// The Hashlist use a bucket list with a fixed amount of keys per bucket.
// The elements per bucket are determined by 
    template <class KEYTYPE = u32, IsAllocator ALLOCATOR= Allocator> class Hashlist {
    public:
        Hashlist(ALLOCATOR& LongLiving, StackAdapter Stack, size MemoryLimit=12_kib);
        ~Hashlist();
        // forbid copies, use clone() method
        Hashlist(const Hashlist&) = delete;
        Hashlist& operator=(const Hashlist&) = delete;
        Hashlist& operator=(Hashlist) = delete;

        void set(KEYTYPE Key, ptr Value);
        bool containsKey(KEYTYPE Key) const;
        void remove(KEYTYPE Key);
        ptr get(KEYTYPE Key)const;
// TODO: glass
        void reserve(size Elements);
        void clone(Hashlist& To)const;        
    protected:
        ALLOCATOR& allocator;
        StackAdapter stack;
        mem pool = { nullptr, 0 };
        size hashesSize = 0;
        size valuesSize = 0;
        ptr values = nullptr;
        size hashesGrowSize = 0;
        size valuesGrowSize = 0;
        size bucketElements = 0;
        size buckets = 0;        

        void detectHardwareOptimizationSettings(StackAdapter Stack);
        void grow();
        size find(KEYTYPE Key);
        size findEmptySlot(const KEYTYPE Key) const;
        size findBucket(const KEYTYPE Key) const;
        size invalidIndex()const;
    };

template <class KEYTYPE, IsAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::detectHardwareOptimizationSettings(StackAdapter Stack) {
    // The idea is to use as many buckets as possible and keep the bucket size at a fix size.
    // The bucket size should utilize the L1 cache. Commonly the cache is a N-Way-Set-Associative.
    // 32kb l1, 64b linesize, 8-way, 
    // 8 lines = 512b per set, 
    // 32kb/512b = 64 sets, 
    // 64sets*64b lines=4096b sequential cache
    static size memorizedGrowSize;
    static size memorizedBucketElements;
    if (memorizedGrowSize == 0 || memorizedBucketElements == 0) {
        size simdWidth = detectMaxSIMDWidth<KEYTYPE>();
        size simdElements = simdWidth / sizeof(KEYTYPE);
        size optimalBlockSize = 64;// fallback l1 cache line 64byte
        CacheLayout cache;
        cache.detect(Stack);        
        auto l1Data = cache.get(getCurrentProcessorNumber(), 1, CacheUseCase::Data);
        if (l1Data) {
            constexpr size associativeMultiplier[] = { 1,2,4,6,8,12,16,24,1,1 };// CacheAssociativity
            auto setSize = l1Data->lineBytes*associativeMultiplier[static_cast<u8>(l1Data->associativity)];
            auto sets = l1Data->bytes / setSize;
            optimalBlockSize = sets * l1Data->lineBytes;            
        }        
        Stack.clear();
        auto instructionsPerBlock = (optimalBlockSize + simdWidth - 1) / simdWidth;
        memorizedBucketElements = instructionsPerBlock* simdElements;
        memorizedGrowSize = optimalBlockSize;
    }
    this->bucketElements = memorizedBucketElements;
    this->hashesGrowSize = memorizedGrowSize;
    this->valuesGrowSize = memorizedBucketElements * sizeof(ptr);
}

template <class KEYTYPE, IsAllocator ALLOCATOR>
Hashlist<KEYTYPE, ALLOCATOR>::Hashlist(ALLOCATOR& LongLiving, StackAdapter Stack, size MemoryLimit)
:allocator(LongLiving), stack(Stack){
    this->detectHardwareOptimizationSettings(this->stack);        
    this->pool = this->allocator.reserve(MemoryLimit);
    auto offset = MemoryLimit / (sizeof(KEYTYPE) + sizeof(ptr)) * sizeof(KEYTYPE);
    this->values = reinterpret_cast<u8*>(this->pool.address) + offset;
}

template <class KEYTYPE, IsAllocator ALLOCATOR>
Hashlist<KEYTYPE, ALLOCATOR>::~Hashlist(){
    this->allocator.clear();
}

template <class KEYTYPE, IsAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::set(KEYTYPE Key, ptr Value){
    auto keyIndex = this->find(Key);
    if (keyIndex == invalidIndex()) {
        keyIndex = this->findEmptySlot(Key);
        if (keyIndex == invalidIndex()) {
            this->grow();
            keyIndex = this->findEmptySlot(Key);
        }
    }
    reinterpret_cast<KEYTYPE*>(this->pool.address)[keyIndex] = Key;
    reinterpret_cast<ptr*>(this->values)[keyIndex] = Value;
}

template<class KEYTYPE, IsAllocator ALLOCATOR>
void Hashlist<KEYTYPE, ALLOCATOR>::grow()
{
    auto block = this->allocator.commit(this->pool, hashesSize, this->hashesGrowSize);
    hashesSize += block.bytes;
    block = this->allocator.commit(this->pool, reinterpret_cast<ptrdiff>(this->values) + this->valuesSize, this->valuesGrowSize);
    this->valuesSize += block.bytes;
}

template<class KEYTYPE, IsAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::find(KEYTYPE Key)
{
    SIMDView<KEYTYPE> keys;
    if (this->buckets) {
        auto offset = findBucket(Key);
        //keys.memory = slice(this->hashes, offset, this->bucketElements);
        auto index = rf::find(keys, Key);
        if (index < this->bucketElements)
            return offset + index;
    }
    return invalidIndex();
}

template<class KEYTYPE, IsAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::findEmptySlot(const KEYTYPE Key) const
{
    if (this->buckets) {
        auto offset = findBucket(Key);
        SIMDView<KEYTYPE> keys;
        //keys.memory = slice(this->hashes, offset, this->bucketElements);
        auto index = rf::find(keys, 0);
        if (index < this->bucketElements)
            return offset + index;
    }
    return invalidIndex();
}

template<class KEYTYPE, IsAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::findBucket(const KEYTYPE Key) const
{
    return (Key & (this->buckets - 1)) * this->bucketElements;
}

template<class KEYTYPE, IsAllocator ALLOCATOR>
inline size Hashlist<KEYTYPE, ALLOCATOR>::invalidIndex() const
{
    return this->buckets * this->bucketElements;
}
} // namespace rf