#ifndef RF_ICONFIG_HPP
#define RF_ICONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
      class IConfig
      {
        public:
        virtual void Read()=0;
        virtual void Write()=0;
        virtual void Clean()=0;

        virtual bool FindSection(const std::string& Section)=0;
        virtual bool FindKey(const std::string& Section, const std::string& Key)=0;
      };
    }
}

#endif // RF_ICONFIG_HPP
