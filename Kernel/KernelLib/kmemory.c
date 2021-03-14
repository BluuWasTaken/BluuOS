#include "kmemory.h"

MemoryBlock Memory[32];

void memset(char value, void* destination, int size)
{
	for (int i = 0; i < size; i++) 
	{
		*(char*)(destination + i) = value;
	}
}

void mem_init(EFI_MEMORY_DESCRIPTOR* descriptors, int len, EFI_RUNTIME_SERVICES* RuntimeServices) 
{
	for (int i = 0; i < 32; i++) 
	{
		Memory[i].PhysicalStart = 0;
		Memory[i].Allocated = 0;
	}

	int MemIndex = 0;
	for (int i = 0; i < len; i++) 
	{
		EFI_MEMORY_DESCRIPTOR Descriptor = descriptors[i];

		if (Descriptor.Type == EfiConventionalMemory) 
		{
			//Duh
			Memory[MemIndex].PhysicalStart = Descriptor.PhysicalStart;
			Memory[MemIndex].VirtualStart = Descriptor.VirtualStart;

			//The End is the Start address + the size of the number of pages in bytes
			Memory[MemIndex].PhysicalEnd = Descriptor.PhysicalStart + (1024 * Descriptor.NumberOfPages);
			Memory[MemIndex].VirtualEnd = Descriptor.VirtualStart + (1024 * Descriptor.NumberOfPages);
			
			Memory[MemIndex].Size = Memory[MemIndex].PhysicalEnd - Memory[MemIndex].PhysicalStart;

			MemIndex++;
		}
	}
}

void* kmalloc(int size)
{
	for (int i = 0; i < 32; i++)
	{
		//Get the amount of free memory of a block by subtracting the amount of memory already allocated 
		if (Memory[i].PhysicalStart != 0 && (Memory[i].Size - Memory[i].Allocated) > size) 
		{
			//Free memory starts at Start + Allocated
			void* address = (void*)Memory[i].PhysicalStart + Memory[i].Allocated;

			Memory[i].Allocated += size;

			return address;
		}
	}

	return 0;
}