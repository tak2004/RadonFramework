#ifndef RF_IO_URICOMPONENTS_HPP
#define RF_IO_URICOMPONENTS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO::UriComponents
{
enum Type
{
  Scheme = 1,
  UserInfo = 2,
  Host = 4,
  Port = 8,
  Path = 16,
  Query = 32,
  Fragment = 64,
  Authority = UserInfo | Host | Port,
  SchemeSpecificPart = UserInfo | Host | Port | Path | Query,
  All = Scheme | SchemeSpecificPart | Fragment
};
}

#endif  // RF_IO_URICOMPONENTS_HPP