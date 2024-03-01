	; RDI    lista
	; RSI    data_to_delete
	; RDX    function cmp
	; RCX    free
	; param1 list [rbp - 8]
	; param2 void *data_ref [rbp - 16]
	; param3 int(*cmp)() [rbp - 24]
	; param4 void(*free_fct)(*void) [rbp - 32]

	section .data
	struct_next equ 8

	section .text
	global  _ft_list_remove_if
	extern  _free

_ft_list_remove_if:
	push rbp
	mov  rbp, rsp
	push rdi; save in stack param1
	push rsi; save in stack param2
	push rdx; save in stack param3
	push rcx; save in stack param4
	push rbx
	push r12
	push r13
	cmp  rdi, 0x0; list void
	je   end

first_node_loop:
	mov  r12, [rdi]; begin_node
	cmp  r12, 0x0; end_list
	je   end
	mov  r13, [r12 + struct_next]; next_node
	mov  rdi, [r12]
	mov  rsi, [rbp - 16]
	mov  rdx, [rbp - 24]
	call rdx; fct cmp
	cmp  rax, 0x0
	je   remove

other_node_loop:
	cmp  qword r13, 0x0
	je   end
	mov  rdi, [r13]
	mov  rsi, [rbp - 16]
	mov  rdx, [rbp - 24]
	call rdx; fct cmp
	cmp  rax, 0x0
	je   remove_other
	mov  r12, [r12 + struct_next]
	mov  r13, [r13 + struct_next]
	jmp  other_node_loop

end:
	pop r13
	pop r12
	pop rbx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	mov rsp, rbp
	pop rbp
	ret

remove:
	mov  rdi, [r12]
	mov  rcx, [rbp - 32]; fct free
	call rcx
	mov  rdi, r12
	call _free
	mov  rdi, [rbp - 8]
	mov  [rdi], r13
	jmp  first_node_loop

remove_other:
	mov  rbx, [r13 + struct_next]; save_next
	mov  rdi, [r13]
	mov  rcx, [rbp - 32]; fct free
	call rcx
	mov  rdi, r13
	call _free
	mov  [r12 + struct_next], rbx
	mov  r13, rbx
	jmp  other_node_loop
