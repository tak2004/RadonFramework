#ifndef RF_SYSTEM_MATH_HASH_PBKDF2_HPP
#define RF_SYSTEM_MATH_HASH_PBKDF2_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::Math::Hash {

void hmac_sha1(const uint8_t* text, size_t text_len, const uint8_t* key,
               size_t key_len, uint8_t digest[20]);

int pkcs5_pbkdf2(const char* pass, size_t pass_len, const uint8_t* salt,
                 size_t salt_len, uint8_t* key, size_t key_len,
                 unsigned int rounds);
} // namespace RadonFramework::System::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_SYSHASH
#define RF_SHORTHAND_NAMESPACE_SYSHASH
namespace RF_SysHash = RadonFramework::System::Math::Hash;
#endif // RF_SHORTHAND_NAMESPACE_SYSHASH

#endif //! RF_SYSTEM_MATH_HASH_PBKDF2_HPP
