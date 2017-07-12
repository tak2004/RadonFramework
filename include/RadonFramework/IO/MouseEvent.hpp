#ifndef RF_MOUSEEVENT_HPP
#define RF_MOUSEEVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/IO/VirtualMouseButton.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework::IO {

struct MouseEvent
{
    RF_Type::Bool MouseButtonState[VirtualMouseButton::MAX];
    RF_Geo::Point2D<> CurrentPosition;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_MOUSEEVENT_HPP