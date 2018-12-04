#ifndef RF_COLLECTIONS_COMMANDBUCKET_HPP
#define RF_COLLECTIONS_COMMANDBUCKET_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Collections {

template<typename K=RF_Type::UInt32>
class CommandBucket
{
public:
    typedef K KeyType;
    template<class T>
    T* AddCommand(const KeyType Key, const RF_Type::Size AdditionalCommandMemory = 0);
    template<class T, class CMD>
    T* AppendCommand(const CMD& Command, const RF_Type::Size AdditionalCommandMemory = 0);
    template<class T>
    RF_Type::UInt8* GetCommandMemory(const T& Command);
    template<class T>
    RF_Type::Size GetCommandMemorySize(const T& Command);
    void Submit();
protected:
    struct CommandHeader
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8>* Child;
        void(*DispatchFunction)(void* Command);
        RF_Type::Size AdditionalCommandMemory;
    };
    RF_Collect::List<KeyType> m_Keys;
    RF_Collect::List<RF_Mem::AutoPointerArray<RF_Type::UInt8>> m_Commands;
    RF_Collect::List<RF_Mem::AutoPointerArray<RF_Type::UInt8>> m_ManagedSubCommands;
    void ExecuteCommandChain(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Command);
};

template<typename K/*=RF_Type::UInt32*/>
template<class T, class CMD>
T* CommandBucket<K>::AppendCommand(const CMD& Command, 
    const RF_Type::Size AdditionalCommandMemory /*= 0*/)
{
    static_assert(std::is_pointer<CMD>::value == false, "CMD must be an object reference!");
    static_assert(std::is_pod<T>::value == true, "T have to be a POD structure!");

    // find tail
    CommandHeader* tail = reinterpret_cast<CommandHeader*>(const_cast<CMD*>(&Command)) - 1;
    while(tail->Child != nullptr)
    {
        tail = reinterpret_cast<CommandHeader*>(tail->Child->Get());
    }

    // add to tail
    RF_Type::Size bytes = sizeof(T) + sizeof(CommandHeader) + AdditionalCommandMemory;
    m_ManagedSubCommands.AddLast(RF_Mem::AutoPointerArray<RF_Type::UInt8>(bytes));
    CommandHeader* header = reinterpret_cast<CommandHeader*>(m_ManagedSubCommands.Last()->Get());
    header->Child = nullptr;
    header->DispatchFunction = T::DispatchFunction;
    header->AdditionalCommandMemory = AdditionalCommandMemory;
    tail->Child = m_ManagedSubCommands.Last();
    return reinterpret_cast<T*>(header + 1);
}

template<typename K/*=RF_Type::UInt32*/>
template<class T>
T* CommandBucket<K>::AddCommand(const KeyType Key, 
    const RF_Type::Size AdditionalCommandMemory)
{
    static_assert(std::is_pod<T>::value == true, "T have to be a POD structure!");
    
    RF_Type::Size bytes = sizeof(T) + sizeof(CommandHeader) + AdditionalCommandMemory;
    m_Commands.AddLast(RF_Mem::AutoPointerArray<RF_Type::UInt8>(bytes));
    m_Keys.AddLast(Key);
    CommandHeader* header = reinterpret_cast<CommandHeader*>(m_Commands.Last()->Get());
    header->Child = nullptr;
    header->DispatchFunction = T::DispatchFunction;
    header->AdditionalCommandMemory = AdditionalCommandMemory;
    return reinterpret_cast<T*>(header + 1);
}

template<typename K/*=RF_Type::UInt32*/>
template<class T>
RF_Type::Size CommandBucket<K>::GetCommandMemorySize(const T& Command)
{
    const CommandHeader* header = reinterpret_cast<const CommandHeader*>(&Command)-1;
    return header->AdditionalCommandMemory;
}

template<typename K/*=RF_Type::UInt32*/>
template<class T>
RF_Type::UInt8* CommandBucket<K>::GetCommandMemory(const T& Command)
{
    return reinterpret_cast<RF_Type::UInt8*>(const_cast<T*>(&Command)+1);
}

template<typename K/*=RF_Type::UInt32*/>
void CommandBucket<K>::Submit()
{
    for (RF_Type::Size i = 0; i < m_Commands.Count(); ++i)
    {
        ExecuteCommandChain(m_Commands[i]);
    } 
    m_Commands.Clear();
    m_ManagedSubCommands.Clear();
}

template<typename K/*=RF_Type::UInt32*/>
void CommandBucket<K>::ExecuteCommandChain(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Command)
{
    CommandHeader* header = reinterpret_cast<CommandHeader*>(Command.Get());
    header->DispatchFunction(reinterpret_cast<void*>(header+1));
    
    if(header->Child != nullptr)
    {
        ExecuteCommandChain(*header->Child);
    }
}

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_COMMANDBUCKET_HPP
