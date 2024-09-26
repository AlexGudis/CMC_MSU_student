extern io_get_udec, io_print_udec, io_print_char

section .data
    x: dd 0
    y: dd 0
    a11: dd 0
    a12: dd 0
    a21: dd 0
    a22: dd 0
    b1: dd 0
    b2: dd 0
    z11: dd 0
    z10: dd 0
    z01: dd 0

section .text
global main
main:
    ;write your code here
    call io_get_udec
    mov dword[a11], eax
    call io_get_udec
    mov dword[a12], eax
    call io_get_udec
    mov dword[a21], eax
    call io_get_udec
    mov dword[a22], eax
    call io_get_udec
    mov dword[b1], eax
    call io_get_udec
    mov dword[b2], eax
    
    
    mov eax, dword[a11]
    mov ebx, dword[a12]
    xor eax, ebx ;eax = a11 ^ a12
    mov ebx, dword[b1]
    xor eax, ebx; eax = (a11 ^ a12) xor b1
    not eax ; eax = not((a11 ^ a12) xor b1)
    
    mov ecx, dword[a21]
    mov edx, dword[a22]
    xor ecx, edx ;ecx = a21 ^ a22
    mov edx, dword[b2]
    xor ecx, edx ;ecx = (a21 ^ a22) xor b2
    not ecx ;     ecx = not((a21 ^ a22) xor b2)
    
    and eax, ecx
    mov dword[z11], eax;
    
    
    mov eax, dword[a12]
    mov ebx, dword[b1]
    xor eax, ebx ; eax = a12 ^ b1
    not eax ; eax = not(a12 ^ b1)
    
    mov ecx, dword[a22]
    mov edx, dword[b2]
    xor ecx, edx ; ecx = a22 ^ b2
    not ecx ; ecx = not(a22 ^ b2)
    
    and eax, ecx
    mov dword[z01], eax
    
    
    mov eax, dword[a11]
    mov ebx, dword[b1]
    xor eax, ebx ; eax = a11 ^ b1
    not eax ; eax = not(a11 ^ b1)
    
    mov ecx, dword[a21]
    mov edx, dword[b2]
    xor ecx, edx ; ecx = a21 ^ b2
    not ecx ; ecx = not(a21 ^ b2)
    
    and eax, ecx
    mov dword[z10], eax
    
    
    mov eax, dword[x]
    mov ebx, dword[z11]
    or eax, ebx
    mov dword[x], eax; x = x or z11
    
    mov eax, dword[y]
    mov ebx, dword[z11]
    or eax, ebx
    mov dword[y], eax; y = y or z11
    
    
    mov eax, dword[x]
    mov ebx, dword[z10]
    or eax, ebx
    mov dword[x], eax; x = x or z10
    
    
    mov eax, dword[y]
    mov ebx, dword[z10]
    not ebx
    mov edx, dword[z01]
    and ebx, edx ; ebx = not(z10) & z01
    or eax, ebx
    mov dword[y], eax
    
    mov eax, dword[x]
    call io_print_udec
    mov eax, ' '
    call io_print_char
    mov eax, dword[y]
    call io_print_udec
    
            
    xor eax, eax
    ret