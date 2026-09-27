; size_t ft_strlen(const char *s);

section .text
global ft_strlen

ft_strlen:
	mov rcx, rdi		; Current character pointer
	xor rax, rax		; Length

.loop:
	cmp byte [rcx], 0	; End of string?
	je .done
	inc rcx
	inc rax
	jmp .loop

.done:
	ret
