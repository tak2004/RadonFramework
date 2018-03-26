#ifndef RF_SYSTEM_SECURITY_HPP
#define RF_SYSTEM_SECURITY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework::System::Security {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
 * check if the dispatching was successfully.
 **/
RF_Type::Bool IsSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result);

using ReadUserEncryptedDataCallback =
  RF_Type::Size (*)(const RF_Type::String& Entryname, RF_Type::UInt8* WriteTo,
                    const RF_Type::Size Bytes);
using WriteUserEncryptedDataCallback =
  RF_Type::Bool (*)(const RF_Type::String& Entryname,
                    const RF_Type::UInt8* ReadFrom, const RF_Type::Size Bytes);
using RemoveUserEncryptedDataCallback =
  RF_Type::Bool (*)(const RF_Type::String& Entryname);
using UserEncryptedDataSizeCallback =
  RF_Type::Size (*)(const RF_Type::String& Entryname);
using IsUserEncryptedEntryAvailableCallback =
  RF_Type::Bool (*)(const RF_Type::String& Entryname);

using GenerateRandomCallback =
  RF_Type::Bool (*)(RF_Type::UInt8* Writeto, const RF_Type::Size NumberInBytes);

using EnsureFillZerosCallback = void (*)(RF_Type::UInt8* WriteAt,
                                         const RF_Type::Size Bytes);

extern ReadUserEncryptedDataCallback ReadUserEncryptedData;
extern WriteUserEncryptedDataCallback WriteUserEncryptedData;
extern RemoveUserEncryptedDataCallback RemoveUserEncryptedData;
extern UserEncryptedDataSizeCallback UserEncryptedDataSize;
extern IsUserEncryptedEntryAvailableCallback IsUserEncryptedEntryAvailable;

extern GenerateRandomCallback GenerateRandom;

extern EnsureFillZerosCallback EnsureFillZeros;

} // namespace RadonFramework::System::Security

#ifndef RF_SHORTHAND_NAMESPACE_SYSSECURITY
#define RF_SHORTHAND_NAMESPACE_SYSSECURITY
namespace RF_SysSecurity = RadonFramework::System::Security;
#endif

#endif // !RF_SYSTEM_SECURITY_HPP
