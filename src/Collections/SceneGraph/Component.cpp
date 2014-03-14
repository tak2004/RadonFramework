#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Collections/SceneGraph/Component.hpp"
#include "RadonFramework/Collections/SceneGraph/ComponentItem.hpp"

using namespace RadonFramework::Collections::SceneGraph;
using namespace RadonFramework::Core::Types;

Component::Component()
{

}

Component::~Component()
{
    //Destroy();
}

Bool Component::IsActive()const
{
    return data->isActive;
}

void Component::Active(Bool newValue)
{
    if (data->isActive != newValue)
    {
        data->isActive = newValue;
        if (data->isActive)
            Activated();
        else
            Deactivate();
    }
}