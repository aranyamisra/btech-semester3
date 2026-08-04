section .data
	ip db 10, "Enter a number: "
	ip_len equ $-ip

section .bss
    num resb 40

section .text
    global _start
    
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, ip
	mov rdx, ip_len
	syscall

	mov rax, 0
	mov rdi, 0
	mov rsi, num
	mov rdx, 40
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, num
	mov rdx, 40
	syscall

	mov rax, 60    
	mov rdi, 0
	syscall
