disk_load:
    pusha
    push dx
    mov ah, 0x02 ; read mode
    mov al, dh   ; read how many sectors
    mov cl, 0x02 ; start from
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0

    int 0x13      ; yell at bios to do something
    jc disk_error ; check for error

    pop dx     ; load sector amount
    cmp al, dh ; check if they were read
    jne read_error
    popa
    ret

disk_error:
    jmp loop_error

read_error:
    jmp loop_error
    
loop_error:
    jmp $