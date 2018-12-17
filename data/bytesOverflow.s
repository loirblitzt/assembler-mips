# TEST_RETURN_CODE = PASS
.set noreorder
.data
	.byte 0xF
	.word 3
.text
	ADD $1,$1,$1
