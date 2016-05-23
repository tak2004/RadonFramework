#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/FileProtocolService.hpp"
#include "RadonFramework/IO/Resource.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"
#include "RadonFramework/IO/FileStream.hpp"

namespace RadonFramework { namespace Core { namespace Idioms {

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
    RF_Collect::AutoVector<RF_IO::FileStream> m_FileStreams;
};

} } }

namespace RadonFramework { namespace IO {

FileProtocolService::FileProtocolService(const RF_Type::String &Name)
:ProtocolService(Name)
{
}

void FileProtocolService::FreeInterface(const Uri& URI)
{
    RF_Collect::HashList::KeyType key = 0;
    key = m_PImpl->CalculateFNV(URI.Path());
    void* value = 0;
    if(m_PImpl->m_StreamLookup.Get(key, value))
    {
        for(decltype(m_PImpl->m_FileStreams)::Iterator it = m_PImpl->m_FileStreams.Begin();
        it != m_PImpl->m_FileStreams.End(); ++it)
        {
            if(*it == value)
            {
                m_PImpl->m_FileStreams.Erase(it);
                break;
            }
        }
        m_PImpl->m_StreamLookup.Erase(key);
    }
}

RF_Type::Bool FileProtocolService::Exists(const Uri& URI)
{
    RF_IO::File file;
    file.SetLocation(URI);
    return file.Exists();
}

Stream* FileProtocolService::GenerateInterface(const Uri& URI)
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
        auto stream = RF_Mem::AutoPointer<FileStream>(new FileStream);
        RF_IO::Uri fileSystem(URI.OriginalString().Replace(URI.Scheme(), RF_Type::String("file")));
        stream->Open(fileSystem, RF_SysFile::FileAccessMode::ReadWrite, RF_SysFile::FileAccessPriority::ReadThroughput);
        result = stream.Get();
        m_PImpl->m_StreamLookup.Add(key, result);
        m_PImpl->m_FileStreams.PushBack(stream);
    }
    return result;
}

} }