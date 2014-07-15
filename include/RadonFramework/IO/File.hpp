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
                static RF_Type::String GenerateTemporaryFilename();
                static Memory::AutoPointer<File> GenerateFile(const Uri& Location);

                static const RF_Type::String& PathSeperator();
                static const RF_Type::Char PathSeperatorChar();
                static const RF_Type::String& Seperator();
                static const RF_Type::Char SeperatorChar();

                File();
                ~File();
                File(const File& Copy);
                File& operator =(const File& Other);

                void SetLocation(const Uri& Location);
                RF_Type::Bool CreateNewFile()const;
                RF_Type::Bool Preallocate(const RF_Type::Size SizeInBytes)const;
                RF_Type::Bool Delete()const;
                RF_Type::Bool Exists()const;
                RF_Type::Bool CopyTo(const RF_Type::String& Destination);
                const RF_Type::String Name()const;
                RF_Type::String Path()const;
                RF_Type::Bool IsHidden()const;
                RF_Type::Bool IsFile()const;
                RF_Type::UInt64 LastModified()const;
                RF_Type::UInt64 CreatedOn()const;
                RF_Type::UInt64 LastAccess()const;
                RF_Type::UInt64 Size()const;
                RF_Type::Bool RenameTo(const Uri& NewLocation);
                RF_Type::Bool AccessMode(AccessMode::Type NewValue);
                AccessMode::Type AccessMode();
                const Uri& Location()const;
                Memory::AutoPointerArray<RF_Type::UInt8> Read();
                RF_Type::Bool Write(const Memory::AutoPointerArray<RF_Type::UInt8>& Data);
            protected:
                Uri m_Location;
        };
    }
}

#endif // RF_IO_FILE_HPP