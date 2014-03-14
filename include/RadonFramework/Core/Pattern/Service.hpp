#ifndef RF_CORE_PATTERN_SERVICE_HPP
#define RF_CORE_PATTERN_SERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Pattern
        {
            class Service
            {
                public:
                    Service(const RFTYPE::String& Name);
                    virtual ~Service();
                    virtual const RFTYPE::String& Name();
                protected:
                    RFTYPE::String m_Name;
            };
        }
    }
}

#endif // RF_CORE_PATTERN_SERVICE_HPP
