;ft__strlen
section .data
msg     db "hola", 0

section .bss

section .text
global  main

main:
	mov rbx, msg
	mov rcx, 0

while:
	cmp byte [rbx], 0
	je  end
	inc rbx
	inc rcx
	jmp while

end:
	mov rax, 1
	mov rdi, 1
	mov rsi, rcx
	syscall
	mov rax, 60
	mov rdi, 0
	syscall
