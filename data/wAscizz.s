# TEST_RETURN_CODE = FAIL
.set noreorder
.data
	.byte 0xF
	.word 3
	.ascii "hello\n"
.text
	ADD $1,$1,$1
