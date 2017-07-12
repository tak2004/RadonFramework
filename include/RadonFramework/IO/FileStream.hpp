#ifndef RF_IO_FILESTREAM_HPP
#define RF_IO_FILESTREAM_HPP

#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::IO {

class FileStream: public Stream
{
public:
    FileStream();
    virtual ~FileStream() override;

    RF_Type::Bool Open(const Uri& Location,
                    const System::IO::FileSystem::FileAccessMode::Type Mode,
                    const System::IO::FileSystem::FileAccessPriority::Type AccessPriority);

    virtual void Close() override;

    virtual void Flush() override;

    virtual RF_Type::UInt64 Read(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Seek(const RF_Type::Int64 Offset,
        const SeekOrigin::Type Origin) override;

    virtual RF_Type::UInt64 Write(const RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Offset, const RF_Type::UInt64 Count) override;

    virtual RF_Type::UInt64 Peek(RF_Type::UInt8* Buffer,
        const RF_Type::UInt64 Index, const RF_Type::UInt64 Count) override;

    virtual RF_Type::Bool CanRead()const override;

    virtual RF_Type::Bool CanSeek()const override;

    virtual RF_Type::Bool CanWrite()const override;

    virtual RF_Type::Bool CanTimeout()const override;

    virtual RF_Type::Bool CanPeek()const override;

    virtual RF_Type::UInt64 Length()const override;

    virtual RF_Type::UInt64 Position()const override;

    virtual Time::TimeSpan ReadTimeout()const override;

    virtual Time::TimeSpan WriteTimeout()const override;
protected:
    Uri m_Location;
    System::IO::FileSystem::FileHandle m_Handle;
    System::IO::FileSystem::FileAccessMode::Type m_Mode;
    System::IO::FileSystem::FileAccessPriority::Type m_AccessPriority;
};
    
}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define  RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_FILESTREAM_HPP