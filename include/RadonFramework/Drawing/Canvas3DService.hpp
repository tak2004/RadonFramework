#ifndef RF_CANVAS3DSERVICE_HPP
#define RF_CANVAS3DSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Drawing/ICanvas3D.hpp>

namespace RadonFramework
{
  namespace Drawing
  {
    class Canvas3DService:public Core::Pattern::Service
    {
      public:
        Canvas3DService(const RFTYPE::String &Name);
        ~Canvas3DService();
        virtual ICanvas3D* CreateCanvas3D()=0;
    };
  }
}

#endif