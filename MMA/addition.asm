%macro rw 4
 	mov rax, %1
 	mov rdi, %2
 	mov rsi, %3
 	mov rdx, %4
 	syscall
 %endmacro
 
 section .data 
	num1ip db "Enter first number: "
	num1ip_len equ $-num1ip
	;fixed input -> num1 db 5h
	
	num2ip db "Enter second number: "
	num2ip_len equ $-num2ip
	
	msg db "Sum = "
	msg_len equ $-msg

section .bss
	num1 resb 50
	num2 resb 50
	result resb 50

section .text
	global _start
	
_start:
	rw 1, 1, num1ip, num1ip_len
	rw 0, 0, num1, 50
	
	rw 1, 1, num2ip, num2ip_len
	rw 0, 0, num2, 50
	
	mov al, [num1]
	add al, [num2]
	mov [result], al
	
	rw 1, 1, msg, msg_len
	rw 1, 1, result, 50
	
	rw 60, 0, 0, 0

