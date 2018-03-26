#include "RadonFramework/System/Security.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::System::Security {

RF_Type::Size
ReadUserEncryptedData_SystemAPIDispatcher(const RF_Type::String& Entryname,
                                          RF_Type::UInt8* WriteTo,
                                          const RF_Type::Size Bytes)
{
  ReadUserEncryptedData = 0;
  Dispatch();
  Assert(ReadUserEncryptedData != ReadUserEncryptedData_SystemAPIDispatcher &&
           ReadUserEncryptedData != 0,
         "Funtion was called and couldn't be dispatched");
  return ReadUserEncryptedData(Entryname, WriteTo, Bytes);
}

RF_Type::Bool
WriteUserEncryptedData_SystemAPIDispatcher(const RF_Type::String& Entryname,
                                           const RF_Type::UInt8* ReadFrom,
                                           const RF_Type::Size Bytes)
{
  WriteUserEncryptedData = 0;
  Dispatch();
  Assert(WriteUserEncryptedData != WriteUserEncryptedData_SystemAPIDispatcher &&
           WriteUserEncryptedData != 0,
         "Funtion was called and couldn't be dispatched");
  return WriteUserEncryptedData(Entryname, ReadFrom, Bytes);
}

RF_Type::Bool
RemoveUserEncryptedData_SystemAPIDispatcher(const RF_Type::String& Entryname)
{
  RemoveUserEncryptedData = 0;
  Dispatch();
  Assert(RemoveUserEncryptedData !=
             RemoveUserEncryptedData_SystemAPIDispatcher &&
           RemoveUserEncryptedData != 0,
         "Funtion was called and couldn't be dispatched");
  return RemoveUserEncryptedData(Entryname);
}

RF_Type::Size
UserEncryptedDataSize_SystemAPIDispatcher(const RF_Type::String& Entryname)
{
  UserEncryptedDataSize = 0;
  Dispatch();
  Assert(UserEncryptedDataSize != UserEncryptedDataSize_SystemAPIDispatcher &&
           UserEncryptedDataSize != 0,
         "Funtion was called and couldn't be dispatched");
  return UserEncryptedDataSize(Entryname);
}

RF_Type::Bool
IsUserEncryptedEntryAvailable_SystemAPIDispatcher(
  const RF_Type::String& Entryname)
{
  IsUserEncryptedEntryAvailable = 0;
  Dispatch();
  Assert(IsUserEncryptedEntryAvailable !=
             IsUserEncryptedEntryAvailable_SystemAPIDispatcher &&
           IsUserEncryptedEntryAvailable != 0,
         "Funtion was called and couldn't be dispatched");
  return IsUserEncryptedEntryAvailable(Entryname);
}

RF_Type::Bool
GenerateRandom_SystemAPIDispatcher(RF_Type::UInt8* Writeto,
                                   const RF_Type::Size NumberInBytes)
{
  GenerateRandom = 0;
  Dispatch();
  Assert(GenerateRandom != GenerateRandom_SystemAPIDispatcher &&
           GenerateRandom != 0,
         "Funtion was called and couldn't be dispatched");
  return GenerateRandom(Writeto, NumberInBytes);
}

void
EnsureFillZeros_SystemAPIDispatcher(RF_Type::UInt8* WriteAt,
                                    const RF_Type::Size Bytes)
{
  EnsureFillZeros = nullptr;
  Dispatch();
  Assert(EnsureFillZeros != EnsureFillZeros_SystemAPIDispatcher &&
           EnsureFillZeros != 0,
         "Funtion was called and couldn't be dispatched");
  EnsureFillZeros(WriteAt, Bytes);
}

ReadUserEncryptedDataCallback ReadUserEncryptedData =
  ReadUserEncryptedData_SystemAPIDispatcher;
WriteUserEncryptedDataCallback WriteUserEncryptedData =
  WriteUserEncryptedData_SystemAPIDispatcher;
RemoveUserEncryptedDataCallback RemoveUserEncryptedData =
  RemoveUserEncryptedData_SystemAPIDispatcher;
UserEncryptedDataSizeCallback UserEncryptedDataSize =
  UserEncryptedDataSize_SystemAPIDispatcher;
IsUserEncryptedEntryAvailableCallback IsUserEncryptedEntryAvailable =
  IsUserEncryptedEntryAvailable_SystemAPIDispatcher;
GenerateRandomCallback GenerateRandom = GenerateRandom_SystemAPIDispatcher;
EnsureFillZerosCallback EnsureFillZeros = EnsureFillZeros_SystemAPIDispatcher;

Bool
IsSuccessfullyDispatched()
{
  Bool result = true;
  result = result &&
           ReadUserEncryptedData != ReadUserEncryptedData_SystemAPIDispatcher &&
           ReadUserEncryptedData != 0;
  result =
    result &&
    WriteUserEncryptedData != WriteUserEncryptedData_SystemAPIDispatcher &&
    WriteUserEncryptedData != 0;
  result =
    result &&
    RemoveUserEncryptedData != RemoveUserEncryptedData_SystemAPIDispatcher &&
    RemoveUserEncryptedData != 0;
  result = result &&
           UserEncryptedDataSize != UserEncryptedDataSize_SystemAPIDispatcher &&
           UserEncryptedDataSize != 0;
  result = result &&
           IsUserEncryptedEntryAvailable !=
             IsUserEncryptedEntryAvailable_SystemAPIDispatcher &&
           IsUserEncryptedEntryAvailable != 0;
  result = result && GenerateRandom != GenerateRandom_SystemAPIDispatcher &&
           GenerateRandom != 0;
  result = result && EnsureFillZeros != EnsureFillZeros_SystemAPIDispatcher &&
           EnsureFillZeros != 0;
  return result;
}

void
GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result)
{
  if (ReadUserEncryptedData == ReadUserEncryptedData_SystemAPIDispatcher ||
      ReadUserEncryptedData == 0)
    Result.AddLast("ReadUserEncryptedData"_rfs);
  if (WriteUserEncryptedData == WriteUserEncryptedData_SystemAPIDispatcher ||
      WriteUserEncryptedData == 0)
    Result.AddLast("WriteUserEncryptedData"_rfs);
  if (RemoveUserEncryptedData == RemoveUserEncryptedData_SystemAPIDispatcher ||
      RemoveUserEncryptedData == 0)
    Result.AddLast("RemoveUserEncryptedData"_rfs);
  if (UserEncryptedDataSize == UserEncryptedDataSize_SystemAPIDispatcher ||
      UserEncryptedDataSize == 0)
    Result.AddLast("UserEncryptedDataSize"_rfs);
  if (IsUserEncryptedEntryAvailable ==
        IsUserEncryptedEntryAvailable_SystemAPIDispatcher ||
      IsUserEncryptedEntryAvailable == 0)
    Result.AddLast("IsUserEncryptedEntryAvailable"_rfs);
  if (GenerateRandom == GenerateRandom_SystemAPIDispatcher ||
      GenerateRandom == 0)
    Result.AddLast("GenerateRandom"_rfs);
  if (EnsureFillZeros == EnsureFillZeros_SystemAPIDispatcher ||
      EnsureFillZeros == 0)
    Result.AddLast("EnsureFillZeros"_rfs);
}

} // namespace RadonFramework::System::Security
