#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Linux/LinuxSMBiosService.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

using namespace RadonFramework::Diagnostics::Profiling;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

LinuxSMBiosService::LinuxSMBiosService( const String &Name )
:SMBiosService(Name)
{
    LoadSMBios();
}

#pragma pack(push,1)
struct RawSMBIOSData
{
    UInt8 anchor[4];
    UInt8 checksum;
    UInt8 eps_length;
    UInt8 major_ver;
    UInt8 minor_ver;
    UInt16 max_struct_size;
    UInt8 revision;
    UInt8 formatted_area[5];
    //dmi infos
    UInt8 dmi_anchor[5];
    UInt8 dmi_checksum;
    UInt16 table_length;
    UInt32 table_address;
    UInt16 table_num_structs;
    UInt8 smbios_bcd_revision;
};
#pragma pack(pop)

void LinuxSMBiosService::LoadSMBios()
{
    UInt32 start=0xE0000UL;
    UInt32 end=0xFFFFFUL;
    UInt32 size=end-start;

    int fd=open("/dev/mem",O_RDONLY);
    if (fd<0)
    {
        LogError("Can't access /dev/mem with error \"%s\".",strerror(errno));
        return;
    }
    char* mem=(char*)mmap(0,size,PROT_READ,MAP_FILE|MAP_SHARED,fd,start);
    if(mem==(void*)-1)
    {
        LogError("MMap failed.");
        close(fd);
        return;
    }
    UInt32 ob=0;
    char* p=(char*)mem;
    while(ob+sizeof(RawSMBIOSData)<end)
    {
        if (RFMEM::Compare(p,"_DMI_",5)==0)
        {
            LogDebug("Found DMI entry.");
            // TODO : implement dmi check
        }

        if(RFMEM::Compare(p,"_SM_",4)==0)
        {
            LogDebug("Found smbios entry.");
            RawSMBIOSData bios;
            RFMEM::Copy(&bios, p, sizeof(RawSMBIOSData));
            if (bios.table_address<start || bios.table_address>(end-bios.table_length))
            {//read new memory range
                munmap(mem,size);
                mem=(char*)mmap(0,bios.table_length,PROT_READ,MAP_FILE|MAP_SHARED,fd,bios.table_address);
                size=bios.table_length;
            }

            AutoPointerArray<RadonFramework::Core::Types::UInt8> arr(new Core::Types::UInt8[size],size);
            RFMEM::Copy(arr.Get(), mem,size);
            ReadBuffer(arr,size).AssignTo(m_SMBios);
            m_MajorVersion=bios.major_ver;
            m_MinorVersion=bios.minor_ver;
            break;
        }
        ob+=16;
        p+=16;
    }
    munmap(mem,size);
    close(fd);
}
