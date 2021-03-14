LDFLAGS= -nostdlib -dll -shared --subsystem 10 -e UefiMain -o main.efi
CFLAGS= -fPIC -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args

SRC = BluuUEFI/UEFI.c Bootloader/GDT64.c Bootloader/LoaderMain.c Bootloader/Paging.c
OBJS = $(patsubst %.c, %.o, $(SRC))
CC = x86_64-w64-mingw32-gcc
LD = x86_64-w64-mingw32-ld
ASM = nasm

.PHONY : all

all : asm objs link clean run
asm:
	nasm Bootloader/Paging_Asm.asm -f elf64 -o Paging_Asm.o
objs : $(OBJS)
link:
	$(LD) $(LDFLAGS) $(OBJS) Paging_Asm.o

clean:
	rm -rf $(OBJS)
	rm -rf *.o
	rm -rf *.so
run:
	uefi-run main.efi
	rm -rf main.efi
