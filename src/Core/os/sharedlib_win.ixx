module;
#include <Windows.h>
export module rf.core.os:sharedlib_win;
import :sharedlib;

export namespace rf {
bool DynamicLibrary::load(const strview &Filepath) {
  bool result = false;
  if (this->handle == nullptr) {
    HMODULE dl = LoadLibrary(static_cast<LPCSTR>(Filepath.address));
    if (dl != NULL) {
      // this->name = Filepath;
      this->handle = static_cast<ptr>(dl);
      result = true;
    }
  }
  return result;
}

bool DynamicLibrary::unload() {
  bool result = true;
  if (this->handle) {
    result = FreeLibrary(*static_cast<HMODULE *>(this->handle)) != NULL;
  }
  return result;
}

ptr DynamicLibrary::getFunctionAddress(const strview &Name) {
  return reinterpret_cast<ptr>(
      GetProcAddress(reinterpret_cast<HMODULE>(this->handle),
                     reinterpret_cast<LPCSTR>(Name.address)));
}

} // namespace rf