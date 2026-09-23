%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    text db "hey there. i am aranya."
    len equ $-text

    msg1 db "Number of words: "
    len1 equ $-msg1

    msg2 db 10, "Number of spaces: "
    len2 equ $-msg2

    msg3 db 10, "Number of sentences: "
    len3 equ $-msg3

section .bss
    spaces resq 1
    words resq 1
    sentences resq 1
    temp resb 1

section .text
    global _start

_start:
    mov rsi, text
    mov rcx, len

    mov qword [spaces], 0
    mov qword [sentences], 0

count_loop:
    mov al, [rsi]

    ; Check for space
    cmp al, ' '
    jne check_fullstop
    inc qword [spaces]
    jmp next_char

check_fullstop:
    ; Check for full stop
    cmp al, '.'
    jne next_char
    inc qword [sentences]

next_char:
    inc rsi
    dec rcx
    jnz count_loop

    ; Words = Spaces + 1
    mov rax, [spaces]
    inc rax
    mov [words], rax

    ; Print words
    rw 1, 1, msg1, len1
    mov ax, [words]
    mov bp, 4
    call print_hex

    ; Print spaces
    rw 1, 1, msg2, len2
    mov ax, [spaces]
    mov bp, 4
    call print_hex

    ; Print sentences
    rw 1, 1, msg3, len3
    mov ax, [sentences]
    mov bp, 4
    call print_hex

    ; Exit
    rw 60, 0, 0, 0


print_hex:
    rol ax, 4
    mov bx, ax
    and ax, 0Fh
    cmp al, 09h
    jbe digit
    add al, 07h

    digit:
        add al, 30h
        mov byte [temp], al
        rw 1, 1, temp, 1

        mov ax, bx
        dec bp
        jnz print_hex

    ret