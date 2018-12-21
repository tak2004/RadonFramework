#ifndef RF_IO_SEEKORIGIN_HPP
#define RF_IO_SEEKORIGIN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO
{
namespace SeekOrigin
{
enum Type
{
  Begin = 0,
  Current,
  End,
  MAX
};
}

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_IO_SEEKORIGIN_HPP
