#ifndef RF_DIAGNOSTICS_APPENDER_HPP
#define RF_DIAGNOSTICS_APPENDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Diagnostics
    {
        class Appender
        {
            public:
                virtual void WriteInfo(const RFTYPE::String& Text)=0;
                virtual void WriteError(const RFTYPE::String& Text)=0;
                virtual void WriteFatalError(const RFTYPE::String& Text)=0;
                virtual void WriteDebug(const RFTYPE::String& Text)=0;
            protected:
        };
    }
}

#endif // RF_DIAGNOSTICS_APPENDER_HPP