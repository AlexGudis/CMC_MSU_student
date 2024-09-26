extern io_get_dec, io_print_dec, io_print_string

section .bss
    x1: resd 1
    x2: resd 1
    x3: resd 1
    x4: resd 1
    y1: resd 1
    y2: resd 1
    y3: resd 1
    y4: resd 1
    x_p: resd 1
    y_p: resd 1
    x_start: resd 1
    x_stop: resd 1
    y_start: resd 1
    y_stop: resd 1
    
section .text:
    ans_yes: db 'YES', 0    
    ans_no: db 'NO', 0
    
section .text
global main
main:
    mov ebp, esp; for correct debugging
    call io_get_dec
    mov dword[x1], eax
    call io_get_dec
    mov dword[y1], eax
    call io_get_dec
    mov dword[x2], eax
    call io_get_dec
    mov dword[y2], eax
    call io_get_dec
    mov dword[x3], eax
    call io_get_dec
    mov dword[y3], eax
    call io_get_dec
    mov dword[x4], eax
    call io_get_dec
    mov dword[y4], eax
    call io_get_dec
    mov dword[x_p], eax
    call io_get_dec
    mov dword[y_p], eax
    
    ;  Проверка х координаты
    mov eax, dword[x1]
    mov ebx, dword[x2]
    
    cmp eax, ebx
    jne .check_xp; if (x1 != x2) => Нашли наш отрезок по координате x
    
    mov ebx, dword[x3]; Если оказалось, что x1 == x2, то точно x1 != x3
    
    .check_xp:
        mov ecx, dword[x_p]
        cmp eax, ebx ; if (x1 < x2)
        jl .below_x_check
            ; eax > ebx
            cmp ecx, eax
            jge .no; Координата по x больше наибольшей координаты по x
            
            cmp ecx, ebx; ecx должен быть больше ebx для принадлежности отрезку  x    
            jle .no; Координта по х меньше наименьшей координаты по х
            jmp .check_yp; Переходим на проверку координаты по y
            
        
        .below_x_check: ; eax < ebx
            cmp  ecx, ebx
            jge .no
            
            cmp ecx, eax
            jle .no
            jmp .check_yp
        
        
    ; Проверка у координаты
.check_yp:    
    mov eax, dword[y1]
    mov ebx, dword[y2]
    
    cmp eax, ebx
    jne .check_coords_y; if (y1 != y2) => Нашли наш отрезок по координате y
    
    mov ebx, dword[y3]; Если оказалось, что y1 == y2, то точно y1 != y3
    
    .check_coords_y:
        mov ecx, dword[y_p]
        cmp eax, ebx ; if (y1 < y2)
        jl .below_y_check
            ; eax > ebx
            cmp ecx, eax
            jge .no; Координата по y больше наибольшей координаты по y
            
            cmp ecx, ebx; ecx должен быть больше ebx для принадлежности отрезку  y    
            jle .no; Координта по y меньше наименьшей координаты по y
            jmp .yes
            
        
        .below_y_check: ; eax < ebx
            cmp  ecx, ebx
            jge .no
            
            cmp ecx, eax
            jle .no
            jmp .yes
    
    
.no:
    mov eax, ans_no
    call io_print_string
    jmp .end  
    
.yes:
    mov eax, ans_yes
    call io_print_string
    
.end:  
    xor eax, eax
    ret