#include "RadonFramework/backend/hashlib++/HashlibHashfunctionService.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"
#include "RadonFramework/backend/hashlib++/hl_md5.h"
#include "RadonFramework/backend/hashlib++/hl_sha1.h"
#include "RadonFramework/backend/hashlib++/hl_sha256.h"
#include "RadonFramework/backend/hashlib++/hl_sha2ext.h"
#include "RadonFramework/precompiled.hpp"

using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::Core::Types;

class HashlibMD5Hashfunction : public IHashfunction
{
protected:
  MD5 m_md5;
  HL_MD5_CTX m_ctx;
  UInt8 m_buf[16];

public:
  void Reset() final
  {
    m_md5.MD5Init(&m_ctx);
    RF_SysMem::Set(m_buf, 0, 16);
  }

  void Update(UInt8 Input) final { m_md5.MD5Update(&m_ctx, &Input, 1); }

  void Update(const UInt8* Data, UInt32 Size) final
  {
    m_md5.MD5Update(&m_ctx, const_cast<unsigned char*>(Data), Size);
  }

  void Final() final { m_md5.MD5Final(m_buf, &m_ctx); }

  String ToString() final
  {
    String result;
    for(int i : m_buf)
    {
      result += String::Format("%02X"_rfs, m_buf[i]);
    }
    return result;
  }

  UInt32 GetDigestLength() final { return 16; }

  UInt8* Digest() final { return m_buf; }
};

HashlibMD5HashfunctionService::HashlibMD5HashfunctionService(const String& Name)
: HashfunctionService(Name)
{
}

IHashfunction* HashlibMD5HashfunctionService::Create()
{
  return new HashlibMD5Hashfunction;
}

void HashlibMD5HashfunctionService::Free(IHashfunction*& Instance)
{
  if(Instance != nullptr)
  {
    delete Instance;
    Instance = nullptr;
  }
}

RF_Type::Size
RadonFramework::Math::Hash::HashlibMD5HashfunctionService::BitLength() const
{
  return 128;
}

class HashlibSHA1Hashfunction : public IHashfunction
{
protected:
  SHA1 m_sha1;
  HL_SHA1_CTX m_ctx;
  UInt8 m_buf[20];

public:
  void Reset() final
  {
    m_sha1.SHA1Reset(&m_ctx);
    RF_SysMem::Set(m_buf, 0, 20);
  }

  void Update(UInt8 Input) final { m_sha1.SHA1Input(&m_ctx, &Input, 1); }

  void Update(const UInt8* Data, UInt32 Size) final
  {
    m_sha1.SHA1Input(&m_ctx, Data, Size);
  }

  void Final() final { m_sha1.SHA1Result(&m_ctx, m_buf); }

  String ToString() final
  {
    String result;
    for(int i : m_buf)
    {
      result += String::Format("%02X"_rfs, m_buf[i]);
    }

    return result;
  }

  UInt32 GetDigestLength() final { return 20; }

  UInt8* Digest() final { return m_buf; }
};

HashlibSHA1HashfunctionService::HashlibSHA1HashfunctionService(
    const String& Name)
: HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA1HashfunctionService::Create()
{
  return new HashlibSHA1Hashfunction;
}

void HashlibSHA1HashfunctionService::Free(IHashfunction*& Instance)
{
  if(Instance != nullptr)
  {
    delete Instance;
    Instance = nullptr;
  }
}

RF_Type::Size
RadonFramework::Math::Hash::HashlibSHA1HashfunctionService::BitLength() const
{
  return 160;
}

class HashlibSHA256Hashfunction : public IHashfunction
{
protected:
  SHA256 m_sha256;
  HL_SHA256_CTX m_ctx;
  UInt8 m_buf[64];

public:
  void Reset() final
  {
    m_sha256.SHA256_Init(&m_ctx);
    RF_SysMem::Set(m_buf, 0, 64);
  }

  void Update(UInt8 Input) final { m_sha256.SHA256_Update(&m_ctx, &Input, 1); }

  void Update(const UInt8* Data, UInt32 Size) final
  {
    m_sha256.SHA256_Update(&m_ctx, Data, Size);
  }

