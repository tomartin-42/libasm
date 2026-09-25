;ft__strlen
section .data

section .bss

section .text
global  ft_strlen

ft_strlen:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rcx, rdi
	xor rax, rax

loop:
	cmp byte [rcx], 0
	je  end
	inc rcx
	inc rax
	jmp loop

end:
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
