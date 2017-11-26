#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Settings.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/Collections/Pair.hpp"
#include "RadonFramework/IO/Directory.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/Collections/HashList.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"
#include "RadonFramework/Math/Hash/Hash32.hpp"

using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Idioms;
using namespace RadonFramework::Core::Policies;
using namespace RadonFramework::IO;
using namespace RadonFramework::System::IO::FileSystem;

template<class T>
struct PImpl<T>::Data
{
    Data()
    :m_Lookup(32)
    {
    }

    ~Data(){}

    HashList m_Lookup;
    List<Pair<String,String>> m_KeyValuePairs;
    String m_Organisation;
    String m_Application;
};

Directory Settings::GetAppDataDir()
{
    Directory result;
    AutoPointer<Directory> userDataDir = Directory::UserApplicationDataDirectory();
    if (userDataDir)
        result.SetLocation(Uri(userDataDir->Location().OriginalString() + "/" + m_PImpl->m_Organisation + "/" + m_PImpl->m_Application));
    return result;
}

void Settings::Initialize(const String& Organisation, const String& Application)
{
    m_PImpl->m_Organisation = Organisation;
    m_PImpl->m_Application = Application;
    m_PImpl->m_Lookup.Clear();
    m_PImpl->m_KeyValuePairs.Clear();
}

Settings::Settings()
{
}

String Settings::GetValue(const RF_Type::String& PropertyName)
{
    String result;
    RF_Hash::Hash32 hash;
    hash.FromString(PropertyName);
    Pair<String,String>* value = nullptr;
    if(m_PImpl->m_Lookup.Get(hash.GetHash(), reinterpret_cast<void*&>(value)))
    {
        result = value->Second;
    }
    return result;
}

void Settings::SetValue(const RF_Type::String& PropertyName, const String& Value)
{
    RF_Hash::Hash32 hash;
    hash.FromString(PropertyName);
    Pair<String, String>* entry = nullptr;
    if(m_PImpl->m_Lookup.Get(hash.GetHash(), reinterpret_cast<void*&>(entry)))
    {
        entry->Second = Value;
    }
    else
    {
        auto& entry = m_PImpl->m_KeyValuePairs.CreateElementAtEnd();
        entry.First = PropertyName;
        entry.Second = Value;
        m_PImpl->m_Lookup.Add(hash.GetHash(), &entry);
    }
}

void Settings::Load()
{
    Directory appDataDir = GetAppDataDir();
    if (appDataDir.Exists())
    {
        File config;
        config.SetLocation(appDataDir.Location().OriginalString() + "/config.txt");
        FileStream fs;
        if (config.Exists())
        {
            AutoPointerArray<UInt8> buf(config.Size());
            if (fs.Open(config.Location(), FileAccessMode::Read, FileAccessPriority::ReadThroughput))
            {
                fs.Read(buf.Get(), 0, buf.Size());
                fs.Close();
                for (Size i = 0, s = 0; i < buf.Size(); ++i)
                {
                    if(buf[i] == '\n' || buf[i] == '\r')
                    {
                        String line = String(reinterpret_cast<const char*>(&buf[s]), i - s);
                        AutoPointerArray<String> keyValue = line.Split(String("="));
                        if(keyValue.Count() == 2)
                        {
                            SetValue(keyValue[0],keyValue[1]);
                        }

                        while(i < buf.Size() && (buf[i] == '\n' || buf[i] == '\r'))
                        {
                            ++i;
                        }
                        s = i;
                    }
                }
            }
        }
    }
}

void Settings::Load(const String& Organisation, const String& Application)
{
    Initialize(Organisation, Application);
    Load();
}

void Settings::Save()
{
    Directory appDataDir = GetAppDataDir();
    if (!appDataDir.Exists())
        appDataDir.CreateNewDirectory();
    auto it = m_PImpl->m_KeyValuePairs.Begin();
    auto end = m_PImpl->m_KeyValuePairs.End();
    File config;
    config.SetLocation(appDataDir.Location().OriginalString() + "/config.txt");
    config.CreateNewFile();
    FileStream fs;
    if (fs.Open(config.Location(), FileAccessMode::Write, FileAccessPriority::DelayReadWrite))
    {
        for (; it != end; ++it)
        {
            String buf = it->First + "=" + it->Second + "\n";
            fs.Write(reinterpret_cast<const UInt8*>(buf.c_str()), 0, buf.Length());
        }
        fs.Close();
    }
}