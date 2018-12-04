#ifndef RF_IO_SETTINGS_HPP
#define RF_IO_SETTINGS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO {

class Directory;

class Settings: public RF_Pattern::Singleton<Settings>
{
public:
    void Initialize(const RF_Type::String& Organisation, const RF_Type::String& Applicationname);
    RF_Type::String GetValue(const RF_Type::String& PropertyName);
    void SetValue(const RF_Type::String& PropertyName, const RF_Type::String& Value);
    void Save();
    void Load();
    void Load(const RF_Type::String& Organisation, const RF_Type::String& Applicationname);
    Directory GetAppDataDir();
protected:
    friend class RF_Pattern::Singleton<Settings>;
    Settings();
private:
    Core::Idioms::PImpl<Settings> m_PImpl;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_SETTINGS_HPP