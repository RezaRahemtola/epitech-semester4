BITS 64

section	.text
    global strpbrk

strpbrk:
	MOV	RCX, 0              ; set counter to 0
    CMP BYTE [RSI], 0x00    ; check if there are chars in needle
    JE .nend                ; returns null
	JMP	.loop               ; looping

.loop:
    MOV R8, 0                       ; set needle counter to 0
    CMP BYTE [RDI + RCX], 0x00      ; check if haystack has reached the end
    JE .nend                        ; returns NULL (no match found)
    MOV R9B, BYTE [RDI + RCX]       ; moving first haystack char
    JMP .compare

.compare:
    CMP BYTE [RSI + R8], 0x00       ; check if needle has reached the end in compare
    JE .transition                  ; not found, keep looking
    CMP BYTE [RSI + R8], R9B        ; check if haystack char matches current needle char
    JE .end                         ; return
    INC R8                          ; no match, going to the next char
    JMP .compare

.transition:
    INC RCX                         ; moving in the haystack
    JMP .loop

.nend:
    MOV RAX, 0      ; set return value to NULL
    RET

.end:
    LEA RAX, [RDI + RCX]    ; set return value to pointer + counter (same as MOV RDI and ADD RCX)
    RET
