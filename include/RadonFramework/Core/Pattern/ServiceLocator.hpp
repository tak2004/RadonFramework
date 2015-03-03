#ifndef RF_CORE_PATTERN_SERVICELOCATOR_HPP
#define RF_CORE_PATTERN_SERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/IEnumerator.hpp>

namespace RadonFramework { namespace Core { namespace Pattern {

template<class T,class N>
struct Locator
{
    typedef typename RF_Collect::AutoVector<T>::Iterator Iterator;
    typedef typename RF_Collect::AutoVector<T>::ConstIterator ConstIterator;

    Locator() = delete;

    static void Initialize()
    {
        Locator::m_Default=0;
    }

    static void Quit()
    {
        Locator::m_Services.Clear();
        Locator::m_Default=0;
    }

    static T& Default()
    {
        if (Locator::m_Services.Size())
            return *Locator::m_Services[Locator::m_Default];
        else
            return Locator::m_NullService;
    }

    static void SetDefault(const RF_Type::String& Name)
    {
        RF_Type::UInt32 i = 0;
        for (Iterator it=Locator::m_Services.Begin();it!=Locator::m_Services.End();++it)
        {
            if ((*it)->Name()==Name)
                break;
            i++;
        }
        if (i<Locator::m_Services.Size())
            m_Default=i;
    }

    static T& Find(const RF_Type::String& Name)
    {
        for (Iterator it=Locator::m_Services.Begin();it!=Locator::m_Services.End();it++)
            if ((*it)->Name()==Name)
                return **it;
        return Locator::m_NullService;
    }

    static void Register(Memory::AutoPointer<T> AService)
    {
        if (AService.Get())
            Locator::m_Services.PushBack(AService);
    }

    static void Remove(const RF_Type::String& Name)
    {
        if (Locator::m_Services.Size()==0)
            return;

        for (Iterator it=Locator::m_Services.begin();it!=Locator::m_Services.end();++it)
            if ((*it)->Name()==Name)
            {
                if (*it->Name()==Locator::m_Services[Locator::m_Default]->Name())
                    Locator::m_Default=0;
                Locator::m_Services.Erase(it);
                return;
            }
    }

    static typename RF_Collect::AutoVector<T>::Iterator Begin()
    {
        return Locator::m_Services.Begin();
    }
                    
    static typename RF_Collect::AutoVector<T>::Iterator End()
    {
        return Locator::m_Services.End();
    }
protected:
    static N m_NullService;
    static RF_Collect::AutoVector<T> m_Services;
    static RF_Type::UInt32 m_Default;
};

template<class T, class N> 
N Locator<T,N>::m_NullService(RF_Type::String("NullService", sizeof("NullService"), Common::DataManagment::UnmanagedInstance));

template<class T, class N> 
RF_Collect::AutoVector<T> Locator<T, N>::m_Services;

template<class T, class N> 
RF_Type::UInt32 Locator<T, N>::m_Default = 0;
        
} } }

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif // RF_CORE_PATTERN_SERVICELOCATOR_HPP
