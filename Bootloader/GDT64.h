#pragma once

struct GDTEntry 
{
	unsigned int LimitLow;
	unsigned int BaseLow;
	unsigned char BaseMiddle;
	unsigned char Access;
	unsigned char Granularity;
	unsigned char BaseHigh;
};

struct GDTPointer
{
	unsigned int Limit;
	unsigned long long int Base;
};

static struct GDTEntry GDT[3];

void LoadGDT();