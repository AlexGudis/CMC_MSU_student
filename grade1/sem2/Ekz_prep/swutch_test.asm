extern io_get_dec, io_print_dec, io_newline

section .rodata align =4
.L4:
    dd .L3 ; x = 1
    dd .L5 ; x = 2
    dd .L9 ; x = 3
    dd .L8 ; x = 4
    dd .L7 ; x = 5
    dd .L7 ; x = 6

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
    
    mov edx , dword [x]
    mov eax , dword [y]
    mov ecx , dword [c]

    dec edx
    cmp edx , 5
    ja .L8
    jmp [.L4 + 4* edx ]

.L3: ; x == 1
    imul eax , ecx ; w = y*z;
    jmp .L2 ; goto switch_end
.L5:
    cdq
    idiv ecx
    jmp .L6
.L9:
    mov eax, 1
.L6:
    add eax, ecx
    jmp .L2
.L7:
    mov eax, 1
    sub eax, ecx
    jmp .L2
.L8:
    mov eax, 2        
.L2:            
    xor eax, eax
    ret