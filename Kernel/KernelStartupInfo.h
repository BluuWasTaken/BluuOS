#pragma once
#include "BluuUEFI/EFI_TYPES.h"
#include "BluuUEFI/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"

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
	struct MemoryMap MemMap;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* Graphics;
};