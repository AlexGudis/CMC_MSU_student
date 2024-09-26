extern io_get_udec, io_print_udec, io_newline, io_print_char

section .bss
    n:
        resd 1
    arr:
        resd 10000

section .text
global main
main:
        call io_get_udec
        mov dword[n], eax

        mov ebx, dword[n]
    .input:
        call io_get_udec
        mov dword[arr + 4 * ebx], eax
        dec ebx
        jnz .input

        mov ecx, dword[n]
    .l1:
        mov edx, dword[arr + 4 * ecx]
        mov ebx, ecx
        .l2:
            cmp edx, dword[arr + 4 * ecx]
            jb .after_if
                mov eax, dword[arr + 4 * ecx]
                mov dword[arr + 4 * ecx], edx
                mov dword[arr + 4 * ebx], eax
                mov edx, eax
            .after_if:
            loop .l2
        mov ecx, ebx   
        loop .l1

        mov ebx, dword[n]        
    .output:
        mov eax, dword[arr + 4 * ebx]
        call io_print_udec
        mov eax, ` `
        call io_print_char
        dec ebx
        jnz .output
        call io_newline

        xor eax, eax
        ret