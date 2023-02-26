BITS 64

section .text
    global strcmp

strcmp:
    MOV RCX, 0          ; set index to 0
    MOV RAX, 0          ; set return value to 0
    MOV DL, 0           ; set first char to 0
    JMP .loop

.loop:
    MOV DL, [RDI + RCX]                 ; move the first string current char to cmp later
    CMP BYTE [RDI + RCX], 0x00          ; check if first string is NULL
    JE .end                             ; returns if NULL
    CMP BYTE [RSI + RCX], 0x00          ; check if second string is NULL
    JE .end                             ; returns if NULL
    CMP DL, BYTE [RSI + RCX]            ; check if match between chars
    JNE .end                            ; strings are not equal anymore, returning
    INC RCX                             ; incrementing the index
    JMP .loop                           ; else we loop

.end:
	MOVZX RAX, BYTE [RDI + RCX]	        ; move first char in return and zero-fill the beginning (for negative)
	MOVZX RDX, BYTE [RSI + RCX]         ; move second
	SUB	RAX, RDX		                ; subbing both 64 registers
    RET
