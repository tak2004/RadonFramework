#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/backend/hashlib++/HashlibHashfunctionService.hpp"
#include "RadonFramework/backend/hashlib++/hl_md5.h"
#include "RadonFramework/backend/hashlib++/hl_sha1.h"
#include "RadonFramework/backend/hashlib++/hl_sha256.h"
#include "RadonFramework/backend/hashlib++/hl_sha2ext.h"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"

using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::Core::Types;

class HashlibMD5Hashfunction:public IHashfunction
{
    protected:
        MD5 m_md5;
        HL_MD5_CTX m_ctx;
        UInt8 m_buf[16];
    public:
        void Reset()
        {
            m_md5.MD5Init(&m_ctx);
            RFMEM::Set(m_buf,0,16);
        }

        void Update(UInt8 Input)
        {
            m_md5.MD5Update(&m_ctx,&Input,1);
        }

        void Update(const UInt8* Data, UInt32 Size)
        {
            m_md5.MD5Update(&m_ctx,const_cast<unsigned char*>(Data),Size);
        }

        void Final()
        {
            m_md5.MD5Final(m_buf,&m_ctx);
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(RF_Type::String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 16;
        }

        UInt8* Digest()
        {
            return m_buf;
        }
};

HashlibMD5HashfunctionService::HashlibMD5HashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* HashlibMD5HashfunctionService::Create()
{
  return new HashlibMD5Hashfunction;
}


class HashlibSHA1Hashfunction:public IHashfunction
{
    protected:
        SHA1 m_sha1;
        HL_SHA1_CTX m_ctx;
        UInt8 m_buf[20];
    public:
        void Reset()
        {
            m_sha1.SHA1Reset(&m_ctx);
            RFMEM::Set(m_buf,0,20);
        }

        void Update(UInt8 Input)
        {
            m_sha1.SHA1Input(&m_ctx,&Input,1);
        }

        void Update(const UInt8 * Data, UInt32 Size)
        {
            m_sha1.SHA1Input(&m_ctx,Data,Size);
        }

        void Final()
        {
            m_sha1.SHA1Result(&m_ctx,m_buf);
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(RF_Type::String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 20;
        }

        UInt8* Digest()
        {
            return m_buf;
        }
};

HashlibSHA1HashfunctionService::HashlibSHA1HashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA1HashfunctionService::Create()
{
    return new HashlibSHA1Hashfunction;
}


class HashlibSHA256Hashfunction:public IHashfunction
{
    protected:
        SHA256 m_sha256;
        HL_SHA256_CTX m_ctx;
        UInt8 m_buf[65];
    public:
        void Reset()
        {
            m_sha256.SHA256_Init(&m_ctx);
            RFMEM::Set(m_buf,0,65);
        }

        void Update(UInt8 Input)
        {
            m_sha256.SHA256_Update(&m_ctx,&Input,1);
        }

        void Update(const UInt8* Data, UInt32 Size)
        {
            m_sha256.SHA256_Update(&m_ctx,Data,Size);
        }

        void Final()
        {
            m_sha256.SHA256_End(&m_ctx,reinterpret_cast<char*>(m_buf));
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(RF_Type::String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 64;
        }

        UInt8* Digest()
        {
            return m_buf;
        }
};

HashlibSHA256HashfunctionService::HashlibSHA256HashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA256HashfunctionService::Create()
{
    return new HashlibSHA256Hashfunction;
}


class HashlibSHA384Hashfunction:public IHashfunction
{
    protected:
        SHA2ext m_sha384;
        HL_SHA_384_CTX m_ctx;
        UInt8 m_buf[97];
    public:
        void Reset()
        {
            m_sha384.SHA384_Init(&m_ctx);
            RFMEM::Set(m_buf,0,97);
        }

        void Update(UInt8 Input)
        {
            m_sha384.SHA384_Update(&m_ctx,&Input,1);
        }

        void Update(const UInt8 * Data, UInt32 Size)
        {
            m_sha384.SHA384_Update(&m_ctx,Data,Size);
        }

        void Final()
        {
            m_sha384.SHA384_End(&m_ctx,reinterpret_cast<char*>(m_buf));
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(RF_Type::String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 96;
        }

        UInt8* Digest()
        {
            return m_buf;
        }
};

HashlibSHA384HashfunctionService::HashlibSHA384HashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA384HashfunctionService::Create()
{
    return new HashlibSHA384Hashfunction;
}


class HashlibSHA512Hashfunction:public IHashfunction
{
    protected:
        SHA2ext m_sha512;
        HL_SHA512_CTX m_ctx;
        UInt8 m_buf[129];
    public:
        void Reset()
        {
            m_sha512.SHA512_Init(&m_ctx);
            RFMEM::Set(m_buf,0,129);
        }

        void Update(UInt8 Input)
        {
            m_sha512.SHA512_Update(&m_ctx,&Input,1);
        }

        void Update(const UInt8* Data, UInt32 Size)
        {
            m_sha512.SHA512_Update(&m_ctx,Data,Size);
        }

        void Final()
        {
            m_sha512.SHA512_End(&m_ctx,reinterpret_cast<char*>(m_buf));
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(RF_Type::String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 128;
        }
        UInt8* Digest()
        {
            return m_buf;
        }
};

HashlibSHA512HashfunctionService::HashlibSHA512HashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* HashlibSHA512HashfunctionService::Create()
{
    return new HashlibSHA512Hashfunction;
}
