module;
#include <Windows.h>
#include <processthreadsapi.h>
export module rf.core.cpu:infos_vs;
import rf.core.types;
import :infos;

export namespace rf {
u32 getAvailableLogicalProcessorCount() {
  static u32 NumberOfProcessors = 0;
  if (NumberOfProcessors == 0) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    NumberOfProcessors = sysInfo.dwNumberOfProcessors;
  }
  return NumberOfProcessors;
}

u32 getCurrentProcessorNumber() {
  u32 result;
  result = ::GetCurrentProcessorNumber();
  return result;
}

u32 getCurrentUniqueProcessorNumber() {
  static u32 MAX_GROUP_COUNT = 64;
  u32 result;
  PROCESSOR_NUMBER value;
  ::GetCurrentProcessorNumberEx(&value);
  result = value.Group * MAX_GROUP_COUNT + value.Number;
  return result;
}

size CacheLayout::estimateScratchpad() {
  DWORD buffer = 0;
  GetLogicalProcessorInformationEx(
      LOGICAL_PROCESSOR_RELATIONSHIP::RelationCache, nullptr, &buffer);
  size bytes = 0;
  auto elements = buffer / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX);
  bytes += sizeof(CacheInfo)*elements*2;
  bytes += sizeof(CacheStack)* getAvailableLogicalProcessorCount();
  bytes += sizeof(CacheLayout::View);
  bytes += buffer;
  return bytes;
}

CacheLayout &CacheLayout::detect(StackAdapter& Scratchpad) {
    DWORD bufferSize = 0;
    GetLogicalProcessorInformationEx(
        RelationCache, nullptr, &bufferSize);
    // windows cache infos
    auto buffer = Scratchpad.push(bufferSize);
    if (GetLogicalProcessorInformationEx(
        RelationCache, reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.address), reinterpret_cast<PDWORD>(& buffer.bytes))) {
        // Count the elements.
        size elements = 0;
        auto ptr = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.address);
        while (bufferSize > 0) {
            elements++;
            bufferSize -= ptr->Size;
            ptr = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(reinterpret_cast<u8*>(ptr) + ptr->Size);
        }
        // temporary cache infos
        auto tmpCacheMemory = Scratchpad.push(elements * sizeof(CacheInfo));
        auto caches = reinterpret_cast<CacheInfo*>(tmpCacheMemory.address);
        auto usedCaches = 0;
        // view
        auto data = Scratchpad.push(sizeof(CacheLayout::View));
        auto view = reinterpret_cast<CacheLayout::View*>(data.address);
        view->lps = getAvailableLogicalProcessorCount();  
        view->caches = 0;
        // stack infos
        auto stackMemory = Scratchpad.push(view->lps * sizeof(CacheStack));
        this->lpCacheMask = reinterpret_cast<CacheStack*>(stackMemory.address);

        ptr = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.address);
        CacheInfo tmp;
        for (auto i = 0,j=0; i < elements; ++i) {
            if (ptr->Relationship == RelationCache) {
                tmp.level = ptr->Cache.Level;
                tmp.bytes = ptr->Cache.CacheSize;
                tmp.lineBytes = ptr->Cache.LineSize;
                switch (ptr->Cache.Associativity)
                {
                case 2:
                    tmp.associativity = CacheAssociativity::_2WaySetAssociative;
                    break;
                case 4:
                    tmp.associativity = CacheAssociativity::_4WaySetAssociative;
                    break;
                case 6:
                    tmp.associativity = CacheAssociativity::_6WaySetAssociative;
                    break;
                case 8:
                    tmp.associativity = CacheAssociativity::_8WaySetAssociative;
                    break;
                case 12:
                    tmp.associativity = CacheAssociativity::_12WaySetAssociative;
                    break;
                case 16:
                    tmp.associativity = CacheAssociativity::_16WaySetAssociative;
                    break;
                case 24:
                    tmp.associativity = CacheAssociativity::_24WaySetAssociative;
                    break;
                case 255:
                    tmp.associativity = CacheAssociativity::FullyAssociative;
                    break;
                default:
                    tmp.associativity = CacheAssociativity::Other;
                    break;
                }
                switch (ptr->Cache.Type)
                {
                case CacheUnified:
                    tmp.usedAs = CacheUseCase::CodeAndData;
                    break;
                case CacheData:
                    tmp.usedAs = CacheUseCase::Data;
                    break;
                case CacheInstruction:
                    tmp.usedAs = CacheUseCase::Code;
                    break;
                case CacheTrace:
                    tmp.usedAs = CacheUseCase::CodeAndDataTLB;
                    break;
                default:
                    tmp.usedAs = CacheUseCase::Other;
                }
                for (j = 0;j < usedCaches;++j) {
                    if (caches[j].associativity == tmp.associativity &&
                        caches[j].bytes == tmp.bytes &&
                        caches[j].level == tmp.level &&
                        caches[j].lineBytes == tmp.lineBytes &&
                        caches[j].usedAs == tmp.usedAs) {
                        break;
                    }
                }
                if (j == usedCaches) {
                    caches[j] = tmp;
                    usedCaches++;
                }                
                size coreOffset=(ptr->Cache.GroupCount-1) * 64;
                for (auto b = 0; b < 64; ++b) {
                    if (ptr->Cache.GroupMask.Mask & (1 << b)) {
                        this->lpCacheMask[coreOffset + b].mask[j]=true;
                    }
                }                
                ptr = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(reinterpret_cast<u8*>(ptr) + ptr->Size);
            }
        }
        view->caches = usedCaches;
        // final cachinfos
        auto cacheMemory = Scratchpad.push(view->caches* sizeof(CacheInfo));
        this->cacheInfos = reinterpret_cast<CacheInfo*>(cacheMemory.address);
        for (auto i = 0, j = 0; i < view->caches; ++i) this->cacheInfos[i] = caches[i];
        this->data.address = data.address;
        this->data.bytes = (reinterpret_cast<ptrdiff>(cacheMemory.address)-reinterpret_cast<ptrdiff>(data.address)) + cacheMemory.bytes;
        this->view = *view;
    }
  return *this; 
}

} // namespace rf