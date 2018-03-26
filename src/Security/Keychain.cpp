#include "RadonFramework/Security/Keychain.hpp"
#include "RadonFramework/System/Security.hpp"
#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/System/Math/Hash/pbkdf2.hpp>

namespace RadonFramework::Security {

void
Keychain::SetKeychainId(const RF_Type::String& Identifier)
{
  m_KeychainIdentifier = Identifier;
}

void
Keychain::AddUserData(const RF_Type::String& Identifier,
                      const RF_Collect::ByteArray& Data)
{
  RF_SysSecurity::WriteUserEncryptedData(m_KeychainIdentifier + Identifier,
                                         &Data(0), Data.Count());
}

void
Keychain::AddEncryptedUserPassword(const RF_Type::String& Username,
                                   RF_Type::String& Password,
                                   RF_Collect::ByteArray& WriteSecretTo,
                                   const RF_Type::Size HashLength /*= 128*/,
                                   const RF_Type::Size Iterations /*= 4096*/,
                                   const RF_Type::Size SecretLength /*= 32*/)
{
  RF_Mem::AutoPointerArray<RF_Type::UInt8> secret(SecretLength);
  RF_SysSecurity::GenerateRandom(secret.Get(), secret.Size());

  RF_Collect::ByteArray key(HashLength);
  RF_SysHash::pkcs5_pbkdf2(Password.c_str(), Password.Size() - 1, secret.Get(),
                           secret.Count(), &key(0), key.Count(), Iterations);
  WriteSecretTo.Resize(SecretLength);
  RF_SysMem::Copy(&WriteSecretTo(0), secret.Get(), secret.Size());
  AddUserData(Username, key);

  RF_SysSecurity::EnsureFillZeros(secret.Get(), secret.Size());
  RF_SysSecurity::EnsureFillZeros(&key(0), key.Count());
  RF_SysSecurity::EnsureFillZeros(
    const_cast<RF_Type::UInt8*>(Password.ByteData()), Password.Size());
  Password.Clear();
}

RF_Type::Bool
Keychain::GetUserData(const RF_Type::String& Identifier,
                      RF_Collect::ByteArray& Data)
{
  Data.Resize(
    RF_SysSecurity::UserEncryptedDataSize(m_KeychainIdentifier + Identifier));
  return RF_SysSecurity::ReadUserEncryptedData(
    m_KeychainIdentifier + Identifier, &Data(0), Data.Count());
}

RF_Type::Bool
Keychain::DoesUserDataExists(const RF_Type::String& Identifier)
{
  return RF_SysSecurity::IsUserEncryptedEntryAvailable(m_KeychainIdentifier +
                                                       Identifier);
}

RF_Type::Bool
Keychain::RemoveUserData(const RF_Type::String& Identifier)
{
  return RF_SysSecurity::RemoveUserEncryptedData(m_KeychainIdentifier +
                                                 Identifier);
}

Keychain::Keychain(const RF_Type::String& Identifier)
  : m_KeychainIdentifier(Identifier)
{}

} // namespace RadonFramework::Security
