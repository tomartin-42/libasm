section .data

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

	check_base_leng: ; check base leng
	mov   rdi, rsi
	call  ft__strlen
	cmp   rax, 2
	jl    end_fail
	;mov  rdi, rsi
	;call .check_chars_in_base
	;mov  rdi, rsi
	;call .check_repeated_char_in_base

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
	jmp return

;.check_repeated_char_in_base:
	; mov rax, [rdi]
	; cmp al, 0
	; je  return
	; inc rdi
	; mov rbx, rdi

;check_chars:
	; mov bl, [rdi]
	; cmp bl, 0
	; je  .check_repeated_char_in_base
	; cmp al, bl
	; je  end_fail
	; inc rbx
	; jmp check_chars

end_fail:
	pop rsi
	pop rdi
	xor rax, rax
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret

return:
	;   Epilog
	mov rsp, rbp
	pop rbp

	mov rax, 42; to test
	ret
