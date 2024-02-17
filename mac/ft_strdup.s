;ft__strdup.s
section .data

section .bss

section .text
global  _ft_strdup

extern _ft_strlen
extern _ft_strcpy
extern _malloc

_ft_strdup:
	;    Prolog
	push rbp
	mov  rbp, rsp
	sub  rsp, 8 ;stack 16bytes align

	xor  rax, rax
	push rdi
	call _ft_strlen
	inc  rax
	mov  rdi, rax
	call _malloc
	cmp  rax, 0
	je   end_fail
	pop  rsi
	mov  rdi, rax
	call _ft_strcpy
	;    Epilog
	add rsp, 8
	mov  rsp, rbp
	pop  rbp

	ret

end_fail:
	pop r9
	add rsp, 8
	xor rax, rax
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
