extern io_get_dec, io_print_dec, io_newline

section .rodata align=4
    .L4:
        dd .L5 ;5
        dd .L6 ;6
        dd .L7 ;7
        dd .L8 ;8

section .data
    c: dd 0
    x: dd 0
    y: dd 0

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    call io_get_dec
    mov dword[c], eax
    call io_get_dec
    mov dword[x], eax
    call io_get_dec
    mov dword[y], eax
    
    mov eax, dword[c]
    sub eax, 5
    jmp [.L4 + 4*eax]
.L5:
    mov eax, dword[x]
    add eax, dword[y]
    call io_print_dec 
    call io_newline   
    jmp .end
.L6:
    mov eax, dword[x]
    sub eax, dword[y]
    call io_print_dec
    call io_newline
    jmp .end
.L7:
    mov eax, dword[x]
    mov ebx, dword[y]
    imul ebx ; тк числа int
    call io_print_dec
    call io_newline
    jmp .end
.L8:
    mov eax, dword[x]
    mov ebx, dword[y]
    cdq
    idiv ebx ;тк числа int
    call io_print_dec
    call io_newline
    
.end:            
    xor eax, eax
    ret