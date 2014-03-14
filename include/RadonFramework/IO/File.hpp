#ifndef RF_IO_FILE_HPP
#define RF_IO_FILE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>
#include <RadonFramework/IO/AccessMode.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class File
        {
            public:
                static Memory::AutoPointer<File> CreateTempFile();
                static RFTYPE::String GenerateTemporaryFilename();
                static Memory::AutoPointer<File> GenerateFile(const Uri& Location);

                static const RFTYPE::String& PathSeperator();
                static const RFTYPE::Char PathSeperatorChar();
                static const RFTYPE::String& Seperator();
                static const RFTYPE::Char SeperatorChar();

                File();
                ~File();
                File(const File& Copy);
                File& operator =(const File& Other);

                void SetLocation(const Uri& Location);
                RFTYPE::Bool CreateNewFile()const;
                RFTYPE::Bool Preallocate(const RFTYPE::Size SizeInBytes)const;
                RFTYPE::Bool Delete()const;
                RFTYPE::Bool Exists()const;
                RFTYPE::Bool CopyTo(const RFTYPE::String& Destination);
                const RFTYPE::String Name()const;
                RFTYPE::String Path()const;
                RFTYPE::Bool IsHidden()const;
                RFTYPE::Bool IsFile()const;
                RFTYPE::UInt64 LastModified()const;
                RFTYPE::UInt64 CreatedOn()const;
                RFTYPE::UInt64 LastAccess()const;
                RFTYPE::UInt64 Size()const;
                RFTYPE::Bool RenameTo(const Uri& NewLocation);
                RFTYPE::Bool AccessMode(AccessMode::Type NewValue);
                AccessMode::Type AccessMode();
                const Uri& Location()const;
                Memory::AutoPointerArray<RFTYPE::UInt8> Read();
                RFTYPE::Bool Write(const Memory::AutoPointerArray<RFTYPE::UInt8>& Data);
            protected:
                Uri m_Location;
        };
    }
}

#endif // RF_IO_FILE_HPP