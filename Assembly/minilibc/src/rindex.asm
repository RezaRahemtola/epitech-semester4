BITS 64

section .text
    global rindex
    extern strrchr

rindex:
    CALL strrchr wrt ..plt
    RET
