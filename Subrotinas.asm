
.org 0x00
.device ATMega328p

.macro InitializeStack
LDI R16, HIGH(RAMEND)
OUT SPH, R16
LDI R16, LOW(RAMEND)
OUT SPL, R16
.endmacro

rjmp INIT2

INIT2:
     InitializeStack
     ldi R30, LOW(ARRAY<<1)
     ldi R31, HIGH(ARRAY<<1)

     LDI R18,4 ; tamanho array
     MOV r17, r30
     ADD R17, R18 ; tamanho array
LOP2:
     LPM R1,Z+
     PUSH R1
     mov r16,r1

     LDI R27,1
     CP R30, R17
     BRNE LOP2



     LDI R19 , LOW(ARRAY)
FOR:
     POP R21
     ST X+, r21
     INC R19
     CPI R19 , HIGH(ARRAY)
     BRSH FOR

Loop:
	rjmp loop

ARRAY: .db 1,2,9,3
