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
    temp    resb 1
    arrptr     resq 1       ; pointer into arr
    count   resq 1          ; elements remaining
    curbyte resb 1          ; current byte being printed

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
    ; NOTE: rax, rdi, rsi, rdx are all clobbered by every `rw` call, and
    ; `syscall` itself also clobbers rcx/r11. Memory locations aren't
    ; touched by any of that, so we keep loop state in .bss instead
    ; of in registers that don't survive a syscall.
    
    mov qword [arrptr], arr
    mov qword [count], 5

print_array:
    mov rsi, [arrptr]           ; load pointer from memory
    mov al, [rsi]             ; al = current array byte
    mov [curbyte], al         ; stash it in memory (survives rw calls)
    mov bp, 2                  ; 2 hex digits to print

print_hex:
    mov al, [curbyte]
    rol al, 4                  ; rotate the stashed copy
    mov [curbyte], al          ; write the rotated value straight back
    and al, 0Fh
    cmp al, 9
    jbe digit
    add al, 07h               ; A-F

digit:
    add al, 30h                ; convert to ASCII
    mov [temp], al
    rw 1, 1, temp, 1           ; print one character
    dec bp
    jnz print_hex
    
    ; print a space after each element
    mov byte [temp], ' '
    rw 1, 1, temp, 1
    
    mov rsi, [arrptr]
    inc rsi
    mov [arrptr], rsi              ; arrptr++
    mov rax, [count]
    dec rax
    mov [count], rax
    jnz print_array
    
    rw 60, 0, 0, 0