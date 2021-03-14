#include "../KernelStartupInfo.h"
#include "../KernelLib/kmemory.h"
#include "GDT64.h"


#define BluuOS {0xA2F0d7ce, 0xACDC, 0xCDAC, { 0x69,0xBE,0xC9,0x18,0xDE,0x8F,0x5A,0xEA }}

void KernelMain(struct KernelStartupInfo info)
{
	mem_init(info.Map.MemoryMap, info.Map.MemMapLen / sizeof(EFI_MEMORY_DESCRIPTOR), info.RuntimeServices);

	int width = info.GOP->Mode->Info->HorizontalResolution;
	int height = info.GOP->Mode->Info->VerticalResolution;

	EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Pixels = kmalloc(40 * 40);

	for (int i = 0; i < 1600; i++) 
	{
		Pixels[i].Red = 255;
		Pixels[i].Green = 255;
		Pixels[i].Blue = 0;
	}

	info.GOP->Blt(info.GOP, Pixels, EfiBltBufferToVideo, 0, 0, 0, 0, 40, 40, 0);
	return;
};