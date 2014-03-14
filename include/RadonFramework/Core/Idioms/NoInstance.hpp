#ifndef RF_CORE_IDIOMS_NOINSTANCE_HPP
#define RF_CORE_IDIOMS_NOINSTANCE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework
{
    namespace Core
    {
        namespace Idioms
        {
            class NoInstance
            {
                private:
                    NoInstance(const NoInstance&);
                    NoInstance& operator=( const NoInstance& );
                    NoInstance(){}
                    ~NoInstance(){}
            };
        }
    }
}

#endif // RF_CORE_IDIOMS_NOINSTANCE_HPP