#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_PORTCONNECTORINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_PORTCONNECTORINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace PortConnectorType
                {
                    enum Type
                    {
                        None=0,
                        Centronics=1,
                        MiniCentronics=2,
                        Proprietary=3,
                        DB25PinMale=4,
                        DB25PinFemale=5,
                        DB15PinMale=6,
                        DB15PinFemale=7,
                        DB9PinMale=8,
                        DB9PinFemale=9,
                        RJ11=10,
                        RJ45=11,
                        _50PinMiniSCSI=12,
                        MiniDIN=13,
                        MicroDIN=14,
                        PS2=15,
                        Infrared=16,
                        HPHIL=17,
                        AccessBus=18,
                        SSASCSI=19,
                        CircularDIN8Male=20,
                        CircularDIN8Female=21,
                        OnBoardIDE=22,
                        OnBoardFloppy=23,
                        _9PinDualInline=24,
                        _25PinDualInline=25,
                        _50PinDualInline=26,
                        _68PinDualInline=27,
                        OnBoardSoundInputFromCDROM=28,
                        MiniCentronicsType14=29,
                        MiniCentronicsType26=30,
                        MiniJack=31,
                        BNC=32,
                        _1394=33,
                        SASOrSATAPlugReceptacle=34,
                        PC98=35,
                        PC98Hireso=36,
                        PCH98=37,
                        PC98Note=38,
                        PC98Full=39,
                        Other=255
                    };
                }

                namespace PortType
                {
                    enum Type
                    {
                        None=0,
                        ParallelPortXTATCompatible=1,
                        ParallelPortPS2=2,
                        ParallelPortECP=3,
                        ParallelPortEPP=4,
                        ParallelPortECPEPP=5,
                        SerialPortXTATCompatible=6,
                        SerialPort16450Compatible=7,
                        SerialPort16550Compatible=8,
                        SerialPort16550ACompatible=9,
                        SCSIPort=10,
                        MIDIPort=11,
                        JoyStickPort=12,
                        KeyboardPort=13,
                        MousePort=14,
                        SSASCSI=15,
                        USB=16,
                        FireWire=17,
                        PCMCIAType1=18,
                        PCMCIAType2=19,
                        PCMCIAType3=20,
                        Cardbus=21,
                        AccessBusPort=22,
                        SCSI2=23,
                        SCSIWide=24,
                        PC98=25,
                        PC98Hireso=26,
                        PCH98=27,
                        VideoPort=28,
                        AudioPort=29,
                        ModemPort=30,
                        NetworkPort=31,
                        SATA=32,
                        SAS=33,
                        _8251Compatible=34,
                        _8251FIFOCompatible=35,
                        Other=255
                    };
                }

                class PortConnectorInformation
                {
                    public:
                        PortConnectorInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::String InternalReferenceDesignator()const;
                        Core::Types::String ExternalReferenceDesignator()const;
                        PortConnectorType::Type InternalConnectorType()const;
                        Core::Types::String InternalConnectorTypeAsString()const;
                        PortConnectorType::Type ExternalConnectorType()const;
                        Core::Types::String ExternalConnectorTypeAsString()const;
                        PortType::Type PortType()const;
                        Core::Types::String PortTypeAsString()const;
                    protected:
                        Core::Types::String PortConnectorTypeToString(PortConnectorType::Type Typ)const;
                        RadonFramework::Core::Types::String m_InternalReferenceDesignator;
                        PortConnectorType::Type m_InternalConnectorType;
                        RadonFramework::Core::Types::String m_ExternalReferenceDesignator;
                        PortConnectorType::Type m_ExternalConnectorType;
                        PortType::Type m_PortType;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_PORTCONNECTORINFORMATION_HPP