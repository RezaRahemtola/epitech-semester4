BITS 64

section	.text
    global memmove
    extern memcpy

memmove:
    MOV RAX, RDI        ; set return value to the pointer
    CMP RSI, RDI        ; check if the strings are equal
    JL .lower           ; src is lower, moving chars from right to left to handle overlap
    JMP .greater        ; else we can memcpy normally

.lower:
    CMP RDX, 0                  ; checking if we have no char to move
    JE .end

    SUB RDX, 1                  ; decrement the count of chars to move (before to avoid -1 everywhere due to length)
    MOV R8B, BYTE [RSI + RDX]   ; saving the char to move
    MOV BYTE [RDI + RDX], R8B   ; moving into dest at
    JMP .lower                  ; looping again

.greater:
    CALL memcpy wrt ..plt       ; calling our memcpy
    RET                         ; returning (RAX already set)

.end:
    RET
