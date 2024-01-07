;ft__strcmp.s
section .data

section .bss

section .text
global  ft__strcmp

ft__strcmp:
	xor rax, rax

loop:
	mov rax, [rdi]; Strin one
	mov rbx, [rsi]; String two
	sub rax, rbx
	cmp rax, 0; Check if equal
	je  end
	cmp byte [rdi], 0
	je  end
	cmp byte [rsi], 0
	je  end
	inc rdi
	inc rsi
	jmp loop

end:
	mov rdi, 0
	ret
