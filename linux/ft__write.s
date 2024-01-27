;ft__write
section .data

section .bss

section .text
global  ft__write

ft__write:
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
