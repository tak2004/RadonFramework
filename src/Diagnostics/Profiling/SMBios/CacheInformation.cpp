#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/CacheInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework;

#pragma pack(push,1)
struct CacheInformationStructure
{
    StructureHeader Header;
    Core::Types::UInt8 SocketDesignation;//string
    Core::Types::UInt16 CacheConfiguration;
    Core::Types::UInt16 MaximumCacheSize;
    Core::Types::UInt16 InstalledSize;
    Core::Types::UInt16 SupportedSRAMType;
    Core::Types::UInt16 CurrentSRAMType;
    Core::Types::UInt8 CacheSpeed;
    Core::Types::UInt8 ErrorCorrectionType;
    Core::Types::UInt8 SystemCacheType;
    Core::Types::UInt8 Associativity;
};
#pragma pack(pop)

CacheInformation::CacheInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                                                      Collections::AutoVector<Core::Types::String> StringList )
{
    CacheInformationStructure* cacheinfo=(CacheInformationStructure*)Data.Get();
    m_SocketDesignation=StringList[cacheinfo->SocketDesignation-1]->TrimEnd(" ");
    m_Level=(cacheinfo->CacheConfiguration & 7)+1;
    m_IsSocketed=cacheinfo->CacheConfiguration>>3 & 1;
    m_Location=(CacheLocation::Type)(cacheinfo->CacheConfiguration>>5 & 3);
    m_IsEnabled=cacheinfo->CacheConfiguration>>7 & 1;
    m_OperationMode=(CacheOperationMode::Type)(cacheinfo->CacheConfiguration>>8 & 3);
    Core::Types::UInt8 granularity=(cacheinfo->MaximumCacheSize & 32768) ? 64 : 1;
    m_MaxCacheSize=(cacheinfo->MaximumCacheSize & 32767)*granularity;
    granularity=(cacheinfo->InstalledSize & 32768) ? 64 : 1;
    m_CacheSize=(cacheinfo->InstalledSize & 32767)*granularity;
    m_SupportedSRAMType=(CacheSRAMTypeField::Type)cacheinfo->SupportedSRAMType;
    m_CurrentSRAMType=(CacheSRAMTypeField::Type)cacheinfo->CurrentSRAMType;
    m_Speed=cacheinfo->CacheSpeed;
    m_ErrorCorrectionType=(CacheErrorCorrectionTypeField::Type)cacheinfo->ErrorCorrectionType;
    m_SystemCacheType=(CacheSystemCacheTypeField::Type)cacheinfo->SystemCacheType;
    m_Associativity=(CacheAssociativityField::Type)cacheinfo->Associativity;
}

Core::Types::String CacheInformation::SocketDesignation()const
{
    return m_SocketDesignation;
}

Core::Types::UInt8 CacheInformation::Level()const
{
    return m_Level;
}

Core::Types::Bool CacheInformation::IsSocketed()const
{
    return m_IsSocketed;
}

CacheLocation::Type CacheInformation::Location()const
{
    return m_Location;
}

Core::Types::String CacheInformation::LocationAsString()const
{
    Core::Types::String str;
    switch (m_Location)
    {
        case CacheLocation::External:
            str="External";
            break;
        case CacheLocation::Internal:
            str="Internal";
            break;
        case CacheLocation::Unknown:
            str="Unknown";
            break;
    }
    return str;
}

Core::Types::Bool CacheInformation::IsEnabled()const
{
    return m_IsEnabled;
}

CacheOperationMode::Type CacheInformation::OperationMode()const
{
    return m_OperationMode;
}

Core::Types::String CacheInformation::OperationModeAsString()const
{
    Core::Types::String str;
    switch (m_OperationMode)
    {
        case CacheOperationMode::Unknown:
            str="Unknown";
            break;
        case CacheOperationMode::VariesWithMemoryAddress:
            str="Varies with memory address";
            break;
        case CacheOperationMode::WriteBack:
            str="Write back";
            break;
        case CacheOperationMode::WriteThrough:
            str="Write through";
            break;
    }
    return str;
    return str;
}

Core::Types::UInt32 CacheInformation::MaxCacheSize()const
{
    return m_MaxCacheSize;
}

Core::Types::UInt32 CacheInformation::CacheSize()const
{
    return m_CacheSize;
}

CacheSRAMTypeField::Type CacheInformation::SupportedSRAMType()const
{
    return m_SupportedSRAMType;
}

CacheSRAMTypeField::Type CacheInformation::CurrentSRAMType()const
{
    return m_CurrentSRAMType;
}

Core::Types::UInt8 CacheInformation::Speed()const
{
    return m_Speed;
}

CacheErrorCorrectionTypeField::Type CacheInformation::ErrorCorrectionType()const
{
    return m_ErrorCorrectionType;
}

CacheSystemCacheTypeField::Type CacheInformation::SystemCacheType()const
{
    return m_SystemCacheType;
}

CacheAssociativityField::Type CacheInformation::Associativity()const
{
    return m_Associativity;
}
