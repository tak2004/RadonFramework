#ifndef RF_SYSTEM_STRING_HPP
#define RF_SYSTEM_STRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <cstdarg>

namespace RadonFramework::Collections
{
template <class T>
class List;
}

namespace RadonFramework::Core::Types
{
class String;
}

namespace RadonFramework::System::String
{
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
using SetLocaleCallback =
    RF_Type::String (*)(const LocaleCategory::Type Category,
                        const RF_Type::String& Locale);

/// Function declaration for GetLocale.
using GetLocaleCallback = const RF_Type::String& (*)();

/// Function declaration for ToUpper.
using ToUpperCallback = RF_Type::Bool (*)(RF_Type::String& Instance);

/// Function declaration for ToLower.
using ToLowerCallback = RF_Type::Bool (*)(RF_Type::String& Instance);

/// Function declaration for Size.
using SizeCallback = RF_Type::Size (*)(const RF_Type::UInt8* Buffer,
                                       const RF_Type::Size BufferSize);

/// Function declaration for Length.
using LengthCallback = RF_Type::Size (*)(const RF_Type::UInt8* Buffer,
                                         const RF_Type::Size BufferSize);

/// Function declaration for ToInt64.
using ToInt64Callback = RF_Type::Bool (*)(const RF_Type::String& Instance,
                                          RF_Type::Int32 Base,
                                          RF_Type::Int64& Out);

/// Function declaration for ToUInt64.
using ToUInt64Callback = RF_Type::Bool (*)(const RF_Type::String& Instance,
                                           RF_Type::Int32 Base,
                                           RF_Type::UInt64& Out);

/// Function declaration for ToFloat64.
using ToFloat64Callback = RF_Type::Bool (*)(const RF_Type::String& Instance,
                                            RF_Type::Float64& Out);

/// Function declaration for Format.
using FormatCallback = RF_Type::Int32 (*)(RF_Type::UInt8* Buffer,
                                          RF_Type::Size BufferSize,
                                          const RF_Type::String& Format,
                                          va_list arg);

using FindCallback = const RF_Type::UInt8* (*)(const RF_Type::UInt8* Buffer,
                                               RF_Type::Size BufferSize,
                                               const RF_Type::UInt8* LookingFor,
                                               RF_Type::Size LookingForSize);

/// Set the language and its location for THIS APPLICATION.
extern SetLocaleCallback SetLocale;
/// Returns the language and location set for THIS APPLICATION.
extern GetLocaleCallback GetLocale;
///
extern ToLowerCallback ToUpper;
///
extern ToLowerCallback ToLower;
/// Returns the amount of bytes(including termination) of the specified string.
extern SizeCallback CStringSizeOf;
///
extern LengthCallback Length;
///
extern ToInt64Callback ToInt64;
///
extern ToUInt64Callback ToUInt64;
///
extern ToFloat64Callback ToFloat64;
///
extern FormatCallback Format;
///
extern FindCallback Find;

}  // namespace RadonFramework::System::String

#ifndef RF_SHORTHAND_NAMESPACE_SYSSTR
#define RF_SHORTHAND_NAMESPACE_SYSSTR
namespace RF_SysStr = RadonFramework::System::String;
#endif

#endif  // RF_SYSTEM_STRING_HPP