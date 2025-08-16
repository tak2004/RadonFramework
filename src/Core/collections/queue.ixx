export module rf.core.collections:queue;
import rf.core.types;
import rf.core.cpu;
import rf.core.os;

export namespace rf {
/** @brief This class is can grow and shrink.
 *
 * The Queue class supports the first-in-first-out(FIFO)
 * model for adding and removing elements.
 * It's implemented as multiple producer(MP) and multiple consumer(MC)
 * container. If you have single producer(SP)-MC, MP-single consumer(SC) or
 * SP-MC then look for the specialized implementation.
 */
template <typename T> class Queue {
public:
  Queue();
  Queue(const Queue &Copy) = delete;
  Queue &operator=(const Queue &Other) = delete;
  ~Queue();

  void setup(const size AvailableLogicalProcessor, const size ReserveElements);
  /// Removes all objects from the Queue<T>.
  void clear();
  /// Removes and assign the object at the beginning of the Queue<T> to Item.
  bool dequeue(T &Item);
  /// Removes the object at the beginning of the Queue<T>.
  bool dequeue();
  /// Adds a copy of an object to the end of the Queue<T>.
  void enqueue(const T &Item);
  /// Adds a copy of an object to the end of the Queue<T>.
  void enqueue(T &Item);
  bool isEmpty() const;

private:
  struct LPInfo {
    AtomicUInt32 head;
    AtomicUInt32 tail;
    LPInfo() : head(limit<u32>::max), tail(limit<u32>::max) {}
  };
  // Used as ring buffer.
  T *array;
  size arrayCount;
  // An information set per logical processor.
  LPInfo *lPInfos;
  size lPInfoCount;

  AtomicUInt32 head;
  AtomicUInt32 tail;
  AtomicUInt32 lastHead;
  AtomicUInt32 lastTail;
};

template <typename T>
Queue<T>::Queue()
    : tail(0), head(0), lastHead(0), lastTail(0), lPInfoCount(0),
      lPInfos(nullptr), array(nullptr), arrayCount(0) {}

template <typename T>
void Queue<T>::setup(const size AvailableLogicalProcessor,
                     const size ReserveElements) {
  lPInfoCount = AvailableLogicalProcessor;
  lPInfos = new LPInfo[lPInfoCount];
  array = new T[ReserveElements];
  arrayCount = ReserveElements;
}

template <typename T> Queue<T>::~Queue() {
  delete[] lPInfos;
  delete[] array;
}

template <typename T> void Queue<T>::enqueue(const T &Item) {
  auto lpId = getCurrentUniqueProcessorNumber();
  lPInfos[lpId].head = head;
  lPInfos[lpId].head = head.FetchAndAdd(1);

  while (lPInfos[lpId].head >= lastTail + arrayCount) {
    u32 min = tail;
    for (size i = 0; i < lPInfoCount; ++i) {
      u32 tmp = lPInfos[i].tail;
      memoryFence();
      if (tmp < min) {
        min = tmp;
      }
    }
    lastTail = min;

    if (lPInfos[lpId].head < lastTail + arrayCount) {
      break;
    }
    shortestPause();
  }
  array[lPInfos[lpId].head & (arrayCount - 1)] = Item;
  lPInfos[lpId].head = limit<u32>::max;
}

template <typename T> void Queue<T>::enqueue(T &Item) {
  auto lpId = getCurrentUniqueProcessorNumber();
  lPInfos[lpId].head = head;
  lPInfos[lpId].head = head.fetchAndAdd(1);

  while (lPInfos[lpId].head >= lastTail + arrayCount) {
    u32 min = tail;

    for (size i = 0; i < lPInfoCount; ++i) {
      u32 tmp = lPInfos[i].tail;
      memoryFence();
      if (tmp < min) {
        min = tmp;
      }
    }
    lastTail = min;

    if (lPInfos[lpId].head < lastTail + arrayCount) {
      break;
    }
    shortestPause();
  }
  array[lPInfos[lpId].head & (arrayCount - 1)] = Item;
  lPInfos[lpId].head = limit<u32>::max;
}

template <typename T> bool Queue<T>::dequeue(T &Item) {
  bool result = false;
  auto lpId = getCurrentUniqueProcessorNumber();

  if (lPInfos[lpId].tail == limit<u32>::max) {
    lPInfos[lpId].tail = tail;
    lPInfos[lpId].tail = tail.fetchAndAdd(1);
  }

  if (lPInfos[lpId].tail >= lastHead) {
    u32 min = head;
    for (size i = 0; i < lPInfoCount; ++i) {
      u32 tmp = lPInfos[i].head;
      memoryFence();
      if (tmp < min) {
        min = tmp;
      }
    }
    lastHead = min;
  }

  if (lPInfos[lpId].tail < lastHead) {
    Item = array[lPInfos[lpId].tail & (arrayCount - 1)];
    result = true;
    lPInfos[lpId].tail = limit<u32>::max;
  }
  return result;
}

template <typename T> bool Queue<T>::dequeue() {
  bool result = false;
  auto lpId = getCurrentUniqueProcessorNumber();

  if (lPInfos[lpId].tail == limit<u32>::max) {
    lPInfos[lpId].tail = tail;
    lPInfos[lpId].tail = tail.fetchAndAdd(1);
  }

  if (lPInfos[lpId].tail >= lastHead) {
    u32 min = head;
    for (size i = 0; i < lPInfoCount; ++i) {
      u32 tmp = lPInfos[i].head;
      memoryFence();
      if (tmp < min) {
        min = tmp;
      }
    }
    lastHead = min;
  }

  if (lPInfos[lpId].tail < lastHead) {
    result = true;
    lPInfos[lpId].tail = limit<u32>::max;
  }
  return result;
}

template <typename T> void Queue<T>::clear() {
  while (dequeue()) {
  }
}

template <typename T> bool Queue<T>::isEmpty() const {
  return lastHead < tail;
}

} // namespace rf