#ifndef RF_SYSTEM_VM_CPPVM_HPP
#define RF_SYSTEM_VM_CPPVM_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace System { namespace VM {

class CppVM
{
public:
    typedef RF_Mem::AutoPointerArray<RF_Type::UInt8> ByteCode;
    
    RF_Type::Bool Load(ByteCode Data)
    {
        return true;
    }

    void* GetFunctionPointer(RF_Type::Size Symbol)
    {
        return nullptr;
    }
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_VM
#define RF_SHORTHAND_NAMESPACE_VM
namespace RF_VM = RadonFramework::System::VM;
#endif

#endif // RF_SYSTEM_VM_CPPVM_HPP