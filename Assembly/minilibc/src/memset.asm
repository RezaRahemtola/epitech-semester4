BITS 64

section	.text
    global memset

memset:
    MOV RAX, RDI    ; set return value to the pointer
    MOV RCX, 0      ; set counter to 0
    JMP .loop

.loop:
    CMP RCX, RDX                ; check if we have copied enought chars
    JE .end                     ; return if we did
    MOV	BYTE [RDI + RCX], SIL   ; set the current char to the given one
	INC	RCX                     ; increment the counter
    JMP .loop

.end:
    RET
