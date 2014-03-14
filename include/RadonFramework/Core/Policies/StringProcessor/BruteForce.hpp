#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_BRUTEFORCE_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_BRUTEFORCE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            namespace StringProcessor
            {
                /** This policy search a String in an other String by comparing
                  * the word of the first String with the characters of the second.
                  * If they don't match then the cursor of the second String
                  * will be increased by one character and do the step again
                  * till a match occur or the cursor reach the end of the String.
                  **/
                struct BruteForce
                {
                    /** This struct will be use by the BruteForce policy to
                      * search an word in a text.
                      **/
                    struct StorageType
                    {
                        StorageType();
                        ~StorageType();
                        Types::String Search;
                        Types::Int32 Position;
                    };

                    /// Configure Storage.
                    static Types::Bool Init(Types::String& Text, 
                                            const Types::UInt32 Position, 
                                            StorageType* Storage);

                    /// Reset the position of the cursor.
                    static void Reset(Types::String& Text, 
                                      const Types::UInt32 Position, 
                                      StorageType* Storage);

                    /** Search the next match and return the position in Text
                      * or return -1 if the cursor reach the end of Text.
                      **/
                    static Types::Int32 DoNext(Types::String& Text, 
                                               StorageType* Storage);

                    /// Search all matches in Text and return the number of hits.
                    static Types::Int32 DoAll(Types::String& Text, 
                                              StorageType* Storage);
                };
            }
        }
    }
}

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_BRUTEFORCE_HPP
