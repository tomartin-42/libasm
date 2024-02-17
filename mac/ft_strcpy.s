;ft__strcpy
section .data

section .bss

section .text
global  _ft_strcpy

_ft_strcpy:
	;    Prolog
	push rbp
	mov  rbp, rsp

	xor rax, rax
	mov rcx, rdi; Backup return value

loop:
	mov al, [rsi]
	mov [rdi], al
	cmp al, 0
	je  end
	inc rsi
	inc rdi
	jmp loop

end:
	mov rax, rcx
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
