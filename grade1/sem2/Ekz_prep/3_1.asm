extern io_print_udec

section .text
global main
main:
    ;write your code here
    xor eax, eax
    ret
    ;ssc*nnnn;
global f
f:
   push ebp
   mov ebp, esp
   sub esp, 4
   
   mov eax, dword[ebp + 8]; eax = q    
   cmp eax, 0
   je .end_rec
   mov ecx, dword[eax + 4] ;ecx = q -> next
   mov dword[esp], ecx
   call f ; eax = f(q -> next)
   xor ebx, ebx
   mov ecx, dword[ebp+8]; ecx = q
   movsx ebx, word[ecx]; ebx = q -> s
   add eax, ebx ; q->s + f(q->next)
    
   xor ebx, ebx
   movsx ebx, byte[ecx + 2] ; bl = q -> c
   idiv ebx ;
   mov eax, edx ; Кладем остаток от деления
   mov esp, ebp
   pop ebp
   ret
       
.end_rec:
    mov eax, 42
    mov esp, ebp
    pop ebp     
    ret 