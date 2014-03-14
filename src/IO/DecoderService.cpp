#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/DecoderService.hpp>
#include <RadonFramework/IO/DecoderServiceLocator.hpp>

using namespace RadonFramework::IO;

DecoderService::DecoderService(const RadonFramework::Core::Types::String &Name)
:Service(Name),
 m_IsAvailable(false)
{

}

DecoderService::DecoderService(const RadonFramework::Core::Types::String &Name,const unsigned int FourCC)
:Service(Name),
 m_FourCC(FourCC)
{
}

const unsigned int DecoderService::FourCC()
{
  return m_FourCC;
}

bool DecoderService::IsAvailable()
{
    return m_IsAvailable;
}
