export module rf.core.patterns:servicelocator;
import rf.core.types;
import rf.core.memory;
import rf.core.collections;

export namespace rf {
class ServiceLocator {
public:
  ServiceLocator(AllocatorAdapter LongLiving, StackAdapter Stack);
  ~ServiceLocator();  
  void initialize();
  void free();

  template<class T>
  bool add(const strview& Name);
  template<class T>
  T* get(const strview& Name);
  template<class T>
  bool remove(const strview& Name);
protected:
  AllocatorAdapter allocator;
  StackAdapter stack;
  //Hashlist<u32,AllocatorAdapter> ids;
  //Pool<Service> services;
  
};
} // namespace rf