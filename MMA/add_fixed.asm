%macro rw 4
 	mov rax, %1
 	mov rdi, %2
 	mov rsi, %3
 	mov rdx, %4
 	syscall
 %endmacro
 
 section .data 
	num1 db 5h
	num2 db 3h
	
	msg db "Sum = "
	msg_len equ $-msg
	

section .bss
	result resb 1

section .text
	global _start
	
_start:	
	mov al, [num1]
	add al, [num2]
	add al, 30h
	mov [result], al
	
	rw 1, 1, msg, msg_len
	rw 1, 1, result, 1
	
	
	rw 60, 0, 0, 0

