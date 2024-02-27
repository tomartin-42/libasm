ift__read
section .data

section .bss

section .text
global  ft_read

ft_read:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rax, 0; syscall to read
	syscall
	cmp rax, 0
	jl  error
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret

error:
	;   Epilog
	mov rax, -1
	mov rsp, rbp
	pop rbp

	ret
