;ft__read
section .data

section .bss

section .text
global  ft__read

ft__read:
	mov rax, 0; syscall to read
	syscal
	cmp rax, 1
	jl  error

error:
	ret
