; void ft_list_push_front(t_list **begin_list, void *data);
; t_list layout: data at offset 0, next at offset 8.

T_LIST_SIZE equ 16
T_LIST_NEXT equ 8

section .text
global ft_list_push_front

extern malloc

ft_list_push_front:
    sub rsp, 24                    ; Save arguments and align stack per System V ABI
    mov [rsp], rdi                 ; Save begin_list
    mov [rsp + 8], rsi             ; Save data

    mov rdi, T_LIST_SIZE
    call malloc wrt ..plt
    test rax, rax
    jz .done                       ; Leave the list unchanged if malloc fails

    mov rdi, [rsp]                 ; Restore begin_list
    mov rsi, [rsp + 8]             ; Restore data
    mov rdx, [rdi]                 ; Current first node
    mov [rax], rsi                 ; new_node->data = data
    mov [rax + T_LIST_NEXT], rdx   ; new_node->next = *begin_list
    mov [rdi], rax                 ; *begin_list = new_node

.done:
    add rsp, 24
    ret
