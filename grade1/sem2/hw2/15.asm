extern io_get_dec, io_print_dec, io_get_char, io_print_char

section .bss
    x1: resd 1
    x2: resd 1
    x3: resd 1
    y1: resd 1
    y2: resd 1
    y3: resd 1
    first_mul: resd 1
    second_mul: resd 1
    bef_ans: resd 1
    
section .text

global main
main:
    ;write your code here
    xor eax, eax
    call io_get_dec
    mov dword[x1], eax
    call io_get_dec
    mov dword[y1], eax
    call io_get_dec
    mov dword[x2], eax
    call io_get_dec
    mov dword[y2], eax
    call io_get_dec
    mov dword[x3], eax
    call io_get_dec
    mov dword[y3], eax
    
    mov eax, dword[x1]
    mov ebx, dword[x3]
    sub eax, ebx
    
    mov ecx, dword[y2]
    mov edx, dword[y3]
    sub ecx, edx
    
    imul ecx
    mov dword[first_mul], eax
    
    
    mov eax, dword[x2]
    mov ebx, dword[x3]
    sub eax, ebx
    
    mov ecx, dword[y1]
    mov edx, dword[y3]
    sub ecx, edx
    
    imul ecx
    mov dword[second_mul], eax
    
    mov ecx, dword[first_mul]
    sub ecx, eax
    mov dword[bef_ans], ecx
    
    mov eax, dword[bef_ans] ;  Модуль ответа без деления на 2
    mov ecx, eax
    sar ecx, 31
    xor eax, ecx
    sub eax, ecx
    mov dword[bef_ans], eax
    
    call io_print_dec
 
    
    xor eax, eax
    ret