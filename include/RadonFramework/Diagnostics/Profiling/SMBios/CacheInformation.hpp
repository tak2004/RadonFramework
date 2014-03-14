#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_CACHEINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_CACHEINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace CacheSRAMTypeField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        NonBurst=4,
                        Burst=8,
                        PipelineBurst=16,
                        Synchronous=32,
                        Asynchronous=64
                        //bit 7-15 Reserved, must be zero
                    };
                }

                namespace CacheErrorCorrectionTypeField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        None=4,
                        Parity=8,
                        SingleBitECC=16,
                        MultiBitECC=32
                    };
                }

                namespace CacheSystemCacheTypeField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        Instruction=4,
                        Data=8,
                        Unified=16
                    };
                }

                namespace CacheAssociativityField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        DirectMapped=4,
                        _2WaySetAssociative=8,
                        _4WaySetAssociative=16,
                        FullyAssociative=32,
                        _8WaySetAssociative=64,
                        _16WaySetAssociative=128
                    };
                }

                namespace CacheLocation
                {
                    enum Type
                    {
                        Internal=0,
                        External=1,
                        Unknown=3
                    };
                }

                namespace CacheOperationMode
                {
                    enum Type
                    {
                        WriteThrough,
                        WriteBack,
                        VariesWithMemoryAddress,
                        Unknown
                    };
                }

                class CacheInformation
                {
                    public:
                        CacheInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::String SocketDesignation()const;
                        Core::Types::UInt8 Level()const;
                        Core::Types::Bool IsSocketed()const;
                        CacheLocation::Type Location()const;
                        Core::Types::String LocationAsString()const;
                        Core::Types::Bool IsEnabled()const;
                        CacheOperationMode::Type OperationMode()const;
                        Core::Types::String OperationModeAsString()const;
                        Core::Types::UInt32 MaxCacheSize()const;
                        Core::Types::UInt32 CacheSize()const;
                        CacheSRAMTypeField::Type SupportedSRAMType()const;
                        CacheSRAMTypeField::Type CurrentSRAMType()const;
                        Core::Types::UInt8 Speed()const;
                        CacheErrorCorrectionTypeField::Type ErrorCorrectionType()const;
                        CacheSystemCacheTypeField::Type SystemCacheType()const;
                        CacheAssociativityField::Type Associativity()const;
                    protected:
                        //smbios
                        Core::Types::String m_SocketDesignation;
                        Core::Types::UInt8 m_Level;
                        Core::Types::Bool m_IsSocketed;
                        CacheLocation::Type m_Location;
                        Core::Types::Bool m_IsEnabled;
                        CacheOperationMode::Type m_OperationMode;
                        Core::Types::UInt32 m_MaxCacheSize;
                        Core::Types::UInt32 m_CacheSize;
                        CacheSRAMTypeField::Type m_SupportedSRAMType;
                        CacheSRAMTypeField::Type m_CurrentSRAMType;
                        Core::Types::UInt8 m_Speed;
                        CacheErrorCorrectionTypeField::Type m_ErrorCorrectionType;
                        CacheSystemCacheTypeField::Type m_SystemCacheType;
                        CacheAssociativityField::Type m_Associativity;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_CACHEINFORMATION_HPP