#ifndef RF_DIAGNOSTICS_DEBUGGING_ERROR_HPP
#define RF_DIAGNOSTICS_DEBUGGING_ERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            template <typename Parent, typename ErrorEnum,RFTYPE::UInt32 ErrorCount>
            struct Error
            {
                //computer readable
                ErrorEnum ErrorCode;
                //human readable
                RFTYPE::UInt32 InternalErrorText;//default:0
                RFTYPE::UInt32 InternalDebugData;//default:0

                static RFTYPE::String ErrorText[ErrorCount];  

                static Parent Generate(ErrorEnum AError)
                {
                    Parent err; 
                    err.ErrorCode=AError; 
                    err.InternalErrorText=0; 
                    err.InternalDebugData=0; 
                    return err;
                }

                static Parent Generate(ErrorEnum AError,
                    const RFTYPE::String& AInternalErrorText)
                {
                    Parent err; 
                    err.ErrorCode=AError; 
                    err.InternalErrorText<<AInternalErrorText; 
                    err.InternalDebugData=0; 
                    return err;
                }

                static Parent Generate(ErrorEnum AError,
                    const RFTYPE::String& AInternalErrorText,
                    void* AInternalDebugData)
                {
                    Parent err; 
                    err.ErrorCode=AError; 
                    err.InternalErrorText=AInternalErrorText; 
                    err.InternalDebugData=AInternalDebugData; 
                    return err;
                }
            };
        }
    }    
}

#endif // RF_DIAGNOSTICS_DEBUGGING_ERROR_HPP