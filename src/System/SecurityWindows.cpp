#include "RadonFramework/System/Security.hpp"
#include "RadonFramework/precompiled.hpp"
#include <Windows.h>
#include <wincred.h>
#include <wincrypt.h>

namespace RadonFramework::System::Security::Windows {

RF_Type::Size
ReadUserEncryptedData(const RF_Type::String& Entryname, RF_Type::UInt8* WriteTo,
                      const RF_Type::Size Bytes)
{
  RF_Type::Size result = 0;
  PCREDENTIAL credout;
  if (CredRead(Entryname.c_str(), CRED_TYPE_GENERIC, 0, &credout)) {
    if (credout->CredentialBlobSize <= Bytes) {
      RF_SysMem::Copy(WriteTo, credout->CredentialBlob,
                      credout->CredentialBlobSize);
      result = credout->CredentialBlobSize;
    }
  }
  CredFree(credout);
  return result;
}

RF_Type::Bool
WriteUserEncryptedData(const RF_Type::String& Entryname,
                       const RF_Type::UInt8* ReadFrom,
                       const RF_Type::Size Bytes)
{
  CREDENTIAL cred;
  memset(&cred, 0, sizeof(cred));
  cred.Type = CRED_TYPE_GENERIC;
  cred.TargetName = const_cast<char*>(Entryname.c_str());
  cred.CredentialBlobSize = Bytes;
  cred.CredentialBlob = (LPBYTE)ReadFrom;
  cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
  auto result = CredWrite(&cred, 0);
  SecureZeroMemory(&cred,
                   sizeof(cred)); // Ensure that the secret data aren't stored.
  return result;
}

RF_Type::Bool
RemoveUserEncryptedData(const RF_Type::String& Entryname)
{
  return CredDelete(Entryname.c_str(), CRED_TYPE_GENERIC, 0);
}

RF_Type::Size
UserEncryptedDataSize(const RF_Type::String& Entryname)
{
  RF_Type::Size result = 0;
  PCREDENTIAL credout;
  if (CredRead(Entryname.c_str(), CRED_TYPE_GENERIC, 0, &credout)) {
    result = credout->CredentialBlobSize;
  }
  CredFree(credout);
  return result;
}

RF_Type::Bool
IsUserEncryptedEntryAvailable(const RF_Type::String& Entryname)
{
  PCREDENTIAL credout;
  auto result = CredRead(Entryname.c_str(), CRED_TYPE_GENERIC, 0, &credout);
  CredFree(credout);
  return result;
}

typedef BOOLEAN (*RtlGenRandomFunction)(_Out_ PVOID RandomBuffer,
                                        _In_ ULONG RandomBufferLength);

RtlGenRandomFunction RtlGenRandom = nullptr;

RF_Type::Bool
GenerateRandom(RF_Type::UInt8* Writeto, const RF_Type::Size NumberInBytes)
{
  return RtlGenRandom(Writeto, NumberInBytes);
}

void
EnsureFillZeros(RF_Type::UInt8* WriteAt, const RF_Type::Size Bytes)
{
  SecureZeroMemory(WriteAt, Bytes);
}

} // namespace RadonFramework::System::Security::Windows

namespace RadonFramework::System::Security {

void
Dispatch()
{
  ReadUserEncryptedData = Windows::ReadUserEncryptedData;
  WriteUserEncryptedData = Windows::WriteUserEncryptedData;
  RemoveUserEncryptedData = Windows::RemoveUserEncryptedData;
  UserEncryptedDataSize = Windows::UserEncryptedDataSize;
  IsUserEncryptedEntryAvailable = Windows::IsUserEncryptedEntryAvailable;
  auto advancedAPIModule = LoadLibrary("Advapi32.dll");
  Windows::RtlGenRandom = reinterpret_cast<Windows::RtlGenRandomFunction>(
    GetProcAddress(advancedAPIModule, "SystemFunction036"));
  if (Windows::RtlGenRandom) {
    GenerateRandom = Windows::GenerateRandom;
  }
  EnsureFillZeros = Windows::EnsureFillZeros;
}

} // namespace RadonFramework::System::Security
