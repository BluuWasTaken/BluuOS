#include "../BluuUEFI/EFI_TYPES.h"
#include "../KernelStartupInfo.h"

typedef struct
{
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_PHYSICAL_ADDRESS PhysicalEnd;

	EFI_VIRTUAL_ADDRESS VirtualStart;
	EFI_VIRTUAL_ADDRESS	VirtualEnd;

	int Allocated;
	int Size;
} MemoryBlock;

void mem_init(struct MemoryMap map);
void* kmalloc(int size);