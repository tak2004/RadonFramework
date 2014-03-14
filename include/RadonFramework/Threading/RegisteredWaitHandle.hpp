#ifndef RF_THREADING_REGISTEREDWAITHANDLE_HPP
#define RF_THREADING_REGISTEREDWAITHANDLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Threading/IWaitHandle.hpp>

namespace RadonFramework
{
    namespace Threading
    {
        namespace CT=Core::Types;

        class RegisteredWaitHandle
        {
            public:
                CT::Bool Unregister(IWaitHandle* WaitObject);
        };
    }
}

#endif // RF_THREADING_REGISTEREDWAITHANDLE_HPP
