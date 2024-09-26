extern scanf, printf, strcmp, strlen, strncpy, io_print_dec, io_print_char

 section .rodata
    sc_n: db "%d", 0
    sc_s: db "%s", 0
    pr: db "%d", 0
    
section .bss
    n: resd 1
    s_unic: resb 5500 ; 
    s: resb 11

section .data
    arr_len: dd 0
    
    

section .text
global main
main:
    push ebp
    mov ebp, esp
    and esp, ~15
    sub esp, 16
    mov dword[esp+4], n
    mov dword[esp], sc_n
    call scanf ; scanf("%d", &n)
    
.wh:
    cmp dword[n], 0
    je .end
    
    mov dword[esp], sc_s
    mov dword[esp+4], s
    call scanf; scanf("%s", s)
    
    mov edi, 1; check = 1
    xor esi, esi; i = 0
    
.for:
    cmp esi, dword[arr_len]
    je .check
    ;mov eax, s_unic; eax = s_unic[0]
    ;add eax, 11
    ;mul esi ; eax = s_unic[0 + 11 * i]
    mov eax, esi;
    mov ecx, 11
    mul ecx; 11 * i
    lea ebx, [s_unic + eax]; ebx = s_unic[0 + i * 11] = s_unic[i]
    mov dword[esp], ebx
    mov dword[esp+4], s
    call strcmp ; strcmp(s_unic[i], s)
    
    cmp eax, 0
    jne .next_step_for
    mov edi, 0; check = 1
    jmp .check; break
    

.next_step_for:
    inc esi
    jmp .for
    
    
    
.check:
    cmp edi, 1  
    jne .next_step_wh
    mov eax, dword[arr_len]
    mov ecx, 11
    mul ecx; 11 * arr_len
    lea ebx, [s_unic + eax] ; ebx = s_unic[0 + 11 * arr_len] = s_unic[arr_len]
    mov dword[esp], ebx
    mov dword[esp+4], s
    mov dword[esp+8], 10
    call strncpy
    inc dword[arr_len]
 
 
.next_step_wh:
    dec dword[n]
    jmp .wh
    
.end:
    mov dword[esp], pr
    mov eax, dword[arr_len]
    mov dword[esp+4], eax
    call printf

    xor eax, eax
    add esp, 16
    mov esp, ebp
    pop ebp
    ret