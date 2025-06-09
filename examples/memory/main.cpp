import rf.core.memory;
import rf.core.os;
import rf.core.types;
import rf.core.cpu;

using namespace rf;
// A container which use following points.
// - hold one POD type
// - can grow dynamically
// - is a continues array,
// - allows holes
//    - no need to swap element data
//    - can use pointer of elements
// - very fast delete/setEnabled, very slow add/update
template <class T> struct ComponentPool {
  static_assert(sizeof(T) >= 8, "T POD must be at least 8 byte large to work "
                                "properly with holes tracking.");
  void init(Allocator *AnAllocator, size ElementLimit, size ElementCapacity) {
    this->allocator = AnAllocator;
    this->memory = AnAllocator->reserve((ElementLimit * sizeof(T)) + (ElementLimit / 8));
    this->components = slice(this->memory, 0, ElementLimit / 8);
    this->enabled.memory = slice(this->memory, ElementLimit * sizeof(T));
    this->resize(ElementCapacity);
    this->used = ElementCapacity;
  }
  T *add(bool Enabled = true) {
    T *result = nullptr;
    if (this->used < this->capacity) {
      if (this->nextFree) {
        result = this->nextFree;
        this->nextFree = *reinterpret_cast<T **>(this->nextFree);
      } else {
        result = offset<T>(this->components, this->used);
      }
    } else {
      this->resize(this->capacity * 2);
      result = offset<T>(this->components, this->used);
    }
    this->bits[this->used] = Enabled;
    this->used++;
  }
  void resize(size NewCapacity) {
    this->allocator->commit(this->components, this->capacity * sizeof(T),
                            sizeof(T) * NewCapacity);
    this->allocator->commit(this->enabled.memory, this->capacity / 8, NewCapacity / 8);
    this->capacity = NewCapacity;
  }
  void update(Arena &Scratchpad) {
    T *element = reinterpret_cast<T *>(this->components.address);
    auto i = nextSet(this->enabled,0);
    while(i < this->capacity){
      auto end = nextUnset(this->enabled,i);
      for (; i < end; i++) {
        if (this->enabled[i]) {
          element[i].update(i, Scratchpad);
        }
      }
      i = nextSet(this->enabled, end);
    }
  }
  ComponentPool& del(T *Element) {
    auto index = indexOf(this->components, Element);
    return this->del(index);
  }
  ComponentPool& del(size Index) {
      T* element = reinterpret_cast<T*>(this->components.address);
      *reinterpret_cast<T**>(element+Index) = this->nextFree;
      this->nextFree = element+Index;
      this->used--;
      this->enabled[Index] = false;
      return *this;
  }
  ComponentPool& setEnabled(T *Element, bool IsEnabled = true) {
    auto index = indexOf(this->components,Element);
    return this->setEnabled(index, IsEnabled);
  }
  ComponentPool& setEnabled(size Index, bool IsEnabled = true) {
      this->enabled.set(Index, IsEnabled);
      return *this;
  }
  // Memory pool, reserved a huge continues chunk, commit only used part.
  mem memory;  
  mem components; // The component data.
  // A dense bit-array which specifies if a component is enabled or
  // disabled/deleted.
  bits enabled;
  // Hole tracking by using a link list which use the deleted element memory to
  // store the next link. This need no additional memory but requires that the
  // element size is at least 8 bytes to store the pointer.
  T *nextFree = nullptr;
  size capacity = 0;
  size used = 0;
  Allocator *allocator;
};

