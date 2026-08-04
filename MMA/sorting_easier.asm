%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    arr db 10h, 08h, 02h, 05h, 01h
    msg db "Sorted array: "
    msglen equ $-msg

section .bss
    temp  resb 1
    store resq 1

section .text
    global _start

_start:
    mov bx, 4                  ; n-1 passes

outer:
    mov rsi, arr
    mov cx, 4                  ; n-1 comparisons

    inner:
        mov al, [rsi]
        mov dl, [rsi+1]
        cmp al, dl
        jbe noswap
    
        xchg al, dl
        mov [rsi], al
        mov [rsi+1], dl
    
        noswap:
            inc rsi
            dec cx
            jnz inner
        
            dec bx
            jnz outer
        
            ; Print message
            rw 1, 1, msg, msglen
        
; Print sorted array
mov rsi, arr
mov r8, 5                  ; number of elements

print_array:
    mov al, [rsi]
    mov bp, 2

    print_hex:
        rol al, 4
        mov bl, al                 ; save rotated value
    
        and al, 0Fh
        cmp al, 9
        jbe digit
        add al, 07h
    
        digit:
            add al, 30h
            mov [temp], al
        
            mov [store], rsi           ; save array pointer
            rw 1, 1, temp, 1
            mov rsi, [store]           ; restore array pointer
        
            mov al, bl                 ; restore rotated byte
            dec bp
            jnz print_hex
        
            ; print space
            mov byte [temp], ' '
            mov [store], rsi
            rw 1, 1, temp, 1
            mov rsi, [store]
        
            inc rsi
            dec r8
            jnz print_array

rw 60, 0, 0, 0