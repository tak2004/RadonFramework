#ifndef RF_SCREEN_HPP
#define RF_SCREEN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Drawing/Forms/DisplayInformation.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        namespace ScreenError
        {
            enum Type
            {
                NoError,
                ResolutionNotSupported,//the device don't support this resolution
                InvalidParameter//one or more parameter are invalid(like BitsPerPixel=0)
            };
        }

        class Screen
        {
            public:
                ~Screen();

                /// Return a list of all supported resolutions by this screen.
                const Collections::Array<Resolution>& SupportedResolutions()const;
                /// Return the width of the current resolution.
                Core::Types::UInt32 Width()const;
                /// Return the height of the current resolution.
                Core::Types::UInt32 Height()const;
                /// Return the bits per pixel of the current resolution.
                Core::Types::UInt32 BitsPerPixel()const;
                /// Return the device name of this screen.
                Core::Types::String DeviceName()const;
                /// Return true if this is the primary screen else false.
                Core::Types::Bool IsPrimary()const;
                /// Return true if this display is mirrored.
                Core::Types::Bool IsMirroring()const;
                /// Return true if this display is attached to desktop.
                Core::Types::Bool IsAttachedToDesktop()const;
                /// Return the current selected resolution.
                const Resolution& CurrentResolution()const;

                /// Try to change the resolution of this screen to NewResolution.
                ScreenError::Type ChangeResolution(const Resolution& NewResolution)const;
                /// Return the list of all available screens.
                static const Memory::AutoPointerArray<Screen>& AllScreens();
                /// Return the primary screen.
                static const Screen& PrimaryScreen();
            private:
                // Allow the Array template to use the default constructor.
                friend class Memory::AutoPointerArray<Screen>;
                /// This constructor is for the Array template.
                Screen();
                /// This is the copy-constructor.
                Screen(const Screen& Copy);
                /// This constructor will be called by the static method AllScreens().
                Screen(Memory::AutoPointer<DisplayInformation> DisplayInfos,
                       const Core::Types::UInt32 CurrentResolution);
                Screen& operator=(const Screen& Other);

                mutable Core::Types::UInt32 m_CurrentResolution;
                Memory::AutoPointer<DisplayInformation> m_DisplayInfos;
                static Memory::AutoPointerArray<Screen> m_Screens;
        };

        inline const Collections::Array<Resolution>& Screen::SupportedResolutions()const
        {
            return m_DisplayInfos->AvaiableResolution;
        }

        inline Core::Types::UInt32 Screen::Width()const
        {
            return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Width;
        }

        inline Core::Types::UInt32 Screen::Height()const
        {
            return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).Height;
        }

        inline Core::Types::UInt32 Screen::BitsPerPixel()const
        {
            return m_DisplayInfos->AvaiableResolution(m_CurrentResolution).BitsPerPixel;
        }

        inline Core::Types::String Screen::DeviceName()const
        {
            return m_DisplayInfos->DisplayName;
        }

        inline Core::Types::Bool RadonFramework::Forms::Screen::IsPrimary()const
        {
            return m_DisplayInfos->IsPrimary;
        }

        inline Core::Types::Bool RadonFramework::Forms::Screen::IsMirroring()const
        {
            return m_DisplayInfos->IsMirroring;
        }

        inline Core::Types::Bool RadonFramework::Forms::Screen::IsAttachedToDesktop()const
        {
            return m_DisplayInfos->IsAttachedToDesktop;
        }

        inline const Resolution& RadonFramework::Forms::Screen::CurrentResolution()const
        {
            return m_DisplayInfos->AvaiableResolution(m_CurrentResolution);
        }
    }
}

#endif // RF_SCREEN_HPP
