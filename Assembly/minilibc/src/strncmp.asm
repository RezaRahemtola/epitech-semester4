BITS 64

section .text
    global strncmp

strncmp:
    MOV RCX, 0          ; set index to 0
    MOV RAX, 0          ; set return value to 0
    MOV R8B, 0          ; set first char to 0
    CMP RDX, 0          ; check if we should compare
    JE .end             ; returns if no char to check
    JMP .loop

.loop:
    MOV R8B, [RDI + RCX]                ; move the first string current char to cmp later
    CMP BYTE [RDI + RCX], 0x00          ; check if first string is NULL
    JE .end                             ; returns if NULL
    CMP BYTE [RSI + RCX], 0x00          ; check if second string is NULL
    JE .end                             ; returns if NULL
    CMP R8B, BYTE [RSI + RCX]           ; check if match between chars
    JNE .end                            ; strings are not equal anymore, returning
    INC RCX                             ; incrementing the index
    CMP RDX, RCX                        ; check if we compared every char
    JE .cend                            ; ending if we did
    JMP .loop                           ; else we loop

.cend:
	MOVZX RAX, BYTE [RDI + RCX - 1]	        ; move first char in return and zero-fill the beginning (for negative)
	MOVZX R8, BYTE [RSI + RCX - 1]          ; move second
	SUB	RAX, R8		                        ; subbing both 64 registers
    RET

.end:
	MOVZX RAX, BYTE [RDI + RCX]	        ; move first char in return and zero-fill the beginning (for negative)
	MOVZX R8, BYTE [RSI + RCX]          ; move second
	SUB	RAX, R8		                    ; subbing both 64 registers
    RET
