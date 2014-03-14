#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Common/Version.hpp"

using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Core::Types;

Version::Version()
:m_Build(0)
,m_Major(0),
m_Minor(0),
m_Revision(0)
{
}

Version::Version(const UInt32 Major, const UInt32 Minor)
:m_Build(0)
,m_Major(Major)
,m_Minor(Minor)
,m_Revision(0)
{
}

Version::Version(const UInt32 Major, const UInt32 Minor, const UInt32 Build)
:m_Build(Build)
,m_Major(Major)
,m_Minor(Minor)
,m_Revision(0)
{
}

Version::Version(const UInt32 Major, const UInt32 Minor,
                 const UInt32 Build, const UInt32 Revision)
:m_Build(Build)
,m_Major(Major)
,m_Minor(Minor)
,m_Revision(Revision)
{
}

UInt32 Version::Build()const
{
    return m_Build;
}

UInt32 Version::Major()const
{
    return m_Major;
}

UInt32 Version::Minor()const
{
    return m_Minor;
}

UInt32 Version::Revision()const
{
    return m_Revision;
}

UInt32 Version::MajorRevision()const
{
    return m_Revision>>16;
}

UInt32 Version::MinorRevision()const
{
    return m_Revision&0x0000FFFF;
}

String Version::ToString()const
{
    String result;
    result=result+m_Major+"."+m_Minor+"."+m_Revision+"."+m_Build;
    return result;
}
