BITS 64

section	.text
    global memcpy

memcpy:
    MOV RAX, RDI    ; set return value to the pointer
    MOV RCX, 0      ; set counter to 0
    JMP .loop

.loop:
    CMP RCX, RDX                        ; check if we have copied enought chars
    JE .end                             ; return if we did
    MOV	R8B, BYTE [RSI + RCX]           ; using first bytes of R8 as tmp storage (RDI, RSI and RDX are taken, RCX is our counter so R8 is next)
	MOV	BYTE [RAX + RCX], R8B           ; moving the new byte to our result
	INC	RCX                             ; increment the counter
    JMP .loop

.end:
    RET
