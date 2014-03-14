#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBiosService.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/InformationFactory.hpp>
#include <RadonFramework/Core/Types/MemoryRange.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

const ReadBuffer& SMBiosService::ReadSMBios()
{
    this->LoadSMBios();
    return m_SMBios;
}

const ReadBuffer& SMBiosService::GetSMBios()const
{
    return m_SMBios;
}

SMBiosService::SMBiosService( const String &Name )
:Service(Name)
{

}

UInt8 SMBiosService::MajorVersion() const
{
    return m_MajorVersion;
}

UInt8 SMBiosService::MinorVersion() const
{
    return m_MinorVersion;
}

AutoVector<String> ParseUnformattedStructure(ReadBuffer &Buf)
{
    AutoVector<String> strlist;
    const UInt8* p=Buf.GetCursorData();
    for(;;)
    {
        if(Buf.ReadUInt8()==0)
        {
            if(MemoryRange(Buf.GetCursorData()-p)>1)
            {
                strlist.PushBack(AutoPointer<String>(new String((Char*)p)));
                p=Buf.GetCursorData();
            }
            if(Buf.AsUInt8()==0)
            {
                Buf.Seek(1);
                break;
            }
        }
    }
    return strlist;
}

struct StructureHeaderFormat
{
    UInt8  Type;
    UInt8  Length;
    UInt16 Handle;
};

AutoVector<SMBios::Information> SMBiosService::GetInformation( 
    const SMBios::HeaderType::Type OfType, ReadBuffer& Buffer)
{
    AutoVector<SMBios::Information> infos;
    StructureHeaderFormat *head=0;
    Bool reading=true;
    AutoVector<String> strlist;

    Buffer.ResetCursor();
    while (reading)
    {
        if (Buffer.IsEnd())
        {
            reading=false;
            break;
        }

        head=(StructureHeaderFormat*)Buffer.GetCursorData();
        if (head->Type==OfType)
        {
            AutoPointerArray<UInt8> data=Buffer.ReadBytes(head->Length);
            strlist=ParseUnformattedStructure(Buffer);
            AutoPointer<SMBios::Information> info(new SMBios::Information);
            info->Type=OfType;
            info->Data=data;
            info->StringList=strlist;
            info->Handle=head->Handle;
            infos.PushBack(info);
        }
        else
            switch (head->Type)
            {
                case SMBios::HeaderType::EndOfTable:
                    reading=false;
                    break;
                default:
                    Buffer.Seek(head->Length);
                    ParseUnformattedStructure(Buffer);
            }
    }

    return infos;
}
