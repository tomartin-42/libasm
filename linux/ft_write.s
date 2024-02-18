;ft__write
section .data

section .bss

section .text
global  ft_write

ft_write:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rax, 1; syscall to write
	syscall
	cmp rax, 0
	jl  error

error:
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
