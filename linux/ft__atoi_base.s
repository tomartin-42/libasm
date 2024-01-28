section .data
value   dd 0
res     dd 0

section .bss

section .text
global  ft__atoi_base

extern ft__strlen

ft__atoi_base:
	;    Prolog
	push rbp
	mov  rbp, rsp

	push rdi
	push rsi

	mov  rdi, rsi
	check_base_leng: ; check base leng
	call ft__strlen
	cmp  rax, 2
	jl   end_fail
	mov  rdx, rax; save base leng

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
	mov  al, [rdi + rcx]
	cmp  al, ' '
	je   increment
	cmp  al, '\t'
	je   increment
	cmp  al, '\r'
	je   increment
	cmp  al, '\n'
	je   increment
	cmp  al, '\v'
	je   increment
	cmp  al, '\f'
	je   increment
	cmp  al, 0
	je   return
	cmp  al, byte '-'
	je   mul_sig
	cmp  al, byte '+'
	call .get_char
	je   increment
	jmp  increment
	jmp loop

.get_char:
	xor r9, r9
	cmp byte [rsi + r9], 0
	je  increment
	cmp [rsi + r9], al
	je  .add_num
	inc r9
	jmp .get_char
	ret

.add_num:
	mov  r12, [res]
	imul r12, rdx
	add  r12, r9
	mov  [res], r12
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
	imul rbx, rbx, -1
	call .inc
	ret

.inc:
	inc rcx
	ret

end_fail:
	pop rsi
	pop rdi
	xor rax, rax
	mov rax, 42
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret

return:
	;   Epilog
	mov rsp, rbp
	pop rbp

	mov rax, [res]; to test
	ret
