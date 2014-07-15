#ifndef RF_DIAGNOSTICS_APPENDER_HPP
#define RF_DIAGNOSTICS_APPENDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Diagnostics {

class Appender
{
public:
    virtual void WriteInfo(const RF_Type::String& Text)=0;
    virtual void WriteError(const RF_Type::String& Text)=0;
    virtual void WriteFatalError(const RF_Type::String& Text)=0;
    virtual void WriteDebug(const RF_Type::String& Text)=0;
protected:
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DIAG
#define RF_SHORTHAND_NAMESPACE_DIAG
namespace RF_Diag = RadonFramework::Diagnostics;
#endif

#endif // RF_DIAGNOSTICS_APPENDER_HPP