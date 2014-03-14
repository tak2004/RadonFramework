#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/Process/ModuleInformation.hpp>
#include <RadonFramework/Core/Types/String.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Profiling::Process;

ModuleInformation::ModuleInformation()
{

}

ModuleInformation::ModuleInformation(const ModuleInformation& Copy)
{
    m_Name=Copy.m_Name;
}

ModuleInformation::ModuleInformation( String& Name )
:m_Name(Name)
{
}

const String& ModuleInformation::Name()const
{
    return m_Name;
}