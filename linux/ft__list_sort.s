section .data
struct_size equ 16
struct_next equ 8

section .text
global  ft__list_sort

ft__list_sort:
	push rbp
	mov  rbp, rsp
	push rdi

	mov rcx, [rdi]; begin->data
	mov rax, [rcx + 8]

	pop rdi
	mov rsp, rbp
	pop rbp
	ret
