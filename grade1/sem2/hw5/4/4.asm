extern fscanf, fopen, printf, fclose

section .rodata
    fname: db "data.in", 0
    f_type: db "r", 0
    scan_type: db "%d", 0

section .bss
    n: resd 1
    x: resd 1


section .text
global main
main:
    ;write your code here
    push ebp
    mov ebp, esp
    and esp, ~15
    sub esp, 16
    mov dword[esp], fname
    mov dword[esp+4], f_type
    call fopen
    ; eax = FILE *f = fopen("data.in", "r")
    mov edi, eax
.wh: ; Считываем, пока не встретим -1 результат в scanf, т.е. EOF
    mov dword[esp], edi
    mov dword[esp+4], scan_type
    mov dword[esp+8], x
    call fscanf
    cmp eax, -1
    je .end
    inc dword[n]
    jmp .wh
    
.end:
    mov dword[esp], scan_type
    mov eax, dword[n]
    mov dword[esp+4], eax
    call printf ;printf("%d", n);
  
    mov dword[esp], edi
    call fclose
    xor eax, eax
    add esp, 16
    mov esp, ebp
    pop ebp
    ret