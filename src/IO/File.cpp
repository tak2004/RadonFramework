#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/Compiler.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include <stdio.h>

using namespace RadonFramework;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::IO;

AutoPointer<File> File::CreateTempFile()
{
    AutoPointer<File> result;
    result=GenerateFile(GenerateTemporaryFilename());
    result->CreateNewFile();
    return result;
}

String File::GenerateTemporaryFilename()
{
    char buffer [L_tmpnam];
    tmpnam(buffer);
    return String(buffer+1);//ignore path seperator
}

AutoPointer<File> File::GenerateFile(const Uri& Location)
{
    AutoPointer<File> result(new File);
    if (result.Get())
    result->SetLocation(Location);
    return result;
}

const String& File::PathSeperator()
{
    static String result(PathSeperatorChar());
    return result;
}

const Char File::PathSeperatorChar()
{
    return FileSystem::PathSeperator();
}

const String& File::Seperator()
{
    static String result(SeperatorChar());
    return result;
}

const Char File::SeperatorChar()
{
    return FileSystem::Seperator();
}

File::File()
{
}

File::~File()
{
}

File::File( const File& Copy )
{
    *this=Copy;
}

File& File::operator =( const File& Other)
{
    m_Location=Other.m_Location;
    return *this;
}

void File::SetLocation(const Uri& Location)
{
    m_Location=Location;
}

Bool File::CreateNewFile() const
{
    return FileSystem::CreateFile(m_Location.GetComponents(UriComponents::Path));
}

Bool File::Preallocate(const RFTYPE::Size SizeInBytes)const
{
    return FileSystem::CreatePreAllocatedFile(m_Location.GetComponents(UriComponents::Path), SizeInBytes);
}

Bool File::Delete() const
{
    return FileSystem::DeleteFile(m_Location.GetComponents(UriComponents::Path));
}

Bool File::Exists() const
{
    return FileSystem::Access(m_Location.GetComponents(UriComponents::Path), AccessMode::Exists);
}

Bool File::CopyTo(const String& Destination)
{
    UInt64 size=Size();
    Bool result=FileSystem::CreatePreAllocatedFile(Destination,size);
    result&=FileSystem::CopyFile(m_Location.GetComponents(UriComponents::Path), Destination);
    return result;
}

const String File::Name() const
{
    String result;
    AutoPointerArray<String> parts=m_Location.GetComponents(UriComponents::Path).Split(Uri::PathSeperator);
    if (parts.Count()>0)
        result=parts[parts.Count()-1];
    return result;
}

String File::Path() const
{
    String path=m_Location.GetComponents(UriComponents::Path);
    return path.SubString(0,path.LastIndexOf(Uri::PathSeperator));
}

Bool File::IsHidden() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    return stat && stat->IsHidden;
}

Bool File::IsFile() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    return stat && !stat->IsDirectory;
}

UInt64 File::LastModified() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    return stat && stat->LastModificationTimestamp;
}

UInt64 File::LastAccess() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    return stat && stat->LastAccessTimestamp;
}

UInt64 File::CreatedOn() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    return stat && stat->CreateionTimestamp;
}

UInt64 File::Size() const
{
    AutoPointer<FileStatus> stat=FileSystem::Stat(m_Location.GetComponents(UriComponents::Path));
    Assert(stat!=0,"Unexspected result.");
    if (stat)
        return stat->Size;
    return 0;
}

Bool File::RenameTo( const Uri& NewLocation )
{
    Bool result=FileSystem::RenameFile(m_Location.GetComponents(UriComponents::Path), NewLocation.GetComponents(UriComponents::Path));
    if (result)
        m_Location=NewLocation;
    return result;
}

Bool File::AccessMode(AccessMode::Type NewValue)
{
    return FileSystem::ChangeMode(m_Location.GetComponents(UriComponents::Path), NewValue);
}

AccessMode::Type File::AccessMode()
{
    AccessMode::Type result=AccessMode::None;
    if (FileSystem::Access(m_Location.GetComponents(UriComponents::Path), AccessMode::Write))
        result|=AccessMode::Write;
    if (FileSystem::Access(m_Location.GetComponents(UriComponents::Path), AccessMode::Read))
        result|=AccessMode::Read;
    if (FileSystem::Access(m_Location.GetComponents(UriComponents::Path), AccessMode::Execute))
        result|=AccessMode::Execute;
    if (FileSystem::Access(m_Location.GetComponents(UriComponents::Path), AccessMode::Exists))
        result|=AccessMode::Exists;
    return result;
}

const Uri& File::Location()const
{
    return m_Location;
}

AutoPointerArray<UInt8> File::Read()
{
    UInt64 size=Size();
    AutoPointerArray<UInt8> result(new UInt8[size],size);
    FileStream stream;
    stream.Open(m_Location, FileSystem::FileAccessMode::Read, FileSystem::FileAccessPriority::ReadThroughput);
    stream.Read(result.Get(), 0, result.Size());
    return result;
}

Bool File::Write(const AutoPointerArray<UInt8>& Data)
{
    Bool result=FileSystem::CreatePreAllocatedFile(m_Location.GetComponents(UriComponents::Path), Data.Size());
    FileStream stream;
    stream.Open(m_Location, FileSystem::FileAccessMode::Write, FileSystem::FileAccessPriority::DelayReadWrite);
    stream.Write(Data.Get(), 0, Data.Size());
    return result;
}