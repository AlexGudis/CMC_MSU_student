extern fscanf, fprintf, fopen, fclose, io_print_dec, io_print_char, qsort

section .rodata
    f_in: db "input.txt", 0
    f_ou: db "output.txt", 0
    f_in_t: db "r", 0
    f_ou_t: db "w", 0
    r_t: db "%d", 0
    w_t: db "%d ", 0
    
section .bss
    a: resd 1000

section .data
    arr_len: dd 0
    i: dd 0

section .text
global main
main:
    ;write your code here
    push ebp
    mov ebp, esp
    and esp, ~15
    sub esp, 16
    mov dword[esp], f_in
    mov dword[esp+4], f_in_t
    call fopen; eax = FILE *fi = fopen("input.txt", "r")
    mov edi, eax ; edi = *fi
    
    mov dword[esp], f_ou
    mov dword[esp+4], f_ou_t
    call fopen; eax = FILE *fo = fopen("output.txt", "w")
    mov esi, eax ; esi = *fo
    
.wh:
    mov dword[esp], edi
    mov dword[esp+4], r_t
    mov ebx, dword[arr_len]
    lea eax, [a + ebx * 4]
    mov dword[esp+8], eax
    call fscanf ;fscanf(fi, "%d", &a[arr_len])
    cmp eax, -1
    je .after_wh
    inc dword[arr_len]
    jmp .wh
    
.after_wh:

    mov dword[esp], a
    mov eax, dword[arr_len]
    mov dword[esp + 4], eax
    mov dword[esp + 8], 4
    mov dword[esp + 12], comp
    call qsort
    
.after_q:
    mov eax, dword[arr_len]
    cmp dword[i], eax
    je .end
    mov dword[esp], esi
    mov dword[esp + 4], w_t
    mov ebx, dword[i]
    lea eax, [a + ebx * 4]; a[i]
    mov ecx, dword[eax]
    mov dword[esp+8], ecx ;fprintf(fo, "%d ", a[i])
    call fprintf
    inc dword[i]
    jmp .after_q
    
.end:
    mov dword[esp], edi
    call fclose
    mov dword[esp], esi
    call fclose
    
    xor eax, eax
    add esp, 16
    mov esp, ebp
    pop ebp
    ret
    
global comp
comp:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp + 8]
    mov eax, dword[eax]
    mov edx, dword[ebp + 12]
    cmp eax, dword[edx]
    jl .ll
    je .le
    mov eax, 1
    jmp .end_comp
.ll:
    mov eax, -1
    jmp .end_comp
.le:
    mov eax, 0
    
.end_comp:  
    mov esp, ebp
    pop ebp
    ret    