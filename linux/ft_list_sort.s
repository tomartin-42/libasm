	;R12    loop_start_node
	;R13    current_node
	;RAX    aux
	;[RBP   - 8]  external_function_cmp
	section .data
	struct_next equ 8

	section .text
	global  ft_list_sort

ft_list_sort:
	push rbp
	mov  rbp, rsp
	push rsi
	push r12
	push r13

	cmp qword [rdi], 0x0; 0 nodes
	je  end
	mov r12, [rdi]; strat loop node
	cmp qword [r12 + struct_next], 0x0; 1 node
	je  end
	mov r13, [r12 + struct_next]

init_loop:
	cmp r13, 0x0; end
	je  increment

cmp:
	mov  rdi, r12
	mov  rdi, [rdi]
	mov  rsi, r13
	mov  rsi, [rsi]
	mov  rax, [rbp - 8]; cmp function
	call rax
	cmp  rax, 0x1
	je   swap
	mov  rcx, [r13 + struct_next]; next
	mov  r13, rcx
	jmp  init_loop

end:
	pop r13
	pop r12
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

increment:
	mov r12, [r12 + struct_next]
	cmp qword r12, 0x0; finish
	je  end
	mov r13, [r12 + struct_next]
	jmp init_loop

swap:
	mov rcx, [r12]
	mov rdx, [r13]
	mov [r12], rdx
	mov [r13], rcx
	mov rcx, [r13 + struct_next]; next
	mov r13, rcx
	jmp init_loop
