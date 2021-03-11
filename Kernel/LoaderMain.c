#include "BluuUEFI/EFI_SYSTEM_TABLE.h"
#include "BluuUEFI/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include "KernelStartupInfo.h"

extern void KernelMain(struct KernelStartupInfo Info);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* ST)
{
	struct MemoryMap MemMap;
	MemMap.MemMapLen = 1;

	ST->BootServices->AllocatePool(EfiConventionalMemory, sizeof(EFI_MEMORY_DESCRIPTOR), (void**)&MemMap.MemoryMap);

	struct EFI_GRAPHICS_OUTPUT_PROTCOL* GOP;
	EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	ST->BootServices->LocateProtocol(&guid, 0, (void**)&GOP);

	
	while (ST->BootServices->GetMemoryMap(&MemMap.DescriptorSize, MemMap.MemoryMap, &MemMap.MapKey, &MemMap.DescriptorSize, &MemMap.DescriptorVersion) == EFI_BUFFER_TOO_SMALL)
	{
		MemMap.MemMapLen++;
		ST->BootServices->FreePool(MemMap.MemoryMap);
		ST->BootServices->AllocatePool(EfiConventionalMemory, sizeof(EFI_MEMORY_DESCRIPTOR) * (MemMap.MemMapLen), (void**)&MemMap.MemoryMap);
	}

	ST->BootServices->ExitBootServices(ImageHandle, MemMap.MapKey);

	struct KernelStartupInfo Info;
	Info.Graphics = GOP;
	Info.MemMap = MemMap;

	KernelMain(Info);

	return EFI_SUCCESS;
}