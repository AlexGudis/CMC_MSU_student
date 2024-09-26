extern io_print_udec

section .bss
    p: resd 1
    q: resw 1


section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    xor ecx, ecx
    mov eax, dword[q]
    dec eax; q-- (1)
    mov ebx, dword[p+8]; ebx = p[2] (2) // Адрес
    mov cx, word[eax]; cx = *(q--) // или movsx ecx, word[eax]????
    
    mov esi, dword[p]
    cmp esi, 0
    je .last_z
    mov esi, dword[q]
    cmp esi, 0
    je .last_z
    cmp dword[ebx], 0
    je .last_z
    
    mov eax, 1
    add dword[ebx], ecx; p[2] += *(q--)
    jmp .end
    

.last_z:
    add dword[ebx], ecx; p[2] += *(q--)
    xor eax, eax
.end:
    ret