  void Final() final
  {
    m_sha256.SHA256_End(&m_ctx, reinterpret_cast<char*>(m_buf));
  }

  String ToString() final
  {
    String result;
    for(int i : m_buf)
    {
      result += String::Format("%02X"_rfs, m_buf[i]);
    }
    return result;
  }

  UInt32 GetDigestLength() final { return 64; }

  UInt8* Digest() final { return m_buf; }
};

HashlibSHA256HashfunctionService::HashlibSHA256HashfunctionService(
    const String& Name)
: HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA256HashfunctionService::Create()
{
  return new HashlibSHA256Hashfunction;
}

void HashlibSHA256HashfunctionService::Free(IHashfunction*& Instance)
{
  if(Instance != nullptr)
  {
    delete Instance;
    Instance = nullptr;
  }
}

RF_Type::Size
RadonFramework::Math::Hash::HashlibSHA256HashfunctionService::BitLength() const
{
  return 256;
}

class HashlibSHA384Hashfunction : public IHashfunction
{
protected:
  SHA2ext m_sha384;
  HL_SHA_384_CTX m_ctx;
  UInt8 m_buf[96];

public:
  void Reset() final
  {
    m_sha384.SHA384_Init(&m_ctx);
    RF_SysMem::Set(m_buf, 0, 96);
  }

  void Update(UInt8 Input) final { m_sha384.SHA384_Update(&m_ctx, &Input, 1); }

  void Update(const UInt8* Data, UInt32 Size) final
  {
    m_sha384.SHA384_Update(&m_ctx, Data, Size);
  }

  void Final() final
  {
    m_sha384.SHA384_End(&m_ctx, reinterpret_cast<char*>(m_buf));
  }

  String ToString() final
  {
    String result;
    for(int i : m_buf)
    {
      result += String::Format("%02X"_rfs, m_buf[i]);
    }
    return result;
  }

  UInt32 GetDigestLength() final { return 96; }

  UInt8* Digest() final { return m_buf; }
};

HashlibSHA384HashfunctionService::HashlibSHA384HashfunctionService(
    const String& Name)
: HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA384HashfunctionService::Create()
{
  return new HashlibSHA384Hashfunction;
}

void HashlibSHA384HashfunctionService::Free(IHashfunction*& Instance)
{
  if(Instance != nullptr)
  {
    delete Instance;
    Instance = nullptr;
  }
}

RF_Type::Size
RadonFramework::Math::Hash::HashlibSHA384HashfunctionService::BitLength() const
{
  return 384;
}

class HashlibSHA512Hashfunction : public IHashfunction
{
protected:
  SHA2ext m_sha512;
  HL_SHA512_CTX m_ctx;
  UInt8 m_buf[128];

public:
  void Reset() final
  {
    m_sha512.SHA512_Init(&m_ctx);
    RF_SysMem::Set(m_buf, 0, 128);
  }

  void Update(UInt8 Input) final { m_sha512.SHA512_Update(&m_ctx, &Input, 1); }

  void Update(const UInt8* Data, UInt32 Size) final
  {
    m_sha512.SHA512_Update(&m_ctx, Data, Size);
  }

  void Final() final
  {
    m_sha512.SHA512_End(&m_ctx, reinterpret_cast<char*>(m_buf));
  }

  String ToString() final
  {
    String result;
    for(int i : m_buf)
    {
      result += String::Format("%02X"_rfs, m_buf[i]);
    }
    return result;
  }

  UInt32 GetDigestLength() final { return 128; }
  UInt8* Digest() final { return m_buf; }
};

HashlibSHA512HashfunctionService::HashlibSHA512HashfunctionService(
    const String& Name)
: HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA512HashfunctionService::Create()
{
  return new HashlibSHA512Hashfunction;
}

void HashlibSHA512HashfunctionService::Free(IHashfunction*& Instance)
{
  if(Instance != nullptr)
  {
    delete Instance;
    Instance = nullptr;
  }
}

RF_Type::Size
RadonFramework::Math::Hash::HashlibSHA512HashfunctionService::BitLength() const
{
  return 512;
}
