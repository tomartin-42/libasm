;ft__write
section .data

section .bss

section .text
global  _ft_write
extern  ___error

_ft_write:
	;    Prolog
	push rbp
	mov  rbp, rsp
	xor rax, rax

	mov rax, 0x2000004; syscall to write
	syscall
	cmp rax, 0
	jl  fail
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret

fail:
	mov rdi, rax
	call ___error	
	mov [rax], rdx
	mov rax, -1
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
