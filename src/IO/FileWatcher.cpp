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
    m_Handle=CreateFileWatcher(m_Path.GetComponents(UriComponents::Path));
}

const Uri& FileWatcher::Path()const
{
    return m_Path;
}

const String& FileWatcher::Filter()
{
    return m_Filter;
}

Bool FileWatcher::WaitForEvent(FileWatcherEvent& Event)
{
    return WaitForFileWatcher(m_Handle, Event);
}

void FileWatcher::Start()
{
    StartFileWatcher(m_Handle);
}

void FileWatcher::ProcessBuffer()
{
    FileWatcherEvent event;
    while(GetFileWatcherEvent(m_Handle, event))
        switch (event.ChangeType)
        {
            case WatcherChangeTypes::Created:
                OnCreated(event.Name);
                break;
            case WatcherChangeTypes::Deleted:
                OnDeleted(event.Name);
                break;
            case WatcherChangeTypes::Changed:
                OnChanged(event.Name);
                break;
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