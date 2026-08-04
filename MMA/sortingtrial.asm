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
    temp resb 1
    temp1 resb 1

section .text
    global _start

_start:
    mov bx, 4              ; n - 1 passes

outer:
    mov rsi, arr
    mov cx, 4              ; n - 1 comparisons

inner:
    mov al, [rsi]          ; current element
    mov dl, [rsi+1]        ; next element

    cmp al, dl             ; compare adjacent elements
    jbe noswap             ; skip if already in order

    xchg al, dl            ; swap
    mov [rsi], al
    mov [rsi+1], dl

noswap:
    inc rsi                ; move to next pair
    dec cx                 ; one comparison completed
    jnz inner              ; continue inner loop

    dec bx                 ; one pass completed
    jnz outer              ; repeat remaining passes

    ; print the message
    rw 1, 1, msg, msglen

    ; print the sorted array
    mov rsi, arr
    mov r8, 5              ; no. of elements

print_array:
    mov al, [rsi]          ; load one array element
    mov bp, 2              ; 2 hex digits to print

print_hex:
    rol al, 4                  ; bring next nibble to lower 4 bits
    mov [temp1], al            ; save rotated value
    and al, 0Fh

    cmp al, 9
    jbe digit
    add al, 07h                ; A-F

digit:
    add al, 30h                ; convert to ASCII
    mov [temp], al
    rw 1, 1, temp, 1           ; print one character

    mov al, [temp1]            ; restore AL
    dec bp
    jnz print_hex

    ; print a space after each element
    mov byte [temp], ' '
    rw 1, 1, temp, 1

    inc rsi                ; next array element
    dec r8
    jnz print_array

    rw 60, 0, 0, 0