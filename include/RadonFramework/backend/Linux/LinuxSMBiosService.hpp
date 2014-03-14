#ifndef RF_LINUXSMBIOSSERVICE_HPP
#define RF_LINUXSMBIOSSERVICE_HPP

#include <RadonFramework/Diagnostics/Profiling/SMBiosService.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            class LinuxSMBiosService:public SMBiosService
            {
                public:
                    LinuxSMBiosService(const Core::Types::String &Name);
                protected:
                    void LoadSMBios();
            };
        }
    }    
}

#endif // RF_LINUXSMBIOSSERVICE_HPP
