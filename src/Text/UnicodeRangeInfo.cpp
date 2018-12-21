#include "RadonFramework/Text/UnicodeRangeInfo.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Text
{
UnicodeRangeInfo::UnicodeRangeInfo(const UnicodeRangeIdentifier Identifier,
                                   const RF_Type::UInt32 Start,
                                   const RF_Type::UInt32 End)
: m_Identifier(Identifier), m_Start(Start), m_End(End)
{
}

const UnicodeRangeIdentifier UnicodeRangeInfo::Identifier() const
{
  return m_Identifier;
}

const RF_Type::UInt32 UnicodeRangeInfo::Start() const
{
  return m_Start;
}

const RF_Type::UInt32 UnicodeRangeInfo::End() const
{
  return m_End;
}

}  // namespace RadonFramework::Text