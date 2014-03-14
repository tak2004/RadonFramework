#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Hash/Hash.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"

using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

AutoPointerArray<UInt8> Hash::Generate(const UInt8 * Data, UInt32 Size,
                                       IHashfunction& Hashfunction)
{
    AutoPointerArray<UInt8> result;
    Hashfunction.Reset();
    Hashfunction.Update((unsigned char*)Data,Size);
    Hashfunction.Final();
    result=AutoPointerArray<UInt8>(new UInt8[Hashfunction.GetDigestLength()],Hashfunction.GetDigestLength());
    RFMEM::Copy(result.Get(),Hashfunction.Digest(),Hashfunction.GetDigestLength());
    return result;
}

AutoPointerArray<UInt8> Hash::Generate(const UInt8 * Data, UInt32 Size,
                                       const String& HashFunctionName)
{
    static HashfunctionService* cacheService=0;
    static IHashfunction* cacheFunction=0;
    
    HashfunctionService* service=0;
    IHashfunction* function=0;

    if (cacheService && cacheService->Name()==HashFunctionName)
    {
        service=cacheService;
        function=cacheFunction;
    }
    else
    {
        service=&HashfunctionServiceLocator::Find(HashFunctionName);
        cacheService=service;
        function=service->Create();
        cacheFunction=function;
    }

    return Generate(Data,Size,*function);
}

AutoPointerArray<UInt8> Hash::Generate(const char* Text, const String& HashFunctionName)
{
    UInt32 len=static_cast<UInt32>(strlen(Text));
    return Generate(reinterpret_cast<const UInt8*>(Text),len,HashFunctionName);
}
