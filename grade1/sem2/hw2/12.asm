extern io_get_dec, io_print_dec, io_print_char

section .bss
    n: resd 1
    mast_numb: resd 1

section .data
    cards: db '23456789TJQKA', 0
    mast: db 'SCDH', 0
    
    
section .text
global main
main:
    mov ebp, esp; for correct debugging
    xor eax, eax
    xor ebx, ebx
    xor ecx,ecx
    xor edx,edx
    call io_get_dec
    mov dword[n], eax; eax = n
    
    sub eax, 1; eax = n-1
    mov ebx, 13
    CDQ 
    idiv ebx; eax = (n-1)//13
    mov dword[mast_numb], eax
    imul ebx; eax = 13*((n-1)//13)
    mov ecx, dword[n]
    sub ecx, eax
    sub ecx, 1; ecx = n-13*((n-1)//13)-1
    
    mov eax, dword[cards + ecx]
    call io_print_char
    
    mov ecx, dword[mast_numb]
    mov eax, dword[mast + ecx]
    call io_print_char
    
    
    xor eax, eax
    xor ebx,ebx
    xor ecx,ecx
    xor edx,edx
    ret