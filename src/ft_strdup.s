; char *ft_strdup(const char *s);

section .text
global ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc

ft_strdup:
	push rdi			; Save source and align the stack per System V ABI

	call ft_strlen wrt ..plt
	lea rdi, [rax + 1]		; Length plus null terminator
	call malloc wrt ..plt

	test rax, rax
	jz .done			; malloc returned NULL

	mov rsi, [rsp]			; Original source
	mov rdi, rax			; Allocated destination
	call ft_strcpy wrt ..plt

.done:
	add rsp, 8			; Discard saved source
	ret
