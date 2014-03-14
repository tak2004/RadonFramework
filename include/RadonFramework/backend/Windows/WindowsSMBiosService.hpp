#ifndef RF_WINDOWSSMBIOSSERVICE_HPP
#define RF_WINDOWSSMBIOSSERVICE_HPP

#include <RadonFramework/Diagnostics/Profiling/SMBiosService.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    class WindowsSMBiosService:public SMBiosService
		    {
			    public:
				    WindowsSMBiosService(const RadonFramework::Core::Types::String &Name);
			    protected:
				    void LoadSMBios();
		    };
	    }
    }
}

#endif // RF_WINDOWSSMBIOSSERVICE_HPP