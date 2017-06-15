#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/FileWatcher.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::IO::FileSystem;

namespace RadonFramework { namespace IO {

FileWatcher::FileWatcher()
{
    m_Handle=FileWatcherHandle::Zero();
}

FileWatcher::FileWatcher(const FileWatcher& Copy)
{
}

FileWatcher::~FileWatcher()
{
    if (m_Handle.GetPointer()!=0)
        DestroyFileWatcher(m_Handle);
}

void FileWatcher::Initialize(const Uri& Path, const String& Filter)
{
    m_Filter=Filter;
    m_Path=Path;
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Path, systemPath);
    m_Handle=CreateFileWatcher(systemPath);
}

const Uri& FileWatcher::Path()const
{
    return m_Path;
}

const String& FileWatcher::Filter()
{
    return m_Filter;
}

Bool FileWatcher::WaitForEvent(RF_SysFile::FileWatcherEvent& Event)
{
    return WaitForFileWatcher(m_Handle, Event);
}

void FileWatcher::Start()
{
    StartFileWatcher(m_Handle);
}

void FileWatcher::ProcessBuffer()
{
    RF_SysFile::FileWatcherEvent internalEvent;
    FileWatcherEvent publicEvent;
    publicEvent.Sender = this;
    while(GetFileWatcherEvent(m_Handle, internalEvent))
    {
        publicEvent.Filename = &internalEvent.Name;
        switch (internalEvent.ChangeType)
        {
            case WatcherChangeTypes::Created:                
                OnCreated(publicEvent);
                break;
            case WatcherChangeTypes::Deleted:
                OnDeleted(publicEvent);
                break;
            case WatcherChangeTypes::Changed:
                OnChanged(publicEvent);
                break;
        }
    }
}

void FileWatcher::Stop()
{
    StopFileWatcher(m_Handle);
}

FileWatcher& FileWatcher::operator=(const FileWatcher& Other)
{
    return *this;
}

} }