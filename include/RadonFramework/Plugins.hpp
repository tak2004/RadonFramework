#ifndef RF_PLUGINS_HPP
#define RF_PLUGINS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#if defined(RF_WINDOWS)
    #include <RadonFramework/System/Drawing/SystemTrayServiceWindows.hpp>
#endif

#if defined(RF_LINUX)

#endif

#if defined(RF_OSX)

#endif

#include <RadonFramework/backend/hashlib++/HashlibHashfunctionService.hpp>
#include <RadonFramework/backend/MurmurHash/MurmurHashHashfunctionService.hpp>

#endif
