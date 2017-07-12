#ifndef RF_DECODERSERVICELOCATOR_HPP
#define RF_DECODERSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/DecoderService.hpp>

namespace RadonFramework::IO {

class NullDecoderService:public DecoderService
{
public:
    NullDecoderService(const RF_Type::String &Name):DecoderService(Name){}
    
    virtual RF_Mem::AutoPointer<Decoder> CreateDecoder(const RF_Type::UInt32 FourCC,
                                                       RF_Decoders::Interface Target)
    {
        return RF_Mem::AutoPointer<Decoder>();
    }
};

struct DecoderServiceLocator:public RF_Pattern::Locator<DecoderService, NullDecoderService>
{
    DecoderServiceLocator() = delete;

    static DecoderServiceLocator::Iterator FindCodec(
        const RF_Type::UInt32 FCC, RF_Decoders::Interface Target);

    static DecoderServiceLocator::Iterator FindByNameOrFourCC(
        const RF_Type::String& Name, const RF_Type::UInt32 FCC);
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif
