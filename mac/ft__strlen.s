;ft__strlen
section .data

section .bss

section .text
global  ft__strlen

ft__strlen:
	;    Prolog
	push rbp
	mov  rbp, rsp

	mov rbx, rdi
	xor rax, rax

loop:
	cmp byte [rbx], 0
	je  end
	inc rbx
	inc rax
	jmp loop

end:
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
