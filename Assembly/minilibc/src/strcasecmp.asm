BITS 64

section .text
    global strcasecmp

strcasecmp:
    MOV RCX, 0          ; set index to 0
    MOV RAX, 0          ; set return value to 0
    MOV DL, 0           ; set first char to 0
    MOV R8B, 0          ; set second char to 0
    JMP .loop

.loop:
    MOV DL, [RDI + RCX]                 ; move the first string current char to cmp later
    MOV R8B, [RSI + RCX]                ; move the second string current char to cmp later
    JMP .transform_first

.compare:
    CMP DL, 0x00                        ; check if first string is NULL
    JE .end                             ; returns if NULL
    CMP R8B, 0x00                       ; check if second string is NULL
    JE .end                             ; returns if NULL
    CMP DL, R8B                         ; check if match between chars
    JNE .end                            ; strings are not equal anymore, returning
    INC RCX                             ; incrementing the index
    JMP .loop                           ; else we loop

.transform_first:
    CMP DL, 65                          ; comparing first string current char with A
    JL .transform_second                ; it's lesser -> no need to transform
    CMP DL, 90                          ; comparing with Z
    JG .transform_second                ; it's greater -> no need to transform
    ADD DL, 32                          ; else lowercasing the char
    JMP .transform_second

.transform_second:
    CMP R8B, 65                         ; comparing first string current char with A
    JL .compare                         ; it's lesser -> no need to transform
    CMP R8B, 90                         ; comparing with Z
    JG .compare                         ; it's greater -> no need to transform
    ADD R8B, 32                          ; else lowercasing the char
    JMP .compare

.end:
	MOVZX RAX, DL	                    ; move first char in return and zero-fill the beginning (for negative)
	MOVZX RDX, R8B                      ; move second
	SUB	RAX, RDX		                ; subbing both 64 registers
    RET
