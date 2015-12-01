#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Directory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/Collections/List.hpp"

using namespace RadonFramework;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

Directory::Directory()
{
}

Directory::~Directory()
{
}

String Directory::PathSeperator()
{
    return RF_SysFile::PathSeperator();
}

String Directory::Seperator()
{
    return RF_SysFile::Seperator();
}

AutoPointer<Directory> Directory::WorkingDirectory()
{
    RF_IO::Uri uri;
    RF_SysFile::SystemPathToUri(RF_SysFile::WorkingDirectory(), uri);
    return GenerateDirectory(uri);
}

AutoPointer<Directory> Directory::HomeDirectory()
{
    RF_IO::Uri uri;
    RF_SysFile::SystemPathToUri(RF_SysFile::HomeDirectory(), uri);
    return GenerateDirectory(uri);
}

AutoPointer<Directory> Directory::ApplicationDirectory()
{
    RF_IO::Uri uri;
    RF_SysFile::SystemPathToUri(RF_SysFile::ApplicationDirectory(), uri);
    return GenerateDirectory(uri);
}

AutoPointer<Directory> Directory::UserApplicationDataDirectory()
{
    RF_IO::Uri uri;
    RF_SysFile::SystemPathToUri(RF_SysFile::UserApplicationDataDirectory(), uri);
    return GenerateDirectory(uri);
}

AutoPointer<Directory> Directory::ApplicationDataDirectory()
{
    RF_IO::Uri uri;
    RF_SysFile::SystemPathToUri(RF_SysFile::ApplicationDataDirectory(), uri);
    return GenerateDirectory(uri);
}

AutoPointer<Directory> Directory::GenerateDirectory( const Uri& Location )
{
    AutoPointer<Directory> result(new Directory());
    if (result.Get())
        result->SetLocation(Location);
    return result;
}

Directory::Directory(const Directory& Copy)
{
    *this=Copy;
}

Directory& Directory::operator =(const Directory& Other)
{
    m_Uri=Other.m_Uri;
    return *this;
}

void Directory::SetLocation(const Uri& Location)
{
    m_Uri=Location;
}

Bool Directory::CreateNewDirectory(const Bool Recursive /* = true */) const
{
    Bool result = false;
    if (Recursive)
    {
        AutoPointerArray<String> dirs = m_Uri.GetComponents(UriComponents::Path).Split(Uri::PathSeperator);
        String path("file://");
        String systemPath;
        for (Size i = 0; i < dirs.Count(); ++i)
        {
            path += RF_Type::String("/") + dirs[i];
            RF_SysFile::UriToSystemPath(path, systemPath);
            result = RF_SysFile::CreateDirectory(systemPath);
        }            
    }
    else
    {
        RF_Type::String systemPath;
        RF_SysFile::UriToSystemPath(m_Uri, systemPath);
        result = RF_SysFile::CreateDirectory(systemPath);
    }
    return result;
}

Bool Directory::Delete() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    return RF_SysFile::DeleteDirectory(systemPath);
}

Bool Directory::Exists() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    return RF_SysFile::Access(systemPath, AccessMode::Exists);
}

String Directory::Name() const
{
    String result;
    AutoPointerArray<String> pathParts = m_Uri.GetComponents(UriComponents::Path).Split(Uri::PathSeperator);
    if (pathParts.Count()>0)
        result=pathParts[pathParts.Count()-1];
    return result;
}

Uri Directory::Location() const
{
    return m_Uri;
}

Bool Directory::IsHidden() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat = RF_SysFile::Stat(systemPath);
    return stat && stat->IsHidden;
}

Bool Directory::IsDirectory() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat = RF_SysFile::Stat(systemPath);
    return stat && stat->IsDirectory;
}

UInt64 Directory::LastModified() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->LastModificationTimestamp;
}

UInt64 Directory::LastAccess() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->LastAccessTimestamp;
}

