#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Core/Types/UInt32.hpp"

using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;

AccessMode::Type RF_IO::operator |(const AccessMode::Type A, const AccessMode::Type B)
{
    return static_cast<AccessMode::Type>(static_cast<UInt32>(A)|static_cast<UInt32>(B));
}

AccessMode::Type& RF_IO::operator |=(AccessMode::Type& A, const AccessMode::Type B)
{
    A=A|B;
    return A;
}