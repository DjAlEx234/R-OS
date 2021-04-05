PREFIX=~/opt/cross/bin/i686-elf
FLAGS=-m32 -ffreestanding -std=gnu99 -O2 -Wall -Wextra
INC="Headers"
QEMU=-m 2G -serial file:out.log

all: run

build: run clean

text.o: InputOutput/text.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

inout.o: InputOutput/inoutb.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

vga.o: InputOutput/vga.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

serial.o: InputOutput/serial.c
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

mouse.o: Devices/mouse.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

keyboard.o: Devices/keybd.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

terminal.o: UI/terminal.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

cmd.o: UI/cmd.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

interface.o: UI/interface.c
	$(PREFIX)-gcc $(FLAGS) -c $< -o $@ -I$(INC)

intasm.o: Interrupt/int.asm
	nasm $< -felf32 -o $@

run: grub

boot.o: GRUB/grub.asm
	nasm $< -felf32 -o $@

grub-kernel.bin: boot.o kernel.o serial.o text.o intasm.o intc.o inout.o string.o cpuid.o keyboard.o terminal.o cmd.o vga.o interface.o mouse.o
	$(PREFIX)-gcc -T GRUB/linker.ld -o $@ -I$(INC) -ffreestanding -O2 -nostdlib $^ -lgcc

qemu-kernel: grub-kernel.bin
	qemu-system-i386 -kernel $< $(QEMU)
	make clean

R-OS.iso: grub-kernel.bin
	mkdir -p GRUB/iso/boot/grub
	cp $< GRUB/iso/boot/kernel.bin
	cp GRUB/grub.cfg GRUB/iso/boot/grub/grub.cfg
	grub-mkrescue -o R-OS.iso GRUB/iso
	rm -r GRUB/iso
	rm /media/sf_vm/R-OS.iso
	cp R-OS.iso /media/sf_vm/R-OS.iso
	qemu-system-i386 -cdrom R-OS.iso $(QEMU)
	make clean
	rm R-OS.iso

grub: R-OS.iso

clean:
	$(RM) *.bin *.o *.log