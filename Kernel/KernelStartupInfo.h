#pragma once
#include "../BluuUEFI/EFI_TYPES.h"
#include "../BluuUEFI/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include "../BluuUEFI/EFI_RUNTIME_SERVICES.h"

struct MemoryMap
{
	UINTN MemoryMapSize;
	EFI_MEMORY_DESCRIPTOR* MemoryMap;
	UINTN MapKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;

	int MemMapLen;
};

struct KernelStartupInfo
{
	struct MemoryMap Map;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP;
	EFI_RUNTIME_SERVICES* RuntimeServices;
};
