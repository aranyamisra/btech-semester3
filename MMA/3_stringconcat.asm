%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    m1 db 10, "Enter first string: "
    l1 equ $-m1

    m2 db 10, "Enter second string: "
    l2 equ $-m2

    m3 db 10, "Concatenated string: "
    l3 equ $-m3

section .bss
    string1 resb 25
    length1 resb 1
    
    string2 resb 25
    length2 resb 1

    string3 resb 50
    length3 resq 1

section .text
    global _start

_start:
    rw 1, 1, m1, l1
    rw 0, 0, string1, 25
    dec rax
    mov [length1], al

    rw 1, 1, m2, l2
    rw 0, 0, string2, 25
    dec rax
    mov [length2], al

    call concatenate

    rw 1, 1, m3, l3
    rw 1, 1, string3, [length3]

    rw 60, 0, 0, 0

    concatenate:
        mov rax, 0
        mov al, [length1]
        add al, [length2]
        mov [length3], rax
    
        mov rsi, string1
        mov rdi, string3
    
        copy_first:
            mov al, [rsi]
            mov [rdi], al
            inc rsi
            inc rdi
            dec byte [length1]
            jnz copy_first
        
            mov rsi, string2
        
        copy_second:
            mov al, [rsi]
            mov [rdi], al
            inc rsi
            inc rdi
            dec byte [length2]
            jnz copy_second
        
            ret