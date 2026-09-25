;ft__write
section .data
extern  __errno_location

section .bss

section .text
global  ft_write

ft_write:
	;    Prolog
	push rbp
	mov  rbp, rsp
	push rbx

	mov rax, 1; syscall to write
	syscall
	cmp rax, 0
	jl  error
	;   Epilog
	pop rbx
	mov rsp, rbp
	pop rbp

	ret

error:
	neg  rax
	mov  rbx, rax
	call __errno_location
	mov  [rax], rbx
	mov  rax, -1
	;    Epilog
	pop  rbx
	mov  rsp, rbp
	pop  rbp

	ret
