# sum month and day from birthday (MIPS ASSEMBLY)
.data
    month: .word 4
    day: .word 16

.text
    lw $t0, month # t0 = month
    lw $t1, day # t1 = day
    add $s0, $t1, $t0 # s0 = t1 + t0
    
    # BONUS - print the result
    move $a0, $s0 # move sum result to a0
    li $v0, 1 # print word instruction
    syscall
    
    li $v0, 10 # exit program instruction
    syscall
