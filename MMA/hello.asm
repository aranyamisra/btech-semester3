section .data
    hello db 10, "hello world, i'm aranya"
    hello_len equ $-hello
    ;initialised variables

section .bss
    ;uninitialised variables

section .text
    global _start
    
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, hello
	mov rdx, hello_len
	syscall

	mov rax, 60
	mov rdi, 0
	syscall