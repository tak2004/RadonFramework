#ifndef RF_DISPLAYINFORMATION_HPP
#define RF_DISPLAYINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Drawing/Forms/Resolution.hpp>

namespace RadonFramework { namespace Forms {

class DisplayInformation
{
public:
    DisplayInformation();

    DisplayInformation(const DisplayInformation& Copy);

    RF_Type::String DisplayName;
    RF_Type::String Description;
    RF_Type::Bool IsPrimary;
    RF_Type::Bool IsAttachedToDesktop;
    RF_Type::Bool IsMirroring;
    RF_Type::UInt32 HorizontalLengthInMilimeter;
    RF_Type::UInt32 VerticalLengthInMilimeter;
    RF_Type::UInt32 Left;
    RF_Type::UInt32 Top;
    RF_Collect::Array<Resolution> AvaiableResolution;

        Left = Other.Left;
        Top = Other.Top;
        HorizontalLengthInMilimeter = Other.HorizontalLengthInMilimeter;
        VerticalLengthInMilimeter = Other.VerticalLengthInMilimeter;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif // RF_DISPLAYINFORMATION_HPP