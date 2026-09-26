; ssize_t ft_read(int fd, void *buf, size_t count);

section .text
global ft_read

extern __errno_location

ft_read:
	mov eax, 0			; Linux syscall number: read
	syscall
	test rax, rax
	js .error
	ret

.error:
	neg rax							; Convert -errno to positive errno
	push rax						; Save errno and align stack per System V ABI
	call __errno_location wrt ..plt
	pop rcx							; Restore positive errno
	mov [rax], ecx			; errno is a 32-bit int
	mov rax, -1
	ret
