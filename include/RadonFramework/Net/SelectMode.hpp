#ifndef RF_SELECTMODE_HPP
#define RF_SELECTMODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net::SelectMode {

enum Type {
	Read,
	Write,
	Error,
	ReadWrite,
	ReadError,
	WriteError,
    ReadWriteError
};

}

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif // RF_SELECTMODE_HPP

