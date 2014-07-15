#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_KNUTHMORRISPRATT_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_KNUTHMORRISPRATT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Core { namespace Policies { namespace StringProcessor {

/** This policy search a String in an other String by comparing
* the word of the first String with the characters of the second.
* If they don't match then the cursor of the second String
* will be increased by one character and do the step again
* till a match occur or the cursor reach the end of the String.
**/
struct KnuthMorrisPratt
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
        RF_Type::Int32* Shift;
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

KnuthMorrisPratt::StorageType::StorageType()
:Position(0)
,Shift(0)
{
}

KnuthMorrisPratt::StorageType::~StorageType()
{
    delete[] Shift;
}

RF_Type::Bool KnuthMorrisPratt::Init(RF_Type::String& Text, 
                                    const RF_Type::UInt32 Position, 
                                    StorageType* Storage)
{
    Storage->Position=Position;
    // preprocessing
    RF_Type::Int32 i=0,j=-1,m=Storage->Search.Length();
    if (Storage->Search.Length()>0)
    {
        delete[] Storage->Shift;
        Storage->Shift=new RF_Type::Int32[m+1];     
        Storage->Shift[i]=j;
        while(i<m)
        {
            while(j>=0 && Storage->Search[i]!=Storage->Search[j])
                j=Storage->Shift[j];
            ++i;
            ++j;
            Storage->Shift[i]=j;
        }
    }
    return true;
}

void KnuthMorrisPratt::Reset(RF_Type::String& Text, 
                                const RF_Type::UInt32 Position, 
                                StorageType* Storage)
{
    Storage->Position=Position;
}

RF_Type::Int32 KnuthMorrisPratt::DoNext(RF_Type::String& Text, 
                                        StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i=0;
    while (Storage->Position<static_cast<RF_Type::Int32>(Text.Length()))
    {
        while(i>-1 && p2[i]!=p1[Storage->Position])
            i=Storage->Shift[i];
        ++i;
        ++Storage->Position;
        if (i>=static_cast<RF_Type::Int32>(Storage->Search.Length()))
            return Storage->Position-i;
    }
    Storage->Position=-1;
    return Storage->Position;
}

RF_Type::Int32 KnuthMorrisPratt::DoAll(RF_Type::String& Text, 
                                        StorageType* Storage)
{
    RF_Type::UInt8 const* p1=(RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2=(RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i=0,hit=0;
    while (Storage->Position<static_cast<RF_Type::Int32>(Text.Length()))
    {
        while(i>-1 && p2[i]!=p1[Storage->Position])
            i=Storage->Shift[i];
        ++i;
        ++Storage->Position;
        if (i>=static_cast<RF_Type::Int32>(Storage->Search.Length()))
        {
            ++hit;
            i=Storage->Shift[i];
        }
    }
    return hit;
}
            
} } } }

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_KNUTHMORRISPRATT_HPP
