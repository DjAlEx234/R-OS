[bits 16]
switch_protected_mode:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1 ; you are now in protection mode
    mov cr0, eax
    jmp CODE_SEG:init_protected

[bits 32]
init_protected:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000 ; stack 2 electric boogaloo
    mov esp, ebp
    call PROTECTION