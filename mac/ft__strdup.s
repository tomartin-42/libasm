;ft__strdup.s
section .data

section .bss

section .text
global  ft__strdup

extern ft__strlen
extern ft__strcpy
extern malloc

ft__strdup:
	;    Prolog
	push rbp
	mov  rbp, rsp

	xor  rax, rax
	push rdi
	call ft__strlen
	inc  rax
	mov  rdi, rax
	call malloc
	cmp  rax, 0
	je   end_fail
	pop  rsi
	mov  rdi, rax
	call ft__strcpy
	;    Epilog
	mov  rsp, rbp
	pop  rbp

	ret

end_fail:
	pop r9
	xor rax, rax
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
