#include "BluuUEFI/EFI_SYSTEM_TABLE.h"
#include "BluuUEFI/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include "KernelStartupInfo.h"

extern void KernelMain(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* ST)
{
	EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP;
	EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	EFI_STATUS stat = ST->BootServices->LocateProtocol(&guid, 0, (void**)&GOP);

	CHAR16 str[] = { stat + 48, L'\r',L'\n',L'\0'};
	ST->ConOut->OutputString(ST->ConOut, str);

	KernelMain(GOP);

	return EFI_SUCCESS;
}