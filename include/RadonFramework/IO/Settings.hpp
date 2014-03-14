#ifndef RF_IO_SETTINGS_HPP
#define RF_IO_SETTINGS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework
{
    namespace IO
    {
        class Directory;

        class Settings: public Singleton<Settings>
        {
            public:
                void Initialize(const RFTYPE::String& Organisation, const RFTYPE::String& Applicationname);
                RFTYPE::String GetValue(const char* PropertyName);
                void SetValue(const char* PropertyName, const RFTYPE::String& Value);
                void Save();
                void Load();
                void Load(const RFTYPE::String& Organisation, const RFTYPE::String& Applicationname);
                Directory GetAppDataDir();
            protected:
                friend class Singleton<Settings>;
                Settings();
            private:
                Core::Idioms::PImpl<Settings> m_PImpl;
        };
    }
}

#endif // RF_IO_SETTINGS_HPP