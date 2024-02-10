section .text
global  ft__list_remove_if
extern  free

	;       RDI    lista
	;       RSI    data_to_delete
	;       RDX    function cmp
	;       RCX    free
	section .data
	struct_next equ 8

	section .text
	global  ft__list_remove_if
	extern  free

ft__list_remove_if:
	push rbp
	mov  rbp, rsp
	push rbx
	mov  r8, [rdi]; begin_node
	mov  rbx, [rdi + struct_next]; next_node

first_node_loop:
	cmp  qword [r8], 0x0
	je   end
	mov  rbx, [r8 + struct_next]
	push rdi
	push rsi
	mov  rdi, [r8]
	call rdx
	pop  rsi
	pop  rdi
	cmp  rax, 0x0
	je   remove_first_node
	mov  r8, rbx
	jmp  first_node_loop

remove_first_node:
	push rsi
	push rdx
	push rcx
	push rdi
	mov  rdi, r8
	call rcx
	pop  rdi
	pop  rcx
	pop  rdx
	pop  rsi
	mov  rdi, rbx
	mov  r8, [rdi]
	jmp  first_node_loop

end:
	pop  rbx
	mov  rsp, rbp
	push rbp
	ret
