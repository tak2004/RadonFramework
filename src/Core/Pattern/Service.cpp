#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>

using namespace RadonFramework::Core::Pattern;
using namespace RadonFramework::Core::Types;

Service::Service(const String &Name)
:m_Name(Name)
{
}

Service::~Service()
{
}

const String& Service::Name()
{
  return m_Name;
}
