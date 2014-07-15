#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
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
struct SkipSearch
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
        RF_Type::Int32* Next;
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

SkipSearch::StorageType::StorageType()
:Position(0)
,Occurrence(0)
,Next(0)
{
}

SkipSearch::StorageType::~StorageType()
{
    delete[] Occurrence;
    delete[] Next;
}

RF_Type::Bool SkipSearch::Init(RF_Type::String& Text, 
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
        delete[] Storage->Next;
        Storage->Occurrence=new RF_Type::Int32[256];     
        Storage->Next=new RF_Type::Int32[Storage->Search.Length()];
        for (;i<256;++i)
            Storage->Occurrence[i]=-1;

        for(;j<static_cast<RF_Type::Int32>(Storage->Search.Length());++j)
        {
            a=Storage->Search[j];
            Storage->Next[j]=Storage->Occurrence[a];
            Storage->Occurrence[a]=j;
        }
    }
    return true;
}

void SkipSearch::Reset(RF_Type::String& Text, 
                        const RF_Type::UInt32 Position, 
                        StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 SkipSearch::DoNext(RF_Type::String& Text, 
                                StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
    {
        k=Storage->Occurrence[p1[Storage->Position]];
        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
        {
            if (RadonFramework::System::Memory::Compare(p1+Storage->Position-k,p2,searchLen))
                return Storage->Position-k;
            k=Storage->Next[k];
        }
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 SkipSearch::DoAll(RF_Type::String& Text, 
                                StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
    RF_Type::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
    {
        k=Storage->Occurrence[p1[Storage->Position]];
        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
        {
            if (RadonFramework::System::Memory::Compare(p1+Storage->Position-k,p2,searchLen)==0)
                ++hit;
            k=Storage->Next[k];
        }
    }
    return hit;
}
            
} } } }

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
