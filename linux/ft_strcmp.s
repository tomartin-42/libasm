; int ft_strcmp(const char *s1, const char *s2);

section .text
global ft_strcmp

ft_strcmp:
.loop:
	movzx eax, byte [rdi]	; Current unsigned byte from s1
	movzx ecx, byte [rsi]	; Current unsigned byte from s2
	cmp eax, ecx
	jne .different
	test al, al			; Both bytes are the null terminator
	je .done
	inc rdi
	inc rsi
	jmp .loop

.different:
	sub eax, ecx			; Return (unsigned char)s1 - (unsigned char)s2

.done:
	ret
