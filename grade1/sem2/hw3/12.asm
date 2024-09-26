extern io_get_udec, io_print_udec 

section .bss
    n: resd 1;  границы диапозона
    k: resd 1;

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    call io_get_udec
    mov dword[n], eax
    call io_get_udec
    mov dword[k], eax
    mov ebx, 1
    xor esi, esi; ans = 0;
    mov ecx, 2
    
.for_1_to_n:
    cmp ebx, dword[n]; for (int i = a; i <= n; i++)
    ja .end
    xor edi, edi; k = 0
    mov eax, ebx
    xor ebp, ebp;
    
    
    .while_loop: ;Найдем кол-во единиц в битовом представлении числа (переведем наше число в 2 с/с)
        cmp eax, 0
        je .result
        inc ebp
        xor edx, edx
        div ecx
        add edi, edx
        jmp .while_loop
         
    .result: ; Вычтем из общего числа значащих бит кол-во единиц и получим число значащих нулей
        sub ebp, edi
        cmp ebp, dword[k]
        je .plus
        inc ebx
        jmp .for_1_to_n
        
    .plus:
        inc esi
        inc ebx
        jmp .for_1_to_n

.end:     
    mov eax, esi
    call io_print_udec
    xor eax, eax
    ret