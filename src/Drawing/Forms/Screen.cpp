#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Screen.hpp"
#include "RadonFramework/Drawing/Forms/WindowServiceLocator.hpp"
#include "RadonFramework/Drawing/Forms/Form.hpp"

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
    m_Screens = AutoPointerArray<Screen>(displaylist.Count());
    UInt32 resindex=0;
    for (UInt32 i=0;i<m_Screens.Count();++i)
    {
        WindowServiceError err = WindowServiceLocator::Default().ScreenResolution(*displaylist[displaylist.Count() - 1], resindex);
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
    RF_ASSERT(0 != screens.Count(), "No screen available.");
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

static const RF_Type::Float32 MM2INCH = 0.0393700787f;

RF_Type::UInt32 RadonFramework::Forms::Screen::DPIY() const
{
    RF_Type::Float32 verticalInches = static_cast<float>(m_DisplayInfos->VerticalLengthInMilimeter)*MM2INCH;
    RF_Type::Float32 resolutionHeight = static_cast<float>(m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Height);
    return  static_cast<RF_Type::UInt32>(resolutionHeight / verticalInches);
}

RF_Type::UInt32 RadonFramework::Forms::Screen::DPIX() const
{
    RF_Type::Float32 horizontalInches = static_cast<float>(m_DisplayInfos->HorizontalLengthInMilimeter)*MM2INCH;
    RF_Type::Float32 resolutionWidth = static_cast<float>(m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Width);
    return  static_cast<RF_Type::UInt32>(resolutionWidth / horizontalInches);
}
