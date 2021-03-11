#!/bin/bash
cd BluuUEFI
make
mv UEFI.o ../UEFI.o
cd ..

for f in *.c; do
	gcc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c -o ${f%.c}.o $f
done

cd Kernel

for f in *.c; do
	gcc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c -o ${f%.c}.o $f
done

for f in *.asm; do
	nasm -f elf64 $f -o ${f%.asm}.o
done

mv *.o ..

cd ..
cd KernelLib

for f in *.c; do
	gcc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c -o ${f%.c}.o $f
done

mv *.o ..
cd ..

ld -shared -Bsymbolic LoaderMain.o -e UefiMain Paging.o kmemory.o GDT64.o KernelMain.o -o main.so
objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 main.so main.efi

rm -rf *.o