; void ft_list_remove_if(t_list **begin_list, void *data_ref,
;     int (*cmp)(), void (*free_fct)(void *));
; Parametros: rdi = &lista, rsi = referencia, rdx = comparador, rcx = liberador.
; Flujo: si cmp(data, referencia) == 0, desenlaza y libera el nodo; si no, avanza.

T_LIST_DATA equ 0
T_LIST_NEXT equ 8

section .text
global ft_list_remove_if

extern free

ft_list_remove_if:
	; Conserva el recorrido y los callbacks entre llamadas.
	push rbx			; Nodo actual
	push r12			; Enlace que apunta al nodo actual
	push r13			; Dato de referencia
	push r14			; Funcion de comparacion
	push r15			; Funcion para liberar los datos
					; Cinco pushes alinean la pila segun System V ABI

	test rdi, rdi ; Lista vacia
	jz .done 
	mov r12, rdi
	mov r13, rsi
	mov r14, rdx
	mov r15, rcx

.loop:
	; node = *link permite sustituir la cabeza y eliminar nodos consecutivos.
	mov rbx, [r12]
	test rbx, rbx 
	jz .done

	mov rdi, [rbx + T_LIST_DATA]	; Datos del nodo
	mov rsi, r13									; Dato de referencia
	call r14											; Compara los datos con la referencia
	test eax, eax
	jne .keep

	; Desenlaza la coincidencia antes de liberar sus datos y el nodo.
	mov rax, [rbx + T_LIST_NEXT]
	mov [r12], rax								; El enlace pasa a apuntar al siguiente nodo
	mov rdi, [rbx + T_LIST_DATA]
	call r15											; Libera los datos del nodo
	mov rdi, rbx  								; rbx -> nodo_actual
	call free wrt ..plt						; Libera la estructura del nodo
	jmp .loop											; Mantiene el enlace por si hay otra coincidencia

.keep:
	lea r12, [rbx + T_LIST_NEXT]	; Avanza el enlace a &node->next
	jmp .loop

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
