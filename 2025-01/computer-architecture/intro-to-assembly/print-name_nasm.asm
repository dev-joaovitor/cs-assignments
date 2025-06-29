section .data
    name db "Joao Vitor da Silva", 0ah ; declare newline-terminated (0ah = \n) string

section .text
    global _start ; define start point

_start:
    mov rax, 1 ; syscall number to write
    mov rdi, 1 ; file descriptor 1 = stdout
    mov rsi, name ; pointer to string
    mov rdx, 21 ; size of the string in bytes
    syscall
    mov rax, 60 ; syscall to exit
    mov rdi, 0 ; exit code 0
    syscall
