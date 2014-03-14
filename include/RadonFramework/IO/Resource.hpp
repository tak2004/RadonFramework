#ifndef RF_IO_RESOURCE_HPP
#define RF_IO_RESOURCE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class Stream;

        class Resource
        {
            public:
                virtual ~Resource();
                virtual void Open();
                virtual RFTYPE::Bool Exists()const=0;
                virtual RFTYPE::Bool IsReadable()const;
                virtual RFTYPE::Bool IsWriteable()const;
                virtual RFTYPE::UInt32 FourCC()=0;
                virtual Stream* Reader()const=0;
                virtual Stream* Writer()const=0;
                virtual RFTYPE::Size GetSize();
                const Uri& Location()const;
                void Location(const Uri& NewLocation);
                Memory::AutoPointerArray<RFTYPE::UInt8> Read();
            protected:
                Uri m_Location;
        };
    }
}

#endif // RF_IO_RESOURCE_HPP