// A container which use following points.
// - hold one POD type
// - can grow dynamically
// - is a continues array,
// - disallow holes
//    - can't use pointer of the elements because they are moved around
//    - need to swap element data
// - sort enabled/disabled elements
// - use less memory
// - very fast add/update, slow delete/setEnabled
template <class T> struct DenseComponentPool {
  void init(Allocator *AnAllocator, size ElementLimit, size ElementCapacity) {
    this->allocator = AnAllocator;
    this->memory = AnAllocator->reserve(ElementLimit * sizeof(T));
    this->resize(ElementCapacity);
    this->used = ElementCapacity;
  }
  T *add() {
    T *result = nullptr;
    if (this->used == this->capacity)
      this->resize(this->capacity * 2);
    result = offset<T>(this->memory,this->used);
    this->used++;
  }
  void resize(size NewCapacity) {
    this->allocator->commit(this->memory, this->capacity * sizeof(T),
                            sizeof(T) * NewCapacity);
    this->capacity = NewCapacity;
  }
  void update(Arena &Scratchpad) {
    T *element = reinterpret_cast<T *>(this->memory.address);
    for (auto i = 0; i < this->firstDisabled; ++i) {
      element[i].update(i, Scratchpad);
    }
  }
  DenseComponentPool& del(T *Element) {
    auto index = indexOf(this->memory,Element);
    return this->del(index);
  }
  DenseComponentPool& del(size Index) {
      T* element = reinterpret_cast<T*>(this->memory.address);
      this->used--;
      if (Index < this->firstDisabled) {
          this->firstDisabled--;
          element[Index] = element[this->firstDisabled];
          element[this->firstDisabled] = element[this->used];
      }
      else {
          element[Index] = element[this->used];
      }
      return *this;
  }
  DenseComponentPool& setEnabled(T* Element, bool IsEnabled = true) {
      auto index = indexOf(this->components, Element);
      return this->setEnabled(index, IsEnabled);
  }
  DenseComponentPool& setEnabled(size Index, bool IsEnabled = true) {
      T* element = reinterpret_cast<T*>(this->memory.address);
      if (Index > this->firstDisabled && IsEnabled) {
          swap<T>(this->memory, Index, this->firstDisabled);
          this->firstDisabled++;
      }
      if (Index <= this->firstDisabled && IsEnabled == false) {
          swap<T>(this->memory, Index, this->firstDisabled);
          this->firstDisabled--;
      }
      return *this;
  }
  void forEach(void(*Callback)(size Index, T& Element, void* Userdata), void* Userdata=nullptr, bool All=false){
      T* element = reinterpret_cast<T*>(this->memory.address);
      for (auto i = 0; i < this->firstDisabled; ++i) {
          Callback(i, element[i], Userdata);
      }
      if (All) {
          for (auto i = this->firstDisabled; i < this->used; ++i) {
              Callback(i, element[i], Userdata);
          }
      }
  }
  // Memory pool, reserved a huge continues chunk, commit only used part.
  mem memory;
  size firstDisabled = 0;
  size capacity = 0;
  size used = 0;
  Allocator *allocator;
};

struct Light {
  f32 r, g, b;
  f32 lumen, angle;

  void update(size Index, Arena &Scratchpad) {
    // Do some renger magic.
  }
};

// A component which will call a function and pass user data to it.
struct ScriptActor {
  typedef void (*ScriptFunction)(size, Arena &, ptr);
  ScriptFunction action;
  ptr userdata;

  void update(size Index, Arena &Scratchpad) {
    this->action(Index, Scratchpad, this->userdata);
  }
};

timeval currentGameDayTime = 0_am;

void NightLight(size Index, Arena &Scratchpad, ptr Userdata) {
  constexpr timeval nightTime = 8_pm;
  constexpr timeval sleepTime = 10_pm;
  Light *light = reinterpret_cast<Light *>(Userdata);
  if (currentGameDayTime > nightTime && currentGameDayTime < sleepTime) {
    light->lumen = 400;
  } else {
    light->lumen = 0;
  }
}

