BITS 64

section	.text
    global strcspn
    extern strlen

strcspn:
	MOV	RCX, 0              ; set counter to 0
    CMP BYTE [RSI], 0x00    ; check if there are chars in needle
    JE .strlen              ; no char to reject, we can return the entire haystack
	JMP	.loop               ; looping

.loop:
    MOV R8, 0                       ; set needle counter to 0
    CMP BYTE [RDI + RCX], 0x00      ; check if haystack has reached the end
    JE .end                         ; returns the counter
    MOV R9B, BYTE [RDI + RCX]       ; moving first haystack char
    JMP .compare

.compare:
    CMP BYTE [RSI + R8], 0x00       ; check if needle has reached the end in compare
    JE .transition                  ; not found, keep looking
    CMP BYTE [RSI + R8], R9B        ; check if haystack char matches current needle char
    JE .end                         ; return (found a reject char)
    INC R8                          ; no match, going to the next char
    JMP .compare

.transition:
    INC RCX                         ; moving in the haystack
    JMP .loop

.strlen:
    CALL strlen wrt ..plt   ; calling our strlen
    RET

.end:
    MOV RAX, RCX
    RET
