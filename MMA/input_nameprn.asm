section .data
	nameip db "Enter your name: "
	nameip_len equ $-nameip

	prnip db "Enter your prn: "
	prnip_len equ $-prnip

section .bss
    name resb 50
	prn resb 40

section .text
    global _start
    
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, nameip
	mov rdx, nameip_len
	syscall

	mov rax, 0
	mov rdi, 0
	mov rsi, name
	mov rdx, 50
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, prnip
	mov rdx, prnip_len
	syscall

	mov rax, 0
	mov rdi, 0
	mov rsi, prn
	mov rdx, 40
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, name
	mov rdx, 50
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, prn
	mov rdx, 40
	syscall

	mov rax, 60
	mov rdi, 0
	syscall