# TEST_RETURN_CODE = PASS
.set noreorder
.data
	.byte 0xF
	.word 3
	.asciiz "hello\n"
.text
	ADD $1,$1,$1
