section .data

section .bss

section .text
global  ft__atoi_base

extern ft__strlen

ft_atoi_base:
	push rdi
	push rsi
	mov  rdi, rsi
	call .check_base_leng
	call .check_chars_in_base

.check_base_leng:
	call ft__strlen
	cmp  rax, 2
	jl   end_fail

.check_chars_in_base:
	xor rax, rax
	mov al, [rdi]
	cmp al, 0; end of string
	je  return
	cmp al, 32; comp space
	je  end_fail
	cmp al, 42; comp +
	je  end_fail
	cmp al, 45; comp -
	je  end_fail
	inc rdi
	jmp .check_chars_in_base

end_fail:
	pop rsi
	pop rdi
	xor rax, rax
	ret

return:
	ret
