[bits 16]
[org 0x7c00]

_start: 

KERNEL_POS equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call kernel_load
call switch_protected_mode

%include "MBR/fs.asm"
%include "MBR/gdt.asm"
%include "MBR/32bit.asm"

jmp $ ; quick loop :)

[bits 16]
kernel_load:
    cli
    mov bx, KERNEL_POS
    mov dh, 21
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
PROTECTION:
    call KERNEL_POS
    jmp $ ; why did kernel return?

BOOT_DRIVE db 0 ; boot drive storage

times 510 - ($-$$) db 0 ; fill 512 byte mbr

dw 0xaa55