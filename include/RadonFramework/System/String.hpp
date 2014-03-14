#ifndef RF_SYSTEM_STRING_HPP
#define RF_SYSTEM_STRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <cstdarg>

namespace RadonFramework {
// forward declarations
namespace Collections {
    template<class T>
    class List;
}
namespace Core { namespace Types {
    class String;
} }
    
namespace System { namespace String {
    /// This function will be called by RadonFramework_Init function.
    void Dispatch();

    /** This function will be called by RadonFraemwork_Init function to
      * check if the dispatching was successfully.
      **/
    RFTYPE::Bool IsSuccessfullyDispatched();
                
    /// This function is for debugging purpose and return all unassigned functions.
    void GetNotDispatchedFunctions(Collections::List<RFTYPE::String>& Result);

    namespace LocaleCategory
    {
        enum Type
        {
            ALL = 0,
            COLLATE,
            CTYPE,
            MONETARY,
            NUMERIC,
            TIME,
            MAX
        };
    }

    /// Function declaration for SetLocale.
    typedef RFTYPE::String (*SetLocaleCallback)(const LocaleCategory::Type Category,
                                                const RFTYPE::String& Locale);

    /// Function declaration for GetLocale.
    typedef const RFTYPE::String& (*GetLocaleCallback)();

    /// Function declaration for ToUpper.
    typedef RFTYPE::Bool (*ToUpperCallback)(RFTYPE::String& Instance);

    /// Function declaration for ToLower.
    typedef RFTYPE::Bool (*ToLowerCallback)(RFTYPE::String& Instance);

    /// Function declaration for Length.
    typedef RFTYPE::Size (*LengthCallback)(const RFTYPE::UInt8* Buffer, 
                                           const RFTYPE::Size BufferSize);

    /// Function declaration for ToInt64.
    typedef RFTYPE::Bool (*ToInt64Callback)(const RFTYPE::String& Instance,
                                            RFTYPE::Int32 Base, RFTYPE::Int64& Out);

    /// Function declaration for ToUInt64.
    typedef RFTYPE::Bool (*ToUInt64Callback)(const RFTYPE::String& Instance,
                                             RFTYPE::Int32 Base, RFTYPE::UInt64& Out);

    /// Function declaration for ToFloat64.
    typedef RFTYPE::Bool (*ToFloat64Callback)(const RFTYPE::String& Instance, 
                                              RFTYPE::Float64& Out);

    /// Function declaration for Format.
    typedef RFTYPE::Int32 (*FormatCallback)(RFTYPE::UInt8* Buffer, RFTYPE::Size BufferSize,
                                            const RFTYPE::String& Format, va_list arg);

    extern SetLocaleCallback SetLocale;
    extern GetLocaleCallback GetLocale;
    extern ToLowerCallback ToUpper;
    extern ToLowerCallback ToLower;
    extern LengthCallback Length;
    extern ToInt64Callback ToInt64;
    extern ToUInt64Callback ToUInt64;
    extern ToFloat64Callback ToFloat64;
    extern FormatCallback Format;
} } }
#endif // RF_SYSTEM_STRING_HPP