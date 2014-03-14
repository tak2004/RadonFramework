#ifndef RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
#define RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
      namespace VirtualMouseButton{
        enum Type{
            Left,
            Right,
            Middle,
            WheelUp,
            WheelDown,
            MAX
        };
      }
    }
}

#endif // RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
