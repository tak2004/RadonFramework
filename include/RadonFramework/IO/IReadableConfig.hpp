#ifndef RF_IHUMANREADABLECONFIG_HPP
#define RF_IHUMANREADABLECONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/IConfig.hpp>

namespace RadonFramework
{
    namespace IO
    {
      class IHumanReadableConfig:public IConfig
      {
        public:
          virtual void SetItem(const std::string& Section, const std::string& Key, const std::string& Value)=0;
        virtual std::string GetItem(const std::string& Section, const std::string& Key)=0;
      };
    }
}

#endif // RF_IHUMANREADABLECONFIG_HPP
