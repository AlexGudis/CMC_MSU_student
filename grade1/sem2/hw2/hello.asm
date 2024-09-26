extern io_print_string, io_newline
section .data
	str: db 'Hello, world!\n', 0

section .text
global main
main:
	mov eax, str
	call io_print_string
	call io_newline
	xor eax, eax
	ret

	
