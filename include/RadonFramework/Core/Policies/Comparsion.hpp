#ifndef RF_CORE_POLICIES_COMPARSION_HPP
#define RF_CORE_POLICIES_COMPARSION_HPP

namespace RadonFramework::Core::Policies
{
template <class T1, class T2>
struct Comparsion
{
  using Type = Delegate2<RF_Type::Int32(T1, T2)>;
};
}  // namespace RadonFramework::Core::Policies

#endif