.device atmega328p
.org 0x0
LDI R16, 1
LDI R17, 0; 10000
LDI r21, 32

OUT DDRB, R16
OUT PORTB, R17

LOP0:
    INC R18
    CPI R18, 255
    BRNE LOP0
    inc r19
    CPI R19, 255
    BRNE LOP0
    inc r20
    CPI R20, 255
    BRNE LOP0
    inc r21
    cpi r21, 255
    brne lop0

    ADD R17, r21
    OUT PORTB, R17
    RJMP LOP0
