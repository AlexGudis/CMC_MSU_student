
section .data
    wow dw 0x1234, 0xbeaf
    tasty dd 0x004010d0

section .text
global main
main:
    xor eax, eax
    movsx eax, byte[wow+3]
    sub ax, 0x4321
    xchg ah, byte[tasty+1]
    xor eax, eax
    ret