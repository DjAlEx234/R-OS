[bits 16]
[org 0x7c00]
_start:

xor ax, ax
mov ds, ax
cld

KERNEL_POS equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x7c00
mov sp, bp

mov si, msg
call bios_print

msg db 'cant find kernel!', 13, 10, 0

bios_print:
   lodsb
   or al, al  ;zero=end of str
   jz done    ;get out
   mov ah, 0x0E
   mov bh, 0
   int 0x10
   jmp bios_print

done:

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
    mov dh, 20 ; important value, number of 512 sectors to be read OF kernel
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
PROTECTION:
    call KERNEL_POS
    jmp $ ; why did kernel return?

BOOT_DRIVE db 0 ; boot drive storage

times 510 - ($-$$) db 0 ; fill 512 byte mbr

dw 0xAA55