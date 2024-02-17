;ft__write
section .data

section .bss

section .text
global  _ft_write

_ft_write:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rax, 1; syscall to write
	syscall
	cmp rax, 1
	jl  error

error:
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
