#ifndef RF_IO_DIRECTORY_HPP
#define RF_IO_DIRECTORY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/IO/AccessMode.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class Directory
        {
            public:
                static const RFTYPE::String& PathSeperator();
                static const RFTYPE::Char PathSeperatorChar();
                static const RFTYPE::String& Seperator();
                static const RFTYPE::Char SeperatorChar();

                /// Return the directory from where the application was started.
                static Memory::AutoPointer<Directory> WorkingDirectory();
                /// Return the the user's home directory.
                static Memory::AutoPointer<Directory> HomeDirectory();
                /// Return the directory where the running application is located.
                static Memory::AutoPointer<Directory> ApplicationDirectory();
                /// Return the data directory for 'current user' which belongs to the running application.
                static Memory::AutoPointer<Directory> UserApplicationDataDirectory();
                /// Return the data directory for 'all user' which belongs to the running application.
                static Memory::AutoPointer<Directory> ApplicationDataDirectory();
                /// This is a util function which create a Directory object and set the location.
                static Memory::AutoPointer<Directory> GenerateDirectory(const Uri& Location);

                Directory();
                virtual ~Directory();
                Directory(const Directory& Copy);
                Directory& operator =(const Directory& Other);

                void SetLocation(const Uri& Location);
                RFTYPE::Bool CreateNewDirectory(const RFTYPE::Bool Recursive = true)const;
                RFTYPE::Bool Delete()const;
                RFTYPE::Bool Exists()const;
                RFTYPE::String Name()const;
                Uri Location()const;
                RFTYPE::Bool IsHidden()const;
                RFTYPE::Bool IsDirectory()const;
                RFTYPE::UInt64 LastModified()const;
                RFTYPE::UInt64 CreatedOn()const;
                RFTYPE::UInt64 LastAccess()const;
                RFTYPE::UInt64 Length()const;
                RFTYPE::Bool RenameTo(const Uri& NewLocation);
                RFTYPE::Bool AccessMode(AccessMode::Type NewValue);
                AccessMode::Type AccessMode();
                RFTYPE::String ToSystemPath()const;
                Memory::AutoPointerArray<RFTYPE::String> Files()const;
                Memory::AutoPointerArray<RFTYPE::String> FilesIncludingSubdirectories()const;
                Memory::AutoPointerArray<Directory> Directories()const;
            protected:
                Uri m_Uri;
        };
    }
}

#endif // RF_IO_DIRECTORY_HPP