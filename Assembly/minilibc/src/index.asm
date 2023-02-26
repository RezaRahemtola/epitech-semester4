BITS 64

section .text
    global index
    extern strchr

index:
    CALL strchr wrt ..plt
    RET
