extern io_get_udec, io_print_udec, io_newline

section .data
    mask    dd      0xffff, 0xff00ff, 0xf0f0f0f, 0x33333333, 0x55555555; *mask = [...]

section .text
global main
main:
    mov ebp, esp; for correct debugging
    call   io_get_udec; scanf("%u", ...) Допустим число n
    mov    ebx, mask; ebx = mask
    add    ebx, 16; ebx = mask[4] ||| i = 4
    mov    ecx, 1; ecx = 1
.label: ;do - while
    mov    esi, dword [ebx]; esi = 0x55555555
    mov    edi, esi; edi = 0x55555555
    not    edi; edi = not(0x55555555)
    mov    edx, eax;  edx = eax
    and    eax, esi; n & 0x55555555 пусть это будет число p (unsigned int)
    and    edx, edi; n & (not(0x55555555)) а это пусть число q (unsigned int)
    
    shl    eax, cl; p << 1
    shr    edx, cl; q >> 1
    
    or     eax, edx; p || q
    shl    ecx, 1; ecx *= 2;
    sub    ebx, 4; ebx = mask[i - 1]
    
    cmp    ebx, mask - 4
    jne    .label; if (mask[i] != (mask - 4))

    call   io_print_udec; print(eax) т.е. print(p||q)
    call   io_newline; print(\n)
    xor    eax, eax
    ret