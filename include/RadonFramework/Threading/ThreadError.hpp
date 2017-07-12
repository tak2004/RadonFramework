#ifndef RF_THREADING_THREADERROR_HPP
#define RF_THREADING_THREADERROR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Threading::ThreadError {

enum Type
{
    NoError,
    ThreadLimitReached,
    InternalError,
    InvalidArgument
};

}

#endif // RF_THREADING_THREADERROR_HPP