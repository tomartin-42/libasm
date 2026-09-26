; void ft_list_sort(t_list **begin_list, int (*cmp)());
; Sorts the list by swapping node data pointers.

T_LIST_NEXT equ 8

section .text
global ft_list_sort

ft_list_sort:
	push r12			; Current outer node
	push r13			; Current comparison node
	push r14			; Comparison callback
								; Three pushes align the stack

	test rdi, rdi
	jz .done
	mov r12, [rdi]		; First node
	mov r14, rsi			; Preserve cmp across callback calls

.outer_loop:
	test r12, r12
	jz .done
	mov r13, [r12 + T_LIST_NEXT]  ; Next node

.inner_loop:
	test r13, r13
	jz .next_outer

	mov rdi, [r12]			; current->data
	mov rsi, [r13]			; other->data
	call r14            ; cmp function

	test eax, eax			; cmp(current->data, other->data) > 0?
	jle .next_inner

	mov rax, [r12]
	mov rcx, [r13]
	mov [r12], rcx
	mov [r13], rax			; Swap data pointers

.next_inner:
	mov r13, [r13 + T_LIST_NEXT]
	jmp .inner_loop

.next_outer:
	mov r12, [r12 + T_LIST_NEXT]
	jmp .outer_loop

.done:
	pop r14
	pop r13
	pop r12
	ret
