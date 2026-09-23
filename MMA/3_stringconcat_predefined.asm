%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    str1 db "MIT"
    l1 equ $-str1

    str2 db "WPU"
    l2 equ $-str2

    m3 db "Concatenated string: "
    l3 equ $-m3

section .bss
    string3 resb 50
    length3 resq 1

section .text
    global _start

_start:
    call concatenate

    rw 1, 1, m3, l3

    rw 1, 1, string3, length3

    rw 60, 0, 0, 0

concatenate:
    mov rax, l1
    add rax, l2
    mov [length3], rax

    ; Copy first string
    mov rsi, str1
    mov rdi, string3
    mov rcx, l1

    copy_first:
        mov al, [rsi]
        mov [rdi], al
        inc rsi
        inc rdi
        dec rcx
        jnz copy_first
    
        ; Copy second string
        mov rsi, str2
        mov rcx, l2
    
    copy_second:
        mov al, [rsi]
        mov [rdi], al
        inc rsi
        inc rdi
        dec rcx
        jnz copy_second
    
    ret