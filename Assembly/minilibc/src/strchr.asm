BITS 64

section	.text
    global strchr

strchr:
	MOV	RCX, 0              ; set counter to 0
    MOV RAX, 0              ; set return value to 0
	JMP	.loop               ; looping

.loop:
    CMP BYTE [RDI + RCX], SIL     ; check if current char match wanted char (SIL to access the first byte of RSI)
    JE .end                       ; return if it matches
	CMP	BYTE [RDI + RCX], 0x00    ; check if NULL
    JE .nend                      ; return NULL if end of string
    INC	RCX                       ; incrementing the counter
	JMP	.loop                     ; else we loop

.nend:
    MOV RAX, 0                    ; return NULL
    RET

.end:
    LEA RAX, [RDI + RCX]          ; set return value to pointer + counter (same as MOV RDI and ADD RCX)
    RET
