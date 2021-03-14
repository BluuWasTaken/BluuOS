#include "GDT64.h"

void LoadGDT()
{
	struct GDTEntry Null;
	Null.LimitLow = 0xFFFF;
	Null.BaseLow = 0;
	Null.BaseMiddle = 0;
	Null.Access = 0;
	Null.Granularity = 1;
	Null.BaseHigh = 0;

	struct GDTEntry Code;
	Code.LimitLow = 0xFFFFF;
	Code.BaseLow = 0;
	Code.BaseMiddle = 0;
	Code.Access = 0x9A;
	Code.Granularity = 0xAF;
	Code.BaseHigh = 0;

	struct GDTEntry Data;
	Data.LimitLow = 0xFFFFF;
	Data.BaseLow = 0;
	Data.BaseMiddle = 0;
	Data.Access = 0b10010010;
	Data.Granularity = 0b00000000;
	Data.BaseHigh = 0;

	GDT[0] = Null;
	GDT[1] = Code;
	GDT[2] = Data;

	struct GDTPointer GdtPointer;
	GdtPointer.Base = (unsigned long long int)GDT;
	GdtPointer.Limit = (sizeof(struct GDTEntry) * 3) - 1;

	__asm__ __volatile__("lgdt %0" :: "g" (GdtPointer));
}
