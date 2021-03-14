#include "BluuUEFI/EFI_SYSTEM_TABLE.h"
#include "BluuUEFI/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include "KernelStartupInfo.h"
#include "Paging.h"

extern void KernelMain(struct KernelStartupInfo Info);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* ST)
{
	struct MemoryMap MemMap;

	MemMap.MemMapLen = sizeof(EFI_MEMORY_DESCRIPTOR);
	ST->BootServices->AllocatePool(EfiConventionalMemory, sizeof(EFI_MEMORY_DESCRIPTOR), (void**)&MemMap.MemoryMap);

	struct EFI_GRAPHICS_OUTPUT_PROTCOL* GOP;
	EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	ST->BootServices->LocateProtocol(&guid, 0, (void**)& GOP);

	EFI_STATUS Stat;

	//Get the memory map, keep allocating memory until there is enough space for it.
	while (Stat != EFI_SUCCESS)
	{
		MemMap.MemMapLen += sizeof(EFI_MEMORY_DESCRIPTOR);

		EFI_STATUS error = ST->BootServices->AllocatePool(EfiLoaderData, MemMap.MemMapLen, (void**)&MemMap.MemoryMap);

		if (error != EFI_SUCCESS)
		{
			return -1;
		}

		Stat = ST->BootServices->GetMemoryMap(&MemMap.MemMapLen, MemMap.MemoryMap, &MemMap.MapKey, &MemMap.DescriptorSize, &MemMap.DescriptorVersion);

		if (Stat != EFI_SUCCESS)
		{
			if (Stat == EFI_BUFFER_TOO_SMALL)
			{
				ST->BootServices->FreePool((void*)MemMap.MemoryMap);
			}

			else
			{
				return -1;
			}
		}
	}

	load_page_directory(page_directory);
	enable_paging();

	ST->BootServices->ExitBootServices(ImageHandle, MemMap.MapKey);

	struct KernelStartupInfo Info;
	Info.GOP = GOP;
	Info.Map = MemMap;
	Info.RuntimeServices = ST->RuntimeServices;

	KernelMain(Info);

	return EFI_SUCCESS;
}