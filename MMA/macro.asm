section .data
	nameip db "Enter your name: "
	nameip_len equ $-nameip

	prnip db "Enter your prn: "
	prnip_len equ $-prnip

section .bss
    name resb 50
	prn resb 40

%macro rw 4
	mov rax, %1
	mov rdi, %2
	mov rsi, %3
	mov rdx, %4
	syscall
%endmacro

section .text
    global _start
    
_start:
	rw 1, 1, nameip, nameip_len
	rw 0, 0, name, 50

	rw 1, 1, prnip, prnip_len
	rw 0, 0, prn, 40

	rw 1, 1, name, 50
	rw 1, 1, prn, 40

	rw 60, 0, 0, 0