;ft__strlen
section .data
msg     db "hola", 0

section .bss

section .text
global  main

ft__strlen:
	mov rbx, msg
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
