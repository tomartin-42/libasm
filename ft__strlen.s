;ft__strlen
section .data

section .bss

section .text
global  ft__strlen

ft__strlen:
	mov rbx, rdi
	xor rax, rax

while:
	cmp byte [rbx], 0
	je  end
	inc rbx
	inc rax
	jmp while

end:
	mov rdi, 0
	ret
