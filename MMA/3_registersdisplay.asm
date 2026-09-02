%macro rw 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    syscall
%endmacro

section .data
	msggdt db "Global Descriptor Table Register: "
	msggdtl equ $-msggdt
	
	msgldt db "Local Descriptor Table Register: "
	msgldtl equ $-msgldt
	
	msgidt db "Interrupt Descriptor Table Register: "
	msgidtl equ $-msgidt
	
	msgtr db "Task Register: "
	msgtrl equ $-msgtr
	
	msgmsw db "Machine Status Word: "
	msgmswl equ $-msgmsw
	
	baseadd db 10, "Base Address: "
	baseaddl equ $-baseadd
	
	offset db 10, "Offset: "
	offsetl equ $-offset
	
	newl db 0Ah

section .bss
	g resq 1
	glim resw 1
	
	ii resq 1
	ilim resw 1
	
	l resw 1
	llim resw 1
	
	t resw 1
	tlim resw 1
	
	m resw 1
	mlim resw 1
	
	temp64 resq 1
	temp16 resw 1
	asc resb 1
	
section .text
    global _start

_start:
	; GDTR
	rw 1, 1, msggdt, msggdtl
	rw 1, 1, baseadd, baseaddl	; base address = 8 bytes (64 bits)
	
	mov rsi, g
	sgdt [rsi]		; stores contents of gdtr in rsi(64 bits = 8 bytes) - in protected: 8+2 (base + limit) = 10 bytes
	mov rax, [rsi]
	call display64
	
	rw 1, 1, offset, offsetl	; offset limit = 2 bytes (16 bits)
	
	mov rsi, glim
	mov ax, [rsi]
	call display16
	
	rw 1, 1, newl, 1
	rw 1, 1, newl, 1
	
	; IDTR
	rw 1, 1, msgidt, msgidtl
	rw 1, 1, baseadd, baseaddl	
	
	mov rsi, ii
	sidt [rsi]	
	mov rax, [rsi]
	call display64
	
	rw 1, 1, offset, offsetl
	
	mov rsi, ilim
	mov ax, [rsi]
	call display16
	
	rw 1, 1, newl, 1
	rw 1, 1, newl, 1
	
	; LDTR
	rw 1, 1, msgldt, msgldtl
	rw 1, 1, baseadd, baseaddl	
	
	mov rsi, l
	sldt [rsi]	
	mov rax, [rsi]
	call display64
	
	rw 1, 1, newl, 1
	rw 1, 1, newl, 1
	
	; TR
	rw 1, 1, msgtr, msgtrl
	rw 1, 1, baseadd, baseaddl	
	
	mov rsi, t
	str [rsi]	
	mov rax, [rsi]
	call display64
	
	rw 1, 1, newl, 1
	rw 1, 1, newl, 1
	
	; MSW
	rw 1, 1, msgmsw, msgmswl
	rw 1, 1, baseadd, baseaddl	
	
	mov rsi, m
	smsw [rsi]	
	mov rax, [rsi]
	call display64
	
	rw 1, 1, newl, 1
	
	rw 60, 0, 0, 0
	
display16:
	mov bp, 4
	up:
		rol ax, 4
		mov [temp16], ax
		and ax, 0Fh
		cmp al, 09
		jbe down
		add al, 07h
		
	down:
		add al, 30h
		mov [asc], al
		rw 1, 1, asc, 1
		mov ax, [temp16]
		dec bp
		jnz up
	ret

display64:
	mov bp, 16
	up2:
		rol rax, 4
		mov [temp64], rax
		and rax, 0Fh
		cmp al, 09
		jbe down2
		add al, 07h
		
	down2:
		add al, 30h
		mov [asc], al
		rw 1, 1, asc, 1
		mov rax, [temp64]
		dec bp
		jnz up2
	ret
