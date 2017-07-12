#ifndef RF_IO_URIPARTIAL
#define RF_IO_URIPARTIAL
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::IO::UriPartial {

enum Type
{
    // The scheme segment of the URI.
    Scheme,
    // The scheme and authority segments of the URI.
    Authority,
    // The scheme, authority, and path segments of the URI.
    Path,
    // The scheme, authority, path, and query segments of the URI.
    Query
};

}

#endif // RF_IO_URIPARTIAL