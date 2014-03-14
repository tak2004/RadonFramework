#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/Forms/Screen.hpp>
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>

using namespace RadonFramework::Forms;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;

AutoPointerArray<Screen> Screen::m_Screens;

Screen::Screen()
:m_CurrentResolution(0)
{

}

Screen::~Screen()
{

}

ScreenError::Type Screen::ChangeResolution( const Resolution& NewResolution )const
{
    WindowServiceLocator::Default().ScreenResolution(*m_DisplayInfos,NewResolution);
    WindowServiceError err=WindowServiceLocator::Default().ScreenResolution(*m_DisplayInfos,m_CurrentResolution);
    return ScreenError::NoError;
}

const AutoPointerArray<Screen>& Screen::AllScreens()
{
    AutoVector<DisplayInformation> displaylist=WindowServiceLocator::Default().GetAllDisplays();
    m_Screens=AutoPointerArray<Screen>(new Screen[displaylist.Size()],displaylist.Size());
    UInt32 resindex=0;
    for (UInt32 i=0;i<m_Screens.Count();++i)
    {
        WindowServiceError err=WindowServiceLocator::Default().ScreenResolution(*displaylist[displaylist.Size()-1],resindex);
        AutoPointer<DisplayInformation> display;
        displaylist.PopBack(&display);
        m_Screens[i]=Screen(display,resindex);
    }
    return m_Screens;
}

const Screen& Screen::PrimaryScreen()
{
    static Screen invalidScreen;
    const AutoPointerArray<Screen>& screens=AllScreens();
    Assert(0 != screens.Count(), "No screen available.");
    for (UInt32 i = 0; i < screens.Count(); ++i)
        if (screens[i].IsPrimary())
            return screens[i];
    return invalidScreen;
}

Screen::Screen(const Screen& Copy)
{
    *this=Copy;
}

Screen& Screen::operator=(const Screen& Other)
{
    if (!m_DisplayInfos.Get())
        m_DisplayInfos=AutoPointer<DisplayInformation>(new DisplayInformation);
    *m_DisplayInfos=*Other.m_DisplayInfos.Get();
    m_CurrentResolution=Other.m_CurrentResolution;
    return *this;
}

Screen::Screen(AutoPointer<DisplayInformation> DisplayInfos,
               const UInt32 CurrentResolution)
:m_CurrentResolution(CurrentResolution)
,m_DisplayInfos(DisplayInfos)
{
}
