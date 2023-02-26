BITS 64

section	.text
    global strstr

strstr:
	MOV	RCX, 0              ; set counter to 0
    CMP BYTE [RSI], 0x00    ; check if needle is NULL
    JE .end                 ; returns haystack
	JMP	.loop               ; looping

.loop:
    MOV R8, 0                       ; set needle counter to 0
    CMP BYTE [RDI + RCX], 0x00      ; check if haystack has reached the end
    JE .nend                        ; returns NULL (no match found)
    MOV R9B, BYTE [RSI]             ; moving first needle char
    CMP BYTE [RDI + RCX], R9B       ; check if current char matches beginning of haystack
    JE .compare                     ; if it matches, comparing the full needle
    JMP .transition

.compare:
    CMP BYTE [RSI + R8], 0x00       ; check if needle has reached the end in compare
    JE .end                         ; found it
    LEA R9, BYTE [RDI + RCX]        ; move haystack begin pointer (to more further after)
    MOV R9B, BYTE [R9 + R8]         ; move the haystack begin pointer to the current char compared
    CMP BYTE [RSI + R8], R9B        ; check if current needle & haystack chars match
    JNE .transition                 ; no match, keep looking
    INC R8                          ; match, going to the next char
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
