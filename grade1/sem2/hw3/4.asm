extern io_get_udec, io_print_udec, io_get_dec

section .bss
    digits: resb 20

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    call io_get_udec    
    xor ecx, ecx
    xor ebx, ebx
    mov byte[digits], 0
    mov ecx, 8
.lp: 
    cmp eax, 0; while (eax != 0)
    jz .before_reverse_lp
    xor edx, edx    
    div ecx; eax /= 8
    mov byte[digits + 1*ebx], dl; Записываем остаток от деления в выделенную область памяти
    inc ebx; Индекс нашей области 
    jmp .lp; Переходим снова к выполнению цикла
    
.before_reverse_lp:
    cmp ebx, 0
    jz .reverse_lp
    dec ebx    
    
                  
.reverse_lp: ;прочитаем в обратном порядке нашу последовательность байт
    mov al, byte[digits + ebx]
    call io_print_udec
    cmp ebx, 0
    jz .end
    dec ebx
    jmp .reverse_lp
.end:       
    xor eax, eax
    ret