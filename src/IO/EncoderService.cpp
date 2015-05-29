#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/EncoderService.hpp>
#include <RadonFramework/IO/EncoderServiceLocator.hpp>

namespace RadonFramework { namespace IO {

EncoderService::EncoderService(const RF_Type::String &Name)
:Service(Name),
m_IsAvailable(false)
{

}

RF_Type::Bool EncoderService::IsAvailable()const
{
    return m_IsAvailable;
}

RF_Type::Bool EncoderService::IsFourCCSupported(const RF_Type::UInt32 FourCC) const
{
    return false;
}

RF_Type::Bool EncoderService::IsEncoderInterface(const RF_Type::UInt32 FourCC, 
                                                 RF_Encoders::Interface Target) const
{
    return false;
}

} }