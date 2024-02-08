	;RDX    current_node
	;RBX    next_node
	;RCX    loop_start_node
	;R9     external_function_cmp
	section .data
	struct_size equ 16
	struct_next equ 8

	section .text
	global  ft__list_sort

ft__list_sort:
	push rbp
	mov  rbp, rsp
	push rbx
	push rsi
	push r14
	push r15

	mov r9, rsi
	cmp qword [rdi], 0x0; 0 nodes
	je  end
	mov rdx, [rdi]
	cmp qword [rdx + struct_next], 0x0; 1 node
	je  end

	mov rcx, [rdi]; strat loop node

loop:
	mov rbx, [rdx + struct_next]
	cmp qword [rcx + struct_next], 0x0; last node, end loop
	je  end
	mov rbx, [rcx + struct_next]
	cmp rbx, 0x0
	je  inc_start_node

	push rdi
	push rsi
	mov  r10, [rcx]
	mov  r11, [rbx]
	mov  rdi, [r10]
	mov  rsi, [r11]
	call r9
	pop  rsi
	pop  rdi
	cmp  rax, 0
	jg   swap

inc_start_node:
	mov rcx, [rcx + struct_next]
	jmp loop

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
	mov [rcx], r14
	mov [rbx], r15

	;   mov rcx, [rdi]
	;   mov rdx, [rcx]
	;   mov rax, [rcx + struct_next]
	;   mov r9, [rax]
	;   mov [rcx], r9
	;   mov [rax], rdx
	jmp loop
