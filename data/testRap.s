# TEST_RETURN_CODE = PASS
.set noreorder

.data
    .space 10
.bss
    .space 12
a:    .space 42
.data
    .asciiz "abcd"
    .word a
.text
    NOP
    LW $1,a
    ADDI $1,$2,a
