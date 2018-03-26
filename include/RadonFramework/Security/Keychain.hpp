#ifndef RF_SECURITY_KEYCHAIN_HPP
#define RF_SECURITY_KEYCHAIN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework::Security {

class Keychain
{
public:
  Keychain(const RF_Type::String& Identifier);
  void SetKeychainId(const RF_Type::String& Identifier);
  /// Add a value to the key-chain with the given identifier.
  void AddUserData(const RF_Type::String& Identifier,
                   const RF_Collect::ByteArray& Data);

  /// Generate a secure password representation of the given password.
  /// It use PBKDF2 with SHA-1 to encrypt the password and erase the variable
  /// itself.
  void AddEncryptedUserPassword(const RF_Type::String& Username,
                                RF_Type::String& Password,
                                RF_Collect::ByteArray& WriteSecretTo,
                                const RF_Type::Size HashLength = 128,
                                const RF_Type::Size Iterations = 4096,
                                const RF_Type::Size SecretLength = 32);

  RF_Type::Bool GetUserData(const RF_Type::String& Identifier,
                            RF_Collect::ByteArray& Data);

  RF_Type::Bool DoesUserDataExists(const RF_Type::String& Identifier);
  RF_Type::Bool RemoveUserData(const RF_Type::String& Identifier);

protected:
  RF_Type::String m_KeychainIdentifier;
};

} // namespace RadonFramework::Security

#ifndef RF_SHORTHAND_NAMESPACE_SECURITY
#define RF_SHORTHAND_NAMESPACE_SECURITY
namespace RF_Security = RadonFramework::Security;
#endif

#endif //! RF_SECURITY_KEYCHAIN_HPP
