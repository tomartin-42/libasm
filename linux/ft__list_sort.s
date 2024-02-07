section .data
struct_size equ 16
struct_next equ 8

section .text
global  ft__list_sort

ft__list_sort:
	push rbp
	mov  rbp, rsp
	push r9

	mov rcx, [rdi]
	mov rdx, [rcx]
	mov rax, [rcx + 8]
	mov r9, [rax]
	mov [rcx], r9
	mov [rax], rdx

	pop r9
	mov rsp, rbp
	pop rbp
	ret