UInt64 Directory::CreatedAt() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->CreateionTimestamp;
}

UInt64 Directory::Length() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    Assert(stat!=0,"Unexspected result.");
    if (stat)
        return stat->Size;
    return 0;
}

Bool Directory::RenameTo( const Uri& NewLocation )
{
    RF_Type::String systemPathFrom, systemPathTo;
    RF_SysFile::UriToSystemPath(m_Uri, systemPathFrom);
    RF_SysFile::UriToSystemPath(NewLocation, systemPathTo);
    if (RF_SysFile::RenameFile(systemPathFrom, systemPathTo))
    {
        m_Uri=NewLocation;
        return true;
    }
    return false;
}

Bool Directory::AccessMode(AccessMode::Type NewValue)
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    return RF_SysFile::ChangeMode(systemPath, NewValue);
}

AccessMode::Type Directory::AccessMode()
{
    AccessMode::Type result=AccessMode::None;
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    if (RF_SysFile::Access(systemPath, AccessMode::Write))
        result|=AccessMode::Write;
    if (RF_SysFile::Access(systemPath, AccessMode::Read))
        result|=AccessMode::Read;
    if (RF_SysFile::Access(systemPath, AccessMode::Execute))
        result|=AccessMode::Execute;
    if (RF_SysFile::Access(systemPath, AccessMode::Exists))
        result|=AccessMode::Exists;
    return result;
}

String Directory::ToSystemPath() const
{
    return m_Uri.GetComponents(UriComponents::Path);
}

AutoPointerArray<String> Directory::Files()const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointerArray<String> content= RF_SysFile::DirectoryContent(systemPath);
    AutoPointerArray<String> result;
    List<String> tmp;
    for (Size i=0; i<content.Count(); ++i)
    {
        if(!RF_SysFile::Stat(systemPath + RF_SysFile::PathSeperator() + content[i])->IsDirectory)
        {
            tmp.AddLast(content[i]);
        }
    }

    result = AutoPointerArray<String>(tmp.Count());
    for(Size i = 0; i<tmp.Count(); ++i)
    {
        result[i].Swap(tmp[i]);
    }
    return result;
}

AutoPointerArray<String> Directory::FilesIncludingSubdirectories()const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointerArray<String> content= RF_SysFile::DirectoryContent(systemPath);
    AutoPointerArray<String> result;
    List<String> tmp;
    for (Size i=0; i<content.Count(); ++i)
    {
        if(RF_SysFile::Stat(systemPath + RF_SysFile::PathSeperator() + content[i])->IsDirectory)
        {
            Directory subdir;
            subdir.SetLocation(systemPath + RF_SysFile::PathSeperator() + content[i]);
            AutoPointerArray<String> dirContent = subdir.FilesIncludingSubdirectories();
            for(Size i = 0; i < dirContent.Size(); ++i)
                tmp.AddLast(dirContent[i]);
        }
        else
            tmp.AddLast(content[i]);
    }

    result = AutoPointerArray<String>(tmp.Count());
    for(Size i = 0; i<tmp.Count(); ++i)
        result[i].Swap(tmp[i]);
    return result;
}

AutoPointerArray<Directory> Directory::Directories()const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Uri, systemPath);
    AutoPointerArray<String> content= RF_SysFile::DirectoryContent(systemPath);
    AutoPointerArray<Directory> result;
    List<Directory> tmp;
    for (Size i=0; i<content.Count(); ++i)
    {
        if(RF_SysFile::Stat(systemPath + RF_SysFile::PathSeperator() + content[i])->IsDirectory)
        {
            Directory dir;
            dir.SetLocation(systemPath + RF_SysFile::PathSeperator() + content[i]);
            tmp.AddLast(dir);
        }
    }

    result = AutoPointerArray<Directory>(tmp.Count());
    for(Size i = 0; i<tmp.Count(); ++i)
        result[i]=tmp[i];
    return result;
}