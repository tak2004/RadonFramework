#ifndef RF_IO_URIKIND_HPP
#define RF_IO_URIKIND_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

namespace UriKind
{
    enum Type
    {
        // The kind of the Uri is indeterminate.
        RelativeOrAbsolute,
        Absolute,
        Relative
    };
}

} }

#endif // RF_IO_URIKIND_HPP