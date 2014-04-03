#ifndef RF_MOUSEEVENT_HPP
#define RF_MOUSEEVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/VirtualKey.hpp>
#include <RadonFramework/IO/VirtualMouseButton.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework
{
    namespace IO
    {
        struct MouseEvent
        {
            RFTYPE::Bool MouseButtonState[IO::VirtualMouseButton::MAX];
            Math::Geometry::Point2D<> CurrentPosition;
        };
    }
}

#endif // RF_MOUSEEVENT_HPP