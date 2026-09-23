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

    count_msg db "Number of occurrences: "
    count_len equ $-count_msg

section .bss
    count resq 1
    temp resb 1

section .text
    global _start

_start:
    mov qword [count], 0
    mov rsi, string1

next_pos:
    mov rdi, string2        ; reset substring pointer
    mov rcx, s2len          ; length of substring
    push rsi                ; save current position

    repe cmpsb              ; compare substring

    pop rsi                 ; restore current position

    je found                 ; match found

    inc rsi                  ; move to next position
    cmp byte [rsi], 0        ; check end of string1
    je check_result

    jmp next_pos


found:
    inc qword [count]        ; increase occurrence count

    inc rsi                  ; move to next position
    cmp byte [rsi], 0        ; check end of string1
    je check_result

    jmp next_pos


check_result:
    cmp qword [count], 0
    je notfound

    rw 1, 1, found_msg, found_len
    rw 1, 1, count_msg, count_len

    mov rax, [count]
    call display16

    jmp exit_program


notfound:
    rw 1, 1, notfound_msg, notfound_len
    jmp exit_program


display16:
    mov bp, 4
    print_loop:
        rol ax, 4
        mov bx, ax
        and al, 0Fh
        cmp al, 09h
        jbe digit
        add al, 07h
    
    digit:
        add al, 30h
        mov [temp], al
        rw 1, 1, temp, 1
        mov ax, bx
        dec bp
        jnz print_loop
    
    ret


exit_program:
    rw 60, 0, 0, 0