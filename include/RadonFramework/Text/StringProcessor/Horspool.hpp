#ifndef RF_TEXT_STRINGPROCESSORS_HORSPOOL_HPP
#define RF_TEXT_STRINGPROCESSORS_HORSPOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Text::StringProcessors {

/** This policy search a String in an other String by comparing
* the word of the first String with the characters of the second.
* If they don't match then the cursor of the second String
* will be increased by one character and do the step again
* till a match occur or the cursor reach the end of the String.
**/
struct Horspool
{
    /** This struct will be use by the BruteForce policy to
    * search an word in a text.
    **/
    struct StorageType
    {
        StorageType();
        ~StorageType();
        RF_Type::String Search;
        RF_Type::Size Position;
        RF_Type::Size* Occurrence;
    };

    /// Configure Storage.
    static RF_Type::Bool Init(RF_Type::String& Text, const RF_Type::Size Position, 
                              StorageType* Storage);

    /// Reset the position of the cursor.
    static void Reset(RF_Type::String& Text, const RF_Type::Size Position, 
                      StorageType* Storage);

    /** Search the next match and return the position in Text
        * or return -1 if the cursor reach the end of Text.
        **/
    static RF_Type::Size DoNext(RF_Type::String& Text, StorageType* Storage);

    /// Search all matches in Text and return the number of hits.
    static RF_Type::Size DoAll(RF_Type::String& Text, StorageType* Storage);

    /** Search all matches in Text and return the number of hits
        * and indices.
        **/
    static RF_Type::Size DoAll(RF_Mem::AutoPointerArray<RF_Type::Size>& Indices,
        RF_Type::String& Text, StorageType* Storage);
};
            
}

#endif // RF_TEXT_STRINGPROCESSORS_HORSPOOL_HPP
