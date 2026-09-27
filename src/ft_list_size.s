; unsigned int ft_list_size(t_list *begin_list);
; t_list layout: data at offset 0, next at offset 8.

section .text
global  ft_list_size

ft_list_size:
	xor rax, rax					; Node count

.loop:
	cmp qword rdi, 0			; End of the list?
	je  .end
	mov rdi, [rdi + 8]		; Advance to the next node
	inc rax								; Count the current node
	jmp .loop

.end:
	ret
