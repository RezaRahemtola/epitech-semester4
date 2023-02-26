BITS 64

section	.text
    global strrchr

strrchr:
	MOV	RCX, 0              ; set counter to 0
    MOV RAX, 0              ; set return value to 0
	JMP	.loop               ; looping

.loop:
    CMP BYTE [RDI + RCX], SIL     ; check if current char match wanted char (SIL to access the first byte of RSI)
    JE .setret                    ; set return value to current found
    JMP .transition

.transition:
    CMP	BYTE [RDI + RCX], 0x00    ; check if NULL
    JE .end                       ; return if end of string
    INC	RCX                       ; incrementing the counter
	JMP	.loop                     ; else we loop

.setret:
    LEA RAX, [RDI + RCX]          ; set return value to pointer + counter (same as MOV RDI and ADD RCX)
    JMP .transition

.end:
    RET                     ; value is already in RAX, we can return
