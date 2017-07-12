#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/MemoryProtocolService.hpp"
#include "RadonFramework/IO/Resource.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/IO/MemoryStream.hpp"

namespace RadonFramework::Core::Idioms {

template<class T>
class PImpl<T>::Data
{
public:
    Data()
    :m_StreamLookup(1024)
    {

    }

    RF_Type::UInt32 CalculateFNV(const RF_Type::String& Value)
    {
        const RF_Type::Size length = Value.Size() + 1;
        RF_Type::UInt32 hash = 2166136261u;
        for(RF_Type::Size i = 0; i < length; ++i)
        {
            hash ^= Value[i];
            hash *= 16777619u;
        }
        return hash;
    }

    RF_Collect::HashList m_StreamLookup;
    RF_Collect::AutoVector<RF_IO::MemoryStream> m_MemoryStreams;
};

}

namespace RadonFramework::IO {

MemoryProtocolService::MemoryProtocolService(const RF_Type::String &Name)
:ProtocolService(Name)
{
}

void MemoryProtocolService::FreeInterface(const Uri& URI)
{
    RF_Collect::HashList::KeyType key = 0;
    key = m_PImpl->CalculateFNV(URI.Path());
    void* value = 0;
    if(m_PImpl->m_StreamLookup.Get(key, value))
    {
        for(decltype(m_PImpl->m_MemoryStreams)::Iterator it = m_PImpl->m_MemoryStreams.Begin();
            it != m_PImpl->m_MemoryStreams.End(); ++it)
        {
            if(*it == value)
            {
                m_PImpl->m_MemoryStreams.Erase(it);
                break;
            }
        }
        m_PImpl->m_StreamLookup.Erase(key);
    }
}

RF_Type::Bool MemoryProtocolService::Exists(const Uri& URI)
{
    RF_Collect::HashList::KeyType key = 0;
    key = m_PImpl->CalculateFNV(URI.Path());
    return m_PImpl->m_StreamLookup.ContainsKey(key);
}

Stream* MemoryProtocolService::GenerateInterface(const Uri& URI)
{
    Stream* result;
    RF_Collect::HashList::KeyType key = 0;
    key = m_PImpl->CalculateFNV(URI.Path());
    void* value = 0;
    if(m_PImpl->m_StreamLookup.Get(key, value))
    {
        result = reinterpret_cast<Stream*>(value);
    }
    else
    {
        auto stream = RF_Mem::AutoPointer<MemoryStream>(new MemoryStream);
        result = stream.Get();
        m_PImpl->m_StreamLookup.Add(key, result);
        m_PImpl->m_MemoryStreams.PushBack(stream);        
    }
    return result;
}

}