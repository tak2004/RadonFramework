#ifndef RF_IO_FILESTREAM_HPP
#define RF_IO_FILESTREAM_HPP

#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>

namespace RadonFramework::IO
{
class FileStream : public Stream
{
public:
  FileStream();
  ~FileStream() override;

  RF_Type::Bool
  Open(const Uri& Location,
       const System::IO::FileSystem::FileAccessMode::Type Mode,
       const System::IO::FileSystem::FileAccessPriority::Type AccessPriority);

  void Close() override;

  void Flush() override;

  RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
                       const RF_Type::UInt64 Index,
                       const RF_Type::UInt64 Count) override;

  RF_Type::UInt64
  Seek(const RF_Type::Int64 Offset, const SeekOrigin::Type Origin) override;

  RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
                        const RF_Type::UInt64 Offset,
                        const RF_Type::UInt64 Count) override;

  RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer,
                       const RF_Type::UInt64 Index,
                       const RF_Type::UInt64 Count) override;

  RF_Type::Bool CanRead() const override;

  RF_Type::Bool CanSeek() const override;

  RF_Type::Bool CanWrite() const override;

  RF_Type::Bool CanTimeout() const override;

  RF_Type::Bool CanPeek() const override;

  RF_Type::UInt64 Length() const override;

  RF_Type::UInt64 Position() const override;

  Time::TimeSpan ReadTimeout() const override;

  Time::TimeSpan WriteTimeout() const override;

protected:
  Uri m_Location;
  System::IO::FileSystem::FileHandle m_Handle;
  System::IO::FileSystem::FileAccessMode::Type m_Mode;
  System::IO::FileSystem::FileAccessPriority::Type m_AccessPriority;
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_IO_FILESTREAM_HPP