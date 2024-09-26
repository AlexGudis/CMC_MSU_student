extern io_get_dec, io_print_dec, io_get_char, io_print_char

section .bss
    coord1_1: resd 1
    coord1_2: resd 1
    coord2_1: resd 1
    coord2_2: resd 1
    ans: resd 1
    

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    call io_get_char
    mov dword[coord1_1], eax
    call io_get_dec
    mov dword[coord1_2], eax
    call io_get_char; space input)
    call io_get_char
    mov dword[coord2_1], eax
    call io_get_dec
    mov dword[coord2_2], eax
    
    mov ebx, dword[coord1_1]
    mov eax, dword[coord2_1]
    sub eax, ebx; coord1_2 - coord2_2
    mov ecx, eax
    sar ecx, 31
    xor eax, ecx
    sub eax, ecx
    
    mov edx, eax
    
    mov ebx, dword[coord1_2]
    mov eax, dword[coord2_2]
    sub eax, ebx; coord1_2 - coord2_2
    mov ecx, eax
    sar ecx, 31
    xor eax, ecx
    sub eax, ecx
    add eax, edx
    
    call io_print_dec
    xor eax, eax
    ret