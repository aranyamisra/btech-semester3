%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    arr dw 0010h, 0008h, 0002h, 0005h, 0001h
    msg db "Sorted array: "
    msglen equ $-msg

section .bss
    temp    resb 1
    arrptr  resq 1
    count   resq 1
    curword resw 1

section .text
    global _start

_start:
    mov bx, 4                  ; n - 1 passes

outer:
    mov rsi, arr
    mov cx, 4                  ; n - 1 comparisons

inner:
    mov ax, [rsi]              ; current WORD
    mov dx, [rsi+2]            ; next WORD

    cmp ax, dx
    jbe noswap                 ; skip if already in order

    xchg ax, dx                ; swap
    mov [rsi], ax
    mov [rsi+2], dx

noswap:
    add rsi, 2                 ; move to next WORD
    dec cx
    jnz inner

    dec bx
    jnz outer

    ; print message
    rw 1, 1, msg, msglen

    ; initialize printing
    mov qword [arrptr], arr
    mov qword [count], 5

print_array:
    mov rsi, [arrptr]
    mov ax, [rsi]
    mov [curword], ax

    mov bp, 4                  ; 4 hexadecimal digits for WORD

print_hex:
    mov ax, [curword]
    rol ax, 4
    mov [curword], ax

    and al, 0Fh

    cmp al, 9
    jbe digit

    add al, 07h                ; A-F

digit:
    add al, 30h                ; convert to ASCII
    mov [temp], al

    rw 1, 1, temp, 1

    dec bp
    jnz print_hex

    ; print space
    mov byte [temp], ' '
    rw 1, 1, temp, 1

    ; move to next WORD
    mov rsi, [arrptr]
    add rsi, 2
    mov [arrptr], rsi

    mov rax, [count]
    dec rax
    mov [count], rax

    jnz print_array

    ; exit
    rw 60, 0, 0, 0