export module rf.core.os:sharedlib;
import rf.core.types;

export namespace rf {

class DynamicLibrary {
public:
  DynamicLibrary();
  DynamicLibrary(DynamicLibrary &&Move);

  /**
   * @brief Cleanup internal data.
   *
   * If you want to unload a library then you have to explicit call
   * the static Unload method because the destructor only clean up
   * internal data but don't unload the library.
   */
  ~DynamicLibrary();

  bool load(const strview &Filepath);

  bool unload();

  ptr getFunctionAddress(const strview &Name);

  /**
   * @brief Return false if the object represent no library.
   *
   * This function return false if the library wasn't loaded.
   */
  operator bool();

  strview getName() const;

  DynamicLibrary &operator=(DynamicLibrary &Move);
  DynamicLibrary &operator=(DynamicLibrary &&Move);

  DynamicLibrary(const DynamicLibrary &NoCopy) = delete;
  DynamicLibrary &operator=(const DynamicLibrary &NoCopy) = delete;

private:
  ptr handle;
  str name;
};

DynamicLibrary::DynamicLibrary() : handle(nullptr) {}

DynamicLibrary::DynamicLibrary(DynamicLibrary &&Move) { *this = Move; }

DynamicLibrary::~DynamicLibrary() { this->unload(); }

DynamicLibrary::operator bool() { return this->handle != nullptr; }

strview DynamicLibrary::getName() const {
  strview result;
  result.address = reinterpret_cast<ptr>(this->name.c_str());
  result.bytes = this->name.bytes();
  return result;
}

DynamicLibrary &DynamicLibrary::operator=(DynamicLibrary &Move) {
  this->unload();
  this->handle = Move.handle;
  this->name = Move.name;
  Move.handle = nullptr;
  return *this;
}

DynamicLibrary &DynamicLibrary::operator=(DynamicLibrary &&Move) {
  *this = Move;
  return *this;
}

} // namespace rf