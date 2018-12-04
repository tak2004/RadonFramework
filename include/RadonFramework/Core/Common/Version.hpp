#ifndef RF_CORE_COMMON_VERSION_HPP
#define RF_CORE_COMMON_VERSION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework::Core::Common
{
class Version
{
public:
  /// Initializes a new instance of the Version class.
  Version() = default;
  /// Initializes a new instance of the Version class using the specified major
  /// and minor values.
  Version(const RF_Type::UInt32 Major, const RF_Type::UInt32 Minor);
  /// Initializes a new instance of the Version class using the specified major,
  /// minor, and build values.
  Version(const RF_Type::UInt32 Major,
          const RF_Type::UInt32 Minor,
          const RF_Type::UInt32 Build);
  /// Initializes a new instance of the Version class with the specified major,
  /// minor, build, and revision numbers.
  Version(const RF_Type::UInt32 Major,
          const RF_Type::UInt32 Minor,
          const RF_Type::UInt32 Build,
          const RF_Type::UInt32 Revision);
  /// Gets the value of the build component of the version number for the
  /// current Version object.
  RF_Type::UInt32 Build() const;
  /// Gets the value of the major component of the version number for the
  /// current Version object.
  RF_Type::UInt32 Major() const;
  /// Gets the value of the minor component of the version number for the
  /// current Version object.
  RF_Type::UInt32 Minor() const;
  /// Gets the value of the revision component of the version number for the
  /// current Version object.
  RF_Type::UInt32 Revision() const;
  /// Gets the high 16 bits of the revision number.
  RF_Type::UInt32 MajorRevision() const;
  /// Gets the low 16 bits of the revision number.
  RF_Type::UInt32 MinorRevision() const;
  /// Return the text representation of the Version.
  RF_Type::String ToString() const;

protected:
  RF_Type::UInt32 m_Build = 0;
  RF_Type::UInt32 m_Major = 0;
  RF_Type::UInt32 m_Minor = 0;
  RF_Type::UInt32 m_Revision = 0;
};

}  // namespace RadonFramework::Core::Common

#ifndef RF_SHORTHAND_NAMESPACE_COMMON
#define RF_SHORTHAND_NAMESPACE_COMMON
namespace RF_Common = RadonFramework::Core::Common;
#endif

#endif  // RF_CORE_COMMON_VERSION_HPP
