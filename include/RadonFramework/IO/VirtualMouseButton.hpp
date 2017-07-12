#ifndef RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
#define RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO::VirtualMouseButton {

enum Type
{
    Left,
    Right,
    Middle,
    Button4,
    Button5,
    MAX
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_RF_VIRTUALMOUSEBUTTON_HPP_HPP
