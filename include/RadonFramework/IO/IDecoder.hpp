#ifndef RF_IDECODER_HPP
#define RF_IDECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Time/TimeSpan.hpp>

namespace RadonFramework
{
    namespace IO
    {
        namespace DecoderTarget
        {
            enum Type
            {
                Image
            };
        }

        class IDecoder
        {
            public:
                //on files it will load the header and on devices it will load device information
                virtual unsigned int LoadInformation()=0;
                virtual bool Seekable()=0;
                virtual bool IsTargetSupported(DecoderTarget::Type Target)=0;

                //reading position will be increased by return value(bytes)
                virtual unsigned int LoadData(void* Data,unsigned int Buffersize)=0;
                virtual unsigned int SeekData(unsigned int Bytes)=0;
                virtual unsigned int TotalData()=0;
                virtual unsigned int TellData()=0;
        };
    }
}

#endif // RF_IDECODER_HPP
