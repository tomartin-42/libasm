;ft__strcmp.s
section .data

section .bss

section .text
global  _ft_strcmp

_ft_strcmp:
	;    Prolog
	push rbp
	mov  rbp, rsp

	xor rax, rax

loop:
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, bl; Check if equal
	jl  low
	jg  higth
	xor rax, rax
	cmp byte [rdi], 0
	je  end
	cmp byte [rsi], 0
	je  end
	inc rdi
	inc rsi
	jmp loop

low:
	mov rax, -1
	jmp end

higth:
	mov rax, 1
	jmp end

end:
	mov rdi, 0
	;   Epilog
	mov rsp, rbp
	pop rbp

	ret
