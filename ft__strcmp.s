;ft__strcmp.s
section .data

section .bss

section .text
global  ft__strcmp

ft__strcmp:
	xor rax, rax

loop:
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, bl; Check if equal
	jl  low
	jg  higth
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
	ret
