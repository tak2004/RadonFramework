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
RF_Type::Bool IsSuccessfullyDispatched();
                
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

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
typedef RF_Type::String (*SetLocaleCallback)(const LocaleCategory::Type Category,
                                            const RF_Type::String& Locale);

/// Function declaration for GetLocale.
typedef const RF_Type::String& (*GetLocaleCallback)();

/// Function declaration for ToUpper.
typedef RF_Type::Bool (*ToUpperCallback)(RF_Type::String& Instance);

/// Function declaration for ToLower.
typedef RF_Type::Bool (*ToLowerCallback)(RF_Type::String& Instance);

/// Function declaration for Size.
typedef RF_Type::Size (*SizeCallback)(const RF_Type::UInt8* Buffer, 
                                     const RF_Type::Size BufferSize);

/// Function declaration for Length.
typedef RF_Type::Size(*LengthCallback)(const RF_Type::UInt8* Buffer,
    const RF_Type::Size BufferSize);

/// Function declaration for ToInt64.
typedef RF_Type::Bool (*ToInt64Callback)(const RF_Type::String& Instance,
                                        RF_Type::Int32 Base, RF_Type::Int64& Out);

/// Function declaration for ToUInt64.
typedef RF_Type::Bool (*ToUInt64Callback)(const RF_Type::String& Instance,
                                            RF_Type::Int32 Base, RF_Type::UInt64& Out);

/// Function declaration for ToFloat64.
typedef RF_Type::Bool (*ToFloat64Callback)(const RF_Type::String& Instance, 
                                            RF_Type::Float64& Out);

/// Function declaration for Format.
typedef RF_Type::Int32 (*FormatCallback)(RF_Type::UInt8* Buffer, RF_Type::Size BufferSize,
                                        const RF_Type::String& Format, va_list arg);

extern SetLocaleCallback SetLocale;
extern GetLocaleCallback GetLocale;
extern ToLowerCallback ToUpper;
extern ToLowerCallback ToLower;
extern SizeCallback CStringSizeOf;
extern LengthCallback Length;
extern ToInt64Callback ToInt64;
extern ToUInt64Callback ToUInt64;
extern ToFloat64Callback ToFloat64;
extern FormatCallback Format;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSSTR
#define RF_SHORTHAND_NAMESPACE_SYSSTR
namespace RF_SysStr = RadonFramework::System::String;
#endif

#endif // RF_SYSTEM_STRING_HPP