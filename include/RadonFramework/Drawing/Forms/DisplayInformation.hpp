#ifndef RF_DISPLAYINFORMATION_HPP
#define RF_DISPLAYINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Drawing/Forms/Resolution.hpp>

namespace RadonFramework::Forms
{
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
  RF_Type::Int32 Left;
  RF_Type::Int32 Top;
  RF_Collect::Array<Resolution> AvaiableResolution;

  DisplayInformation& operator=(const DisplayInformation& Other);
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif

#endif  // RF_DISPLAYINFORMATION_HPP