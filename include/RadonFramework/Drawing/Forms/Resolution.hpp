#ifndef RF_RESOLUTION_HPP
#define RF_RESOLUTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework { namespace Forms {

struct Resolution
{
    RF_Type::UInt32 Left;
    RF_Type::UInt32 Top;
    RF_Type::UInt32 Width;
    RF_Type::UInt32 Height;
    RF_Type::UInt32 BitsPerPixel;
    RF_Type::UInt32 Frequency;
    RF_Type::UInt32 DPIX;
    RF_Type::UInt32 DPIY;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif // !RF_SHORTHAND_NAMESPACE_FORM

#endif // RF_RESOLUTION_HPP