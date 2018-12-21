#ifndef RF_POINTERID_HPP
#define RF_POINTERID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>

namespace RadonFramework::Memory
{
using PtrID = RF_Type::UInt64;
using PointerIDHolder = union {
  PtrID ID;
  void* Ptr;

  struct
  {
    RF_Type::UInt32 ID32;
    RF_Type::UInt32 unset1;
  } Identifier32Bit;

  struct
  {
    void* Ptr32;
    RF_Type::UInt32 unset2;
  } Pointer32Bit;
};

struct PointerID
{
  static const PointerID& Zero();
  static PointerID GenerateFromPointer(void* Ptr);
  static PointerID GenerateFromID(PtrID ID);

  PtrID GetID() const;
  void* GetPointer() const;

  bool operator==(const PointerID& other) const;
  bool operator!=(const PointerID& other) const;

private:
  PointerIDHolder m_PtrID;
};

}  // namespace RadonFramework::Memory

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif
