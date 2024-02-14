section .data

section .bss

section .text
global  ft_atoi_base

ft_atoi_base:
	;    Prolog
	push rbp
	mov  rbp, rsp
	push r12

	xor  r9, r9; base_length
	xor  rax, rax; result
	mov  rcx, 1; sign
	;r12 conter

base_loop:
	cmp byte [rsi, r9], 0
	je  base_end
	mov r8, r9
	jmp check_dup_base

check_dup_base:
	inc r8
	mov r12, [rsi + r8]
	cmp [rsi + r9], r12b
	je  end_fail
	cmp r12b, 0
	je  check_base_chars
	jmp check_dup_base

check_base_chars:
	cmp byte [rsi + r9], 32; ' '
	je  end_fail
	cmp byte [rsi + r9], 43; '+'
	je  end_fail
	cmp byte [rsi + r9], 45; '-'
	je  end_fail
	cmp byte [rsi + r9], 9; '\t'
	je  end_fail
	cmp byte [rsi + r9], 10; '\n'
	je  end_fail
	cmp byte [rsi + r9], 13; '\r'
	je  end_fail
	cmp byte [rsi + r9], 11; '\v'
	je  end_fail
	cmp byte [rsi + r9], 12; '\f'
	je  end_fail
	inc r9
	jmp base_loop

base_end:
	cmp r9, 2
	jl  end_fail
	mov r12, -1

inc:
	inc r12

atoi_loop:
	cmp byte [rdi + r12], 32; ' '
	je  inc
	cmp byte [rdi + r12], 9; '\t'
	je  inc
	cmp byte [rdi + r12], 10; '\n'
	je  inc
	cmp byte [rdi + r12], 13; '\r'
	je  inc
	cmp byte [rdi + r12], 11; '\v'
	je  inc
	cmp byte [rdi + r12], 12; '\f'
	je  inc
	cmp byte [rdi + r12], 43; '+'
	je  inc
	cmp byte [rdi + r12], 45; '-'
	je  sing
	cmp byte [rdi + r12], 0
	je  set_rax
	xor r10, r10
	jmp add_num

sing:
	neg rcx
	jmp inc

end_fail:
	pop r12
	mov rsp, rbp
	pop rbp
	ret

base_inc:
	inc r10

add_num:
	mov r8b, byte [rsi + r10]
	cmp r8b, 0
	je  set_rax
	cmp r8b, byte [rdi + r12]
	jne base_inc
	mul r9
	add rax, r10
	xor r10, r10
	inc r12
	jmp add_num

set_rax:
	cmp rcx, 1
	je  return
	neg rax

return:
	pop r12
	mov rsp, rbp
	pop rbp
	ret