int main() {
  // Prepare an allocator tree. The tree will be pretty slow compared to other
  // code. The reason are virtual functions and system calls. It's fine because
  // the functions are called during the start and in background threads. The
  // Heap is the root, all other allocators can be mixed and matched as trunk.
  // In the hot loop the arenas will take place and are the branches. They take
  // care of the lifetime.

  Heap osAllocator;                           // OS API wrapper
  AllocatorOwnership trackOwnershipAllocator; // Remember the ownage of memory.
  // Allocations can go wrong and this information is only accessible from a
  // higher level.
  trackOwnershipAllocator.embed(&osAllocator);
  // With a Prometheus exporter you can track the data over time, compare and
  // profile.
  AllocatorDiagnostic diagnosticAllocator;
  diagnosticAllocator.embed(&trackOwnershipAllocator);
  // Zero all commited, allocated and mapped memory.
  AllocatorEvents zeroAllocator;
  zeroAllocator.onPostCommit = [](mem &MemoryBlock) {};
  zeroAllocator.onPostAllocate = [](mem &MemoryBlock) {};
  zeroAllocator.onPostMap = [](memmap &MemoryBlock) {};
  zeroAllocator.embed(&diagnosticAllocator);
  Allocator *myAllocator = &zeroAllocator;

  // Generate a log buffer which maps the log twice in a row.
  // Writing beyond logBuffer will continue in the mapped area which redirects
  // to the beginning of the logBuffer. The memory controller takes care of the
  // complicated part of preventing an access violation and split read/write
  // into pieces.
  auto logRingBuffer = myAllocator->map(20_mb);
  auto logBuffer = myAllocator->mapView(logRingBuffer, logRingBuffer.bytes / 2);
  myAllocator->mapView(logRingBuffer, logBuffer.bytes, logBuffer.address);
  // Also usefull for job queues and message queues.

  // Request the current virtual and physical memory to partition the memory.
  // Cache the values somewhere if you want to use the information in the hot
  // loop. This are indirect system calls which can hurt the CPU utilization.
  SystemMemoryInformation memoryInfos;
  getSystemMemoryInformation(memoryInfos);
  auto pageSize = getAllocationGranularity();
  auto mapSize = getMapGranularity();

  // A stack with a fixed size. No longer used data in the middle of the stack
  // are dead waste. Use multiple arenas to put overlapping lifetimes into the
  // same arena and waste less memory. Prefere push all objects and then use a
  // clear instead of pop everyone. This improves performance. You also need to
  // know the bytesize of the top object if you want to pop it because the
  // areana doesn't care about objects.
  Arena engineMemory;
  engineMemory.memory = myAllocator->allocate(50_mb);

  // Like a DenseArena except it can stretch to the reservation limit.
  // If an allocation need to call a resize then it will be slower and the
  // base-line is also slower because of the additional check. This should be
  // avoided in the hot loop but fine for background threads.
  // StretchableArena ecsWorld;
  // ecsWorld.init(myAllocator, 2_gb);

  // The frame arena keeps all objects which live just one frame.
  Arena frame;
  frame.memory = myAllocator->allocate(50_mb);
  
  CacheLayout cache;
  auto bytes = CacheLayout::estimateScratchpad();
  if (bytes < frame.memory.bytes) {      
      auto cacheLayout = engineMemory.push(cache.detect(frame).data.bytes);
      copy(cache.data, cacheLayout);      
      cache.loadFrom(cacheLayout);
  }  

  ComponentPool<Light> lights;
  lights.init(myAllocator, 100000, 1000);
  DenseComponentPool<ScriptActor> scripts;
  scripts.init(myAllocator, 100000, 1000);
  scripts.forEach([](size Index, ScriptActor& Script, void* Userdata) {
      Script.action = NightLight;
      Script.userdata = &reinterpret_cast<Light*>(Userdata)[Index];},
      lights.components.address, true);
  // Put some holes into the pools.
  lights.setEnabled(1).setEnabled(9).setEnabled(17).setEnabled(25).setEnabled(33);
  scripts.setEnabled(1).setEnabled(9).setEnabled(17).setEnabled(25).setEnabled(33);
  for (;;) {
    frame.clear();// Reset the arena to the beginning instead of popping all
                  // the objects.
    scripts.update(frame);
    lights.update(frame);
    currentGameDayTime = (currentGameDayTime + 1_h) % 1_d;
  }
}