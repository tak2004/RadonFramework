#ifndef RF_IO_OPTIONRULE_HPP
#define RF_IO_OPTIONRULE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace IO
    {
        struct OptionRule
        {
            typedef RF_Type::Bool (*ValueCheckCallback)(const RF_Type::String& Value);

			enum Type
            {
                Required,
                Optional
            };

            inline void Init(const char* ShortName, const char* LongName, 
                ValueCheckCallback ValueCheck, const char* Description,
				Type Availability)
            {
                this->ShortName=ShortName;
                this->LongName=LongName;
                this->ValueCheck=ValueCheck;
                this->Description=Description;
				this->Availability=Availability;
            }

            inline void Init(const char* ShortName, const char* LongName,
                const char* Description, Type Availability)
            {
                this->ShortName = ShortName;
                this->LongName = LongName;
                this->ValueCheck = nullptr;
                this->Description = Description;
                this->Availability = Availability;
            }

            const char* ShortName;
            const char* LongName;
            ValueCheckCallback ValueCheck;
            const char* Description;
			Type Availability;
        };
    }
}

#endif // RF_IO_OPTIONRULE_HPP
