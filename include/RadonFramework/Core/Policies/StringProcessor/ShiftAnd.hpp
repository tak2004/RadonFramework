#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_SHIFTAND_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_SHIFTAND_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            namespace StringProcessor
            {
                struct ShiftAnd
                {
                    struct StorageType
                    {
                        StorageType();
                        ~StorageType();
                        Types::String Search;
                        Types::Int32 Position;
                        Types::UInt32 Lastbit;
                        Types::UInt32* Shift;
                    };

                    static Types::Bool Init(Types::String& Text, 
                                            const Types::UInt32 Position, 
                                            StorageType* Storage);

                    static void Reset(Types::String& Text, 
                                      const Types::UInt32 Position, 
                                      StorageType* Storage);

                    static Types::Int32 DoNext(Types::String& Text, 
                                               StorageType* Storage);

                    static Types::Int32 DoAll(Types::String& Text, 
                                              StorageType* Storage);
                };

                ShiftAnd::StorageType::StorageType()
                :Position(0)
                ,Lastbit(0)
                ,Shift(0)
                {

                }

                ShiftAnd::StorageType::~StorageType()
                {
                    delete[] Shift;
                }

                Types::Bool ShiftAnd::Init(Types::String& Text, 
                                            const Types::UInt32 Position, 
                                            StorageType* Storage)
                {
                    if (Storage->Search.Length()>0)
                    {
                        if (Storage->Search.Length()>32)
                            return false;
                        Storage->Position=0;
                        delete[] Storage->Shift;
                        Storage->Shift=new Types::UInt32[256];
                        Types::Int32 k=1;
                        Types::Int8 a;
                        for (Types::Int32 j=0;j<static_cast<Types::Int32>(Storage->Search.Length());++j)
                        {
                            a=Storage->Search[j];
                            Storage->Shift[a]|=k;
                            Storage->Lastbit=k;
                            k<<=1;
                        }
                    }
                    return true;
                }

                void ShiftAnd::Reset(Types::String& Text, 
                                    const Types::UInt32 Position, 
                                    StorageType* Storage)
                {
                    Storage->Position=Position;
                }

                Types::Int32 ShiftAnd::DoNext(Types::String& Text, 
                                            StorageType* Storage)
                {
                    Types::UInt32 z=0;
                    Types::UInt8 const* p1=(Types::UInt8*)Text.c_str();
                    for (;Storage->Position<static_cast<Types::Int32>(Text.Length());++Storage->Position)
                    {
                        z=((z<<1)|1)&Storage->Shift[p1[Storage->Position]];
                        if ((z&Storage->Lastbit)!=0)
                            return Storage->Position-Storage->Search.Length()-1;
                    }
                    Storage->Position=-1;
                    return Storage->Position;
                }

                Types::Int32 ShiftAnd::DoAll(Types::String& Text, 
                                            StorageType* Storage)
                {
                    Types::UInt32 z=0,hit=0;
                    Types::UInt8 const* p1=(Types::UInt8*)Text.c_str();
                    for (;Storage->Position<static_cast<Types::Int32>(Text.Length());++Storage->Position)
                    {
                        z=((z<<1)|1)&Storage->Shift[p1[Storage->Position]];
                        if ((z&Storage->Lastbit)!=0)
                            ++hit;
                    }
                    return hit;
                }
            }
        }
    }
}

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_SHIFTAND_HPP