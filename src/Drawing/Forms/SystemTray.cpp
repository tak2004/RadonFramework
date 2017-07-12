#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/SystemTray.hpp"
#include "RadonFramework/Drawing/TrayIcon.hpp"
#include "RadonFramework/System/Drawing/SystemTrayServiceLocator.hpp"
#include "RadonFramework/Collections/HashMap.hpp"

namespace RadonFramework::Core::Idioms {
template<>
class RF_Idiom::PImpl<RF_Draw::SystemTray>::Data
{
public:
    RF_Collect::AutoVector<RF_Draw::TrayIcon> m_Icons;
    RF_Collect::HashMap<RF_SysDraw::SystemTrayService::Handle, RF_Draw::TrayIcon*> m_Lookup;
    RF_SysDraw::SystemTrayService* m_Backend;
};
}

namespace RadonFramework::Drawing {

SystemTray::Handle SystemTray::Add(RF_Mem::AutoPointer<TrayIcon>& NewTrayIcon)
{
    auto iconHandle = m_PImpl->m_Backend->AddIcon(*NewTrayIcon.Get());
    m_PImpl->m_Lookup[iconHandle] = NewTrayIcon.Get();
    m_PImpl->m_Icons.PushBack(NewTrayIcon);
    return iconHandle;
}

void SystemTray::Remove(SystemTray::Handle RegisteredTrayIcon)
{
    if(m_PImpl->m_Lookup.ContainsKey(RegisteredTrayIcon))
    {
        auto it = m_PImpl->m_Icons.Begin();
        auto end = m_PImpl->m_Icons.End();
        for(; it != end; ++it)
        {
            if(*it == m_PImpl->m_Lookup[RegisteredTrayIcon])
            {
                m_PImpl->m_Icons.Erase(it);
                m_PImpl->m_Backend->Remove(RegisteredTrayIcon);
                break;
            }
        }
    }
}

const RF_Collect::AutoVector<TrayIcon>& SystemTray::GetRegisteredTrayIcons() const
{
    return m_PImpl->m_Icons;
}

void SystemTray::RequestTrayIconSize(RF_Geo::Size2D<>& WriteTo) const
{

}

RF_Type::Bool SystemTray::IsSupported()
{
    auto it = RF_SysDraw::SystemTrayServiceLocator::Begin();
    auto end = RF_SysDraw::SystemTrayServiceLocator::End();
    for(; it != end; ++it)
    {
        if((*it)->IsSupported())
        {
            return true;
        }
    }
    return false;
}

SystemTray::SystemTray()
{
    auto it = RF_SysDraw::SystemTrayServiceLocator::Begin();
    auto end = RF_SysDraw::SystemTrayServiceLocator::End();
    for(; it != end; ++it)
    {
        if((*it)->IsSupported())
        {
            m_PImpl->m_Backend = *it;
            m_PImpl->m_Backend->OnAction = OnAction;
        }
    }
}


SystemTray::~SystemTray()
{

}

void SystemTray::OnAction(RF_Type::UInt32 ActionId)
{
    SystemTray& instance = SystemTray::GetInstance();
    for(RF_Type::Size i = 0; i < instance.m_PImpl->m_Icons.Count(); ++i)
    {
        instance.m_PImpl->m_Icons[i]->OnAction(ActionId);
    }
}

}