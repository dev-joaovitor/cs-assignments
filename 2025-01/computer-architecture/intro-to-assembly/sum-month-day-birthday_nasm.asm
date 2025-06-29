section .data
    month dw 4 ; define 16-bit number
    day dw 16 ; define 16-bit number

section .bss
    result resw 1 ; reserve 1 word (16-bit) for result

section .text
    global _start ; define start point

_start:
    movzx rax, word [month] ; rax = month
    movzx rbx, word [day] ; rbx = day
    add rax, rbx ; rax += rbx
    mov [result], ax ; store sum

    mov rax, 60 ; syscall to exit
    mov rdi, 0 ; exit code 0
    syscall

; no print BONUS as it requires
; word to string conversion
; and it's too complex.
