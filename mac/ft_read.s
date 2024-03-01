;ft__read
section .data

section .bss

section .text
global  _ft_read
extern  ___error

_ft_read:
	;    Prolog
	push rbp
	mov  rbp, rsp
	xor  rax, rax

	mov rax, 0x2000003; syscall to read
	syscall
	jc  fail
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret

fail:
	mov  rdx, rax
	call ___error
	mov  [rax], rdx
	mov  rax, -1
	;    Epilog
	mov  rsp, rbp
	pop  rbp

	ret
