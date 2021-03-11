#include "kmemory.h"

MemoryBlock Memory[32];

void mem_init(struct MemoryMap map) 
{
	for (int i = 0; i < 32; i++) 
	{
		Memory[i].PhysicalStart = 0;
		Memory[i].Allocated = 0;
	}

	int MemIndex = 0;
	for (int i = 0; i < map.MemMapLen; i++) 
	{
		if (map.MemoryMap[i].Type == EfiConventionalMemory) 
		{
			//Duh
			Memory[MemIndex].PhysicalStart = map.MemoryMap[i].PhysicalStart;
			Memory[MemIndex].VirtualStart = map.MemoryMap[i].VirtualStart;

			//The End is the Start address + the size of the number of pages in bytes
			Memory[MemIndex].PhysicalEnd = map.MemoryMap[i].PhysicalStart + (1024 * map.MemoryMap[i].NumberOfPages);
			Memory[MemIndex].VirtualEnd = map.MemoryMap[i].VirtualStart + (1024 * map.MemoryMap[i].NumberOfPages);
			//
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