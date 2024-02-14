section .data
struct_size equ 16; sizeof t_list

section .bss

section .text
global  ft__list_push_front
extern  malloc

ft__list_push_front:
	;    Prolog
	push rbp
	mov  rbp, rsp

	push rdi; save rdi - bengin_list
	push rsi; save rsi - data
	mov  rdi, struct_size
	call malloc
	cmp  rax, 0
	je   end
	pop  rsi
	pop  rdi
	mov  rdx, [rdi]
	mov  [rax + 8], rdx; *bengin = *new_node
	mov  [rax], rsi; seve data
	mov  [rdi], rax

end:
	mov rsp, rbp
	pop rbp
	ret
