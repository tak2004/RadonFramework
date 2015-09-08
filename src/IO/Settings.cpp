#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Settings.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/IO/Directory.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"
#include "RadonFramework/Core/Common/StringCache.hpp"

using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Idioms;
using namespace RadonFramework::Core::Policies;
using namespace RadonFramework::IO;
using namespace RadonFramework::System::IO::FileSystem;

struct eqstr { bool operator()(const char* s1, const char* s2) const { return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0); } };

template<class T>
struct PImpl<T>::Data
{
    Data() { m_Data.SetEmptyKey(0); }
    ~Data(){}

    HashMap<const char*, String, hash<const char*>, eqstr, HashMapOperationEfficient<const char*, String, hash<const char*>, eqstr> > m_Data;
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
}

Settings::Settings()
{
}

String Settings::GetValue(const char* PropertyName)
{
    String result;
    if (m_PImpl->m_Data.ContainsKey(PropertyName))
        result = m_PImpl->m_Data[PropertyName];
    return result;
}

void Settings::SetValue(const char* PropertyName, const String& Value)
{
    m_PImpl->m_Data[PropertyName] = Value;
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
                    if (buf[i] == '\n')
                    {
                        String line = String(reinterpret_cast<const char*>(&buf[s]), i - s);
                        AutoPointerArray<String> keyValue = line.Split(String("="));
                        if (keyValue.Count() == 2)
                        {
                            const char* key = StringCache::Find(keyValue[0]);
                            if (key == 0)
                                key = keyValue[0].c_str();
                            m_PImpl->m_Data[key] = keyValue[1];
                        }
                        s = i+1;
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
    auto it = m_PImpl->m_Data.Begin();
    auto end = m_PImpl->m_Data.End();
    File config;
    config.SetLocation(appDataDir.Location().OriginalString() + "/config.txt");
    config.CreateNewFile();
    FileStream fs;
    if (fs.Open(config.Location(), FileAccessMode::Write, FileAccessPriority::DelayReadWrite))
    {
        for (; it != end; ++it)
        {
            String buf = String::UnsafeStringCreation(it->first) + "=" + it->second + "\n";
            fs.Write(reinterpret_cast<const UInt8*>(buf.c_str()), 0, buf.Length());
        }
        fs.Close();
    }
}