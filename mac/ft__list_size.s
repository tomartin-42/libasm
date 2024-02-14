section .data

section .bss

section .text
global  ft__list_size

ft__list_size:
	;    Prolog
	push rbp
	mov  rbp, rsp
	push rdi

	xor rax, rax

loop:
	cmp qword rdi, 0
	je  end
	mov rdi, [rdi + 8]
	inc rax
	jmp loop

end:
	pop rdi
	mov rsp, rbp
	pop rbp
	ret
