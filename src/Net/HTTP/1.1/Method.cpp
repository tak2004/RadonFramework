#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/HTTP/1.1/Method.hpp"
#include "RadonFramework/Math/Integer.hpp"
#include <string.h>

using namespace RadonFramework::Net::HTTP::V1_1;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Math;

const char* Method::Value[]={
        "GET",
        "PUT",
        "HEAD",
        "POST",
        "TRACE",
        "DELETE",
        "OPTIONS",
        "CONNECT",
        ""
    };

UInt32 Method::ValueLen[]={
        3,
        3,
        4,
        4,
        5,
        6,
        7,
        7,
        0
    };

UInt32 Method::MaxLen=7;

Method::Type Method::Parse(const UInt8* Buffer, const UInt32 Bytes)
{
    // Use Bytes as index.
    // 0 means a invalid result.
    // 9. entry will be used for out of bound values
    static UInt32 LastIndex[]={8,8,8,1,3,4,5,7,8};
    static UInt32 FirstIndex[]={8,8,8,0,2,4,5,6,8};

    // Clamp the values between 0 and 8 to map out of bound values to 8.
    UInt32 clampedLen=Integer<UInt32>::ClampUpperBound(Bytes,MaxLen);
    UInt32 index=FirstIndex[clampedLen];
    UInt32 lastIndex=LastIndex[clampedLen];

    if (index<8)
        for (;index<lastIndex;++index)
            if (RFMEM::Compare(Buffer,Value[index],Bytes)==0)
                return Method::Type(index);
    return Unknown;
}