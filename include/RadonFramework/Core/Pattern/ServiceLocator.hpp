#ifndef RF_CORE_PATTERN_SERVICELOCATOR_HPP
#define RF_CORE_PATTERN_SERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/IEnumerator.hpp>
#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

namespace RadonFramework::Core::Pattern
{
template <class T, class N>
struct Locator
{
  using Iterator = typename RF_Collect::AutoVector<T>::Iterator;
  using ConstIterator = typename RF_Collect::AutoVector<T>::ConstIterator;

  Locator() = delete;

  static void Initialize() { Locator::m_Default = 0; }

  static void Quit()
  {
    Locator::m_Services.Clear();
    Locator::m_Default = 0;
  }

  static T& Default()
  {
    if(Locator::m_Services.Count())
      return *Locator::m_Services[Locator::m_Default];
    else
      return Locator::m_NullService;
  }

  static void SetDefault(const RF_Type::String& Name)
  {
    RF_Type::UInt32 i = 0;
    for(Iterator it = Locator::m_Services.Begin();
        it != Locator::m_Services.End(); ++it)
    {
      if((*it)->Name() == Name)
        break;
      i++;
    }
    if(i < Locator::m_Services.Count())
      m_Default = i;
  }

  static T& Find(const RF_Type::String& Name)
  {
    for(Iterator it = Locator::m_Services.Begin();
        it != Locator::m_Services.End(); it++)
      if((*it)->Name() == Name)
        return **it;
    return Locator::m_NullService;
  }

  static void Register(Memory::AutoPointer<T> AService)
  {
    if(AService.Get())
    {
      Locator::m_Services.PushBack(AService);
    }
  }

  static void Remove(const RF_Type::String& Name)
  {
    if(Locator::m_Services.Count() == 0)
      return;

    for(Iterator it = Locator::m_Services.Begin();
        it != Locator::m_Services.End(); ++it)
      if((*it)->Name() == Name)
      {
        if((*it)->Name() == Locator::m_Services[Locator::m_Default]->Name())
          Locator::m_Default = 0;
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

  static RF_Type::Bool IsNullService(const T& Instance)
  {
    return &Locator::m_NullService == &Instance;
  }

protected:
  static N m_NullService;
  static RF_Collect::AutoVector<T> m_Services;
  static RF_Type::UInt32 m_Default;
};

template <class T, class N>
N Locator<T, N>::m_NullService("NullService"_rfs);

template <class T, class N>
RF_Collect::AutoVector<T> Locator<T, N>::m_Services;

template <class T, class N>
RF_Type::UInt32 Locator<T, N>::m_Default = 0;

}  // namespace RadonFramework::Core::Pattern

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif  // RF_CORE_PATTERN_SERVICELOCATOR_HPP
