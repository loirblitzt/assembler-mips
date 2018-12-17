# TEST_RETURN_CODE = PASS
.set noreorder
.data
    .space 10 , 20
.bss
    .space 12
a:    .space 42
.text
    ADDI $1,$2,a
