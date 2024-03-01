;ft__strdup.s
section .data

section .bss

section .text
global  _ft_strdup

extern _ft_strlen
extern _ft_strcpy
extern _malloc

_ft_strdup:
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

	ret

end_fail:
	xor rax, rax
	mov rdi, 0

	ret
