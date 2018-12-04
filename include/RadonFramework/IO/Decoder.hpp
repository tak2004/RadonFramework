#ifndef RF_IO_DECODER_HPP
#define RF_IO_DECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Decoders/Interface.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework::IO {

class Decoder
{
public:
    virtual void SetData(RF_Type::UInt8* ByteData, RF_Type::Size Bytes)=0;
    //on files it will load the header and on devices it will load device information
    virtual RF_Type::Size LoadInformation() = 0;
    virtual RF_Type::Bool Seekable()=0;

    //reading position will be increased by return value(bytes)
    virtual RF_Type::Size LoadData(void* Data, unsigned int Buffersize) = 0;
    virtual RF_Type::Size SeekData(RF_Type::Size Bytes) = 0;
    virtual RF_Type::Size TotalData() = 0;
    virtual RF_Type::Size TellData() = 0;
};
    
}

#endif // RF_IO_DECODER_HPP
