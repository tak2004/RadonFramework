#ifndef RF_IO_FILESTREAM_HPP
#define RF_IO_FILESTREAM_HPP

#include <RadonFramework/IO/Stream.hpp>
#include <RadonFramework/System/IO/FileSystem.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class FileStream: public Stream
        {
            public:
                FileStream();
                ~FileStream();

                RFTYPE::Bool Open(const Uri& Location,
                                const System::IO::FileSystem::FileAccessMode::Type Mode,
                                const System::IO::FileSystem::FileAccessPriority::Type AccessPriority);

                void Close();

                void Flush();

                RFTYPE::UInt64 Read(RFTYPE::UInt8* Buffer,
                                  const RFTYPE::UInt64 Index,
                                  const RFTYPE::UInt64 Count);

                RFTYPE::UInt64 Seek(const RFTYPE::UInt64 Offset,
                                  const SeekOrigin::Type Origin);

                RFTYPE::UInt64 Write(const RFTYPE::UInt8* Buffer,
                                   const RFTYPE::UInt64 Offset,
                                   const RFTYPE::UInt64 Count);

                RFTYPE::Bool CanRead()const;
                RFTYPE::Bool CanSeek()const;
                RFTYPE::Bool CanWrite()const;
                RFTYPE::Bool CanTimeout()const;
                RFTYPE::UInt64 Length()const;
                RFTYPE::UInt64 Position()const;
                Time::TimeSpan ReadTimeout()const;
                Time::TimeSpan WriteTimeout()const;
            protected:
                Uri m_Location;
                System::IO::FileSystem::FileHandle m_Handle;
                System::IO::FileSystem::FileAccessMode::Type m_Mode;
                System::IO::FileSystem::FileAccessPriority::Type m_AccessPriority;
        };
    }
}

#endif // RF_IO_FILESTREAM_HPP