#include "RadonFramework/Core/Types/StringSet.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Core::Types
{
StringSet::StringSet() noexcept : m_ElementCount(0), m_Elements(nullptr) {}

StringSet::StringSet(const StringView& Source, const Size Elements) noexcept
: m_Source(Source), m_ElementCount(Elements)
{
  m_Elements = new Element[Elements];
  RF_SysMem::Set(m_Elements, 0, sizeof(Element) * m_ElementCount);
}

Bool StringSet::IsEmpty() const
{
  return m_Elements == 0;
}

StringView StringSet::Last() const
{
  StringView result;
  if(!IsEmpty())
  {
    auto& element = m_Elements[m_ElementCount - 1];
    result = m_Source.SubString(element.Offset, element.Count);
  }
  return result;
}
Size StringSet::Count() const
{
  return m_ElementCount;
}
StringView StringSet::operator[](const Size Index) const
{
  return m_Source.SubString(m_Elements[Index].Offset, m_Elements[Index].Count);
}

Bool StringSet::Set(const Size Index, const Size Offset, const Size Count)
{
  Bool result = false;
  if (Index < m_ElementCount)
  {
    result = true;
    m_Elements[Index] = {Offset, Count};
  }
  return Bool();
}

}  // namespace RadonFramework::Core::Types
