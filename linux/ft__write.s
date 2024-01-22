;ft__write
section .data

section .bss

section .text
global  ft__write

ft__write:
	mov rax, 1; syscall to write
	syscall
	cmp rax, 1
	jl  error

error:
	ret
