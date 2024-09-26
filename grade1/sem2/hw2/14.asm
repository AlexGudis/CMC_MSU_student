extern io_get_dec, io_print_dec, io_newline

section .bss
    M: resd 1
    N: resd 1
    K: resd 1
    D: resd 1
    X: resd 1
    Y: resd 1
    boxes: resd 1
    check: resd 1
    b_div_3: resd 1
    always: resd 1

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    call io_get_dec
    mov dword[M], eax
    call io_get_dec
    mov dword[N], eax
    call io_get_dec ; Обработка K = 0
    mov ebx, eax
    sub ebx, 1
    adc eax, 0
    mov dword[K], eax
    call io_get_dec
    mov dword[D], eax
    call io_get_dec
    mov dword[X], eax
    call io_get_dec
    mov dword[Y], eax
    
    
    mov eax, dword[M]
    mov ebx, dword[N]
    mul ebx; eax = M * N
    mov ebx, dword[K]
    mul ebx; eax = M * N * K
    ;call io_print_dec
    
    mov ebx, dword[D]
    CDQ
    div ebx; eax = (M * N * K) // D
    sub edx, 1
    sbb eax, 0
    inc eax; Можем разместить так, чтобы последняя коробка оказалась заполненной не полностью
    mov dword[boxes], eax
    ;call io_print_dec
    ;call io_newline
    
    
    mov eax, dword[X]
    mov ebx, 6
    CDQ
    div ebx
    ;call io_print_dec
    sub eax, 1
    mov ebx, 0
    adc ebx, 0
    mov eax, ebx; eax = 0 (Время после 6 утра). eax == 1 (Время до 6 утра)
    mov dword[check], eax
    ;call io_print_dec
    
    mov eax, dword[boxes]
    sub eax, 1
    mov ebx, 3
    cdq
    div ebx
    add eax, 1
    mov dword[b_div_3], eax; получили часть коробок, которые не будут пропущены пограничниками
    
    mov eax, dword[boxes]
    mov ebx, dword[b_div_3]
    
    sub eax, ebx; Всегда пропустят столько
    mov dword[always], eax
    mov eax, dword[check]
    mul ebx; eax = check * b_div_3 (Та часть, которую могут не пропустить)
    
    mov ebx, dword[always]
    add eax, ebx; (boxes - b_div_3) + check * b_div_3
    
    call io_print_dec
    

    
    xor eax, eax,
    ret