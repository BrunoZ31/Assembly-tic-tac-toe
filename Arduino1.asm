.device atmega328p
.org 0x0
LDI R16, 32
LDI R17, 32
LDI R22, 32
OUT DDRB, R16
OUT PORTB, R17

LOP0:
    INC R18
    CPI R18, 255
    BRNE LOP0
    clr r18
    inc r19
    CPI R19, 255
    BRNE LOP0
    clr r19
    inc r21
    cpi r21, 10
    brne lop0
    clr r21
    ADD R17, r22
    OUT PORTB, R17

    RJMP Lop0
