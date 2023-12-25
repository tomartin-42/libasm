;ft__strlen
section .data

section .bss

section .text
global  _ft__strlen

_ft__strlen:
	mov rbx, rdi
	mov rax, 0

while:
	cmp byte [rbx], 0
	je  end
	inc rbx
	inc rax
	jmp while

end:
	mov rdi, 0
	ret
