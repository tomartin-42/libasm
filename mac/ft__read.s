;ft__read
section .data

section .bss

section .text
global  ft__read

ft__read:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rax, 0; syscall to read
	syscall
	cmp rax, 1
	jl  error

error:
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
