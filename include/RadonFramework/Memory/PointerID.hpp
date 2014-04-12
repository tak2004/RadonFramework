#ifndef RF_POINTERID_HPP
#define RF_POINTERID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Memory
    {
        typedef RFTYPE::UInt64 PtrID;
        typedef union
        {
            PtrID ID;
            void* Ptr;

            struct Identifier32Bit
            {
                RFTYPE::UInt32 ID32;
                RFTYPE::UInt32 unset1;
            };

            struct Pointer32Bit
            {
                void* Ptr32;
                RFTYPE::UInt32 unset2;
            };
        }PointerIDHolder;

        struct PointerID
        {
            static const PointerID& Zero();
            static PointerID GenerateFromPointer(void* Ptr);
            static PointerID GenerateFromID(PtrID ID);

            PtrID GetID()const;
            void* GetPointer()const;

            bool operator==(const PointerID& other)const;
            bool operator!=(const PointerID& other)const;
            private:
                PointerIDHolder m_PtrID;
        };
    }
}

#endif
