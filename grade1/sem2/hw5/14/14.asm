extern free, io_newline, malloc, fscanf, fprintf, fopen, fclose, io_print_dec, io_print_char, qsort

section .rodata
    f_in: db "input.txt", 0
    f_ou: db "output.txt", 0
    f_in_t: db "r", 0
    f_ou_t: db "w", 0
    r_t: db "%d", 0
    w_t: db "%d ", 0

section .data
    x: dd 0
    head: dd 0; Указатель на голову списка
    swapped: dd 1

section .text
global main
main:
    mov ebp, esp; for correct debugging
    ;write your code here
    push ebp
    mov ebp, esp
    and esp, ~15
    sub esp, 16
    mov dword[esp], f_in
    mov dword[esp+4], f_in_t
    call fopen; eax = FILE *fi = fopen("input.txt", "r")
    mov edi, eax ; edi = *fi
    
    ; ЗАКРЫТЬ ВХОДНОЙ ФАЙЛ, НАПЕЧАТАТЬ В ВЫХОДНОЙ ФАЙЛш
 
.wh_read:
    mov dword[esp], edi
    mov dword[esp+4], r_t
    mov dword[esp+8], x
    call fscanf
    cmp eax, -1
    je .sort
    mov dword[esp], 8
    call malloc ; lsit *l = (list *)malloc(sizeof(list *))
    cmp dword[head], 0
    je .creates
    mov dword[esi + 4], eax; p -> next = l 
    mov esi, eax ; p = l
    mov ebx, dword[x]
    mov dword[esi], ebx
    mov dword[esi+4], 0
    jmp .wh_read
.creates:
    mov dword[head], eax ; 
    mov ebx, dword[x]
    mov dword[eax], ebx ; head -> elem = x
    mov esi, eax ; p = head
    mov dword[esi + 4], 0; p -> next = 0
    jmp .wh_read
   
.sort:
    mov eax, dword[esi + 4] ; Проверка связи с последним элементом
    cmp dword[swapped], 0
    je .end
    mov dword[swapped], 0
    mov esi, dword[head]; p = head
.in_wh:
    mov eax, dword[esi]
    cmp dword[esi + 4], 0 ; while (p -> next)
    je .sort
    
    mov eax, dword[esi]; eax = p -> elem
    mov ebx, dword[esi + 4]; ebx = p -> next
    mov edx, dword[ebx]; edx = p -> next -> elem
    cmp eax, edx
    jng .after_in_wh
    mov ecx, eax; ecx = p -> elem
    mov dword[esi], edx ; p -> elem = p -> next -> elem
    mov dword[ebx], ecx ; p -> next -> elem = p -> elem
    mov dword[swapped], 1
    
    
.after_in_wh:
    mov ebx, dword[esi + 4]
    mov esi, ebx ; p = p -> next
    jmp .in_wh
    
.end:
    mov dword[esp], edi
    call fclose
    
    mov dword[esp], f_ou
    mov dword[esp + 4], f_ou_t
    call fopen
    mov edi, eax ; edi = FILE *fo = fopen("output.txt", "w")
    
    mov esi, dword[head]
.print_wh:
    cmp esi, 0
    je .leave
    mov eax, dword[esi]
    
    mov dword[esp], edi
    mov dword[esp+4], w_t
    mov dword[esp + 8], eax
    call fprintf
    
    
    
    ;call io_print_dec
    ;call io_newline
    cmp dword[esi + 4], 0
    je .leave
    mov ebx, dword[esi + 4]
    mov esi, ebx ; p = p -> next
    jmp .print_wh

.leave:   
    mov dword[esp], edi
    call fclose
     
    xor eax, eax
    add esp, 16
    mov esp, ebp
    pop ebp
    ret
    
 