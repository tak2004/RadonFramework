#ifndef RF_CORE_PATTERN_SERVICELOCATOR_HPP
#define RF_CORE_PATTERN_SERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Idioms/NoInstance.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/IEnumerator.hpp>

namespace RadonFramework
{
    namespace Core
    {
        namespace Pattern
        {
            template<class T,class N>
            class Locator:public Idioms::NoInstance
            {
                public:
                    typedef typename Collections::AutoVector<T>::Iterator Iterator;
                    typedef typename Collections::AutoVector<T>::ConstIterator ConstIterator;

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

                    static void SetDefault(const Types::String& Name)
                    {
                        Types::UInt32 i=0;
                        for (Iterator it=Locator::m_Services.Begin();it!=Locator::m_Services.End();++it)
                        {
                            if ((*it)->Name()==Name)
                                break;
                            i++;
                        }
                        if (i<Locator::m_Services.Size())
                            m_Default=i;
                    }

                    static T& Find(const Types::String& Name)
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

                    static void Remove(const Types::String& Name)
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

                    static typename Collections::AutoVector<T>::Iterator Begin()
                    {
                        return Locator::m_Services.Begin();
                    }
                    
                    static typename Collections::AutoVector<T>::Iterator End()
                    {
                        return Locator::m_Services.End();
                    }
                protected:
                    static N m_NullService;
                    static Collections::AutoVector<T> m_Services;
                    static Types::UInt32 m_Default;
                private:
                    ~Locator();
            };

            template<class T, class N> 
            N Locator<T,N>::m_NullService(RFTYPE::String("NullService", sizeof("NullService"), Common::DataManagment::UnmanagedInstance));

            template<class T, class N> 
            Collections::AutoVector<T> Locator<T,N>::m_Services;

            template<class T, class N> 
            Types::UInt32 Locator<T,N>::m_Default=0;
        }
    }
}

#endif // RF_CORE_PATTERN_SERVICELOCATOR_HPP
