#ifndef RF_DRAWING_FORM_SCREEN_HPP
#define RF_DRAWING_FORM_SCREEN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Drawing/Forms/DisplayInformation.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Forms
{
class Form;

namespace ScreenError
{
enum Type
{
  NoError,
  ResolutionNotSupported,  // the device don't support this resolution
  InvalidParameter  // one or more parameter are invalid(like BitsPerPixel=0)
};
}

class Screen
{
public:
  ~Screen();

  /// Return a list of all supported resolutions by this screen.
  const RF_Collect::Array<Resolution>& SupportedResolutions() const;
  /// Return the width of the current resolution.
  RF_Type::UInt32 Width() const;
  /// Return the height of the current resolution.
  RF_Type::UInt32 Height() const;
  /// Return the dots per inch on x-axis.
  RF_Type::UInt32 DPIX() const;
  /// return the dots per inch on y-axis.
  RF_Type::UInt32 DPIY() const;
  /// Return the left start position of the screen on the whole desktop.
  RF_Type::Int32 Left() const;
  /// Return the top start position of the screen on the whole desktop.
  RF_Type::Int32 Top() const;
  /// Return the start position of the screen on the whole desktop.
  RF_Geo::Point2D<> Position() const;
  /// Return the bits per pixel of the current resolution.
  RF_Type::UInt32 BitsPerPixel() const;
  /// Return the device name of this screen.
  RF_Type::String DeviceName() const;
  /// Return true if this is the primary screen else false.
  RF_Type::Bool IsPrimary() const;
  /// Return true if this display is mirrored.
  RF_Type::Bool IsMirroring() const;
  /// Return true if this display is attached to desktop.
  RF_Type::Bool IsAttachedToDesktop() const;
  /// Return the current selected resolution.
  const Resolution& CurrentResolution() const;

  /// Try to change the resolution of this screen to NewResolution.
  ScreenError::Type ChangeResolution(const Resolution& NewResolution) const;
  /// Return the list of all available screens.
  static const RF_Mem::AutoPointerArray<Screen>& AllScreens();
  /// Return the primary screen.
  static const Screen& PrimaryScreen();

private:
  // Allow the Array template to use the default constructor.
  friend class RF_Mem::AutoPointerArray<Screen>;
  /// This constructor is for the Array template.
  Screen();
  /// This is the copy-constructor.
  Screen(const Screen& Copy);
  /// This constructor will be called by the static method AllScreens().
  Screen(RF_Mem::AutoPointer<DisplayInformation> DisplayInfos,
         const RF_Type::UInt32 CurrentResolution);
  Screen& operator=(const Screen& Other);

  mutable RF_Type::UInt32 m_CurrentResolution;
  RF_Mem::AutoPointer<DisplayInformation> m_DisplayInfos;
  static RF_Mem::AutoPointerArray<Screen> m_Screens;
};

inline const RF_Collect::Array<Resolution>& Screen::SupportedResolutions() const
{
  return m_DisplayInfos->AvaiableResolution;
}

inline RF_Type::UInt32 Screen::Width() const
{
  return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Width;
}

inline RF_Type::UInt32 Screen::Height() const
{
  return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Height;
}

inline RF_Type::Int32 Screen::Left() const
{
  return m_DisplayInfos->Left;
}

inline RF_Type::Int32 Screen::Top() const
{
  return m_DisplayInfos->Top;
}

inline RF_Geo::Point2D<> Screen::Position() const
{
  return RF_Geo::Point2D<>(Left(), Top());
}

inline RF_Type::UInt32 Screen::BitsPerPixel() const
{
  return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).BitsPerPixel;
}

inline RF_Type::String Screen::DeviceName() const
{
  return m_DisplayInfos->DisplayName;
}

inline RF_Type::Bool RadonFramework::Forms::Screen::IsPrimary() const
{
  return m_DisplayInfos->IsPrimary;
}

inline RF_Type::Bool RadonFramework::Forms::Screen::IsMirroring() const
{
  return m_DisplayInfos->IsMirroring;
}

inline RF_Type::Bool RadonFramework::Forms::Screen::IsAttachedToDesktop() const
{
  return m_DisplayInfos->IsAttachedToDesktop;
}

inline const Resolution&
RadonFramework::Forms::Screen::CurrentResolution() const
{
  return m_DisplayInfos->AvaiableResolution(m_CurrentResolution);
}

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif  // RF_DRAWING_FORM_SCREEN_HPP
