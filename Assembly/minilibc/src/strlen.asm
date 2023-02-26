BITS 64

section	.text
    global strlen

strlen:
	MOV	RCX, 0              ; set counter to 0
	JMP	.loop               ; looping

.loop:
	CMP	BYTE [RDI + RCX], 0x00    ; check if NULL
    JE .end                       ; return if NULL with RAX value
    INC	RCX                       ; incrementing the counter
	JMP	.loop                     ; else we loop

.end:
    MOV RAX, RCX                  ; move counter to return value
    RET
