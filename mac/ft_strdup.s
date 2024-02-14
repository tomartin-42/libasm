;ft__strdup.s
section .data

section .bss

section .text
global  ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc

ft_strdup:
	;    Prolog
	push rbp
	mov  rbp, rsp

	xor  rax, rax
	push rdi
	call ft_strlen
	inc  rax
	mov  rdi, rax
	call malloc
	cmp  rax, 0
	je   end_fail
	pop  rsi
	mov  rdi, rax
	call ft_strcpy
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
