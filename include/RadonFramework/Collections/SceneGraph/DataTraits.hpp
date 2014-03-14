#ifndef RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP
#define RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Collections
    {
        namespace SceneGraph
        {
            template <class T>
            struct DataTraits
            {
                typedef RFTYPE::Int64 IDType;
            };
        }
    }
}

#endif // RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP