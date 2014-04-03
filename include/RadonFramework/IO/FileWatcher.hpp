#ifndef RF_IO_FILEWATCHER_HPP
#define RF_IO_FILEWATCHER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class FileWatcher: IObserver
        {
            public:
                FileWatcher();
                FileWatcher(const FileWatcher& Copy);
                ~FileWatcher();

                void Initialize(const Uri& Path,
                                const RFTYPE::String& Filter="");
                
                const Uri& Path()const;
                const RFTYPE::String& Filter();

                /// Retun False on time out else True.
                RFTYPE::Bool WaitForEvent(System::IO::FileSystem::FileWatcherEvent& Event);

                void Start();
                void ProcessBuffer();
                void Stop();

                Event<const RFTYPE::String&> OnCreated;
                Event<const RFTYPE::String&> OnChanged;
                Event<const RFTYPE::String&> OnDeleted;
            private:
                System::IO::FileSystem::FileWatcherHandle m_Handle;
                RFTYPE::String m_Filter;
                Uri m_Path;
        };
    }
}

#endif // RF_IO_FILEWATCHER_HPP