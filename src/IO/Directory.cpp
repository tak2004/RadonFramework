#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Directory.hpp"
#include "RadonFramework/Compiler.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/Collections/List.hpp"
#include <stdio.h>

using namespace RadonFramework;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::IO;
using namespace RadonFramework::Collections;

Directory::Directory()
{
}

Directory::~Directory()
{
}

String Directory::PathSeperator()
{
    return FileSystem::PathSeperator();
}

String Directory::Seperator()
{
    return FileSystem::Seperator();
}

AutoPointer<Directory> Directory::WorkingDirectory()
{
    return GenerateDirectory(Uri(FileSystem::WorkingDirectory()));
}

AutoPointer<Directory> Directory::HomeDirectory()
{
    return GenerateDirectory(Uri(FileSystem::HomeDirectory()));
}

AutoPointer<Directory> Directory::ApplicationDirectory()
{
    return GenerateDirectory(Uri(FileSystem::ApplicationDirectory()));
}

AutoPointer<Directory> Directory::UserApplicationDataDirectory()
{
    return GenerateDirectory(Uri(FileSystem::UserApplicationDataDirectory()));
}

AutoPointer<Directory> Directory::ApplicationDataDirectory()
{
    return GenerateDirectory(Uri(FileSystem::ApplicationDataDirectory()));
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
    AutoPointerArray<String> dirs = m_Uri.GetComponents(UriComponents::Path).Split(Uri::PathSeperator);
    if (Recursive)
    {
        String path;
        for (Size i = 0; i < dirs.Count(); ++i)
        {
            path += dirs[i]+"/";
            result = FileSystem::CreateDirectory(path);
        }            
    }
    else
        result = FileSystem::CreateDirectory(m_Uri.GetComponents(UriComponents::Path));
    return result;
}

Bool Directory::Delete() const
{
    return remove(m_Uri.GetComponents(UriComponents::Path).c_str()) == 0;
}

Bool Directory::Exists() const
{
    return FileSystem::Access(m_Uri.GetComponents(UriComponents::Path), AccessMode::Exists);
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
    AutoPointer<FileStatus> stat = FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    return stat && stat->IsHidden;
}

Bool Directory::IsDirectory() const
{
    AutoPointer<FileStatus> stat = FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    return stat && stat->IsDirectory;
}

UInt64 Directory::LastModified() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    return stat && stat->LastModificationTimestamp;
}

UInt64 Directory::LastAccess() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    return stat && stat->LastAccessTimestamp;
}

UInt64 Directory::CreatedOn() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    return stat && stat->CreateionTimestamp;
}

UInt64 Directory::Length() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path));
    Assert(stat!=0,"Unexspected result.");
    if (stat)
        return stat->Size;
    return 0;
}

Bool Directory::RenameTo( const Uri& NewLocation )
{
    if (rename(m_Uri.GetComponents(UriComponents::Path).c_str(), NewLocation.GetComponents(UriComponents::Path).c_str())==0)
    {
        m_Uri=NewLocation;
        return true;
    }
    return false;
}

Bool Directory::AccessMode(AccessMode::Type NewValue)
{
    return FileSystem::ChangeMode(m_Uri.GetComponents(UriComponents::Path), NewValue);
}

AccessMode::Type Directory::AccessMode()
{
    AccessMode::Type result=AccessMode::None;
    if (FileSystem::Access(m_Uri.GetComponents(UriComponents::Path), AccessMode::Write))
        result|=AccessMode::Write;
    if (FileSystem::Access(m_Uri.GetComponents(UriComponents::Path), AccessMode::Read))
        result|=AccessMode::Read;
    if (FileSystem::Access(m_Uri.GetComponents(UriComponents::Path), AccessMode::Execute))
        result|=AccessMode::Execute;
    if (FileSystem::Access(m_Uri.GetComponents(UriComponents::Path), AccessMode::Exists))
        result|=AccessMode::Exists;
    return result;
}

String Directory::ToSystemPath() const
{
    return m_Uri.GetComponents(UriComponents::Path);
}

AutoPointerArray<String> Directory::Files()const
{
    AutoPointerArray<String> content=FileSystem::DirectoryContent(m_Uri.GetComponents(UriComponents::Path));
    AutoPointerArray<String> result;
    List<String> tmp;
    for (UInt32 i=0; i<content.Count(); ++i)
        if (!FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path)+Uri::PathSeperator+content[i])->IsDirectory)
            tmp.AddLast(content[i]);
    result = AutoPointerArray<String>(new String[tmp.Count()], tmp.Count());
    for(UInt32 i = 0; i<tmp.Count(); ++i)
        result[i].Swap(tmp[i]);
    return result;
}

AutoPointerArray<String> Directory::FilesIncludingSubdirectories()const
{
    AutoPointerArray<String> content=FileSystem::DirectoryContent(m_Uri.GetComponents(UriComponents::Path));
    AutoPointerArray<String> result;
    List<String> tmp;
    for (UInt32 i=0; i<content.Count(); ++i)
        if (FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path)+Uri::PathSeperator+content[i])->IsDirectory)
        {
            Directory subdir;
            subdir.SetLocation(m_Uri.GetComponents(UriComponents::Path)+Uri::PathSeperator+content[i]);
            AutoPointerArray<String> dirContent=subdir.FilesIncludingSubdirectories();
            for (Size i=0; i<dirContent.Size(); ++i)
                tmp.AddLast(dirContent[i]);
        }
        else
            tmp.AddLast(content[i]);
    result = AutoPointerArray<String>(new String[tmp.Count()], tmp.Count());
    for(UInt32 i = 0; i<tmp.Count(); ++i)
        result[i].Swap(tmp[i]);
    return result;
}

AutoPointerArray<Directory> Directory::Directories()const
{
    AutoPointerArray<String> content=FileSystem::DirectoryContent(m_Uri.GetComponents(UriComponents::Path));
    AutoPointerArray<Directory> result;
    List<Directory> tmp;
    for (UInt32 i=0; i<content.Count(); ++i)
        if (FileSystem::Stat(m_Uri.GetComponents(UriComponents::Path)+Uri::PathSeperator+content[i])->IsDirectory)
        {
            Directory dir;
            dir.SetLocation(m_Uri.GetComponents(UriComponents::Path)+Uri::PathSeperator+content[i]);
            tmp.AddLast(dir);
        }
    result = AutoPointerArray<Directory>(new Directory[tmp.Count()], tmp.Count());
    for(UInt32 i = 0; i<tmp.Count(); ++i)
        result[i]=tmp[i];
    return result;
}