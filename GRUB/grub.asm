MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM
section .bss
align 16
stack_bottom:
resb 16384
stack_top:
section .text
global _start:function (_start.end - _start)
_start:
        cli
        mov esp, stack_top
        extern multiboot_main
        push ebx; give me the multiboot ram ;)
        push eax; magic!!
        call multiboot_main   
.loop:	jmp $
.end: