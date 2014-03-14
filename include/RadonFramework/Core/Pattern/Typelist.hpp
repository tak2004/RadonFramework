#ifndef RF_CORE_PATTERN_TYPELIST_HPP
#define RF_CORE_PATTERN_TYPELIST_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework
{
    namespace Core
    {
        namespace Pattern
        {
            struct EmptyType{};

            template<class HEAD, class TAIL>
            struct TypeList
            {
                typedef HEAD Head;
                typedef TAIL Tail;
            };

            template <class T1=EmptyType, class T2=EmptyType, class T3=EmptyType,
                      class T4=EmptyType, class T5=EmptyType, class T6=EmptyType,
                      class T7=EmptyType, class T8=EmptyType, class T9=EmptyType>
            struct MakeTypeList
            {
                typedef TypeList<T1,Tail> Result;
                private:
                    typedef MakeTypeList<T2,T3,T4,T5,T6,T7,T8,T9>::Result Tail;
            };

            template<>
            struct MakeTypeList<>
            {
                typedef EmptyType Result;
            };
        }
    }
}

#endif // RF_CORE_PATTERN_TYPELIST_HPP