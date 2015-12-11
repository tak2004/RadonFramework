#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/File.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include <stdio.h>

using namespace RadonFramework;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

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
    return String(buffer+1, L_tmpnam);//ignore path separator
}

AutoPointer<File> File::GenerateFile(const Uri& Location)
{
    AutoPointer<File> result(new File);
    if (result.Get())
    result->SetLocation(Location);
    return result;
}

String File::PathSeperator()
{
    return RF_SysFile::PathSeperator();
}

String File::Seperator()
{
    return RF_SysFile::Seperator();
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
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return RF_SysFile::CreateFile(systemPath);
}

Bool File::Preallocate(const RF_Type::Size SizeInBytes)const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return RF_SysFile::CreatePreAllocatedFile(systemPath, SizeInBytes);
}

Bool File::Delete() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return RF_SysFile::DeleteFile(systemPath);
}

Bool File::Exists() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return RF_SysFile::Access(systemPath, AccessMode::Exists);
}

Bool File::CopyTo(const Uri& Destination)
{
    UInt64 size=Size();
    RF_Type::String systemPathFrom, systemPathTo;
    RF_SysFile::UriToSystemPath(m_Location, systemPathFrom);
    RF_SysFile::UriToSystemPath(Destination, systemPathTo);
    Bool result = RF_SysFile::CreatePreAllocatedFile(systemPathTo, size);
    result&= RF_SysFile::CopyFile(systemPathFrom, systemPathTo);
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
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return systemPath.SubString(0, systemPath.LastIndexOf(RF_SysFile::PathSeperator()));
}

Bool File::IsHidden() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->IsHidden;
}

Bool File::IsFile() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && !stat->IsDirectory;
}

UInt64 File::LastModified() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->LastModificationTimestamp;
}

UInt64 File::LastAccess() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->LastAccessTimestamp;
}

UInt64 File::CreatedOn() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    return stat && stat->CreateionTimestamp;
}

UInt64 File::Size() const
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AutoPointer<FileStatus> stat= RF_SysFile::Stat(systemPath);
    Assert(stat!=0,"Unexspected result.");
    if (stat)
        return stat->Size;
    return 0;
}

Bool File::RenameTo( const Uri& NewLocation )
{
    RF_Type::String systemPathFrom, systemPathTo;
    RF_SysFile::UriToSystemPath(m_Location, systemPathFrom);
    RF_SysFile::UriToSystemPath(NewLocation, systemPathTo);
    Bool result= RF_SysFile::RenameFile(systemPathFrom, systemPathTo);
    if (result)
        m_Location=NewLocation;
    return result;
}

Bool File::AccessMode(AccessMode::Type NewValue)
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    return RF_SysFile::ChangeMode(systemPath, NewValue);
}

AccessMode::Type File::AccessMode()
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    AccessMode::Type result=AccessMode::None;
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

const Uri& File::Location()const
{
    return m_Location;
}

AutoPointerArray<UInt8> File::Read()
{
    UInt64 size=Size();
    AutoPointerArray<UInt8> result(size);
    FileStream stream;
    stream.Open(m_Location, RF_SysFile::FileAccessMode::Read, RF_SysFile::FileAccessPriority::ReadThroughput);
    stream.Read(result.Get(), 0, result.Size());
    return result;
}

Bool File::Write(const AutoPointerArray<UInt8>& Data)
{
    RF_Type::String systemPath;
    RF_SysFile::UriToSystemPath(m_Location, systemPath);
    Bool result= RF_SysFile::CreatePreAllocatedFile(systemPath, Data.Size());
    FileStream stream;
    stream.Open(m_Location, RF_SysFile::FileAccessMode::Write, RF_SysFile::FileAccessPriority::DelayReadWrite);
    stream.Write(Data.Get(), 0, Data.Size());
    return result;
}