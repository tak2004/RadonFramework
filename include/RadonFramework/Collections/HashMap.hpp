#ifndef RF_HASHMAP_HPP
#define RF_HASHMAP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#pragma warning(disable : 4996) // vc++ raise a security warning because of uninitialized_copy
#include <RadonFramework/backend/google/sparse_hash_map>
#include <RadonFramework/backend/google/dense_hash_map>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

using SPARSEHASH_HASH;
//using ext::hash;
//using __gnu_cxx::hash;

namespace RadonFramework
{
    namespace Collections
    {
        template <class A, class B, class C, class D>
        struct HashMapMemoryEfficient
        {
            typedef google::sparse_hash_map<A, B, C, D> Type;
        };

        template <class A, class B, class C, class D>
        struct HashMapOperationEfficient
        {
            typedef google::dense_hash_map<A, B, C, D> Type;
        };

        template <class KEYTYPE, class VALUETYPE, class HASHFCN = SPARSEHASH_HASH<KEYTYPE>,
                  class EQUALKEY = STL_NAMESPACE::equal_to<KEYTYPE>, typename LOGIC = HashMapMemoryEfficient<KEYTYPE, VALUETYPE, HASHFCN, EQUALKEY> >
        class HashMap
        {
            private:
                typedef typename LOGIC::Type hm;
            public:
                typedef typename hm::iterator Iterator;
                void Clear(){
                    m_HashMap.clear();
                }
                RadonFramework::Core::Types::Bool ContainsKey(KEYTYPE Key) const{
                    return m_HashMap.find(Key)!=m_HashMap.end();
                }
                RadonFramework::Core::Types::UInt32 Size(){
                    return m_HashMap.size();
                }
                VALUETYPE& operator[](const KEYTYPE& Key){
                    return m_HashMap[Key];
                }
                void Erase(const KEYTYPE &Key){
                    m_HashMap.erase(Key);
                }
                void Erase(Iterator Pos){
                    m_HashMap.erase(Pos);
                }
                Iterator Begin(){
                    return m_HashMap.begin();
                }
                Iterator End(){
                    return m_HashMap.end();
                }
                void SetDeletedKey(const KEYTYPE& key)
                {
                     m_HashMap.set_deleted_key(key);
                }
                void SetEmptyKey(const KEYTYPE& key)
                {
                    m_HashMap.set_empty_key(key);
                }
            protected:
                hm m_HashMap;
        };
    }
}

#endif
