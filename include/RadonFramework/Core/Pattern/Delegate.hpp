#ifndef RF_DELEGATE_HPP
#define RF_DELEGATE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

//It's really nice code which work on most systems without problems.
//For more information look at http://www.codeproject.com/cpp/FastDelegate.asp
#include <RadonFramework/backend/FastDelegate.h>
#include <RadonFramework/backend/FastDelegateBind.h>

#define Delegate fastdelegate::FastDelegate0
#define Delegate1 fastdelegate::FastDelegate1
#define Delegate2 fastdelegate::FastDelegate2
#define Delegate3 fastdelegate::FastDelegate3
#define Delegate4 fastdelegate::FastDelegate4
#define Delegate5 fastdelegate::FastDelegate5
#define Delegate6 fastdelegate::FastDelegate6
#define Delegate7 fastdelegate::FastDelegate7
#define Delegate8 fastdelegate::FastDelegate8
#define MakeDelegate fastdelegate::MakeDelegate

#endif
