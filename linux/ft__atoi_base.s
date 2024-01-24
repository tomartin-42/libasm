section .data

section .bss

section .text
global  ft__atoi_base

extern ft__strlen

ft__atoi_base:
	push rdi
	push rsi
	mov  rdi, rsi
	jmp  .check_base_leng
	mov rdi, rsi
	jmp .check_chars_in_base
	mov rdi, rsi
	jmp check_repeated_char_in_base

.check_base_leng:
	call ft__strlen
	cmp  rax, 2
	jl   end_fail
	ret

.check_chars_in_base:
	xor rax, rax
	mov al, [rdi]
	cmp al, 0; end of string
	je  return
	cmp al, 32; comp space
	je  end_fail
	cmp al, 43; comp +
	je  end_fail
	cmp al, 45; comp -
	je  end_fail
	inc rdi
	jmp .check_chars_in_base
	ret

check_repeated_char_in_base:
	mov rax, [rdi]
	cmp al, 0
	je  return
	inc rdi
	mov rbx, rdi

check_chars:
	mov bl, [rdi]
	cmp bl, 0
	je  check_repeated_char_in_base
	cmp al, bl
	je  end_fail
	inc rbx
	jmp check_chars

end_fail:
	pop rsi
	pop rdi
	xor rax, rax
	ret

return:
	ret
