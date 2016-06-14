#include "RadonFramework/precompiled.hpp"
#include <X11/Xlib.h>

#undef Bool
#undef True
#undef False

#include <RadonFramework/backend/X11/Forms/X11WindowService.hpp>
#include <RadonFramework/backend/X11/Forms/X11Window.hpp>
#include <RadonFramework/backend/X11/Forms/X11Application.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include "RadonFramework/Collections/AutoVector.hpp"

using namespace RadonFramework::Forms;
using namespace RadonFramework::Math::Geometry;
using namespace RadonFramework::Collections;

X11WindowService::X11WindowService(const Core::Types::String &Name)
:WindowService(Name),m_Application(0)
{
}

X11WindowService::~X11WindowService()
{
}

IWindow* X11WindowService::NewWindow()
{
    return new X11Window(this);
}

AbstractApplication* X11WindowService::Application()
{
    if (!m_Application)
        m_Application=new X11Application;
    return m_Application;
}

//Size X11WindowService::ScreenResolution()
//{
//    int ModeCount;
//    XRRScreenSize *xrrs = XRRSizes(((X11Application*)m_Application)->GetDisplay(), 0, &ModeCount);
//    Window root = RootWindow(((X11Application*)m_Application)->GetDisplay(), 0);
//    XRRScreenConfiguration *conf = XRRGetScreenInfo(((X11Application*)m_Application)->GetDisplay(), root);
//    Rotation original_rotation;
//    SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
//
//    return Size(xrrs[original_size_id].width,xrrs[original_size_id].height);
//}

AutoVector<DisplayInformation> X11WindowService::GetAllDisplays()
{
    return AutoVector<DisplayInformation>();
}

WindowServiceError X11WindowService::ScreenResolution(const DisplayInformation& DiplayInfo,
                                                      Core::Types::UInt32& ResolutionListIndex)
{
    ResolutionListIndex=0; return WindowServiceError::Generate(WindowServiceErrors::InvalidArgument);
}

void X11WindowService::ScreenResolution(const DisplayInformation& DiplayInfo,
                                        const Resolution& NewResolution)
{

}
