#include "RadonFramework/Core/Common/StringCache.hpp"
#include <cstring>
#include "RadonFramework/Collections/Array.hpp"
#include "RadonFramework/Core/Pattern/Singleton.hpp"
#include "RadonFramework/Core/Types/AtomicPointer.hpp"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;

class Cache
{
public:
  Cache(Size buckets) : Hashes(buckets) {}
  const char*** Values;
  Array<UInt32> Hashes;
};

AtomicPointer<Cache> CACHE = nullptr;

UInt32 CalculateFNV(const char* str)
{
  const Size length = strlen(str) + 1;
  UInt32 hash = 2166136261u;
  for(Size i = 0; i < length; ++i)
  {
    hash ^= *str++;
    hash *= 16777619u;
  }

  return hash;
}

const char* StringCache::Find(const String& Value)
{
  const char* result = nullptr;
  if(CACHE != nullptr && CACHE->Values != nullptr)
  {
    Size i = 0;
    const char*** stringList = CACHE->Values;
    UInt32 valueHash = CalculateFNV(Value.c_str());
    while(*stringList != nullptr)
    {
      const char** listEntry = *stringList;
      while((*listEntry) != nullptr)
      {
        UInt32 hash = CACHE->Hashes(i);
        if(valueHash == hash)
        {
          result = *listEntry;
          break;
        }

        if(Value == String::UnsafeStringCreation(*listEntry))
        {
          CACHE->Hashes(i) = valueHash;
          result = *listEntry;
          break;
        }

        ++listEntry;

        ++i;
      }

      if(result == nullptr)
      {
        ++stringList;
      }
      else
      {
        break;
      }
    }
  }
  return result;
}

Size GetCacheElementAmount(const char*** values)
{
  Size result = 0;
  if(values != nullptr)
  {
    const char*** stringList = values;
    while(*stringList != nullptr)
    {
      const char** listEntry = *stringList;
      while(*listEntry != nullptr)
      {
        ++listEntry;
        ++result;
      }
      ++stringList;
    }
  }
  return result;
}

void StringCache::Exchange(const char*** newValues)
{
  Size elementCount = GetCacheElementAmount(newValues);
  AutoPointer<Cache> newCache(new Cache(elementCount));
  newCache->Values = newValues;

  for(;;)
  {
    Cache* oldCache = CACHE;

    if(CACHE.CompareAndExchange(oldCache, newCache.Get()) == oldCache)
    {
      newCache.Release();
      newCache.Reset(oldCache);
      break;
    }
  }
}