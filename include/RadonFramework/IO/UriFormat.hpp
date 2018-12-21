#ifndef RF_IO_URIFORMAT_HPP
#define RF_IO_URIFORMAT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO::UriFormat
{
enum Type
{
  // Escaping is performed according to the rules in RFC-2396.
  UriEscaped,
  // No escaping is performed.
  Unescaped
};
}

#endif  // RF_IO_URIFORMAT_HPP