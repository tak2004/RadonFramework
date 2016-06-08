#ifndef RF_SYSTEM_VM_BYTECODEINSTRUCTIONS_HPP
#define RF_SYSTEM_VM_BYTECODEINSTRUCTIONS_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace System { namespace VM {

enum class ByteCodeInstructions
{
    GoTo,// go to label
    Call,// jump to subroutine
    Return,// return from subroutine
    ReturnBool,// return from subroutine with bool
    IfUnequal, // go to label if unequal
    IfEqual, // go to label if equal
    PushBool,// push a bool onto the stack

};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_VM
#define RF_SHORTHAND_NAMESPACE_VM
namespace RF_VM = RadonFramework::System::VM;
#endif

#endif // RF_SYSTEM_VM_BYTECODEINSTRUCTIONS_HPP