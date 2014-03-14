#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/PortConnectorInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct PortConnectorInformationStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 InternalReferenceDesignator;//string
    RadonFramework::Core::Types::UInt8 InternalConnectorType;
    RadonFramework::Core::Types::UInt8 ExternalReferenceDesignator;//string
    RadonFramework::Core::Types::UInt8 ExternalConnectorType;
    RadonFramework::Core::Types::UInt8 PortType;
};
#pragma pack(pop)

PortConnectorInformation::PortConnectorInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                                   Collections::AutoVector<Core::Types::String> StringList)
{
    PortConnectorInformationStructure* portinfo=(PortConnectorInformationStructure*)Data.Get();
    if (portinfo->InternalReferenceDesignator)
        m_InternalReferenceDesignator=StringList[portinfo->InternalReferenceDesignator-1]->TrimEnd(" ");
    m_InternalConnectorType=(PortConnectorType::Type)portinfo->InternalConnectorType;
    if (portinfo->ExternalReferenceDesignator)
        m_ExternalReferenceDesignator=StringList[portinfo->ExternalReferenceDesignator-1]->TrimEnd(" ");
    m_ExternalConnectorType=(PortConnectorType::Type)portinfo->ExternalConnectorType;
    m_PortType=(PortType::Type)portinfo->PortType;
}

Core::Types::String PortConnectorInformation::PortConnectorTypeToString(PortConnectorType::Type Typ)const
{
    Core::Types::String str;
    switch (Typ)
    {
        case PortConnectorType::_9PinDualInline:str="9Pin dual inline";break;
        case PortConnectorType::_68PinDualInline:str="68Pin dual inline";break;
        case PortConnectorType::_50PinMiniSCSI:str="50Pin mini SCSI";break;
        case PortConnectorType::_50PinDualInline:str="50Pin dual inline";break;
        case PortConnectorType::_25PinDualInline:str="25Pin dual inline";break;
        case PortConnectorType::_1394:str="1394";break;
        case PortConnectorType::SSASCSI:str="SSASCSI";break;
        case PortConnectorType::SASOrSATAPlugReceptacle:str="SAS or SATA plug receptacle";break;
        case PortConnectorType::RJ11:str="RJ11";break;
        case PortConnectorType::RJ45:str="RJ45";break;
        case PortConnectorType::PS2:str="PS2";break;
        case PortConnectorType::Proprietary:str="Proprietary";break;
        case PortConnectorType::PCH98:str="PC-H98";break;
        case PortConnectorType::PC98Note:str="PC-98 note";break;
        case PortConnectorType::PC98Hireso:str="PC-98 Hireso";break;
        case PortConnectorType::PC98Full:str="PC-98 Full";break;
        case PortConnectorType::PC98:str="PC-98";break;
        case PortConnectorType::Other:str="Other";break;
        case PortConnectorType::OnBoardSoundInputFromCDROM:str="Onboard sound input from CDRom";break;
        case PortConnectorType::OnBoardIDE:str="Onboard IDE";break;
        case PortConnectorType::OnBoardFloppy:str="Onboard Floppy";break;
        case PortConnectorType::None:str="None";break;
        case PortConnectorType::MiniJack:str="MiniJack";break;
        case PortConnectorType::MiniDIN:str="Mini DIN";break;
        case PortConnectorType::MiniCentronicsType26:str="Mini centronics type 26";break;
        case PortConnectorType::MiniCentronicsType14:str="Mini centronics type 14";break;
        case PortConnectorType::MiniCentronics:str="Mini centronics";break;
        case PortConnectorType::MicroDIN:str="Micro DIN";break;
        case PortConnectorType::Infrared:str="Infrared";break;
        case PortConnectorType::HPHIL:str="HPHIL";break;
        case PortConnectorType::DB9PinMale:str="DB 9Pin male";break;
        case PortConnectorType::DB9PinFemale:str="DB 9Pin female";break;
        case PortConnectorType::DB25PinMale:str="DB 25Pin male";break;
        case PortConnectorType::DB25PinFemale:str="DB 25Pin female";break;
        case PortConnectorType::DB15PinMale:str="DB 15Pin male";break;
        case PortConnectorType::DB15PinFemale:str="DB 15Pin female";break;
        case PortConnectorType::CircularDIN8Male:str="Circular DIN8 male";break;
        case PortConnectorType::CircularDIN8Female:str="Circular DIN8 female";break;
        case PortConnectorType::Centronics:str="Centronics";break;
        case PortConnectorType::BNC:str="BNC";break;
        case PortConnectorType::AccessBus:str="Access bus";break;
    }
    return str;
}

