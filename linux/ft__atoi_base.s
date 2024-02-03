section .data

section .bss

section .text
global  ft__atoi_base

ft__atoi_base:
	;    Prolog
	push rbp
	mov  rbp, rsp
	push r12

	xor r9, r9; base_length
	xor rax, rax; result

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
	mov rax, 100000
	pop r12
	mov rsp, rbp
	pop rbp
	ret

end_fail:
	pop r12
	mov rsp, rbp
	pop rbp
	ret
