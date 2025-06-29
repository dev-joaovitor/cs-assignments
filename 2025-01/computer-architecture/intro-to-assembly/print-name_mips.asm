# print my name (MIPS ASSEMBLY)
.data
    name: .asciiz "Joao Vitor da Silva"

.text
    li $v0, 4 # print string instruction
    la $a0, name # load string as argument
    syscall
    
    li $v0, 10 # exit program instruction
    syscall
