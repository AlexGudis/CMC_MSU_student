extern io_get_dec, io_print_dec

section .bss
    a: resd 1
    b: resd 1
    c: resd 1
    d: resd 1
    e: resd 1
    f: resd 1

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
    call io_get_dec
    mov dword[c], eax
    call io_get_dec
    mov dword[d], eax
    call io_get_dec
    mov dword[e], eax
    call io_get_dec
    mov dword[f], eax
    xor eax, eax
    mov eax, dword[a]
    
    
    mov eax, dword[f]
    add eax, dword[e]
    imul eax, dword[a]
    
    mov ebx, dword[d]
    add ebx, dword[f]
    imul ebx, dword[b]
    add eax, ebx
    
    mov edx, dword[d]
    add edx, dword[e]
    imul edx, dword[c]
    add eax, edx
    
    call io_print_dec
    
    xor eax, eax
    ret