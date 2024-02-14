	;RDX    current_node
	;RBX    next_node
	;RCX    loop_start_node
	;R9     external_function_cmp
	section .data
	struct_next equ 8

	section .text
	global  ft_list_sort

ft_list_sort:
	push rbp
	mov  rbp, rsp
	push rbx
	push rsi
	push r14
	push r15

	mov r9, rsi
	cmp qword [rdi], 0x0; 0 nodes
	je  end
	mov rbx, [rdi]; strat loop node
	cmp qword [rbx + struct_next], 0x0; 1 node
	je  end

	mov rcx, rbx

loop:
	mov rcx, [rcx + struct_next]
	cmp rcx, 0x0
	je  inc_start_node

prepare_cmp:
	push rdi
	push rsi
	mov  rdi, [rbx]
	mov  rsi, [rcx]
	call r9
	pop  rsi
	pop  rdi
	cmp  rax, 0x1
	je   swap
	jmp  loop

end:
	pop r15
	pop r14
	pop rsi
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

swap:
	mov r14, [rcx]
	mov r15, [rbx]
	mov [rcx], r15
	mov [rbx], r14
	jmp loop

inc_start_node:
	mov rbx, [rbx + struct_next]
	cmp qword [rbx + struct_next], 0x0; last node, end loop
	je  end
	mov rcx, rbx
	jmp loop
