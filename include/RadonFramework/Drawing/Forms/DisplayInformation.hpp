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

struct DisplayInformation
{
    RF_Type::String DisplayName;
    RF_Type::String Description;
    RF_Type::Bool IsPrimary;
    RF_Type::Bool IsAttachedToDesktop;
    RF_Type::Bool IsMirroring;
    RF_Collect::Array<Resolution> AvaiableResolution;
    DisplayInformation& operator=(const DisplayInformation& Other){
        DisplayName=Other.DisplayName;
        Description=Other.Description;
        IsPrimary=Other.IsPrimary;
        IsAttachedToDesktop=Other.IsAttachedToDesktop;
        IsMirroring=Other.IsMirroring;
        AvaiableResolution=Other.AvaiableResolution;
        return *this;
    }
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif // RF_DISPLAYINFORMATION_HPP