#ifndef RF_IO_FILEWATCHER_HPP
#define RF_IO_FILEWATCHER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>

namespace RadonFramework { namespace IO {
    
class FileWatcher;

struct FileWatcherEvent
{
    FileWatcher* Sender;
    RF_Type::String* Filename;
};
        
class FileWatcher: RF_Pattern::IObserver
{
public:
    FileWatcher();
    FileWatcher(const FileWatcher& Copy);
    ~FileWatcher();

    void Initialize(const Uri& Path,
                    const RF_Type::String& Filter = ""_rfs);
                
    const Uri& Path()const;
    const RF_Type::String& Filter();

    /// Retun False on time out else True.
    RF_Type::Bool WaitForEvent(System::IO::FileSystem::FileWatcherEvent& Event);

    void Start();
    void ProcessBuffer();
    void Stop();

    FileWatcher& operator=(const FileWatcher& Other);
       

    RF_Pattern::Event<const FileWatcherEvent&> OnCreated;
    RF_Pattern::Event<const FileWatcherEvent&> OnChanged;
    RF_Pattern::Event<const FileWatcherEvent&> OnDeleted;
private:
    System::IO::FileSystem::FileWatcherHandle m_Handle;
    RF_Type::String m_Filter;
    Uri m_Path;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_FILEWATCHER_HPP