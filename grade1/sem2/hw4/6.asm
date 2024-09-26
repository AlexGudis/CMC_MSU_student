extern io_get_udec, io_print_udec, io_newline

section .bss
    N: resd 1
    A: resd 1000
    K: resd 1


section .text
global main
main:
    push ebp
    mov ebp, esp
    sub esp, 4 ; ТК планирую пользоваться стеком)))
    ;write your code here
    call io_get_udec; Считываем число N
    mov dword[N], eax
    xor ebx, ebx
.reading:
    cmp ebx, dword[N]; for (int i = 0; i < n; i++)...
    je .m0
    call io_get_udec
    mov dword[A + 4*ebx], eax; Считывем числа с клавиатуры и помещаем их в выделенное место в памяти
    inc ebx
    jmp .reading
    
.m0:  
    call io_get_udec; Считываем число K
    mov dword[K], eax
    xor ebx, ebx; Наша переменная i
    mov esi, 0; Наше поле с финальным ответом - Сколько таких чисел?
    
.m1: ;Проходимся в цикле по "массиву" и вызываем для каждого числа функцию
    cmp ebx, dword[N]; for (int i = 0; i < n; i++)...
    je .end
    mov eax, dword[A + 4*ebx]
    mov dword[esp], eax
    call func  
    
    cmp eax, dword[K]
    jne .next_digit
    add esi, 1
    
.next_digit:
    inc ebx
    jmp .m1
    
.end:
    mov eax, esi
    call io_print_udec
    call io_newline
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
    
; Функция считает количество значащих нулей у полученного числа
global func
func:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov dword[ebp-4], 0 ; Тут будет общее число значащих бит
    mov dword[ebp-8], 0; Тут будет число единиц
    mov eax, dword[ebp+8]; Положили наше число
    mov ecx, 2
    
.while_loop: ;Найдем кол-во единиц в битовом представлении числа (переведем наше число в 2 с/с)
    cmp eax, 0
    je .result
    inc dword[ebp-4]
    xor edx, edx    
    div ecx
    add dword[ebp-8], edx
    jmp .while_loop
         
.result: ; Вычтем из общего числа значащих бит кол-во единиц и получим число значащих нулей. Их и вернем
    mov eax, dword[ebp-4]
    sub eax, dword[ebp-8]
    mov esp, ebp
    pop ebp
    ret        