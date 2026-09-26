; int ft_atoi_base(char *str, char *base);
; Flujo: valida la base, salta espacios, procesa signos, convierte y aplica el signo.
; r8: longitud de base | r9/r10: busquedas auxiliares | r11: indice de str
; rax: resultado | rcx: signo | dl: caracter actual

section .text
global ft_atoi_base

ft_atoi_base:
	; Fase 1: valida la base mientras calcula su longitud en r8.
	; Cada caracter debe ser unico y no puede ser un signo ni un espacio.
	xor r8, r8			; Longitud de la base

.base_loop:
	mov al, [rsi + r8]
	test al, al
	jz .base_done
	cmp al, '+'
	je .invalid
	cmp al, '-'
	je .invalid
	cmp al, ' '
	je .invalid
	cmp al, 9
	jb .check_duplicates
	cmp al, 13
	jbe .invalid			; Reject '\t', '\n', '\v', '\f' and '\r'

.check_duplicates:
	; Recorre el resto de la base buscando otra aparicion del caracter actual.
	lea r9, [r8 + 1]

.duplicate_loop:
	mov dl, [rsi + r9]
	test dl, dl
	jz .next_base_char
	cmp al, dl
	je .invalid
	inc r9
	jmp .duplicate_loop

.next_base_char:
	inc r8
	jmp .base_loop

.base_done:
	cmp r8, 2
	jb .invalid				; Una base valida necesita al menos dos caracteres
	xor r11, r11			; Indice dentro de str

.skip_spaces:
	; Fase 2: salta los espacios iniciales. Una vez aparezca un signo,
	; los espacios dejan de estar permitidos y finalizaran la conversion.
	mov dl, [rdi + r11]
	cmp dl, ' '			; Comprueba el espacio normal (ASCII 32)
	je .next_space	; Si lo encuentra, avanza al siguiente caracter
	cmp dl, 9				; Inicio del rango de espacios ASCII 9-13
	jb .sign_start	; Un valor menor que 9 no es un espacio
	cmp dl, 13			; Final del rango de espacios ASCII 9-13
	jbe .next_space	; Si esta entre 9 y 13, tambien debe saltarse
	jmp .sign_start

.next_space:
	inc r11
	jmp .skip_spaces

.sign_start:
	mov ecx, 1			; Signo positivo por defecto

.sign_loop:
	; Fase 3: consume signos consecutivos. Cada '-' invierte el signo;
	; cada '+' simplemente avanza al siguiente caracter.
	mov dl, [rdi + r11]
	cmp dl, '+'
	je .next_sign
	cmp dl, '-'
	jne .convert_start
	neg rcx

.next_sign:
	inc r11
	jmp .sign_loop

.convert_start:
	xor eax, eax			; Resultado acumulado

.convert_loop:
	; Fase 4: busca el caracter actual de str dentro de la base.
	; Su posicion sera el valor numerico del digito.
	mov dl, [rdi + r11]
	test dl, dl
	jz .apply_sign
	xor r10, r10			; Digit value

.find_digit:
	cmp r10, r8
	je .apply_sign			; Un caracter ajeno a la base termina la conversion
	mov r9b, [rsi + r10]
	cmp dl, r9b
	je .accumulate
	inc r10
	jmp .find_digit

.accumulate:
	; resultado = resultado * longitud_base + valor_digito
	imul rax, r8
	add rax, r10
	inc r11
	jmp .convert_loop

.apply_sign:
	; Fase 5: aplica el signo calculado y devuelve el resultado.
	cmp ecx, 1
	je .done
	neg rax

.done:
	ret

.invalid:
	; Cualquier base invalida produce 0 sin intentar convertir str.
	xor eax, eax
	ret
