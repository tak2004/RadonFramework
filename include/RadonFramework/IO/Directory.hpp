#ifndef RF_IO_DIRECTORY_HPP
#define RF_IO_DIRECTORY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/IO/AccessMode.hpp>

namespace RadonFramework::IO {

class File;

class Directory
{
public:
    static RF_Type::String PathSeperator();
    static RF_Type::String Seperator();

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
    /// Return the temporary directory of the system.
    static Memory::AutoPointer<Directory> TemporaryDirectory();
    /// This is a util function which create a Directory object and set the location.
    static Memory::AutoPointer<Directory> GenerateDirectory(const Uri& Location);

    Directory();
    virtual ~Directory();
    Directory(const Directory& Copy);
    Directory& operator =(const Directory& Other);

    void SetLocation(const Uri& Location);
    RF_Type::Bool CreateNewDirectory(const RF_Type::Bool Recursive = true)const;
    RF_Type::Bool Delete()const;
    RF_Type::Bool Exists()const;
    RF_Type::String Name()const;
    Uri Location()const;
    RF_Type::Bool IsHidden()const;
    RF_Type::Bool IsDirectory()const;
    RF_Type::Bool HasParent()const;
    RF_Type::UInt64 LastModified()const;
    RF_Type::UInt64 CreatedAt()const;
    RF_Type::UInt64 LastAccess()const;
    RF_Type::UInt64 Length()const;
    RF_Type::Bool RenameTo(const Uri& NewLocation);
    RF_Type::Bool AccessMode(AccessMode::Type NewValue);
    AccessMode::Type AccessMode();
    RF_Type::String ToSystemPath()const;
    Memory::AutoPointerArray<RF_Type::String> Files()const;
    Memory::AutoPointerArray<RF_Type::String> FilesIncludingSubdirectories()const;
    Memory::AutoPointerArray<Directory> Directories()const;
    /// Returns an file instance if the directory exists and the specified Filename is an valid file.
    Memory::AutoPointer<File> SubFile(const RF_Type::String& Filename)const;
protected:
    Uri m_Uri;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_DIRECTORY_HPP