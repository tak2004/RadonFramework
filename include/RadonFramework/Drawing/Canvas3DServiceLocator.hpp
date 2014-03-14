#ifndef RF_CANVAS3DSERVICELOCATOR_HPP
#define RF_CANVAS3DSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/Canvas3DService.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        class NullCanvas3DService:public Canvas3DService
        {
            public:
                NullCanvas3DService(const RadonFramework::Core::Types::String &Name):Canvas3DService(Name){}
                ICanvas3D* CreateCanvas3D(){return 0;}
        };

        typedef Core::Pattern::Locator<Canvas3DService,NullCanvas3DService> Canvas3DServiceLocator;
    }
}

#endif
