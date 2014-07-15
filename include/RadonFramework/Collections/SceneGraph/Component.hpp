#ifndef RF_COLLECTIONS_SCENEGRAPH_COMPONENT_HPP
#define RF_COLLECTIONS_SCENEGRAPH_COMPONENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Collections { namespace SceneGraph {

class ComponentItem;

class Component
{
public:
    virtual ~Component();

    virtual void Update() = 0;
    virtual void Created() = 0;
    virtual void Destroy() = 0;
    virtual void Activated() = 0;
    virtual void Deactivate() = 0;

    RF_Type::Bool IsActive()const;
    void Active(RF_Type::Bool newValue);
protected:
    Component();
	Memory::AutoPointer<ComponentItem> data;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SCENE
#define RF_SHORTHAND_NAMESPACE_SCENE
namespace RF_Scene = RadonFramework::Collections::SceneGraph;
#endif

#endif // RF_COLLECTIONS_SCENEGRAPH_COMPONENT_HPP