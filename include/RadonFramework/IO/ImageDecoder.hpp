#ifndef RF_IO_IMAGEDECODER_HPP
#define RF_IO_IMAGEDECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Decoder.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework { namespace IO {

class ImageDecoder:public Decoder
{
public:
    virtual RF_Mem::AutoPointerArray<RF_Type::UInt8> LoadLayer(RF_Type::UInt32 Layer)=0;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_IMAGEDECODER_HPP
