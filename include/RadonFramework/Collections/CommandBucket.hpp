#ifndef RF_COLLECTIONS_COMMANDBUCKET_HPP
#define RF_COLLECTIONS_COMMANDBUCKET_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Collections {

template<typename K=RF_Type::UInt32>
class CommandBucket
{
public:
    typedef K KeyType;
    template<class T>
    T* AddCommand(const KeyType Key, const RF_Type::Size NeededMemorySize);
protected:
    
};

template<typename K>
template<class T>
T* CommandBucket<K>::AddCommand(const KeyType Key, const RF_Type::Size NeededMemorySize)
{

}

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_COMMANDBUCKET_HPP
