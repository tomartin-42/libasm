section .data
res     dq 0

section .bss

section .text
global  ft__atoi_base

extern ft__strlen

ft__atoi_base:
	;    Prolog
	push rbp
	mov  rbp, rsp
	push r12
	push rbx
	push r8
	push rdx
	push rdi
	push rsi

	xor r8, r8
	xor rax, rax
	check_base_leng: ; check base leng
	cmp byte [rsi + rax], 0
	je  end_base_leng
	inc rax
	jmp check_base_leng

end_base_leng:
	cmp rax, 2
	jl  end_fail
	mov rdx, rax; save base leng

	mov rdi, rsi
	check_chars_in_base: ; check incorrect chars in base
	xor rax, rax
	mov al, [rdi]
	cmp al, 32; comp space
	je  end_fail
	cmp al, 43; comp +
	je  end_fail
	cmp al, 45; comp -
	je  end_fail
	inc rdi
	cmp al, 0; end of string
	jne check_chars_in_base

	mov rdi, rsi
	check_repeated_char_in_base: ; check repeated char in base
	mov rax, [rdi]
	cmp al, 0
	je  calc_number
	inc rdi
	xor rcx, rcx

	check_chars: ; check chars in al - bl
	mov bl, [rdi + rcx]
	cmp bl, 0
	je  check_repeated_char_in_base
	cmp al, bl
	je  end_fail
	inc rcx
	jmp check_chars

calc_number:
	xor rcx, rcx
	pop rsi; restore to original value rsi "base"
	pop rdi; restore rdi original value rdi "str"
	mov rbx, 1

loop:
	xor  rax, rax
	xor  r8, r8
	mov  al, [rdi + rcx]
	cmp  al, ' '
	je   increment
	cmp  al, 9; '\t'
	je   increment
	cmp  al, 13; '\r'
	je   increment
	cmp  al, 10; '\n'
	je   increment
	cmp  al, 11; '\v'
	je   increment
	cmp  al, 12; '\f'
	je   increment
	cmp  al, 0
	je   return
	cmp  al, byte '-'
	je   mul_sig
	cmp  al, byte '+'
	je   increment
	call get_char
	;jmp loop

get_char:
	mov al, [rdi + rcx]
	cmp al, 0
	je  return
	cmp al, '-'
	je  return
	cmp al, '+'
	je  return
	cmp r8, rdx
	je  end_fail
	cmp byte [rsi + r8], 0
	je  .ret
	cmp [rsi + r8], al
	je  .add_num
	inc r8
	jmp get_char

.ret:
	ret

.add_num:
	mov  r12, [res]
	imul r12, rdx
	add  r12, r8
	mov  [res], r12
	call .internal_increment
	jmp  get_char

.internal_increment:
	xor r8, r8
	inc rcx
	ret

increment:
	call .inc
	jmp  loop

.inc:
	inc rcx
	ret

mul_sig:
	call .mul_sig
	jmp  loop

.mul_sig:
	cmp  rbx, -1
	je   end_fail
	imul rbx, rbx, -1
	call .inc
	ret

.inc:
	inc rcx
	ret

end_fail:
	xor rax, rax

	;   Epilog
	pop rsi
	pop rdi
	pop r8
	pop rbx
	pop r12
	mov rsp, rbp
	pop rbp

	ret

return:
	mov  rax, [res]
	imul rax, rbx
	;    Epilog
	pop  rsi
	pop  rdi
	pop  rdx
	pop  r8
	pop  rbx
	pop  r12
	mov  rsp, rbp
	pop  rbp

	ret
