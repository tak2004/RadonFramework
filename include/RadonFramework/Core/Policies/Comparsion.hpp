#ifndef RF_CORE_POLICIES_COMPARSION_HPP

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            template<class T1, class T2>
            struct Comparsion
            {
                typedef Delegate2<T1,T2,RF_Type::Int32> Type;
            };
        }
    }
}

#endif