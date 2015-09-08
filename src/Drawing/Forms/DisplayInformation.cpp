#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/DisplayInformation.hpp"

namespace RadonFramework { namespace Forms {

DisplayInformation::DisplayInformation()
:IsPrimary(false)
,IsAttachedToDesktop(true)
,IsMirroring(false)
{
}

DisplayInformation::DisplayInformation(const DisplayInformation& Copy)
{
    *this = Copy;
}

DisplayInformation& DisplayInformation::operator=(const DisplayInformation& Other)
{
    DisplayName = Other.DisplayName;
    Description = Other.Description;
    IsPrimary = Other.IsPrimary;
    IsAttachedToDesktop = Other.IsAttachedToDesktop;
    IsMirroring = Other.IsMirroring;
    AvaiableResolution = Other.AvaiableResolution;
    return *this;
}

} }