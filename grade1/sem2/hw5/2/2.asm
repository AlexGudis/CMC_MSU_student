extern scanf, printf, strlen, io_print_char, io_print_string, io_print_dec

section .rodata
    sc: db "%s", 0
    p1: db "1 2", 0
    p2: db "2 1", 0
    p3: db "0", 0

section .bss
    s1: resb 1001 ; Первая строка
    s2: resb 1001
    n1: resd 1 ; Длина первой строки
    n2: resd 1
    ans: resd 1

section .text
global main
main:
    push ebp
    mov ebp, esp
    xor eax, eax
    and esp, ~15
    sub esp, 16
    
    mov dword[esp], sc ;scanf("%s", s1)
    mov dword[esp+4], s1
    call scanf
    
    mov dword[esp], sc; scanf("%s", s2);
    mov dword[esp+4], s2
    call scanf
    
    mov dword[esp], s1; n1 = strlen(s1)
    call strlen
    mov dword[n1], eax
    
    mov dword[esp], s2; n2 = strlen(s2)
    call strlen
    mov dword[n2], eax
    
    mov ebx, dword[n1]
    mov esi, -1; i = -1
    cmp ebx, eax; n1 ? n2
    jbe .check2
    ; n1 > n2:
.check1:
    inc esi
    cmp esi, dword[n1] ; for (int i = 0; i < n1; i++)
    je .check_ans; После выполнения цикла перейдем на проверку итогового ответа
    xor edi, edi; j = 0
    mov ecx, 1; check = 1; Будем смотреть, нашли ли подстроку
.check1_jl:
    cmp edi, dword[n2]; for (int j = 0; j < n2; j++)
    je .check1_incheck
    movsx eax, byte[s2 + edi]
    movsx ebx, byte[s1 + edi + esi]
    ;call io_print_char
    ;mov eax, ebx
    ;call io_print_char
    cmp ebx, eax; if (s1[i+j] ? s2[j])
    je .next_step_1 
    ; Элементы не совпали
    mov ecx, 0; check = 0
    jmp .check1_incheck ; Вываливаемся из вложенного цикла j
    
.next_step_1: 
    ; Элементы совпали
    inc edi; if (s1[i+j] == s2[j]) -> Проверяем дальше 2 сторку на вхождение в 1
    jmp .check1_jl
    
.check1_incheck:
    cmp ecx, 1
    jne .check1 ; флаг не равен 1, значит s2 не подстрока пока что
    mov dword[ans], 2
    jmp .check_ans ;Переходим на проверку ответа
    
    
.check2:
    inc esi
    cmp esi, dword[n2] ; for (int i = 0; i < n2; i++)
    je .check_ans; После выполнения цикла перейдем на проверку итогового ответа
    xor edi, edi; j = 0
    mov ecx, 1; check = 1; Будем смотреть, нашли ли подстроку
.check2_jl:
    cmp edi, dword[n1]; for (int j = 0; j < n1; j++)
    je .check2_incheck
    movsx edx, byte[s1 + edi]
    movsx eax, byte[s2 + edi + esi]
    cmp eax, edx; if (s2[i+j] ? s1[j])
    je .next_step_2 
    ; Элементы не совпали
    mov ecx, 0
    jmp .check2_incheck ; Вываливаемся из вложенного цикла j
    
.next_step_2: 
    ; Элементы совпали
    inc edi; if (s1[i+j] == s2[j]) -> Проверяем дальше 1 сторку на вхождение в 2
    jmp .check2_jl
    
.check2_incheck:
    cmp ecx, 1
    jne .check2 ; флаг не равен 1, значит s1 не подстрока пока что
    mov dword[ans], 1
    jmp .check_ans ;Переходим на проверку ответа

.check_ans:
    cmp dword[ans], 1
    je .1_in_2
    cmp dword[ans], 2
    je .2_in_1

.zero_ans:
    mov dword[esp], p3
    call printf; printf("0\n")
    jmp .end  
  
.2_in_1:
    mov dword[esp], p2
    call printf; printf("2 1\n")
    jmp .end


.1_in_2:
    mov dword[esp], p1
    call printf; printf("1 2\n")

.end:    
    add esp, 16
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret