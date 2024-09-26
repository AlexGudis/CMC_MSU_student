extern io_get_udec, io_print_udec, io_print_char

section .rodata
    info: dd 2011

section .data
    K: dd 0
    N: dd 0
    A: dd 0
    x_i_1: dd 0 ;xi-1
    x_i_2: dd 0 ;xi-2

section .text
global main
main:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    ;write your code here
    call io_get_udec
    mov dword[K], eax
    call io_get_udec
    mov dword[N], eax
    call io_get_udec
    mov dword[A], eax
    xor esi, esi; esi = 0
    
    mov eax, dword[A]
    xor edx, edx
    mov ecx, 2011
    div ecx 
    mov dword[x_i_1], edx ; x0 = A mod 2011
    mov dword[x_i_2], edx ; x0 = A mod 2011
    
.lp:
    cmp esi, dword[N]
    je .end
        
    mov eax, dword[x_i_1]
    mov dword[esp], eax
    mov eax, dword[x_i_2]
    mov dword[esp+4], eax ; loading agruments for func
    call func ; get the result of (xi-1 # xi-2) mod 2011
    mov ebx, dword[x_i_1]
    mov dword[x_i_2], ebx
    mov dword[x_i_1], eax
    inc esi
    jmp .lp
    
.end:
    call io_print_udec
    add esp, 8
    pop ebp
    
    xor eax, eax
    ret
   
global func
func:
    push ebp
    mov ebp, esp
    mov ecx, dword[ebp + 8]; xi-1
    mov ebx, dword[ebp + 12] ;xi-2
    mov eax, dword[K]
.while: ; Возводим K в степень до тех пора, пока  K <= xi-2
    cmp eax, ebx
    ja .after_loop
    mul dword[K]
    jmp .while
          
.after_loop: ; xi-1 * (K в какой-то степени) и прибавляем xi-2
    mul ecx
    add eax, ebx
    xor edx, edx
    
    div dword[info]
    mov eax, edx
    
    mov esp, ebp
    pop ebp
    ret