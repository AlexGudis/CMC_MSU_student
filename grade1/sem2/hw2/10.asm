extern io_get_dec, io_print_dec

section .bss
    a: resd 1
    b: resd 1
    
section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    call io_get_dec
    mov dword[a], eax
    call io_get_dec
    mov dword[b], eax
    
    mov eax, dword[a]
    sub eax, 1
    mov ebx, 42
    imul ebx
    mov ecx, eax 
    add ecx, dword[b]
    
    mov eax, dword[a]
    mov ebx, 2
    idiv ebx
    sub ecx, eax
    mov eax, ecx
    
    call io_print_dec

    xor eax, eax
    ret