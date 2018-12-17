# TEST_RETURN_CODE = FAIL
.set noreorder
.data
	.byte 0xF
	.word 3
	.asciiz 3
.text
	ADD $1,$1,$1
