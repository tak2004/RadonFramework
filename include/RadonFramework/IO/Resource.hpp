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
                virtual RF_Type::Bool Exists()const=0;
                virtual RF_Type::Bool IsReadable()const;
                virtual RF_Type::Bool IsWriteable()const;
                virtual RF_Type::UInt32 FourCC()=0;
                virtual Stream* Reader()const=0;
                virtual Stream* Writer()const=0;
                virtual RF_Type::Size GetSize();
                const Uri& Location()const;
                void Location(const Uri& NewLocation);
                Memory::AutoPointerArray<RF_Type::UInt8> Read();
            protected:
                Uri m_Location;
        };
    }
}

#endif // RF_IO_RESOURCE_HPP