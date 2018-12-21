#ifndef RF_IO_OPTIONRULE_HPP
#define RF_IO_OPTIONRULE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO
{
struct OptionRule
{
  using ValueCheckCallback = RF_Type::Bool (*)(const RF_Type::String& Value);

  enum Type
  {
    Required,
    Optional
  };

  inline void Init(const char* AShortName,
                   const char* ALongName,
                   ValueCheckCallback AValueCheck,
                   const char* ADescription,
                   Type AvailabilityIs)
  {
    this->ShortName = AShortName;
    this->LongName = ALongName;
    this->ValueCheck = AValueCheck;
    this->Description = ADescription;
    this->Availability = AvailabilityIs;
  }

  inline void Init(const char* AShortName,
                   const char* ALongName,
                   const char* ADescription,
                   Type AvailabilityIs)
  {
    this->ShortName = AShortName;
    this->LongName = ALongName;
    this->ValueCheck = nullptr;
    this->Description = ADescription;
    this->Availability = AvailabilityIs;
  }

  const char* ShortName;
  const char* LongName;
  ValueCheckCallback ValueCheck;
  const char* Description;
  Type Availability;

private:
  RF_Type::UInt8 Padding[4];
};

}  // namespace RadonFramework::IO

#endif  // RF_IO_OPTIONRULE_HPP
