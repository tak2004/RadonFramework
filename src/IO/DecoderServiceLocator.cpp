#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/DecoderServiceLocator.hpp>

using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

namespace RadonFramework { namespace IO {

DecoderServiceLocator::Iterator DecoderServiceLocator::FindCodec(
    const RF_Type::UInt32 FCC, RF_Decoders::Interface Target)
{
    for(DecoderServiceLocator::Iterator it = DecoderServiceLocator::m_Services.Begin();
        it != DecoderServiceLocator::m_Services.End(); ++it)
    {
        if((*it)->IsDecoderInterface(FCC, Target))
            return it;
    }
    return DecoderServiceLocator::m_Services.End();
}

DecoderServiceLocator::Iterator DecoderServiceLocator::FindByNameOrFourCC(
    const RF_Type::String& Name, const RF_Type::UInt32 FCC)
{
    for(DecoderServiceLocator::Iterator it = DecoderServiceLocator::m_Services.Begin();
        it != DecoderServiceLocator::m_Services.End(); ++it)
    {
        if((*it)->Name(Name) || (*it)->IsFourCCSupported(FCC))
            return it;
    }
    return DecoderServiceLocator::m_Services.End();
}

} }