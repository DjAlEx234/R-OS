PREFIX=~/opt/cross/bin/i686-elf
FLAGS=-m32 -ffreestanding -std=gnu99 -O2 -Wall -Wextra
INC="Headers"

all: run

build: run clean

kernel.bin: kernel-entry.o kernel.o text.o intasm.o intc.o inout.o string.o cpuid.o keyboard.o
	$(PREFIX)-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: Kernel/kernel-entry.asm
	nasm $< -felf -o $@

text.o: InputOutput/text.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

inout.o: InputOutput/inoutb.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

intc.o: Interrupt/int.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

kernel.o: Kernel/kernel.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

cpuid.o: Kernel/cpuid.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC) -Wno-incompatible-pointer-types
	#oh god anything but the incompatible pointer type
string.o: Kernel/string.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

keyboard.o: Devices/keybd.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

intasm.o: Interrupt/int.asm
	nasm $< -felf32 -o $@

mbr.bin: MBR/mbr.asm
	nasm $< -f bin -o $@

os.img: mbr.bin kernel.bin
	cat $^ > $@

run: os.img
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy

clean:
	$(RM) *.bin *.o *.img