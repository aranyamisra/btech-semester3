%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    string1 db "abab", 0
    
    string2 db "ab"
    s2len equ $-string2
    
    found_msg db "Substring is present", 10
    found_len equ $-found_msg
    
    notfound_msg db "Substring is not present", 10
    notfound_len equ $-notfound_msg

section .text
    global _start

_start:

    mov rsi, string1        ; pointer to main string
    mov rdi, string2        ; pointer to substring

next_pos:

    mov rcx, s2len          ; length of substring (ab = 2)
    push rsi                ; save current position

    repe cmpsb              ; compare string1 and string2

    pop rsi                 ; restore current position

    je found                ; if all characters matched

    inc rsi                 ; move to next position
    cmp byte [rsi], 0       ; check end of string1
    je notfound

    jmp next_pos


found:
    rw 1, 1, found_msg, found_len
    jmp exit_program


notfound:
    rw 1, 1, notfound_msg, notfound_len

exit_program:
    rw 60, 0, 0, 0