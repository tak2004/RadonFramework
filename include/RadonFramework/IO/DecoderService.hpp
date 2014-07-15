#ifndef RF_DECODERSERVICE_HPP
#define RF_DECODERSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include <RadonFramework/Core/Pattern/Service.hpp>

namespace RadonFramework
{
  namespace IO
  {
    class IDecoder;
    class DecoderService:public Core::Pattern::Service
    {
      protected:
        unsigned int m_FourCC;
        bool m_IsAvailable;
      public:
        DecoderService(const RF_Type::String &Name);
        DecoderService(const RF_Type::String &Name,const unsigned int FourCC);
        const unsigned int FourCC();
        virtual IDecoder* CreateDecoder(std::istream* StreamInput, bool Seekable)=0;
        virtual bool IsAvailable();
        virtual void Refresh()=0;
    };
  }
}

#endif
