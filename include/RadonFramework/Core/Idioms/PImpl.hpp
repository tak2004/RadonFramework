#ifndef RF_CORE_IDIOMS_PIMPL_HPP
#define RF_CORE_IDIOMS_PIMPL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Idioms {

/** This template simplify the usage of the PImpl pattern.
  * To use this template you have to derive your class from it and
  * set the class Type for parameter T, add a default constructor,
  * a virtual destructor and implement a template struct PImpl<T>::Data.
  * You can access the Data structure by using (*this)-> .
  */
template<class T>
class PImpl
{
public:
    struct Data;

    PImpl() : impl_(new Data()) {}
    virtual ~PImpl() { delete impl_; }

    Data const* operator->() const { return impl_; }
    Data const& operator *() const { return *impl_; }
    Data*       operator->() { return  impl_; }
    Data&       operator *() { return *impl_; }
private:
    Data* impl_;
};

} } }

#endif // RF_CORE_IDIOMS_PIMPL_HPP