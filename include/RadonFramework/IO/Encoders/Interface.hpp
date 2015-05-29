#ifndef RF_IO_ENCODERS_INTERFACE_HPP
#define RF_IO_ENCODERS_INTERFACE_HPP

namespace RadonFramework { namespace IO { namespace Encoders {

enum class Interface
{
    Generic,
    Image
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_ENCODERS
#define RF_SHORTHAND_NAMESPACE_ENCODERS
namespace RF_Encoders = RadonFramework::IO::Encoders;
#endif

#endif // RF_IO_ENCODERS_INTERFACE_HPP