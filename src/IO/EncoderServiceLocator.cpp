#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/EncoderServiceLocator.hpp>

using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

namespace RadonFramework::IO {

EncoderServiceLocator::Iterator EncoderServiceLocator::FindCodec(
    const RF_Type::UInt32 FCC, RF_Encoders::Interface Target)
{
    for(EncoderServiceLocator::Iterator it = EncoderServiceLocator::m_Services.Begin();
        it != EncoderServiceLocator::m_Services.End(); ++it)
    {
        if((*it)->IsEncoderInterface(FCC, Target))
            return it;
    }
    return EncoderServiceLocator::m_Services.End();
}

EncoderServiceLocator::Iterator EncoderServiceLocator::FindByNameOrFourCC(
    const RF_Type::String& Name, const RF_Type::UInt32 FCC)
{
    for(EncoderServiceLocator::Iterator it = EncoderServiceLocator::m_Services.Begin();
        it != EncoderServiceLocator::m_Services.End(); ++it)
    {
        if((*it)->Name() == Name || (*it)->IsFourCCSupported(FCC))
            return it;
    }
    return EncoderServiceLocator::m_Services.End();
}

}