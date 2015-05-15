#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/DecoderService.hpp>
#include <RadonFramework/IO/DecoderServiceLocator.hpp>

namespace RadonFramework { namespace IO {

DecoderService::DecoderService(const RF_Type::String &Name)
:Service(Name),
m_IsAvailable(false)
{

}

RF_Type::Bool DecoderService::IsAvailable()const
{
    return m_IsAvailable;
}

RF_Type::Bool DecoderService::IsFourCCSupported(const RF_Type::UInt32 FourCC) const
{
    return false;
}

RF_Type::Bool DecoderService::IsDecoderInterface(const RF_Type::UInt32 FourCC, 
                                                 RF_Decoders::Interface Target) const
{
    return false;
}

} }