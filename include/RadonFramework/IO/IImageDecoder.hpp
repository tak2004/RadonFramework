#ifndef RF_IIMAGEDECODER_HPP
#define RF_IIMAGEDECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/IDecoder.hpp>
#include <RadonFramework/Drawing/Image.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework
{
  namespace IO
  {
    class IImageDecoder:public IDecoder
    {
      public:
        virtual ~IImageDecoder(){};
        virtual Memory::AutoPointer<Drawing::ImageInfo> Information()=0;
        virtual Memory::AutoPointerArray<Core::Types::UInt8> LoadLayer(Core::Types::UInt32 Frame, 
                                                                    Core::Types::UInt32 Layer)=0;
    };
  }
}

#endif // RF_IDECODER_HPP
