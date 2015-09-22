#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/FileStream.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/File.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::IO::FileSystem;

FileStream::FileStream()
{
    m_Handle = FileHandle::Zero();
}

FileStream::~FileStream()
{
    if (m_Handle!=FileHandle::Zero())
        Close();
}

Bool FileStream::Open(const Uri& Location, const FileAccessMode::Type Mode,
                      const FileAccessPriority::Type AccessPriority)
{
    m_Mode=Mode;
    m_Location=Location;
    m_AccessPriority=AccessPriority;
    m_Handle=OpenFile(m_Location.GetComponents(UriComponents::Path), m_Mode, m_AccessPriority);
    return m_Handle!=FileHandle::Zero();
}

void FileStream::Close()
{
    Assert(m_Handle!=FileHandle::Zero(), "Invalid operation.");
    CloseFile(m_Handle);
}

void FileStream::Flush()
{
    Assert(m_Handle!=FileHandle::Zero(),"Invalid operation.");
    FlushFile(m_Handle);
}

UInt64 FileStream::Read( UInt8* Buffer, const UInt64 Index, const UInt64 Count )
{
    Assert(m_Handle!=FileHandle::Zero(),"Invalid operation.");
    UInt64 result=0;
    ReadFile(m_Handle, Buffer+Index, Count, result);
    return result;
}

UInt64 FileStream::Seek( const Int64 Offset, const SeekOrigin::Type Origin )
{
    Assert(m_Handle!=FileHandle::Zero(),"Invalid operation.");
    return SeekFile(m_Handle, Offset, Origin);
}

UInt64 FileStream::Write(const UInt8* Buffer, const UInt64 Offset, const UInt64 Count )
{
    Assert(m_Handle!=FileHandle::Zero(),"Invalid operation.");
    UInt64 result=0;
    WriteFile(m_Handle, Buffer+Offset, Count, result);
    return result;
}

Bool FileStream::CanRead() const
{
    static Bool mode[FileAccessMode::MAX]={true, false, true};
    return mode[m_Mode];
}

Bool FileStream::CanSeek() const
{
    return true;
}

Bool FileStream::CanWrite() const
{
    static Bool mode[FileAccessMode::MAX]={false, true, true};
    return mode[m_Mode];
}

Bool FileStream::CanTimeout() const
{
    return false;
}

UInt64 FileStream::Length() const
{
    File file;
    file.SetLocation(m_Location);
    return file.Size();
}

UInt64 FileStream::Position() const
{
    Assert(m_Handle!=FileHandle::Zero(), "Invalid operation.");
    return TellFile(m_Handle);
}

TimeSpan FileStream::ReadTimeout() const
{
    return TimeSpan();
}

TimeSpan FileStream::WriteTimeout() const
{
    return TimeSpan();
}

RF_Type::UInt64 FileStream::Peek(RF_Type::UInt8* Buffer, const RF_Type::UInt64 Index,
    const RF_Type::UInt64 Count)
{
    Assert(m_Handle != FileHandle::Zero(), "Invalid operation.");
    UInt64 result = 0;
    ReadFile(m_Handle, Buffer + Index, Count, result);
    SeekFile(m_Handle, -static_cast<RF_Type::Int64>(result), RF_IO::SeekOrigin::Current);
    return result;
}

RF_Type::Bool RadonFramework::IO::FileStream::CanPeek() const
{
    return true;
}
