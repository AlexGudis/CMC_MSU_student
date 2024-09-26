extern io_get_dec, io_print_dec, io_print_char

section .bss
    arr: resd 10000
    n: resd 1
    
section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    xor ebx, ebx
    call io_get_dec; eax = n
    mov dword[n], eax
    mov edi, 1; swapped = 1;
    

.get_arr:
    cmp ebx, dword[n]; for, scanf...
    jz .m1
    call io_get_dec
    mov dword[arr+ebx*4], eax
    inc ebx
    jmp .get_arr

.m1:
    mov ebx, dword[n]
    dec ebx; ebx = n - 1
    
.while_lp:; while (swapped)
    cmp edi, 1
    jnz .print_arr
    xor edi, edi
    xor ecx, ecx
    
    .for_loop: ; for (int i = 0; i < n - 1; i++) 
        cmp ecx, ebx; i < n - 1
        jz .while_lp
        mov eax, dword[arr+ecx*4]
        cmp eax, dword[arr+ecx*4 + 4]; arr[i] ? arr[i+1]
        jle .i_inc
        ; if (arr[i] > arr[i+1]) // Выполняем перестановку двух элементов массива
        mov edx, dword[arr+ecx*4+4]
        mov dword[arr+ecx*4+4], eax
        mov dword[arr+ecx*4], edx
        mov edi, 1; swapped = 1
        
        .i_inc:
            inc ecx
            jmp .for_loop
            
.print_arr:
    xor ebx, ebx; ebx = 0
    .for_loop_print:
        cmp ebx, dword[n]; for (int i = 0; i < n; i++)
        jz .end
        mov eax, dword[arr + ebx*4]
        call io_print_dec
        mov eax, ' '
        call io_print_char
        inc ebx
        jmp .for_loop_print
.end:            
    xor eax, eax
    ret