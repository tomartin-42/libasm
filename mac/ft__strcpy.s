;ft__strcpy
section .data

section .bss

section .text
global  ft__strcpy

ft__strcpy:
	;    Prolog
	push rbp
	mov  rbp, rsp

	xor rax, rax
	mov rbx, rdi; Backup return value

loop:
	mov al, [rsi]
	mov [rdi], al
	cmp al, 0
	je  end
	inc rsi
	inc rdi
	jmp loop

end:
	mov rax, rbx
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
