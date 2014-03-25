#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Radon.hpp"
#include "RadonFramework/Plugins.hpp"
#include <RadonFramework/Drawing/Forms/WindowServiceLocator.hpp>
#include <RadonFramework/Drawing/Canvas3DServiceLocator.hpp>
#include <RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp>
#include <RadonFramework/IO/DecoderServiceLocator.hpp>
#include <RadonFramework/IO/ProtocolServiceLocator.hpp>
#include <RadonFramework/IO/FileProtocolService.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBiosServiceLocator.hpp>
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/System/Processor.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/System/Time.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/Diagnostics/ProcessorData.hpp"

using namespace RadonFramework::Forms;
using namespace RadonFramework::Drawing;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Time;
using namespace RadonFramework;
using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics::Profiling;
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
        RFTYPE::UInt32 m_IsSubSystemInitialized;
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
        RFMEM::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Memory;
    }

    if (Flags & RadonFramework::Init::Time)
    {
        RFTIME::Dispatch();
        m_PIMPL->m_IsSubSystemInitialized &= RadonFramework::Init::Time;
    }

    if (Flags & RadonFramework::Init::Drawing)
    {
        #ifdef RF_USE_OPENGL
            #ifdef RF_USE_X11
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL1Canvas3DService("OpenGL1.x")));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL2Canvas3DService("OpenGL2.x")));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new X11OpenGL3Canvas3DService("OpenGL3.x")));
            #endif
            #ifdef RF_USE_GDI
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL1Canvas3DService("OpenGL1.x")));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL2Canvas3DService("OpenGL2.x")));
            Canvas3DServiceLocator::Register(AutoPointer<Canvas3DService>((Canvas3DService*)new GDIOpenGL3Canvas3DService("OpenGL3.x")));
            #endif
        #endif
        Canvas3DServiceLocator::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Drawing;
    }

    if (Flags & RadonFramework::Init::Forms)
    {
        #ifdef RF_USE_X11
        WindowServiceLocator::Register(AutoPointer<WindowService>(new X11WindowService("Linux_X11")));
        #endif
        #ifdef RF_USE_GDI
        WindowServiceLocator::Register(AutoPointer<WindowService>(new WindowsWindowService("Windows_GDI")));
        #endif
        WindowServiceLocator::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Forms;
    }

    if (Flags & RadonFramework::Init::Hashing)
    {
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new MurmurHashHashfunctionService("MurmurHash")));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibMD5HashfunctionService("MD5")));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA1HashfunctionService("SHA1")));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA256HashfunctionService("SHA256")));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA384HashfunctionService("SHA384")));
        HashfunctionServiceLocator::Register(AutoPointer<HashfunctionService>(new HashlibSHA512HashfunctionService("SHA512")));
        HashfunctionServiceLocator::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Hashing;
    }

    if (Flags & RadonFramework::Init::IO)
    {
        RFFILE::Dispatch();
        DecoderServiceLocator::Initialize();
        ProtocolServiceLocator::Register(AutoPointer<ProtocolService>(new FileProtocolService("file")));
        ProtocolServiceLocator::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::IO;
    }

    if (Flags & RadonFramework::Init::Net)
    {
        Network::NetService::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Net;
    }
    
    if (Flags & RadonFramework::Init::Diagnostics)
    {
        #ifdef RF_WINDOWS
            SMBiosServiceLocator::Register(AutoPointer<SMBiosService>(new WindowsSMBiosService("Windows_SMBios")));
        #endif
        #ifdef RF_LINUX
            SMBiosServiceLocator::Register(AutoPointer<SMBiosService>(new LinuxSMBiosService("Linux_SMBios")));
        #endif
        SMBiosServiceLocator::Initialize();
        m_PIMPL->m_IsSubSystemInitialized&=RadonFramework::Init::Diagnostics;
    }

    if (Flags & RadonFramework::Init::Core)
    {
        RFSTR::Dispatch();
        RFENV::Dispatch();
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
        SMBiosServiceLocator::Quit();
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Core)
    {
    }

    if (m_PIMPL->m_IsSubSystemInitialized & RadonFramework::Init::Process)
    {
    }
}

Bool Radon::IsSubSystemInitialized(RFTYPE::UInt32 Flag)const
{
    return false;
}