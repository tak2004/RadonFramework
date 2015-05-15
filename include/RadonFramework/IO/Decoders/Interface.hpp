#ifndef RF_IO_DECODERS_INTERFACE_HPP
#define RF_IO_DECODERS_INTERFACE_HPP

namespace RadonFramework { namespace IO { namespace Decoders {

enum class Interface
{
    Generic,
    Image
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_DECODERS
#define RF_SHORTHAND_NAMESPACE_DECODERS
namespace RF_Decoders = RadonFramework::IO::Decoders;
#endif

#endif // RF_IO_DECODERS_INTERFACE_HPP