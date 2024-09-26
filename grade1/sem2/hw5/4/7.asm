extern scanf, printf, strcmp, strlen, strncpy

 section .rodata
    sc_n: db "%d", 0
    sc_s: db "%s", 0
    pr: db "%d\n", 0

section .data
    arr_len: dd 0
    
section .bss
    s_unic: db 500*11

section .text
global main
main:
    ;write your code here
    xor eax, eax
    ret