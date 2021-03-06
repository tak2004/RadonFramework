#ifndef RF_CORE_IDIOMS_PIMPL_HPP
#define RF_CORE_IDIOMS_PIMPL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Idioms
{
/** This template simplify the usage of the PImpl pattern.
 * Implement a template<class T> class PImpl<T>::Data in the private unit.
 * You can access the Data structure like a pointer.
 */
template <class T>
class PImpl
{
public:
  struct Data;

  PImpl() : impl_(new Data()) {}
  ~PImpl() { delete impl_; }

  Data const* operator->() const { return impl_; }
  Data const& operator*() const { return *impl_; }
  Data* operator->() { return impl_; }
  Data& operator*() { return *impl_; }

private:
  Data* impl_;
};

}  // namespace RadonFramework::Core::Idioms

#ifndef RF_SHORTHAND_NAMESPACE_IDIOM
#define RF_SHORTHAND_NAMESPACE_IDIOM
namespace RF_Idiom = RadonFramework::Core::Idioms;
#endif

#endif  // RF_CORE_IDIOMS_PIMPL_HPP