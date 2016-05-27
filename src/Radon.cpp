#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Radon.hpp"
#include "RadonFramework/Plugins.hpp"
#include "RadonFramework/Drawing/Forms/WindowServiceLocator.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceLocator.hpp"
#include "RadonFramework/Drawing/FontServiceLocator.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"
#include "RadonFramework/IO/DecoderServiceLocator.hpp"
#include "RadonFramework/IO/ProtocolServiceLocator.hpp"
#include "RadonFramework/IO/FileProtocolService.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/System/Drawing/SystemTrayServiceLocator.hpp"
#include "RadonFramework/System/Drawing/OSFontService.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/Core/Common/DataManagment.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Forms;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Time;
using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Threading;
using namespace RadonFramework::System;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics;

class Radon::PIMPL
{
    public:
        PIMPL()
        :m_IsSubSystemInitialized(0)
        {}
        RF_Type::UInt32 m_IsSubSystemInitialized;
};

Bool Radon::m_IsInitialized=false;

Radon::Radon(UInt32 Flags)
{
    Assert(!m_IsInitialized, "The framework is already initialized, do it a second time can occur unpredictable behavior.")
    if (!m_IsInitialized)
    {
        m_PIMPL = AutoPointer<PIMPL>(new PIMPL());
        m_PIMPL->m_IsSubSystemInitialized=Flags;
        InitSubSystem(Flags);
        m_IsInitialized=true;
    }
}

Radon::~Radon()
{
    if (m_IsInitialized)
    {
        QuitSubSystem(m_PIMPL->m_IsSubSystemInitialized);
        m_PIMPL->m_IsSubSystemInitialized=0;
        m_IsInitialized=false;
    }
}

void Radon::InitSubSystem(UInt32 Flags)
{
    if (Flags & RadonFramework::Init::Memory)
    {
        RF_SysMem::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Memory;
    }

    if(Flags & RadonFramework::Init::Threading)
    {
        RF_SysThread::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Threading;
    }

    if (Flags & RadonFramework::Init::Time)
    {
        RF_SysTime::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Time;
    }

    if (Flags & RadonFramework::Init::Drawing)
    {
        Canvas3DServiceLocator::Initialize();
        #ifdef RF_USE_OPENGL
            #ifdef RF_USE_X11
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL1Canvas3DService("OpenGL1.x"_rfs)));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL2Canvas3DService("OpenGL2.x"_rfs)));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL3Canvas3DService("OpenGL3.x"_rfs)));
            Canvas3DServiceLocator::SetDefault("OpenGL3.x"_rfs);
            #endif
            #ifdef RF_USE_GDI
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL1Canvas3DService("OpenGL1.x"_rfs)));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL2Canvas3DService("OpenGL2.x"_rfs)));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL3Canvas3DService("OpenGL3.x"_rfs)));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGLCanvas3DService("Newest OpenGL Version with GDI"_rfs)));
            Canvas3DServiceLocator::SetDefault("Newest OpenGL Version with GDI"_rfs);
            #endif
            #ifdef RF_USE_WDM
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new WDMOpenGLCanvas3DService("Newest OpenGL Version without GDI"_rfs)));
            Canvas3DServiceLocator::SetDefault("Newest OpenGL Version without GDI"_rfs);
            #endif
        #endif
        RF_SysDraw::SystemTrayServiceLocator::Initialize();
        #if defined(RF_WINDOWS)
        RF_SysDraw::SystemTrayServiceLocator::Register(AutoPointer<RF_SysDraw::SystemTrayService>((RF_SysDraw::SystemTrayService*)new RF_SysDraw::SystemTrayServiceWindows("Windows system tray"_rfs)));
        #endif
        
        FontServiceLocator::Initialize();
        #if defined(RF_WINDOWS)        
            FontServiceLocator::Register(AutoPointer<FontService>((FontService*)new RF_SysDraw::OSFontService("OS Fonts"_rfs)));
        #endif
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Drawing;
    }

    if (Flags & RadonFramework::Init::Forms)
    {
        WindowServiceLocator::Initialize();
        #ifdef RF_USE_X11
        WindowServiceLocator::Register(AutoPointer<WindowService>(new X11WindowService("Linux_X11"_rfs)));
        #endif
        #ifdef RF_USE_GDI
        WindowServiceLocator::Register(AutoPointer<WindowService>(new WindowsWindowService("Windows_GDI"_rfs)));
        #endif
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Forms;
    }

    if (Flags & RadonFramework::Init::Hashing)
    {
        HashfunctionServiceLocator::Initialize();
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new MurmurHashHashfunctionService("MurmurHash"_rfs)));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibMD5HashfunctionService("MD5"_rfs)));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA1HashfunctionService("SHA1"_rfs)));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA256HashfunctionService("SHA256"_rfs)));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA384HashfunctionService("SHA384"_rfs)));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA512HashfunctionService("SHA512"_rfs)));
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Hashing;
    }

    if (Flags & RadonFramework::Init::IO)
    {
        RFFILE::Dispatch();
        DecoderServiceLocator::Initialize();
        ProtocolServiceLocator::Initialize();
        ProtocolServiceLocator::Register(AutoPointer<ProtocolService>(new FileProtocolService("file"_rfs)));
        ProtocolServiceLocator::Register(AutoPointer<ProtocolService>(new MemoryProtocolService("mem"_rfs)));
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::IO;
    }

    if (Flags & RadonFramework::Init::Net)
    {
        Network::NetService::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Net;
    }
    
    if (Flags & RadonFramework::Init::Diagnostics)
    {
        RF_SysHardware::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Diagnostics;
    }

    if (Flags & RadonFramework::Init::Core)
    {
        RF_SysStr::Dispatch();
        RF_SysEnv::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Core;
    }

    if (Flags & RadonFramework::Init::Process)
    {
        RFPROC::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Process;
    }
}

void Radon::QuitSubSystem(UInt32 Flags)
{
    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Memory)
    {
    }

    if(m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Threading)
    {

    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Time)
    {

    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Drawing)
    {
        Canvas3DServiceLocator::Quit();
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Forms)
    {
        WindowServiceLocator::Quit();
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Hashing)
        HashfunctionServiceLocator::Quit();

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::IO)
    {
        DecoderServiceLocator::Quit();
        ProtocolServiceLocator::Quit();
    }
    
    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Net)
        Network::NetService::Free();
    
    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Diagnostics)
    {
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Core)
    {
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Process)
    {
    }
}

Bool Radon::IsSubSystemInitialized(RF_Type::UInt32 Flag)const
{
    return false;
}