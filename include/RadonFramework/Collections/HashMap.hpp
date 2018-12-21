#ifndef RF_HASHMAP_HPP
#define RF_HASHMAP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#pragma warning(disable : 4996)  // vc++ raise a security warning because of
                                 // uninitialized_copy
#include <RadonFramework/backend/google/dense_hash_map>
#include <RadonFramework/backend/google/sparse_hash_map>

using SPARSEHASH_HASH;
// using ext::hash;
// using __gnu_cxx::hash;

namespace RadonFramework::Collections
{
template <class A, class B, class C, class D>
struct HashMapMemoryEfficient
{
  using Type = google::sparse_hash_map<A, B, C, D>;
};

template <class A, class B, class C, class D>
struct HashMapOperationEfficient
{
  using Type = google::dense_hash_map<A, B, C, D>;
};

template <class KEYTYPE,
          class VALUETYPE,
          class HASHFCN = SPARSEHASH_HASH<KEYTYPE>,
          class EQUALKEY = STL_NAMESPACE::equal_to<KEYTYPE>,
          typename LOGIC =
              HashMapMemoryEfficient<KEYTYPE, VALUETYPE, HASHFCN, EQUALKEY>>
class HashMap
{
private:
  using hm = typename LOGIC::Type;

public:
  using Iterator = typename hm::iterator;
  using ConstIterator = typename hm::const_iterator;
  void Clear() { m_HashMap.clear(); }
  RF_Type::Bool ContainsKey(KEYTYPE Key) const
  {
    return m_HashMap.find(Key) != m_HashMap.end();
  }
  RF_Type::UInt32 Size() { return m_HashMap.size(); }
  VALUETYPE& operator[](const KEYTYPE& Key) { return m_HashMap[Key]; }
  void Erase(const KEYTYPE& Key) { m_HashMap.erase(Key); }
  void Erase(Iterator Pos) { m_HashMap.erase(Pos); }
  Iterator Begin() { return m_HashMap.begin(); }
  ConstIterator Find(const KEYTYPE& Key) const { return m_HashMap.find(Key); }
  Iterator End() { return m_HashMap.end(); }
  void SetDeletedKey(const KEYTYPE& key) { m_HashMap.set_deleted_key(key); }
  void SetEmptyKey(const KEYTYPE& key) { m_HashMap.set_empty_key(key); }

protected:
  hm m_HashMap;
};

template <class K, class T>
using SparseHashMap =
    HashMap<K,
            T,
            SPARSEHASH_HASH<K>,
            STL_NAMESPACE::equal_to<K>,
            HashMapOperationEfficient<K,
                                      T,
                                      SPARSEHASH_HASH<K>,
                                      STL_NAMESPACE::equal_to<K>>>;

}  // namespace RadonFramework::Collections

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif
