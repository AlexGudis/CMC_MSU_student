extern io_get_udec, io_print_udec

section .bss
    N: resd 1
    K: resd 1

section .data
    S: dd 0

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    push ebp
    mov ebp, esp
    sub esp, 8
    call io_get_udec
    mov dword[N], eax
    add dword[S], eax
    call io_get_udec
    mov dword[K], eax
        
.lp:
    mov eax, dword[K]   
    mov dword[esp+4], eax; Размещаем К на стеке
    mov eax, dword[N]
    mov dword[esp], eax; Размещаем число, которое будем переводить на стеке
    call func; Функция получает N и K и возвращает число в виде суммы цифр исходного в с/с с основанием
    ; K записанное в 10с/с
    
    
    add dword[S], eax; summ += новое число на доске
    cmp eax, dword[esp]
    je .end
    mov dword[N], eax
    jmp .lp
    
    
.end:
    mov eax, dword[S]
    call io_print_udec
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
    
    
global func
func:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, dword[ebp + 8]; eax = N
    mov ecx, dword[ebp + 12]; ecx = K
    mov dword[ebp - 4], 0; summ = 0
    
.m0:
    cmp eax, 0
    je .end_func
    xor edx, edx
    div ecx; n /= k
    add dword[ebp - 4], edx; Добавляем остаток, то есть цифру числа в данной с/с (с основанием K)
    jmp .m0         
                        
.end_func:
    mov eax, dword[ebp - 4]
    mov esp, ebp
    pop ebp
    ret                                
    
    
    
    