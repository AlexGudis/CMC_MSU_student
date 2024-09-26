extern io_get_dec, io_print_udec

section .bss
    a: resb 1
    b: resb 1
    c: resb 1
    d: resb 1
    x: resb 1

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    xor ebx, ebx
    call io_get_dec
    mov byte[a], al
    call io_get_dec
    mov byte[b], al
    call io_get_dec
    mov byte[c], al
    call io_get_dec
    mov byte[d], al
    

    movzx eax, byte[a]
   
      
    movzx ebx, byte[b]
    sal ebx, 8
    or eax, ebx
    xor ebx, ebx
    
    movzx ebx, byte[c]
    sal ebx, 16
    or eax, ebx
    xor ebx, ebx
    
    movzx ebx, byte[d]
    sal ebx, 24
    or eax, ebx
    xor ebx, ebx
    
    call io_print_udec
    
    xor eax, eax
    ret