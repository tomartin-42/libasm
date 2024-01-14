;ft__strdup.s
section .data

section .bss

section .text
global  ft__strdup

extern ft__strlen
extern ft__strcpy
extern malloc

ft__strdup:
	xor  rax, rax
	push rdi
	call ft__strlen
	inc  rax
	;mov rdi, rax
	mov  rdi, 500
	call malloc

	ret
