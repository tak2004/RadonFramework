#ifndef RF_MOUSEEVENT_HPP
#define RF_MOUSEEVENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/IO/VirtualMouseButton.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>

namespace RadonFramework::IO
{
struct MouseEvent
{
  RF_Geo::Point2D<> CurrentPosition;
  RF_Type::Bool MouseButtonState[VirtualMouseButton::MAX];

private:
  RF_Type::UInt8 Padding[3];
};

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_MOUSEEVENT_HPP