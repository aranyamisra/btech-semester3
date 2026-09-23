%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    msggdt db "Global Descriptor Table Register:", 10
    msggdtl equ $-msggdt

    base db "Base address: "
    basel equ $-base

    offset db 10, "Limit: "
    offsetl equ $-offset

    newl db 10

section .bss
    g resb 10

    temp64 resq 1
    temp16 resw 1
    asc resb 1

section .text
    global _start

_start:

    rw 1, 1, msggdt, msggdtl
    rw 1, 1, base, basel

    sgdt [g]

    mov rax, [g]             ; GDTR base
    call display64

    rw 1, 1, offset, offsetl

    mov ax, [g + 8]         ; GDTR limit
    call display16

    rw 1, 1, newl, 1

    rw 60, 0, 0, 0


display64:
        mov bp, 16
    up:
        rol rax, 4
        mov [temp64], rax
        and al, 0Fh
        cmp al, 09h
        jbe down
        add al, 07h
    
    down:
        add al, 30h
        mov [asc], al
        rw 1, 1, asc, 1
        mov rax, [temp64]
        dec bp
        jnz up
    ret


display16:
        mov bp, 4
    
    up2:
        rol ax, 4
        mov [temp16], ax
        and al, 0Fh
        cmp al, 09h
        jbe down2
        add al, 07h
    
    down2:
        add al, 30h
        mov [asc], al
        rw 1, 1, asc, 1
        mov ax, [temp16]
    
        dec bp
        jnz up2
    
        ret