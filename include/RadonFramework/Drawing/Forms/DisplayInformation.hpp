#ifndef RF_DISPLAYINFORMATION_HPP
#define RF_DISPLAYINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Drawing/Forms/Resolution.hpp>

namespace RadonFramework
{
    namespace Forms
    {
        struct DisplayInformation
        {
            Core::Types::String DisplayName;
            Core::Types::String Description;
            Core::Types::Bool IsPrimary;
            Core::Types::Bool IsAttachedToDesktop;
            Core::Types::Bool IsMirroring;
            Collections::Array<Resolution> AvaiableResolution;
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
    }
}

#endif // RF_DISPLAYINFORMATION_HPP