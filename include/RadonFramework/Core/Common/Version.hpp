#ifndef RF_CORE_COMMON_VERSION_HPP
#define RF_CORE_COMMON_VERSION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Common
        {
            class Version
            {
                public:
                    /// Initializes a new instance of the Version class.
                    Version();
                    /// Initializes a new instance of the Version class using the specified major and minor values.
                    Version(const Types::UInt32 Major, const Types::UInt32 Minor);
                    /// Initializes a new instance of the Version class using the specified major, minor, and build values.
                    Version(const Types::UInt32 Major, const Types::UInt32 Minor,
                            const Types::UInt32 Build);
                    /// Initializes a new instance of the Version class with the specified major, minor, build, and revision numbers.
                    Version(const Types::UInt32 Major, const Types::UInt32 Minor,
                            const Types::UInt32 Build, const Types::UInt32 Revision);
                    /// Gets the value of the build component of the version number for the current Version object.
                    Types::UInt32 Build()const;
                    /// Gets the value of the major component of the version number for the current Version object.
                    Types::UInt32 Major()const;
                    /// Gets the value of the minor component of the version number for the current Version object.
                    Types::UInt32 Minor()const;
                    /// Gets the value of the revision component of the version number for the current Version object.
                    Types::UInt32 Revision()const;
                    /// Gets the high 16 bits of the revision number.
                    Types::UInt32 MajorRevision()const;
                    /// Gets the low 16 bits of the revision number.
                    Types::UInt32 MinorRevision()const;
                    /// Return the text representation of the Version.
                    Types::String ToString()const;
                protected:
                    Types::UInt32 m_Build;
                    Types::UInt32 m_Major;
                    Types::UInt32 m_Minor;
                    Types::UInt32 m_Revision;
            };
        }
    }
}

#endif // RF_CORE_COMMON_VERSION_HPP
