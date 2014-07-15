#ifndef RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP
#define RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Collections { namespace SceneGraph {
            
template <class T>
struct DataTraits
{
    typedef RF_Type::Int64 IDType;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_DATATRAITS_HPP