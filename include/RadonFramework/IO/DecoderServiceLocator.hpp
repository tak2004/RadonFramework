#ifndef RF_DECODERSERVICELOCATOR_HPP
#define RF_DECODERSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/IO/DecoderService.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class NullDecoderService:public DecoderService
        {
            public:
                NullDecoderService(const RadonFramework::Core::Types::String &Name):DecoderService(Name){}
                IDecoder* CreateDecoder(std::istream* , bool ){return 0;}
                void Refresh(){}
        };

        class DecoderServiceLocator:public Core::Pattern::Locator<DecoderService,NullDecoderService>
        {
            public:
                static DecoderServiceLocator::Iterator FindNameOrFourCC(
                    const RadonFramework::Core::Types::String& Name, 
                    const RadonFramework::Core::Types::UInt32 FCC);
            private:
                ~DecoderServiceLocator();
        };
    }
}

#endif
