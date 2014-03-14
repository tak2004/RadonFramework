#ifndef RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
#define RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <string.h>

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
                struct SkipSearch
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
                        Types::Int32* Occurrence;
                        Types::Int32* Next;
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

                Types::Bool SkipSearch::Init(Types::String& Text, 
                                             const Types::UInt32 Position, 
                                             StorageType* Storage)
                {
                    Storage->Position=Position;
                    // preprocessing
                    Types::Int32 i=0,j=0;
                    Types::UInt8 a;
                    if (Storage->Search.Length()>0)
                    {
                        delete[] Storage->Occurrence;
                        delete[] Storage->Next;
                        Storage->Occurrence=new Types::Int32[256];     
                        Storage->Next=new Types::Int32[Storage->Search.Length()];
                        for (;i<256;++i)
                            Storage->Occurrence[i]=-1;

                        for(;j<static_cast<Types::Int32>(Storage->Search.Length());++j)
                        {
                            a=Storage->Search[j];
                            Storage->Next[j]=Storage->Occurrence[a];
                            Storage->Occurrence[a]=j;
                        }
                    }
                    return true;
                }

                void SkipSearch::Reset(Types::String& Text, 
                                     const Types::UInt32 Position, 
                                     StorageType* Storage)
                {
                    Storage->Position=Position;
                }

                Types::Int32 SkipSearch::DoNext(Types::String& Text, 
                                              StorageType* Storage)
                {
                    Types::UInt8 const* p1=(Types::UInt8*)Text.c_str();
                    Types::UInt8 const* p2=(Types::UInt8*)Storage->Search.c_str();
                    Types::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
                    Types::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
                    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
                    {
                        k=Storage->Occurrence[p1[Storage->Position]];
                        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
                        {
                            if (RFMEM::Compare(p1+Storage->Position-k,p2,searchLen))
                                return Storage->Position-k;
                            k=Storage->Next[k];
                        }
                    }
                    Storage->Position=-1;
                    return Storage->Position;
                }

                Types::Int32 SkipSearch::DoAll(Types::String& Text, 
                                             StorageType* Storage)
                {
                    Types::UInt8 const* p1=(Types::UInt8*)Text.c_str();
                    Types::UInt8 const* p2=(Types::UInt8*)Storage->Search.c_str();
                    Types::Int32 txtLen=Text.Length(),searchLen=Storage->Search.Length();
                    Types::Int32 hit=0,searchLenMinusOne=searchLen-1,k;
                    for(Storage->Position=searchLenMinusOne;Storage->Position<txtLen;Storage->Position+=searchLen)
                    {
                        k=Storage->Occurrence[p1[Storage->Position]];
                        while(k>=0 && Storage->Position-k<=txtLen-searchLen)
                        {
                            if (RFMEM::Compare(p1+Storage->Position-k,p2,searchLen)==0)
                                ++hit;
                            k=Storage->Next[k];
                        }
                    }
                    return hit;
                }
            }
        }
    }
}

#endif // RF_CORE_POLICIES_STRINGPROCESSOR_SKIPSEARCH_HPP
