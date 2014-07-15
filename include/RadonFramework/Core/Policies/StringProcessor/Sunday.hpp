#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_SUNDAY_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_SUNDAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <string.h>

namespace RadonFramework { namespace Core { namespace Policies { namespace StringProcessor {
/** This policy search a String in an other String by comparing
    * the word of the first String with the characters of the second.
    * If they don't match then the cursor of the second String
    * will be increased by one character and do the step again
    * till a match occur or the cursor reach the end of the String.
    **/
struct Sunday
{
    /** This struct will be use by the BruteForce policy to
        * search an word in a text.
        **/
    struct StorageType
    {
        StorageType();
        ~StorageType();
        RF_Type::String Search;
        RF_Type::Int32 Position;
        RF_Type::Int32* Occurrence;
    };

    /// Configure Storage.
    static RF_Type::Bool Init(RF_Type::String& Text, 
                            const RF_Type::UInt32 Position, 
                            StorageType* Storage);

    /// Reset the position of the cursor.
    static void Reset(RF_Type::String& Text, 
                        const RF_Type::UInt32 Position, 
                        StorageType* Storage);

    /** Search the next match and return the position in Text
        * or return -1 if the cursor reach the end of Text.
        **/
    static RF_Type::Int32 DoNext(RF_Type::String& Text, 
                                StorageType* Storage);

    /// Search all matches in Text and return the number of hits.
    static RF_Type::Int32 DoAll(RF_Type::String& Text, 
                                StorageType* Storage);
};

// Implementation

Sunday::StorageType::StorageType()
:Position(0)
,Occurrence(0)
{
}

Sunday::StorageType::~StorageType()
{
    delete[] Occurrence;
}

RF_Type::Bool Sunday::Init(RF_Type::String& Text, 
                            const RF_Type::UInt32 Position, 
                            StorageType* Storage)
{
    Storage->Position=Position;
    // preprocessing
    RF_Type::Int32 i=0,j=0;
    RF_Type::UInt8 a;
    if (Storage->Search.Length()>0)
    {
        delete[] Storage->Occurrence;
        Storage->Occurrence=new RF_Type::Int32[256];     
        for (;i<256;++i)
            Storage->Occurrence[i]=-1;

        for(;j<static_cast<RF_Type::Int32>(Storage->Search.Length());++j)
        {
            a=Storage->Search[j];
            Storage->Occurrence[a]=j;
        }
    }
    return true;
}

void Sunday::Reset(RF_Type::String& Text, 
                        const RF_Type::UInt32 Position, 
                        StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 Sunday::DoNext(RF_Type::String& Text, 
                                StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0;
    while (Storage->Position<=txtLen-searchLen)
    {
        if(RadonFramework::System::Memory::Compare(p1 + Storage->Position, p2, searchLen) == 0)
        {
            Storage->Position+=searchLen;
            return Storage->Position;
        }
        Storage->Position+=searchLen;
        if (Storage->Position<txtLen)
            Storage->Position-=Storage->Occurrence[p1[Storage->Position]];
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 Sunday::DoAll(RF_Type::String& Text, 
                                StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0;
    while (Storage->Position<=txtLen-searchLen)
    {
        if(RadonFramework::System::Memory::Compare(p1 + Storage->Position, p2, searchLen) == 0)
            ++hit;
        Storage->Position+=searchLen;
        if (Storage->Position<txtLen)
            Storage->Position-=Storage->Occurrence[p1[Storage->Position]];
    }
    return hit;
}

} } } }

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_SUNDAY_HPP