Core::Types::String PortConnectorInformation::InternalReferenceDesignator()const
{
    return m_InternalReferenceDesignator;
}

Core::Types::String PortConnectorInformation::ExternalReferenceDesignator()const
{
    return m_ExternalReferenceDesignator;
}

PortConnectorType::Type PortConnectorInformation::InternalConnectorType()const
{
    return m_InternalConnectorType;
}

Core::Types::String PortConnectorInformation::InternalConnectorTypeAsString()const
{
    return PortConnectorTypeToString(m_InternalConnectorType);
}

PortConnectorType::Type PortConnectorInformation::ExternalConnectorType()const
{
    return m_ExternalConnectorType;
}

Core::Types::String PortConnectorInformation::ExternalConnectorTypeAsString()const
{
    return PortConnectorTypeToString(m_ExternalConnectorType);
}

PortType::Type PortConnectorInformation::PortType()const
{
    return m_PortType;
}

Core::Types::String PortConnectorInformation::PortTypeAsString()const
{
    Core::Types::String str;
    switch (m_PortType)
    {
        case PortType::_8251FIFOCompatible:str="8251 FIFO compatible";break;
        case PortType::_8251Compatible:str="8251 compatible";break;
        case PortType::VideoPort:str="Video port";break;
        case PortType::USB:str="USB";break;
        case PortType::SSASCSI:str="SSASCSI";break;
        case PortType::SerialPortXTATCompatible:str="Serial port XTAT compatible";break;
        case PortType::SerialPort16550Compatible:str="Serial port 16550 compatible";break;
        case PortType::SerialPort16550ACompatible:str="Serial port 16550A compatible";break;
        case PortType::SerialPort16450Compatible:str="Serial port 16450 compatible";break;
        case PortType::SCSIWide:str="SCSI wide";break;
        case PortType::SCSIPort:str="SCSI port";break;
        case PortType::SCSI2:str="SCSI2";break;
        case PortType::SATA:str="SATA";break;
        case PortType::SAS:str="SAS";break;
        case PortType::PCMCIAType3:str="PCMCIA type 3";break;
        case PortType::PCMCIAType2:str="PCMCIA type 2";break;
        case PortType::PCMCIAType1:str="PCMCIA type 1";break;
        case PortType::PCH98:str="PC-H98";break;
        case PortType::PC98Hireso:str="PC-98 Hireso";break;
        case PortType::PC98:str="PC-98";break;
        case PortType::ParallelPortXTATCompatible:str="Parallel port XTAT compatible";break;
        case PortType::ParallelPortPS2:str="Parallel port PS2";break;
        case PortType::ParallelPortEPP:str="Parallel port EPP";break;
        case PortType::ParallelPortECPEPP:str="Parallel port ECPEPP";break;
        case PortType::ParallelPortECP:str="Parallel port ECP";break;
        case PortType::Other:str="Other";break;
        case PortType::None:str="None";break;
        case PortType::NetworkPort:str="Network port";break;
        case PortType::MousePort:str="Mouse port";break;
        case PortType::ModemPort:str="Modem port";break;
        case PortType::MIDIPort:str="MIDI port";break;
        case PortType::KeyboardPort:str="Keyboard port";break;
        case PortType::JoyStickPort:str="Joystick port";break;
        case PortType::FireWire:str="FireWire";break;
        case PortType::Cardbus:str="Card bus";break;
        case PortType::AudioPort:str="Audio port";break;
        case PortType::AccessBusPort:str="Access bus port";break;
    }
    return str;
}