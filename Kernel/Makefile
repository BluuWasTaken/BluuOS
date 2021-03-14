CFLAGS= -I/BluuUEFI -m64 -mcmodel=medium -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args

SRC = $(wildcard *.c) $(wildcard "KernelLib"/*.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
CFLAGS=-fno-stack-protector -ffreestanding -nostdlib
objs : $(OBJS)

Compile:
