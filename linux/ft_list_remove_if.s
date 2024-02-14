	;       RDI    lista
	;       RSI    data_to_delete
	;       RDX    function cmp
	;       RCX    free
	section .data
	struct_next equ 8

	section .text
	global  ft_list_remove_if
	extern  free

ft_list_remove_if:
	push rbp
	mov  rbp, rsp
	push rbx
	push r12
	push r13
	cmp  rdi, 0x0
	je   end

first_node_loop:
	mov  r8, [rdi]; begin_node
	cmp  r8, 0x0
	je   end
	mov  rbx, [r8 + struct_next]; next_node
	cmp  qword [r8], 0x0
	je   end
	push rdi
	push rsi
	mov  rdi, [r8]
	call rdx
	pop  rsi
	pop  rdi
	cmp  rax, 0x0
	je   remove

other_node_loop:
	cmp  qword rbx, 0x0
	je   end
	push rdi
	push rsi
	mov  rdi, [rbx]
	call rdx
	pop  rsi
	pop  rdi
	cmp  rax, 0x0
	je   remove_other
	mov  r8, [r8 + struct_next]
	mov  rbx, [r8 + struct_next]
	jmp  other_node_loop

;remove_first_node:
	; push rdi
	; push rsi
	; mov  r13, rcx; save free function
	; mov  r12, [r8]; node->data
	; mov  rdi, r8
	; call free; free node with free
	; mov  rdi, r12
	; call r13; free node->data with function
	; pop  rsi
	; pop  rdi
	; mov  [rdi], rbx
	; jmp  first_node_loop

end:
	pop r13
	pop r12
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

remove:
	push rdi
	push rsi
	push rbx
	push rdx
	push rcx
	mov  r12, [r8]
	mov  rdi, r8
	call rcx
	pop  rcx
	mov  rdi, r12
	push rcx
	call free
	pop  rcx
	pop  rdx
	pop  rbx
	pop  rsi
	pop  rdi
	mov  [rdi], rbx
	jmp  first_node_loop

remove_other:
	push rdi
	push rsi
	push rbx
	push rdx
	mov  r10, [rbx + struct_next]; save next-node
	mov  r12, [rbx]
	mov  rdi, rbx
	push r10
	push r8
	push rcx
	call rcx
	pop  rcx
	pop  r8
	pop  r10
	mov  rdi, r12
	push r10
	push r8
	push rcx
	call free
	pop  rcx
	pop  r8
	pop  r10
	pop  rdx
	pop  rbx
	pop  rsi
	pop  rdi
	mov  [r8 + struct_next], r10
	mov  rbx, r10
	jmp  other_node_loop
