#include "../../BluuUEFI/EFI_TYPES.h"
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

void memset(char value, void* destination, int size);
void mem_init(EFI_MEMORY_DESCRIPTOR* descriptors, int len, EFI_RUNTIME_SERVICES* RuntimeServices);
void* kmalloc(int size);
