%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
    num_arr db 12h, 72h, 26h, 07h, 51h

    msg db "Sum of elements in the array = "
    msglen equ $-msg
    
section .bss
    result resw 1                          ; Stores the final 16-bit sum
    temp   resb 1                         ; Stores one ASCII character for printing

section .text
    global _start

_start:
    mov rsi, num_arr      	; Point RSI to the beginning of the array
    mov ax, 00h           	; Clear AX (accumulator for sum)
    mov bx, 0h            	; Clear BX
    mov cx, 5             	; Number of array elements

up2:
    mov bl, byte [rsi]    	; Load current array element into BL
    add ax, bx            	; Add BX to AX
    jnc skip              		; If no carry, skip the next instruction
    inc ah                		; Increment AH if Carry Flag is set

skip:
    inc rsi               	; Move to the next array element
    dec cx                	; Decrement loop counter
    jnz up2               	; Repeat until all elements are processed

    mov word [result], ax 	; Store the final sum

    rw 1, 1, msg, msglen  	; Print the message

    mov ax, word [result] 	; Load the sum into AX for hexadecimal display
    mov bp, 4             	; Four hexadecimal digits to print

up:
    rol ax, 4             	; Rotate left by 4 bits to bring next hex digit to AL
    mov bx, ax            ; Save rotated value in BX
    and ax, 0Fh           ; Mask upper bits, keep only the lower nibble
    cmp al, 09             ; Check if digit is 0–9
    jbe down              	; If yes, skip alphabet conversion
    add al, 07h            ; Convert 0Ah–0Fh to A–F

down:
    add al, 30h           		; Convert hexadecimal digit to ASCII
    mov byte [temp], al   	; Store ASCII character
    rw 1, 1, temp, 1      	; Print one character
    mov ax, bx            	; Restore AX for the next rotation
    dec bp                		; One digit printed
    jnz up                		; Print remaining digits

    rw 60, 0, 0, 0 
