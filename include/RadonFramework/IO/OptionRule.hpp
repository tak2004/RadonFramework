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
            typedef RFTYPE::Bool (*ValueCheckCallback)(const RFTYPE::String& Value);

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

            const char* ShortName;
            const char* LongName;
            ValueCheckCallback ValueCheck;
            const char* Description;
			Type Availability;
        };
    }
}

#endif // RF_IO_OPTIONRULE_HPP
