#include "KernelStartupInfo.h"

void KernelMain(EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP)
{
	if (GOP == 0) return;

	GOP->SetMode(GOP, 0);
	return;
};