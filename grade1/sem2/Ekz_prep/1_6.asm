extern io_print_udec

section .data
    go db 0xab, 0xcd, 0xef
    funny dd alphabet
    
section .bss
    alphabet resd 1 

section .text
global main
main:
    mov ebp, esp; for correct debugging
    xor eax, eax
    mov ax, word[go+1]
    add ax, 0xaaaa
    call io_print_udec
    mov al, byte[funny+2]
    xor eax, eax
    ret