extern io_get_udec, io_print_udec, io_newline

section .bss
    K: resd 1

section .text
global main
main:
    ;write your code here
    push ebp
    mov ebp, esp
    sub esp, 4
    call io_get_udec
    mov dword[K], eax
    xor edi, edi; edi = 0. Наш счетчик найденного количества недостаточных чисел
    xor eax, eax
    mov esi, 1; Наше проверяемое натуральное число
.while_k:
    cmp edi, dword[K]
    je .end
    
    mov dword[esp], esi ;Заносим аргумент функции (наше проверямое число) на стек
    call f ; в eax будет 1, если число недостаточное, 0 в противном случае
    cmp eax, 1
    je .next_k ;Если недостаточное, то нашли еще одно K
    
    inc esi ;Иначе ничего не нашли и нужно просто увеличить проверяемое число
    jmp .while_k
    
.next_k:
    inc esi ;Увеличиваем проверяемое число
    inc edi ; Увеличиваем счетчик найденных K
    jmp .while_k
    
    
    
.end:
    dec esi ;т.к. перед проверкой в последний раз мы на 1 увеличили наше число
    mov eax, esi; Переносим наше k-ое число на регистр eax
    call io_print_udec    
    call io_newline
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
    
    
    
global f
f:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov dword[ebp-4], 0
    mov ecx, 1
.for_1_to_n:
    mov eax, dword[ebp+8]
    cmp ecx, dword[ebp+8]
    je .end_func ;Если i == n
    ; i < n:
    xor edx, edx
    div ecx
    cmp edx, 0
    jne .next_iter; n % i != 0
    ; n % i == 0:
    add dword[ebp-4], ecx

.next_iter:
    inc ecx
    jmp .for_1_to_n
    

.end_func:   
    mov eax, dword[ebp-4]
    cmp eax, dword[ebp+8]
    jb .end_ret_1 
    xor eax, eax ; сумма делителей числа >= исходного числа, значит, это не недостаточное число   
    mov esp, ebp
    pop ebp
    ret
    
.end_ret_1:
    mov eax, 1 ; Сумма делителей числа < исходного числа, значит, это недостаточное число
    mov esp, ebp
    pop ebp
    ret
    