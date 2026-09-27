; char *ft_strcpy(char *restrict dst, const char *restrict src);

section .text
global ft_strcpy

ft_strcpy:
	mov rcx, rdi		; Original destination pointer

.loop:
	mov al, [rsi]		; Read source byte
	mov [rdi], al		; Copy byte to destination
	test al, al		; Null terminator copied?
	jz .done
	inc rsi
	inc rdi
	jmp .loop

.done:
	mov rax, rcx		; Return original destination
	ret
