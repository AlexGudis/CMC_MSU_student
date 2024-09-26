extern io_get_dec, io_print_dec, io_print_char

section .text
global main
main:
    ;write your code here
    call func
    
    
    xor eax, eax
    ret
    
    
global func
func:
    push ebp
    mov ebp, esp
    sub esp, 4
    call io_get_dec
    cmp eax, 0
    je .end_rec
    mov dword[ebp-4], eax
    call func
    mov eax, dword[ebp-4]
    call io_print_dec
    mov eax, ' '
    call io_print_char
    
.end_rec:
    mov esp, ebp
    pop ebp
    ret        