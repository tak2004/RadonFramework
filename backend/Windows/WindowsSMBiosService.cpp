#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/WindowsSMBiosService.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <Windows.h>

using namespace RadonFramework::Diagnostics::Profiling;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

WindowsSMBiosService::WindowsSMBiosService( const String &Name )
:SMBiosService(Name)
{
	LoadSMBios();
}

#pragma warning(push)
#pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#pragma pack(push,1)
struct RawSMBIOSData
{
	UInt8  Used20CallingMethod;
	UInt8  SMBIOSMajorVersion;
	UInt8  SMBIOSMinorVersion;
	UInt8  DmiRevision;
	UInt32 Length;
	UInt8  SMBIOSTableData[];
};
#pragma pack(pop)
#pragma warning(pop)

typedef LONG NTSTATUS;

typedef NTSTATUS (__stdcall *GetSystemFirmwareTablePtr) (IN UInt32 iFirmwareTableProviderSignature,
														 IN UInt32 FirmwareTableID,
														 OUT void* InputBuffer,
														 IN UInt32 InputBufferLength );

void WindowsSMBiosService::LoadSMBios()
{
	GetSystemFirmwareTablePtr GetSystemFirmwareTable = 0;
	HMODULE hKerneldll;
	hKerneldll = GetModuleHandle("kernel32.dll");
	if (!hKerneldll)
	{
		LogError("GetModuleHandle returned an bad value.");
		return;
	}

	// These APIs are only available on W2K3 SP1 and higher.
	GetSystemFirmwareTable = (GetSystemFirmwareTablePtr) GetProcAddress(hKerneldll, "GetSystemFirmwareTable");
	if (GetSystemFirmwareTable==0)
	{
		LogError("GetSystemFirmwareTable not supported by this OS.");
		return;
	}
	int iBufferSizeNeeded = GetSystemFirmwareTable( 'RSMB', 0, 0, 0 );
	char* pBuffer=new char[iBufferSizeNeeded];
	RFMEM::Set( pBuffer, 0, iBufferSizeNeeded );
	iBufferSizeNeeded = GetSystemFirmwareTable('RSMB', 0, pBuffer, iBufferSizeNeeded);
	RawSMBIOSData* smbios=(RawSMBIOSData*)pBuffer;
	AutoPointerArray<RadonFramework::Core::Types::UInt8> arr(new Core::Types::UInt8[smbios->Length],smbios->Length);
	RFMEM::Copy(arr.Get(), smbios->SMBIOSTableData, smbios->Length);
	m_SMBios=ReadBuffer(arr,smbios->Length);
	m_MajorVersion=smbios->SMBIOSMajorVersion;
	m_MinorVersion=smbios->SMBIOSMinorVersion;
	delete[] pBuffer;
}
