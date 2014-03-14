#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/WindowService.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging;

template <typename Parent, typename ErrorEnum,UInt32 ErrorCount>
String Error<Parent,ErrorEnum,ErrorCount>::ErrorText[ErrorCount]={"",
                                                                  "",
                                                                  "",
                                                                  ""};

WindowService::WindowService(const String &Name)
:Service(Name)
{
}

WindowService::~WindowService()
{
}
