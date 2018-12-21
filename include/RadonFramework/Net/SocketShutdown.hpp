#ifndef RF_SOCKETSHUTDOWN_HPP
#define RF_SOCKETSHUTDOWN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net
{
namespace SocketShutdown
{
enum Type
{
  Send,
  Receive,
  Both,
  MAX
};
}

}  // namespace RadonFramework::Net

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
