#ifndef RF_IO_ENCODER_HPP
#define RF_IO_ENCODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Encoders/Interface.hpp>

namespace RadonFramework::IO {

class Encoder
{
public:
    virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> GenerateData() = 0;
};
    
}

#endif // RF_IO_ENCODER_HPP
