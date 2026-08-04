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
	result resw 1
	temp resb 1
	temp1 resb 1
	
section .text
	global _start
	
_start:
	mov rsi, num_arr
	mov ax, 00h	; clear accumulator
	mov bx, 0h 
	mov cx, 5 	; counter
	
	up2: 
		mov bl, byte[rsi]	; moving first byte in bl
		add ax, bx	; addition operation
		jnc skip	; jump when not carry
		inc ah  	; ah contains carry
	
	skip: 
		inc rsi	; increment pointer
		dec cx 		; decrement pointer
		jnz up2		; jump when not zero
	
	mov word[result], ax

	rw 1, 1, msg, msglen
	
	mov ax, word[result]	; store word in accumulator
	mov bp, 4
	
	up:
		rol ax, 4
		mov bx, ax
		and ax, 0Fh
		cmp al, 09
		jbe down
		add al, 07h
		
	down:
		add al, 30h
		mov byte[temp], al
		rw 1, 1, temp, 1
		mov ax, bx
		dec bp
		jnz up
		
		rw 60, 0, 0, 0
